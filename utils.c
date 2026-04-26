/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:41:23 by srayees           #+#    #+#             */
/*   Updated: 2026/04/24 17:41:24 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	int		len;

	if (!s)
		return (NULL);
	len = strlen(s);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	strcpy(result, s);
	return (result);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	strcpy(result, s1);
	strcat(result, s2);
	return (result);
}

int	ft_strlen(const char *s)
{
	if (!s)
		return (0);
	return (strlen(s));
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		count;
	int		i;
	int		j;
	int		len;

	if (!s)
		return (NULL);
	count = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			count++;
		i++;
	}
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < count)
	{
		if (s[i] != c)
		{
			len = 0;
			while (s[i] && s[i] != c)
			{
				len++;
				i++;
			}
			result[j] = malloc(len + 1);
			if (!result[j])
				return (free_split(result), NULL);
			strncpy(result[j], s + i - len, len);
			result[j][len] = '\0';
			j++;
		}
		else
			i++;
	}
	result[j] = NULL;
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

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (1);
	return (strcmp(s1, s2));
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v');
}

char	*expand_variable(const char *var_name, t_context *ctx)
{
	char	buf[20];

	if (!var_name || !ctx)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
	{
		sprintf(buf, "%d", ctx->last_exit_status);
		return (ft_strdup(buf));
	}
	if (get_env_value(var_name, ctx->env))
		return (ft_strdup(get_env_value(var_name, ctx->env)));
	return (ft_strdup(""));
}
