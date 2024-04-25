#include "client.h"

/* Constructors */
SimlpeClientTCP::SimlpeClientTCP() noexcept {
  this->client_init(DEF_PORT, DEF_IP);
}

SimlpeClientTCP::SimlpeClientTCP(int port, std::string ip_addr) noexcept {
  this->client_init(port, ip_addr);
}

/* Main methods */
void SimlpeClientTCP::client_start() {
  int client_socket = this->create_socket();
  this->connect_to_server(client_socket);
  this->client_main_loop(client_socket);
  close(client_socket);
}

/* Private method */
void SimlpeClientTCP::client_init(int port, std::string ip_addr) noexcept {
  client_.sin_family = AF_INET;
  client_.sin_port = htons(port);
  inet_pton(AF_INET, ip_addr.c_str(), &client_.sin_addr);
}

int SimlpeClientTCP::create_socket() {
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    //TODO Throw exception "Create socket error"
    std::cout << "Create socket error" << std::endl;
  }
  return client_socket;
}

int SimlpeClientTCP::connect_to_server(int client_socket) {
  int connect_res = connect(client_socket, (sockaddr *)&client_, sizeof(client_));
  if (connect_res == -1) {
    //TODO Throw exception "Connect to server failed"
    std::cout << "Connect to server failed" << std::endl;
  }
  return 0;
}

void SimlpeClientTCP::client_main_loop(int client_socket) {
  char buf[BUFSIZ] = {0};
  std::string user_input;

  while(true) {
    std::cout << "> ";
    getline(std::cin, user_input);

    // Send data to server
    this->send_data_to_server(client_socket, user_input);
    int bytes_recieved = recv(client_socket, buf, BUFSIZ, 0);
    this->print_message(std::string(buf, bytes_recieved)); 
  }
}

int  SimlpeClientTCP::send_data_to_server(int client_socket, std::string data) {
  int send_res = send(client_socket, data.c_str(), data.size() + 1, 0);
  if (send_res == -1) {
    //TODO Throw exception "Could not send data to server"
    std::cout << "Could not send data to server" << std::endl;
  }
  return 0;
}

void SimlpeClientTCP::print_message(std::string str) noexcept {
  std::cout << "SERVER> " << str << std::endl;
}