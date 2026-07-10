/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:41:14 by srayees           #+#    #+#             */
/*   Updated: 2026/07/08 15:54:38 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

typedef struct s_env_table
{
	t_env_var			**buckets;
	int					size;
}						t_env_table;

t_env_table				*init_env_table(void);
int						env_set(t_env_table *table, const char *key,
							const char *value);
char					*env_get(t_env_table *table, const char *key);
int						env_unset(t_env_table *table, const char *key);
void					free_env_table(t_env_table *table);
t_env_table				*load_env_from_array(char **envp);
char					**env_table_to_array(t_env_table *table);

char					*get_env_value_from_state(t_shell_state *state,
							const char *key);
int						set_env_value_in_state(t_shell_state *state,
							const char *key, const char *value);
int						unset_env_value_from_state(t_shell_state *state,
							const char *key);
char					**get_env_array_from_state(t_shell_state *state);
void					free_env_array(char **env_array);
void					set_exit_status_in_state(t_shell_state *state,
							int status);
int						get_exit_status_from_state(t_shell_state *state);

int						ft_str_is_numeric(char *str);

char					*expand_variables(char *str, t_shell_state *state);
char					*remove_quotes(const char *str);

void					dig_prompt(void);
void					fill_env_array(t_env_table *table, char **envp);
unsigned int			hash_function(const char *key);
int						count_env_var(t_env_table *table);
char					*expand_single_variable(const char *str, int start,
							int *new_len, t_shell_state *state);
char					*extract_var_name(const char *str, int *len);
char					*expand_variable(const char *var_name,
							t_shell_state *state);
int						env_update(t_env_var *current, const char *value);
t_env_var				*find_env_var(t_env_table *table, const char *key,
							t_env_var **prev);
int						update_existing_var(t_env_var *current,
							const char *value);
t_env_var				*add_new_var(t_env_table *table, const char *key,
							const char *value, unsigned int index);
t_env_var				*create_env_var(const char *key, const char *value);
#endif