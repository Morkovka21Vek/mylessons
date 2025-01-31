#include <fcntl.h>
#include <linux/joystick.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include <cstring>
#include <sstream>

#ifndef BAUDRATE
  #define baud_rate 9600
#else
  #define baud_rate BAUDRATE
#endif


#ifdef DEBUG
  #define debugf(y, str, ...)\
          printf("\033[%d;1H", y);\
          struct winsize windowSize;\
          ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize);\
          for (int i = 0; i < windowSize.ws_col-1; i++)\
            printf(" ");\
          printf("\033[%d;1H", y);\
          printf(str, __VA_ARGS__);
#else
  #define debugf(y, str, ...)
#endif

int main(int argc, char** argv) {
    int result = -1;

    const int joy_fd = open("/dev/input/js0", O_RDONLY);
    const int car_serial_port = open("/dev/rfcomm0", O_RDWR| O_NOCTTY);

    if (joy_fd < 0) {
        fprintf(stderr, "%s: Не удалось открыть устройство(джойстик) (ERROR: %d; Line: %d): %s\n", __FILE__, errno, __LINE__, strerror(errno));
        goto exit_error;
    }
    if (car_serial_port < 0) {
        fprintf(stderr, "%s: Не удалось открыть устройство(машина)   (ERROR: %d; Line: %d): %s\n", __FILE__, errno, __LINE__, strerror(errno));
        printf("\x1B[32musing:\033[0m\nsudo rfcomm bind /dev/rfcomm0 <BLUETOOTH MAC>\n");
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
        if ((int)e.number == 0) {
          x_axis = e.value;
          debugf(1, "X: %f\n", ((float)e.value+32768)/(32768*2)*100);
        }
        else if ((int)e.number == 4) {
          y_axis = e.value;
          debugf(2, "Y: %f\n", ((float)e.value+32768)/(32768*2)*100);
        }

        int x_axis_map = static_cast<int>((120 + (x_axis - (-32768)) * (55 - 120) / (32768 - (-32768))) / 5) * 5;
        int y_axis_map = static_cast<int>((static_cast<float>(-y_axis) / 32768 * 255) / 10) * 10;


        std::ostringstream oss;
        oss << y_axis_map << ',' << x_axis_map << '\n';
        std::string dataToSend = oss.str();

        if (old_x_axis_map != x_axis_map || old_y_axis_map != y_axis_map) {
          old_x_axis_map = x_axis_map;
          old_y_axis_map = y_axis_map;

          ssize_t bytesWritten = write(car_serial_port, dataToSend.c_str(), dataToSend.size());
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
