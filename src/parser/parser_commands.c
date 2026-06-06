/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:13:23 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:13:27 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

int	count_word_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != PIPE && tokens->type != END)
	{
		if (tokens->type == WORD)
			count++;
		else if (tokens->type >= REDIR_IN && tokens->type <= REDIR_HEREDOC)
		{
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				tokens = tokens->next;
			continue ;
		}
		tokens = tokens->next;
	}
	return (count);
}

t_command	*init_command(int argc)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argc = argc;
	if (argc > 0)
	{
		cmd->argv = ft_calloc(argc + 1, sizeof(char *));
		if (!cmd->argv)
		{
			free(cmd);
			return (NULL);
		}
	}
	return (cmd);
}

t_command	*build_simple_command(t_token **current, t_shell_state *state)
{
	t_command	*cmd;
	int			argc;

	if (!current || !*current)
		return (NULL);
	argc = count_word_tokens(*current);
	cmd = init_command(argc);
	if (!cmd)
		return (NULL);
	if (!populate_command_arguments(cmd, current, state))
	{
		free_command(cmd);
		return (NULL);
	}
	return (cmd);
}

int	populate_command_arguments(t_command *cmd, t_token **current,
		t_shell_state *state)
{
	int	i;

	i = 0;
	while (*current && (*current)->type != PIPE && (*current)->type != END)
	{
		if ((*current)->type == WORD)
		{
			if (!process_word_token(cmd, &i, current, state))
				return (0);
		}
		else if ((*current)->type >= REDIR_IN
			&& (*current)->type <= REDIR_HEREDOC)
		{
			if (!add_redirection_to_command(cmd, current, state))
				return (0);
		}
		*current = (*current)->next;
	}
	return (1);
}

int	process_word_token(t_command *cmd, int *i, t_token **current,
		t_shell_state *state)
{
	char	*expanded;
	char	*unquoted;

	if (!(*current)->value)
		expanded = NULL;
	else
		expanded = expand_variables((*current)->value, state);
	if (expanded)
	{
		unquoted = remove_quotes(expanded);
		free(expanded);
		if (unquoted)
			cmd->argv[(*i)++] = unquoted;
		else
			cmd->argv[(*i)++] = ft_strdup((*current)->value);
	}
	else
		cmd->argv[(*i)++] = ft_strdup((*current)->value);
	return (1);
}
