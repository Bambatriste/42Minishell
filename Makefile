# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 14:32:03 by lnelson           #+#    #+#              #
#    Updated: 2021/12/29 18:07:34 by lnelson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRCS_DIR	= srcs/

OBJS_DIR	= objs/

INCLS_DIR	= includes/

LIBS_DIR	= libft/

CFLAGS		= -Wall -Wextra -Werror -I ${INCLS_DIR} -g3

FLAGS		= -L ${LIBS_DIR} -lft -lreadline

CC			= gcc

SRCS		=	main.c\
				exec.c\
				ft_cmd_get_add.c\
				ft_convert.c\
				ft_env.c\
				ft_export.c\
				ft_redir_lst.c\
				ft_tok_lst.c\
				get_lists.c\
				parce_tokens.c\
				utils.c\
				ft_cd.c\
				ft_cmd_lst.c\
				ft_copy_env.c\
				ft_echo.c\
				ft_exit.c\
				ft_pwd.c\
				ft_search_value.c\
				ft_sort_export.c\
				ft_unset.c\
				spec_tokens.c\
				get_path.c\

OBJS		= ${SRCS:.c=.o}

OBJS		:= ${addprefix ${OBJS_DIR}, ${OBJS}}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
			${CC} ${CFLAGS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			make -C ${LIBS_DIR}
			${CC} -o $@ ${OBJS} ${FLAGS} ${MLX_FLAGS}

sanitize:	${OBJS}
			make -C ${LIBS_DIR}
			${CC} -o $@ ${OBJS} ${FLAGS} ${MLX_FLAGS} -g3 -fsanitize=address	

clean:
			make clean -C ${LIBS_DIR}
			${RM} ${OBJS}

cclean:
			${RM} ${OBJS}
			
fclean:		clean
			make fclean -C ${LIBS_DIR}
			${RM} ${NAME} sanitize

re:			fclean all

RM			= rm -f
