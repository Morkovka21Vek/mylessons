#include <fcntl.h>
#include <linux/joystick.h>
#include <sys/types.h>
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

void stick_joy_getVal(struct js_event js_e, int *x_axis, int *y_axis);
void game_joy_getVal (struct js_event js_e, int *x_axis, int *y_axis);
void rudder_getVal   (struct js_event js_e, int *x_axis, int *y_axis);

ssize_t send_data(enum mode_joy joy_mode, int joy_fd, int car_serial_port) {
    struct js_event js_e;
    static int x_axis=0, y_axis=0,
               old_x_axis_map = -1, old_y_axis_map = -1;

    if (read(joy_fd, &js_e, sizeof(js_e)) == sizeof(js_e)) {
      switch(joy_mode) {
        case stick_joy: stick_joy_getVal(js_e, &x_axis, &y_axis); break;
        case game_joy:  game_joy_getVal (js_e, &x_axis, &y_axis); break;
        case rudder:    rudder_getVal   (js_e, &x_axis, &y_axis); break;
      }

      int x_axis_map = (int)((120 + (x_axis - (-32768)) * (55 - 120) / (32768 - (-32768))) / 5) * 5;
      int y_axis_map = (int)(((float)-y_axis / 32768 * 255) / 10) * 10;

      const size_t SIZE_BUFF = 15;
      char buffer[SIZE_BUFF];
      memset(&buffer, 0, SIZE_BUFF);

      ssize_t len_write = snprintf(buffer, SIZE_BUFF, "%d,%d\n", y_axis_map, x_axis_map);

      if (old_x_axis_map != x_axis_map || old_y_axis_map != y_axis_map) {
        ssize_t bytesWritten = write(car_serial_port, buffer, len_write);

        if (bytesWritten >= 0)
        {
          old_x_axis_map = x_axis_map;
          old_y_axis_map = y_axis_map;
        }

        debugf(3, "Send %ld bytes, str: %s\n", bytesWritten, buffer);
        return bytesWritten;
        }
      }
    return -1;
}

void stick_joy_getVal(struct js_event js_e, int *x_axis, int *y_axis) {
  switch ((int)js_e.number)
  {
    case 0:
      *x_axis = js_e.value;
      debugf(1, "X: %d\n", x_axis);
      break;
    case 4:
      *y_axis = js_e.value;
      debugf(2, "Y: %d\n", y_axis);
      break;
  }
}

void game_joy_getVal(struct js_event js_e, int *x_axis, int *y_axis) {
  switch ((int)js_e.number)
  {
    case 0:
    case 3:
      *x_axis = js_e.value;
      debugf(1, "X: %d\n", x_axis);
      break;
    case 2:
      *y_axis = (int)(js_e.value / 2) + (32768 / 2);
      debugf(2, "Y(axis 2): %d\n", y_axis);
      break;
    case 5:
      *y_axis = -((int)(js_e.value / 2) + (32768 / 2));
      debugf(2, "Y(axis 5): %d\n", y_axis);
      break;
  }
}

void rudder_getVal(struct js_event js_e, int *x_axis, int *y_axis) {
  switch ((int)js_e.number)
  {
    case 0:
      do {
        int crop_eval_x = (js_e.value > 7000) ? 7000 : js_e.value;
        crop_eval_x = (crop_eval_x < -7000) ? -7000 : crop_eval_x;
        *x_axis = ((float)crop_eval_x - (-7000)) / (7000 - (-7000)) * (32767 - (-32768)) + (-32767);

        debugf(1, "crop_eval_x: %d real: %d; x_axis: %d; X: %f\n", crop_eval_x, js_e.value, x_axis, ((float)x_axis+32768)/(32768*2)*100);
      } while(0);
      break;
    case 3:
      *y_axis = 32768 - ((int)(js_e.value / 2) + (32768 / 2));
      debugf(2, "real: %d; y_axis: %d\n", js_e.value, y_axis);
      break;
    case 2:
      *y_axis = -(32768 - ((int)(js_e.value / 2) + (32768 / 2)));
      debugf(2, "real: %d; y_axis: %d\n", js_e.value, y_axis);
      break;
  }
}
