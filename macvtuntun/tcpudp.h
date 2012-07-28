#ifndef TCPUDP_H
#define TCPUDP_H

#endif // TCPUDP_H
int open_socket();
void get_macaddr();
void getack();
ssize_t sendpkt(int fd,const void* data,size_t len);
ssize_t recvpkt(int fd,void* data, size_t len);
