/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	setup_child_pipes(int *pipe_fd, int has_next)
{
	if (has_next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	setup_parent_pipes(int *pipe_fd, int has_next)
{
	if (has_next)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

int	handle_builtin_single(t_cmd *cmd, t_context *ctx)
{
	if (is_builtin(cmd->args[0]) && !cmd->next)
		return (execute_builtin(cmd, ctx));
	return (-1);
}

void	wait_children(pid_t *pids, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
}

int	fork_command(pid_t *pid, t_cmd *cmd, int *pipe_fd, t_context *ctx)
{
	if (cmd->next && pipe(pipe_fd) == -1)
		return (1);
	*pid = fork();
	if (*pid == -1)
		return (1);
	if (*pid == 0)
	{
		setup_child_pipes(pipe_fd, cmd->next != NULL);
		if (handle_redirections(cmd))
			exit(1);
		execute_command(cmd, ctx);
		exit(0);
	}
	return (0);
}
