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

int init_sock(int* sockfd, int port, const char* serv_url){
    int result = 0;

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    do {
        //if((*sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        if((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            perror("Error : Could not create socket\n");
            result = 1;
            break;
        }

        if(inet_pton(AF_INET, serv_url, &serv_addr.sin_addr) <= 0)
        {
            perror("inet_pton error occured\n");
            result = 2;
            break;
        }

        if(connect(*sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            perror("Error : Connect Failed\n");
            result = 3;
            break;
        }
    } while(0);

    return result;
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
    //char *arg_baudrate = parse_argument(argc, argv, "-b", "--baudrate");
    //if (arg_baudrate == NULL || strlen(arg_baudrate) == 0) arg_baudrate = "9600";
    char *arg_only = parse_argument(argc, argv, "-o", "--only");
    char *arg_count = parse_argument(argc, argv, "-c", "--count");
    if (arg_count == NULL || strlen(arg_count) == 0) arg_count = "100";

    printf("%s\n", arg_device);
    printf("%s\n", arg_server);
    printf("%s\n", arg_server_port);
    //printf("%s\n", arg_baudrate);
    printf("%s\n", arg_count);

    const char* SEND_DATA = "\r\n\r\nHello World;;";

    int device_fd = open(arg_device, O_RDWR | O_NOCTTY);
    if (device_fd == -1) {
        fprintf(stderr, "Ошибка открытия serial: %s\n", strerror(errno));
        goto ERROR;
    }

    struct termios options;
    memset(&options, 0, sizeof(options));

    if (tcgetattr(device_fd, &options) == -1) {
        fprintf(stderr, "Ошибка получения настроек serial: %s\n", strerror(errno));
        goto ERROR_CLOSE_DEV;
    }
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~PARENB;
    options.c_cflag |= CREAD | CLOCAL;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
    options.c_oflag &= ~OPOST;
    options.c_cc[VMIN] = strlen(SEND_DATA) - 4;
    options.c_cc[VTIME] = 0;

    if (tcsetattr(device_fd, TCSANOW, &options) == -1) {
        fprintf(stderr, "Ошибка установки serial: %s\n", strerror(errno));
        goto ERROR_CLOSE_DEV;
    }

    int error_code = 0;
    if ((error_code = init_sock(&sockfd, atoi(arg_server_port), arg_server)) != 0) {
        fprintf(stderr, "Ошибка инициализации сокета: %d\n", error_code);
        goto ERROR_CLOSE_DEV;
    }

    double time_sum = 0;
    unsigned int fail_count = 0;
    short int *array = (short int *)malloc(atoi(arg_count) * sizeof(short int));
    for (int i = 0; i < atoi(arg_count); i++) {
        const size_t BUFFSIZE = 64;
        char buff[BUFFSIZE];
        memset(&buff, 0, BUFFSIZE);

        time_t time_start = time(0);
        int write_len = write(sockfd, SEND_DATA, strlen(SEND_DATA));
        if (write_len == -1) {
            fprintf(stderr, "Ошибка записи в сокет: %s\n", strerror(errno));
            goto ERROR_FREE_ARR;
        }

        ssize_t read_len = read(device_fd, buff, BUFFSIZE - 1);
        if (read_len == -1) {
            fprintf(stderr, "Ошибка чтения serial: %s\n", strerror(errno));
            goto ERROR_FREE_ARR;
        }
        buff[read_len] = 0;

        time_t time_end = time(0);

        if(strcmp(buff, "Hello World;;") == 0) {
            if (arg_only == NULL)
                printf("OK: %s\t", buff);
        } else {
            if (arg_only == NULL)
                printf("FAIL: %s\t", buff);
            fail_count++;
        }

        if (arg_only != NULL)
            printf("%f\n", difftime(time_end, time_start));
        else
            printf("Time: %f\n\n", difftime(time_end, time_start));
        array[i] = (short int)difftime(time_end, time_start);
        time_sum += difftime(time_end, time_start);
    }

    if (arg_only == NULL) {
        printf("Mean: %f\n", time_sum / atoi(arg_count));
        printf("Failed: %d\n", fail_count);
    }

    return_result = 0;
ERROR_FREE_ARR:
    free(array);
ERROR_CLOSE_DEV:
    close(device_fd);
ERROR:
    return return_result;
}
