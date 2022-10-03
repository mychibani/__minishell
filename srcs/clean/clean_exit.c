/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:33:40 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/03 11:00:00 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_env(t_program_data *data)
{
	int	i;

	i = 0;
	if (!data->envp)
		return ;
	while (data->envp[i])
	{
		free(data->envp[i][0]);
		free(data->envp[i][1]);
		free(data->envp[i]);
		i++;
	}
	free(data->envp);
}

void	__exit(t_program_data *data, t_user_input *ui, int rv)
{
	destroy_env(data);
	(void)ui;
	exit(rv);
}
