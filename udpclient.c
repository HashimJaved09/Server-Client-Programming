#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
  	int client, portNum, n;
  	char buf[1024] = {0};
  	struct sockaddr_in server;
  	socklen_t addr_size;
	
  	client = socket(PF_INET, SOCK_DGRAM, 0); //creating UDP socket

  	server.sin_family = AF_INET; //setting address struct
  	server.sin_port = htons(6969);
  	server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  	memset(server.sin_zero, '\0', sizeof server.sin_zero);  

  	addr_size = sizeof server; //initialize size variable to be used later on
	
	while(1)
  	{
    		printf("\nType a Message to send to server: ");  
    		fgets(buf, 1024, stdin); //getting msg from user to send to server 
    	
    		n = strlen(buf) + 1;
    		if(buf[0] == '0') break;
    	
    		sendto(client, buf, n, 0, (struct sockaddr*)&server, addr_size); //sending message to server
			
    		n = recvfrom(client, buf, 1024, 0, NULL, NULL); //receiving message from server

    		printf("\n\nReceived from server: %s\n",buf); //printing received msg from server  
  	}
  	return 0;
}
