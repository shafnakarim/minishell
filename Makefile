NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRCS		= main.c \
			parsing.c \
			execution.c \
			builtins.c \
			signals.c \
			environment.c \
			utils.c \
			readline_mock.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
