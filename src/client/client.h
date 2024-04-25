#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include <iostream>
#include <string>

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

#include "client_exceptions.h"

#define DEF_PORT 9090
#define DEF_IP "127.0.0.1"

class SimlpeClientTCP {
  public:
    SimlpeClientTCP() noexcept;
    SimlpeClientTCP(int port, std::string ip_addr) noexcept;

    void client_start();
  private:
    sockaddr_in client_;

    void client_init(int port, std::string ip_addr) noexcept;
    int create_socket();
    int connect_to_server(int client_socket);
    int send_data_to_server(int client_socket, std::string data);
    void client_main_loop(int client_socket);

    void print_message(std::string) noexcept;
};

#endif // SRC_CLIENT_H_