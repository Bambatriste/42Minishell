/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:15:53 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/29 17:22:12 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* IF never BUFF , infinite loop , need to prevent that ?*/

void	builtin_pwd()
{
	char	*buff;
	int		size;

	size = 1;
	buff = NULL;
	while (!buff)
	{
		buff = getcwd(buff, size);
		size += size;
	}
	printf("%s\n", buff);
	free(buff);
	errno = 0;
}
