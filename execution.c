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

static int	handle_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	if (!cmd || !cmd->redirects)
		return (0);
	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
		{
			fd = open(redir->target, O_RDONLY);
			if (fd < 0)
			{
				perror(redir->target);
				return (1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == TOKEN_REDIR_OUT)
		{
			fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(redir->target);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == TOKEN_REDIR_APPEND)
		{
			fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(redir->target);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}

static char	*find_in_path(const char *cmd_name, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;

	if (strchr(cmd_name, '/'))
		if (access(cmd_name, X_OK) == 0)
			return (ft_strdup(cmd_name));
	path_env = get_env_value("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd_name);
		free(temp);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

int	execute_pipeline(t_pipeline *pipeline, t_context *ctx)
{
	pid_t	*pids;
	int		i;
	int		status;
	int		pipe_fd[2];
	t_cmd	*cmd;

	if (!pipeline || !pipeline->commands)
		return (0);
	pids = malloc(sizeof(pid_t) * pipeline->cmd_count);
	if (!pids)
		return (1);
	cmd = pipeline->commands;
	i = 0;
	while (cmd)
	{
		if (is_builtin(cmd->args[0]) && !cmd->next)
		{
			status = execute_builtin(cmd, ctx);
			free(pids);
			return (status);
		}
		if (cmd->next && pipe(pipe_fd) == -1)
			return (free(pids), 1);
		pids[i] = fork();
		if (pids[i] == -1)
			return (free(pids), 1);
		if (pids[i] == 0)
		{
			if (cmd->next)
				dup2(pipe_fd[1], STDOUT_FILENO);
			if (cmd->next)
				close(pipe_fd[0]);
			if (cmd->next)
				close(pipe_fd[1]);
			if (handle_redirections(cmd))
				exit(1);
			execute_command(cmd, ctx);
			exit(0);
		}
		if (cmd->next)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
		}
		cmd = cmd->next;
		i++;
	}
	i = 0;
	while (i < pipeline->cmd_count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	free(pids);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

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
