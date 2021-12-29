#include "minishell.h"


/*	This function consider that the first element of the list is '1'	*/

t_cmd	*ft_cmd_getn(t_cmd *first, int n)
{
	int i;
	t_cmd *temp;

	i = 1;
	temp = first;
	while (temp)
	{
		if (i == n)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

t_cmd	*ft_cmdget_last(t_cmd *first)
{
	t_cmd *temp;

	temp = first;
	while (temp->next)
		temp = temp->next;
	return (temp);
}