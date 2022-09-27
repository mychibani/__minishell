/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:35:26 by caubry            #+#    #+#             */
/*   Updated: 2022/09/27 15:33:28 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_unsetvar(t_user_input *ui, int i)
{
    char    **new_env;
    int j;

    j = 0;
    while (ui->env[j])
        j++;
    new_env = malloc(sizeof(char *) * j);
    j = 0;
    while(j != i)
    {
        new_env[j] = ui->env[j];
        j++;
    }
    j++;
    while(ui->env[j])
    {
        new_env[j] = ui->env[i];
        j++;
    }
    ui->env = new_env;
}

void    ft_unset(t_user_input *ui)
{
    char    *var;
    char    *search;
    t_lexer *var_to_unset;
    int i;
    int exist;
    
    i = 0;
    exist = 0;
    var_to_unset = ui->lexer->next;
    while (var_to_unset && var_to_unset->type == WORD)
    {
        var = __strdup(var_to_unset->token);
        search = _strjoin(var, "=");
        while (ui->env[i] && !exist)
        {
            if (!(__strncmp(ui->env[i], search, __strlen(search))))
                exist = i;
            else
                i++;
        }
        if (exist)
            ft_unsetvar(ui,i);
        var_to_unset = var_to_unset->next;
    }
}