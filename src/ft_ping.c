#include "ft_ping.h"

static void	init_data(t_data *data)
{
    data->v_flag = 0;
	data->exit_code = 0;
}

void free_exit(t_data *data, int exit_code)
{
    (void) data;
    exit(exit_code);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	init_data(&data);
	parse_args(argv + 1, &data);
    free_exit(&data, data.exit_code);
	return (0);
}
