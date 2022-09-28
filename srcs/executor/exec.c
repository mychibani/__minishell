#include "minishell.h"

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
    i = 0;
    return (argVec);
}

int	ft_cmd(t_user_input *ui)
{
    char *cmd;
    char    **argVec;

    cmd = ui->lexer->token;
    argVec = ft_prep_arg(ui);
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
    // else if (ft_strncmp(cmd, "exit"))
    //     ft_exit(cmd);
	else if (execve(_strjoin(__strdup("/usr/bin/"), cmd), \
            argVec, ui->env) == -1)
		printf("Command '%s' not found\n", cmd);
	return (1);
}
