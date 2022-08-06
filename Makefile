# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rykawamu </var/mail/rykawamu>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/06 23:47:18 by rykawamu          #+#    #+#              #
#    Updated: 2022/08/06 23:47:22 by rykawamu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= tetris
CC		= gcc
CFLAG	= -Wall -Wextra -Werror -lncurses
SRCS	= main.c init.c time.c operate.c block.c output.c window.c
OBJS	= ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${SRCS} ${OBJS}
	${CC} ${CFLAG} -o ${NAME} ${SRCS}

tetris: main.c
	gcc main.c init.c time.c operate.c block.c output.c window.c -lncurses -o tetris

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}
 
 re: fclean tetris

.PHONY: all tetris clean fclean re
