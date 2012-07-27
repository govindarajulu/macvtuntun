#include <error.h>
#include <sys/socket.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <main.h>

int open_socket()
{
    int fd;
    struct sockaddr_in saddr_in;
    memset(&saddr_in,0,sizeof(saddr_in));
    saddr_in.sin_family=AF_INET;
    saddr_in.sin_port=htons(port);
    bcopy(saddress->h_addr_list[0],&saddr_in.sin_addr.s_addr,saddress->h_length);
    if(udp){

    }
    else{
        fd=socket(AF_INET,SOCK_STREAM,0);
        if(fd==-1){
            perror("socket");
            exit(-1);
        }
    }
    return fd;
}
