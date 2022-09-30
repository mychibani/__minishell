/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:07:31 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/30 15:14:55 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_size(char **env)
{
	int	size;

	size = 0;
	if (!env)
		return (0);
	while (env[size])
		size++;
	return (size);
}

int	get_env_var(t_program_data *data, char **env, int size)
{
	int	i;

	i = 0;
	data->envp = (char ***)malloc(sizeof(char **) * (size + 1));
	if (!data->envp)
		return (0);
	while (i < size)
	{
		data->envp[i] = (char **)malloc(sizeof(char *) * 3);
		data->envp[i][0] = __strdup(env[i]);
		data->envp[i][1] = __strdup("1");
		data->envp[i][3] = NULL);
		if (!data->envp[i][0])
			return (0);
		i++;
	}
	data->envp[i] = NULL;
	return (_SUCCESS_);
}

