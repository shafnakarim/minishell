/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

static void	skip_quoted_string(const char *input, int *i)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
		(*i)++;
}

static void	advance_word_pointer(const char *input, int *i)
{
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'' || input[*i] == '"')
			skip_quoted_string(input, i);
		else
			(*i)++;
	}
}

static void	handle_operator_tokens(const char *input, int *i, t_token **head)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(head, new_token(TOKEN_REDIR_HEREDOC, "<<"));
		*i += 2;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(head, new_token(TOKEN_REDIR_APPEND, ">>"));
		*i += 2;
	}
	else if (input[*i] == '<')
	{
		add_token(head, new_token(TOKEN_REDIR_IN, "<"));
		(*i)++;
	}
	else if (input[*i] == '>')
	{
		add_token(head, new_token(TOKEN_REDIR_OUT, ">"));
		(*i)++;
	}
}

void	process_token_char(const char *input, int *i, t_token **head)
{
	char	*word;

	while (ft_isspace(input[*i]))
		(*i)++;
	if (!input[*i])
		return ;
	if (input[*i] == '|')
	{
		add_token(head, new_token(TOKEN_PIPE, "|"));
		(*i)++;
	}
	else if (input[*i] == '<' || input[*i] == '>')
		handle_operator_tokens(input, i, head);
	else
	{
		word = extract_word(input, i);
		if (word)
		{
			add_token(head, new_token(TOKEN_WORD, word));
			free(word);
		}
	}
}

char	*extract_word(const char *input, int *i)
{
	char	*word;
	int		start;
	int		len;

	start = *i;
	advance_word_pointer(input, i);
	len = *i - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, input + start, len + 1);
	return (word);
}
