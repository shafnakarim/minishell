/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

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
