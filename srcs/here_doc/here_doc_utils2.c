/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:20:45 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/11 15:12:02 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_join(char *adding_line, char **heredoc)
{
	char	*new_heredoc;
	int		i;
	int		j;
	int		len;

	new_heredoc = NULL;
	i = -1;
	j = -1;
	len = (__strlen(adding_line) + __strlen(*heredoc) + 1);
	if (!*heredoc)
		*heredoc = __strdup("");
	new_heredoc = (char *)malloc(sizeof(char) * len);
	if (!new_heredoc)
		return (free(*heredoc), 0);
	while ((*heredoc)[++i])
		new_heredoc[i] = (*heredoc)[i];
	while (adding_line[++j])
	{
		new_heredoc[i] = adding_line[j];
		i++;
	}
	new_heredoc[i] = '\0';
	free(*heredoc);
	*heredoc = new_heredoc;
	return (1);
}

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
