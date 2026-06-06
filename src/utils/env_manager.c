/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:14:41 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:14:43 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* Shell State Management */
t_shell_state	*init_shell_state(char **envp)
{
	t_shell_state	*state;
	char			*pid_str;

	state = malloc(sizeof(t_shell_state));
	if (!state)
		return (NULL);
	state->env_table = load_env_from_array(envp);
	if (!state->env_table)
	{
		free(state);
		return (NULL);
	}
	if (env_get(state->env_table, "OLDPWD"))
		env_unset(state->env_table, "OLDPWD");
	state->shell_pid = getpid();
	state->exit_status = 0;
	set_env_value_in_state(state, "?", "0");
	pid_str = ft_itoa(state->shell_pid);
	if (pid_str)
	{
		set_env_value_in_state(state, "$", pid_str);
		free(pid_str);
	}
	return (state);
}

void	cleanup_shell_state(t_shell_state *state)
{
	if (!state)
		return ;
	if (state->env_table)
	{
		free_env_table(state->env_table);
		rl_clear_history();
	}
	free(state);
}

char	*get_env_value_from_state(t_shell_state *state, const char *key)
{
	if (!state || !state->env_table)
		return (NULL);
	return (env_get(state->env_table, key));
}

int	set_env_value_in_state(t_shell_state *state, const char *key,
		const char *value)
{
	if (!state || !state->env_table)
		return (0);
	return (env_set(state->env_table, key, value));
}

int	unset_env_value_from_state(t_shell_state *state, const char *key)
{
	if (!state || !state->env_table)
		return (0);
	return (env_unset(state->env_table, key));
}
