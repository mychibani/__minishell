/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:28:32 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/03 20:02:28 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				env;
	int				order;
	struct s_env	*next;
}	t_env;

typedef struct s_lexer
{
	t_type			type;
	char			*token;
	int				hd_type;
	int				empty;
	struct s_lexer	*next;	
}	t_lexer;

typedef struct s_user_input
{
	t_list		*token;
	t_lexer		*lexer;
	t_lexer		*error_delim;
	t_env		**test_env;
	// char		**env;
	char		*to_tokenize;
	int			ret_token;
	int			ret_hd;
}	t_user_input;

typedef struct s_program_data
{
	int				rv;
	int				synthax_error;
	t_user_input	*ui;
	t_list			*token;	
	char			**all_inputs;
	char			**env;
}	t_program_data;

#endif