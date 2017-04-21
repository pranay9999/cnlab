#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
int main()
{
	int sfd,newsfd,s,len,n,i,num,fact=1;
	struct sockaddr_in servaddr, ca,client;
	sfd=socket(AF_INET, SOCK_STREAM,0);
	if(sfd<0)
	{
		perror("socket() error:");
		exit(-1);
	}
	//creates a socket
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(2345);
	//convert port address given from command line into network byte order
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	//extracts the machine IP address
	//servaddr.sin_addr.s_addr=inet_addr("172.16.0.100");
	s=bind(sfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	//bind the server with the specified address
	if(s<0)
	{
		perror("bind() error:");
		exit(-1);
	}
	s=listen(sfd,5);
	//tells its readiness to TCP
	if(s<0)
	{
		perror("listen() error:");
		exit(-1);
	}
	printf("Server is ready and waiting for client requests...........\n");
	newsfd=accept(sfd,(struct sockaddr*)&ca,&len); //server blocks fr connection request
	if(newsfd<0)
	{
		perror("accept() error:");
		exit(-1);
	}
	printf("Connected to client........");
	n=recv(newsfd,&num,10,0);
	//reads data into ‘buff’ from the scoket
	printf("\nNumber from client: %d",num);
	//displays the data on to the terminal
	for(i=1;i<=num;i++)
		fact=fact*i;
	//converts the data in the ‘buff’ to upper case
	send(newsfd,&fact, n,0);
	//writes the data from ‘buff’ over to socket.
	close(sfd); close(newsfd);
	//close the connection
	return 0;
}
