#include "minishell.h"

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
        ft_export(ui);
    else if (!(__strcmp(cmd, "unset")))
        ft_unset(ui);
    else if (!(__strcmp(cmd, "env")))
        ft_env(ui);
    // else if (ft_strncmp(cmd, "exit"))
    //     ft_exit(cmd);
	else
		printf("Command '%s' not found\n", cmd);
	return (1);
}
