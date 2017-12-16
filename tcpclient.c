#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>                //allows you to use socket functions
#include <netinet/in.h> //includes (sockaddr_in) used to store IP addresses

#define PORT 7769                  //port address to be used in the program
  
int main(int argc, char const *argv[]) //passing arguments to the main function
{
    struct sockaddr_in address; //sockaddr_in type variable to store address for (AF_INET) Family which stores port in 
                                                                               //sin_port and IPv4 address in sin_addr 
    int sock = 0, valread;
    struct sockaddr_in serv_addr;                     //variable serv_addr to store address of server 
    char buf[1024] = {0}; //making memory buffer to store recieved data and initializing it with zero
    
	              //socket function is used to create socket with the specified domain(AF_INET) and type(SOCK_STREAM)
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)                  //if it returns -ve value which indicates error
    {                                                //if successful completion, socket() returns non-negative number
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));       //clear our address (used to set memory block with given value)
  
    serv_addr.sin_family = AF_INET;                 //telling server address about family type AF_INET (host address)
    serv_addr.sin_port = htons(PORT);             //telling server about port address (htons = host to network short)
      
                                                             //convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  //inet_pton() converts given characters into a network
    {                                                           //address structure in the AF_INET address_family, then 
        printf("\nInvalid address/ Address not supported \n"); //copies network_address structure to serv_addr.sin_addr 
        return -1;                                             
    }
  
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) //connects socket(sock) to the address specified
    {                                                                    //and sizeof(serv_addr) specifies size of address
        printf("\nConnection Failed \n");
        return -1;
    }
    
    while(1)
    {
    	printf("\n\nType a MESSAGE to send to Server: ");
    	fgets(buf, 1024, stdin);
    	
    	if(buf[0] == '0') break;
    	
    	send(sock , buf , 1024 , 0);                      //send() is used to send a message on the socket 
    
    	valread = read(sock , buf, 1024);    //read() reads given no. of bytes from socket into the buffer
    	
    	printf("\nReceived from Server: %s\n",buf); //printing read data from buffer(recieved from server)
    }
    return 0;
}
