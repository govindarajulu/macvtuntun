#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>
#include <getopt.h>
#include <netdb.h>
#include <main.h>
#include <tun.h>
#include <tcpudp.h>
#include <arpa/ftp.h>
void process_arg(int argc, char* argv[]){
    int next_arg;
    struct hostent * daddress;
    struct hostent * saddress;
    const struct option long_option[]={
        {"port",1,NULL,'p'},
        {"udp",0,NULL,'u'},
        {"tun",1,NULL,'t'},
        {"help",0,NULL,'h'},
        {"daddr",1,NULL,'d'},
        {"saddr",1,NULL,'s'}
    };
    const char *short_opt="p:ut:hd:s:";
    port=4500;
    udp=0;
    tcpudp_fd=-1;
    tun_fd=-1;
    tun_name=NULL;

    memset(&saddr_in,0,sizeof(saddr_in));
    saddr_in.sin_family=AF_INET;
    saddr_in.sin_port=htons(0);

    memset(&daddr_in,0,sizeof(daddr_in));
    daddr_in.sin_family=AF_INET;

    do{
        next_arg=getopt_long(argc,argv,short_opt,long_option,NULL);
        switch(next_arg)
        {
        case 'h':
usage:
            printf("Usage: %s [-ut] [-p port] [-h] [-t tunnel name] ",argv[0]);
            printf("[-d address] [-s address]\n");
            printf("-p tcp/udp port\n");
            printf("-u use udp socket\n");
            printf("-t tunnel name\n");
            printf("-h help menu\n");
            printf("-d macvtun system IP address\n");
            printf("-s source ip address to use\n");
            exit(0);
            break;
        case 'u':
            udp=1;
            break;
        case 'd':
            daddress=gethostbyname(optarg);
            printf("daddress=%s\n",optarg);
            if(daddress==NULL){
                perror("gethostbyname");
                printf("could not resolved hostname\n");
                exit(-1);
            }
            bcopy(daddress->h_addr_list[0],&daddr_in.sin_addr.s_addr,daddress->h_length);

            break;
        case 's':
            printf("saddress=%s\n",optarg);
            saddress=gethostbyname(optarg);
            if(saddress==NULL){
                perror("gethostbyname");
                printf("could not resolved hostname\n");
                exit(-1);
            }
            bcopy(saddress->h_addr_list[0],&saddr_in.sin_addr.s_addr,saddress->h_length);
            break;
        case 't':
            tun_name=malloc(strlen(optarg)+1);
            strcpy(tun_name,optarg);
            break;
        case 'p':
            port=atoi(optarg);
            break;
        case -1:
            break;
        case '?':
            goto usage;
        default:
            printf("usage: %s -h -o <object>\n",argv[0]);
            break;
        }
    }while(next_arg!=-1);
    daddr_in.sin_port=htons(port);
    printf("%d",port);
}

int main(int argc, char* argv[])
{
    process_arg(argc,argv);
    open_socket();

    return 0;
}
