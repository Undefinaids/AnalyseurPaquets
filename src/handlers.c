/*
** EPITECH PROJECT, 2018
** handlers
** File description:
** handlers
*/

#include "packet.h"

void	print_data(unsigned char* data , int size)
{
	int i, j;

	for (i = 0; i < size; i++) {
		if (i != 0 && i % 16 == 0) {
			fprintf(file, "         ");
			for (j = i - 16; j < i; j++) {
				if (data[j] >= 32 && data[j] <= 128)
					fprintf(file, "%c", (unsigned char)data[j]);
				else
					fprintf(file, ".");
			}
			fprintf(file, "\n");
		}
		if (i % 16 == 0)
			fprintf(file, "   ");
		fprintf(file, " %02X", (unsigned int)data[i]);
		if (i == size - 1) {
			for (j = 0; j < 15 - i % 16; j++) {
				fprintf(file, "   ");
			}
			fprintf(file, "         ");
			for (j = i - i % 16; j <= i; j++) {
				if (data[j] >= 32 && data[j] <= 128)
					fprintf(file, "%c", (unsigned char)data[j]);
				else
					fprintf(file, ".");
			}
			fprintf(file, "\n");
		}
	}
}

void	handle_tcp(data_t *data, unsigned char *buffer, unsigned int size)
{
	unsigned short iphdrlen;
	struct iphdr *iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));
	iphdrlen = iph->ihl * 4;
	struct tcphdr *tcph = (struct tcphdr*)(buffer + iphdrlen + sizeof(struct ethhdr));
	int header_size = sizeof(struct ethhdr) + iphdrlen + tcph->doff * 4;

	fprintf(file, "\n\n***********************TCP Packet*************************\n");
	print_ipheader(buffer, size);
	fprintf(file, "\n");
	fprintf(file, "TCP Header\n");
	fprintf(file, "   |-Source Port      : %u\n", ntohs(tcph->source));
	fprintf(file, "   |-Destination Port : %u\n", ntohs(tcph->dest));
	fprintf(file, "   |-Sequence Number    : %u\n", ntohl(tcph->seq));
	fprintf(file, "   |-Acknowledge Number : %u\n", ntohl(tcph->ack_seq));
	fprintf(file, "   |-Header Length      : %d DWORDS or %d BYTES\n", (unsigned int)tcph->doff, (unsigned int)tcph->doff * 4);
	fprintf(file, "   |-Urgent Flag          : %d\n", (unsigned int)tcph->urg);
	fprintf(file, "   |-Acknowledgement Flag : %d\n", (unsigned int)tcph->ack);
	fprintf(file, "   |-Push Flag            : %d\n", (unsigned int)tcph->psh);
	fprintf(file, "   |-Reset Flag           : %d\n", (unsigned int)tcph->rst);
	fprintf(file, "   |-Synchronise Flag     : %d\n", (unsigned int)tcph->syn);
	fprintf(file, "   |-Finish Flag          : %d\n", (unsigned int)tcph->fin);
	fprintf(file, "   |-Window         : %d\n", ntohs(tcph->window));
	fprintf(file, "   |-Checksum       : %d\n", ntohs(tcph->check));
	fprintf(file, "   |-Urgent Pointer : %d\n", tcph->urg_ptr);
	fprintf(file, "\n");
	fprintf(file, "                        DATA Dump                         ");
	fprintf(file, "\n");
	fprintf(file, "IP Header\n");
	print_data(buffer, iphdrlen);

	fprintf(file, "TCP Header\n");
	print_data(buffer + iphdrlen,tcph->doff * 4);

	fprintf(file, "Data Payload\n");
	print_data(buffer + header_size, size - header_size);
	fprintf(file, "\n###########################################################");
	data->tcp += 1;
}

void	handle_udp(data_t *data, unsigned char *buffer, unsigned int size)
{
	unsigned short iphdrlen;     
	struct iphdr *iph = (struct iphdr *)(buffer +  sizeof(struct ethhdr));
	iphdrlen = iph->ihl * 4;
	struct udphdr *udph = (struct udphdr*)(buffer + iphdrlen  + sizeof(struct ethhdr));
	int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;
     
	fprintf(file, "\n\n***********************UDP Packet*************************\n");
	print_ipheader(buffer, size);
	fprintf(file, "\nUDP Header\n");
	fprintf(file, "   |-Source Port      : %d\n", ntohs(udph->source));
	fprintf(file, "   |-Destination Port : %d\n", ntohs(udph->dest));
	fprintf(file, "   |-UDP Length       : %d\n", ntohs(udph->len));
	fprintf(file, "   |-UDP Checksum     : %d\n", ntohs(udph->check));

	fprintf(file, "\n");
	fprintf(file, "IP Header\n");
	print_data(buffer, iphdrlen);

	fprintf(file, "UDP Header\n");
	print_data(buffer + iphdrlen, sizeof(udph));

	fprintf(file, "Data Payload\n");
	print_data(buffer + header_size, size - header_size);
     
	fprintf(file, "\n###########################################################");
	data->udp += 1;
}
