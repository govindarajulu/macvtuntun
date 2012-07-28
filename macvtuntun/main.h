#ifndef MAIN_H
#define MAIN_H

#endif // MAIN_H
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
int tcpudp_fd;
int tun_fd;
int port;
int udp;
char tun_name[32];
char tun_mac[6];
struct sockaddr_in daddr_in;
struct sockaddr_in saddr_in;
