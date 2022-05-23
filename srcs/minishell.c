#include "minishell.h"

int main(int ac, char **av, char **env)
{
    change_directory(av, av[1]);
    return (2);
}