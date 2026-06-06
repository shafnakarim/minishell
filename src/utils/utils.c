/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:15:46 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:15:48 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

int	ft_str_is_numeric(char *str)
{
	int	i;
	int	digit;

	i = 0;
	digit = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[0] != '-')
			return (0);
		i++;
	}
	digit = ft_atoi(str);
	if (digit == -1 && ft_strlen(str) > 4)
		return (0);
	return (digit % 256);
}

void	fill_env_array(t_env_table *table, char **envp)
{
	char		*env_str;
	int			idx;
	int			i;
	t_env_var	*current;

	idx = 0;
	i = 0;
	while (i < table->size)
	{
		current = table->buckets[i];
		while (current)
		{
			env_str = ft_strjoin(current->key, "=");
			if (env_str)
			{
				envp[idx] = ft_strjoin(env_str, current->value);
				free(env_str);
				if (envp[idx])
					idx++;
			}
			current = current->next;
		}
		i++;
	}
	envp[idx] = NULL;
}

int	count_env_var(t_env_table *table)
{
	int			count;
	int			i;
	t_env_var	*current;

	count = 0;
	i = 0;
	while (i < table->size)
	{
		current = table->buckets[i];
		while (current)
		{
			count++;
			current = current->next;
		}
		i++;
	}
	return (count);
}

t_env_var	*find_env_var(t_env_table *table, const char *key, t_env_var **prev)
{
	unsigned int	index;
	t_env_var		*current;

	if (!table || !key)
		return (NULL);
	index = hash_function(key);
	current = table->buckets[index];
	*prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		*prev = current;
		current = current->next;
	}
	return (NULL);
}

t_env_var	*add_new_var(t_env_table *table, const char *key, const char *value,
		unsigned int index)
{
	t_env_var	*new_var;

	new_var = create_env_var(key, value);
	if (!new_var)
		return (NULL);
	new_var->next = table->buckets[index];
	table->buckets[index] = new_var;
	return (new_var);
}
