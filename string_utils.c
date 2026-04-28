/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (1);
	return (strcmp(s1, s2));
}
