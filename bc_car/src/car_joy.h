
#ifndef CAR_JOY_H
#define CAR_JOY_H

enum mode_joy {stick_joy, game_joy, rudder};
ssize_t send_data(enum mode_joy joy_mode, int joy_fd, int car_serial_port);

#endif // CAR_JOY_H
