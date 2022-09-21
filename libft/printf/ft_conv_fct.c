/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __conv_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 08:24:40 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/09 14:29:24 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__putchar(char c, t_struct *content)
{
	write(1, &c, 1);
	content->ret += 1;
}

void	__putstr(char *str, t_struct *content)
{
	int	i;

	i = 0;
	if (!str)
	{
		__putstr("(null)", content);
		return ;
	}
	while (str[i])
	{
		__putchar(str[i], content);
		i++;
	}
}

void	__base(unsigned long long nb, char *base, t_struct *content)
{
	unsigned long long	base_size;

	base_size = 0;
	while (base[base_size])
		base_size++;
	if (nb > base_size - 1)
		__base((nb / base_size), base, content);
	__putchar(base[nb % base_size], content);
}

void	__putnbr(int n, t_struct *content)
{
	long	nb;

	nb = n;
	if (n < 0)
	{
		nb *= -1;
		__putchar('-', content);
	}
	if (nb <= 9)
		__putchar(nb + 48, content);
	if (nb >= 10)
	{
		__putnbr(nb / 10, content);
		__putnbr(nb % 10, content);
	}
}

void	__print_memory(void *nb, t_struct *content)
{
	__putstr("0x", content);
	__base((unsigned long long)nb, M, content);
}
