#include "tictactoe.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(){


    grid g;
    int play_again;
    char answer;
    int moves;
    int player;
    int randomPlayer=0;
    int available;
    int x, y;

    srand(time(NULL));

    do {
        play_again = 0;
        moves = 0;
        g = create_empty_grid();
        printg(g);

        printf("Do you wanna play against a random player (computer picking random cells) (y/n): ");
        scanf("%c", &answer);
        if(answer=='y' || answer=='Y') randomPlayer=1;


        do{
            available = 1; //always available until proven otherwise
            moves++;
            player=moves%2; // 1 for X and 0 for O

            
                
            
            printf("%c\'s turn.\n", celltochar(player));
            if(player == X && randomPlayer){
                random_player(player, g);
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