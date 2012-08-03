#ifndef TCPUDP_H
#define TCPUDP_H
#include <sys/socket.h>
#include <main.h>
#include <sys/types.h>
#include <tun.h>
#endif // TCPUDP_H
int open_socket();
void get_macaddr();
void getack();

struct msghdr recvmsghdr;
struct iovec recviovec[2];
u_int16_t recvmsglen;
unsigned char recvmsgdata[MAX_PKT];
size_t recvmsgdatalen;

struct msghdr sendmsghdr;
struct iovec sendiovec[2];
u_int16_t sendmsglen;
unsigned char sendmsgdata[MAX_PKT];
size_t sendmsgdatalen;

ssize_t sendpkt(int fd,const void* data,size_t len);
ssize_t recvpkt(int fd,void* data, size_t len);
ssize_t recvmsgpkt(int fd);
void* read_from_sock(void*);
