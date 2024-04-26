#include <getopt.h>
#include <vector>
#include "client.h"

// g++ main.cpp client.cpp -o test

int main(int argc, char* argv[]) {
  int get_opt_index = 0;
  std::string ip_addr = "";
  std::string port_str = "";
  int port = DEF_PORT;
  
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
        //fprintf(stderr, "%s: invalid option -- '%c'\n", argv[0], optopt);
        fprintf(stderr, "use: \n");
        fprintf(stderr, "\t -h <server IP adress>; default %s\n", DEF_IP);
        fprintf(stderr, "\t -p <server port>; default %d\n", DEF_PORT);
        return 1;
    }
  }
  
  if (ip_addr == "") {
    ip_addr = DEF_IP;
  }

  if (port_str != "") {
    port = atoi(port_str.c_str());
  }


  SimlpeClientTCP client(port, ip_addr);
  client.client_start();

  return 0;
}