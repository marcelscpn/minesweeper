#include <stdio.h>
#include <stdlib.h>

struct board{
	int height;
	int width;
	int** cell;
};

typedef struct board board;

board* create_new_board(int h, int w, int percentage){
	board* ret = (board*)malloc(sizeof(board));
	ret->height = h;
	ret->width = w;
	ret->cell = (int**)malloc(ret->height * sizeof(int *));
	int i, j;
	for(i = 0; i < ret->height; i++){
		*(ret->cell + i) = malloc(ret->width * sizeof(int));
		for(j = 0; j < ret->width; j++){
			*(*(ret->cell + i) + j) = 0;
		}
	}
	int num = h * w * percentage / 100;
	int x, y;
	while(num){
		x = rand() % ret->width; 
		y = rand() % ret->height;
		if(!*(*(ret->cell + y) + x)){
			*(*(ret->cell + y) + x) = 1;
			num--; 
		}	
	}
	return ret;
}

int flag(board* layover, int x, int y){
	if(*(*(layover->cell + y) + x) >= 0){
		return 1;
	}
	else if(*(*(layover->cell + y) + x) == -1){
		*(*(layover->cell + y) + x) = -2;
		return 0;
	}
	else if(*(*(layover->cell + y) + x) == -2){
		*(*(layover->cell + y) + x) == -1;
		return 0;
	}
}


int main(int argc, char* argv[]){
	board* B = create_new_board(10, 20, 10);
	int i, j;
	for(i = 0; i < 10; i++){
		for(j = 0; j < 20; j++){
			printf("%d ", *(*(B->cell + i) + j));
		}
		printf("\n");
	}
	return 0;
}


