/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "socket.h"
extern _environment env; //global data
bool running = false, end = false;
int serv_sockfd, cli_sockfd;
bool debug = false;
void error(const char *msg)
{
    printf("Error! %s\n", msg);
    exit(-1);
}
void dlog(const char *msg)
{
    if (debug)
        printf("%s\n", msg);
}
void server_connect(int port)
{
    dlog("Server connect\n");
    int portno;
    struct sockaddr_in serv_addr;
    serv_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sockfd < 0) 
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(serv_sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    running = true;
}
void server(int port)
{
    if (!running)
    {
        server_connect(port);
        return; //so we can call it from main
    }
    if (running)
    {
        dlog("Server run\n");
        int newsockfd;
        socklen_t clilen;
        char buffer[256];
        struct sockaddr_in cli_addr;
        int n;
        listen(serv_sockfd,5);
        dlog("listening\n");
        clilen = sizeof(cli_addr);
        newsockfd = accept(serv_sockfd, 
                       (struct sockaddr *) &cli_addr, 
                       &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) error("ERROR reading from socket");
        strcpy(env.socket_message, buffer);
        //fprintf(stdout, "%s\n", env.socket_message);
        n = write(newsockfd,"OK",3);
        if (n < 0) error("ERROR writing to socket");
        close(newsockfd);
    }
    if (end)
        close(serv_sockfd);
}

void client(char *host, int port)
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
    //printf("Please enter the message: ");
    bzero(buffer,256);
    ostringstream t;
    t << "  "; //pad it so it lines up with the health display on p1||p2
    t << "Score: ";
    t << env.totalscore;
    t << " Lives: ";
    t << env.lives;
    t << " Kills: ";
    t << env.kills;
    t << " Levels Completed: ";
    t << env.levels_completed;
    strcpy(buffer, t.str().c_str());
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
        error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
        error("ERROR reading from socket");
    //printf("%s\n",buffer);
    close(sockfd);
}
void server_end(void)
{
    close(serv_sockfd);
    dlog("socket closed");
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