/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:16:42 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:16:45 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		ft_echo(int argc, char **argv);
int		ft_cd(int argc, char **argv, t_shell_state *state);
int		ft_pwd(void);
int		ft_export(int argc, char **argv, t_shell_state *state);
int		ft_unset(int argc, char **argv, t_shell_state *state);
int		ft_env(t_shell_state *state);
int		ft_exit(int argc, char **argv, t_shell_state *state);
void	print_cd_error(char *target);
void	print_export_error(char *name);
void	print_declare_format(char **sorted_env, int count);
int		validate_export_name(char *name);
char	**create_env_copy(char **envp, int count);
void	sort_env_array(char **env_array, int count);
char	*extract_value(char *eq_pos);
int		count_env_vars(char **envp);
#endif