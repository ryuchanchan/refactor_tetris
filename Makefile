tetris: main.c
	gcc main.c init.c utils.c operate.c block.c output.c -lncurses -o tetris

fclean:
	${RM} tetris
 
 re: fclean tetris

.PHONY: fclean re