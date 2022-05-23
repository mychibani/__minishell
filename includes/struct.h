#ifndef STRUCT_H
# define STRUCT_H

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

#endif