/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:56:39 by caubry            #+#    #+#             */
/*   Updated: 2022/10/06 12:35:53 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_check_code(char *code)
{
	int	i;

	i = 0;
	while (code[i])
	{
		if (!ft_isdigit((int)code[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_user_input *ui)
{
	int	exit_code;
	int	num;
	int	arg;

	num = 1;
	arg = 1;
	if (!ui->lexer->next)
		exit_code = 0;
	else if (ft_check_code(ui->lexer->next->token))
		exit_code = __atoi(ui->lexer->next->token);
	else
		num = 0;
	if (ui->lexer->next && ui->lexer->next->next)
		arg++;
	printf("exit\n");
	if (!num)
		printf("exit : numeric argument required\n");
	else if (arg > 1)
	{
		printf("exit : too many arguments\n");
		return ;
	}
	exit(exit_code);
}
