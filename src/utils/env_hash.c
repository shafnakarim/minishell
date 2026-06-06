/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:14:27 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:14:29 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#define HASH_TABLE_SIZE 256

unsigned int	hash_function(const char *key)
{
	unsigned int	hash;
	int				i;

	hash = 5381;
	i = 0;
	while (key[i])
	{
		hash = ((hash << 5) + hash) + key[i];
		i++;
	}
	return (hash % HASH_TABLE_SIZE);
}

t_env_table	*init_env_table(void)
{
	t_env_table	*table;
	int			i;

	table = malloc(sizeof(t_env_table));
	if (!table)
		return (NULL);
	table->buckets = malloc(sizeof(t_env_var *) * HASH_TABLE_SIZE);
	if (!table->buckets)
	{
		free(table);
		return (NULL);
	}
	i = 0;
	while (i < HASH_TABLE_SIZE)
	{
		table->buckets[i] = NULL;
		i++;
	}
	table->size = HASH_TABLE_SIZE;
	return (table);
}

t_env_var	*create_env_var(const char *key, const char *value)
{
	t_env_var	*var;

	var = malloc(sizeof(t_env_var));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	if (!var->key || !var->value)
	{
		free(var->key);
		free(var->value);
		free(var);
		return (NULL);
	}
	var->next = NULL;
	return (var);
}

int	env_set(t_env_table *table, const char *key, const char *value)
{
	unsigned int	index;
	t_env_var		*current;

	if (!table || !key)
		return (0);
	index = hash_function(key);
	current = table->buckets[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (update_existing_var(current, value));
		current = current->next;
	}
	if (!add_new_var(table, key, value, index))
		return (0);
	return (1);
}

char	*env_get(t_env_table *table, const char *key)
{
	unsigned int	index;
	t_env_var		*current;

	if (!table || !key)
		return (NULL);
	index = hash_function(key);
	current = table->buckets[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
