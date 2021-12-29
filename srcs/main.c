/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:40:30 by bdruez            #+#    #+#             */
/*   Updated: 2021/12/29 18:18:36 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir_lst(t_redir *first)
{
	while (first)
	{
		printf("type: %s \tfilename: %s\n", 
		first->type == REDIR_OUT ? ">" : first->type == REDIR_IN ? "<" : first->type == REDIR_OUT2 ? ">>" : "<<", 
		first->filename);
		first = first->next;
	}
	return ;
}

void	print_cmd_lst(t_cmd *list)
{
	int i;
	int	j;

	i = 1;
	j = 0;
	if (list == NULL)
		return ;
	printf("\n\t\tCOMMANDS LIST:\n");
	while(list)
	{
		printf("\t\tcmd_lst %i | \t fd[0] = %i fd[1] = %i\n",
		i,
		list->fd[0], 
		list->fd[1]);
		j = 0;
		if (list->args == NULL)
			printf("NULL\n");
		else
		{
			while (list->args[j])
			{
				if (j == 0)
					printf("-cmd: %s\n", list->args[j]);
				else
					printf("--arg: %s\n", list->args[j]);
				j++;
			}
		}
		i++;
		write(1, "\nRedirs:_____\n", 15);
		if (list->redir == NULL)
			printf("NULL\n");
		else
			print_redir_lst(list->redir);
		write(1, "\n\n\n", 3);
		list = list->next;
	}
	return ;
}


void	print_content(void *content)
{	
	t_env_str *content2 = (t_env_str *)content;
	printf("variable : %s\n", content2->name);
	printf("contenu : %s\n", content2->value);
}


void	ft_free_content(void *content)
{
	t_env_str *content2 = (t_env_str *)content;
	free(content2->name);
	free(content2->value);
	content2->name = NULL;
	content2->value = NULL;

	free(content2);
}

void	ft_free_cmds(void *content)
{
	t_cmd *content2 = (t_cmd *)content;

	int i = 0;

	while(content2->args[i])
	{
		free(content2->args[i]);
		i++;
	}
	free(content2->args);

	free(content2);
}


void	exec_print(void *content)
{
	t_cmd *cmd = (t_cmd *)content;

	printf("%s    ", cmd->args[0]);
	printf("%s\n", cmd->args[1]);

	//printf("%d\n", cmd->type);

}

t_list	*transform(t_cmd *first)
{
	t_cmd *temp;
	t_list *ret;

	ret = NULL;
	temp = first;
	while (temp)
	{
		ft_lstadd_back(&ret, ft_lstnew((void *)temp));
		temp = temp->next;
	}
	return (ret);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char    *temp;
	t_tokenl *list = NULL;
	t_cmd *cmds = NULL;
	t_list *commands;



	t_list *lst_env;

	lst_env = NULL;
	ft_lst_copyenv(env, &lst_env);
	
	while (1)
	{
    	temp = readline(NULL);
		if (temp == NULL || temp[0] == 0)
			return (0);
		if (list)
			ft_lst_clear(list);
		list = parce_cmd_line(temp);
		if (list == NULL)
			return (0);
		spec_types(list);
		cmds = get_cmd_lst(list);
		commands = transform(cmds);
		//print_cmd_lst(cmds);
		exec_cmds(commands, env, lst_env);
	}
	return (0);
}
