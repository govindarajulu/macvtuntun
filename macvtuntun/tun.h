#pragma once
#ifndef TUN_H
#define TUN_H

#endif // TUN_H
#define MAX_PKT 3000
int tun_alloc(char *dev, int flags);
void* read_from_if(void*);
