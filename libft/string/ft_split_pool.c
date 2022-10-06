/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:17:05 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/06 12:59:34 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_charset(char	c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strdup_charset(char	*str, char *sep)
{
	int		i;
	char	*final_str;

	i = 0;
	while (str[i] && !ft_is_charset(str[i], sep))
		i++;
	final_str = (char *)malloc(sizeof(char) * i + 1);
	if (!(final_str))
		return (0);
	i = 0;
	while (str[i] && !ft_is_charset(str[i], sep))
	{
		final_str[i] = str[i];
		i++;
	}
	final_str[i] = '\0';
	return (final_str);
}

static int	ft_compute_size(char *str, char *sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!sep)
		return (1);
	while (str[i])
	{
		if (!ft_is_charset(str[i], sep) && str[i])
		{
			while (!ft_is_charset(str[i], sep) && str[i])
				i++;
			count++;
		}
		while (ft_is_charset(str[i], sep) && (str[i]))
			i++;
	}
	return (count);
}

static char	**ft_return_malloc_s(int size)
{
	char	**final_tab;

	final_tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!(final_tab))
		return (0);
	final_tab[0] = 0;
	return (final_tab);
}

char	**__split_pool(char *str, char *sep)
{
	int		i;
	int		j;
	char	**final_tab;
	int		size;

	i = 0;
	j = 0;
	size = ft_compute_size(str, sep);
	final_tab = ft_return_malloc_s(size);
	while (j < size)
	{
		if (str[i])
		{
			if (!ft_is_charset(str[i], sep))
			{
				final_tab[j++] = ft_strdup_charset(str + i, sep);
				while (!ft_is_charset(str[i], sep) && str[i])
					i++;
			}
		}
		while (ft_is_charset(str[i], sep) && str[i])
			i++;
	}
	final_tab[j] = 0;
	return (final_tab);
}
