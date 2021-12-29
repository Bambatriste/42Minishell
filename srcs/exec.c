#include "minishell.h"

int redir_out(t_redir *redir, int *fd_out)
{
    *fd_out = open(redir->filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    dup2(*fd_out, STDOUT_FILENO);
    close(*fd_out);
    return (0);
}

int redir_in(t_redir *redir, int *fd_in)
{
    *fd_in = open(redir->filename, O_RDWR , S_IRWXU);
    if (*fd_in == -1)
    {
        perror(redir->filename);
        close(*fd_in);
        exit(0);
    }
    dup2(*fd_in, STDIN_FILENO);
    close(*fd_in);
    return (0);
}

int redir_append(t_redir *redir, int *fd_out)
{
    *fd_out = open(redir->filename, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
    dup2(*fd_out, STDOUT_FILENO);
    close(*fd_out);
    return (0);
}

int redir_heredoc(t_redir *redir, int *fd_in)
{
    int ret;
    char *str;
    int n;

    ret = 1;
    *fd_in = open("tmp_heredoc", O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
    while (ret)
    {
        str = readline(">");
        n = ft_strlen(str);
        if ((int)ft_strlen(redir->filename) > n)
            n = ft_strlen(redir->filename);
        ret = ft_strncmp(redir->filename, str, n);
        if (ret != 0)
        {
            write(*fd_in, ft_strjoin(str, "\n"), ft_strlen(str) + 1);
            *fd_in = open("tmp_heredoc", O_RDWR | O_APPEND, S_IRWXU);
        }
    }
    dup2(*fd_in, STDIN_FILENO);
    close (*fd_in);
    unlink("tmp_heredoc");
    return (0);
}

int redirect(t_cmd * cmd)
{
    t_redir *redir;
    int fd_out;
    int fd_in;

    redir = cmd->redir;
    if (cmd->redir == NULL)
        return (1);
    while (redir)
    {
        if (redir->type == REDIR_OUT)
            redir_out(redir, &fd_out);
        else if (redir->type == REDIR_IN)
            redir_in(redir, &fd_in);
        else if (redir ->type == REDIR_OUT2)
            redir_append(redir, &fd_out);
        else if (redir->type == REDIR_IN2)
            redir_heredoc(redir, &fd_in);
        redir = redir->next;
    }
    return (1);
}

char		*try_acces(char *cmd_name, t_list *env)
{
	char **paths;
	int i;
	char *test_path;
	int access_return;

	i = 0;
	paths = get_paths(env);
	while (paths[i])
	{
		test_path = ft_strjoin(paths[i], cmd_name);
		//printf("%s\n", test_path);
		access_return = access(test_path, F_OK);
		//printf("%d\n", access_return);
		if (access_return == 0)
			return (test_path);
		i++;
	}
	return (NULL);
}

int execute_cmd(t_cmd *cmd, t_cmd *prev, t_cmd *next, char **envp, t_list *env)
{
	char *cmd_path;
    if (next != NULL)
        dup2(cmd->fd[1], STDOUT_FILENO);
    if (prev != NULL)
        dup2(prev->fd[0], STDIN_FILENO);
    redirect(cmd);
	cmd_path = try_acces(cmd->args[0], env);
	//printf("%s\n", cmd_path);
    execve(cmd_path, cmd->args, envp);
    printf("execve failed for test : %s\n", cmd->args[0]);
    exit(1);
    return (1);
}

int exec_cmd(t_cmd *cmd, t_cmd *prev, t_cmd *next_cmd, char **envp, t_list *env)
{
    pid_t pid;
    int status;

    pipe(cmd->fd);
    pid = fork();
    if (pid == 0)
        execute_cmd(cmd, prev, next_cmd, envp, env);
    else
    {
        waitpid(pid, &status, 0);
        close(cmd->fd[1]);
        if (prev)
			close(prev->fd[0]);
        if (!next_cmd)
            close (cmd->fd[0]);
    }
    return (1);
}

int exec_cmds(t_list *lst, char **envp, t_list *env)
{
	t_cmd *prev;
    t_cmd *next;
    t_cmd *cmd;

	prev = NULL;
    next = NULL;
    while (lst)
    {
        cmd = lst->content;
        next = (t_cmd *)lst->next;
        exec_cmd(cmd, prev, next, envp, env);
		prev = lst->content;
        lst = lst->next;
    }
    return (1);
}

