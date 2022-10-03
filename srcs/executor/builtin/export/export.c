/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:24:20 by caubry            #+#    #+#             */
/*   Updated: 2022/10/03 14:21:28 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **to_free, int i)
{
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

// char	**ft_setvar(t_user_input *ui, char *name, char *value)
// {
// 	char	**new_env;
// 	int		i;

// 	i = 0;
// 	while (ui->test_env[i])
// 		i++;
// 	new_env = malloc(sizeof(char *) * (i + 2));
// 	i = 0;
// 	while (ui->env[i])
// 	{
// 		new_env[i] = __strdup(ui->test_env[i]);
// 		i++;
// 	}
// 	new_env[i] = _strjoin(name, "=");
// 	new_env[i] = _strjoin(test_env[i], value);
// 	new_env[i + 1] = NULL;
// 	return (new_env);
// }

// char	*ft_changevar(t_user_input *ui, char *name, char *value, int i)
// {
// 	ui->env[i] = _strjoin(name, "=");
// 	ui->env[i] = _strjoin(ui->env[i], value);
// 	return (ui->env[i]);
// }

// void	ft_export(t_user_input *ui, char *to_set)
// {
// 	char	**var;
// 	char	*search;
// 	char	*tmp;
// 	int		i;
// 	int		exist;
// 	t_env	*new;
// 	char	*name;
// 	char	*value;
	
// 	i = 0;
// 	exist = 0;
// 	var = __split(to_set, '=');
// 	tmp = __strdup(var[0]);
// 	search = _strjoin(tmp, "=");
// 	while (ui->env[i] && !exist)
// 	{
// 		if (!(__strncmp(ui->env[i], search, __strlen(search))))
// 			exist = i;
// 		else
// 			i++;
// 	}
// 	if (exist)
// 		ui->env[i] = ft_changevar(ui, var[0], var[1], i);
// 	else
// 		ui->env = ft_setvar(ui, var[0], var[1]);
// 	free(search);
// 	ft_free(var, 1);
// }




void	ft_changevar(t_env *env, char *var_to_split)
{
	char	*name;
	char	*value;
	int		length_name;
	int		length_value;
	
	free(env->name);
	free(env->value);
	length_name = ft_var_length(var_to_split);
	length_value = __strlen(var_to_split) - length_name - 1;
	name = malloc(sizeof(char) * length_name + 1);
	value = malloc(sizeof(char) * __strlen(var_to_split) - length_name);
	if (!name || !value)
		return ;
	name = __strncpy(name, var_to_split, length_name);
	value = __strncpy(value, var_to_split + length_name + 1, length_value);
	env->name = name;
	env->value = value;
}

int	ft_var_length(char	*var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (-1);
	return (i);
}

void	ft_export(t_user_input *ui, char *to_set)
{
	t_env	*search;
	
	search = *(ui->test_env);
	while (search)
	{
		if (!(__strncmp(search->name, to_set, ft_var_length(to_set))))
		{
			ft_changevar(search, to_set);
			return ;
		}
		search = search->next;
	}
	__env_lstadd_back(ui->test_env, ft_init_env(to_set));
}
