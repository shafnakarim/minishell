/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

static int	apply_input_redir(const char *target)
{
	int	fd;

	fd = open(target, O_RDONLY);
	if (fd < 0)
	{
		perror(target);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	apply_output_redir(const char *target, int flags)
{
	int	fd;

	fd = open(target, flags, 0644);
	if (fd < 0)
	{
		perror(target);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	apply_single_redirect(t_redir *redir)
{
	int	flags;

	if (redir->type == TOKEN_REDIR_IN)
		return (apply_input_redir(redir->target));
	else if (redir->type == TOKEN_REDIR_OUT)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		return (apply_output_redir(redir->target, flags));
	}
	else if (redir->type == TOKEN_REDIR_APPEND)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		return (apply_output_redir(redir->target, flags));
	}
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	t_redir	*redir;

	if (!cmd || !cmd->redirects)
		return (0);
	redir = cmd->redirects;
	while (redir)
	{
		if (apply_single_redirect(redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}
