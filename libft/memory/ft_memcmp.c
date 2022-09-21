/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:07:45 by ychibani          #+#    #+#             */
/*   Updated: 2021/11/23 14:03:38 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	__memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] == str2[i] && i < n - 1)
		i++;
	if (i < n)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}
