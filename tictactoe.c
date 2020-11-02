#include "tictactoe.h"
#include <stdlib.h>
#include <stdio.h>


grid create_empty_grid(void){
    grid g = (grid)malloc(3*sizeof(int*));
    for(int i=0; i<3; i++){
        *(g+i) = (int*)malloc(3*sizeof(int));
        for(int j=0; j<3; j++)
            *(*(g+i)+j) = EMPTY;
    }
    return g;
}

result check_line(line l, grid g){
    result r=0;
    for(int i=0; i<3; i++){
        r+=g[l][i];
    }
    if(r != O_WINS*3 && r!=X_WINS*3)
        return DRAW;
    return r/3;
}

result check_col(col c, grid g){
    result r=0;
    for(int i=0; i<3; i++){
        r+=g[i][c];
    }
    if(r!= O_WINS*3 && r!=X_WINS*3)
        return DRAW;
    return r/3;
}

result check_diag(grid g) {
    if((g[0][0] == g[1][1] && g[1][1]==g[2][2]) || (g[0][2]==g[1][1] && g[1][1]==g[2][0]))
        return g[1][1]!=EMPTY ? g[1][1] : DRAW;

    return DRAW;
}

int empty_cells(grid g){
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(g[i][j] == EMPTY) 
                return 1;

    return 0;
}

result game_state(grid g){
    result res;
    for(int i=0; i<3; i++)
        if((res=check_line(i, g)) != DRAW || (res=check_col(i, g)) != DRAW)
            return res;
    
    if((res=check_diag(g)) != DRAW)
        return res;

    else if(empty_cells(g))
        return NOT_FINISHED;

    else return DRAW;
}

char celltochar(int cell) {
    switch(cell){
        case EMPTY: return ' ';
        case O: return 'O';
        case X: return 'X';
        default: puts("error");
                exit(EXIT_FAILURE);
    }
}

void printg(grid g){
    puts("  0 1 2");
    puts("  _ _ _");
    for(int i = 0; i<3; i++){
        printf("%d|%c|%c|%c|\n", i, celltochar(g[i][0]), celltochar(g[i][1]), celltochar(g[i][2]));
        puts("  - - -");
    }

    puts("");
}

void print_result(result r){
    switch(r) {
        case O_WINS: puts("O wins!!!");
                    break;
        case X_WINS: puts("X wins!!!");
                    break;
        case DRAW: puts("No one wins this time.");
                    break;
        default: puts("Something went wrong!");
                    break;
    }
}

void random_player(int player, grid g) {
    //seed should be initialized before calling this function
    int x, y;
    do{
        x = rand()%3;
        y = rand()%3; 
    }while(g[y][x] != EMPTY);

    g[y][x] = player;
}

int max(int a, int b) {
    return a>b?a:b;
}

int min(int a, int b) {
    return a<=b?a:b;
}

int minimax(grid g, int maximizingPlayer) {
    result res = game_state(g);
    if(res != NOT_FINISHED){
        return res;
    }
    int value;
    if(maximizingPlayer==X){
        value = -2;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(g[i][j] == EMPTY){
                    g[i][j] = X;
                    value = max(value, minimax(g, O));
                    g[i][j] = EMPTY;
                }
            }
        }
    }

    if(maximizingPlayer==O){
        value = 2;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(g[i][j] == EMPTY){
                    g[i][j] = O;
                    value = min(value, minimax(g, X));
                    g[i][j] = EMPTY;
                }
            }
        }
    }

    return value;

}

void bestMove(grid g) {
    int bestScore = -2, score;
    int x, y;
    for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(g[i][j] == EMPTY){
                    g[i][j] = X;
                    score = minimax(g, O);
                    g[i][j] = EMPTY;
                    if(score>bestScore){
                        bestScore = score;
                        x=i;
                        y=j;
                    }
                }
            }
    }
    g[x][y] = X;

}
