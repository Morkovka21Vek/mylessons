#include "Socket.h"
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char const *argv[]) {
   using namespace std;
   try {
       //Connection conn("34.224.200.202",80);
       Connection conn("192.168.4.1", 80);
       //conn.tx("GET /get HTTP/1.1\r\nHost: httpbin.org\r\nUser-Agent: curl/8.5.0\r\nAccept: */*\r\n\r\n");
       //conn.tx("GET /api/get_buttons_status HTTP/1.1\r\nHost: 192.168.4.1\r\nUser-Agent: curl/8.5.0\r\nAccept: */*\r\n\r\n");
       //conn.tx("GET /api/get_buttons_status HTTP/1.1\r\nHost: 192.168.4.1\r\n\r\n");
       conn.tx("GET /api/get_buttons_count HTTP/1.1\r\nHost: 192.168.4.1\r\nUser-Agent: curl/8.5.0\r\nAccept: */*\r\n\r\n");
       cout << "Hello message sent" << endl;
       string s = conn.rx();
       //cout << s << endl;
       conn.tx("GET /api/get_buttons_count HTTP/1.1\r\nHost: 192.168.4.1\r\nUser-Agent: curl/8.5.0\r\nAccept: */*\r\n\r\n");
       cout << "Hello message sent" << endl;
       s = conn.rx();
       //cout << s << endl;

       std::string parsed;

       std::string body;
       std::cout << "\033[0;42m";
       //body = s.substr(s.find("\r\n\r\n"), s.length());
       body = s;
       std::cout << body << "\033[0m" << std::endl;

       std::stringstream input_stringstream(static_cast<std::string>(body));
       if (getline(input_stringstream, parsed, ';')) {
         std::cout << parsed << std::endl;
       }
       if (getline(input_stringstream, parsed, ';')) {
         std::cout << parsed << std::endl;
       }

   } catch (exception &e) {
       cerr << e.what() << endl;
       return EXIT_FAILURE;
   }
    return 0;
}
