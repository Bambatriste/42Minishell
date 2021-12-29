/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 19:51:14 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/29 19:51:16 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_paths(t_list *env)
{
	char *path_str;
	char **split;
	char *tmp;
	int i;

	i = 0;
	path_str = ft_search_value(env, "PATH");
	split = ft_split(path_str, ':');
	while (split[i])
	{
		tmp = split[i];
		split[i] = ft_strjoin(split[i], "/");
		if (tmp)
			free(tmp);
		i++;
	}
	return (split);
}

/* property of Napoleon-42 */
void	free_paths(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	return ;
}
