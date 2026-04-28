/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	g_signal = 0;

static void	print_prompt(void)
{
	printf("minishell$ ");
	fflush(stdout);
}

static int	process_input(const char *input, t_context *ctx)
{
	t_token		*tokens;
	t_pipeline	*pipeline;
	int			status;

	if (!input || !*input)
		return (0);
	tokens = tokenize(input);
	if (!tokens)
		return (0);
	pipeline = parse_tokens(tokens);
	free_tokens(tokens);
	if (!pipeline)
		return (0);
	status = execute_pipeline(pipeline, ctx);
	free_pipeline(pipeline);
	ctx->last_exit_status = status;
	return (status);
}

void	run_shell(t_context *ctx)
{
	char	*input;

	setup_signals();
	while (1)
	{
		g_signal = 0;
		print_prompt();
		input = readline("");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		process_input(input, ctx);
		free(input);
	}
}
