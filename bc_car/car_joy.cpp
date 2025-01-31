#include <fcntl.h>
#include <linux/joystick.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include <cstring>
#include <sstream>
#include "config_menu.h"

#ifndef BAUDRATE
  #define baud_rate 9600
#else
  #define baud_rate BAUDRATE
#endif


#ifdef DEBUG
  #define debugf(y, str, ...)\
          printf("\033[%d;1H", y);\
          ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize);\
          for (int i = 0; i < windowSize.ws_col-1; i++)\
            printf(" ");\
          printf("\033[%d;1H", y);\
          printf(str, __VA_ARGS__);
#else
  #define debugf(y, str, ...)
#endif

int main() {
    struct winsize windowSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize);

    mode_joy joy_mode = stick_joy;
    start_menu(joy_mode, windowSize.ws_col, windowSize.ws_row);

    printf("\033[1;1H");
    for (int y = 0; y < windowSize.ws_row; y++) {
      for (int x = 0; x < windowSize.ws_col; x++)
        printf(" ");
      printf("\n");
    }
    printf("\033[1;1H\n");

    int result = -1;

    const int joy_fd = open("/dev/input/js0", O_RDONLY);
    const int car_serial_port = open("/dev/rfcomm0", O_RDWR| O_NOCTTY);

    if (joy_fd < 0) {
        fprintf(stderr, "%s: Не удалось открыть устройство(джойстик) (ERROR: %d; Line: %d): %s\n", __FILE__, errno, __LINE__, strerror(errno));
        result = 1;

        goto exit_error;
    }
    if (car_serial_port < 0) {
        fprintf(stderr, "%s: Не удалось открыть устройство(машина)   (ERROR: %d; Line: %d): %s\n", __FILE__, errno, __LINE__, strerror(errno));
        printf("\x1B[32musing:\033[0m\nsudo rfcomm bind /dev/rfcomm0 <BLUETOOTH MAC>\n");
        result = 2;

        goto exit_error_bluetooth;
    }

    //==========CONFIG_CAR==========//
    struct termios options;
    tcgetattr(car_serial_port, &options);
    cfsetispeed(&options, baud_rate);
    cfsetospeed(&options, baud_rate);
    options.c_cflag |= (CLOCAL | CREAD); // Ignore modem control lines and enable receiver
    options.c_cflag &= ~PARENB; // No parity
    options.c_cflag &= ~CSTOPB; // 1 stop bit
    options.c_cflag &= ~CSIZE; // Clear the current data size setting
    options.c_cflag |= CS8; // 8 data bits
    options.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
    options.c_oflag &= ~OPOST; // Raw output
    tcsetattr(car_serial_port, TCSANOW, &options);
    //==========CONFIG_CAR==========//

    struct js_event e;
    while (true) {
      static int x_axis=0, y_axis=0,
                 old_x_axis_map = -1, old_y_axis_map = -1;

      if (read(joy_fd, &e, sizeof(e)) == sizeof(e)) {
        switch(joy_mode) {

          case stick_joy:
            switch ((int)e.number)
            {
              case 0:
                x_axis = e.value;
                debugf(1, "X: %f\n", ((float)e.value+32768)/(32768*2)*100);
                break;
              case 4:
                y_axis = e.value;
                debugf(2, "Y: %f\n", ((float)e.value+32768)/(32768*2)*100);
                break;
            }
            break;

          case game_joy:
            switch ((int)e.number)
            {
              case 0:
              case 3:
                x_axis = e.value;
                debugf(1, "X: %f\n", ((float)e.value+32768)/(32768*2)*100);
                break;
              case 2:
                y_axis = static_cast<int>(e.value / 2) + (32768 / 2);
                debugf(2, "Y: %f\n", ((float)e.value+32768)/(32768*2)*100/2-50);
                break;
              case 5:
                y_axis = -(static_cast<int>(e.value / 2) + (32768 / 2));
                debugf(2, "Y: %f\n", ((float)e.value+32768)/(32768*2)*100/2+50);
                break;
            }
            break;

          case rudder:
            switch ((int)e.number)
            {
              case 0:
                do {
                  int crop_eval_x = (e.value > 7000) ? 7000 : e.value;
                  crop_eval_x = (crop_eval_x < -7000) ? -7000 : crop_eval_x;
                  x_axis = ((float)crop_eval_x - (-7000)) / (7000 - (-7000)) * (32767 - (-32768)) + (-32767);

                  debugf(1, "crop_eval_x: %d real: %d; x_axis: %d; X: %f\n", crop_eval_x, e.value, x_axis, ((float)x_axis+32768)/(32768*2)*100);
                } while(0);
                break;
              case 3:
                y_axis = 32768 - (static_cast<int>(e.value / 2) + (32768 / 2));
                debugf(2, "real: %d; y_axis: %d\n", e.value, y_axis);
                break;
              case 2:
                y_axis = -(32768 - (static_cast<int>(e.value / 2) + (32768 / 2)));
                debugf(2, "real: %d; y_axis: %d\n", e.value, y_axis);
                break;
          }
            break;
        }

        int x_axis_map = static_cast<int>((120 + (x_axis - (-32768)) * (55 - 120) / (32768 - (-32768))) / 5) * 5;
        int y_axis_map = static_cast<int>((static_cast<float>(-y_axis) / 32768 * 255) / 10) * 10;


        std::ostringstream oss;
        oss << y_axis_map << ',' << x_axis_map << '\n';
        std::string dataToSend = oss.str();

        if (old_x_axis_map != x_axis_map || old_y_axis_map != y_axis_map) {
          old_x_axis_map = x_axis_map;
          old_y_axis_map = y_axis_map;

#ifdef DEBUG
          ssize_t bytesWritten = write(car_serial_port, dataToSend.c_str(), dataToSend.size());
#else
          write(car_serial_port, dataToSend.c_str(), dataToSend.size());
#endif
          debugf(3, "Send %ld bytes, str: %s\n", bytesWritten, dataToSend.c_str());
        }
      }
    }

    result = 0;
exit_error_bluetooth:
    close(joy_fd);
exit_error:
    close(car_serial_port);

    return result;
}

