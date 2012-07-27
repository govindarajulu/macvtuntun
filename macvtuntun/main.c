#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>
#include <getopt.h>

int tcpudp_fd=-1;
int port=4500;
int udp=1;
int tcp=-1;
const char *short_opt="hutp:";
const struct option long_option[]={
    {"help",0,NULL,'h'},
    {"udp",0,NULL,'u'},
    {"tcp",0,NULL,'t'},
    {"port",1,NULL,'p'}
};
void process_arg(int argc, char* argv[]){
    int next_arg;
    do{
        next_arg=getopt_long(argc,argv,short_opt,long_option,NULL);
        switch(next_arg)
        {
        case 'h':
            usage:
            printf("Usage: %s [-ut] [-p port] [-h]\n",argv[0]);
            printf("-p tcp/udp port\n");
            printf("-u use usp socket\n");
            printf("-t use tcp socket\n");
            printf("-h help menu\n");
            exit(0);
            break;
        case 'u':
            udp=1;
            tcp=-1;
            break;
        case 't':
            tcp=1;
            udp=-1;
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
    return 0;
}
