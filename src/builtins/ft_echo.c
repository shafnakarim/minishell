/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaa-s <jaa-s@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:52:42 by jaa-s             #+#    #+#             */
/*   Updated: 2026/06/22 17:08:01 by jaa-s            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] == '\0')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	print_arguments(int argc, char **argv, int start_index)
{
	int	i;

	i = start_index;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		if (i < argc - 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
}

static void	print_newline_if_needed(int n_flag)
{
	if (!n_flag)
		ft_putstr_fd("\n", 1);
}

int	ft_echo(int argc, char **argv)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (i < argc && check_n_flag(argv[i]))
	{
		n_flag = 1;
		i++;
	}
	print_arguments(argc, argv, i);
	print_newline_if_needed(n_flag);
	return (0);
}
