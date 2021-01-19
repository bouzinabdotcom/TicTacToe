#include "tictactoe.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int N=3;

void setN(int val) {
    N = val;
}

grid create_empty_grid(void){
    grid g = (grid)malloc(N*sizeof(int*));
    for(int i=0; i<N; i++){
        *(g+i) = (int*)malloc(N*sizeof(int));
        for(int j=0; j<N; j++)
            *(*(g+i)+j) = EMPTY;
    }
    return g;
}

result check_line(line l, grid g){
    result r=0;
    for(int i=0; i<N; i++){
        r+=g[l][i];
    }
    if(r != O_WINS*N && r!=X_WINS*N)
        return DRAW;
    return r/N;
}

result check_col(col c, grid g){
    result r=0;
    for(int i=0; i<N; i++){
        r+=g[i][c];
    }
    if(r!= O_WINS*N && r!=X_WINS*N)
        return DRAW;
    return r/N;
}
//TODO
result check_diag(grid g) {
    result r1=0, r2=0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(i==j)
                r1+=g[i][j];
            if(j+i == N-1)
                r2+=g[i][j];

        }
    }
    if(r1!= O_WINS*N && r1!=X_WINS*N && r2!= O_WINS*N && r2!=X_WINS*N)
        return DRAW;
    return (r1== O_WINS*N || r1==X_WINS*N) ? r1/N : r2/N;

    // if((g[0][0] == g[1][1] && g[1][1]==g[2][2]) || (g[0][2]==g[1][1] && g[1][1]==g[2][0]))
    //     return g[1][1]!=EMPTY ? g[1][1] : DRAW;

    // return DRAW;
}

int empty_cells(grid g){
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(g[i][j] == EMPTY) 
                return 1;

    return 0;
}

result game_state(grid g){
    result res;
    for(int i=0; i<N; i++)
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
    printf("  ");
    for(int i = 0; i<N; i++)
        printf("%d ", i);
    puts("");
    printf("  ");
    for(int i = 0; i<N; i++)
        printf("_ ");
    puts("");
    for(int i = 0; i<N; i++){
        printf("%d|", i);
        for(int j = 0; j<N; j++)
            printf("%c|", celltochar(g[i][j]));
        puts("");
        printf("  ");
        for(int j = 0; j<N; j++)
            printf("_ ");
        puts("");
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
        x = rand()%N;
        y = rand()%N; 
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
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
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
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
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
    for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
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

void MinMax(grid g) {
    int score = INT_MAX;
    int x=0, y=0, valeur;

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) {
            if(g[i][j] == EMPTY) {
                g[i][j] = X;
                valeur = Max(g);
                if(score > valeur){
                    score = valeur;
                    x=i;
                    y=j;
                }
                g[i][j] = EMPTY;
            }
        }
     g[x][y] = X;
    
}

void MinMax_abp(grid g, int alpha, int beta) {
    int x=0, y=0, valeur;

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) {
            if(g[i][j] == EMPTY) {
                g[i][j] = X;
                valeur = Max_abp(g, alpha, beta);
                if(beta > valeur){
                    beta = valeur;
                    x=i;
                    y=j;
                }
                g[i][j] = EMPTY;
            }
        }
     g[x][y] = X;
    
}

void MinMax_abp_xy(grid g, int alpha, int beta, int * xi, int * yi) {
    int x=0, y=0, valeur;

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) {
            if(g[i][j] == EMPTY) {
                g[i][j] = X;
                valeur = Max_abp(g, alpha, beta);
                if(beta > valeur){
                    beta = valeur;
                    x=i;
                    y=j;
                }
                g[i][j] = EMPTY;
            }
        }
     *xi = x;
     *yi = y;
    
}

int Max(grid g) {
    switch(game_state(g)){
        case O_WINS:
            return 10;
        case X_WINS:
            return -10;
        case DRAW: 
            return 0;
    }

    int score = INT_MIN, valeur;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) {

            if(g[i][j] == EMPTY) {
                g[i][j] = O;
                valeur = Min(g);
                if(score<valeur) 
                    score = valeur;
                g[i][j] = EMPTY;
            }
        }
    
    return score;
}

int Max_abp(grid g, int alpha, int beta) {
    switch(game_state(g)){
        case O_WINS:
            return 10;
        case X_WINS:
            return -10;
        case DRAW: 
            return 0;
    }

    int valeur;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) {

            if(g[i][j] == EMPTY) {
                g[i][j] = O;
                valeur = Min_abp(g, alpha, beta);
                g[i][j] = EMPTY;
                
                if(alpha<valeur) 
                    alpha = valeur;
                if(alpha >= beta)
                    return alpha;
            }
        }
    
    return alpha;
}

int Min(grid g) {
    switch(game_state(g)){
        case O_WINS:
            return 10;
        case X_WINS:
            return -10;
        case DRAW: 
            return 0;
    }

    int score = INT_MAX, valeur;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) {
            if(g[i][j] == EMPTY) {
                g[i][j] = X;
                valeur = Max(g);
                if(score>valeur) 
                    score = valeur;
                g[i][j] = EMPTY;
            }
        }
    
    return score;
}

int Min_abp(grid g, int alpha, int beta) {
    switch(game_state(g)){
        case O_WINS:
            return 10;
        case X_WINS:
            return -10;
        case DRAW: 
            return 0;
    }

    int valeur;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) {
            if(g[i][j] == EMPTY) {
                g[i][j] = X;
                valeur = Max_abp(g, alpha, beta);
                g[i][j] = EMPTY;
                
                if(beta>valeur) 
                    beta = valeur;
                if(beta <= alpha)
                    return beta;
            }
        }
    
    return beta;
}

