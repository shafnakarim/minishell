/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:15:55 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:15:58 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	env_unset(t_env_table *table, const char *key)
{
	t_env_var	*current;
	t_env_var	*prev;

	current = find_env_var(table, key, &prev);
	if (!current)
		return (0);
	if (prev)
		prev->next = current->next;
	else
		table->buckets[hash_function(key)] = current->next;
	free(current->key);
	free(current->value);
	free(current);
	return (1);
}

void	free_env_table(t_env_table *table)
{
	t_env_var	*current;
	t_env_var	*next;
	int			i;

	if (!table)
		return ;
	i = 0;
	while (i < table->size)
	{
		current = table->buckets[i];
		while (current)
		{
			next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			current = next;
		}
		i++;
	}
	free(table->buckets);
	free(table);
}

int	process_env_entry(char *entry, t_env_table *table)
{
	char	*key;
	char	*value;
	char	*eq_pos;

	eq_pos = ft_strchr(entry, '=');
	if (!eq_pos)
		return (1);
	key = ft_substr(entry, 0, eq_pos - entry);
	value = ft_strdup(eq_pos + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (0);
	}
	env_set(table, key, value);
	free(key);
	free(value);
	return (1);
}

t_env_table	*load_env_from_array(char **envp)
{
	t_env_table	*table;
	int			i;

	table = init_env_table();
	if (!table)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		if (!process_env_entry(envp[i], table))
		{
			free_env_table(table);
			return (NULL);
		}
		i++;
	}
	return (table);
}

char	**env_table_to_array(t_env_table *table)
{
	char	**envp;
	int		count;

	if (!table)
		return (NULL);
	count = count_env_var(table);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	fill_env_array(table, envp);
	return (envp);
}
