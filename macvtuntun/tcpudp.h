#pragma once
#ifndef TCPUDP_H
#define TCPUDP_H
#include <sys/socket.h>
#include <main.h>
#include <sys/types.h>
#include <tun.h>
#endif // TCPUDP_H
int open_socket();
void get_macaddr();
void getack();
void* read_from_sock(void*);
int cread(int fd, char *buf, int n);
int cwrite(int fd, char *buf, int n);
int write_n(int fd, char *buf, int n);
