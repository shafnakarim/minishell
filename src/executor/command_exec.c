/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaa-s <jaa-s@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:56:03 by jaa-s             #+#    #+#             */
/*   Updated: 2026/06/16 09:56:07 by jaa-s            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <sys/wait.h>

static void	handle_child_process(t_command *cmd, t_shell_state *state)
{
	int	status;

	if (handle_redirections(cmd) == -1)
		exit(1);
	if (!cmd->argv)
	{
		status = 0;
		exit(status);
	}
	execute_external_command(cmd, state);
}

static void	handle_parent_process(pid_t pid, t_shell_state *state)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		set_exit_status_in_state(state, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		set_exit_status_in_state(state, 128 + WTERMSIG(status));
}

static pid_t	create_child_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}

void	execute_simple_command(t_command *cmd, t_shell_state *state)
{
	pid_t	pid;

	pid = create_child_process();
	if (pid == -1)
	{
		set_exit_status_in_state(state, 1);
		return ;
	}
	if (pid == 0)
		handle_child_process(cmd, state);
	else
		handle_parent_process(pid, state);
}

char	*find_cmd_in_paths(char **paths, char **argv)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = build_command_path(paths[i], argv[0]);
		if (cmd_path && access(cmd_path, F_OK | X_OK) == 0)
		{
			free_paths_array(paths, i);
			free(argv[0]);
			argv[0] = cmd_path;
			return (ft_strdup(cmd_path));
		}
		free(cmd_path);
		free(paths[i]);
		i++;
	}
	free(paths);
	return (NULL);
}
