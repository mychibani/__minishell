/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:25:01 by caubry            #+#    #+#             */
/*   Updated: 2022/10/10 17:21:49 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_pipe(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (tmp)
		return (1);
	else
		return (0);
}

void	_error_prompt(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	**get_path(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (!__strncmp("PATH=", envp[i], 5))
			return (__split(&envp[i][5], ':'));
		i++;
	}
	return (NULL);
}

char	*pipex_join(char *path, char *instructions)
{
	int		i;
	int		j;
	int		size;
	char	*command_path;

	i = 0;
	j = 0;
	size = __strlen(path) + __strlen(instructions) + 2;
	command_path = (char *)malloc(sizeof(char) * (size));
	if (!command_path)
		return (NULL);
	while (path[i])
	{
		command_path[i] = path[i];
		i++;
	}
	command_path[i++] = '/';
	if (!instructions)
		return (free(command_path), NULL);
	while (instructions[j])
		command_path[i++] = instructions[j++];
	command_path[i] = '\0';
	return (command_path);
}

char	*find_command_path(t_pipe *data)
{
	char	**bin;
	char	*inst;
	int		i;

	i = 0;
	bin = data->elem->cmd;
	if (!bin[0])
		return (NULL);
	if (access(bin[0], F_OK) == 0)
		return (bin[0]);
	inst = pipex_join(".", bin[0]);
	if (access(inst, F_OK) == 0)
		return (inst);
	free(inst);
	if (!data->path)
		return (NULL);
	while (data->path[i])
	{
		inst = pipex_join(data->path[i++], bin[0]);
		if (access(inst, F_OK) == 0)
			return (inst);
		free(inst);
	}
	return (NULL);
}
