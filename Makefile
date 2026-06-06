NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE)
LIBFT_DIR = libft
INCLUDE = include
READLINE_DIR = include/mac
LIBFT = $(LIBFT_DIR)/libft.a
READLINE = $(READLINE_DIR)/libreadline.a
HISTORY = $(READLINE_DIR)/libhistory.a

# Source directories
LEXER_DIR = src/lexer
PARSER_DIR = src/parser
EXECUTOR_DIR = src/executor
BUILTINS_DIR = src/builtins
UTILS_DIR = src/utils
OBJ_DIR = obj

# Source files
LEXER_SRCS = $(LEXER_DIR)/lexer.c $(LEXER_DIR)/lexer_init.c $(LEXER_DIR)/token.c \
			$(LEXER_DIR)/token_utils.c $(LEXER_DIR)/quote_handler.c

PARSER_SRCS = $(PARSER_DIR)/parser_main.c $(PARSER_DIR)/parser_commands.c \
			$(PARSER_DIR)/parser_redirections.c $(PARSER_DIR)/parser_pipeline.c \
			$(PARSER_DIR)/parser_memory.c $(PARSER_DIR)/error.c

EXECUTOR_SRCS = $(EXECUTOR_DIR)/executor_main.c $(EXECUTOR_DIR)/heredoc.c \
				$(EXECUTOR_DIR)/redirections.c $(EXECUTOR_DIR)/builtin_check.c \
				$(EXECUTOR_DIR)/builtin_exec.c $(EXECUTOR_DIR)/path_resolver.c \
				$(EXECUTOR_DIR)/command_exec.c $(EXECUTOR_DIR)/external_exec.c \
				$(EXECUTOR_DIR)/pipeline.c $(EXECUTOR_DIR)/pipeline_util.c

BUILTINS_SRCS = $(BUILTINS_DIR)/ft_echo.c $(BUILTINS_DIR)/ft_cd.c $(BUILTINS_DIR)/ft_pwd.c \
				 $(BUILTINS_DIR)/ft_unset.c $(BUILTINS_DIR)/ft_env.c \
				$(BUILTINS_DIR)/ft_exit.c $(BUILTINS_DIR)/builtin_utils.c $(BUILTINS_DIR)/export2.c $(BUILTINS_DIR)/export.c

UTILS_SRCS = $(UTILS_DIR)/utils.c $(UTILS_DIR)/signals.c\
			$(UTILS_DIR)/env_hash.c $(UTILS_DIR)/env_manager.c $(UTILS_DIR)/expansion.c\
			$(UTILS_DIR)/utils2.c $(UTILS_DIR)/env_utils.c $(UTILS_DIR)/expan_utils.c

ALL_SRCS = main.c $(LEXER_SRCS) $(PARSER_SRCS) $(EXECUTOR_SRCS) $(BUILTINS_SRCS) $(UTILS_SRCS)

# Object files
OBJS = $(ALL_SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  -lcurses $(HISTORY) $(READLINE) $(LIBFT) -o $(NAME)

# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -lncurses -lreadline -lhistory $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
