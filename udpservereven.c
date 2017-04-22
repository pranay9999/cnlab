#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
int main(int argc, char *argv[])
{
	int ser_sfd, nbytes, i, addr_len,len,num,doub;
	char buffer[1024],buff[50]; 
	struct sockaddr_in sa,ca;
	ser_sfd = socket(AF_INET, SOCK_DGRAM, 0); //Create UDP socket
	sa.sin_family = AF_INET;
	sa.sin_port = htons(2345);
	//sa.sin_addr.s_addr = inet_addr("172.16.4.60");
	sa.sin_addr.s_addr=htonl(INADDR_ANY);
	len=sizeof(sa); //Fill the server address structure
	bind(ser_sfd, (struct sockaddr *) &sa, len);
	addr_len = sizeof (ca); //register server address
	nbytes =recvfrom(ser_sfd, &num,1024,0,(struct sockaddr *)&ca, &addr_len);
	printf("Number from client is %d",num);
		if(num%2==0)
		{
			strcpy(buff,"Even number");
	
		}
		else
		{
			strcpy(buff,"Odd number");
		}
	sendto(ser_sfd, &buff,nbytes,0,(struct sockaddr *)&ca, addr_len);//Send the message
	return 0;
}
