#include "minishell.h"

void	ft_env(t_user_input *ui)
{
    int i;
    char **env;

    i = 0;
    env = ui->env;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}