#include "minishel.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*current;
	t_env	*new;
	int		i;
	char	*eq;

	if (!envp || !*envp)
		return (NULL);
	env = NULL;
	i = 0;
	while (envp[i])
	{
		eq = strchr(envp[i], '=');
		if (eq)
		{
			new = malloc(sizeof(t_env));
			if (!new)
				return (NULL);
			new->key = malloc(eq - envp[i] + 1);
			if (!new->key)
				return (free(new), NULL);
			strncpy(new->key, envp[i], eq - envp[i]);
			new->key[eq - envp[i]] = '\0';
			new->value = ft_strdup(eq + 1);
			if (!new->value)
				return (free(new->key), free(new), NULL);
			new->next = NULL;
			if (!env)
				env = new;
			else
			{
				current = env;
				while (current->next)
					current = current->next;
				current->next = new;
			}
		}
		i++;
	}
	return (env);
}

char	*get_env_value(const char *key, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	set_env_value(const char *key, const char *value, t_env **env)
{
	t_env	*current;
	t_env	*new;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *env;
	*env = new;
}

void	unset_env_value(const char *key, t_env **env)
{
	t_env	*current;
	t_env	*previous;

	if (!*env)
		return ;
	current = *env;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

char	**env_to_array(t_env *env)
{
	char	**array;
	int		count;
	int		i;
	t_env	*current;
	char	*temp;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	current = env;
	i = 0;
	while (current && i < count)
	{
		temp = ft_strjoin(current->key, "=");
		array[i] = ft_strjoin(temp, current->value);
		free(temp);
		if (!array[i])
			return (free_split(array), NULL);
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
