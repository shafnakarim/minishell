/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

t_cmd	*create_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * 100);
	if (!cmd->args)
		return (free(cmd), NULL);
	cmd->arg_count = 0;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

static int	handle_pipe_token(t_token *tok, t_cmd **cmd,
		t_pipeline *pipeline)
{
	if (*cmd)
		pipeline->cmd_count++;
	*cmd = NULL;
	return (0);
}

static int	handle_word_token(t_token *tok, t_cmd **cmd,
		t_pipeline *pipeline, int *first_word)
{
	t_cmd	*current;

	if (!*cmd)
	{
		*cmd = create_new_cmd();
		if (!*cmd)
			return (1);
		if (*first_word)
		{
			pipeline->commands = *cmd;
			*first_word = 0;
		}
		else
		{
			current = pipeline->commands;
			while (current->next)
				current = current->next;
			current->next = *cmd;
		}
	}
	(*cmd)->args[(*cmd)->arg_count++] = remove_quotes(tok->value);
	return (0);
}

static int	handle_redir_token(t_token *tok, t_cmd *cmd)
{
	t_redir	*redir;

	if (cmd && tok->next && tok->next->type == TOKEN_WORD)
	{
		redir = malloc(sizeof(t_redir));
		if (!redir)
			return (1);
		redir->type = tok->type;
		redir->target = ft_strdup(tok->next->value);
		redir->next = cmd->redirects;
		cmd->redirects = redir;
		return (2);
	}
	return (0);
}

int	process_token(t_token **tok, t_cmd **cmd, t_pipeline *pipeline,
		int *first_word)
{
	int	skip;

	if ((*tok)->type == TOKEN_PIPE)
		handle_pipe_token(*tok, cmd, pipeline);
	else if ((*tok)->type == TOKEN_WORD)
		handle_word_token(*tok, cmd, pipeline, first_word);
	else if ((*tok)->type >= TOKEN_REDIR_IN
		&& (*tok)->type <= TOKEN_REDIR_HEREDOC)
	{
		skip = handle_redir_token(*tok, *cmd);
		if (skip == 2)
			*tok = (*tok)->next;
	}
	return (0);
}
