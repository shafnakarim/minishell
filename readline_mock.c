#include "minishel.h"

static int		hist_size = 0;
static char		**history = NULL;
static int		hist_capacity = 100;

char	*readline(const char *prompt)
{
	char	buffer[1024];
	int		n;
	int		i;

	if (prompt)
		printf("%s", prompt);
	fflush(stdout);
	n = 0;
	while (n < 1023)
	{
		i = read(STDIN_FILENO, &buffer[n], 1);
		if (i <= 0)
			break ;
		if (buffer[n] == '\n')
		{
			buffer[n] = '\0';
			return (ft_strdup(buffer));
		}
		n++;
	}
	if (n == 0)
		return (NULL);
	buffer[n] = '\0';
	return (ft_strdup(buffer));
}

void	add_history(char *line)
{
	if (!line || !*line)
		return ;
	if (!history)
	{
		history = malloc(sizeof(char *) * hist_capacity);
		if (!history)
			return ;
	}
	if (hist_size >= hist_capacity)
	{
		char **temp = malloc(sizeof(char *) * (hist_capacity + 50));
		if (!temp)
			return ;
		hist_capacity += 50;
		int i = 0;
		while (i < hist_size)
		{
			temp[i] = history[i];
			i++;
		}
		free(history);
		history = temp;
	}
	history[hist_size++] = ft_strdup(line);
}

void	rl_clear_history(void)
{
	int	i;

	if (!history)
		return ;
	i = 0;
	while (i < hist_size)
	{
		free(history[i]);
		i++;
	}
	free(history);
	history = NULL;
	hist_size = 0;
}

void	rl_on_new_line(void)
{
	return ;
}

void	rl_replace_line(const char *text, int clear_undo)
{
	(void)text;
	(void)clear_undo;
	return ;
}

void	rl_redisplay(void)
{
	return ;
}
