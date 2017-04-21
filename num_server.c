#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
int main(){
	int sfd,cfd,err,n,num;
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
	n = recv(cfd,&num,sizeof(num),0);
	printf("number received is %d\n",num);
	fflush(stdout);
	num*=2;
	send(cfd,&num,sizeof(num),0);
	close(sfd);		
	close(cfd);

}
