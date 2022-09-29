/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:36:31 by caubry            #+#    #+#             */
/*   Updated: 2022/09/29 10:31:25 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str, int i, char *quote)
{
	if (__strchr("'\"", str[i])
		&& (*quote == 0 || *quote == str[i]))
	{
		if (*quote == 0)
			*quote = str[i];
		else
			*quote = 0;
		i++;
	}
	return (i);
}

char	*remove_quote(char *str)
{
	char	*no_quote;
	int		i;
	int		j;
	char	quote;

	no_quote = malloc(sizeof(char) * (__strlen(str) + 1));
	i = 0;
	j = 0;
	quote = 0;
	if (!no_quote)
		return (NULL);
	while (str[i])
	{
		i = check_quote(str, i, &quote);
		if (str[i] && str[i] != quote)
		{
			no_quote[j] = str[i];
			j++;
			i++;
		}
	}
	no_quote[j] = '\0';
	free (str);
	return (no_quote);
}

char	*fill_print_echo(t_lexer *lexer)
{
	char	*echo_content;
	t_lexer	*echo_arg;
	int		i;

	echo_content = NULL;
	echo_arg = lexer;
	i = 0;
	while (echo_arg)
	{
		if (i > 0)
			echo_content = _strjoin(echo_content, " ");
		echo_arg->token = remove_quote(echo_arg->token);
		echo_content = _strjoin(echo_content, echo_arg->token);
		if (!echo_content)
			return (NULL);
		echo_arg = echo_arg->next;
		i++;
	}
	return (echo_content);
}

void	ft_echo(t_user_input *ui)
{
	int		flg;
	char	*print_echo;
	t_lexer	*echo_arg;

	flg = 0;
	echo_arg = ui->lexer->next;
	while (echo_arg->token && !__strcmp(echo_arg->token, "-n"))
	{
		echo_arg = echo_arg->next;
		flg = 1;
	}
	print_echo = fill_print_echo(echo_arg);
	if (!flg)
		print_echo = _strjoin(print_echo, "\n");
	printf("%s", print_echo);
	free(print_echo);
}
