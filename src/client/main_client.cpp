#include <getopt.h>
#include <vector>
#include "client.h"

std::string get_launch_parameters(int argc, char* argv[], int *port, bool *err);

int main(int argc, char* argv[]) {
  int port = 0;
  bool is_err = false;
  std::string ip_addr = get_launch_parameters(argc, argv, &port, &is_err);

  if (is_err) {
    return 1;
  }
  
  SimlpeClientTCP client(port, ip_addr);
  client.client_start();

  return 0;
}

std::string get_launch_parameters(int argc, char* argv[], int *port, bool *err) {
  int get_opt_index = 0;
  std::string ip_addr = "";
  std::string port_str = "";
  *port = DEF_PORT;

  while ((get_opt_index = getopt(argc, argv, "h:p:")) != -1) {
    switch (get_opt_index) {
      case 'h':
        // server host ip address
        ip_addr = optarg;
        break;
      case 'p':
        port_str = optarg;
        break;
      default:
        *err = true;
        fprintf(stderr, "use: \n");
        fprintf(stderr, "\t -h <server IP adress>; default %s\n", DEF_IP);
        fprintf(stderr, "\t -p <server port>; default %d\n", DEF_PORT);
        break;
    }
  }

  if (ip_addr == "") ip_addr = DEF_IP;
  if (port_str != "") *port = atoi(port_str.c_str());

  return ip_addr;
}