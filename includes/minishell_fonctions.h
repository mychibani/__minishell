/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fonctions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:42:53 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/04 13:48:16 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FONCTIONS_H
# define MINISHELL_FONCTIONS_H

/*
**		Init
*/

// t_program_data	*init_data_struct(t_program_data *data);
// t_user_input	*init_user_input_struct(t_user_input *ui);
// void			__init_structs(t_program_data *data, t_user_input *ui);

/*
**		Env
*/

int				get_env_var(t_program_data *data, char **env, int size);
int				get_env_size(char **env);

/*
**		Cd
*/

int				change_directory(char *path);
t_program_data	*init_data_struct(t_program_data *data);
t_user_input	*init_user_input_struct(t_user_input *ui);
void			__init_structs(t_program_data *data, t_user_input *ui);

/*
**		Cd
*/

int				change_directory(char *path);
void			ft_cd(t_user_input *ui);

/*
**		echo
*/

void	ft_echo(t_user_input *ui);
char	*remove_quote(char *str);

/*
**		env
*/

void	ft_env(t_user_input *ui);
t_env	*ft_init_env(char *var_to_split);
t_env	**ft_split_env(char	**env);

/*
**		env_utils
*/

void	__env_clear(t_env **lst, void (*del)(void*));
char	*__strncpy(char *dst, const char *src, size_t dstsize);
t_env	*__lst_env_new(char *name, char *value, int appear);
void	__env_lstadd_back(t_env **alst, t_env *new);
int		ft_size(char **str);


/*
**		exit
*/

void	ft_exit(t_user_input *ui);

/*
**		export
*/

void	ft_choose_export(t_user_input *ui);
void	ft_export_arg(t_user_input *ui, char *var);
void	ft_export_no_arg(t_user_input *ui);
void	ft_make_export(t_env *search, char *to_set, t_user_input *ui);
void	ft_changevar(t_env *env, char *var_to_split);

/*
**		export_utils
*/

void	ft_free(char **to_free, int i);
int		ft_var_length(char	*var);
int		ft_valid_var(char *str);
void	ft_concat_var(t_env *env, char *var_to_split);


/*
**		pwd
*/

void	ft_pwd(void);

/*
**		unset
*/

void	ft_unset(t_user_input *ui);

/*
**		exec
*/

int				ft_cmd(t_user_input *ui);


/*
**		Tokenizer Utils
*/

t_state			return_quoted_state(char c, t_state state, t_state quoted);
void			skip_spaces(char *str, int *i);
int				adjust_i(char *str, int i, int state);
int				__is_operator(char c);

/*
**		Tokenizer
*/

int				tokenize(char *to_tokenize, t_list **token_list);
int				add_char_token(char c, char **token);
int				add_token(char *token, t_list **begin);
int				get_operator(char **token, char *str, int i);
int				get_word(char **token, char *str, int i);

/*
**		Lexer
*/

int				lexer(t_list *token, t_lexer **lexer);
t_lexer			*synthax_checker(t_lexer **lexer, t_program_data *data);

/*
**		Parsing
*/

int				treat_usr_inputs(char *user_input,
					t_program_data *data, t_user_input *ui);

/*
**		Heredoc
*/

void			treat_eof(char *line, char *eof, t_program_data *data);
void			init_child_hd(char *eof, t_lexer *travel,
					t_program_data *data, t_lexer *save);
int				__heredoc(t_user_input *ui, t_program_data *data);
int				heredoc_join(char *adding_line, char **heredoc);
int				get_usr_input(char **eof, t_program_data *data);
int				read_from_stdin(char *eof, char **heredoc,
					t_program_data *data);
int				heredoc_join(char *adding_line, char **heredoc);

/*
**		Signals
*/

void			treat_signal(int sig);
void			hd_signal(int sig);
void			init_signals(void);
void			ctrld_signal(int sig);
void			__signal(int sig);

/*
**		Clean
*/

char			**__free_tab(char **tab);
void			__lexer_clear(t_lexer **lst);
void			__clean_input(t_user_input *ui, char **inputs, char *line);
void			destroy_env(t_program_data *data);

/*
**
*/

int				sequence_launcher(t_lexer **seq, t_program_data *data);
char			*get_testing_wd(char *start_wd, int *offset);
int				find_key(char *testing_wd, char *env_str,
					t_program_data *data, int j);
char			*handle_quotes_in_env(char *str);
int				get_value(char *testing_wd, char *env_str,
					char **expanded_wd, char *key_value);
int				__heredoc_expansion(char **token, t_program_data *data);
void	update_token(char **token, char **new_token);
int		parameter_expand(char *str, char **expanded_wd, t_program_data *data, int *offset);
int	treat_final_rv(char **wd, int *offset, t_program_data *data);
char *get_key(char *str);
int	is_valid_char(char c);

/*
**		Exit
*/

void			__exit(t_program_data *data, t_user_input *ui, int rv);

/*
**		Utils
*/

void			print_data(t_program_data *data, t_user_input *ui);
void			print_linked_list(t_list *list);
void			print_lexer_list(t_lexer *lexer);

#endif