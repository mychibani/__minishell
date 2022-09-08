SRCS_FILES =	char/ft_isdigit.c			\
				char/ft_isprint.c			\
				char/ft_isalnum.c			\
				char/ft_isalpha.c			\
				char/ft_isascii.c			\
				char/ft_toupper.c			\
				char/ft_tolower.c			\
				string/ft_substr.c			\
				string/ft_bzero.c			\
				string/ft_strncmp.c			\
				string/ft_strcmp.c			\
				string/ft_strchr.c			\
				string/ft_strlcpy.c			\
				string/ft_strlcat.c			\
				string/ft_strrchr.c			\
				string/ft_strdup.c			\
				string/ft_strtrim.c			\
				string/ft_strlen.c			\
				string/ft_strmapi.c			\
				string/ft_strnstr.c			\
				string/ft_split.c			\
				string/ft_striteri.c		\
				string/ft_strjoin.c			\
				stdlib/ft_atoi.c			\
				stdlib/ft_itoa.c			\
				lists/ft_lstiter.c			\
				lists/ft_lstsize.c			\
				lists/ft_lstadd_front.c		\
				lists/ft_lstadd_back.c		\
				lists/ft_lstnew.c			\
				lists/ft_lstlast.c			\
				lists/ft_lstdelone.c		\
				lists/ft_lstclear.c			\
				lists/ft_lstmap.c			\
				memory/ft_memcmp.c			\
				memory/ft_memset.c			\
				memory/ft_memcpy.c			\
				memory/ft_memchr.c			\
				memory/ft_memmove.c			\
				memory/ft_calloc.c			\
				fd/ft_putchar_fd.c			\
				fd/ft_putnbr_fd.c			\
				fd/ft_putendl_fd.c			\
				fd/ft_putstr_fd.c			\
				fd/gnl.c					\
				printf/ft_conv_fct.c		\
				printf/ft_treat_format.c	\
				printf/ft_printf.c			\

OBJS_FILES 		=		${SRCS:.c=.o}

DEPS_FILES		=		${SRCS:.c=.d}

HEADER_INC		=	-I $(HEADER_PATH)

SRCS_PATH 		=		.


CC				=	gcc

FLAGS			=	-Wall -Wextra -Werror

RM				=	rm -rf

NAME			=	libft.a

INCS            =   -I ./includes


SRCS			=	$(addprefix $(SRCS_PATH)/, $(SRCS_FILES))

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

all		:	$(NAME)


.c.o		:
			@echo "Compiling ${_GREEN}${_BOLD}$<${_END}..."
			@$(CC) $(FLAGS) ${INCS} -MMD -c $< -o $@ ${INCS}

$(NAME)		:	$(OBJS_FILES)
			@echo "${_YELLOW}${_BOLD}Library Done!${_END}"
			@ar rc $(NAME) $(OBJS_FILES)

clean:
			@echo "Deleting ${_RED}${_BOLD}objects files${_END}..."
			@${RM} ${OBJS_FILES} ${DEPS_FILES}

fclean:		clean
			@echo "Deleting ${_RED}${_BOLD}libraries${_END}..."
			@${RM} ${NAME} 


re :		fclean all

-include ${DEPS_FILES}

.PHONY:		all clean fclean re
