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
    /*
     * So I can print errors that the socket recieves
     * this is only used in multiplayers and usually
     * just a disconnect from the communication.
     */
    printf("Error! %s\n", msg);
    endwin();
    exit(-1);
}
void dlog(const char *msg)
{
    /*
     * Used for debugging, if you turn on debugging,
     * this will print all the status messages onto
     * the screen as the socket thread prints them.
     */
    if (debug)
        printf("%s\n", msg);
}
void server_connect(int port)
{
    /*
     * Initialize a multiplayer game by opening a socket
     * that lets us pass a buffer between the two programs
     */
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
    /*
     * Gather all the information into a string
     * send it into a buffer, flush the network
     * stream, write the buffer to it, and send
     * the OK signal over to the client so it
     * can be set as the socket message and
     * displayed as the other player's score and
     * stats to compete.
     */
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
        n = (int)read((int)newsockfd,buffer,255);
        if (n < 0) error("ERROR reading from socket");
        strcpy(env.socket_message, buffer);
        //fprintf(stdout, "%s\n", env.socket_message);
        n =(int)write((int)newsockfd,"OK",3);
        if (n < 0) error("ERROR writing to socket");
        close(newsockfd);
    }
    if (end)
        close(serv_sockfd);
}

void client(char *host, int port)
{
    /*
     * Recieve the socket message, and set it as
     * the socket message in the environment
     * so that the display thread will show it.
     */
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
    t << " Health: ";
    t << env.health;
    t << " Lives: ";
    t << env.lives;
    t << " Kills: ";
    t << env.kills;
    t << " Levels Completed: ";
    t << env.levels_completed;
    t << " Time: " << right << setw(2) << setprecision(2) << setfill('0') << env.timer.minute << ":" << right << setw(2) << env.timer.second << setfill(' ') << left;
    if (env.paused)
        t << "\33[31m Player has paused game\33[0m";
    strcpy(buffer, t.str().c_str());
    n = (int)write((int)sockfd,buffer,(int)strlen(buffer));
    if (n < 0) 
        error("ERROR writing to socket");
    bzero(buffer,256);
    n = (int)read((int)sockfd,buffer,255);
    if (n < 0) 
        error("Shutting down, (player probably quit)");
    //printf("%s\n",buffer);
    close(sockfd);
}
void server_end(void)
{
    /*
     * Kill the socket so we can shut down the
     * game. And the other player's game will die
     * as well.
     */
    close(serv_sockfd);
    dlog("socket closed");
}