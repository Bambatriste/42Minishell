#include "minishell.h"


int		spec_first_token_type(t_tokenl *first, int *key)
{
	if (ft_strcmp("<", first->str) == 1 || ft_strcmp(">", first->str) == 1 ||
		ft_strcmp("<<", first->str) == 1 || ft_strcmp(">>", first->str) == 1)
		spec_redir(first);
	else if (first->str[0] == '|')
		return (0);
	else
	{
		first->type = CMD;
		*key = 1;
	}
	return (1);
}

int		spec_last_token_type(t_tokenl *last, int key)
{
	char a;

	a = last->str[ft_strlen(last->str)];
	if (a == '<' || a == '|' || a == '>')
		return (0);
	else
	{
		if (last->type != FILE)
		{
			if (key == 0)
				last->type = CMD;
			else
				last->type = ARG;
		}
	}
	return (1);
}

int	spec_last_first_token(t_tokenl *token, int *key)
{
	if (token->id == 1)
	{
		if (spec_first_token_type(token, key) == 0)
			return (0);
	}
	else
	{
		if (spec_last_token_type(token, *key) == 0)
			return (0);
	}
	return (1);
}

int		spec_redir(t_tokenl *token)
{
	token->type = REDIR;
	if (token->next == NULL)
		return (0);
	else
		token->next->type = FILE;
	return 1;
}

void	spec_cmd(t_tokenl *token, int *key)
{
	token->type = CMD;
	*key = 1;
	return ;
}

void	spec_pipe(t_tokenl *token, int *key)
{
	token->type = PIPE;
	*key = 0;
}

int	spec_types(t_tokenl *first)
{
	t_tokenl *temp;
	int			key;
	//char	redir_strs[4][2] = {"<<", "<", ">", ">>"};

	key = 0;
	temp = first;
	while (temp != NULL)
	{
		if (temp->id == 1 || temp->next == NULL)
		{
			if (spec_last_first_token(temp, &key) == 0)
				return (0);
		}
		else if (ft_strcmp(temp->str, "|") == 1)
			spec_pipe(temp, &key);
		else if (ft_strcmp("<", temp->str) == 1 || ft_strcmp(">", temp->str) == 1 ||
				ft_strcmp("<<", temp->str) == 1 || ft_strcmp(">>", temp->str) == 1)
			spec_redir(temp);
		else if (key == 0 && temp->type == NOSPEC)
			spec_cmd(temp, &key);
		else if (key == 1 && temp->type == NOSPEC)
			temp->type = ARG;
		temp = temp->next;
	}
	return (1);
}
