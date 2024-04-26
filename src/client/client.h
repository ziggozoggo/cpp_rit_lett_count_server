#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "client_exceptions.h"

#define DEF_PORT 9090
#define DEF_IP "127.0.0.1"
#define DEF_RECONNECT_DELAY 5

class SimlpeClientTCP {
 public:
  SimlpeClientTCP() noexcept;
  SimlpeClientTCP(const int& port, const std::string& ip_addr) noexcept;

  void client_start();

 private:
  sockaddr_in client_;
  bool is_reconnecting_;
  int reconnect_delay_;

  void client_init(int port, std::string ip_addr) noexcept;
  int create_socket();
  int connect_to_server(int client_socket);
  int send_data_to_server(int client_socket, std::string data);
  void client_main_loop(int client_socket);
  void reconnect_to_server(int sleep_time);

  void print_message(std::string) noexcept;
  void print_welcome_message() noexcept;
};

#endif  // SRC_CLIENT_H_