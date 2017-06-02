
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    //printf("Client programming\n");

    char* host;
    char* path;
    int sockfd;
    int connection;
    char* user_input;
    char url[255];

    if(argc != 3) {
        printf("Usage: %s <host> <path>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    path = argv[2];
    //Get url
    //user_input = argv[1]; 

    //copy into url
    //strcpy(url, user_input);   

    //printf("User Input: Host: %s Path: %s\n", host, path);

    //seperate the host name from the path
    //int scanned = sscanf(url, "http://%[^/]/%s", host, path);
    //if(scanned>0) {
     //   printf("Host: %s\nPath: %s", host, path); 
    //} else {
    //printf("Error");
    //}

    //Create socket    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0) {
        perror("Error opening socket");
    }

    //Connect to a server
    struct hostent *server_he; //a host address entry
    
    if ((server_he = gethostbyname(host)) == NULL) {
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
    serveraddr.sin_port = htons(80);

    //Connect to server
    if(connect(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
        perror("Cannot connect to the server\n");
        exit(0);
    }else {
        printf("Connected to the server\n");
    }

    //Use the API to send a message
    char request[255];
    //Construct message
    sprintf(request, "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n", path, host);
    printf("request=%s\n",request);
    int bytes_sent;
    //send message
    bytes_sent = send(sockfd, request, strlen(request), 0);

    //Use the API to receive a message
    char buffer[1024];
    char http_code[20];
    char* tok;
    int byte_received;
    int http_code_num = 0;
    char* file_name;
   
    
    file_name = strrchr(path, '/');
    if(file_name != NULL) {
	file_name = file_name +1;
    	printf("File name: %s\n", file_name);
    } else {
        file_name = path;
    }

    printf("Filename: %s", file_name);



    bzero(buffer, 1024);
    byte_received = recv(sockfd, http_code, 16, 0);    
    byte_received = recv(sockfd, buffer, 1024, 0);
    printf("HTTP code: %s\n", http_code);

    //get http code, tokenize string, use 2nd token for code
    tok = strtok(http_code, " ");
    tok = strtok(NULL, " ");
    if(tok != NULL) {
        printf("Token: %s\n", tok);
        http_code_num = atoi(tok);
    }
    //if code is good, 200, then proceed with download
    if(http_code_num == 200) {

            //remove header from buffer
            char* end_of_header = strstr(buffer, "\r\n\r\n");           
            char* data_here = end_of_header + 4;
            //get length of data_here
            int data_here_size = strlen(data_here);
            printf("Data size: %d\n", data_here_size);
            printf("Buffer size: %d\n", strlen(buffer));
            //printf("End of header: %d\n", (strlen(buffer)-data_here_size
            //print buffer from data_here location
            
                         
 
            
            //int length_of_data = byte_received - ();
            printf("The data part is: %s\n", data_here);
	    if(byte_received < 0) {
		error("ERROR reading from socket\n");
	    } 

	    //print entire message
	    //printf("Message received:\n%s\n", buffer);
           if(file_name != NULL) { 
                    printf("Writing data");
		    FILE *bfp = fopen("File 1", "wb");
                    //write what is inside the buffer minus the header *****Do not use a pointer. Must be array
                    //fwrite(data_here, sizeof(char), data_here_size, 0); 
                    //fclose(bfp);
                    //printf("Closing file");

                    //refill buffer before entering loop
                   // byte_received = recv(sockfd, buffer, 1024, 0);
             //}
                    //Continue writing the rest of the file
		    while(byte_received > 0) {
			printf("%s", buffer);
		        //save to file
		        fwrite(buffer, sizeof(char), byte_received, bfp);
			byte_received = recv(sockfd, buffer, 1024, 0);
		    }
        a            //close file
	    }
    
    } else {
       //print error message here
       printf("%d Error. Please try again later.\n", http_code_num); 
    } 



    return 0;
}







