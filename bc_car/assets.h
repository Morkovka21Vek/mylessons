enum mode_joy {stick_joy, game_joy, rudder};
int send_data(mode_joy joy_mode, const int joy_fd, const int car_serial_port);
