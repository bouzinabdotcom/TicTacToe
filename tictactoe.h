typedef int** grid;
typedef int line, col;
typedef int result;

#define O_WINS 0
#define X_WINS 1
#define X 1
#define O 0
#define DRAW -1
#define NOT_FINISHED 555
#define EMPTY 666

grid create_empty_grid(void);
result check_line(line, grid);
result check_col(col, grid);
result check_diag(grid);
int empty_cells(grid);
result game_state(grid);

char celltochar(int);

void printg(grid);
void print_result(result);