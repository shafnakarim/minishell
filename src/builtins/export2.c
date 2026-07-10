/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaa-s <jaa-s@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:33:55 by jaa-s             #+#    #+#             */
/*   Updated: 2026/06/16 09:33:58 by jaa-s            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static void	print_env_sorted(t_shell_state *state)
{
	char	**envp;
	char	**sorted_env;
	int		count;

	envp = get_env_array_from_state(state);
	if (!envp)
		return ;
	count = count_env_vars(envp);
	sorted_env = create_env_copy(envp, count);
	if (!sorted_env)
	{
		free_env_array(envp);
		return ;
	}
	sort_env_array(sorted_env, count);
	print_declare_format(sorted_env, count);
	free(sorted_env);
	free(envp);
}

static char	*extract_key(char *arg, char *eq_pos)
{
	return (ft_substr(arg, 0, eq_pos - arg));
}

static int	export_with_value(t_shell_state *state, char *arg)
{
	char	*eq_pos;
	char	*key;
	char	*value;

	eq_pos = ft_strchr(arg, '=');
	key = extract_key(arg, eq_pos);
	if (!key)
		return (1);
	if (!validate_export_name(key))
	{
		print_export_error(key);
		free(key);
		return (1);
	}
	value = extract_value(eq_pos);
	if (!value)
	{
		free(key);
		return (1);
	}
	set_env_value_in_state(state, key, value);
	free(key);
	free(value);
	return (0);
}

static int	export_without_value(char *arg, t_shell_state *state)
{
	if (!validate_export_name(arg))
	{
		print_export_error(arg);
		return (1);
	}
	set_env_value_in_state(state, arg, "_*_*_");
	return (0);
}

int	ft_export(int argc, char **argv, t_shell_state *state)
{
	int	i;
	int	exit_status;

	if (argc == 1)
	{
		print_env_sorted(state);
		return (0);
	}
	exit_status = 0;
	i = 1;
	while (i < argc)
	{
		if (ft_strchr(argv[i], '='))
		{
			if (export_with_value(state, argv[i]) != 0)
				exit_status = 1;
		}
		else
		{
			if (export_without_value(argv[i], state) != 0)
				exit_status = 1;
		}
		i++;
	}
	return (exit_status);
}
