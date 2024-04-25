#include "server.h"

/* Constructors */
EchoServer::EchoServer() noexcept : max_conn_(DEF_MAX_CONN), master_socket_(0) {
  address_.sin_port = htons(DEF_PORT);
  this->address_init();  
}

EchoServer::EchoServer(int port, int max_conn) noexcept : max_conn_(max_conn), master_socket_(0) {
  address_.sin_port = htons(port);
  this->address_init();
}

/* Main methods */
void EchoServer::start_server() {
	int opt = 1; 
	int master_socket , addrlen , new_socket,
		max_clients = 30 , activity, i , valread , sd;

  std::vector<int>client_socket(max_conn_);

	int max_sd; 
	// struct sockaddr_in address; 
		
	char buffer[1025]; //data buffer of 1K 
		
	//set of socket descriptors 
	fd_set readfds; 
		
	//a message 
	const char *message = "ECHO Daemon v1.0 \r\n"; 
			
	//create a master socket 
  this->set_master_socket();
	
  // if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) 
	// { 
	// 	perror("socket failed"); 
	// 	exit(EXIT_FAILURE); 
	// } 
	
	//set master socket to allow multiple connections , 
	//this is just a good habit, it will work without this 
	// if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
	// 	sizeof(opt)) < 0 ) 
	// { 
	// 	perror("setsockopt"); 
	// 	exit(EXIT_FAILURE); 
	// } 
	
	//type of socket created 
	// address.sin_family = AF_INET; 
	// address.sin_addr.s_addr = INADDR_ANY; 
	// address.sin_port = htons(config_.port); 
		
	//bind the socket to localhost port 8888 
	if (bind(master_socket_, (struct sockaddr *)&address_, sizeof(address_))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
  // printf("Listener on port %d \n", address_.sin_port); 
		
	//try to specify maximum of 3 pending connections for the master socket 
	if (listen(master_socket_, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
		
	//accept the incoming connection 
	addrlen = sizeof(address_); 
	puts("Waiting for connections ..."); 
		
	while(true) 
	{ 
		//clear the socket set 
		FD_ZERO(&readfds); 
	
		//add master socket to set 
		FD_SET(master_socket_, &readfds); 
		max_sd = master_socket_; 
			
		//add child sockets to set 
		for ( i = 0 ; i < max_clients ; i++) 
		{ 
			//socket descriptor 
			sd = client_socket[i]; 
				
			//if valid socket descriptor then add to read list 
			if(sd > 0) 
				FD_SET( sd , &readfds); 
				
			//highest file descriptor number, need it for the select function 
			if(sd > max_sd) 
				max_sd = sd; 
		} 
	
		//wait for an activity on one of the sockets , timeout is NULL , 
		//so wait indefinitely 
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL); 
	
		if ((activity < 0) && (errno!=EINTR)) 
		{ 
			printf("select error"); 
		} 
			
		//If something happened on the master socket , 
		//then its an incoming connection 
		if (FD_ISSET(master_socket_, &readfds)) 
		{ 
			if ((new_socket = accept(master_socket_, 
					(struct sockaddr *)&address_, (socklen_t*)&addrlen))<0) 
			{ 
				perror("accept"); 
				exit(EXIT_FAILURE); 
			} 
			
			//inform user of socket number - used in send and receive commands 
			printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address_.sin_addr) , ntohs 
				(address_.sin_port)); 
		
			//send new connection greeting message 
			if( send(new_socket, message, strlen(message), 0) != strlen(message) ) 
			{ 
				perror("send"); 
			} 
				
			puts("Welcome message sent successfully"); 
				
			//add new socket to array of sockets 
			for (i = 0; i < max_clients; i++) 
			{ 
				//if position is empty 
				if( client_socket[i] == 0 ) 
				{ 
					client_socket[i] = new_socket; 
					printf("Adding to list of sockets as %d\n" , i); 
						
					break; 
				} 
			} 
		} 
			
		//else its some IO operation on some other socket 
		for (i = 0; i < max_clients; i++) 
		{ 
			sd = client_socket[i]; 
				
			if (FD_ISSET( sd , &readfds)) 
			{ 
				//Check if it was for closing , and also read the 
				//incoming message 
				if ((valread = read( sd , buffer, 1024)) == 0) 
				{ 
					//Somebody disconnected , get his details and print 
					getpeername(sd , (struct sockaddr*)&address_ , (socklen_t*)&addrlen); 
					printf("Host disconnected , ip %s , port %d \n" , 
						inet_ntoa(address_.sin_addr) , ntohs(address_.sin_port)); 
						
					//Close the socket and mark as 0 in list for reuse 
					close( sd ); 
					client_socket[i] = 0; 
				} 
					
				//Echo back the message that came in 
				else
				{ 
					//set the string terminating NULL byte on the end 
					//of the data read 
					buffer[valread] = '\0'; 
					send(sd , buffer , strlen(buffer) , 0 ); 
				} 
			} 
		} 
	} 
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
  int res_set = setsockopt(master_socket_, SOL_SOCKET, SO_REUSEADDR,
                           (char *)&opt, sizeof(opt));
  if (res_set < 0) {
    //TODO throw error: "Set multiple connections to master socket failed"
    printf("Set multiple connections to master socket failed");
  }
  // std::cout << "HI" << std::endl;
}