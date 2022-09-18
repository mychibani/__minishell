/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:33:40 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/18 19:36:50 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__exit(t_program_data *data, t_user_input *ui, int rv)
{
	(void)data;
	if (ui->token)
		__lstclear(&ui->token, free);
	__lexer_clear(&ui->lexer, free);
	printf("exit\n");
	exit(rv);
}
