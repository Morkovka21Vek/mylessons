#include "include/assets.h"
#include <sstream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <unistd.h>

int sock;

void initSocket() {
  sock = socket(AF_INET, SOCK_STREAM, 0);
  const char* adr_serv = "192.168.4.1";

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(80);

  inet_pton(AF_INET, adr_serv, &serv_addr.sin_addr);

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    throw std::runtime_error("\nConnection Failed \n");
}

void getHttpBtnCout(player& pl1, player& pl2, int windowWidth, int windowHeight) {
  //std::cout << sock << std::endl;

  const std::string req_s = "GET /api/get_buttons_count HTTP/1.1\r\nHost: 192.168.4.1\r\nUser-Agent: curl/8.5.0\r\nAccept: */*\r\n\r\n";

  int val1 = 0, val2 = 0;

  send(sock, req_s.c_str(), req_s.length(), 0);

  std::string full_request;
  unsigned int total_buffer_len = 0;

  while(1) {
    char buffer[1024] = {0};
    int n = read(sock, buffer, sizeof(buffer));
    if (n <= 0) std::cerr << "ERROR! N = " << n << std::endl;

    if (n >= 0) {
      total_buffer_len += n;
      full_request.append(buffer);
    }

    unsigned int request_len = 0;
    if((full_request.find("\r\n\r\n")) != std::string::npos) {
      request_len = std::stoi(
          full_request.substr(full_request.find("Content-Length: ") + 16,
          full_request.substr(full_request.find("Content-Length: ") + 16,
              full_request.length()).find("\r\n"))) + full_request.find("\r\n\r\n") + 4;
    }

    if (request_len != 0 && total_buffer_len >= request_len) break;
  }

  //std::cerr << full_request << std::endl;

  std::string body = full_request.substr(full_request.find("\r\n\r\n")+4, full_request.length());

  std::string parsed;
  std::stringstream input_stringstream(static_cast<std::string>(body));

  if (getline(input_stringstream,parsed,';')) {
    //std::cerr << parsed << std::endl;
    try { 
      val1 = std::stoi(parsed);
    } catch(...) {
      std::cerr << "ERROR" << std::endl;
    }
  }
  if (getline(input_stringstream,parsed,';')) {
    //std::cerr << parsed << std::endl;
    try { 
      val2 = std::stoi(parsed);
    } catch(...) {
      std::cerr << "ERROR" << std::endl;
    }
  }

  pl1.pos += val1;
  pl1.pos -= val2;

  if (pl1.pos < 0) pl1.pos = 0;
  else if (pl1.pos + pl1.height > windowHeight) pl1.pos = windowHeight - pl1.height;

  if (pl2.pos < 0) pl2.pos = 0;
  else if (pl2.pos + pl2.height > windowHeight) pl2.pos = windowHeight - pl2.height;
  
}
