#include "ft_ping.h"

static void	fill_dest_addr(t_data *data, struct addrinfo *res)
{
	struct sockaddr_in	*addr_in;

	addr_in = (struct sockaddr_in *)res->ai_addr;
	data->dest_addr = *addr_in;
	if (!inet_ntop(AF_INET, &addr_in->sin_addr, data->dest_ip_str, INET_ADDRSTRLEN))
	{
		fprintf(stderr, "ft_ping: inet_ntop failed\n");
		exit(1);
	}
}

void    resolve_targets(t_data *data)
{
    struct addrinfo	hints;
	struct addrinfo	*res;
	int				status;
	struct in_addr	tmp;

	data->is_ip_literal = (inet_pton(AF_INET, data->host, &tmp) == 1);
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	status = getaddrinfo(data->host, NULL, &hints, &res);
	if (status != 0)
	{
		fprintf(stderr, "ft_ping: %s: %s\n", data->host, gai_strerror(status));
		exit(1);
	}
	fill_dest_addr(data, res);
	freeaddrinfo(res);
}