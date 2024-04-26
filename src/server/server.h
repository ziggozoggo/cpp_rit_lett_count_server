#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_

#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "count_letter_frq.h"
#include "server_exceptions.h"

#define DEF_PORT 9090
#define DEF_MAX_CONN 30
#define DEF_PENDING_CONN 3

class EchoServer {
 public:
  EchoServer() noexcept;
  EchoServer(const int& port, const int& max_conn) noexcept;

  std::string get_info() noexcept;
  void start_server(std::string (*func)(const std::string&));

 private:
  int max_conn_;
  sockaddr_in address_;
  int master_socket_;
  int connections_count_;

  void address_init() noexcept;
  void set_master_socket();
  void bind_master_socket();
  int listen_master_socket();
  void main_server_loop(int* addrlen, std::string (*func)(const std::string&));
};

#endif  // SRC_SERVER_H_
