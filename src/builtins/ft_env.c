/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaa-s <jaa-s@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:52:52 by jaa-s             #+#    #+#             */
/*   Updated: 2026/06/16 09:53:36 by jaa-s            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static void	print_env_array(char **envp)
{
	int		i;
	char	*eq_pos;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "$=", 2) == 0 || ft_strncmp(envp[i], "?=",
				2) == 0)
		{
			i++;
			continue ;
		}
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos && ft_strcmp(eq_pos + 1, "_*_*_") == 0)
		{
			i++;
			continue ;
		}
		ft_putendl_fd(envp[i], 1);
		i++;
	}
}

int	ft_env(t_shell_state *state)
{
	char	**envp;

	envp = get_env_array_from_state(state);
	if (!envp)
		return (1);
	print_env_array(envp);
	free_env_array(envp);
	return (0);
}
