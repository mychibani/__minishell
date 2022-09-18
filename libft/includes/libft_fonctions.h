/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fonctions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:02:29 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/18 17:02:59 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FONCTIONS_H
# define LIBFT_FONCTIONS_H

int			__printf(const char *format_str, ...);
void		__treat_format(t_struct *content, va_list format);
void		__putchar(char c, t_struct *content);
void		__putstr(char *str, t_struct *content);
void		__base(unsigned long long nb, char *base, t_struct *content);
void		__putnbr(int n, t_struct *content);
void		__print_memory(void *nb, t_struct *content);
void		*__memset(void *b, int c, size_t len);
void		__striteri(char *s, void (*f)(unsigned int, char*));
void		__bzero(void *s, size_t n);
void		*__memcpy(void *dst, const void *src, size_t n);
void		*__memmove(void *dst, const void *src, size_t len);
void		*__memchr(const void *s, int c, size_t n);
size_t		__strlen(const char *s);
int			__memcmp(const void *s1, const void *s2, size_t n);
int			__isalpha(int c);
int			__isdigit(int c);
int			__isalnum(int c);
int			__in_ascii(int c);
int			__isprint(int c);
int			__toupper(int c);
int			__tolower(int c);
int			__strncmp(const char *s1, const char *s2, size_t n);
int			__strcmp(const char *s1, const char *s2);
char		*__strchr(const char *s, int c);
char		*__strrchr(const char *s, int c);
size_t		__strlcat(char *dst, char *src, size_t dstsize);
size_t		__strlcpy(char *dst, const char *src, size_t dstsize);
char		*__strnstr(const char *haystack, const char *needle, size_t len);
int			__atoi(const char *str);
void		*__calloc(size_t count, size_t size);
char		*__strdup(const char *s1);
char		*__substr(char const *s, unsigned int start, size_t len);
char		*__strtrim(char const *s1, char const *set);
char		**__split(char const *s, char c);
char		*_strjoin(char *s1, char *s2);
char		*__itoa(int n);
char		*__strmapi(char const *s, char (*f)(unsigned int, char));
void		__putchar_fd(char c, int fd);
void		__putstr_fd(char *s, int fd);
void		__putendl_fd(char *s, int fd);
void		__putnbr_fd(int n, int fd);
t_list		*__lstnew(void *content);
void		__lstadd_front(t_list **alst, t_list *new);
int			__lstsize(t_list *lst);
t_list		*__lstlast(t_list *lst);
void		__lstadd_back(t_list **alst, t_list *new);
void		__lstdelone(t_list *lst, void (*del)(void *));
void		__lstclear(t_list **lst, void (*del)(void *));
void		__lstiter(t_list *lst, void (*f)(void *));
t_list		*__lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char		*__gnl(int fd);

#endif