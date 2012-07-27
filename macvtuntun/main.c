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

void process_arg(int argc, char* argv[]){
    port=4500;
    udp=0;
    tcpudp_fd=-1;
    tun_fd=-1;
    tun_name=NULL;
    int next_arg;
    const struct option long_option[]={
        {"port",1,NULL,'p'},
        {"udp",0,NULL,'u'},
        {"tun",1,NULL,'t'},
        {"help",0,NULL,'h'},
        {"daddr",1,NULL,'d'},
        {"saddr",1,NULL,'s'}
    };
    const char *short_opt="p:ut:hd:s:";
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
            if(daddress==NULL){
                perror("gethostnamebyhost");
                printf("could not resolved hostname\n");
                exit(-1);
            }
            break;
        case 's':
            saddress=gethostbyname(optarg);
            if(saddress==NULL){
                perror("gethostnamebyhost");
                printf("could not resolved hostname\n");
                exit(-1);
            }
            break;
        case 't':
            tun_name=malloc(strlen(optarg)+1);
            strcpy(tun_name,optarg);
            break;
        case 'p':
            port=atoi(optarg);
        case -1:
            break;
        case '?':
            goto usage;
        default:
            printf("usage: %s -h -o <object>\n",argv[0]);
            break;
        }
    }while(next_arg!=-1);
}

int main(int argc, char* argv[])
{
    process_arg(argc,argv);
    printf("port=%d, tun name = %s",port,tun_name);
    return 0;
}
