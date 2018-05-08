#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#define  BUFLEN                   1024                 /* buffer length */
int sender(int b[10],int k)
 {
 	int checksum,sum=0,i;
        	printf("\n****SENDER****\n");
     
for(i=0;i<k;i++)
      		sum+=b[i];
      		printf("SUM IS: %d",sum);
                     
    	checksum=~sum;
    	printf("\nSENDER's CHECKSUM IS:%d",checksum);
    	return checksum;
}
int main(int argc, char **argv)
{
        int n;
        int sd, port;
        char buf[BUFLEN];
        char buffer[512];
	//int parity=0;
	
       struct sockaddr_in server;
     
       port=atoi(argv[1]);

        /* create a stream socket */
        if(( sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                fprintf(stderr, "can't create a socket\n");
                exit(1);
        }

      
        server.sin_family = AF_INET;
        server.sin_port = port;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");


        /* connecting to the server */
        if(connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
                fprintf(stderr, "can't connect\n");
                exit(1);
        }

	int a[10],i,m,scheck,rcheck;
     	printf("\nENTER SIZE OF THE STRING:");
     	scanf("%d",&m);
     	printf("\nENTER THE ELEMENTS OF THE ARRAY:");
     	for(i=0;i<m;i++)
	scanf("%d",&a[i]);
	scheck=sender(a,m);
	write(sd,&scheck,sizeof(int));
	write(sd,&a,sizeof(a));
	
	write(sd,&m,sizeof(int));
	//for(i=0;i<m;i++)
		//write(sd,&a[i],sizeof(int));
	printf("Sent to Server\n");
       close(sd);
       return(0); 


}
