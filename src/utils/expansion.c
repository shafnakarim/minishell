/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 12:15:09 by srayees           #+#    #+#             */
/*   Updated: 2026/06/06 12:15:11 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*expand_variable(const char *var_name, t_shell_state *state)
{
	char	*value;

	if (!var_name || !state)
		return (ft_strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(get_exit_status_from_state(state)));
	if (ft_strcmp(var_name, "$") == 0)
		return (ft_itoa(state->shell_pid));
	value = get_env_value_from_state(state, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*extract_var_name(const char *str, int *len)
{
	int	i;

	i = 0;
	if (str[i] == '{')
	{
		i++;
		while (str[i] && str[i] != '}')
			i++;
		if (str[i] == '}')
		{
			*len = i + 1;
			return (ft_substr(str, 1, i - 1));
		}
	}
	else
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
			i++;
		*len = i;
		return (ft_substr(str, 0, i));
	}
	*len = 1;
	return (ft_strdup(""));
}

char	*expand_single_variable(const char *str, int start, int *new_len,
		t_shell_state *state)
{
	char	*var_name;
	char	*expanded;
	int		var_len;

	var_name = extract_var_name(str + start + 1, &var_len);
	if (!var_name)
		return (NULL);
	expanded = expand_variable(var_name, state);
	free(var_name);
	if (!expanded)
		return (NULL);
	*new_len = var_len + 1;
	return (expanded);
}

static int	process_quote_char(char c, int *i, int *in_dquote, int *in_squote)
{
	if ((c == '\'' && !(*in_dquote)) || (c == '\"' && !(*in_squote)))
	{
		if (c == '\'')
			*in_squote = !(*in_squote);
		else
			*in_dquote = !(*in_dquote);
		(*i)++;
		return (1);
	}
	return (0);
}

char	*remove_quotes(const char *str)
{
	char	*result;
	int		i;
	int		j;
	int		in_dquote;
	int		in_squote;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_dquote = 0;
	in_squote = 0;
	while (str[i])
	{
		if (!process_quote_char(str[i], &i, &in_dquote, &in_squote))
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
