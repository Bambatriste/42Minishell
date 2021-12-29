#include "minishell.h"

int		xft_strcmp(char *s1, char *s2)
{
	int i;
	int	size[2];

	size[0] = ft_strlen(s1);
	size[1] = ft_strlen(s2);
	if (size[0] != size[1])
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return 1;
}

void	ft_rediradd_back(t_redir **begin_list, t_redir *new)
{
	t_redir	*ptr;

	if (*begin_list == NULL)
		*begin_list = new;
	else
	{
		ptr = *begin_list;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = new;
	}
}

t_redir	*ft_redirnew(t_tokenl *token)
{
	t_redir	*res;

	res = malloc(sizeof(t_redir));
	if (res == NULL)
		return (res);
	if (xft_strcmp(token->str, "<") == 1)
		res->type = REDIR_IN;
	else if (xft_strcmp(token->str, "<<") == 1)
		res->type = REDIR_IN2;
	else if (xft_strcmp(token->str, ">") == 1)
		res->type = REDIR_OUT;
	else if (xft_strcmp(token->str, ">>") == 1)
		res->type = REDIR_OUT2;
	else
		res->type = -1;
	res->filename = token->next->str;
	res->next = NULL;
	return (res);
}