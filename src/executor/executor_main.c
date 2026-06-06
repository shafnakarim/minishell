

#include "executor.h"
#include "utils.h"

static int	is_single_command(t_command *commands)
{
	if (commands && !commands->next)
		return (1);
	return (0);
}

static void	handle_single_builtin(t_command *commands, t_shell_state *state)
{
	int	status;

	if (handle_redirections(commands) == -1)
	{
		set_exit_status_in_state(state, 1);
		return ;
	}
	status = execute_builtin(commands, state);
	dup2(STDIN_FILENO, STDOUT_FILENO);
	set_exit_status_in_state(state, status);
}

static int	is_single_builtin_command(t_command *commands)
{
	if (is_single_command(commands) && commands->argv
		&& is_builtin(commands->argv[0]))
		return (1);
	return (0);
}

void	execute(t_command *commands, t_shell_state *state)
{
	if (!commands)
		return ;
	if (is_single_builtin_command(commands))
	{
		handle_single_builtin(commands, state);
		return ;
	}
	execute_pipeline(commands, state);
}
