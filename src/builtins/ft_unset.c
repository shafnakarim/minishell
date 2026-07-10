/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaa-s <jaa-s@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:53:16 by jaa-s             #+#    #+#             */
/*   Updated: 2026/06/16 09:53:20 by jaa-s            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static int	validate_variable_name(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_unset_error(char *name)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	unset_single_var(t_shell_state *state, char *name)
{
	if (!validate_variable_name(name))
	{
		print_unset_error(name);
		return (1);
	}
	unset_env_value_from_state(state, name);
	return (0);
}

int	ft_unset(int argc, char **argv, t_shell_state *state)
{
	int	i;
	int	exit_status;

	if (argc < 2)
		return (0);
	exit_status = 0;
	i = 1;
	while (i < argc)
	{
		if (unset_single_var(state, argv[i]) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
