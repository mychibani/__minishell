/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __treat_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:43:52 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/09 14:29:38 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__treat_format(t_struct *content, va_list argument)
{
	if (content->conversion == 'd' || content->conversion == 'i')
		__putnbr(va_arg(argument, int), content);
	else if (content->conversion == 'c')
		__putchar(va_arg(argument, int), content);
	else if (content->conversion == 's')
		__putstr(va_arg(argument, char *), content);
	else if (content->conversion == 'p')
		__print_memory(va_arg(argument, void *), content);
	else if (content->conversion == 'x')
		__base((unsigned long long)va_arg(argument, unsigned int), M, content);
	else if (content->conversion == 'u')
		__base((unsigned long long)va_arg(argument, unsigned int), D, content);
	else if (content->conversion == 'X')
		__base((unsigned long long)va_arg(argument, unsigned int), R, content);
	else if (content->conversion == '%')
		__putchar('%', content);
	else
		return ;
}
