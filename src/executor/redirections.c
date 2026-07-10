/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaa-s <jaa-s@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:59:54 by jaa-s             #+#    #+#             */
/*   Updated: 2026/06/16 09:59:58 by jaa-s            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <fcntl.h>

int	my_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}

int	my_open(char *filename)
{
	int	fd;

	if (!filename)
		return (-1);
	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", filename, strerror(errno));
	}
	return (fd);
}

static int	process_input_redirection(t_in_redir *in)
{
	if (!in)
		return (0);
	while (in)
	{
		if (in->in_mode == 0)
			in->in_fd = my_open(in->in_file);
		else if (in->in_mode == 1)
			in->in_fd = handle_heredoc(in->delimeter, 0);
		else
			in->in_fd = STDIN_FILENO;
		if (in->in_fd < 0)
			return (-1);
		if (in->next == NULL)
			break ;
		close(in->in_fd);
		in = in->next;
	}
	if (my_dup2(in->in_fd, STDIN_FILENO) != 0)
		return (-1);
	return (0);
}

static int	process_output_redirection(t_out_redir *out)
{
	if (!out)
		return (0);
	while (out)
	{
		if (out->out_mode == 0)
			out->out_fd = open(out->out_file, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else if (out->out_mode == 1)
			out->out_fd = open(out->out_file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			out->out_fd = STDOUT_FILENO;
		if (out->out_fd < 0)
			return (perror("open"), -1);
		if (out->next == NULL)
			break ;
		close(out->out_fd);
		out = out->next;
	}
	if (my_dup2(out->out_fd, STDOUT_FILENO) != 0)
		return (-1);
	return (0);
}

int	handle_redirections(t_command *cmd)
{
	t_out_redir	*out;
	t_in_redir	*in;

	if (!cmd)
		return (-1);
	out = cmd->out_redir;
	in = cmd->in_redir;
	if (process_input_redirection(in) < 0)
		return (-1);
	if (process_output_redirection(out) < 0)
		return (-1);
	return (0);
}
