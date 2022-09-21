#include "minishell.h"

int change_directory(char **args, char *path, char *home)
{
    char *actual_dir; //recuperer grace a jujules

    actual_dir = NULL;
    // g_status = 0;

    /*Tips a savoir
    Par defaut $CDPATH est vide et si on fait CD $CDPATH --> on se tp a HOME
    cd -- = cd $OLDPWD
    cd ~ = cd $HOME
    */

    /*
    e.1 Si le directory n'est pas entree et que la Variable HOME n'est pas dans le env;
    ft_putstr_fd(bash: cd: HOME not set);

    e.2 Si le directory n'est pas entree mais que la variable HOME est dans le env : se tp a la la variable HOME changer PWD et OLD PWD Garder en memoire le PATH actuel

    e.3 si le directory commence par un '/' se tp au directory et aller a l'etape 7

    e.4 si le directory commence par un '.' ou par un ".." aller a l'etape 6

    e.5 la on utilise $CDPATH imaginons que $CDPATH == /usr/bin/local:/$HOME/Documents/42-Minishell
    si $CDPATH est non NULL tester la concatenation du path dans lequel on souhaite rentrer avec $CDPATH
    cd /$HOME/Documents/42-Minishell + /srcs/parser
    si il est NULL tester avec "./" + new_path, 

    */
    if (args && args[1] && args[2])
        return (ft_putstr_fd("minishell: cd: too many argumetns\n",2), 1);
    chdir(path);
    perror(path);
    return (2);
}
