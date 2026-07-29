NAME		= ft_ping

SRCS		= ft_ping.c \
				parse_args.c \
				resolve_target.c \
				socket.c \
				setup.c \
				stats.c \
				packet.c \
				send.c

OBJS		= $(addprefix $(ODIR), $(SRCS:.c=.o))

SDIR		= src/

ODIR		= obj/

IDIR		= includes/

DEPS		= $(addprefix $(ODIR), $(SRCS:.c=.d))

CFLAGS		= -Wall -Wextra -Werror -MMD -Iincludes/ 

AR			= ar rcs

RM			= rm -rf

all:		dir ${NAME}

dir:
				mkdir -p $(ODIR)

obj/%.o:	src/%.c Makefile
				$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lm 

bonus:		all

clean:
				$(RM) $(ODIR)

fclean:		
				$(RM) $(ODIR)
				$(RM) $(NAME)

re:			fclean all

-include ${DEPS}

.PHONY:		clean fclean re all dir
