/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_enums.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:06:56 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/18 17:08:05 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ENUMS_H
# define MINISHELL_ENUMS_H

typedef enum e_type
{
	OPERATOR,
	PIPE,
	WORD,
	REDIRECTION,
	HERE_DOC,
	INVALID,
	NEW_LINE
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

#endif