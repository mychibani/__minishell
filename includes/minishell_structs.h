/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:28:32 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/12 08:16:50 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
}					t_token ;


typedef struct s_user_input
{
	t_list		*token;
	char		*to_tokenize;
	int			ret_token;
	int			ret_hd;
}	t_user_input;


typedef	struct s_program_data
{
	t_user_input	*ui;
	t_list			*token;	
	char			**all_inputs;

}	t_program_data;

#endif