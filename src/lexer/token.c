/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:12:32 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:12:34 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_type	get_special_token_type(char c, char next);

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		if (value)
			free(value);
		return (NULL);
	}
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_token(t_tokenizer *tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens || !new_token)
		return ;
	if (!tokens->head)
	{
		tokens->head = new_token;
		return ;
	}
	current = tokens->head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

t_token	*handle_regular_word(t_tokenizer *tokens)
{
	char	*value;
	int		word_start;
	int		word_len;

	if (!tokens || tokens->pos >= tokens->len)
		return (NULL);
	word_start = tokens->pos;
	word_len = get_word_length(tokens);
	if (word_len == 0)
		return (NULL);
	value = ft_substr(tokens->input, word_start, word_len);
	if (!value)
		return (NULL);
	return (create_token(WORD, value));
}

t_token	*handle_special_char(t_tokenizer *tokens)
{
	t_token_type	type;
	char			*value;
	int				len;

	if (!tokens || tokens->pos >= tokens->len)
		return (NULL);
	if (tokens->pos + 1 < tokens->len)
		type = get_special_token_type(tokens->input[tokens->pos],
				tokens->input[tokens->pos + 1]);
	else
		type = get_special_token_type(tokens->input[tokens->pos], '\0');
	if (type == REDIR_HEREDOC || type == REDIR_APPEND)
		len = 2;
	else
		len = 1;
	value = extract_special_token_value(tokens, len);
	if (!value)
		return (NULL);
	return (create_token(type, value));
}

t_tokenizer	*tokenize(t_tokenizer *tokens)
{
	int	result;

	if (!tokens)
		return (NULL);
	while (skip_whitespace(tokens))
	{
		result = process_token(tokens);
		if (result == -1)
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	if (!add_end_token(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}
