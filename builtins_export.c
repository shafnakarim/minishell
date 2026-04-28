/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

static void	print_env_var(const char *key, const char *value)
{
	printf("declare -x %s\"%s\"\n", key, value);
}

static int	export_single_var(const char *arg, t_context *ctx)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = strchr(arg, '=');
	if (eq)
	{
		key = malloc(eq - arg + 1);
		if (!key)
			return (1);
		strncpy(key, arg, eq - arg);
		key[eq - arg] = '\0';
		value = eq + 1;
		set_env_value(key, value, &ctx->env);
		free(key);
	}
	return (0);
}

int	builtin_export(char **args, int arg_count, t_context *ctx)
{
	int		i;
	t_env	*current;

	if (arg_count == 0)
	{
		current = ctx->env;
		while (current)
		{
			print_env_var(current->key, current->value);
			current = current->next;
		}
		return (0);
	}
	i = 0;
	while (i < arg_count)
	{
		if (export_single_var(args[i], ctx))
			return (1);
		i++;
	}
	return (0);
}
