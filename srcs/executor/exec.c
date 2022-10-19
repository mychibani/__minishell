/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:52:10 by caubry            #+#    #+#             */
/*   Updated: 2022/10/19 08:33:08 by ychibani         ###   ########.fr       */
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

void	del_hds(t_cmd_list *cmd_list)
{

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

int	get_nb_cmd(t_cmd_list *cmd_list)
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

int	init_seq(t_cmd_list *cmd, t_program_data *data, int fds[2], t_user_input *ui)
{
	
}

int	handle_redir(t_cmd_list *cmd)
{
	t_cmd_list *save;

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

int	__execute_sequence(t_cmd_list *save, t_program_data *data, t_user_input *ui)
{
	int			fds[2];

	if (get_nb_cmd(save) == 1 || is_builtin(save->arg))
	{
		if (save->redirect)
		{
			if (!__save_fds(fds))
				return (cmd_list_free(save), 0);
			if (!handle_redir(save))
				return (del_hds(save), cmd_list_free(save), 0);
		}
		exec_builtin(save->arg, data, save, 0);
		if (save->redirect && !__restore_fds(fds))
			perror("restore failed :");
		return (del_hd(save), cmd_list_free(save), data->rv);
	}
	if (!init_seq(save, data, fds, ui))
		return (cmd_list_free(&save), __putstr_fd("Malloc Err", 2), 0);
	// data->rv = exec;
	return (del_hd(save));
}