/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:12:06 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:12:08 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*create_token(t_token_type type, char *value);

char	*extract_quoted_content(t_tokenizer *tokens, int start, int end)
{
	char	*content;
	int		len;

	len = end - start;
	content = ft_substr(tokens->input, start, len - 1);
	return (content);
}

static t_token	*create_quoted_token(t_tokenizer *tokens, int start, int end)
{
	char	*content;

	content = extract_quoted_content(tokens, start, end + 1);
	if (!content)
		return (NULL);
	return (create_token(WORD, content));
}

int	process_quotes(t_tokenizer *tokens, int start)
{
	int	end;
	int	quote_end;

	end = start;
	while (end < tokens->len && !ft_isspace(tokens->input[end])
		&& !is_operator(tokens->input[end]))
	{
		if (tokens->input[end] == '\'')
		{
			quote_end = handle_single_quote(tokens, end);
			if (quote_end == -1)
				return (-1);
			end = quote_end;
		}
		else if (tokens->input[end] == '"')
		{
			quote_end = handle_double_quote(tokens, end);
			if (quote_end == -1)
				return (-1);
			end = quote_end;
		}
		end++;
	}
	return (end);
}

int	finalize_quote_token(t_tokenizer *tokens, int start, int end)
{
	t_token	*token;

	token = create_quoted_token(tokens, start, end);
	if (!token)
		return (0);
	add_token(tokens, token);
	return (1);
}

int	handle_quotes(t_tokenizer *tokens)
{
	int	start;
	int	end;

	if (!tokens || tokens->pos >= tokens->len)
		return (-1);
	start = tokens->pos;
	end = process_quotes(tokens, start);
	if (end == -1)
		return (-1);
	if (!finalize_quote_token(tokens, start, end))
		return (-1);
	tokens->pos = end;
	return (1);
}
