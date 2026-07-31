#include "ft_ping.h"

static t_data	*g_data;

static void	print_stats(t_data *data)
{
	double	loss;
	double	avg;
	double	mdev;

	loss = 0;
	if (data->sent > 0)
		loss = 100.0 * (data->sent - data->received) / data->sent;
	printf("\n--- %s ping statistics ---\n", data->host);
	printf(
		"%d packets transmitted, %d received, %.0f%% packet loss, time %dms\n",
		data->sent, data->received, loss, 100); // TIME
	if (data->received > 0)
	{
		avg = data->rtt_sum / data->received;
		mdev = sqrt(data->rtt_sum2 / data->received - avg * avg);
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
			data->rtt_min, avg, data->rtt_max, mdev);
	}
}

static void	handle_sigint(int sig)
{
	(void) sig;
	print_stats(g_data);
	free_exit(g_data, 0);
}

static void	print_header(t_data *data)
{
	struct in_addr	tmp;

	if (inet_pton(AF_INET, data->host, &tmp) == 1)
		printf("PING %s (%s): 56(84) bytes of data\n",
			data->dest_ip_str, data->dest_ip_str);
	else
		printf("PING %s (%s): 56(84) bytes of data\n",
			data->host, data->dest_ip_str);
}

void	setup(t_data *data)
{
	g_data = data;
	signal(SIGINT, handle_sigint);
	print_header(data);
}
