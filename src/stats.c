#include "ft_ping.h"

void    print_stats(t_data *data)
{
    double	loss;
	double	avg;
	double	mdev;

	loss = 0;
	if (data->sent > 0)
		loss = 100.0 * (data->sent - data->received) / data->sent;
	printf("\n--- %s ping statistics ---\n", data->host);
	printf("%d packets transmitted, %d packets received, %.0f%% packet loss\n",
		data->sent, data->received, loss);
	if (data->received > 0)
	{
		avg = data->rtt_sum / data->received;
		mdev = sqrt(data->rtt_sum2 / data->received - avg * avg);
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
			data->rtt_min, avg, data->rtt_max, mdev);
	}
}
