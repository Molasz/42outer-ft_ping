#include "ft_ping.h"

static void	read_flag(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'v')
			data->v_flag = 1;
		else
		{
			fprintf(stderr, "ft_ping: %c: Name or service not known\n", str[i]);
			free_exit(data, 2);
		}
		i++;
	}
}

static int	read_flags(char **argv, t_data *data)
{
	int		i;
	int		args;

	i = 0;
	args = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1])
			read_flag(argv[i] + 1, data);
		else
			args++;
		i++;
	}
	return (args);
}

void	parse_args(char **argv, t_data *data)
{
	read_flags(argv, data);
}
