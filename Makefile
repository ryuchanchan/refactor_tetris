tetris: main.c
	gcc main.c init.c time.c operate.c block.c output.c window.c -lncurses -o tetris

fclean:
	${RM} tetris
 
 re: fclean tetris

.PHONY: fclean re