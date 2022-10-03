/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:21:14 by caubry            #+#    #+#             */
/*   Updated: 2022/10/03 19:21:00 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cdhome(char *cd)
{
	if (!(__strcmp(cd, "--")))
		return (1);
	if (!(__strcmp(cd, "~")))
		return (1);
	return (0);
}

void	ft_cd(t_user_input *ui)
{
	t_lexer	*path;
	char	*oldpwd;
	char	*pwd;
	char	*test;
	
	path = ui->lexer->next;
	test = getcwd(NULL, 0);
	oldpwd = _strjoin(__strdup("oldpwd="), test);
	free(test);
	ft_export_arg(ui, oldpwd);
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
	test = getcwd(NULL, 0);
	pwd = _strjoin(__strdup("pwd="), test);
	ft_export_arg(ui, pwd);
	free(test);
	free(pwd);
	free(oldpwd);
}
