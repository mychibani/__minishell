/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:05:03 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/19 16:11:29 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "define.h"
# include "struct.h"
# include "enum.h"
# include "fonctions.h"
# include "libft.h"

typedef enum e_type
{
	OPERATOR,
	WORD,
	PONCT,
	SPACE,
	REDIR,
};

typedef struct s_list
{
	void    		*content;
	struct s_list	*next;
}					t_list;

typedef struct s_token
{
	int				type; //1-operator, 2-word, 3-ponct, 4-space, 5-redir

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

	char			*content;
	struct s_token	*next;
}					t_token ;

//	main.c
int	main(int argc, char **argv, char **env);

#endif