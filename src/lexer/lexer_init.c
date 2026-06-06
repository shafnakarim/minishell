/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:11:35 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:11:39 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tokenizer	*init_tokenizer(char *input)
{
	t_tokenizer	*tokenizer;

	tokenizer = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	if (!tokenizer)
		return (NULL);
	tokenizer->input = input;
	tokenizer->pos = 0;
	tokenizer->len = ft_strlen(input);
	tokenizer->head = NULL;
	tokenizer->error = 0;
	return (tokenizer);
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == ';' || c == '&' || c == '('
		|| c == ')');
}

int	handle_single_quote(t_tokenizer *tokens, int start)
{
	int	end;

	end = start + 1;
	while (end < tokens->len && tokens->input[end] != '\'')
		end++;
	if (end >= tokens->len || tokens->input[end] != '\'')
	{
		print_syntax_error("unclosed single quote");
		return (-1);
	}
	return (end);
}

int	handle_double_quote(t_tokenizer *tokens, int start)
{
	int	end;

	end = start + 1;
	while (end < tokens->len && tokens->input[end] != '"')
	{
		if (tokens->input[end] == '\\' && end + 1 < tokens->len)
			end += 2;
		else
			end++;
	}
	if (end >= tokens->len || tokens->input[end] != '"')
	{
		print_syntax_error("unclosed double quote");
		return (-1);
	}
	return (end);
}

void	free_tokens(t_tokenizer *tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens)
		return ;
	current = tokens->head;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	tokens->head = NULL;
}
