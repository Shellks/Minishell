# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/13 14:29:15 by nibernar          #+#    #+#              #
#    Updated: 2023/07/28 11:48:18 by acarlott         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g3
CC = cc

HEADER_PATH = ./include/
HEADER_FILES = env.h exec.h lexer.h minishell.h parser.h
HEADERS = $(addprefix $(HEADER_PATH), $(HEADER_FILES))

LIBFT_PATH	=	./libft/
LIBFT_FILE	=	libft.a
LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

SRCS =	src/minishell.c							\
		src/env/get_pwd.c						\
		src/env/get_env.c						\
		src/env/create_new_env.c				\
		src/lexer/lexer.c						\
		src/lexer/lexer_bis.c					\
		src/lexer/ft_fusion.c					\
		src/lexer/check_quote.c 				\
		src/expand/ft_expand.c					\
		src/exec/expand_here_doc_utils.c		\
		src/exec/ft_expand_here_doc.c			\
		src/expand/ft_expand_status.c			\
		src/expand/ft_expand_utils.c			\
		src/expand/ft_expand_space.c			\
		src/expand/ft_expand_in_quote.c			\
		src/expand/ft_expand_quote_utils.c		\
		src/parsing/parser_utils.c				\
		src/parsing/parser.c					\
		src/built_in/ft_exit.c					\
		src/built_in/ft_echo.c					\
		src/built_in/ft_env.c					\
		src/built_in/ft_unset.c					\
		src/built_in/ft_export.c				\
		src/built_in/ft_export_utils.c			\
		src/built_in/ft_export_join.c			\
		src/built_in/ft_print_export.c			\
		src/built_in/ft_cd.c					\
		src/built_in/ft_pwd.c					\
		src/built_in/ft_builtin.c				\
		src/exec/ft_redirection.c				\
		src/exec/ft_here_doc.c					\
		src/exec/get_cmd_pipex.c				\
		src/exec/pipex.c						\
		src/exec/pipex_manager.c				\
		src/exec/ft_get_fd_heredoc.c			\
		src/signal/ft_ctrl_c.c					\
		src/utils/ft_print.c					\
		src/utils/ft_free.c						\
		src/utils/get_next_line.c				\
		src/utils/ft_close.c					\
		src/utils/ft_error_msg.c				\
		src/utils/ft_get_env_tab.c				\
		src/utils/ft_dup.c						\
		src/list/parser/ft_parser_size.c		\
		src/list/parser/ft_parser_add_back.c	\
		src/list/parser/ft_parser_clear.c		\
		src/list/parser/ft_parser_delone.c		\
		src/list/parser/ft_parser_last.c		\
		src/list/parser/ft_parser_new.c			\
		src/list/parser/ft_redir_clear.c		\
		src/list/parser/ft_redir_delone.c		\
		src/list/parser/ft_redir_new.c			\
		src/list/parser/ft_redir_add_back.c		\
		src/list/parser/ft_redir_last.c			\
		src/list/lexer/ft_lexer_add_back.c		\
		src/list/lexer/ft_lexer_add_front.c		\
		src/list/lexer/ft_lexer_clear.c			\
		src/list/lexer/ft_lexer_delone.c		\
		src/list/lexer/ft_lexer_first.c			\
		src/list/lexer/ft_lexer_last.c			\
		src/list/lexer/ft_lexer_new.c			\
		src/list/lexer/ft_lexer_size.c			\
		src/list/env/ft_env_add_back.c			\
		src/list/env/ft_env_add_front.c			\
		src/list/env/ft_env_clear.c				\
		src/list/env/ft_env_delone.c			\
		src/list/env/ft_env_first.c				\
		src/list/env/ft_env_last.c				\
		src/list/env/ft_env_new.c				\
		src/list/env/ft_env_size.c

OBJS = ${SRCS:.c=.o}

all : lib ${NAME}

./src/%.o: ./src/%.c ${HEADERS} ${LIBFT_LIB}
	${CC} ${CFLAGS} -I${HEADER_PATH} -g -c $< -o $@


${NAME} : ${OBJS}
	echo "\033[1;34m\nCompiling: \033[1;33m minishell..."
	${CC} ${CFLAGS} ${OBJS} ${LIBFT_LIB} -o ${NAME} -lreadline
	echo "\033[1;32mSucces !\n"
	
force :

lib: force
	@make -sC $(LIBFT_PATH)

clean :
	echo "\033[1;31mDelete *.o"
	make clean -sC ${LIBFT_PATH}
	${RM} ${OBJS} 
	echo "\033[1;32mSucces !\n"

fclean: clean
	echo "\033[1;31mDelete *.a && executable"
	make fclean -sC ${LIBFT_PATH}
	${RM} ${NAME}
	echo "\033[1;32mSucces !\n"

re : fclean all

.SILENT:

.PHONY: all clean fclean re force
