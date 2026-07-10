/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:12:19 by srayees           #+#    #+#             */
/*   Updated: 2026/07/03 15:10:13 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	skip_whitespace(t_tokenizer *tokens)
{
	while (tokens->pos < tokens->len && ft_isspace(tokens->input[tokens->pos]))
		tokens->pos++;
	return (tokens->pos < tokens->len);
}

int	is_quote_char(char c)
{
	return (c == '\'' || c == '"');
}

int	is_wrd_char(char c)
{
	return (!ft_isspace(c) && !is_special_char(c));
}
