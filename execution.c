/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:40:33 by srayees           #+#    #+#             */
/*   Updated: 2026/04/24 17:40:34 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	execute_command(t_cmd *cmd, t_context *ctx)
{
	char	*path;
	char	**envp;

	if (!cmd || !cmd->args || cmd->arg_count == 0)
		return (0);
	cmd->args[cmd->arg_count] = NULL;
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd, ctx));
	path = find_in_path(cmd->args[0], ctx->env);
	if (!path)
	{
		printf("%s: command not found\n", cmd->args[0]);
		return (127);
	}
	envp = env_to_array(ctx->env);
	if (!envp)
		return (free(path), 1);
	if (execve(path, cmd->args, envp) == -1)
	{
		perror("execve");
		free(path);
		free_split(envp);
		return (127);
	}
	return (0);
}
