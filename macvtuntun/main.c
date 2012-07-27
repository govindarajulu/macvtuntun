#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>
#include <getopt.h>

int tcpudp_fd=-1;

int main(int argc, char* argv[])
{
    const char *short_opt="hutp:";
    const struct option long_option[]={
        {"help",0,NULL,'h'},
        {"udp",0,NULL,'u'},
        {"tcp",0,NULL,'t'},
        {"port",1,NULL,'p'}
    };
    int next_arg;
    do{
        next_arg=getopt_long(argc,argv,short_opt,long_option,NULL);
        switch(next_arg)
        {
        case 'h':
            printf("help\n");
            printf("Usage: %s [-ut] [-p port] [-h]\n");
            printf("-p tcp/udp port\n");
            printf("-u use usp socket\n");
            printf("-t use tcp socket\n");
            break;
        case 'o':
            printf("o-%s\n",optarg);
            break;
        case '?':
            printf("?\n");
            break;
        case -1:
            break;
        default:
            printf("usage: %s -h -o <object>\n",argv[0]);
            break;

        }
    }while(next_arg!=-1);
    return 0;
}

