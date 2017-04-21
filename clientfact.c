#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#define MAX 100
int main()
{
	int sfd,newsfd,s,len,n,num;
	struct sockaddr_in servaddr,sa;
	sfd=socket(AF_INET, SOCK_STREAM,0);
	//creates an unnamed socket
	if(sfd<0)
	{
		perror("socket() error:");
		exit(-1);
	}
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(2345);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	s=connect(sfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	//requests for connection with the server (172.16.0.100)
	if(s<0)
	{
		perror("connect() error:");
		exit(-1);
	}
	write(1,"Enter num: ",10);
	n=read(0,&num,10);
	//read a message from keyboard (i.e. From user)
	send(sfd,&num,n,0);
	//writes the message over to the socket from the buffer
	n=recv(sfd,&fact,10,0);
	//reads a message from the socket into the buffer
	printf("Factorial of %d is %d",num,fact);
	//display the message on the terminal
	close(sfd);
	return 0;
}
