#include <fcntl.h>
#include <linux/joystick.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
//#include <cstring>
#include <sstream>

int main(int argc, char** argv) {
    struct winsize windowSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize);

    //int baudRate = B9600;
    unsigned int baudRate = 9600;

    //if(argc != 2)
    //{
    //  std::cout << "Usage: " << argv[0] << " [j / w]" << std::endl;
    //  return 1;
    //}

    int fd = open("/dev/input/js0", O_RDONLY);
    if (fd < 0) {
        //std::cerr << "Не удалось открыть устройство: " << strerror(errno) << std::endl;
        std::cerr << "Не удалось открыть устройство" << std::endl;
        return 1;
    }

    int car_serial_port = open("/dev/rfcomm1", O_RDWR| O_NOCTTY);
    if (car_serial_port < 0) {
      //printf("Error %i from open: %s\n", errno, strerror(errno));
      std::cerr << "Не удалось открыть устройство" << std::endl;
    }

    //==========CONFIG_CAR==========//
    struct termios options;
    tcgetattr(car_serial_port, &options);
    cfsetispeed(&options, baudRate);
    cfsetospeed(&options, baudRate);
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
    int x_axis=0, y_axis=0;

    int old_x_axis_map = -1, old_y_axis_map = -1;

    struct js_event e;
    while (true) {
      if (read(fd, &e, sizeof(e)) == sizeof(e)) {
        //if (e.type == JS_EVENT_AXIS) {
        //    std::cout << "Ось: " << (int)e.number << " Значение: " << e.value << std::endl;
        //} else if (e.type == JS_EVENT_BUTTON) {
        //    std::cout << "Кнопка: " << (int)e.number << " Статус: " << (int)e.value << std::endl;
        //}
        if ((int)e.number == 0) {
          x_axis = e.value;
          std::cout << "\033[10;0H";
          for (int i = 0; i < windowSize.ws_col; i++)
            std::cout << ' ';
          std::cout << "\033[10;0H";
          std::cout << "X: " << ((float)e.value+32768)/(32768*2)*100 << '%' << std::endl;
        }
        if ((int)e.number == 4) {
          y_axis = e.value;
          std::cout << "\033[11;0H";
          for (int i = 0; i < windowSize.ws_col; i++)
            std::cout << ' ';
          std::cout << "\033[11;0H";
          std::cout << "Y: " << ((float)e.value+32768)/(32768*2)*100 << '%' << std::endl;
        }
      int x_axis_map=0, y_axis_map=0;
      bool flag_dir = false;

      if(y_axis < 0) {
        y_axis_map = ((float)(-y_axis)/32768*255);
      } else {
        flag_dir = true;
        y_axis_map = ((float)y_axis/32768*255);
      }

      y_axis_map = static_cast<int>(y_axis_map/10)*10;

      //x_axis_map = 120 + (x_axis - (-32768)) * (55 - 120) / (32767 - (-32768));
      x_axis_map = static_cast<int>((120 + (x_axis - (-32768)) * (55 - 120) / (32767 - (-32768)))/5)*5;

      std::ostringstream oss;
      oss << flag_dir << ',' << y_axis_map << ',' << x_axis_map << '\n';

      std::string dataToSend = oss.str();

      std::cout << "\033[12;1H";
      //std::cout << flag_dir << ',' << y_axis_map << ',' << x_axis_map << ';' << std::endl;
      for (int i = 0; i < windowSize.ws_col; i++)
        std::cout << ' ';
      std::cout << "\033[12;1H";

      std::cout << dataToSend.c_str() << std::endl;

      if (old_x_axis_map != x_axis_map || old_y_axis_map != y_axis_map) {
        old_x_axis_map = x_axis_map;
        old_y_axis_map = y_axis_map;
        ssize_t bytesWritten = write(car_serial_port, dataToSend.c_str(), dataToSend.size());
      }
      //std::cout << bytesWritten << std::endl;

      /*
      char buffer[256];
      ssize_t bytesRead = read(car_serial_port, buffer, sizeof(buffer) - 1);
      if (bytesRead < 0) {
          //std::cerr << "Ошибка чтения из последовательного порта: " << strerror(errno) << std::endl;
          std::cerr << "Ошибка чтения из последовательного порта: " << std::endl;
      } else if (bytesRead > 0) {
          buffer[bytesRead] = 0;
          std::cout << "Прочитано " << bytesRead << " байт:]\n> " << buffer << std::endl;
      }
      */
      }
    }

    close(fd);
    return 0;
}

