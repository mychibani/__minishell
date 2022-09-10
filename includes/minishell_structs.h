/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:28:32 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/10 17:47:31 by ychibani         ###   ########.fr       */
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

/*
	Penser a specifier pour Word; (j'en ai besoin pour l'execution des commandes)

	Words:
	- File
	- Option
	- Command
	- Argument
	- Delimiter
	
	et la pour savoir si je dois juste faire transiter l'output de la commande dans une prochaine commande ou d'un fichier directement
	Operators:
	- Pipe
	- Redirect
*/

typedef	struct s_program_data
{
	t_user_input	*ui;
	t_list			*token;	
	int				es;
	int				max_cmd;
	char			*prompt;
	char			***envp;
	char			*error_str;
	char			**all_inputs;

}	t_program_data;

#endif