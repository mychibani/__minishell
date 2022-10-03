/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:33:40 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/03 14:07:27 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__exit(t_program_data *data, t_user_input *ui, int rv)
{
	(void)data;
	if (ui->test_env)
	{
		__env_clear(ui->test_env, free);
		free(ui->test_env);
	}
	if (ui->token)
		__lstclear(&ui->token, free);
	if (ui->lexer)
		__lexer_clear(&ui->lexer, free);
	printf("exit\n");
	exit(rv);
}
