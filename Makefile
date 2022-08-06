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

tetris: main.c
	gcc main.c init.c time.c operate.c block.c output.c window.c -lncurses -o tetris

fclean:
	${RM} tetris
 
 re: fclean tetris

.PHONY: fclean re
