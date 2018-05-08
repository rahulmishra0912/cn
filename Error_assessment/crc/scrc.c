#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
 #include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include <dirent.h>
#include <string.h>


#define BUFLEN                 1024        /* buffer length */

int main(int argc, char **argv)
{
	char *curr_dir = NULL;
    	DIR *dp = NULL;
   	struct dirent *dptr = NULL;
    	unsigned int count = 0;
        int n1,n2,n,i=0,digit,sum=0;
	int yes=1,flag=0;
        int sd, new_sd, client_len, port;
        struct sockaddr_in server, client;
        char  buf[BUFLEN],buf1[BUFLEN],buf2[BUFLEN],res[BUFLEN];

 int j,keylen,msglen;
 char input[100], key[30],temp[30],quot[100],rem[30],key1[30];

	
	//recieve port number through terminal
         port = atoi(argv[1]);
     
        /* create a stream socket */
        if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                fprintf(stderr,"can't create a socket\n");
                exit(1);
        }

        /* Fill the structure fileds with values */

        server.sin_family = AF_INET;
        server.sin_port = port;
        server.sin_addr.s_addr =inet_addr("127.0.0.1");
	
       // Reuse the port and address
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
    		perror("setsockopt");
   		 exit(1);
	}

        /* bind an address to the socket */
        if(bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
                fprintf(stderr, "can't bind name to socket\n");
                exit(1);
        }

        /* queue up to 5 connect requests */
        listen(sd,5);

        while(1)
        {
		
                client_len = sizeof(client);
		
		//accept the clients
                if((new_sd = accept(sd, (struct sockaddr *) &client, &client_len)) == -1)
                {
                        fprintf(stderr, "can't accept client \n");
                        exit(1);
                }
       
		
		while(1){


		//buf=crc buf1=input  buf2=key
      		  n= read(new_sd, buf, sizeof(buf));

		  n1 = read(new_sd, buf1, sizeof(buf));

	         n2 = read(new_sd, buf2, sizeof(buf));
	
	keylen=strlen(buf2);
 	msglen=strlen(buf1);
 	strcpy(key1,buf2);

	 for(i=0;i<keylen-1;i++)
	 {
	 buf1[msglen+i]=buf[i];
	 }
//printf("%s\n",buf1);
//printf("%s\n",key);
	for(i=0;i<keylen;i++)
 	  temp[i]=buf1[i];

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
 	rem[keylen-1]=buf1[i+keylen];
	 strcpy(temp,rem);
 //printf("tt=%s",temp);
 	}
 	strcpy(rem,temp);
	rem[keylen-1]='\0';
 	//printf("%s\n",rem);


		//printf("%s\n",buf);
		printf("CRC=%s\n",rem);
		for(i=0;i<strlen(rem);i++)
		{
			if(rem[i]=='1')
			{
				flag=1;
			}
		}

	if(flag==1)
	{
		strcpy(res,"Error");
	}
	else
	{
		strcpy(res,"No error");
	}

	 write(new_sd, res, BUFLEN);
      }
 		
		i++;
               //close the socket
      		 close(new_sd);
       		 close(sd);
       		 return(0);
	}
}
