#include "minishell.h"

int ft_execve(char *cmd, char **argVec, char **env)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return -1;
    }
    else if (pid == 0)
        execve(cmd, argVec, env);
    else
        wait(NULL);
    ft_free(argVec, 0);
    free(cmd);
    return 1;
}

char    **ft_prep_arg(t_user_input *ui)
{
    char    **argVec;
    char    *tmparg;
    t_lexer *tmplex;
    int i;

    tmplex = ui->lexer;
    tmparg = NULL;
    i = 0;
    while (tmplex && tmplex->type == WORD)
    {
        tmparg = _strjoin(tmparg, tmplex->token);
        tmparg = _strjoin(tmparg, "\n");
        i++;
        tmplex = tmplex->next;
    }
    argVec = __split(tmparg, '\n');
    free(tmparg);
    i = 0;
    return (argVec);
}

int	ft_cmd(t_user_input *ui)
{
    char *cmd;

    cmd = ui->lexer->token;
	if (!cmd)
		return (0);
	if (!(__strcmp(cmd, "echo")))
		ft_echo(ui);
    else if (!(__strcmp(cmd, "cd")))
        ft_cd(ui);
    else if (!(__strcmp(cmd, "pwd")))
        ft_pwd(ui);
    else if (!(__strcmp(cmd, "export")))
        ft_export(ui, ui->lexer->next->token);
    else if (!(__strcmp(cmd, "unset")))
        ft_unset(ui);
    else if (!(__strcmp(cmd, "env")))
        ft_env(ui);
    else if (!(__strcmp(cmd, "exit")))
        ft_exit(ui);
	else if ((ft_execve(_strjoin(__strdup("/usr/bin/"), cmd), 
            ft_prep_arg(ui), ui->env)) == -1)
            printf("Command '%s' not found\n", cmd);
	return (1);
}
