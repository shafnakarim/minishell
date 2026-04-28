NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRCS		= main.c \
			main_loop.c \
			parsing.c \
			tokenizer.c \
			tokenizer_helpers.c \
			parser.c \
			quote_utils.c \
			parse_helpers.c \
			cleanup.c \
			execution.c \
			exec_redir.c \
			exec_path.c \
			exec_pipeline.c \
			exec_pipeline_helpers.c \
			builtins.c \
			builtins_basic.c \
			builtins_env.c \
			builtins_export.c \
			builtins_exec.c \
			signals.c \
			environment.c \
			env_utils.c \
			env_array.c \
			env_modify.c \
			utils.c \
			string_utils.c \
			split_utils.c \
			var_utils.c \
			readline_mock.c \
			readline_history.c

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
