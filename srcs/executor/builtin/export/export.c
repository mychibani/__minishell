/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:24:20 by caubry            #+#    #+#             */
/*   Updated: 2022/09/27 14:47:04 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_setvar(t_user_input *ui, char *name, char *value)
{
    char    **new_env;
    int i;

    i = 0;
    while (ui->env[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 2));
    i = 0;
    while (ui->env[i])
    {
        new_env[i] = __strdup(ui->env[i]);
        i++;
    }
    new_env[i] = _strjoin(name,"=");
    new_env[i] = _strjoin(new_env[i], value);
    ui->env = new_env;
    return (ui->env[i]);
}

char    *ft_changevar(t_user_input *ui, char *name, char *value, int i)
{
    ui->env[i] = _strjoin(name,"=");
    ui->env[i] = _strjoin(ui->env[i], value);
    printf("new var = %s\n", ui->env[i]);
    return (ui->env[i]);
}

void    ft_export(t_user_input *ui)
{
    char    **var;
    char    *search;
    char    *tmp;
    int i;
    int exist;
    
    i = 0;
    exist = 0;
    var = __split(ui->lexer->next->token, '=');
    tmp = __strdup(var[0]);
    search = _strjoin(tmp, "=");
    while (ui->env[i] && !exist)
    {
        if (!(__strncmp(ui->env[i], search, __strlen(search))))
            exist = i;
        else
            i++;
    }
    if (exist)
        ui->env[i] = ft_changevar(ui,var[0], var[1],i);
    else
        ui->env[i] = ft_setvar(ui,var[0], var[1]);
}