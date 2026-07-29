#include "ft_ping.h"

static void	init_data(t_data *data)
{
    data->host = NULL;
    data->v_flag = 0;
	data->sockfd = -1;
	data->sent = 0;
	data->received = 0;
	data->rtt_min = -1;
	data->rtt_max = 0;
	data->rtt_sum = 0;
	data->rtt_sum2 = 0;
	data->exit_code = 0;
}

void	free_exit(t_data *data, int exit_code)
{
    if (data->sockfd >= 0)
		close(data->sockfd);
    exit(exit_code);
}

void	send_loop(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		send_recv(data, i);
		i++;
		sleep(1);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	init_data(&data);
	parse_args(argv + 1, &data);
	resolve_targets(&data);
	open_socket(&data);
	setup(&data);
	send_loop(&data);
    free_exit(&data, data.exit_code);
	return (0);
}
