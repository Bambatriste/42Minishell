#include "minishell.h"


void	ft_lst_clear(t_tokenl *first)
{
	t_tokenl *temp;
	t_tokenl *temp2;

	temp = first;
	while (temp != NULL)
	{
		temp2 = temp;
		if (temp->str)
			free(temp->str);
		temp = temp->next;
		free(temp2);
	}
}

t_tokenl	*ft_toknew(void)
{
	t_tokenl *ret;

	ret = malloc(sizeof(t_tokenl));
	if (ret == NULL)
		return (ret);
	ret->type = NOSPEC;
	ret->str = NULL;
	ret->next = NULL;
	ret->id = -1;
	return (ret);
}

t_tokenl	*ft_tokadd_back(t_tokenl **begin_list, t_tokenl *new)
{
	t_tokenl *temp;

	temp = *begin_list;
	if (*begin_list == NULL)
	{
		*begin_list = new;
		(*begin_list)->id = 1;
		return new;
	}
	while (temp->next != NULL)
		temp = temp->next;
	new->id = temp->id + 1;
	temp->next = new;
	return new;
}
