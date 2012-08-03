#include <error.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <net/if.h>
#include <sys/socket.h>
#include <error.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <main.h>
#include <tcpudp.h>
int cread(int fd, char *buf, int n){

    int nread;

    if((nread=read(fd, buf, n)) < 0){
        perror("Reading data");
        exit(1);
    }
    return nread;
}
int cwrite(int fd, char *buf, int n){

    int nwrite;

    if((nwrite=write(fd, buf, n)) < 0){
        perror("Writing data");
        exit(1);
    }
    return nwrite;
}

int read_n(int fd, char *buf, int n) {

    int nread, left = n;

    while(left > 0) {
        if ((nread = cread(fd, buf, left)) == 0){
            return 0 ;
        }else {
            left -= nread;
            buf += nread;
        }
    }
    return n;
}
int write_n(int fd, char *buf, int n) {

    int nwrite, left = n;

    while(left > 0) {
        if ((nwrite = cwrite(fd, buf, left)) == 0){
            return 0 ;
        }else {
            left -= nwrite;
            buf += nwrite;
        }
    }
    return n;
}

int open_socket()
{
    int fd,cfd;
    printf("using source IP address: %s:%d\n",inet_ntoa(saddr_in.sin_addr),ntohs(saddr_in.sin_port));
    printf("connecting to macvtun server: %s:%d\n",inet_ntoa(daddr_in.sin_addr),ntohs(daddr_in.sin_port));
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
    return fd;
}

void get_macaddr(){
    int s;
    struct ifreq buffer;
    s = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&buffer, 0x00, sizeof(buffer));
    strcpy(buffer.ifr_name, tun_name);
    ioctl(s, SIOCGIFHWADDR, &buffer);
    close(s);
    memset(tun_mac,0,6);
    bcopy(buffer.ifr_hwaddr.sa_data,tun_mac,6);
    printf("Mac address of %s is ",tun_name);
    printf("%x:%x:%x:%x:%x:%x\n",
           (unsigned char) tun_mac[0],
           (unsigned char) tun_mac[1],
           (unsigned char) tun_mac[2],
           (unsigned char) tun_mac[3],
           (unsigned char) tun_mac[4],
           (unsigned char) tun_mac[5]
           );
}

void getack(){
    unsigned char integ[6];
    if(read_n(tcpudp_fd,(char*)integ,6)==-1){
        perror("read");
        exit(-1);
    }
    if(!(integ[0]==65 &&
         integ[1]==66 &&
         integ[2]==67 &&
         integ[3]==68 &&
         integ[4]==69 &&
         integ[5]==70)){
        printf("ack failed\n");
        exit(-1);
    }else{
        printf("got ack\n");
    }
}

void* read_from_sock(void* none){
    unsigned int size;
    while(1){
        read_n(tcpudp_fd,(char*)&recvpktdata.len,4);
        size=ntohl(recvpktdata.len);
        if(size>MAX_PKT){
            printf("size received is %d,greater then MAX_PKT\n",size);
            exit(-1);
        }
        read_n(tcpudp_fd,recvpktdata.data,size);
        write_n(tun_fd,recvpktdata.data,size);
    }
    return none;
}
