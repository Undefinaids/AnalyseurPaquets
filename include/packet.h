/*
** PERSONAL PROJECT, 2018
** packet
** File description:
** packet
*/

#ifndef PACKET_H_
#define PACKET_H_

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <net/ethernet.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

typedef struct	data_s {
	unsigned int udp;
	unsigned int tcp;
	unsigned int others;
}		data_t;

typedef struct	packet_s
{
        int	protocol;
	void	(*fct)(data_t *data, unsigned char *buffer, unsigned int size);
}	        packet_t;

void	handle_udp(data_t *data, unsigned char *buffer, unsigned int size);
void	handle_tcp(data_t *data, unsigned char *buffer, unsigned int size);
void	print_ipheader(unsigned char *buffer, int size);

extern int sock_raw;
extern FILE *file;
extern const packet_t packet[3];

#endif /* PACKET_H_ */
