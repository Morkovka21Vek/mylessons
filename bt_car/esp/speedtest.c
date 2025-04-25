#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

char* parse_argument(int argc, char *argv[], const char *param_short, const char *param_long) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], param_short) == 0 || strcmp(argv[i], param_long) == 0) {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                return argv[i + 1];
            } else {
                return "";
            }
        }
    }
    return NULL;
}

int init_sock(int* sockfd, struct sockaddr_in* serv_addr, int port, const char* serv_url){
    int result = 0;

    memset(serv_addr, 0, sizeof(*serv_addr));

    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port = htons(port);

    do {
        if((*sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        {
            perror("Error : Could not create socket\n");
            result = 1;
            break;
        }

        if(inet_pton(AF_INET, serv_url, &serv_addr->sin_addr) <= 0)
        {
            perror("inet_pton error occured\n");
            result = 2;
            break;
        }

        if(connect(*sockfd, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) == -1)
        {
            perror("Error : Connect Failed\n");
            result = 3;
            break;
        }
    } while(0);

    return result;
}

int init_serial(int device_fd, int speed){
    int return_code = -1;
    struct termios options;
    memset(&options, 0, sizeof(options));

    if (tcgetattr(device_fd, &options) == -1) {
        fprintf(stderr, "Ошибка получения настроек serial: %s\n", strerror(errno));
        return_code = 1;
        goto ERROR;
    }

    speed_t baud_rate;
    switch (speed) {
        case 9600:   baud_rate = B9600;   break;
        case 19200:  baud_rate = B19200;  break;
        case 115200: baud_rate = B115200; break;
        default:
            perror("Скорость не поддерживается\n");
            return_code = 2;
            goto ERROR;
    }
    cfsetispeed(&options, baud_rate);
    cfsetospeed(&options, baud_rate);

    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~PARENB;
    options.c_cflag |= CREAD | CLOCAL;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
    options.c_oflag &= ~OPOST;
    options.c_cc[VMIN] = 1;
    options.c_cc[VTIME] = 0;

    if (tcsetattr(device_fd, TCSANOW, &options) == -1) {
        fprintf(stderr, "Ошибка установки serial: %s\n", strerror(errno));
        return_code = 3;
        goto ERROR;
    }

    return_code = 0;
ERROR:
    return return_code;
}

int main(int argc, char *argv[]) {
    int return_result = -1;
    int sockfd;

    char *arg_device = parse_argument(argc, argv, "-d", "--device");
    if (arg_device == NULL || strlen(arg_device) == 0) arg_device = "/dev/ttyUSB0";
    char *arg_server = parse_argument(argc, argv, "-s", "--server");
    if (arg_server == NULL || strlen(arg_server) == 0) arg_server = "192.168.4.1";
    char *arg_server_port = parse_argument(argc, argv, "-p", "--port");
    if (arg_server_port == NULL || strlen(arg_server_port) == 0) arg_server_port = "81";
    char *arg_baudrate = parse_argument(argc, argv, "-b", "--baudrate");
    if (arg_baudrate == NULL || strlen(arg_baudrate) == 0) arg_baudrate = "115200";
    char *arg_only = parse_argument(argc, argv, "-o", "--only");
    char *arg_count = parse_argument(argc, argv, "-c", "--count");
    if (arg_count == NULL || strlen(arg_count) == 0) arg_count = "100";

    //printf("%s\n", arg_device);
    //printf("%s\n", arg_server);
    //printf("%s\n", arg_server_port);
    //printf("%s\n", arg_baudrate);
    //printf("%s\n", arg_count);

    int device_fd = open(arg_device, O_RDWR | O_NOCTTY);
    if (device_fd == -1) {
        fprintf(stderr, "Ошибка открытия serial: %s\n", strerror(errno));
        goto ERROR;
    }
    if (init_serial(device_fd, atoi(arg_baudrate)) != 0) {
        goto ERROR_CLOSE_DEV;
    }

    struct sockaddr_in serv_addr;
    if (init_sock(&sockfd, &serv_addr, atoi(arg_server_port), arg_server) != 0) {
        goto ERROR_CLOSE_DEV;
    }

    double time_sum = 0;
    unsigned int fail_count = 0;
    for (int i = 0; i < atoi(arg_count); i++) {
        const size_t BUFF_SIZE = 64;
        char buff[BUFF_SIZE];
        memset(&buff, 0, BUFF_SIZE);

        const size_t DATABUFF_SIZE = 64;
        char databuff[DATABUFF_SIZE];
        memset(&databuff, 0, DATABUFF_SIZE);

        snprintf(databuff, DATABUFF_SIZE, "%d,%d;", i, i+1);

        struct timespec time_start, time_end;
        clock_gettime(CLOCK_MONOTONIC, &time_start);

        //int write_len = write(sockfd, databuff, strlen(databuff));
        ssize_t write_len = sendto(sockfd, databuff, strlen(databuff), 0, (struct sockaddr*)NULL, sizeof(serv_addr));
        if (write_len == -1) {
            fprintf(stderr, "Ошибка записи в сокет: %s\n", strerror(errno));
            goto ERROR_CLOSE_DEV;
        }

        ssize_t read_len = read(device_fd, buff, BUFF_SIZE - 1);
        if (read_len == -1) {
            fprintf(stderr, "Ошибка чтения serial: %s\n", strerror(errno));
            goto ERROR_CLOSE_DEV;
        }
        buff[read_len] = 0;

        clock_gettime(CLOCK_MONOTONIC, &time_end);

        if(strcmp(buff, databuff) == 0) {
            if (arg_only == NULL)
                printf("OK: %s\t", buff);
        } else {
            if (arg_only == NULL)
                printf("FAIL(%s): %s\t", databuff, buff);
            fail_count++;
        }

        double time_diff = (time_end.tv_sec - time_start.tv_sec) * 1000.0
                         + (time_end.tv_nsec - time_start.tv_nsec) / 1000000.0;
        if (arg_only != NULL)
            printf("%f\n", time_diff);
        else
            printf("Time: %f\n\n", time_diff);
        time_sum += time_diff;
    }

    if (arg_only == NULL) {
        printf("Mean: %f\n", time_sum / atoi(arg_count));
        printf("Failed: %d\n", fail_count);
    }

    return_result = 0;
ERROR_CLOSE_DEV:
    close(device_fd);
ERROR:
    return return_result;
}
