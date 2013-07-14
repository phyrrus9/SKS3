/*****************************************************************
 Super Key Seeker Version 3
 Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 This software is free, it may be customized, redistributed
 or used in any way that suits your needs. This software is
 open source, meaning that it MUST be distributed along with
 its source code or have provisions to recieve the source code
 if desired. This program, though it is free and open source
 is still copyright © the following names and companies:
 Ethan Laur (phyrrus9) <phyrrus9@gmail.com> 2012
 MOD Technologies LLC <http:modtech.co> 2012
 This program source code MUST be distributed with this comment
 block intact as a reference to users who would actually like
 to follow the rules. Please do not be a jerk and take credit
 for a program you did not write. This code for the most part
 was written by the following people and companies:
 Ethan Laur (phyrrus9) <phyrrus9@gmail.com>
 Dereck Wonnacott <dereck@gmail.com>
 GNU Project (for ncurses which we all so dearly love)
 All third party lisencing by the above authors is transmitted
 with the source code of this program to its new author, who
 may add his or her name to this block for the works they did
 It is greatly appreciated if any work you do on the program
 is reported back to the original authors (copyright section)
 so that we can incorporate your features into the game as a
 public release. We thank you for reading this file.
 If you want to know how many lines of code are in this project,
 you can just cd into the source directory and run the following
 find . -type f -print0 | xargs -0 cat | wc -l
 =================================================================
 File: socket.cpp
 Description: Multiplayer code, this will control the server and
 client functions used to pass the socket message between clients
 as well as some error handling functions and stuff to properly
 shut the game down to avoid segfaults and portbinds.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "socket.h"
extern _environment env; //global data
bool running = false, endSocket = false;
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
        if (env.socket_message[0] == 'P')
        {
                pause();
                env.socket_paused = true;
        }
        else
            if (env.socket_paused)
            {
                env.socket_paused = false;
                unpause();
            }
        //fprintf(stdout, "%s\n", env.socket_message);
        n =(int)write((int)newsockfd,"OK",3);
        if (n < 0) error("ERROR writing to socket");
        close(newsockfd);
    }
    if (endSocket)
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
    bzero(buffer,256);
    ostringstream t;
    if (env.paused)
        t << "P";
    else
        t << " ";
    t << " "; //pad it so it lines up with the health display on p1||p2
    t << "Score: ";
    t << env.totalscore;
    t << " Health: ";
    t << env.health;
    t << " Lives: ";
    t << env.lives;
    t << " Kills: ";
    t << env.kills;
    t << " Keys: ";
    t << env.keys;
    t << " Levels Completed: ";
    t << env.levels_completed;
    t << " Time: " << right << setw(2) << setprecision(2) << setfill('0') << env.timer.minute << ":" << right << setw(2) << env.timer.second << setfill(' ') << left;
    if (env.paused)
    {
        t << "\n\r\t    \33[31m Player has paused game\33[0m";
        //env.player_socket_paused = false;
    }
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
