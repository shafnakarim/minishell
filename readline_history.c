/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

static int	g_hist_size = 0;
static char	**g_history = NULL;
static int	g_hist_capacity = 100;

static int	expand_history(void)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (g_hist_capacity + 50));
	if (!temp)
		return (1);
	g_hist_capacity += 50;
	i = 0;
	while (i < g_hist_size)
	{
		temp[i] = g_history[i];
		i++;
	}
	free(g_history);
	g_history = temp;
	return (0);
}

void	add_history(char *line)
{
	if (!line || !*line)
		return ;
	if (!g_history)
	{
		g_history = malloc(sizeof(char *) * g_hist_capacity);
		if (!g_history)
			return ;
	}
	if (g_hist_size >= g_hist_capacity)
		if (expand_history())
			return ;
	g_history[g_hist_size++] = ft_strdup(line);
}

void	rl_clear_history(void)
{
	int	i;

	if (!g_history)
		return ;
	i = 0;
	while (i < g_hist_size)
	{
		free(g_history[i]);
		i++;
	}
	free(g_history);
	g_history = NULL;
	g_hist_size = 0;
}
