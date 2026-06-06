

#include "builtins.h"
#include "executor.h"
#include "utils.h"

static int	is_echo_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	return (0);
}

static int	is_filesystem_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	return (0);
}

static int	is_env_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

static int	is_exit_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (is_echo_builtin(cmd))
		return (1);
	if (is_filesystem_builtin(cmd))
		return (1);
	if (is_env_builtin(cmd))
		return (1);
	if (is_exit_builtin(cmd))
		return (1);
	return (0);
}
