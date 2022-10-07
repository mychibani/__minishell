/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:21:14 by caubry            #+#    #+#             */
/*   Updated: 2022/10/07 11:04:49 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_home(t_user_input *ui)
{
	int		exist;
	t_env	*tmp;

	exist = 0;
	tmp = *(ui->test_env);
	while (tmp && !exist)
	{
		if (!__strncmp(tmp->name, "HOME", 4))
			exist = 1;
		tmp = tmp->next;
	}
	if (exist)
		chdir(getenv("HOME"));
	else
		printf("cd: HOME not set\n");
}

void	ft_check_oldpwd(t_env *tmp)
{
	while (tmp)
	{
		if (!__strncmp(tmp->name, "OLDPWD", 6))
			break ;
		tmp = tmp->next;
	}
	if (tmp && tmp->value)
	{
		printf("%s\n", tmp->value);
		chdir(tmp->value);
	}
	else
		printf("cd: OLDPWD not set\n");
}

void	ft_apply_cd(t_lexer *path, t_user_input *ui)
{
	t_env	*tmp;

	tmp = *(ui->test_env);
	if (path->next && path->next->type == WORD)
		return ;
	if (ft_cdhome(path->token))
		ft_check_home(ui);
	else if (ft_cdpwd(path->token))
		ft_check_oldpwd(tmp);
	else
		chdir(path->token);
}

void	ft_cd(t_user_input *ui)
{
	t_lexer	*path;
	char	*oldpwd;
	char	*pwd;
	char	*test;

	path = ui->lexer->next;
	if (path && path->next && path->next->type == WORD)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	test = getcwd(NULL, 0);
	if (!test)
		test = __strdup(ft_getpwd(ui));
	oldpwd = __strjoin(__strdup("OLDPWD="), test);
	free(test);
	if (!path)
		ft_check_home(ui);
	else
		ft_apply_cd(path, ui);
	ft_changevar(ft_find_var("OLDPWD", ui->test_env), oldpwd);
	test = getcwd(NULL, 0);
	pwd = __strjoin(__strdup("PWD="), test);
	ft_changevar(ft_find_var("PWD", ui->test_env), pwd);
	free(test);
	free(pwd);
	free(oldpwd);
}
