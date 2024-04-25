#include "server.h"

// g++ main.cpp server.cpp -o test

int main() {
  EchoServer a;
  a.start_server(count_letter_frequency);
  return 0;
}