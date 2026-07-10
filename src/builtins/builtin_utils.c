/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaa-s <jaa-s@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:33:22 by jaa-s             #+#    #+#             */
/*   Updated: 2026/06/16 09:33:27 by jaa-s            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_cd_error(char *target)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

void	print_export_error(char *name)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	*extract_value(char *eq_pos)
{
	return (ft_strdup(eq_pos + 1));
}
