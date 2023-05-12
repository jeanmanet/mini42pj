# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 12:02:12 by jmanet            #+#    #+#              #
#    Updated: 2023/05/12 10:25:09 by jmanet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRCS = $(wildcard srcs/*.c srcs/*/*.c srcs/*/*/*.c)

INCLUDES = includes/minishell.h

CC = gcc

FLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

LIBFT = libft/libft.a

LIBS =  ${LIBFT} -lreadline -lncurses

.c.o:
	${CC} -I ${INCLUDES} ${FLAGS} -c $< -o ${<:.c=.o}

OBJS = ${SRCS:.c=.o}

all : ${NAME}

${NAME} : ${LIBFT} ${OBJS} ${INCLUDES}
	${CC} ${SRCS} ${LIBS} -I includes/ -L/Users/jmanet/.brew/Cellar/readline/8.2.1/lib ${FLAGS} -o ${NAME}

${LIBFT}:
	make bonus -C libft/

clean :
	rm -rf ${OBJS}
	make clean -C libft/

fclean : clean
	rm -rf ${NAME}
	rm -rf ${LIBFT}

re : fclean all

d :
	${CC} ${SRCS} ${LIBS} -I includes/ -o ${NAME} -g

