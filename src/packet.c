#include "ft_ping.h"

static unsigned short	compute_checksum(void *buf, int len)
{
	unsigned short	*ptr;
	unsigned int	sum;
	unsigned short	odd_byte;

	ptr = (unsigned short *) buf;
	sum = 0;
	while (len > 1)
	{
		sum += *ptr++;
		len -= 2;
	}
	if (len == 1)
	{
		odd_byte = 0;
		*(unsigned char *)&odd_byte = *(unsigned char *)ptr;
		sum += odd_byte;
	}
	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);
	return ((unsigned short) ~sum);
}

void	build_packet(t_data *data, char *packet, int seq)
{
	struct icmphdr	*icmp_hdr;
	struct timeval	*tv;
	int				i;

	memset(packet, 0, PACKET_SIZE);
	icmp_hdr = (struct icmphdr *) packet;
	icmp_hdr->type = ICMP_ECHO;
	icmp_hdr->code = 0;
	icmp_hdr->un.echo.id = getpid() & 0xFFFF;
	icmp_hdr->un.echo.sequence = seq;
	icmp_hdr->checksum = 0;

	tv = (struct timeval *)(packet + sizeof(struct icmphdr));
	gettimeofday(tv, NULL);

	i = sizeof(struct timeval);
	while (i < DATA_SIZE)
	{
		packet[sizeof(struct icmphdr) + i] = i;
		i++;
	}
	icmp_hdr->checksum = compute_checksum(packet, PACKET_SIZE);
	(void) data;
}