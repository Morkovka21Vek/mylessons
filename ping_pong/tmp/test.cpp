#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <stdexcept>
#include <iostream>

int main(int argc, char const *argv[]) {
    int sock;
    //const char* adr_serv = "34.224.200.202";
    const char* adr_serv = "192.168.4.1";

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    inet_pton(AF_INET, adr_serv, &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
      throw std::runtime_error("Connection Failed");

    //std::string req_s = "GET /get HTTP/1.1\r\nHost: httpbin.org\r\nUser-Agent: curl/8.5.0\r\nAccept: */*\r\n\r\n";
    const std::string req_s = "GET /api/get_buttons_count HTTP/1.1\r\nHost: 192.168.4.1\r\nUser-Agent: curl/8.5.0\r\nAccept: */*\r\n\r\n";

    for(int i = 0; i < 2; ++i) {
      send(sock, req_s.c_str(), req_s.length(), 0);
      std::cout << std::endl << std::endl << "==============================" << std::endl;

      std::string full_request;
      unsigned int total_buffer_len = 0;
      while(1) {
        char buffer[1024] = {0};
        int n = read(sock, buffer, sizeof(buffer));
        if (n <= 0) std::cerr << "ERROR! N = " << n << std::endl;

        if (n >= 0)
          total_buffer_len += n;
        full_request.append(buffer);

        unsigned int request_len = 0;
        if((full_request.find("\r\n\r\n")) != std::string::npos) {
          request_len = std::stoi(
              full_request.substr(full_request.find("Content-Length: ") + 16,
              full_request.substr(full_request.find("Content-Length: ") + 16,
                  full_request.length()).find("\r\n"))) + full_request.find("\r\n\r\n") + 4;
        }

        //std::cout << buffer << std::endl;
        std::cout << request_len << std::endl;
        if (request_len != 0 && total_buffer_len >= request_len) break;
      }

      std::cout << full_request << std::endl;
      std::cout << "==============================" << std::endl;
    }
    close(sock);
    return 0;
}

