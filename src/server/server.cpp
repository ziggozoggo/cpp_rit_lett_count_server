#include "server.h"

/* Constructors */
EchoServer::EchoServer() noexcept : max_conn_(DEF_MAX_CONN), master_socket_(0) {
  hello_message_ = DEF_START_MSG;
  address_.sin_port = htons(DEF_PORT);
  this->address_init();  
}

EchoServer::EchoServer(int port, int max_conn) noexcept : max_conn_(max_conn), master_socket_(0) {
  hello_message_ = DEF_START_MSG;
  address_.sin_port = htons(port);
  this->address_init();
}

/* Main methods */
void EchoServer::start_server(std::string (*func)()) {
  //TODO...
  this->set_master_socket();
  this->bind_master_socket();
  int addrlen = this->listen_master_socket();
  this->main_server_loop(&addrlen, func); 
}

/* Utilities methods */
std::string EchoServer::get_info() noexcept {
  char buffer [BUFSIZ];
  sprintf (buffer, "PORT: %d, MAX_CONN: %d\n", 
           address_.sin_port, max_conn_);
  return buffer;
}

/* Private utils */
void EchoServer::address_init() noexcept {
  address_.sin_family = AF_INET;
  address_.sin_addr.s_addr = INADDR_ANY;
}

void EchoServer::set_master_socket() {
  master_socket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (master_socket_ == 0) {
    //TODO throw error: "Set master socket failed"
    printf("Set master socket failed");
  }
  
  // Allow multiple connections
  int opt = 1;
  int setsock_code = setsockopt(master_socket_, SOL_SOCKET, SO_REUSEADDR,
                           (char *)&opt, sizeof(opt));
  if (setsock_code < 0) {
    //TODO throw error: "Set multiple connections to master socket failed"
    printf("Set multiple connections to master socket failed");
  }
  // std::cout << "HI" << std::endl;
}

void EchoServer::bind_master_socket() {
  int bind_code = bind(master_socket_, (struct sockaddr *)&address_, sizeof(address_));
  if (bind_code < 0) {
    //TODO throw error: "Bind master socket to IP:port failed"
    printf("Bind master socket to IP:port failed");
  }
}

int EchoServer::listen_master_socket() {
  int listen_code = listen(master_socket_, DEF_PENDING_CONN);
  if (listen_code < 0) {
    //TODO throw error: "Set listen master socket failed"
    printf("Set listen master socket failed");
  }
  puts("Waiting for connections ...");
  return sizeof(address_); 
}

void EchoServer::main_server_loop(int *addrlen, std::string (*func)()) {
  int max_sd = 0;
  int sd = 0;
  int activity = 0;
  int new_socket = 0;

  char buffer[1025]; //data buffer of 1K 
  int valread = 0;

  fd_set readfds;
  std::vector<int> client_socket(max_conn_);
  
  while(true) {
    // Clear socket set
    FD_ZERO(&readfds);
    // Add master socket to set
    FD_SET(master_socket_, &readfds);
    max_sd = master_socket_;

    // Add child socket
    for (int i = 0; i < max_conn_; i++) {
      sd = client_socket[i];
      if (sd > 0) {
        FD_SET(sd, &readfds);
      }
      if (sd > max_sd) {
        max_sd = sd;
      }
    }

    // Set activity; timeout is NULL == inf
    activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
    if ((activity < 0) && (errno != EINTR)) {
      //TODO throw error: "Activity select error"
      printf("Activity select error");
    }

    // Incoming connection
    if (FD_ISSET(master_socket_, &readfds)) {
      new_socket = accept(master_socket_, (struct sockaddr *)&address_, (socklen_t*)addrlen);
      if (new_socket < 0) {
        //TODO throw error: "Accept connection failed"
        printf("Accept connection failed");
      }
      //inform user of socket number - used in send and receive commands 
			printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address_.sin_addr) , ntohs 
				    (address_.sin_port));
      
      const char* message = hello_message_.c_str(); 
      int send_code = send(new_socket, message, strlen(message), 0);
      if (send_code != strlen(message)) {
        //TODO throw error: "Send hello message to client failed"
        printf("Send hello message to client failed");
      } else {
        puts("Welcome message sent successfully");
      } 

      // Add new socket to array
      for (int i = 0; i < max_conn_; i++) {
        if (!client_socket[i]) {
          client_socket[i] = new_socket;
          printf("Adding to list of sockets as %d\n" , i);
          break;
        }
      }
    }

    // IO on other socket
    for (int i = 0; i < max_conn_; i++) {
      sd = client_socket[i];
      if (FD_ISSET(sd, &readfds)) {
        
        valread = read(sd, buffer, 1024);
        if (!valread) {
          // Closing connection
          getpeername(sd , (struct sockaddr*)&address_ , (socklen_t*)addrlen);
          printf("Host disconnected , ip %s , port %d \n" , 
						inet_ntoa(address_.sin_addr) , ntohs(address_.sin_port));
          close(sd);
          client_socket[i] = 0; 
        } else {
          //TODO Do Work
          std::string tmp = func();

          send(sd, tmp.c_str(), strlen(tmp.c_str()), 0);

          // buffer[valread] = '\0';
          // send(sd, buffer, strlen(buffer), 0);
        }
      }
    }
  }
}

/* EXPERIMENTS */
std::string echo_func() {
  return "Hello from echo func!\n";
}