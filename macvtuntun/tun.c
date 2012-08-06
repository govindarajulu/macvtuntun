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
    struct pktdata_t sendpktdata;
    int size;
    while(1){
        size=cread(tun_fd,(char*)&sendpktdata,MAX_PKT);
        if(size>MAX_PKT){
            fprintf(stderr,"size received is %d, greater then MAX_PKT\n",size);
            exit(-1);
            pthread_cancel(pt_read_from_sock);
            pthread_exit(NULL);
        }
        sendpktdata.len=htonl(size);
        printf("read %d bytes from tap\n",size);
        int i;
         for(i=0;i<size;i++){
             printf("%2x",(unsigned char)sendpktdata.data[i]);
        }
        printf("\n");
        write_n(tcpudp_fd,(char*)&sendpktdata,size+4);
    }
    pthread_exit(none);
}
