#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int sock, n;
  	char buf[1024] = {0};
  	struct sockaddr_in server;
  	struct sockaddr_storage serverStorage;
  	socklen_t addr_size;

  	sock = socket(PF_INET, SOCK_DGRAM, 0); //creating UDP socket

  	server.sin_family = AF_INET; //setting address struct
  	server.sin_port = htons(6969);
  	server.sin_addr.s_addr = inet_addr("127.0.0.1");
  	
  	memset(server.sin_zero, '\0', sizeof server.sin_zero);  

  	n = bind(sock, (struct sockaddr *) &server, sizeof(server)); //binding socket with address struct
	if(n > 0) printf("Server has opened a connection and is listening on port 6969");
	
  	addr_size = sizeof serverStorage; //initialize size variable to be used later on

  	while(1)
  	{
  	  	//try to receive any incoming UDP datagram
    		n = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&serverStorage, &addr_size);
		
		printf("\nReceived from Client: %s", buf); //printing client msg
		
		printf("\n\nType a MESSAGE to send to Client: ");
    		fgets(buf, 1024, stdin);
    	
    		if(buf[0] == '0') break;

    		n = sendto(sock, buf, n, 0, (struct sockaddr *)&serverStorage, addr_size); //sending msg to client
  	}
  	return 0;
}
