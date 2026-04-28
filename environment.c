/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:40:29 by srayees           #+#    #+#             */
/*   Updated: 2026/04/24 17:40:31 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

static t_env	*create_env_node(char *env_str)
{
	t_env	*new;
	char	*eq;

	eq = strchr(env_str, '=');
	if (!eq)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = malloc(eq - env_str + 1);
	if (!new->key)
		return (free(new), NULL);
	strncpy(new->key, env_str, eq - env_str);
	new->key[eq - env_str] = '\0';
	new->value = ft_strdup(eq + 1);
	if (!new->value)
		return (free(new->key), free(new), NULL);
	new->next = NULL;
	return (new);
}

static void	add_env_node(t_env **env, t_env *new)
{
	t_env	*current;

	if (!*env)
	{
		*env = new;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new;
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if (!envp || !*envp)
		return (NULL);
	env = NULL;
	i = 0;
	while (envp[i])
	{
		new = create_env_node(envp[i]);
		if (new)
			add_env_node(&env, new);
		i++;
	}
	return (env);
}
