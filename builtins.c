#include "minishel.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_context *ctx)
{
	if (!cmd || !cmd->args || cmd->arg_count == 0)
		return (0);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd->args + 1, cmd->arg_count - 1));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd->args + 1, cmd->arg_count - 1, ctx));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd->args + 1, cmd->arg_count - 1, ctx));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd->args + 1, cmd->arg_count - 1, ctx));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(ctx->env));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(cmd->args + 1, cmd->arg_count - 1));
	return (0);
}

int	builtin_echo(char **args, int arg_count)
{
	int	i;
	int	newline;

	newline = 1;
	i = 0;
	if (arg_count > 0 && ft_strcmp(args[0], "-n") == 0)
	{
		newline = 0;
		i = 1;
	}
	while (i < arg_count)
	{
		printf("%s", args[i]);
		if (i < arg_count - 1)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	builtin_cd(char **args, int arg_count, t_context *ctx)
{
	char	*path;
	char	buffer[4096];
	char	*home;

	if (arg_count == 0)
	{
		home = get_env_value("HOME", ctx->env);
		if (!home)
			return (0);
		path = home;
	}
	else
		path = args[0];
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(buffer, sizeof(buffer)))
		set_env_value("PWD", buffer, &ctx->env);
	return (0);
}

int	builtin_pwd(void)
{
	char	buffer[4096];

	if (getcwd(buffer, sizeof(buffer)))
	{
		printf("%s\n", buffer);
		return (0);
	}
	perror("pwd");
	return (1);
}

int	builtin_export(char **args, int arg_count, t_context *ctx)
{
	int		i;
	char	*eq;
	char	*key;
	char	*value;
	t_env	*current;

	if (arg_count == 0)
	{
		current = ctx->env;
		while (current)
		{
			printf("declare -x %s\"%s\"\n", current->key, current->value);
			current = current->next;
		}
		return (0);
	}
	i = 0;
	while (i < arg_count)
	{
		eq = strchr(args[i], '=');
		if (eq)
		{
			key = malloc(eq - args[i] + 1);
			if (!key)
				return (1);
			strncpy(key, args[i], eq - args[i]);
			key[eq - args[i]] = '\0';
			value = eq + 1;
			set_env_value(key, value, &ctx->env);
			free(key);
		}
		i++;
	}
	return (0);
}

int	builtin_unset(char **args, int arg_count, t_context *ctx)
{
	int	i;

	i = 0;
	while (i < arg_count)
	{
		unset_env_value(args[i], &ctx->env);
		i++;
	}
	return (0);
}

int	builtin_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

int	builtin_exit(char **args, int arg_count)
{
	int	exit_code;

	exit_code = 0;
	if (arg_count > 0)
		exit_code = atoi(args[0]);
	exit(exit_code);
	return (0);
}
