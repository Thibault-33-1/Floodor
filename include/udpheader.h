#ifndef UDPHEADER_H_INCLUDED
#define UDPHEADER_H_INCLUDED


#include <stdio.h>   // fputs
#include <string.h>  //memset
#include <sys/socket.h>
#include <stdlib.h>  //for exit(0);
#include <errno.h>   //For errno - the error number
#include <netinet/tcp.h>   //Provides declarations for tcp header
#include <netinet/ip.h>    //Provides declarations for ip header
#include <netinet/in.h>     /** Both for  inet_addr() **/
#include <arpa/inet.h>      /** inet_addr() **/

#include <time.h> /* srand() */

/* 96 bit (12 bytes) pseudo header needed for udp header checksum calculation */

struct pseudo_header    //needed for checksum calculation
{
    unsigned int source_address;
    unsigned int dest_address;
    unsigned char placeholder;
    unsigned char protocol;
    unsigned short udp_length;

    struct udphdr udp;
};

#endif



