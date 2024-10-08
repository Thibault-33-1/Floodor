#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

 /************** in main.c *************************/

#include "../include/headers.h"

void setWindow(void);

unsigned short udp_csum(unsigned short *ptr,int nbytes);

unsigned short tcp_csum(unsigned short *ptr,int nbytes);

void createUDPThread(void);

void createTCPThread(void);

void udpFlood(void) __attribute__((noreturn));

void tcpFlood(void) __attribute__((noreturn));

#endif // PROTOTYPES_H_INCLUDED
