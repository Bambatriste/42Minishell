#include "minishell.h"

void	skip_char(char *str, char a, int *i)
{
	while (str[*i] == a && str[*i])
		*i = *i + 1;
	return ;
}

//	join all characters inside the spec. quotes till the ending quote or \0
int		add_quotes(int *i, char *str, t_tokenl *last)
{
	char key;

	key = str[*i];
	*i = *i + 1;
	while (str[*i] && str[*i] != key)
	{
		last->str = ft_strjoin_char(last->str, str[*i]);
		if (last->str == NULL)
			return (0);
		*i = *i + 1;
	}
	if (str[*i] == key)
		*i = *i + 1;	
	return (1);
}


//	join all '<' '>' characters to the *last->str, stop at the first non spec. char
int		addred_helper1(int *i, char *str, t_tokenl *last)
{
	while ((str[*i] == '<' || str[*i] == '>') && str[*i])
	{
		last->str = ft_strjoin_char(last->str, str[*i]);
		if (last->str == NULL)
			return (0);
		*i = *i + 1;
	}
	return (1);
}

//	join all characters to the *last->str, stop at the first non '<' '>' ' ' char. or \0
int		addred_helper2(int *i, char *str, t_tokenl *last)
{
	while (str[*i] != '<' && str[*i] != '>' && str[*i] && str[*i] != ' ')
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			if (add_quotes(i, str, last) == 0)
				return (0);
		}
		else
		{
			last->str = ft_strjoin_char(last->str, str[*i]);
			if (last->str == NULL)
				return (0);
		}
		*i = *i + 1;
	}
	return (1);
}

int		add_redirs(t_tokenl **first, int *i, char *str)
{
	t_tokenl *last;

	last = NULL;
	while (str[*i] != ' ' && str[*i])
	{
		last = ft_tokadd_back(first, ft_toknew());
		if (last == NULL)
			return (0);
		if (str[*i] == '<' || str[*i] == '>')
		{
			if (addred_helper1(i, str, last) == 0)
				return (0);
		}
		else if (str[*i] != '<' || str[*i] != '>')
			if (addred_helper2(i, str, last) == 0)
				return (0);
	}
	return (1);
}

int		add_pipe(t_tokenl **first, int *i, char *str)
{
	t_tokenl *last;

	last = ft_tokadd_back(first, ft_toknew());
	if (last == NULL)
		return (0);
	while (str[*i] == '|' && str[*i])
	{
		last->str = ft_strjoin_char(last->str, '|');
		if (last->str == NULL)
			return (0);
		*i = *i + 1;
	}
	return (1);
}

int		add_token(t_tokenl **first, int *i, char *str)
{
	t_tokenl *last;

	last = ft_tokadd_back(first, ft_toknew());
	if (last == NULL)
		return (0);
	while (str[*i] != ' ' && str[*i] != '>' && str[*i] != '<' && str[*i] &&
		str[*i] != '|' && str[*i])
	{
		if (str[*i] == '\"' || str[*i] == '\'')
		{
			if (add_quotes(i, str, last) == 0)
				return (0);
		}
		else
		{
			last->str = ft_strjoin_char(last->str, str[*i]);
			if (last->str == NULL)
				return (0);
		if (str[*i])
			*i = *i + 1;
		}
	}
	return (1); 
}

// to rewrite geting list, cout >>file>file> >><< <> and also $ (all expandsJ)
t_tokenl	*parce_cmd_line(char *str)
{
	int i;
	t_tokenl *first;

	i = 0;
	first = NULL;
	while (str[i])
	{
		if (str[i] == ' ')
			skip_char(str, ' ', &i);
		if (str[i] == '<' || str[i] == '>')
		{
			if (add_redirs(&first, &i, str) == 0)
				return (NULL);
		}
		else if (str[i] == '|')
		{
			if (add_pipe(&first, &i, str) == 0)
				return (NULL);
		}
		else if (str[i])
			if (add_token(&first, &i, str) == 0)
				return (NULL);
	}
	return (first);
}