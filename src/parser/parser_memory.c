/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:13:46 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:13:48 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static void	free_in_redirections(t_in_redir *redir)
{
	t_in_redir	*next;

	while (redir)
	{
		next = redir->next;
		if (redir->delimeter)
			free(redir->delimeter);
		if (redir->in_file)
			free(redir->in_file);
		free(redir);
		redir = next;
	}
}

static void	free_out_redirections(t_out_redir *redir)
{
	t_out_redir	*next;

	while (redir)
	{
		next = redir->next;
		if (redir->out_file)
			free(redir->out_file);
		free(redir);
		redir = next;
	}
}

void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	free_in_redirections(cmd->in_redir);
	free_out_redirections(cmd->out_redir);
	free(cmd);
}

void	free_commands(t_command *commands)
{
	t_command	*next;

	while (commands)
	{
		next = commands->next;
		free_command(commands);
		commands = next;
	}
}

int	add_redirection_to_command(t_command *cmd, t_token **current,
		t_shell_state *state)
{
	char	*expanded;
	char	*unquoted;

	if ((*current)->next && (*current)->next->value != NULL)
	{
		expanded = expand_variables((*current)->next->value, state);
		if (expanded)
		{
			unquoted = remove_quotes(expanded);
			free(expanded);
			if (unquoted)
			{
				free((*current)->next->value);
				(*current)->next->value = unquoted;
			}
		}
	}
	if ((*current)->type == REDIR_IN || (*current)->type == REDIR_HEREDOC)
		return (handle_in_redirection_command(cmd, current));
	else if ((*current)->type == REDIR_OUT || (*current)->type == REDIR_APPEND)
		return (handle_out_redirection_command(cmd, current));
	return (1);
}
