#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <pcap.h>       /*inutile pour l'instant */
#include <gtk-2.0/gtk/gtk.h>

#include <sys/socket.h>     /** inet_ntoa() **/
#include <arpa/inet.h>      // both for inet_addr(), et autrement error dans la déclaration du header ip **/
#include <netinet/in.h>
#include <netinet/udp.h>        //Provides declarations for udp header
#include <netinet/ip.h>         //Provides declarations for ip header
#include <netinet/if_ether.h>   /** ??????? */
#include <ctype.h>      /** isprint() **/

#include <stdlib.h>     /** EXIT_SUCCESS; **/
#include <stdio.h>
#include <errno.h>      /** perror **/
#include <string.h>     /* memset */
#include <pthread.h>


typedef struct in_addr   IN_ADDR;
typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

#endif
