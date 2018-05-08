
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define  BUFLEN                   1024                 /* buffer length */

int main(int argc, char **argv)
{
        int n;
        int sd, port;
        char buf[BUFLEN];
        char buffer[512];
	int parity=0;
	
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

	printf("enter a number\n");
	scanf("%d",&n);
	//printf("%d\n",n);
	write(sd,&n,sizeof(int));
	while(n){
		parity=!parity;
		n=n&(n-1);
	}
	
	write(sd,&parity,sizeof(int));
	printf("Sent to Server\n");
       close(sd);
       return(0); 
}

