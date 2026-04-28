/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srayees <srayees@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 00:00:00 by srayees           #+#    #+#             */
/*   Updated: 2026/04/26 00:00:00 by srayees          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

static void	free_redirects(t_redir *redirects)
{
	t_redir	*redir_next;

	while (redirects)
	{
		redir_next = redirects->next;
		if (redirects->target)
			free(redirects->target);
		free(redirects);
		redirects = redir_next;
	}
}

static void	free_cmd_args(t_cmd *cmd)
{
	int	i;

	if (!cmd->args)
		return ;
	i = 0;
	while (i < cmd->arg_count)
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
}

void	free_pipeline(t_pipeline *pipeline)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!pipeline)
		return ;
	current = pipeline->commands;
	while (current)
	{
		next = current->next;
		free_cmd_args(current);
		free_redirects(current->redirects);
		free(current);
		current = next;
	}
	free(pipeline);
}
