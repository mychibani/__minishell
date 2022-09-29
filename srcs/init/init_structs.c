/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:33:33 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/29 13:16:42 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program_data	*init_data_struct(t_program_data *data, char **env)
{
	data->all_inputs = NULL;
	data->token = NULL;
	data->ui = NULL;
	data->env = env;
	return (data);
}

t_user_input	*init_user_input_struct(t_user_input *ui)
{
	ui->token = NULL;
	ui->to_tokenize = NULL;
	ui->ret_hd = 0;
	ui->ret_token = 0;
	ui->error_delim = NULL;
	ui->lexer = NULL;
	return (ui);
}

void	__init_structs(t_program_data *data, t_user_input *ui, char **env)
{
	init_data_struct(data, env);
	// __memset(&data, 0, sizeof(data));
	init_user_input_struct(ui);
	ui->test_env = ft_split_env(data->env);
	ui->env = data->env;
	__memset(&data, 0, sizeof(data));
}
