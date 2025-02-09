#include <mock_stdio.h>
#include <mock_unistd.h>
#include <assets.h>
#include <linux/joystick.h>
#include <string>

void test_send_data_stick_simple() {
  mode_joy mode = stick_joy;

  int joy_fd = 1;
  int car_serial_port = 2;

  struct js_event event;
  memset(&event, 0, sizeof(event));

  read_ExpectAndReturn(joy_fd, &event, sizeof(event), sizeof(event));
  read_IgnoreArg_buffer();
  printf_IgnoreAndReturn(1);

  std::string str = "0,85\n";

  write_ExpectAndReturn(car_serial_port, str.c_str(), str.size(), str.size());
  send_data(mode, joy_fd, car_serial_port);
}
