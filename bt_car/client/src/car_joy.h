#ifndef CAR_JOY_H
#define CAR_JOY_H

#include <sys/socket.h>

enum mode_joy {stick_joy, game_joy, rudder};
ssize_t send_data(enum mode_joy joy_mode, int joy_fd);
int init_sock(int port, const char* serv_url);

#endif // CAR_JOY_H
