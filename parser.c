/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/26 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

t_pipeline	*parse_tokens(t_token *tokens)
{
	t_pipeline	*pipeline;
	t_cmd		*cmd;
	t_token		*tok;
	int			first_word;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->commands = NULL;
	pipeline->cmd_count = 0;
	cmd = NULL;
	tok = tokens;
	first_word = 1;
	while (tok)
	{
		process_token(&tok, &cmd, pipeline, &first_word);
		tok = tok->next;
	}
	if (cmd && pipeline->commands)
		pipeline->cmd_count++;
	return (pipeline);
}
