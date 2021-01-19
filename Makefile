all: main.c ez-draw.c morpion/tictactoe.c
	gcc -o main main.c ez-draw.c morpion/tictactoe.c -lX11 -lXext 


clean: 
	rm -rf *.o