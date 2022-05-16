# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 13:40:44 by yboudoui          #+#    #+#              #
#    Updated: 2022/03/11 19:10:32 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	./srcs/

HEAD_DIR	=	./includes/

SRCS		=	${SRC_DIR}get_next_line.c\
				${SRC_DIR}get_next_line_utils.c
				
HEAD		=	${HEAD_DIR}get_next_line.h

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -D BUFFER_SIZE=$(BUFFER_SIZE) 

all:
			${CC} ${CFLAGS} -I${HEAD_DIR} ${SRCS}
