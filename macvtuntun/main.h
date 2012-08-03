#pragma once
#ifndef MAIN_H
#define MAIN_H
#endif // MAIN_H
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <pthread.h>
#include <tun.h>
int tcpudp_fd;
int tun_fd;
int port;
char tun_name[32];
char tun_mac[6];
struct sockaddr_in daddr_in;
struct sockaddr_in saddr_in;
pthread_t pt_read_from_if;
pthread_t pt_read_from_sock;

struct pktdata_t{
    unsigned int len;
    char data[MAX_PKT];
}__attribute__((packed));

struct pktdata_t recvpktdata;
struct pktdata_t sendpktdata;
