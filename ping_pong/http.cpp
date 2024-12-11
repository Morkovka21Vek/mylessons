#include "assets.h"
//#include <cpr/cpr.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Socket.h"


void getHttpBtnCout(player& pl1, player& pl2, int windowWidth, int windowHeight) {
  //cpr::Response r = cpr::Get(cpr::Url{"http://192.168.4.1:80/api/get_buttons_count"});
  Connection conn("192.168.4.1", 80);

  int val1 = 0, val2 = 0;

  conn.tx("GET /api/get_buttons_count HTTP/1.1\r\nHost: 192.168.4.1\r\n\r\n");
  std::string s = conn.rx();

  conn.tx("GET /api/get_buttons_count HTTP/1.1\r\nHost: 192.168.4.1\r\n\r\n");
  s = conn.rx();
  std::cerr << s << std::endl;
  
  std::string body = s;

  std::string parsed;
  std::stringstream input_stringstream(static_cast<std::string>(body));

  if (getline(input_stringstream,parsed,';')) {
    std::cerr << parsed << std::endl;
    try { 
      val1 = std::stoi(parsed);
    } catch(...) {
      std::cerr << "ERROR" << std::endl;
    }
  }
  if (getline(input_stringstream,parsed,';')) {
    std::cerr << parsed << std::endl;
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
