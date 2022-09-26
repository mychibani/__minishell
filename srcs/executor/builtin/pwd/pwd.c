#include "minishell.h"

void	ft_pwd(t_user_input *ui)
{
    (void) *ui;
    printf("%s\n", getenv("PWD"));
}
