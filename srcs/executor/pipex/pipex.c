/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:30:41 by caubry            #+#    #+#             */
/*   Updated: 2022/10/08 20:25:43 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	*bin = data->elem->cmd;
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


void	_clean_char_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	_clean_exit(t_pipe *data)
{
	clean(data);
	exit(0);
}

void	free_content(t_cmd **lst)
{
	// t_list	*move;

	// move = *lst;
	// if (!move)
	// 	return ;
	// while (move)
	// {
	// 	if (move->content)
	// 		_clean_char_tab(move->content);
	// 	move = move->next;
	// }
}

void	useless_fct(void *elem)
{
	(void)elem;
}

void	clean(t_pipe *data)
{
	t_list	*temp;

	temp = data->head;
	// if (data->limiter)
	// 	unlink("/tmp/heredoc.tmp");
	// if (data->path)
	// 	_clean_char_tab(data->path);
	// free_content(&temp);
	// ft_lstclear(&temp, useless_fct);
	// free(data->pid);
	// free(data);
}

int	_close_file_descriptors(int _first, int _second)
{
	if (_first > 0)
		close(_first);
	if (_second > 0)
		close(_second);
	return (_SUCCESS_);
}

int	_file_descriptors_duplicators(int _first, int _second)
{
	if (_first > 0)
		dup2(_first, STDIN_FILENO);
	if (_second > 0)
		dup2(_second, STDOUT_FILENO);
	return (1);
}

int	open_infile(char *infile_name, t_pipe *data)
{
	int	infile;

	infile = open(infile_name, O_RDONLY);
	if (access(infile_name, R_OK))
	{
		__putstr_fd("pipex: ", STDERR_FILENO);
		__putstr_fd("no such file or directory: ", STDERR_FILENO);
		__putstr_fd(infile_name, STDERR_FILENO);
		__putstr_fd("\n", 2);
		_close_file_descriptors(data->pipe[0], data->pipe[1]);
		// clean(data);
		exit(EXIT_FAILURE);
	}
	else if (infile < 0)
	{
		_close_file_descriptors(data->pipe[0], data->pipe[1]);
		// clean(data);
		_error_prompt(infile_name);
	}
	else
		return (infile);
	return (infile);
}

int	open_outfile(char *outfile_name, int mode, t_pipe *data)
{
	int	outfile;

	if (mode == USUAL)
		outfile = open(outfile_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		outfile = open(outfile_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (outfile < 0)
	{
		close(data->prev_read);
		_close_file_descriptors(data->pipe[0], data->pipe[1]);
		// clean(data);
		_error_prompt(outfile_name);
	}
	return (outfile);
}

int	__is_child(pid_t process)
{
	if (process == 0)
		return (_TRUE_);
	else
		return (_FALSE_);
}

int	__count_cmd(t_cmd *head)
{
	t_cmd	*tmp;
	int		i;

	tmp = head;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	_error_prompt(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

t_cmd	*ft_cmd_new(t_lexer *lexer, t_cmd *new)
{
	char	*outfiles;
	char	*infiles;

	outfiles = NULL;
	infiles = NULL;
	while (lexer && lexer->type != PIPE)
	{
		if (!__strcmp(lexer->token, ">")
			|| !__strcmp(lexer->token,">>"))
		{
			outfiles = __strjoin(outfiles, lexer->next->token);
			outfiles = __strjoin(outfiles, "\n");
			lexer = lexer->next->next;
		}
		else if(!__strcmp(lexer->token, "<"))
		{
			infiles = __strjoin(infiles, lexer->next->token);
			infiles = __strjoin(infiles, "\n");
			lexer = lexer->next->next;
		}
		else
		{
			if (new->cmd)
				new->cmd = __strjoin(new->cmd, " ");
			new->cmd = __strjoin(new->cmd, lexer->token);
			lexer = lexer->next;
		}
	}
	new->infile_name = __split(infiles, '\n');
	new->outfile_name = __split(outfiles, '\n');
	return (new);
}

t_cmd	*init_new_cmd(t_cmd *new)
{
	new->mode = 0;
	new->outfile = 0;
	new->cmd = NULL;
	new->infile_name = NULL;
	new->outfile_name = NULL;
	new->next = NULL;
	return (new);
}

t_lexer	*ft_split_cmd(t_lexer *lexer, t_cmd **head)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = malloc(sizeof(t_cmd));
	if (!(new))
		return (NULL);
	new = init_new_cmd(new);
	new = ft_cmd_new(lexer, new);
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	while (lexer && lexer->type != PIPE)
		lexer = lexer->next;
	if (!lexer)
		return (lexer);
	return (lexer->next);
}

t_cmd	*init_cmd_list(t_user_input *ui)
{
	t_cmd	*head;
	t_lexer	*split_cmd;

	split_cmd = ui->lexer;
	head = NULL;
	while (split_cmd)
	{
		split_cmd = ft_split_cmd(split_cmd, &head);
	}
	return (head);
}

void	init_pipe(t_user_input *ui, t_pipe *data)
{
	data->elem = init_cmd_list(ui);
	data->head = data->elem;
	data->ninst = __count_cmd(data->elem);
	data->index = 0;
	data->pid = (int *)malloc(sizeof(int) * (data->ninst));
	data->path = get_path(ui->env);
	if (!data->pid)
		_error_prompt("error :");
}

void	init(t_pipe *data)
{
	data->prev_read = 0;
	data->head = NULL;
	data->elem = NULL;
	data->path = NULL;
	data->ninst = 0;
	data->index = 0;
	data = NULL;
}

t_pipe	*ft_init_pipex(t_user_input *ui, t_pipe *pipe)
{
	init(pipe);
	init_pipe(ui, pipe);
	return (pipe);
}

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

void	__printfcmd(t_cmd *head)
{
	t_cmd *tmp;
	int i;
	int j;

	tmp = head;
	i = 1;
	while (tmp)
	{
		printf("Pipe %d :\n", i);
		printf("commande = %s\n", tmp->cmd);
		printf("infiles : ");
		j = 0;
		while (tmp->infile_name && tmp->infile_name[j])
		{
			printf("< %s ", tmp->infile_name[j]);
			j++;
		}
		printf("\noutfiles : ");
		j = 0;
		while (tmp->outfile_name && tmp->outfile_name[j])
		{
			printf("> %s ", tmp->outfile_name[j]);
			j++;
		}
		printf("\n");
		tmp = tmp->next;
		i++;
	}
}

int	pipex(t_pipe *data, t_user_input *ui)
{	
	while (data->index < data->ninst)
	{
		if (pipe(data->pipe) < 0)
			return (perror("pipe"), _FAILURE_);
		data->pid[data->index] = fork();
		if (data->pid[data->index] < 0)
			return (perror("fork "), _FAILURE_);
		if (__is_child(data->pid[data->index]))
			exec_children_work(data, ui);
		if (!__is_child(data->pid[data->index]))
		{
			if (data->index)
				_close_file_descriptors(data->prev_read, data->pipe[1]);
			else
				close(data->pipe[1]);
			data->prev_read = data->pipe[0];
		}
		data->index++;
		data->elem = data->elem->next;
	}
	return (_SUCCESS_);
}

int	ft_pipex(t_user_input *ui)
{
	ui->pipe = malloc(sizeof(t_pipe));
	if (!ui->pipe)
		return (perror("error"), STDERR_FILENO);
	if (!ft_is_pipe(ui->lexer))
		return (ft_cmd(ui));
	if (!ft_init_pipex(ui, ui->pipe))
		return (STDERR_FILENO);
	if (!__pipex(ui->pipe, ui))
		return (STDERR_FILENO);
	// __printfcmd(ui->pipe->head);
	return (ft_cmd(ui));
}