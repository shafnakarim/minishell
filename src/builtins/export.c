/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaa-s <jaa-s@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:33:41 by jaa-s             #+#    #+#             */
/*   Updated: 2026/06/16 09:33:45 by jaa-s            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

char	**create_env_copy(char **envp, int count)
{
	char	**sorted_env;
	int		i;

	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sorted_env[i] = envp[i];
		i++;
	}
	sorted_env[count] = NULL;
	return (sorted_env);
}

static void	check(char *sorted, char *eq_pos)
{
	char	*key;

	key = ft_substr(sorted, 0, eq_pos - sorted);
	if (key)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(key, 1);
		free(key);
	}
}

void	print_declare_format(char **sorted_env, int count)
{
	int		i;
	char	*eq_pos;

	i = 0;
	while (i < count)
	{
		if (ft_strncmp(sorted_env[i], "$=", 2) == 0 || ft_strncmp(sorted_env[i],
				"?=", 2) == 0)
		{
			i++;
			continue ;
		}
		eq_pos = ft_strchr(sorted_env[i], '=');
		if (eq_pos && ft_strcmp(eq_pos + 1, "_*_*_") == 0)
			check(sorted_env[i], eq_pos);
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putendl_fd(sorted_env[i], 1);
		}
		free(sorted_env[i]);
		i++;
	}
}

int	validate_export_name(char *name)
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

void	sort_env_array(char **env_array, int count)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strcmp(env_array[j], env_array[j + 1]) > 0)
			{
				temp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
