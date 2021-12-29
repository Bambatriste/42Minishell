#include "minishell.h"

int		count_cmds(t_tokenl *first)
{
	int i;
	t_tokenl *temp;

	temp = first;
	i = 1;
	while (temp)
	{
		if (temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}

t_cmd	*get_cmd_lst(t_tokenl *first)
{
	t_cmd *ret;
	t_tokenl *token;

	ret = NULL;
	token = first;
	while (token)
	{
		ft_cmdadd_back(&ret, ft_cmdnew(token, NULL));
		while (token && token->type != PIPE)
		{
			if (token->type == REDIR)
				ft_rediradd_back(&(ft_cmdget_last(ret)->redir),
				ft_redirnew(token));
			token = token->next;
		}
		if (token)
			token = token->next;
	}
	return (ret);
}