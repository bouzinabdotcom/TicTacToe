#include "ez-draw.h"
#include "morpion/tictactoe.h"

#include <stdio.h>
#include <stdio_ext.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>


int l = 600, w = 600;
grid g;
result r;



void win1_on_expose(Ez_event *ev) {
    for(int i=1; i<N; i++){
        ez_set_thick(4);

        ez_draw_line(ev->win,  i*l/N,  0, i*l/N,  w);
        ez_draw_line(ev->win,  0,  i*w/N, w, i*w/N);

    }
}

int getcoord(int xy) {
    return xy/(l/N);
}

void make_move_on_click(Ez_event *ev) {
    //O's turn
    int x = getcoord(ev->mx);
    int y = getcoord(ev->my);

    
    if(g[y][x] == EMPTY) {
        ez_draw_circle(ev->win, x*(l/N)+10, y*(l/N)+10, (x+1)*(w/N)-10, (y+1)*(w/N)-10);
        g[y][x] = O;

        //x's turn

        MinMax_abp_xy(g, INT_MIN, INT_MAX, &y, &x);
        ez_draw_line(ev->win,  x*(l/N)+10, y*(l/N)+10, (x+1)*(w/N)-10, (y+1)*(w/N)-10);
        ez_draw_line(ev->win,  x*(l/N)+10, (y+1)*(l/N)-10, (x+1)*(w/N)-10, y*(w/N)+10);
        g[y][x] = X;
        printg(g);

        r = game_state(g);
        printf("%d\n", check_diag(g));
        if(r != NOT_FINISHED) {
            
            ez_set_color(ez_black);
            ez_fill_rectangle(ev->win, 0, 0, l-1, w-1);
            print_result(r);
            ez_set_color(ez_white);
            if(r == DRAW)
                ez_draw_text (ev->win, EZ_MC, l/2, w/2, "DRAW");
            else 
                ez_draw_text (ev->win, EZ_MC, l/2, w/2, "%s WINS", r==X_WINS ? "X" : "O");


        }
    }

} 


void win1_on_event (Ez_event *ev)                /* Called by ez_main_loop() */
{                                                /* for each event on win1   */
    switch (ev->type) {
        case Expose   : win1_on_expose(ev); break;
        case ButtonPress : make_move_on_click(ev); break;
    }
}

void init_game(int size) {
    if(ez_init() < 0) exit(1);
    N = size;
    ez_window_create(l, w, "TicTacToe", win1_on_event);

    
    g = create_empty_grid(); 
    

    ez_main_loop();

    exit(0);

}







int main() {

    
    char answer;
    int temp;

    srand(time(NULL)); //init seed for the rand() call in the random_player function

    do{
        printf("Please choose size of grid (>1): ");
        scanf("%d", &temp);
        setN(temp);
    }while(N<2);


    init_game(N);


}