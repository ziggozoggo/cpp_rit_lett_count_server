#include "client.h"

// g++ main.cpp client.cpp -o test

int main() {
  SimlpeClientTCP client;
  client.client_start();

  return 0;
}