#include "assets.h"
#include <cpr/cpr.h>
#include <string>
#include <iostream>
#include <sstream>


void getHttpBtnCout(player& pl1, player& pl2, int windowWidth, int windowHeight) {
  cpr::Response r = cpr::Get(cpr::Url{"http://192.168.4.1:80/api/get_buttons_count"});
  //cpr::Response r = cpr::Get(cpr::Url{"http://www.httpbin.org/get"});

  int val1 = 0, val2 = 0;

  std::string parsed;
  std::stringstream input_stringstream(static_cast<std::string>(r.text));

  if (getline(input_stringstream,parsed,';')) {
    //std::cerr << parsed << std::endl;
    val1 = std::stoi(parsed);
  }
  if (getline(input_stringstream,parsed,';')) {
    //std::cerr << parsed << std::endl;
    val2 = std::stoi(parsed);
  }

  pl1.pos += val1;
  pl1.pos -= val2;

  if (pl1.pos < 0) pl1.pos = 0;
  else if (pl1.pos + pl1.height > windowHeight) pl1.pos = windowHeight - pl1.height;

  if (pl2.pos < 0) pl2.pos = 0;
  else if (pl2.pos + pl2.height > windowHeight) pl2.pos = windowHeight - pl2.height;
  
}
