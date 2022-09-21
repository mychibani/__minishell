/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:18:31 by ychibani          #+#    #+#             */
/*   Updated: 2021/11/23 15:53:33 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	__is_charset(char *sep, char c)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	__calculate_str(char *str, char *sep)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = __strlen(str) - 1;
	len = 0;
	while (__is_charset(sep, str[i]) && str[i++])
		len++;
	if (!str[i])
		return (__strlen(str) - (len));
	while (__is_charset(sep, str[j]) && str[j--])
		len++;
	return ((__strlen(str) - len));
}

char	*__strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		size;
	char	*final_str;

	i = 0;
	j = 0;
	if (!s1)
		return (0);
	size = __calculate_str((char *)s1, (char *)set);
	if (!set)
		return (__strdup(s1));
	final_str = (char *)malloc(sizeof(char) * size + 1);
	if (!(final_str))
		return (0);
	while (s1[i] && __is_charset((char *)set, s1[i]))
		i++;
	while (j < size)
	{
		final_str[j] = s1[i];
		i++;
		j++;
	}
	final_str[j] = 0;
	return (final_str);
}
