#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
int main(int argc, char *argv[])
{
	int cli_sfd, nbytes,num,doub;
	socklen_t addr_size;
	char buffer[1024],buff[50];
	struct sockaddr_in sa, ca;
	cli_sfd = socket(AF_INET, SOCK_DGRAM, 0);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(2345);
	sa.sin_addr.s_addr=htonl(INADDR_ANY);
	memset(sa.sin_zero, '\0', sizeof sa.sin_zero); //create a UDP socket
	ca.sin_family = AF_INET;//Fill the server address structure
	ca.sin_port = 0;
	ca.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(ca.sin_zero, '\0', sizeof ca.sin_zero);
	bind(cli_sfd,(struct sockaddr*)&ca,sizeof(ca)); //Fill the client address structure
	//UDP will assign a free port number
	//Machine’s IP address on which we run client registration with UDP
	addr_size = sizeof(sa);//Client server interaction using UDP protocol
	printf("CLIENT>Enter number:"); 
	scanf("%d",&num);
	sendto(cli_sfd,&num,sizeof(num), 0, (struct sockaddr *) &sa, addr_size); 
	nbytes=recvfrom(cli_sfd, &buff,1024,0, (struct sockaddr *) &sa, &addr_size);
	printf("SERVER>Given number %d is %s\n",num,buff);

return 0;
}
