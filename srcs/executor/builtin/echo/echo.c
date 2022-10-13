/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:36:31 by caubry            #+#    #+#             */
/*   Updated: 2022/10/11 11:41:45 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str, int i, char *quote)
{
	if (__strchr("'\"", str[i])
		&& (*quote == 0 || *quote == str[i]))
	{
		if (*quote == 0)
		{
			*quote = str[i];
		}
		else
			*quote = 0;
		i++;
	}
	return (i);
}

int	edit_quote(char *str, int i, char *quote)
{
	if (str[i] && str[i] == *quote)
	{
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
		i = edit_quote(str, i, &quote);
	}
	no_quote[j] = '\0';
	// free (str);
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
			echo_content = __strjoin(echo_content, " ");
		echo_arg->token = remove_quote(echo_arg->token);
		echo_content = __strjoin(echo_content, echo_arg->token);
		free(echo_arg->token);
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
	int		i;

	flg = 0;
	i = 2;
	echo_arg = ui->lexer->next;
	print_echo = NULL;
	if (!echo_arg)
		print_echo = __strdup("");
	while (echo_arg && echo_arg->token && !__strncmp(echo_arg->token, "-n", 2))
	{
		while (*(echo_arg->token) + i == 'n')
			i++;
		if (!*(echo_arg->token) + i)
		{
			echo_arg = echo_arg->next;
			flg = 1;
		}
	}
	if (echo_arg)
		print_echo = fill_print_echo(echo_arg);
	else
		print_echo = __strdup("");
	if (!flg)
		print_echo = __strjoin(print_echo, "\n");
	__putstr_fd(print_echo, STDOUT_FILENO);
	free(print_echo);
}

char	*fill_print_echo_pipe(char **s)
{
	char	*echo_content;
	char	*echo_arg;
	int		j;

	j = 0;
	echo_content = NULL;
	echo_arg = s[j];
	while (s[j])
	{
		if (j > 0)
			echo_content = __strjoin(echo_content, " ");
		echo_arg = remove_quote(echo_arg);
		echo_content = __strjoin(echo_content, echo_arg);
		free(echo_arg);
		if (!echo_content)
			return (NULL);
		j++;
		echo_arg = s[j];
	}
	return (echo_content);
}

void	ft_echo_pipe(char **cmd)
{
	int		flg;
	char	*print_echo;
	char	*echo_arg;
	int		i;
	int		j;

	flg = 0;
	i =	2;
	j = 1;
	echo_arg = cmd[j];
	print_echo = NULL;
	if (!echo_arg)
		print_echo = __strdup("");
	while (echo_arg && !__strncmp(echo_arg, "-n", 2))
	{
		while (*(echo_arg) + i == 'n')
			i++;
		if (!*(echo_arg) + i)
		{
			j++;
			echo_arg = cmd[j];
			flg = 1;
		}
	}
	if (echo_arg)
		print_echo = fill_print_echo_pipe(cmd + j);
	if (!flg)
		print_echo = __strjoin(print_echo, "\n");
	__putstr_fd(print_echo, STDOUT_FILENO);
	free(print_echo);
}

