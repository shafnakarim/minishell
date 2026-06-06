/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:14:50 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:14:52 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**get_env_array_from_state(t_shell_state *state)
{
	if (!state || !state->env_table)
		return (NULL);
	return (env_table_to_array(state->env_table));
}

void	set_exit_status_in_state(t_shell_state *state, int status)
{
	char	*status_str;

	if (!state)
		return ;
	state->exit_status = status;
	status_str = ft_itoa(status);
	if (status_str)
	{
		set_env_value_in_state(state, "?", status_str);
		free(status_str);
	}
}

int	get_exit_status_from_state(t_shell_state *state)
{
	if (!state)
		return (0);
	return (state->exit_status);
}

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

int	update_existing_var(t_env_var *current, const char *value)
{
	if (!current || !value)
		return (0);
	free(current->value);
	current->value = ft_strdup(value);
	if (!current->value)
		return (0);
	return (1);
}
