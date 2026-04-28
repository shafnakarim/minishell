/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

static int	process_command_loop(t_pipeline *pipeline, t_context *ctx,
		pid_t *pids)
{
	int		i;
	int		pipe_fd[2];
	t_cmd	*cmd;
	int		result;

	cmd = pipeline->commands;
	i = 0;
	while (cmd)
	{
		result = handle_builtin_single(cmd, ctx);
		if (result >= 0)
			return (result);
		if (fork_command(&pids[i], cmd, pipe_fd, ctx))
			return (-1);
		setup_parent_pipes(pipe_fd, cmd->next != NULL);
		cmd = cmd->next;
		i++;
	}
	return (-2);
}

int	execute_pipeline(t_pipeline *pipeline, t_context *ctx)
{
	pid_t	*pids;
	int		result;

	if (!pipeline || !pipeline->commands)
		return (0);
	pids = malloc(sizeof(pid_t) * pipeline->cmd_count);
	if (!pids)
		return (1);
	result = process_command_loop(pipeline, ctx, pids);
	if (result >= 0)
		return (free(pids), result);
	if (result == -1)
		return (free(pids), 1);
	wait_children(pids, pipeline->cmd_count);
	free(pids);
	return (0);
}
