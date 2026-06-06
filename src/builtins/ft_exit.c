

#include "builtins.h"
#include "utils.h"

static void	exit_with_status(t_shell_state *state, int status)
{
	set_exit_status_in_state(state, status);
}

static void	exit_numeric_error(t_shell_state *state)
{
	ft_putstr_fd("exit: numeric argument required\n", 2);
	exit_with_status(state, 255);
}

static void	exit_too_many_args(void)
{
	ft_putstr_fd("exit: too many arguments\n", 2);
}

static int	handle_numeric_argument(char *arg, t_shell_state *state)
{
	int	exit_code;

	exit_code = ft_str_is_numeric(arg);
	if (exit_code == 0)
	{
		exit_numeric_error(state);
	}
	else
	{
		exit_with_status(state, exit_code);
	}
	return (exit_code);
}

int	ft_exit(int argc, char **argv, t_shell_state *state)
{
	if (argc > 2)
	{
		exit_too_many_args();
		return (1);
	}
	if (argc == 2)
		return (handle_numeric_argument(argv[1], state));
	exit_with_status(state, 0);
	return (0);
}
