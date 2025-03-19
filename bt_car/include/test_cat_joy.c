//#include "mock_stdio.h"
//#include "../include/mocks/mock_unistd.h"
#include "mock_unistd.h"

//#include "car_joy.h"
//#include <linux/joystick.h>
//
//#include <string.h>
//#include <sys/types.h>
//#include <stdio.h>

void test_send_data_stick_simple() {
  //enum mode_joy mode = stick_joy;

  int joy_fd = 1;
  int car_serial_port = 2;

  //struct js_event event;
  //memset(&event, 0, sizeof(event));

  //read_ExpectAndReturn(joy_fd, &event, sizeof(event), sizeof(event));
  ////read_IgnoreArg_buffer();
  ////printf_IgnoreAndReturn(1);

  //const size_t SIZE_BUFF = 15;
  //char buffer[SIZE_BUFF];
  //memset(&buffer, 0, SIZE_BUFF);
  //ssize_t len_write = snprintf(buffer, SIZE_BUFF, "0,85\n");

  //write_ExpectAndReturn(car_serial_port, buffer, len_write, len_write);
  //send_data(mode, joy_fd, car_serial_port);
}
