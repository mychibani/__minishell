/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:52:10 by caubry            #+#    #+#             */
/*   Updated: 2022/10/03 14:14:09 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execve(char *cmd, char **argvec, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
		execve(cmd, argvec, env);
	else
		wait(NULL);
	ft_free(argvec, 0);
	free(cmd);
	return (1);
}

char	**ft_prep_arg(t_user_input *ui)
{
	char	**argvec;
	char	*tmparg;
	t_lexer	*tmplex;
	int		i;

	tmplex = ui->lexer;
	tmparg = NULL;
	i = 0;
	while (tmplex && tmplex->type == WORD)
	{
	tmparg = _strjoin(tmparg, tmplex->token);
	tmparg = _strjoin(tmparg, "\n");
	i++;
	tmplex = tmplex->next;
	}
	argvec = __split(tmparg, '\n');
	free(tmparg);
	i = 0;
	return (argvec);
}

int	ft_cmd(t_user_input *ui)
{
	char	*cmd;

	cmd = ui->lexer->token;
	if (!cmd)
		return (0);
	if (!(__strcmp(cmd, "echo")))
		ft_echo(ui);
	else if (!(__strcmp(cmd, "cd")))
		ft_cd(ui);
	else if (!(__strcmp(cmd, "pwd")))
		ft_pwd();
	else if (!(__strcmp(cmd, "export")))
		ft_export(ui, ui->lexer->next->token);
	else if (!(__strcmp(cmd, "unset")))
		ft_unset(ui);
	else if (!(__strcmp(cmd, "env")))
		ft_env(ui);
	else if (!(__strcmp(cmd, "exit")))
		ft_exit(ui);
	// else if ((ft_execve(_strjoin(__strdup("/usr/bin/"), cmd),
	// 			ft_prep_arg(ui), ui->test_env)) == -1)
		// printf("Command '%s' not found\n", cmd);
	return (1);
}
