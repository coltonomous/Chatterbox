#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// error handling helper function
void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[501];	// Stores message contents
	char handle[11];	// Stores client handle
	char host[20];	// Stores server handle
	
    // creates the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname(argv[1]);

    // establishes serv_addr
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // connects to the server and checks if it was successful
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        error("CLIENT: ERROR connecting to host\n");
    }

    // clears the command line
    printf("\e[1;1H\e[2J");

	// Confirms successful connection to client
	printf("Connection to host successful...\n");
	
    // gets client handle
    bzero(handle,10);
    printf("Ener a handle for the session (up to 10 characters): ");
    fgets(handle, 10, stdin);

    // removes the newline from the end of handle
	if (handle[strlen(handle) - 1] == '\n') {
		handle[strlen(handle) - 1] = '\0';
	}
	
	// Sends client handle to server
	write(sockfd, handle, strlen(handle));
	
	// Gets server handle from server
	bzero(host, sizeof(host));
	read(sockfd, host, sizeof(host));

    while (1) {
		// presents the user's handle and waits for message
		printf("%s> ", handle);
		bzero(buffer, sizeof(buffer));
		fgets(buffer, sizeof(buffer), stdin);

		// removes the newline from the end of message
		if (buffer[strlen(buffer) - 1] == '\n') {
			buffer[strlen(buffer) - 1] = '\0';
		}
		
		// Handles client message sending
		write(sockfd, buffer, strlen(buffer));
		if (strcmp(buffer, "\\quit") == 0){ // checks if the user typed "\quit"
			break;
		}
		
		// Handles client message receiving
		bzero(buffer, sizeof(buffer));
		read(sockfd, buffer, sizeof(buffer));
		if (strstr(buffer, "\\quit")){ // checks if the server typed "\quit"
			break;
		} else {
			printf("%s> %s\n", host, buffer);
		}
    }
	close(sockfd);
    return 0;
}

/*
The following resources were referenced for this project implementation:
http://www.linuxhowtos.org/C_C++/socket.htm
Beej's Guide
*/