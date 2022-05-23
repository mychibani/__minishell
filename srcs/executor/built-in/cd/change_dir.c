#include "minishell.h"

int change_directory(char **args, char *path)
{
    char *actual_dir; //recuperer grace a jujules

    actual_dir = NULL;
    // g_status = 0;

    if (args && args[1] && args[2])
        return (ft_putstr_fd("minishell: cd: too many argumetns\n",2), 1);
    chdir(path);
    perror(path);
    return (2);
}
