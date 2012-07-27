#ifndef MAIN_H
#define MAIN_H

#endif // MAIN_H
#include <string.h>
#include <netdb.h>

int tcpudp_fd;
int tun_fd;
int port;
int udp;
char* tun_name;
struct hostent * daddress;
struct hostent * saddress;
