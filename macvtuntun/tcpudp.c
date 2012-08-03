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
int open_socket()
{
    int fd,cfd;
    printf("using source IP address: %s:%d\n",inet_ntoa(saddr_in.sin_addr),ntohs(saddr_in.sin_port));
    printf("connecting to macvtun server: %s:%d\n",inet_ntoa(daddr_in.sin_addr),ntohs(daddr_in.sin_port));
    if(udp){
        fd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
        if(fd==-1){
            perror("socket");
            exit(-1);
        }
        if(bind(fd,(struct sockaddr*)&saddr_in,sizeof(saddr_in))==-1){
            perror("bind");
            exit(-1);
        }
        return fd;
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
        return fd;
    }
    return -1;
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
    if(read(tcpudp_fd,integ,6)==-1){
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
ssize_t sendpkt(int fd,const void* data,size_t len){
    ssize_t size;
    if(udp){
        size=sendto(fd,data,len,0,(struct sockaddr*)&daddr_in,sizeof(struct sockaddr));
        if(size==-1){
            perror("sendto");
            exit(-1);
        }
    }else{
        size=write(fd,data,len);
        if(size==-1){
            perror("write");
            exit(-1);
        }
    }
    return size;
}
ssize_t recvpkt(int fd,void* data, size_t len){
    ssize_t size;
    if(udp){
        unsigned int socklen;
        socklen=sizeof(struct sockaddr);
        size=recvfrom(fd,data,len,0,(struct sockaddr*)&daddr_in,&socklen);
        if(size==-1){
            perror("recvfrom");
            exit(-1);
        }
    }else{
        size=read(fd,data,len);
        if(size==-1){
            perror("read");
            exit(-1);
        }
    }
    return size;
}

ssize_t recvmsgpkt(int fd){
    ssize_t pktsize=-1,recvsize=0;
    if(udp){

    }else{
        recvsize=recvmsg(fd,&recvmsghdr,0);
        if(recvsize<0){
            perror("recvmsg");
            exit(-1);
        }
        //recvsize=recvsize-recvmsghdr.msg_iov->iov_len;
        while((unsigned)recvsize<sizeof(recvmsglen)){
            int i=-1;
            i=read(fd,&((char*)&recvmsglen)[recvsize],sizeof(recvmsglen)-recvsize);
            if(i==-1){
                perror("recvmsg");
                exit(-1);
            }
            recvsize=recvsize+i;
            printf("packetsize=%d,receved =%d\n",pktsize,recvsize);
        }
        pktsize=*(u_int16_t*)recvmsghdr.msg_iov->iov_base;
        pktsize=ntohs(pktsize);
        if(pktsize>MAX_PKT){
            printf("malformat packet(size=%d). pkt length greater than %d\n",pktsize,MAX_PKT);
            exit(-1);
        }
        recvsize=recvsize-sizeof(recvmsglen);
        printf("packetsize=%d,receved =%d\n",pktsize,recvsize);
        while(recvsize<pktsize){
            int i=-1;
            i=read(fd,&recvmsgdata[recvsize],pktsize-recvsize);
            if(i==-1){
                perror("recvmsg");
                exit(-1);
            }
            recvsize=recvsize+i;
            printf("packetsize=%d,receved =%d\n",pktsize,recvsize);
        }
    }
    return recvsize;
}

void* read_from_sock(void* none){
    return none;
}
