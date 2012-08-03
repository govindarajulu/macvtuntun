#include <stdio.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <error.h>
#include <string.h>
#include <stropts.h>
#include <linux/types.h>
#include <asm-generic/ioctl.h>
#include <tun.h>
#include <main.h>
#include <tcpudp.h>

int tun_alloc(char *dev, int flags){
    int fd;
    int err;
    struct ifreq ifr;
    fd=open("/dev/net/tun",O_RDWR);
    if(fd==-1){
        perror("open");
        return fd;
    }
    memset((void *)&ifr,0,sizeof(ifr));
    if(*dev){
        strcpy((char*)&ifr.ifr_ifrn,dev);
    }
    ifr.ifr_ifru.ifru_flags=flags;
    if((err=ioctl(fd, TUNSETIFF,(void *)&ifr))<0){
        perror("ioctl");
        return err;
    }
    strcpy(dev,ifr.ifr_ifrn.ifrn_name);
    return fd;
}

void* read_from_if(void* none){
    int size;
    while(1){
        size=cread(tun_fd,sendpktdata.data,MAX_PKT);
        if(size>MAX_PKT){
            printf("size received is greater then MAX_PKT\n");
            exit(-1);
        }
        sendpktdata.len=htonl(size);
        write_n(tcpudp_fd,(char*)&sendpktdata,size+4);
    }
    return none;
}
