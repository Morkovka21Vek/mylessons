#include "Socket.h"
#include <iostream>

int main(int argc, char const *argv[]) {
   using namespace std;
   try {
       Connection conn("34.224.200.202",80);
       //Connection conn("192.168.4.1",80);
       //conn.tx("Hello from client");
       for(int i=0; i < 100; ++i){
         conn.tx("GET /get HTTP/1.1\r\nHost: httpbin.org\r\nUser-Agent: curl/8.5.0\r\nAccept: */*\r\n\r\n");
         //conn.tx("GET / HTTP/1.1\r\nHost: httpbin.org\r\nUser-Agent: curl/8.5.0\r\nAccept: */*\r\n\r\n");
         cout << "-----------------------------------------" << endl;
         string s = conn.rx();
         cout << s << endl;
       }
   } catch (exception &e) {
       cerr << e.what() << endl;
       return EXIT_FAILURE;
   }
    return 0;
}
