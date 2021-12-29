#include "minishell.h"

void	ft_cmdadd_back(t_cmd **begin_list, t_cmd *new)
{
	t_cmd	*ptr;

	if (*begin_list == 0)
		*begin_list = new;
	else
	{
		ptr = *begin_list;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

int	get_arg_nbr(t_tokenl *token)
{
	int res;
	t_tokenl *temp;

	res = 0;
	temp = token;
	while (temp)
	{
		if (temp->type == ARG)
			res++;
		else if (temp->type == PIPE)
			return (res);
		temp = temp->next;
	}
	return (res);
}

char	*null_string_array(char **arr)
{
	char **temp;
	int i;

	i = 0;
	temp = arr;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	if (temp)
		free(temp);
	return (NULL);
}

char	**load_args(t_tokenl *token)
{
	char **args;
	t_tokenl *temp;
	int	i;

	i = 0;
	args = malloc(sizeof(char *) * (get_arg_nbr(token) + 2));
	if (args == NULL)
		return (args);
	args[get_arg_nbr(token) + 1] = NULL;
	temp = token;
	while (temp)
	{
		if (temp->type == ARG || temp->type == CMD)
		{
			args[i] = ft_strdup(temp->str);
			if (args[i] == NULL)
				return ((char **)null_string_array(args));
			i++;
		}
		else if (temp->type == PIPE)
			return (args);
		temp = temp->next;	
	}
	return (args);
}

int		is_cmd_in_pipe(t_tokenl *token)
{
	t_tokenl *temp;

	temp = token;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == CMD)
			return (1);
		temp = temp->next;
	}
	return (0);
}

t_cmd	*ft_cmdnew(t_tokenl *token, t_redir *first)
{
	t_cmd *ret;

	ret = malloc(sizeof(t_cmd));
	if (ret == NULL)
		return (ret);
	if (is_cmd_in_pipe(token) == 0)
		ret->args = NULL;
	else
	{
		ret->args = load_args(token);
		if (ret->args == NULL)
		{
			free(ret);
			return (ret);
		}
	}
	ret->fd[0] = 0;
	ret->fd[1] = 1;
	ret->redir = first;
	ret->next = NULL;
	return (ret);
}