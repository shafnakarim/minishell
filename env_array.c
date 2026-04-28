/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

static int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	*create_env_string(t_env *current)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(current->key, "=");
	result = ft_strjoin(temp, current->value);
	free(temp);
	return (result);
}

char	**env_to_array(t_env *env)
{
	char	**array;
	int		count;
	int		i;
	t_env	*current;

	count = count_env_vars(env);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	current = env;
	i = 0;
	while (current && i < count)
	{
		array[i] = create_env_string(current);
		if (!array[i])
			return (free_split(array), NULL);
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
