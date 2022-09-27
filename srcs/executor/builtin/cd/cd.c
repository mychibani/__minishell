/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:38:48 by caubry            #+#    #+#             */
/*   Updated: 2022/09/27 13:09:03 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cdhome(char *cd)
{
    if (!(__strcmp(cd, "--")))
        return (1);
    if (!(__strcmp(cd, "~")))
        return (1);
    return (0);
}

void    ft_cd(t_user_input *ui)
{
    (void) *ui;
    t_lexer *path;

    path = ui->lexer->next;
    if (!path)
        chdir(getenv("HOME"));
    else
    {
        if (path->next && path->next->type == WORD)
            return ;
        if (ft_cdhome(path->token))
            path->token = __strdup(getenv("HOME"));
        chdir(path->token);
    }
}