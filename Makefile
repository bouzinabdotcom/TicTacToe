all: main.o tictactoe.o
	gcc main.o tictactoe.o -o tictactoe
	make clean

tictactoe.o: tictactoe.c
	gcc -c tictactoe.c

main.o: main.c
	gcc -c main.c

clean: 
	rm -rf *.o