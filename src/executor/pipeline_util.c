

#include "executor.h"
#include "utils.h"
#include <sys/wait.h>

static int	create_pipe_if_needed(t_command *current, int *fd)
{
	if (current->next)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

static void	setup_child_pipes(int in_fd, int *fd, t_command *cmd)
{
	if (in_fd != 0 && cmd && cmd->in_redir == NULL)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	else if (in_fd != 0)
		close(in_fd);
	if (cmd->next)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
}

static void	cleanup_parent_pipes(int *in_fd, int *fd, t_command *current)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (current->next)
	{
		*in_fd = fd[0];
		close(fd[1]);
	}
}

void	wait_for_all_children(t_shell_state *state)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			set_exit_status_in_state(state, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				ft_putstr_fd("\n", 1);
			set_exit_status_in_state(state, 128 + WTERMSIG(status));
		}
	}
}

int	launch_child_and_manage_pipe(t_command *cmd, t_shell_state *state,
		int *in_fd, int fd[2])
{
	pid_t	pid;

	if (create_pipe_if_needed(cmd, fd) == -1)
		return (set_exit_status_in_state(state, 1), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), set_exit_status_in_state(state, 1), -1);
	if (pid == 0)
	{
		init_signals_child();
		setup_child_pipes(*in_fd, fd, cmd);
		execute_simple_command(cmd, state);
		exit(get_exit_status_from_state(state));
	}
	cleanup_parent_pipes(in_fd, fd, cmd);
	return (0);
}
