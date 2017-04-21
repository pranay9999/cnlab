#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
int encrypt(int e,int n,int m)
{
	int i;
	int c = 1 ;
	for(i=0;i<e;i++)
		c = c*m%n;
	c=c%n;
	return c;	
}
int main(){
	int sfd,cfd,err,s,e,n,num,m;
	char buff[100];
	struct sockaddr_in servaddr,ca;
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
		printf("Socket Creation error\n");
	else
		printf("created\n");
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(3272);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	err = bind(sfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if(err<0)
		printf("Bind error\n");
	else
		printf("binded\n");
	err = listen(sfd,5);
	if(err<0)
		printf("Listen error\n");
	else
		printf("Listening...\n");
	fflush(stdout);
	cfd = accept(sfd,(struct sockaddr*)0,0);
	if(cfd<0)
		printf("Accept error");
	else
		printf("Accepted\n");
	fflush(stdout);
	s = recv(cfd,&e,sizeof(num),0);
	printf("E received is %d\n",e);
	s = recv(cfd,&n,sizeof(num),0);
	printf("N received is %d\n",n);
	fflush(stdout);
	printf("Enter number:");
	scanf("%d",&m);
	num = encrypt(e,n,m);
	printf("Encrypted is %d\n",num);
	send(cfd,&num,sizeof(num),0);
	close(sfd);		
	close(cfd);
}
