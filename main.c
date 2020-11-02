#include "tictactoe.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(){


    grid g;
    int play_again;
    char answer;
    int player;
    int computer, ai;
    int available;
    int x, y;

    srand(time(NULL)); //init seed for the rand() call in the random_player function

    do {
        computer=0;
        ai=0;
        play_again = 0;
        g = create_empty_grid();
        printg(g);
        
        printf("Do you wanna play against the computer ?(y/n): ");
        fflush(stdin);
        scanf("%c", &answer);
        if(answer=='y' || answer=='Y') computer=1;

        printf("Do you wanna play against AI ? (impossible to beat) (y/n): ");
        fflush(stdin);
        scanf("%c", &answer);
        if(answer=='y' || answer=='Y') ai=1;

        player = O;


        do{
            
            available = 1; //always available until proven otherwise
            player=-player; // 1 for X and 0 for O

            
                
            
            printf("%c\'s turn.\n", celltochar(player));
            if(player == X && computer){
                // random_player(player, g);
                if(ai) bestMove(g);
                else random_player(X, g);
            }
            else{
                do {
                
                    if(!available)
                        puts("That cell is not available choose another one.");

                    if(x>2 || y>2) {
                        puts("line and column should be between 0 and 2.");
                    }
                    printf("Choose line: ");
                    fflush(stdin);
                    scanf("%d", &y);
                    printf("Choose column: ");
                    fflush(stdin);
                    scanf("%d", &x);
                    available = (g[y][x] == EMPTY);
                }while(!available || x > 2 || y>2);
                g[y][x] = player;

            }
            

            
            
            printg(g);
        }while(game_state(g)==NOT_FINISHED);

        print_result(game_state(g));
        printf("Play again ? (Y/N): ");
        fflush(stdin);
        scanf("%c", &answer);
        if(answer == 'y' || answer == 'Y') play_again=1;
    }while(play_again);

    return 0;
}