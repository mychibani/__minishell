/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:36:37 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/11 15:13:19 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_quote(char *s, char *to_find)
{
	int		i;
	t_state	q_state;

	q_state = 0;
	i = 0;
	while (s[i] && &s[i] != to_find)
	{
		q_state = return_quoted_state(s[i], q_state, 0);
		i++;
	}
	if (__strchr("\'\"", s[i]))
		q_state = return_quoted_state(s[i], q_state, 0);
	return (q_state != UNQUOTED);
}

int	get_strs_size(char *s, char *charset)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (!is_charset(s[i], charset))
		{
			while ((s[i]) && (!is_charset(s[i], charset)
					|| in_quote(s, &s[i])))
				i++;
			size++;
		}
		else
			i++;
	}
	return (size);
}

char	**strs_malloc(int size)
{
	char	**final_tab;

	final_tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!(final_tab))
		return (0);
	final_tab[0] = 0;
	return (final_tab);
}

char	*unquoted_dup(char *s, char *charset)
{
	int		i;
	char	*final_str;

	i = 0;
	while (s[i] && (!is_charset(s[i], charset) || in_quote(s, &s[i])))
		i++;
	final_str = (char *)malloc(sizeof(char) * (i + 1));
	if (!final_str)
		return (NULL);
	i = 0;
	while (s[i] && (!is_charset(s[i], charset) || in_quote(s, &s[i])))
	{
		final_str[i] = s[i];
		i++;
	}
	final_str[i] = '\0';
	return (final_str);
}

char	**unquoted_char_split(char *s, char *charset)
{
	int		i;
	int		j;
	int		size;
	char	**strs;

	i = 0;
	j = 0;
	size = get_strs_size(s, charset);
	strs = strs_malloc(size);
	while (j < size)
	{
		if (s[i] && (!is_charset(s[i], charset) || in_quote(s, &s[i])))
		{
			strs[j++] = unquoted_dup(s + i, charset);
			while ((in_quote(s, &s[i]) || !is_charset(s[i], charset)) && s[i])
				i++;
		}
		while ((is_charset(s[i], charset) || in_quote(s, &s[i])) && s[i])
			i++;
	}
	strs[j] = 0;
	return (strs);
}
