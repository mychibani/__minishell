# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 14:03:48 by jroux-fo          #+#    #+#              #
#    Updated: 2022/05/22 19:13:57 by ychibani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES		=	srcs/parser/main.c


HEADER_FILES		=	libft.h					\
				define.h				\
				fonctions.h				\
				includes.h


NAME			= 	minishell

OBJS_FILES 		= 	${SRCS_FILES:.c=.o}

DEPS_FILES		=	${SRCS_FILES:.c=.d}

INCS			=	-I ./includes -I libft/includes/

LIBFT			=	libft/libft.a

CC			=	gcc

CFLAGS			=  	-Wall -Werror -Wextra

RM			=	rm -rf

_END=$'\e[0m
_BOLD=$'\e[1m
_UNDER=$'\e[4m
_REV=$'\e[7m
_GREY=$'\e[30m
_RED=$'\e[0;31m
_GREEN=$'\e[32m
_YELLOW=$'\e[33m
_BLUE=$'\e[34m
_PURPLE=$'\e[35m
_CYAN=$'\e[36m
_WHITE=$'\e[37m

_IGREY=$'\e[40m
_IRED=$'\e[41m
_IGREEN=$'\e[42m
_IYELLOW=$'\e[43m
_IBLUE=$'\e[44m
_IPURPLE=$'\e[45m
_ICYAN=$'\e[46m
_IWHITE=$'\e[47m

all:		${NAME}

.c.o:
				@echo "Compiling ${_YELLOW}${_BOLD}$<${_END}..."
				@${CC} ${CFLAGS} ${INCS} -MMD -c $< -o $@ ${INCS}

${NAME}:		${OBJS_FILES}
				@echo "Compiling ${_GREEN}${_BOLD}libft${_END}..."
				@${MAKE} -C libft >/dev/null
				@echo "Compiling ${_CYAN}${_BOLD}minishell${_END}..."
				@${CC} ${CFLAGS} ${INCS} ${OBJS_FILES} -o ${NAME} ${LIBFT}

clean:
				@echo "Deleting ${_RED}${_BOLD}binary files${_END}..."
				@${RM} ${OBJS_FILES} ${DEPS_FILES}
				@echo "Deleting ${_RED}${_BOLD}libft binary files${_END}..."
				@${MAKE} -C libft fclean >/dev/null

fclean:			clean
				@echo "Deleting ${_RED}${_BOLD}minishell${_END}..."
				@${RM} ${OBJS_MAIN} ${OBJS_PIPEX} ${OBJS_PARSING} ${OBJS_UTILS} ${OBJS_INIT} ${OBJS_CLEAN} ${OBJS_HERE_DOC} ${NAME} ${PIPEX_BONUS}
				@echo "Deleting ${_RED}${_BOLD}libft librairy${_END}..."
				@${MAKE} -C libft fclean >/dev/null

re:				fclean all

-include ${DEPS_FILES}

.PHONY:			all clean fclean re bonus
