all: main.c ez-draw.c core/tictactoe.c
	gcc -o morpion main.c ez-draw.c core/tictactoe.c -lX11 -lXext 


clean: 
	rm -rf *.o