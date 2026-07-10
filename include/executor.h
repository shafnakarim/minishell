/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:03:11 by srayees           #+#    #+#             */
/*   Updated: 2026/07/08 15:51:58 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"

void	execute(t_command *commands, t_shell_state *state);

int		handle_redirections(t_command *cmd);
int		handle_heredoc(char *delimiter, int index);

int		is_builtin(const char *cmd);
int		execute_builtin(t_command *cmd, t_shell_state *state);

void	execute_simple_command(t_command *cmd, t_shell_state *state);
void	execute_external_command(t_command *cmd, t_shell_state *state);
void	execute_pipeline(t_command *commands, t_shell_state *state);
char	*build_command_path(char *dir, char *cmd);
void	free_paths_array(char **paths, int start);

void	wait_for_all_children(t_shell_state *state);
int		launch_child_and_manage_pipe(t_command *cmd, t_shell_state *state,
			int *in_fd, int fd[2]);

char	*get_cmd_path(char **argv, t_shell_state *state);
char	*find_cmd_in_paths(char **paths, char **argv);
int		my_open(char *filename);

#endif