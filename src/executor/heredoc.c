

#include "executor.h"
#include "utils.h"
#include <fcntl.h>

volatile sig_atomic_t	g_heredoc_recieved = 0;

static void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		close(STDIN_FILENO);
		g_heredoc_recieved = SIGINT;
	}
}

static void	setup_heredoc_signals(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static int	create_temp_file(char *tmp_file)
{
	int	fd;

	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

static void	write_heredoc_content(int fd, char *delimiter)
{
	char	*line;

	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
    	&& line[ft_strlen(delimiter)] == '\0')
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

int	handle_heredoc(char *delimiter, int index)
{
	int	fd;

	(void)index;
	fd = create_temp_file("/tmp/minishell_heredoc");
	if (fd < 0)
		return (-1);
	write_heredoc_content(fd, delimiter);
	init_signals();
	if (g_heredoc_recieved == SIGINT)
		return (-1);
	fd = open("/tmp/minishell_heredoc", O_RDONLY, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}
