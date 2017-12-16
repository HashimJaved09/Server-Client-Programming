#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>                //allows you to use socket functions
#include <netinet/in.h> //includes (sockaddr_in) used to store IP addresses

#define PORT 7769                  //port address to be used in the program

int main(int argc, char const *argv[]) //passing arguments to the main function
{
    int sock, new_socket, valread;
    struct sockaddr_in address; //sockaddr_in type variable to store address for (AF_INET) Family which stores port in 
                                                                               //sin_port and IPv4 address in sin_addr
    int opt = 1;
    int addrlen = sizeof(address);                                 //storing size of address variable
    char buf[1024] = {0}; //making memory buffer to store recieved data and initializing it with zero
      
              //creating socket of AF_INET Family, using SOCK_STREAM socket scheme and using default protocol
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) //if socket() returns 0, it means socket isn't created
    {
        perror("socket failed");
    }
    
    address.sin_family = AF_INET;                             //telling address about family type AF_INET (host address)
    address.sin_addr.s_addr = INADDR_ANY; //value "INADDR_ANY" means that address will bind to any/all IP addresses that
                                                                                         //local computer currently has
    address.sin_port = htons(PORT);                 //telling server about port address (htons = host to network short)
      
                                                                                           //attaching socket to the port
    if (bind(sock, (struct sockaddr *)&address, sizeof(address))<0) //binds a name to a socket which is unnamed initially
    {                                                          //returns 0 for successful completion, otherwise -1(error)
        perror("bind failed");
    }
    
    if (listen(sock, 3) < 0) //listen for socket connections and limit the queue of incoming connections(backlog)
    {                                       //listen() return 0 if successfull; otherwise, -1 and indicates error
        perror("listen");
    }
    
    if ((new_socket = accept(sock, (struct sockaddr*)&address, (socklen_t*)&addrlen))<0) //accept connections on socket
    {                                                             //extracts the first connection from queue of pending 
        perror("accept");                                      //connections and creates a new socket with same address
    }                                                                                  //and Family as specified socket
    
	while(1)
	{		
    	valread = read(new_socket, buf, 1024); //read() reads given no. of bytes from socket into the buffer
    	
    	printf("\nReceived from Client: %s\n",buf);       //printing read data from buffer(recieved from client)
    	
    	printf("\n\nType a MESSAGE to send to Client: ");
    	fgets(buf, 1024, stdin);
    	
    	if(buf[0] == '0') break;
    	
    	send(new_socket, buf, 1024 , 0);                    //send() is used to send a message on the socket
    }
    return 0;
}
