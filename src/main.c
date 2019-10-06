/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include "packet.h"

int sock_raw;
FILE *file;
const packet_t packet[3] = {
	{6, &handle_tcp},
	{17, &handle_udp},
	{-1,  NULL}
};

void	handle_packets(unsigned char *buffer, data_t *data, unsigned int size)
{
	struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));

	for (int i = 0; packet[i].protocol != -1; i++) {
		if (iph->protocol == packet[i].protocol) {
			(*(packet[i].fct))(data, buffer, size);
			return;
		}
	}
	data->others++;
}

int	main_loop(int sock_raw)
{
	data_t data;
	unsigned char *buffer = malloc(sizeof(unsigned char) * (65535 + 1));
	int saddr_size , data_size;
	struct sockaddr saddr;

	data.others = 0;
	data.udp = 0;
	data.tcp = 0;
	while (1) {
		saddr_size = sizeof saddr;
		data_size = recvfrom(sock_raw , buffer , 65536 , 0 , &saddr , (socklen_t*)&saddr_size);
		if (data_size < 0)
			return (-1);
		handle_packets(buffer, &data, data_size);
		printf(" - PAQUET TCP : %d UDP : %d AUTRES : %d - \n", data.tcp, data.udp, data.others);
	}
}

int	main(void)
{
	int sock_raw;

	file = fopen("log.txt","w");
	if (file == NULL) {
		printf("Unable to create log.txt file.");
		return (-1);
        }
        printf("Starting\n");
        sock_raw = socket(AF_PACKET , SOCK_RAW , htons(ETH_P_ALL));
        if (sock_raw < 0) {
		perror("Socket Error");
		return (-1);
        }
	main_loop(sock_raw);
	return (0);
}
