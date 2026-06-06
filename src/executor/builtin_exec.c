

#include "builtins.h"
#include "executor.h"
#include "utils.h"

static int	execute_echo_builtin(t_command *cmd)
{
	return (ft_echo(cmd->argc, cmd->argv));
}

static int	execute_filesystem_builtin(t_command *cmd, t_shell_state *state)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (ft_cd(cmd->argc, cmd->argv, state));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd());
	return (-1);
}

static int	execute_env_builtin(t_command *cmd, t_shell_state *state)
{
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_export(cmd->argc, cmd->argv, state));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_unset(cmd->argc, cmd->argv, state));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(state));
	return (-1);
}

static int	execute_exit_builtin(t_command *cmd, t_shell_state *state)
{
	return (ft_exit(cmd->argc, cmd->argv, state));
}

int	execute_builtin(t_command *cmd, t_shell_state *state)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (execute_echo_builtin(cmd));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (execute_filesystem_builtin(cmd, state));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (execute_filesystem_builtin(cmd, state));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (execute_env_builtin(cmd, state));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (execute_env_builtin(cmd, state));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (execute_env_builtin(cmd, state));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		exit_status = execute_exit_builtin(cmd, state);
		cleanup_shell_state(state);
		free_commands(cmd);
		exit(exit_status);
	}
	return (-1);
}
