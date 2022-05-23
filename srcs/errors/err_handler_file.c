/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:58:30 by ychibani          #+#    #+#             */
/*   Updated: 2022/05/23 14:08:40 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_dir_dont_exist(char *failed_path)
{
	ft_putstr_fd("minishell: cd", 2);
	ft_putstr_fd(failed_path, 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putchar_fd('\n');
	//exit status = 127
}

void	ft_print_cannot_open_dir(char *failed_path)
{
	ft_putstr_fd("minishell: cd", 2);
	ft_putstr_fd(failed_path, 2);
	ft_putstr_fd(": Permission denied", 2);
	ft_putchar_fd('\n');
	//exxit status = 1;
}

void	ft_print_is_not_dir(char *failed_path)
{
	ft_putstr_fd("minishell: cd", 2);
	ft_putstr_fd(failed_path, 2);
	ft_putstr_fd(": Not a directory", 2);
	ft_putchar_fd('\n');
	//exit status = 1
}
