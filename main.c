#include "ez-draw.h"
#include "core/tictactoe.h"

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
            
            ez_draw_text (ev->win, EZ_MC, l/2, w-10, "r: replay     q: quit", r==X_WINS ? "X" : "O");


        }
    }

} 

void init_game(int);

void handle_key_press(Ez_event *ev) {
    if(strcmp(ev->key_string, "q")==0)
        ez_window_destroy(ev->win);
    
    else if (strcmp(ev->key_string, "r") == 0) {
        ez_window_destroy(ev->win);
        init_game(N);
    }
}


void win1_on_event (Ez_event *ev)                /* Called by ez_main_loop() */
{                                                /* for each event on win1   */
    switch (ev->type) {
        case Expose   : win1_on_expose(ev); break;
        case ButtonPress : make_move_on_click(ev); break;
        case KeyPress: handle_key_press(ev); break;
    }
}

void init_game(int size) {
    N = size;
    ez_window_create(l, w, "TicTacToe", win1_on_event);

    
    g = create_empty_grid(); 
    


}







int main() {

    if(ez_init() < 0) exit(1);
    
    char answer;
    int temp;

    srand(time(NULL)); //init seed for the rand() call in the random_player function

    do{
        printf("Please choose size of grid (>1): ");
        scanf("%d", &temp);
        setN(temp);
    }while(N<2);


    init_game(N);


    ez_main_loop();

    exit(0);
}