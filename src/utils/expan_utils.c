/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:14:59 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:15:01 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*handle_variable(char *result, char *str, int *i,
		t_shell_state *state)
{
	char	*temp;
	char	*expanded;
	int		var_len;

	expanded = expand_single_variable(str, *i, &var_len, state);
	if (expanded)
	{
		temp = ft_strjoin(result, expanded);
		free(result);
		free(expanded);
		result = temp;
		*i += var_len;
	}
	return (result);
}

static char	*handle_regular_char(char *result, char c)
{
	char	*temp;
	char	*expanded;
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	temp = ft_substr(str, 0, 1);
	if (temp)
	{
		expanded = ft_strjoin(result, temp);
		free(result);
		free(temp);
		return (expanded);
	}
	return (result);
}

static int	is_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?' || c == '{');
}

static char	*handle_double_dollar(char *result, t_shell_state *state)
{
	char	*temp;
	char	*pid_str;

	pid_str = ft_itoa(state->shell_pid);
	if (!pid_str)
		return (result);
	temp = ft_strjoin(result, pid_str);
	free(result);
	free(pid_str);
	return (temp);
}

char	*expand_variables(char *str, t_shell_state *state)
{
	char	*result;
	int		i;

	if (str[0] == '\'')
		return (ft_strdup(str));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '$')
		{
			result = handle_double_dollar(result, state);
			i += 2;
		}
		else if (str[i] == '$' && str[i + 1] && is_variable_char(str[i + 1]))
			result = handle_variable(result, str, &i, state);
		else
			result = handle_regular_char(result, str[i++]);
		if (!result)
			return (NULL);
	}
	return (result);
}
