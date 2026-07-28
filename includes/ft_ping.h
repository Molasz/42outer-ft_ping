#ifndef FT_PING_H
# define FT_PING_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_data
{
	int	v_flag;
	int	exit_code;
}	t_data;

void free_exit(t_data *data, int exit_code);

// parse_args
void	parse_args(char **argv, t_data *data);

#endif
