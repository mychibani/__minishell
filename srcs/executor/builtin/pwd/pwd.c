/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:36:41 by caubry            #+#    #+#             */
/*   Updated: 2022/10/07 11:06:33 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getpwd(t_user_input *ui)
{
	t_env	*tmp;

	tmp = *(ui->test_env);
	while (tmp)
	{
		if (!__strcmp(tmp->name, "PWD"))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_pwd(t_user_input *ui)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = __strdup(ft_getpwd(ui));
	printf("%s\n", pwd);
	free(pwd);
}
