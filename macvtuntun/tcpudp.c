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
    printf("using source IP address: %s:%d\n",inet_ntoa(saddr_in.sin_addr),ntohs(saddr_in.sin_port));
    printf("connecting to macvtun server: %s:%d\n",inet_ntoa(daddr_in.sin_addr),ntohs(daddr_in.sin_port));
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
        cfd=connect(fd,(struct sockaddr*)&daddr_in,sizeof(struct sockaddr));
        if(cfd==-1){
            perror("connect");
            exit(-1);
        }
    }
    return fd;
}
