#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

/*
** ----- Defines ---------------------------------------------------------------
*/

#define READ_END	0
#define WRITE_END	1

#define REDIR_IN 0
#define REDIR_OUT  1
#define REDIR_IN2 2
#define REDIR_OUT2  3

# define CMD 1
# define ARG 2
# define FILE 3
# define REDIR 4
# define PIPE 5
# define NOSPEC 6

/*
** ----- Structures ------------------------------------------------------------
*/

typedef	struct s_token
{
    int             id;
	char            type;
	char            *str;
	struct s_token *next;
}				t_tokenl;

typedef struct env_str
{
	char	*name;
	char	*value;
	int		export;
}	t_env_str;

typedef struct s_redir
{
    int               type;
    char              *filename;
    struct s_redir    *next;
}		    t_redir;


typedef struct s_command
{
    char			    **args;
    t_redir	             *redir;
    int			   	    fd[2];
    struct s_command	*next;
}	        t_cmd;


int exec_cmds(t_list *lst, char **envp);
void	builtin_echo(char **av);
void	builtin_pwd();
void	builtin_unset(t_list *lst, char **strs);
void    builtin_exit(char **args, t_list *lst_env, t_list *lst_export);
void	builtin_cd(char **args, t_list *lst_env, t_list *lst_export);
void	builtin_env(t_list *lst_env);
void	builtin_export(t_list *export_lst, t_list *env_lst, char **strs);
void	ft_lst_copyenv(char **env, t_list **head);
void	ft_free_content(void *content);
char	*ft_search_value(t_list *lst, char *name);
int	found_in_env(char *str, void *content);
char **ft_convert(t_list *head);
int	ft_check_if_exists(t_list *lst, char *name);
char	*get_name(char *str, char *name);
char *get_value_str(char *str, char *value);
void	ft_free_content(void *content);
void    ft_sort_export(t_list *lst);
void	export_to_list(char *str, t_list *export_lst, t_list *env_lst, int export_env);
void    ft_exit(t_list *lst_env, t_list *lst_export);


t_cmd   *get_cmd_lst(t_tokenl *first);

int     found_in_env(char *str, void *content);
char    *ft_search_value(t_list *lst, char *name);
char    *ft_get_value(void *content);
int     found_in_env(char *str, void *content);

char    *get_value_str(char *str, char *value);
void    ft_lst_copyenv(char **env, t_list **head);
char    *get_name(char *str, char *name);


t_tokenl	*ft_toknew(void);
t_tokenl	*ft_tokadd_back(t_tokenl **begin_list, t_tokenl *new);
t_tokenl	*parce_cmd_line(char *str);

/*			### LIST.C ###				*/

t_cmd	*ft_cmdget_last(t_cmd *first);
t_cmd	*ft_cmdnew(t_tokenl *token, t_redir *first);
t_cmd	*ft_cmd_getn(t_cmd *first, int n);
void	ft_cmdadd_back(t_cmd **begin_list, t_cmd *new);
char	**load_args(t_tokenl *token);
int		get_arg_nbr(t_tokenl *token);
char	*null_string_arrray(char **arr);

t_redir	*ft_redirnew(t_tokenl *token);
void	ft_rediradd_back(t_redir **befin_list, t_redir *new);

/*			### MAIN.C ###				*/


/*			### GET_TOKENS_UTILS.C ###	*/

int		ft_strstrchr(char **strstr, char *str);
int		ft_strcmp(char *s1, char *s2);
int		get_squote(char *str, int *i, t_tokenl *temp);
int		get_dquote(char *str, int *i, t_tokenl *temp);
int		get_quote(char *str, int *i, t_tokenl *temp);
t_tokenl *line_to_tlist(char *str);


/*			### GET_TOKENS.C ### 		*/

char *ft_strjoin_char(char *str, char a);
t_tokenl    *new_token(t_tokenl *this);
void    *exit_ltl(t_tokenl *first, char *errmasg);
void    ft_lst_clear(t_tokenl *first);

/*			###	SPEC_TOKENS.C ###		*/

int	spec_first_token_type(t_tokenl *first, int *key);
int	spec_last_token_type(t_tokenl *last, int key);
int	spec_last_first_token(t_tokenl *token, int *key);
int	spec_redir(t_tokenl *token);
void	spec_cmd(t_tokenl *token, int *key);
int	spec_types(t_tokenl *first);

#endif