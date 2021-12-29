#include "minishell.h"

char *ft_strjoin_char(char *str, char a)
{
	int i;
	char *ret;

	if (!str)
	{
		ret = malloc(2);
		ret[1] = 0;
		ret[0] = a;
		return ret;
	}
	ret = malloc(sizeof(char) * (ft_strlen(str) + 2));
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i++] = a;
	ret[i] = 0;
	free(str);
	return (ret);
}

int		ft_strstrchr(char **strstr, char *str)
{
	int i;

	i = 0;
	while (strstr[i])
	{
		if (ft_strcmp(strstr[i], str) == 1)
			return (1);
		i++;
	}
	return (0);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return 1;
}