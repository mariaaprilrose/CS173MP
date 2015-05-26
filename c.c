#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>


int main(int argc, char *argv[])
{
   int socket_desc, portno, len, read_size;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   
   char message[256], server_message[1024];
   
   if (argc <3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }
   portno = atoi(argv[2]);
   
   /* Create a socket point */
   socket_desc = socket(AF_INET, SOCK_STREAM, 0);
   
   if (socket_desc < 0)
   {
      perror("ERROR opening socket");
      exit(1);
   }
   server = gethostbyname(argv[1]);
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   /* Now connect to the server */
   if (connect(socket_desc, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
   {
      perror("ERROR connecting");
      exit(1);
   }

   /* Now read server response */
   //FIRST MESSAGE RECIEVED
   bzero(server_message,256);
   len = read(socket_desc, server_message, 255);
   printf("%s\n", server_message);



   printf("Please enter the message: ");
   scanf("%s", message);
    /* Send message to the server*/

   //2ND MESSAGE SEND
   write(socket_desc, message, strlen(message));
   read(socket_desc, server_message, 255);
   printf("server: message %s\n", server_message );


   while((read_size = recv(socket_desc , server_message , 2000 , 0)) > 0){
   	printf("server's message %s\n", server_message );

   	printf("Choose What to do \n");
    printf("[1] View Files [2] Send Files [3] Download, [4] Quit \n");
    scanf("%s", message);
    printf("message: %s\n", message );

	   if (strcmp("1", message)== 0){
	   		write(socket_desc , message , strlen(message));
	   		printf("one\n");
	   }
	   else if(strcmp(message, "4")==0){
	   		write(socket_desc , message , strlen(message));
	   		printf("4\n");
	   }
	   else{
	   		
	   		printf("elsedfuck\n");
	   		break;
	   	}
	}

   return 0;
}

   
   /* Now ask for a message from the user, this message
   * will be read by server
   */
   /*
   printf("Please enter the message: ");
   bzero(message,256);
   fgets(message,255,stdin);*/
   
   /* Send message to the server*/
/*  	len = write(socket_desc, message, strlen(message));
   
   if (len < 0)
   {
      perror("ERROR writing to socket");
      exit(1);
   }
*/
   /* Now read server response */
/*    bzero(message,256);
   	len = read(socket_desc, message, 255);
   
   if (len < 0){
      perror("ERROR reading from socket");
      exit(1);
   } 

   printf("%s\n", message);*/


/*  while( (read_size = recv(socket_desc , message , 2000 , 0)) > 0 )
    {

        //Send the message back to server
        printf("Please enter the message: ");
        bzero(message,256);
        fgets(message,255,stdin);

        len= write(socket_desc , message , strlen(message));

        if (len < 0){
      		perror("ERROR writing to socket");
      		exit(1);
   		}

   		len = read(socket_desc, message, 255);
   		if (len < 0){
      		perror("ERROR reading from socket");
      		exit(1);
   		printf("%s\n", message);
   		}

    }
   if (len < 0)
   {
      perror("ERROR reading from socket");
      exit(1);
   }*/
