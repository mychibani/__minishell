/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:52:10 by caubry            #+#    #+#             */
/*   Updated: 2022/10/25 19:48:29 by ychibani         ###   ########.fr       */
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

int	restore_fds(int fds[2])
{
	if (dup2(STDIN_FILENO, fds[0]) < 0)
		return (-1);
	if (dup2(STDOUT_FILENO, fds[1]) < 0)
		return (-1);
	if (close(fds[0]))
		return (-1);
	if (close(fds[1]))
		return (-1);
	return (1);
}

int	__save_fds(int fds[2])
{
	fds[0] = dup(STDIN_FILENO);
	fds[1] = dup(STDOUT_FILENO);
	if (fds[1] < 0 || fds[0] < 0)
		return (-1);
	return (1);
}




int	del_hds(t_cmd *cmd)
{
	t_redirect	*save;
	char		*tmp;

	while (cmd)
	{
		save = cmd->redirect;
		while (cmd->redirect)
		{
			if (cmd->redirect->type == HD)
			{
				tmp = __get_name(cmd->index);
				if (!tmp)
					return (0);
				unlink(tmp);
				free(tmp);
				break ;
			}
			cmd->redirect = cmd->redirect->next;
		}
		cmd->redirect = save;
		cmd = cmd->next;
	}
	return (1);
}

int	__is_builtin(char **arg)
{
	if (!arg || !arg[0])
		return (0);
	if (!__strcmp(arg[0], "echo"))
		return (1);
	if (!__strcmp(arg[0], "cd"))
		return (1);
	if (!__strcmp(arg[0], "pwd"))
		return (1);
	if (!__strcmp(arg[0], "env"))
		return (1);
	if (!__strcmp(arg[0], "export"))
		return (1);
	if (!__strcmp(arg[0], "unset"))
		return (1);
	if (!__strcmp(arg[0], "exit"))
		return (1);
	return (0);
}

int	get_nb_cmd_in_cmd(t_cmd *cmd_list)
{
	int	i;

	i = 0;
	while (cmd_list)
	{
		if (cmd_list)
			i++;
		cmd_list = cmd_list->next;
	}
	return (i);
}

int	__find_path(char **envp)
{
	int	i;

	i = 0;
	if (!envp && !envp[0])
		return (0);
	while (envp[i])
	{
		if (__strncmp(envp[i], "PATH", 5))
			return (1);
		i++;
	}
	return (0);
}

int	init_seq(t_cmd *cmd, t_program_data *data)
{
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
	cmd->index = 0;
	if (data->env && __find_path(data->env))
	{
		cmd->all_path = get_path(data->env);
		if (!cmd->path)
			return (0);
	}
	else
		cmd->path = NULL;
	return (1);
}

int	handle_redir(t_cmd *cmd)
{
	t_cmd *save;

	save = cmd;
	while (save->redirect)
	{
		if (save->redirect->type == LESS && !less_redirection(save))
			return (MALLOC_ERROR);
		if (save->redirect->type == GREAT && !great_redirection(save))
			return (MALLOC_ERROR);
		if (save->redirect->type == D_GREAT && !dgreat_redirection(save))
			return (MALLOC_ERROR);
		if (save->redirect->type == HD && !hd_redirection(save))
			return (MALLOC_ERROR);
		save->redirect = save->redirect->next;
	}
	return (1);
}

int	__execute_sequence(t_cmd *save, t_program_data *data)
{
	int			fds[2];

	if (get_nb_cmd_in_cmd(save) == 1 || __is_builtin(save->arg))
	{
		if (save->redirect)
		{
			if (!__save_fds(fds))
				return (cmd_list_free(&save), 0);
			if (!handle_redir(save))
				return (del_hds(save), cmd_list_free(&save), 0);
		}
		// exec_builtin(save->arg, data, save, 0);
		if (save->redirect && !restore_fds(fds))
			perror("restore failed :");
		// return (del_hds(save), cmd_list_free(save), data->rv);
	}
	if (!init_seq(save, data))
		return (cmd_list_free(&save), __putstr_fd("Malloc Err", 2), 0);
	// data->rv = launch_fork(data, save, save);
	return (del_hds(save));
}