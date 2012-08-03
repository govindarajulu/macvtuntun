#ifndef TUN_H
#define TUN_H

#endif // TUN_H
int tun_alloc(char *dev, int flags);
void writepktotun();
#define MAX_PKT 3000
void* read_from_if(void*);
