/*
** EPITECH PROJECT, 2018
** print
** File description:
** print
*/

#include "packet.h"

void print_ethernet_header(unsigned char *buffer, int size)
{
	struct ethhdr *eth = (struct ethhdr *)buffer;

	(void) size;
	fprintf(file, "\n");
	fprintf(file, "Ethernet Header\n");
	fprintf(file, "   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
	fprintf(file, "   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]);
	fprintf(file, "   |-Protocol            : %u \n", (unsigned short)eth->h_proto);
}
 
void print_ipheader(unsigned char *buffer, int size)
{
	struct sockaddr_in source, dest;
	print_ethernet_header(buffer, size);
	struct iphdr *iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));

	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = iph->saddr;

	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = iph->daddr;

	fprintf(file, "\n");
	fprintf(file, "IP Header\n");
	fprintf(file, "   |-IP Version        : %d\n", (unsigned int)iph->version);
	fprintf(file, "   |-IP Header Length  : %d DWORDS or %d Bytes\n", (unsigned int)iph->ihl, ((unsigned int)(iph->ihl)) * 4);
	fprintf(file, "   |-Type Of Service   : %d\n", (unsigned int)iph->tos);
	fprintf(file, "   |-IP Total Length   : %d  Bytes(Size of Packet)\n", ntohs(iph->tot_len));
	fprintf(file, "   |-Identification    : %d\n", ntohs(iph->id));
	fprintf(file, "   |-TTL      : %d\n", (unsigned int)iph->ttl);
	fprintf(file, "   |-Protocol : %d\n", (unsigned int)iph->protocol);
	fprintf(file, "   |-Checksum : %d\n", ntohs(iph->check));
	fprintf(file, "   |-Source IP        : %s\n", inet_ntoa(source.sin_addr));
	fprintf(file, "   |-Destination IP   : %s\n", inet_ntoa(dest.sin_addr));
}
