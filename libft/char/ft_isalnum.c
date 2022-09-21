/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:25:45 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/10 12:45:37 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	__isalnum(int c)
{
	if (__isdigit(c))
		return (1);
	if (__isalpha(c))
		return (1);
	return (0);
}
