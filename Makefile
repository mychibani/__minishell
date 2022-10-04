# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 14:03:48 by jroux-fo          #+#    #+#              #
#    Updated: 2022/09/15 11:50:13by ychibani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES		=		srcs/minishell/minishell.c			\
						srcs/init/init_structs.c			\
						srcs/init/env.c						\
						srcs/parser/parsing.c				\
						srcs/parser/synthax_checker.c		\
						srcs/token/tokenizer.c				\
						srcs/token/word_operator_fct.c		\
						srcs/token/tokenizer_utils_fct.c	\
						srcs/lexer/lexer.c					\
						srcs/lexer/lexer_utils.c			\
						srcs/utils/utils.c					\
						srcs/clean/cleaner_prog.c			\
						srcs/clean/clean_exit.c				\
						srcs/executor/signals/signal.c		\
						srcs/here_doc/here_doc.c			\
						srcs/here_doc/here_doc_utils.c		\
						srcs/expander/expander.c			\
						srcs/expander/expander2.c			\
						srcs/expander/dq_expander.c			\
						srcs/expander/heredoc_expand.c		\
						srcs/executor/builtin/echo/echo.c	\
						srcs/executor/exec.c				\
						srcs/executor/builtin/env/env.c		\
						srcs/executor/builtin/env/env_utils.c		\
						srcs/executor/builtin/pwd/pwd.c		\
						srcs/executor/builtin/cd/cd.c		\
						srcs/executor/builtin/export/export.c \
						srcs/executor/builtin/export/export_utils.c \
						srcs/executor/builtin/unset/unset.c	\
						srcs/executor/builtin/exit/exit.c


NAME			= 	minishell

OBJS_FILES 		= 	${SRCS_FILES:.c=.o}

DEPS_FILES		=	${SRCS_FILES:.c=.d}

INCS			=	-I ./includes -I libft/includes/

LIBFT			=	libft/libft.a

CC				=	gcc 

CFLAGS			=  	-Wall -Werror -Wextra -g3 

RM				=	rm -rf

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
				@${CC} ${CFLAGS} ${INCS} -MMD -c $< -o $@ -lreadline

${NAME}:		${OBJS_FILES}
				@echo "Compiling ${_GREEN}${_BOLD}libft${_END}..."
				@${MAKE} -C libft >/dev/null
				@echo "Compiling ${_CYAN}${_BOLD}minishell${_END}..."
				@${CC} ${CFLAGS} ${INCS} ${OBJS_FILES} -o ${NAME} ${LIBFT} -lreadline

clean:
				@echo "Deleting ${_RED}${_BOLD}binary files${_END}..."
				@${RM} ${OBJS_FILES} ${DEPS_FILES}
				@echo "Deleting ${_RED}${_BOLD}libft binary files${_END}..."
				@${MAKE} -C libft fclean >/dev/null

fclean:			clean
				@echo "Deleting ${_RED}${_BOLD}minishell${_END}..."
				@${RM} ${OBJS_FILES} ${NAME}

re:				fclean 
				make all

git:		
			git add .
			git commit -m "$m"
			git push origin master

-include	${DEPS_FILES}

.PHONY:			all clean fclean re
