#include "ft_ping.h"

void	open_socket(t_data *data)
{
	struct timeval	tv;

	data->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (data->sockfd < 0)
	{
		fprintf(stderr, "ft_ping: icmp open socket: %s\n", strerror(errno));
		free_exit(data, 1);
	}
	tv.tv_sec = TIMEOUT_SEC;
	tv.tv_usec = 0;
	if (setsockopt(data->sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
	{
		fprintf(stderr, "ft_ping: setsockopt: %s\n", strerror(errno));
		free_exit(data, 1);
	}
}