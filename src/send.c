#include "ft_ping.h"

static double	elapsed_ms(struct timeval *sent)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - sent->tv_sec) * 1000.0
		+ (now.tv_usec - sent->tv_usec) / 1000.0);
}

static void	update_stats(t_data *data, double rtt)
{
	data->received++;
	if (data->rtt_min < 0 || rtt < data->rtt_min)
		data->rtt_min = rtt;
	if (rtt > data->rtt_max)
		data->rtt_max = rtt;
	data->rtt_sum += rtt;
	data->rtt_sum2 += rtt * rtt;
}

static void	handle_packet(t_data *data, char *buf, int len, int seq)
{
	struct ip		*ip_hdr;
	struct icmphdr	*icmp_hdr;
	int				ip_hdr_len;
	struct timeval	*tv_sent;
	double			rtt;

	ip_hdr = (struct ip *) buf;
	ip_hdr_len = ip_hdr->ip_hl * 4;
	if (len < ip_hdr_len + (int) sizeof(struct icmphdr))
		return ;
	icmp_hdr = (struct icmphdr *)(buf + ip_hdr_len);
	if (icmp_hdr->type == ICMP_ECHOREPLY)
	{
		if ((icmp_hdr->un.echo.id & 0xFFFF) != (getpid() & 0xFFFF))
			return ;
		tv_sent = (struct timeval *)(buf + ip_hdr_len + sizeof(struct icmphdr));
		rtt = elapsed_ms(tv_sent);
		update_stats(data, rtt);
		printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.1f ms\n",
			len - ip_hdr_len, data->dest_ip_str, seq + 1, ip_hdr->ip_ttl, rtt);
	}
	else if (data->v_flag)
		printf("From %s: icmp type=%d code=%d\n",
			data->dest_ip_str, icmp_hdr->type, icmp_hdr->code);
}

void	send_recv(t_data *data, int seq)
{
	char	packet[PACKET_SIZE];
	char	recv_buf[1024];
	int		recv_len;

	build_packet(packet, seq);
	if (sendto(data->sockfd, packet, PACKET_SIZE, 0,
			(struct sockaddr *)&data->dest_addr, sizeof(data->dest_addr)) < 0)
	{
		fprintf(stderr, "ft_ping: sendto: %s\n", strerror(errno));
		return ;
	}
	data->sent++;
	recv_len = recvfrom(data->sockfd, recv_buf, sizeof(recv_buf), 0, 0, 0);
	if (recv_len < 0)
	{
		if (data->v_flag)
			printf("Request timeout for icmp_seq %d\n", seq);
		return ;
	}
	handle_packet(data, recv_buf, recv_len, seq);
}
