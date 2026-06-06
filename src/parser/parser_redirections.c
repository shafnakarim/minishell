/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:14:05 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:14:07 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_in_redir	*create_in_redirection(t_token **current)
{
	t_in_redir	*redir;

	redir = malloc(sizeof(t_in_redir));
	if (!redir)
		return (NULL);
	if ((*current)->type == REDIR_IN)
		redir->in_mode = 0;
	else
		redir->in_mode = 1;
	redir->delimeter = NULL;
	redir->in_file = NULL;
	redir->next = NULL;
	*current = (*current)->next;
	if (!*current || (*current)->type != WORD)
	{
		print_syntax_error("syntax error near unexpected token 'newline'");
		free(redir);
		return (NULL);
	}
	return (redir);
}

t_in_redir	*handle_in_redirection(t_token **current)
{
	t_in_redir	*redir;

	redir = create_in_redirection(current);
	if (!redir)
		return (NULL);
	if (redir->in_mode == 1)
		redir->delimeter = ft_strdup((*current)->value);
	else
		redir->in_file = ft_strdup((*current)->value);
	if ((redir->in_mode == 1 && !redir->delimeter) || (redir->in_mode == 0
			&& !redir->in_file))
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

t_out_redir	*handle_out_redirection(t_token **current)
{
	t_out_redir	*redir;

	redir = malloc(sizeof(t_out_redir));
	if (!redir)
		return (NULL);
	if ((*current)->type == REDIR_OUT)
		redir->out_mode = 0;
	else
		redir->out_mode = 1;
	redir->out_file = NULL;
	redir->next = NULL;
	*current = (*current)->next;
	if (!*current || (*current)->type != WORD)
	{
		print_syntax_error("syntax error near unexpected token 'newline'");
		free(redir);
		return (NULL);
	}
	redir->out_file = ft_strdup((*current)->value);
	if (!redir->out_file)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

int	handle_in_redirection_command(t_command *cmd, t_token **current)
{
	t_in_redir	*in_redir;
	t_in_redir	*in_last;

	in_redir = handle_in_redirection(current);
	if (!in_redir)
		return (0);
	if (!cmd->in_redir)
		cmd->in_redir = in_redir;
	else
	{
		in_last = cmd->in_redir;
		while (in_last->next)
			in_last = in_last->next;
		in_last->next = in_redir;
	}
	return (1);
}

int	handle_out_redirection_command(t_command *cmd, t_token **current)
{
	t_out_redir	*out_redir;
	t_out_redir	*out_last;

	out_redir = handle_out_redirection(current);
	if (!out_redir)
		return (0);
	if (!cmd->out_redir)
		cmd->out_redir = out_redir;
	else
	{
		out_last = cmd->out_redir;
		while (out_last->next)
			out_last = out_last->next;
		out_last->next = out_redir;
	}
	return (1);
}
