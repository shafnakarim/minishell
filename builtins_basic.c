/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_basic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	builtin_exit(char **args, int arg_count)
{
	int	exit_code;

	exit_code = 0;
	if (arg_count > 0)
		exit_code = atoi(args[0]);
	exit(exit_code);
	return (0);
}
