#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int n,e,d,P,FLAG,M,num,phi;
void check(){
	int i;
	printf("Called \n");
	for(i=3;e%i==0&&phi%i==0;i+2)
	{
		FLAG=1;
	}FLAG=0;
}
void decrypt()
{
	int i;
	M=1;
	for(i=0;i<d;i++)
	M=M*num%n;
	M=M%n;
	printf("Decrypted keyword: %d",M);
}
void main()
{
	int sfd,c,p,q,s;
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
	printf("Enter p and q:");
	scanf("%d%d",&p,&q);
	n=p*q;
	phi=(p-1)*(q-1);
	printf("%d \n",phi);
	fflush(stdout);
	do
	{
		printf("Enter e:");
		scanf("%d",&e);
		check();
		
	}while(FLAG==1);
	d=1;
	do{
		s=(d*e)%phi;
		d++;
	}while(s!=1);
	d=d-1;
	printf("Public key:{%d,%d}\n",e,n);
	printf("private key:{%d,%d}\n",d,n);
	send(sfd,&e,sizeof(e),0);
	send(sfd,&n,sizeof(n),0);
	recv(sfd,&num,sizeof(num),0);
	printf("%d \n",num);
	decrypt();
}
