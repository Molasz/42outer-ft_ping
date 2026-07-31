#include "ft_ping.h"

static void	fill_dest_addr(t_data *data, struct addrinfo *res)
{
	struct sockaddr_in	*addr_in;

	addr_in = (struct sockaddr_in *)res->ai_addr;
	data->dest_addr = *addr_in;
	if (!inet_ntop(AF_INET, &addr_in->sin_addr,
			data->dest_ip_str, INET_ADDRSTRLEN))
	{
		fprintf(stderr, "ft_ping: inet_ntop failed\n");
		free_exit(data, 1);
	}
}

static void	open_socket(t_data *data)
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

void	resolve_targets(t_data *data)
{
	struct addrinfo	hints;
	struct addrinfo	*res;
	int				status;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	status = getaddrinfo(data->host, NULL, &hints, &res);
	if (status != 0)
	{
		fprintf(stderr, "ft_ping: %s: %s\n", data->host, gai_strerror(status));
		free_exit(data, 1);
	}
	fill_dest_addr(data, res);
	freeaddrinfo(res);
	open_socket(data);
}
