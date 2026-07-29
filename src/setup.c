#include "ft_ping.h"

static t_data	*g_data;

static void	handle_sigint(int sig)
{
	(void) sig;
	print_stats(g_data);
	free_exit(g_data, 0);
}

static void	print_header(t_data *data)
{
	if (data->is_ip_literal)
		printf("PING %s (%s): 56 data bytes\n", data->dest_ip_str, data->dest_ip_str);
	else
		printf("PING %s (%s): 56 data bytes\n", data->host, data->dest_ip_str);
}

void	setup(t_data *data)
{
	g_data = data;
	signal(SIGINT, handle_sigint);
	print_header(data);
}