
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


#define  BUFLEN                   1024                 /* buffer length */

int main(int argc, char **argv)
{
        int n,i=0;
        int sd, port;
        char buf[BUFLEN];
	int j,keylen,msglen;
	 char input[100], key[30],temp[30],quot[100],rem[30],key1[30],msg[30],buf2[100];


        
       struct sockaddr_in server;

       //recieve port number through terminal
       port=atoi(argv[1]);

        /* create a stream socket */
        if(( sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                fprintf(stderr, "can't create a socket\n");
                exit(1);
        }

       
        /* Fill the structure fileds with values */
        server.sin_family = AF_INET;
        server.sin_port = port;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");


        /* connecting to the server */
        if(connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
                fprintf(stderr, "can't connect\n");
                exit(1);
        }
	printf("Files in current directory\n");
	while(1){
     	//read the files sent by server
	//printf("Enter message to server\n");
	//gets(buf);
	
	printf("Enter Data: ");
 	gets(input);

 	printf("Enter Key: ");
 	gets(key);

	strcpy(msg,input);
	keylen=strlen(key);
 	msglen=strlen(input);
 	strcpy(key1,key);

	 for(i=0;i<keylen-1;i++)
	 {
	 input[msglen+i]='0';
	 }

	 for(i=0;i<keylen;i++)
 	temp[i]=input[i];

 	for(i=0;i<msglen;i++)
 	{
 	quot[i]=temp[0];
	
	if(quot[i]=='0')
 	for(j=0;j<keylen;j++)
 	   key[j]='0';
 	else
 	for(j=0;j<keylen;j++)
	  key[j]=key1[j];


 	for(j=keylen-1;j>0;j--)
 	{
 		if(temp[j]==key[j])
 		  rem[j-1]='0';
 		else
		  rem[j-1]='1';
 	}
 	rem[keylen-1]=input[i+keylen];
	 strcpy(temp,rem);
	
 //printf("tt=%s",temp);
 	}
 	strcpy(rem,temp);
	rem[keylen-1]='\0';
printf("CRC=%s\n",rem);
 	 write(sd, rem, BUFLEN); 
        write(sd,msg,BUFLEN);
        write(sd,key,BUFLEN);

  read(sd, buf2, sizeof(buf));
      
   printf("%s\n",buf2);
	}

       close(sd);
       return(0); 
}

