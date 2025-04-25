#include <fcntl.h>
#include <linux/joystick.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include <string.h>

#include "car_joy.h"

#if defined(DEBUG) && !defined(DEBUG_NEWLINE)
  #define debugf(y, str, ...) {\
            printf("\033[%d;1H", y);\
            struct winsize windowSize;\
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize);\
            for (int i = 0; i < windowSize.ws_col-1; i++)\
              printf(" ");\
            printf("\033[%d;1H", y);\
            printf(str, __VA_ARGS__);\
          }
#elif defined(DEBUG) && defined(DEBUG_NEWLINE)
  #define debugf(y, str, ...) printf(str, __VA_ARGS__);
#else
  #define debugf(y, str, ...)
#endif

static int sockfd;
static struct sockaddr_in serv_addr;

void stick_joy_getVal(struct js_event js_e, int *x_axis, int *y_axis);
void game_joy_getVal (struct js_event js_e, int *x_axis, int *y_axis);
void rudder_getVal   (struct js_event js_e, int *x_axis, int *y_axis);

ssize_t send_data(enum mode_joy joy_mode, int joy_fd) {
    struct js_event js_e;
    static int x_axis=0, y_axis=0,
               old_x_axis = -1, old_y_axis = -1;

    if (read(joy_fd, &js_e, sizeof(js_e)) == sizeof(js_e)) {
        switch(joy_mode) {
          case stick_joy: stick_joy_getVal(js_e, &x_axis, &y_axis); break;
          case game_joy:  game_joy_getVal (js_e, &x_axis, &y_axis); break;
          case rudder:    rudder_getVal   (js_e, &x_axis, &y_axis); break;
        }

        const size_t SIZE_BUFF = 15;
        char buffer[SIZE_BUFF];
        memset(&buffer, 0, SIZE_BUFF);

        ssize_t len_write = snprintf(buffer, SIZE_BUFF, "%d,%d\n", y_axis, x_axis);

        if (old_x_axis != x_axis || old_y_axis != y_axis) {
          //ssize_t bytesWritten = write(car_serial_port, buffer, len_write);
          ssize_t bytesWritten = sendto(sockfd, buffer, len_write, 0, (struct sockaddr*)NULL, sizeof(serv_addr));

          if (bytesWritten >= 0)
          {
            old_x_axis = x_axis;
            old_y_axis = y_axis;
          }

          debugf(3, "Send %ld bytes, str: %s\n", bytesWritten, buffer);
          return bytesWritten;
        }
        else
            return 0;
    }
    return -1;
}

int scale_joystick(int value, int max) {
    return (value + 32767) * max / 65534;
}

void stick_joy_getVal(struct js_event js_e, int *x_axis, int *y_axis) {
  switch ((int)js_e.number)
  {
    case 0:
      *x_axis = scale_joystick(js_e.value, 99);
      debugf(1, "X: %d\n", *x_axis);
      break;
    case 4:
      *y_axis = scale_joystick(js_e.value, 510);
      debugf(2, "Y: %d\n", *y_axis);
      break;
  }
}

void game_joy_getVal(struct js_event js_e, int *x_axis, int *y_axis) {
  switch ((int)js_e.number)
  {
    case 0:
    case 3:
      *x_axis = scale_joystick(js_e.value, 99);
      debugf(1, "X: %d\n", *x_axis);
      break;
    case 2:
      *y_axis = 255 + scale_joystick(js_e.value, 255);
      debugf(2, "Y(axis 2): %d\n", *y_axis);
      break;
    case 5:
      *y_axis = 255 - scale_joystick(js_e.value, 255);
      debugf(2, "Y(axis 5): %d\n", *y_axis);
      break;
  }
}

void rudder_getVal(struct js_event js_e, int *x_axis, int *y_axis) {
  switch ((int)js_e.number)
  {
    case 0:
    {
      int crop_eval_x = (js_e.value > 7000) ? 7000 : js_e.value;
      crop_eval_x = (crop_eval_x < -7000) ? -7000 : crop_eval_x;
      *x_axis = (crop_eval_x + 7000) * 99 / 14000;

      debugf(1, "X: %d\n", *x_axis);
      break;
    }
    case 3:
      *y_axis = 255 + scale_joystick(js_e.value, 255);
      debugf(2, "3)real: %d; y_axis: %d\n", js_e.value, *y_axis);
      break;
    case 2:
      *y_axis = 255 - scale_joystick(js_e.value, 255);
      debugf(2, "2)real: %d; y_axis: %d\n", js_e.value, *y_axis);
      break;
  }
}

int init_sock(int port, const char* serv_url) {
    int result = 0;

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    do {
        if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        {
            perror("Error : Could not create socket\n");
            result = 1;
            break;
        }

        if(inet_pton(AF_INET, serv_url, &serv_addr.sin_addr) <= 0)
        {
            perror("inet_pton error occured\n");
            result = 2;
            break;
        }

        if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        {
            perror("Error : Connect Failed\n");
            result = 3;
            break;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) {
            perror("setsockopt failed");
            result = 4;
            break;
        }

    } while(0);

    printf("sockinit result = %d\n", result);
    return result;
}
