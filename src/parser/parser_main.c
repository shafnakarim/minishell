/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:13:37 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:13:39 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command	*parse_command(char *input, t_shell_state *state)
{
	t_tokenizer	*tokenizer;
	t_command	*commands;

	if (!input || !*input)
		return (NULL);
	tokenizer = init_tokenizer(input);
	if (!tokenizer)
		return (NULL);
	tokenizer = tokenize(tokenizer);
	free(input);
	if (!tokenizer)
		return (NULL);
	commands = build_commands(tokenizer, state);
	free_tokens(tokenizer);
	free(tokenizer);
	return (commands);
}
