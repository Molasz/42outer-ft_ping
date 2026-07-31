#include "ft_ping.h"

static void	print_help(void)
{
	printf("\nUsage\n");
	printf("\tping [options] <destination>\n\n");
	printf("Options:\n");
	printf("<destination>      DNS name or IP address\n");
	printf("-v                 verbose output\n");
	printf("-h/?               print help and exit\n");
	exit(0);
}

static void	read_flag(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'v')
			data->v_flag = 1;
		else if (str[i] == '?' || str[i] == 'h')
			print_help();
		else
		{
			fprintf(stderr, "ping: invalid option -- '%c'\n", str[i]);
			fprintf(stderr, "Try './ft_ping -h' for more information.");
			exit(1);
		}
		i++;
	}
}

static void	read_flags(char **argv, t_data *data)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1])
			read_flag(argv[i] + 1, data);
		else if (!data->host)
			data->host = argv[i];
		else
		{
			fprintf(stderr, "ft_ping: only one ip/domain allowed\n");
			exit(1);
		}
		i++;
	}
}

void	parse_args(char **argv, t_data *data)
{
	read_flags(argv, data);
	if (!data->host)
	{
		fprintf(stderr, "ft_ping: missing host operand\n");
		fprintf(stderr, "Try './ft_ping --help' for more information.\n");
		exit(1);
	}
}
