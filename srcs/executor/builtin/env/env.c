/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:36:36 by caubry            #+#    #+#             */
/*   Updated: 2022/10/06 12:39:31 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

char	**ft_collect_env(int *no_env, t_user_input *ui, char **env)
{
	char	**collect_env;
	char	*pwd;
	char	*var_pwd;
	char	*shlvl;

	collect_env = env;
	if (!*env)
	{
		*no_env = 1;
		pwd = getcwd(NULL, 0);
		var_pwd = __strjoin(__strdup("PWD="), pwd);
		free(pwd);
		shlvl = __strdup("SHLVL=1");
		ui->test_env = malloc(sizeof(t_env) * 5);
		if (!ui->test_env)
			return (NULL);
		*(ui->test_env) = NULL;
		__env_lstadd_back(ui->test_env, ft_init_env("OLDPWD"));
		__env_lstadd_back(ui->test_env, ft_init_env(var_pwd));
		__env_lstadd_back(ui->test_env, ft_init_env(shlvl));
		__env_lstadd_back(ui->test_env, ft_init_env("_=/usr/bin/env"));
		free(var_pwd);
		free(shlvl);
	}
	return (collect_env);
}

t_env	*ft_init_env(char *var_to_split)
{
	char	*name;
	char	*value;
	t_env	*env;
	int		length_name;
	int		length_value;

	length_name = ft_var_length(var_to_split);
	length_value = __strlen(var_to_split) - length_name - 1;
	name = malloc(sizeof(char) * length_name + 1);
	if (!name)
		return (NULL);
	name = __strncpy(name, var_to_split, length_name);
	if ((size_t)length_name == __strlen(var_to_split))
	{
		env = __lst_env_new(name, NULL, 0);
		return (env);
	}
	value = malloc(sizeof(char) * length_value + 1);
	if (!value)
		return (NULL);
	value = __strncpy(value, var_to_split + length_name + 1, length_value);
	env = __lst_env_new(name, value, 1);
	return (env);
}

t_env	**ft_split_env(char	**env)
{
	t_env	**list_env;
	int		i;

	i = 0;
	list_env = malloc(sizeof(t_env) * (ft_size(env) + 1));
	if (!list_env)
		return (NULL);
	*list_env = NULL;
	while (env[i])
	{
		if (!*list_env)
			*list_env = ft_init_env(env[i]);
		else
			__env_lstadd_back(list_env, ft_init_env(env[i]));
		i++;
	}
	return (list_env);
}

void	ft_env(t_user_input *ui)
{
	t_env	*env;

	env = *(ui->test_env);
	while (env)
	{
		if (env->env == 1)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return ;
}
