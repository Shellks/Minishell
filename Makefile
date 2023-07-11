# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/13 14:29:15 by nibernar          #+#    #+#              #
#    Updated: 2023/07/11 17:46:58 by nibernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -o2 -g3
CC = cc
HEADER = ./include

SRCS =	src/minishell.c						\
		src/env/get_pwd.c					\
		src/env/get_env.c					\
		src/lexer/lexer.c					\
		src/lexer/lexer_bis.c				\
		src/lexer/ft_fusion.c				\
		src/lexer/check_quote.c 			\
		src/expand/ft_expand.c				\
		src/expand/ft_expand_status.c		\
		src/expand/ft_expand_utils.c		\
		src/expand/ft_expand_space.c		\
		src/expand/ft_expand_in_quote.c		\
		src/expand/ft_expand_quote_utils.c	\
		src/parsing/parser_utils.c			\
		src/parsing/parser.c				\
		src/print_lexer.c					\
		src/built_in/ft_exit.c				\
		src/built_in/ft_echo.c				\
		src/built_in/ft_env.c				\
		src/built_in/ft_unset.c				\
		src/built_in/ft_export.c			\
		src/built_in/ft_cd.c				\
		src/exec/ft_redirection.c			\
		src/exec/ft_here_doc.c				\
		src/utils/ft_free.c					\
		src/utils/get_next_line.c			\
		src/utils/ft_close.c				\
		list/parser/ft_parser_add_back.c	\
		list/parser/ft_parser_clear.c		\
		list/parser/ft_parser_delone.c		\
		list/parser/ft_parser_last.c		\
		list/parser/ft_parser_new.c			\
		list/parser/ft_redir_clear.c		\
		list/parser/ft_redir_delone.c		\
		list/parser/ft_redir_new.c			\
		list/parser/ft_redir_add_back.c		\
		list/parser/ft_redir_last.c			\
		list/lexer/ft_lexer_add_back.c		\
		list/lexer/ft_lexer_add_front.c		\
		list/lexer/ft_lexer_clear.c			\
		list/lexer/ft_lexer_delone.c		\
		list/lexer/ft_lexer_first.c			\
		list/lexer/ft_lexer_last.c			\
		list/lexer/ft_lexer_new.c			\
		list/lexer/ft_lexer_size.c			\
		list/env/ft_env_add_back.c			\
		list/env/ft_env_add_front.c			\
		list/env/ft_env_clear.c				\
		list/env/ft_env_delone.c			\
		list/env/ft_env_first.c				\
		list/env/ft_env_last.c				\
		list/env/ft_env_new.c				\
		list/env/ft_env_size.c

OBJS = ${SRCS:.c=.o}

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))


./src/%.o: ./src/%.c ${HEADER}/minishell.h ${LIBFT_LIB}
		${CC} ${CFLAGS} -I ${HEADER} -g -c $< -o $@ 


all : ${NAME}

lib: force
	@echo "\033[0;33m\nCOMPILING $(LIBFT_PATH)\n"
	@make -C $(LIBFT_PATH)
	@echo "\033[1;32mLIBFT created\n"

	
${NAME} : lib ${OBJS} ${LIBFT_LIB}
	echo "\033[1;34m\nCreate: \033[1;33mMinishell"
	${CC} ${CFLAGS} ${OBJS} ${LIBFT_LIB} -o ${NAME} -lreadline
	echo "\033[1;32mSucces !\n\033[0m"


	
force :

clean :
	echo "\033[1;31m\nClean: \033[1;36mAll .o"
	make clean -C ${LIBFT_PATH}
	${RM} ${OBJS} 
	echo "\033[1;32mDelete !\n"

fclean: clean
	echo "\033[1;31mClean: \033[1;36mAll.a && executable"
	make fclean -C ${LIBFT_PATH}
	${RM} ${NAME}
	echo "\033[1;32mDelete !\n"

re : fclean all

.SILENT:

.PHONY: all clean fclean re force
