/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:18:34 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/25 14:32:26y ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_es;

int	wait_here_doc(pid_t pid, t_program_data *data)
{
	int	status;
	int	ret;

	ret = 0;
	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) > 0)
		ret = (WEXITSTATUS(status));
	if (WIFSIGNALED(status) > 0)
		ret = (WTERMSIG(status) + 128);
	if (ret == 130)
		data->rv = 130;
	return (ret);
}

int	eof_type(char *eof)
{
	if (eof[0] == '\'' && eof[__strlen(eof) - 1] == '\'')
		return (1);
	if (eof[0] == '\"' && eof[__strlen(eof) - 1] == '\"')
		return (2);
	return (3);
}

int	end_of_info(char *hd_content, int here_doc_fd, t_lexer *lexer, int eof_type)
{
	if (close(here_doc_fd) < 0)
		return (free(hd_content), 0);
	if (unlink(".hd_file") < 0)
		return (free(hd_content), 0);
	free(lexer->next->token);
	lexer->next->token = hd_content;
	lexer->next->hd_type = eof_type;
	return (_SUCCESS_);
}

int	get_child_info(t_lexer *lexer, char *eof)
{
	char	buffer[32];
	char	*hd_content;
	int		ret;
	int		here_doc_fd;

	hd_content = NULL;
	here_doc_fd = open(".hd_file", O_RDONLY);
	if (here_doc_fd < 0)
		return (0);
	ret = 1;
	while (ret)
	{
		ret = read(here_doc_fd, buffer, 31);
		if (ret < 0)
			return (free(hd_content), close(here_doc_fd), unlink(".hd_file"), 0);
		buffer[ret] = '\0';
		hd_content = __strjoin(hd_content, buffer);
		if (!hd_content)
			return (close(here_doc_fd), unlink(".hd_file"), 0);
	}
	return (end_of_info(hd_content, here_doc_fd, lexer, eof_type(eof)));
}

int	__handle_here_doc(t_lexer *start, t_lexer *end, t_program_data *data)
{
	pid_t		pid;
	char		*eof;
	t_lexer		*save;

	save = start;
	while (start != end && start && start->next != end)
	{
		if (start->type == HERE_DOC)
		{
			eof = start->next->token;
			pid = fork();
			if (pid < 0)
				return (0);
			if (pid == 0)
				init_child_hd(eof, start, save, data);
			else
			{
				if (wait_here_doc(pid, data) == 130)
					return (130);
				if (!get_child_info(start, eof))
					return (0);
				start = start->next;
			}
		}
		start = start->next;
	}
	return (1);
}

int	__heredoc(t_user_input *ui, t_program_data *data)
{
	ui->ret_hd = __handle_here_doc(ui->lexer, ui->error_delim, data);
	if (ui->ret_hd == 0)
		return (__lexer_clear(&ui->lexer, free), __exit(data, ui, 0), 0);
	else if (ui->ret_hd == 130)
		return (__lexer_clear(&ui->lexer, free), 0);
	else
		return (_SUCCESS_);
}