/* Client code */
// TCP/IP
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#define MAX 1000
#define PORT_NUMBER     5001
#define SERVER_ADDRESS  "127.0.0.1"
#define FILENAME        "new1.txt"

int main(int argc, char **argv)
{
        int client_socket;
        ssize_t len;
        struct sockaddr_in remote_addr;
        char buffer[BUFSIZ];
        int file_size;
        FILE *received_file;
        int remain_data = 0;

        /* Zeroing remote_addr struct */
        memset(&remote_addr, 0, sizeof(remote_addr));

        /* Construct remote_addr struct */
        remote_addr.sin_family = AF_INET;
        inet_pton(AF_INET, SERVER_ADDRESS, &(remote_addr.sin_addr));
        remote_addr.sin_port = htons(PORT_NUMBER);

        /* Create client socket */
        client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1)
        {
                fprintf(stderr, "Error creating socket --> %s\n", strerror(errno));

                exit(EXIT_FAILURE);
        }
        else
        {
 				printf("Socket created successfully\n");       
        }

        /* Connect to the server */
        if (connect(client_socket, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
        {
                fprintf(stderr, "Error on connect --> %s\n", strerror(errno));

                exit(EXIT_FAILURE);
        }
        else
        {
        		printf("Connected Successfully\n");
        }
        
        char *chat,buff[MAX];
        int n;
        if (n=recv(client_socket, buff,MAX, 0)<0)
        {
			       fprintf(stderr, "Error receiving msg --> %s\n", strerror(errno));
        }
        else
        {
        buff[n] = '\0';
	 	printf("%s",buff);
        }
        
	 	
	 	
   /*     printf("Send message: ");
        scanf("%s",chat);
         send(client_socket, chat,BUFSIZ, 0);
      */   

        /* Receiving file size */
        recv(client_socket, buffer, BUFSIZ, 0);
        file_size = atoi(buffer);
        //fprintf(stdout, "\nFile size : %d\n", file_size);

        received_file = fopen(FILENAME, "w+");
        if (received_file == NULL)
        {
                fprintf(stderr, "Failed to open file  --> %s\n", strerror(errno));

                exit(EXIT_FAILURE);
        }
        else
        {
        	printf("File opened\n");
        }

        remain_data = file_size;

        while (((len = recv(client_socket, buffer, BUFSIZ, 0)) > 0) && (remain_data > 0))
        {
                fwrite(buffer, sizeof(char), len, received_file);
                remain_data -= len;
                fprintf(stdout, "Receive %ld bytes and we hope :- %d bytes\n", len, remain_data);
        }
        fclose(received_file);

        close(client_socket);

        return 0;
}
