/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_enums.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:06:56 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/17 14:12:06 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ENUMS_H
# define MINISHELL_ENUMS_H

typedef enum e_type
{
	PIPE,
	WORD,
	REDIRECTION,
	HERE_DOC,
	INVALID,
	NEW_LINE,
	OPERATOR
}	t_type;

typedef enum e_state
{
	UNQUOTED,
	S_QUOTED,
	D_QUOTED,
	BACKSLASH,
}	t_state;

typedef enum e_token_pos
{
	FIRST,
	MIDDLE,
	LAST
}	t_token_pos;

typedef enum e_redir_type
{
	HD,
	GREAT,
	LESS,
	D_GREAT
}	t_redir_type;

#endif