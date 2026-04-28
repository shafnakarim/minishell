/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

static void	fill_word(char **result, const char *s, char c, int *indices)
{
	int	len;

	len = 0;
	while (s[indices[1]] && s[indices[1]] != c)
	{
		len++;
		indices[1]++;
	}
	result[indices[0]] = malloc(len + 1);
	if (!result[indices[0]])
		return ;
	strncpy(result[indices[0]], s + indices[1] - len, len);
	result[indices[0]][len] = '\0';
	indices[0]++;
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		count;
	int		indices[2];

	if (!s)
		return (NULL);
	count = count_words(s, c);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	indices[0] = 0;
	indices[1] = 0;
	while (s[indices[1]] && indices[0] < count)
	{
		if (s[indices[1]] != c)
			fill_word(result, s, c, indices);
		else
			indices[1]++;
	}
	result[indices[0]] = NULL;
	return (result);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
