#include "socket.h"
extern _environment env; //global data
bool running = false, end = false;
void error(const char *msg)
{
}

int server_connect(int port)
{
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    running = true;
    return sockfd;
}
void server(int port)
{
    int sockfd;
    if (!running)
        sockfd = server_connect(port);
    if (running)
    {
        int newsockfd;
        socklen_t clilen;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;
        int n;
        listen(sockfd,5);
        printf("listening\n");
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, 
                       (struct sockaddr *) &cli_addr, 
                       &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) error("ERROR reading from socket");
        strcpy(env.socket_message, buffer);
        fprintf(stdout, "%s\n", env.socket_message);
        n = write(newsockfd,"OK",3);
        if (n < 0) error("ERROR writing to socket");
        close(newsockfd);
    }
    if (end)
        close(sockfd);
}

void client(char *host, int port)
{
    while (true)
    {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    char buffer[256];
    portno = port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
        error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
        error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    }
}
/*
 int sockfd, newsockfd, portno;
 socklen_t clilen;
 char buffer[256];
 struct sockaddr_in serv_addr, cli_addr;
 int n;
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) 
 error("ERROR opening socket");
 bzero((char *) &serv_addr, sizeof(serv_addr));
 portno = port;
 serv_addr.sin_family = AF_INET;
 serv_addr.sin_addr.s_addr = INADDR_ANY;
 serv_addr.sin_port = htons(portno);
 if (bind(sockfd, (struct sockaddr *) &serv_addr,
 sizeof(serv_addr)) < 0) 
 error("ERROR on binding");
 listen(sockfd,5);
 printf("listening\n");
 clilen = sizeof(cli_addr);
 newsockfd = accept(sockfd, 
 (struct sockaddr *) &cli_addr, 
 &clilen);
 if (newsockfd < 0) 
 error("ERROR on accept");
 bzero(buffer,256);
 n = read(newsockfd,buffer,255);
 if (n < 0) error("ERROR reading from socket");
 fprintf(stdout, "Message: %s\n", buffer);
 if (strcmp(buffer, "hello") == 0)
 printf("Good!\n");
 else
 printf("Bad :(\n");
 
 n = write(newsockfd,"OK",3);
 if (n < 0) error("ERROR writing to socket");
 close(newsockfd);
 close(sockfd);
*/