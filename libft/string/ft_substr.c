/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:20:02 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/10 12:47:54 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*__substr(char const *s, unsigned int start, size_t len)
{
	char			*final_str;
	unsigned int	len_tot;

	if (!s)
		return (0);
	if (__strlen(s) < start)
		return (__strdup(""));
	len_tot = __strlen(s + start);
	if (len_tot < len)
		len = len_tot;
	final_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(final_str))
		return (0);
	__strlcpy(final_str, s + start, len + 1);
	return (final_str);
}
