
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>


int main(int argc, char *argv[]) {
    
    //printf("Client programming\n");

    char* user_input;
    char url[256];
    int sockfd;
    int connection;
    char host[50];
    char path[255];
    char* servername;
    int port = 80;

    if(argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        exit(0);
    }
    user_input = argv[1]; 

    //copy into url
    //strcpy(url, user_input);   

    printf("User Input: %s \n", user_input);

    //seperate the host name from the path
    int scanned = sscanf(argv[1], "http://%[^/]/%s", host, path);
    if(scanned) {
        printf("Host: %s\nPath: %s", host, path); 
    } else {
    printf("Error");
    }

    //Create socket    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0) {
        perror("Error opening socket");
    }
    //close(sockfd);

    //Connect to a server

    struct hostent *server_he; //a host address entry
    
    if ((server_he = gethostbyname(servername)) == NULL) {
        perror("Error in gethostbyname");
        return 2;
    }

    struct sockaddr_in serveraddr;
    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    
    //copy the server address from gethostbyname
    //return in struct hostent (stored in *server_he
    bcopy((char*)server_he->h_addr, (char*)&serveraddr.sin_addr.s_addr, server_he->h_length);
    
    //set port number
    //serveraddr.sin_port = port;
    serveraddr.sin_port = htons(port);

    //Connect to server
    if(connect(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
        perror("Cannot connect to the server\n");
        exit(0);
    }else {
        printf("Connected to the server\n");
    }

    //Use the API to send a message
    char* msg = "GET / HTTP/1.0\r\n\r\n";
    int bytes_sent;
    bytes_sent = send(sockfd, msg, strlen(msg), 0);

    //Use the API to receive a message
    char buffer[1024];
    int byte_received;
    bzero(buffer, 1024);
    byte_received = recv(sockfd, buffer, 1024, 0);
    if(byte_received < 0) {
        error("ERROR reading from socket\n");
    }
    printf("Message received: %s\n", buffer);



    return 0;
}






