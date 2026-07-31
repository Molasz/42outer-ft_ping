#ifndef FT_PING_H
# define FT_PING_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <math.h>
# include <netinet/ip_icmp.h>
# include <sys/time.h>
# include <netinet/ip.h>

# define PACKET_SIZE 64
# define DATA_SIZE 56
# define TIMEOUT_SEC 1

typedef struct s_data
{
	char				*host;
	int					v_flag;
	struct sockaddr_in	dest_addr;
	char				dest_ip_str[INET_ADDRSTRLEN];
	int					sockfd;
	int					sent;
	int					received;
	double				rtt_min;
	double				rtt_max;
	double				rtt_sum;
	double				rtt_sum2;
}	t_data;

void	free_exit(t_data *data, int exit_code);
void	parse_args(char **argv, t_data *data);
void	resolve_targets(t_data *data);
void	setup(t_data *data);
void	build_packet(char *packet, int seq);
void	send_recv(t_data *data, int seq);

#endif
