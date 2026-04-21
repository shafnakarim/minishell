#include "minishel.h"

static t_token	*new_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value ? ft_strdup(value) : NULL;
	token->next = NULL;
	return (token);
}

static void	add_token(t_token **head, t_token *new)
{
	t_token	*current;

	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

static char	*extract_word(const char *input, int *i)
{
	char	*word;
	int		start;
	int		len;
	char	quote;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|' &&
		input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	len = *i - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	strncpy(word, input + start, len);
	word[len] = '\0';
	return (word);
}

t_token	*tokenize(const char *input)
{
	t_token	*head;
	int		i;
	char	*word;

	if (!input)
		return (NULL);
	head = NULL;
	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|')
		{
			add_token(&head, new_token(TOKEN_PIPE, "|"));
			i++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			add_token(&head, new_token(TOKEN_REDIR_HEREDOC, "<<"));
			i += 2;
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(&head, new_token(TOKEN_REDIR_APPEND, ">>"));
			i += 2;
		}
		else if (input[i] == '<')
		{
			add_token(&head, new_token(TOKEN_REDIR_IN, "<"));
			i++;
		}
		else if (input[i] == '>')
		{
			add_token(&head, new_token(TOKEN_REDIR_OUT, ">"));
			i++;
		}
		else
		{
			word = extract_word(input, &i);
			if (word)
				add_token(&head, new_token(TOKEN_WORD, word));
			if (word)
				free(word);
		}
	}
	return (head);
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

static char	*remove_quotes(const char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	result = malloc(strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
			{
				result[j++] = str[i];
				i++;
			}
			if (str[i] == quote)
				i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

t_pipeline	*parse_tokens(t_token *tokens)
{
	t_pipeline	*pipeline;
	t_cmd		*cmd;
	t_token		*current;
	char		*clean;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->commands = NULL;
	pipeline->cmd_count = 0;
	cmd = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (cmd)
				pipeline->cmd_count++;
			cmd = NULL;
			current = current->next;
		}
		else if (current->type == TOKEN_WORD)
		{
			if (!cmd)
			{
				cmd = malloc(sizeof(t_cmd));
				if (!cmd)
					return (NULL);
				cmd->args = malloc(sizeof(char *) * 100);
				if (!cmd->args)
					return (free(cmd), NULL);
				cmd->arg_count = 0;
				cmd->redirects = NULL;
				cmd->next = NULL;
				if (!pipeline->commands)
					pipeline->commands = cmd;
				else
				{
					t_cmd *t = pipeline->commands;
					while (t->next)
						t = t->next;
					t->next = cmd;
				}
			}
			clean = remove_quotes(current->value);
			cmd->args[cmd->arg_count++] = clean;
			current = current->next;
		}
		else if (current->type == TOKEN_REDIR_IN || 
			current->type == TOKEN_REDIR_OUT ||
			current->type == TOKEN_REDIR_APPEND ||
			current->type == TOKEN_REDIR_HEREDOC)
		{
			if (current->next && current->next->type == TOKEN_WORD)
			{
				t_redir *redir = malloc(sizeof(t_redir));
				if (!redir)
					return (NULL);
				redir->type = current->type;
				redir->target = ft_strdup(current->next->value);
				redir->next = cmd->redirects;
				cmd->redirects = redir;
				current = current->next->next;
			}
			else
				current = current->next;
		}
		else
			current = current->next;
	}
	if (cmd && pipeline->commands)
		pipeline->cmd_count++;
	return (pipeline);
}

void	free_pipeline(t_pipeline *pipeline)
{
	t_cmd	*current;
	t_cmd	*next;
	t_redir	*redir;
	t_redir	*redir_next;
	int		i;

	if (!pipeline)
		return ;
	current = pipeline->commands;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (i < current->arg_count)
			{
				free(current->args[i]);
				i++;
			}
			free(current->args);
		}
		redir = current->redirects;
		while (redir)
		{
			redir_next = redir->next;
			free(redir->target);
			free(redir);
			redir = redir_next;
		}
		free(current);
		current = next;
	}
	free(pipeline);
}
