/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:21:14 by caubry            #+#    #+#             */
/*   Updated: 2022/10/04 15:58:39 by caubry           ###   ########.fr       */
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

t_env	*ft_find_var(char	*name, t_env **env)
{
	t_env	*var;

	var = *env;
	while (var && __strcmp(var->name, name))
		var = var->next;
	if (!var)
		return (NULL);
	return (var);
}

void	ft_cd(t_user_input *ui)
{
	t_lexer	*path;
	char	*oldpwd;
	char	*pwd;
	char	*test;

	path = ui->lexer->next;
	test = getcwd(NULL, 0);
	oldpwd = __strjoin(__strdup("OLDPWD="), test);
	free(test);
	ft_changevar(ft_find_var("OLDPWD", ui->test_env), oldpwd);
	if (!path)
		chdir(getenv("HOME"));
	else
	{
		if (path->next && path->next->type == WORD)
			return ;
		if (ft_cdhome(path->token))
		{
			free(path->token);
			path->token = __strdup(getenv("HOME"));
		}
		chdir(path->token);
	}
	test = getcwd(NULL, 0);
	pwd = __strjoin(__strdup("PWD="), test);
	ft_changevar(ft_find_var("PWD", ui->test_env), pwd);
	free(test);
	free(pwd);
	free(oldpwd);
}
