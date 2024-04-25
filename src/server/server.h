#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_

#include <iostream>
#include <string>
#include <vector>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

#define DEF_PORT 9090
#define DEF_START_MSG "RIT LETT CNT SRVR v0.1"
#define DEF_MAX_CONN 30

struct EchoServerConfig {
  int port;
  std::size_t max_conn;
  std::string start_message;
}; 

class EchoServer {
  public:
    EchoServer() noexcept;
    EchoServer(int port, int max_conn) noexcept;

    std::string get_info() noexcept;
    void start_server();

  private:
    EchoServerConfig config_;
};

#endif // SRC_SERVER_H_

