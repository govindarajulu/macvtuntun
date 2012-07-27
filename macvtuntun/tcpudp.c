#include <error.h>
#include <sys/socket.h>
#include <error.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <main.h>

int open_socket()
{
    int fd,cfd;
    struct sockaddr_in saddr_in;
    memset(&saddr_in,0,sizeof(saddr_in));
    saddr_in.sin_family=AF_INET;
    saddr_in.sin_port=htons(4444);
    bcopy(saddress->h_addr_list[0],&saddr_in.sin_addr.s_addr,saddress->h_length);
    printf("saddr=%s\n",inet_ntoa(*(struct in_addr*)saddress->h_addr_list[0]));

    memset(&peeraddr_in,0,sizeof(peeraddr_in));
    peeraddr_in.sin_family=AF_INET;
    peeraddr_in.sin_port=htons(port);
    bcopy(daddress->h_addr_list[0],&peeraddr_in.sin_addr.s_addr,daddress->h_length);
    printf("daddr=%s\n",inet_ntoa(*(struct in_addr*)daddress->h_addr_list[0]));
    if(udp){

    }
    else{ //tcp
        fd=socket(AF_INET,SOCK_STREAM,0);
        if(fd==-1){
            perror("socket");
            exit(-1);
        }
        if(bind(fd,(struct sockaddr*)&saddr_in,sizeof(saddr_in))==-1){
            perror("bind");
            exit(-1);
        }
        cfd=connect(fd,(struct sockaddr*)&peeraddr_in,sizeof(struct sockaddr));
        if(cfd==-1){
            perror("connect");
            exit(-1);
        }


    }

    return fd;
}
