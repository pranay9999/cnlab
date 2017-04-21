#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
void main()
{
	int sfd,c,p,q,n,phi;
	//char buff[100];
	struct sockaddr_in servaddr,clientaddr;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd>0)
	{
		printf("created \n");
	}
	servaddr.sin_port=htons(3272);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	c=connect(sfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(c==0)
	printf("connected\n");
	else printf("Error\n");
	printf("Enter message:");
	scanf("%d",&n);
	send(sfd,&n,sizeof(n),0);
	recv(sfd,&n,sizeof(n),0);
	printf("Server Message:%d",n);
	
}
