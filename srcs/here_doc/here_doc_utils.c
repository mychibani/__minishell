/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:56:23 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/11 14:21:20 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_es;

void	treat_eof(char *line, char *eof, t_program_data *data)
{
	if (!line)
	{
		data->rv = 130;
		__putstr_fd(" here-document delimited by end-of-file (wanted `", 2);
		__putstr_fd(eof, 2);
		__putstr_fd("')\n", 2);
		__gnl(-1);
		free(line);
		return ;
	}
	__gnl(-1);
	free(line);
	data->rv = 0;
}

int	read_from_stdin(char *eof, char **heredoc, t_program_data *data)
{
	char	*adding_line;

	adding_line = NULL;
	while (42)
	{
		__putstr_fd("> ", 2);
		adding_line = __gnl(0);
		if ((!adding_line) || ((!__strncmp(adding_line, eof, __strlen(eof)))
				&& ((__strlen(adding_line)) == (__strlen(eof) + 1))))
		{
			treat_eof(adding_line, eof, data);
			break ;
		}
		if (!heredoc_join(adding_line, heredoc))
			return (__gnl(-1), 0);
		free(adding_line);
	}	
	return (_SUCCESS_);
}

int	trim_eof(char **eof)
{
	char	*tmp;

	tmp = NULL;
	if (((*eof)[0] == '"' && (*eof)[__strlen(*eof) - 1] == '"'))
	{
		tmp = __strtrim(*eof, "\"");
		if (!tmp)
			return (0);
		free(*eof);
		*eof = tmp;
	}
	else if (((*eof)[0] == '\'' && (*eof)[__strlen(*eof) - 1] == '\''))
	{
		tmp = __strtrim(*eof, "'");
		if (!tmp)
			return (0);
		free(*eof);
		*eof = tmp;
	}
	return (1);
}

int	get_usr_input(char **eof, t_program_data *data)
{
	int		here_doc_fd;
	char	*here_doc;

	here_doc = NULL;
	if (!trim_eof(eof))
		return (-1);
	if (!read_from_stdin(*eof, &here_doc, data))
		return (-1);
	here_doc_fd = open(".hd_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (here_doc_fd < 0)
		return (free(here_doc), 0);
	__putstr_fd(here_doc, here_doc_fd);
	free(here_doc);
	close(here_doc_fd);
	return (1);
}

void	init_child_hd(char *eof, t_lexer *travel,
		t_program_data *data, t_lexer *save)
{
	g_es = 0;
	data->rv = 0;
	signal(SIGINT, hd_signal);
	signal(SIGQUIT, SIG_IGN);
	if (!get_usr_input(&eof, data))
		return (__lexer_clear(&save),
			__putstr_fd("Malloc Error in Here_doc\n", 2));
	travel->next->token = eof;
	__lexer_clear(&save);
	__free_tab(data->all_inputs);
	data->all_inputs = NULL;
	destroy_env(data);
	exit(data->rv);
}
