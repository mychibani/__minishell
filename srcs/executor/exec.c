/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:52:10 by caubry            #+#    #+#             */
/*   Updated: 2022/10/10 13:37:21 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_list(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (i);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**ft_list_to_chr(t_env **env)
{
	t_env	*tmp;
	char	**env_exec;
	char	*value;
	int		i;

	tmp = *env;
	i = 0;
	env_exec = malloc(sizeof(char *) * (ft_size_list(tmp) + 2));
	if (!env_exec)
		return (NULL);
	env_exec[0] = 0;
	tmp = *env;
	while (tmp)
	{
		env_exec[i] = __strjoin(__strdup(tmp->name), "=");
		value = __strdup(tmp->value);
		env_exec[i] = __strjoin(env_exec[i], value);
		printf("env_exec = %s\n", env_exec[i]);
		free(value);
		i++;
		tmp = tmp->next;
	}
	env[i] = 0;
	return (env_exec);
}

int	ft_execve(char *cmd, char **argvec, char **env)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (!access(cmd, X_OK))
			execve(cmd, argvec, env);
		else
		{
			path = __strjoin(__strdup("/usr/bin/"), cmd);
			execve(path, argvec, env);
			free(path);
		}
		exit (EXIT_SUCCESS);
	}
	else
		wait(NULL);
	ft_free(argvec, 0);
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
		tmparg = __strjoin(tmparg, tmplex->token);
		tmparg = __strjoin(tmparg, "\n");
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
		ft_pwd(ui);
	else if (!(__strcmp(cmd, "export")))
		ft_choose_export(ui);
	else if (!(__strcmp(cmd, "unset")))
		ft_unset(ui);
	else if (!(__strcmp(cmd, "env")))
		ft_env(ui);
	else if (!(__strcmp(cmd, "exit")))
		ft_exit(ui);
	else if (ft_execve(cmd, ft_prep_arg(ui), ui->env) == -1)
		printf("Command '%s' not found\n", cmd);
	return (1);
}

int	ft_cmd_pipe(t_user_input *ui, char **cmd)
{
	if (!cmd)
		return (0);
	if (!(__strcmp(cmd[0], "echo")))
		ft_echo_pipe(cmd);
	else if (!(__strcmp(cmd[0], "cd")))
		ft_cd(ui);
	else if (!(__strcmp(cmd[0], "pwd")))
		ft_pwd(ui);
	else if (!(__strcmp(cmd[0], "export")))
		ft_choose_export(ui);
	else if (!(__strcmp(cmd[0], "unset")))
		ft_unset(ui);
	else if (!(__strcmp(cmd[0], "env")))
		ft_env(ui);
	else if (!(__strcmp(cmd[0], "exit")))
		ft_exit(ui);
	else
		return (0);
	return (1);
}

