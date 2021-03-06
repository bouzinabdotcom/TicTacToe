typedef int** grid;
typedef int line, col;
typedef int result;

#define O_WINS -1
#define X_WINS 1
#define X 1
#define O -1
#define DRAW 0
#define NOT_FINISHED 555
#define EMPTY 666

extern int N;

void setN(int);

grid create_empty_grid(void);
result check_line(line, grid);
result check_col(col, grid);
result check_diag(grid);
int empty_cells(grid);
result game_state(grid);

char celltochar(int);

void printg(grid);
void print_result(result);

//random player
void random_player(int, grid); // call srand(time(NULL)) before calling this function

//minimax
int max(int, int);
int min(int, int);
int minimax(grid, int);
void bestMove(grid);
void MinMax(grid);
void MinMax_abp(grid, int, int);
void MinMax_abp_xy(grid, int, int, int *, int *);
int Min(grid);
int Max(grid);
int Min_abp(grid, int, int);
int Max_abp(grid, int, int);