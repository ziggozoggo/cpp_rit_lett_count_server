#include "server.h"

// g++ main.cpp server.cpp -o test

int main() {
  EchoServer a;
  //std::cout << a.get_info() << std::endl;
  a.start_server(echo_func);
  return 0;
}