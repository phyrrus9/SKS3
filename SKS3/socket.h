/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <sstream>
#include "engine.h"

void dlog(const char *); //log for debugging
void server(int); //runs the socket that recieves the data from the client
void server_end(void); //closes the server socket
void client(char *, int); //sends data to the other computer