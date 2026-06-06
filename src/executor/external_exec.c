

#include "executor.h"
#include "utils.h"

static void	print_command_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

static char	**get_environment_array(t_shell_state *state)
{
	char	**envp;

	envp = get_env_array_from_state(state);
	return (envp);
}

static void	cleanup_and_exit(char *cmd_path, int exit_code)
{
	if (cmd_path)
		free(cmd_path);
	exit(exit_code);
}

static void	execute_with_path(char *cmd_path, char **argv, char **envp)
{
	execve(cmd_path, argv, envp);
	perror("execve");
}

void	execute_external_command(t_command *cmd, t_shell_state *state)
{
	char	*cmd_path;
	char	**envp;

	cmd_path = get_cmd_path(cmd->argv, state);
	if (!cmd_path)
	{
		print_command_not_found(cmd->argv[0]);
		exit(127);
	}
	envp = get_environment_array(state);
	if (!envp)
		cleanup_and_exit(cmd_path, 1);
	execute_with_path(cmd_path, cmd->argv, envp);
	cleanup_and_exit(cmd_path, 126);
}
