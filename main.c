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

int	main(int argc, char **argv, char **envp)
{
	t_context	ctx;
	char		*input;

	(void)argc;
	(void)argv;
	ctx.env = init_env(envp);
	ctx.last_exit_status = 0;
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
		process_input(input, &ctx);
		free(input);
	}
	free_env(ctx.env);
	rl_clear_history();
	return (ctx.last_exit_status);
}
