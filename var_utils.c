/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

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
