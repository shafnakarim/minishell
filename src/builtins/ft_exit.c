/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:52:59 by jaa-s             #+#    #+#             */
/*   Updated: 2026/07/07 14:53:11 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static void	exit_with_status(t_shell_state *state, int status)
{
	set_exit_status_in_state(state, status);
}

static void	exit_too_many_args(void)
{
	ft_putstr_fd("exit: too many arguments\n", 2);
}

static int	handle_numeric_argument(char *arg, t_shell_state *state)
{
	int	exit_code;

	if (!ft_str_is_numeric(arg))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit_with_status(state, 255);
		return (255);
	}
	exit_code = ft_atoi(arg);
	exit_code = (exit_code + 256) % 256;
	exit_with_status(state, exit_code);
	return (exit_code);
}

int	ft_exit(int argc, char **argv, t_shell_state *state)
{
	if (argc > 2)
	{
		exit_too_many_args();
		return (1);
	}
	if (argc == 2)
		return (handle_numeric_argument(argv[1], state));
	exit_with_status(state, 0);
	return (0);
}
