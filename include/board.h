#ifndef __BOARD_H__
#define __BOARD_H__

struct board{
	int height;
	int width;
	int** cell;
};

typedef struct board board;

void print_layover(board* layover);
board* create_layover(int h, int w, int init);
board* create_new_board(int h, int w, int num);
int free_board(board* b);
int* neighborhood(board* layover, int x, int y);
int count_neighboring_indices(board* layover, int x, int y, int ind);
int* index_neighborhood(board* layover, int x, int y, int ind);
int* remove_neighborhood(int* A, int* B);
int flag(board* layover, int x, int y);
int uncover(board* layover, board *mines, int x, int y, int rec);
int check_covered(board* layover);

#endif
