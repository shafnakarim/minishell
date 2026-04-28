/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:47:55 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 14:02:34 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

char				*readline(const char *prompt);
void				add_history(char *line);
void				rl_clear_history(void);
void				rl_on_new_line(void);
void				rl_replace_line(const char *text, int clear_undo);
void				rl_redisplay(void);

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	int				arg_count;
	t_redir			*redirects;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipeline
{
	t_cmd			*commands;
	int				cmd_count;
}					t_pipeline;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_context
{
	t_env			*env;
	int				last_exit_status;
}					t_context;

t_token				*tokenize(const char *input);
void				free_tokens(t_token *tokens);
t_pipeline			*parse_tokens(t_token *tokens);
void				free_pipeline(t_pipeline *pipeline);

int					execute_pipeline(t_pipeline *pipeline, t_context *ctx);
int					execute_command(t_cmd *cmd, t_context *ctx);

int					builtin_echo(char **args, int arg_count);
int					builtin_cd(char **args, int arg_count, t_context *ctx);
int					builtin_pwd(void);
int					builtin_export(char **args, int arg_count, t_context *ctx);
int					builtin_unset(char **args, int arg_count, t_context *ctx);
int					builtin_env(t_env *env);
int					builtin_exit(char **args, int arg_count);
int					is_builtin(const char *cmd);
int					execute_builtin(t_cmd *cmd, t_context *ctx);

t_env				*init_env(char **envp);
char				*get_env_value(const char *key, t_env *env);
void				set_env_value(const char *key, const char *value,
						t_env **env);
void				unset_env_value(const char *key, t_env **env);
void				free_env(t_env *env);
char				**env_to_array(t_env *env);

void				setup_signals(void);

char				*ft_strdup(const char *s);
char				*ft_strjoin(const char *s1, const char *s2);
int					ft_strlen(const char *s);
char				**ft_split(const char *s, char c);
void				free_split(char **split);
int					ft_strcmp(const char *s1, const char *s2);
char				*expand_variable(const char *var_name, t_context *ctx);
int					ft_isspace(int c);
void    			run_shell(t_context *ctx);
void    			process_token_char(const char *input, int *i, t_token **head);
#endif