#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"

void print_layover(board* layover){
	int i, j;
	printf("  ");
	for(i = 0; i < layover->width; i++){
		printf("%d ", i % 10);
	}
	printf("\n");
	for(i = 0; i < layover->height; i++){
		printf("%d ", i % 10);
		for(j = 0; j < layover->width; j++){
			switch(*(*(layover->cell + i) + j)){
				case -4: printf("f ");
					 break;
				case -3: printf("# ");
					 break;
				case -2: printf("* ");
					 break;
				case -1: printf(". ");
					 break;
				case 0: printf("  ");
					break;
				default: printf("%d ", *(*(layover->cell + i) + j));
					 break;
			}
		}
		printf("\n");
	}
}

board* create_layover(int h, int w, int init){
        board* ret = (board*)malloc(sizeof(board));
        ret->height = h;
        ret->width = w;
        ret->cell = (int**)malloc(ret->height * sizeof(int *));
        int i, j;
        for(i = 0; i < ret->height; i++){
                *(ret->cell + i) = malloc(ret->width * sizeof(int));
                for(j = 0; j < ret->width; j++){
                        *(*(ret->cell + i) + j) = init;
                }
        }
	return ret;
}

board* create_new_board(int h, int w, int num){
	board* ret = create_layover(h, w, 0);
	if(num > h * w){
		num = h * w;
	}
	int x, y;
	srand((unsigned)time(NULL));
	while(num){
		x = rand() % ret->width; 
		y = rand() % ret->height;
		if(x == 0 && y == 0) continue;
		if(!*(*(ret->cell + y) + x)){
			*(*(ret->cell + y) + x) = 1;
			num--; 
		}	
	}
	return ret;
}

int count_neighboring_indices(board* layover, int x, int y, int ind){
		int i, sum = 0;
		int* neighb = neighborhood(layover, x, y);
		for(i = 0; i < *neighb; i++){
			sum += *(*(layover->cell + *(neighb + 2*i + 1)) + *(neighb + 2*i + 2));
		}
		free(neighb);
		return sum;
}

int* neighborhood(board* mines, int x, int y){
	int* ret = (int*)malloc(17 * sizeof(int));
	int count = 0;
	if(x - 1 >= 0){
		*(ret + 1 + 2*count) = y;
		*(ret + 2 + 2*count) = x - 1;
		count++;
	}
	if(x - 1 >= 0 && y + 1 < mines->width){
		*(ret + 1 + 2*count) = y + 1;
		*(ret + 2 + 2*count) = x - 1;
		count++;
	}
	if(y + 1 < mines->width){
		*(ret + 1 + 2*count) = y + 1;
		*(ret + 2 + 2*count) = x;
		count++;
	}
	if(x + 1 < mines->height && y + 1 < mines->width){
		*(ret + 1 + 2*count) = y + 1;
		*(ret + 2 + 2*count) = x + 1;
		count++;
	}
	if(x + 1 < mines->height){
		*(ret + 1 + 2*count) = y;
		*(ret + 2 + 2*count) = x + 1;
		count++;
	}
	if(x + 1 < mines->height && y - 1 >= 0){
		*(ret + 1 + 2*count) = y - 1;
		*(ret + 2 + 2*count) = x + 1;
		count++;
	}
	if(y - 1 >= 0){
		*(ret + 1 + 2*count) = y - 1;
		*(ret + 2 + 2*count) = x;
		count++;
	}
	if(x - 1 >= 0 && y - 1 >= 0){
		*(ret + 1 + 2*count) = y - 1;
		*(ret + 2 + 2*count) = x - 1;
		count++;
	}
	*ret = count; 
	return ret;
}

int flag(board* layover, int x, int y){
	if(*(*(layover->cell + y) + x) != -1 && *(*(layover->cell + y) + x) != -2){
		return 1;
	}
	else if(*(*(layover->cell + y) + x) == -1){
		*(*(layover->cell + y) + x) = -2;
		return 0;
	}
	else if(*(*(layover->cell + y) + x) == -2){
		*(*(layover->cell + y) + x) = -1;
		return 0;
	}
}

int uncover(board* layover, board *mines, int x, int y, int rec){
	int i, j;
	if(*(*(layover->cell + y) + x) != -1){ 
		return 1;
	}
	if(*(*(mines->cell + y) + x) == 1 && !rec){
		for(i = 0; i < layover->height; i++){
			for(j = 0; j < layover->width; j++){
				if(*(*(mines->cell + i) + j) == 1 && *(*(layover->cell + i) + j) == -1){
					*(*(layover->cell + i) + j) = -3;
				}
				else if(*(*(mines->cell + i) + j) == 0 && *(*(layover->cell + i) + j) == -2){
					*(*(layover->cell + i) + j) = -4;
				}
			}
		}
		return -1;
	}
	int n;	
	if(*(*(mines->cell + y) + x) == 0){	
		n = count_neighboring_indices(mines, x, y, 1);
		*(*(layover->cell + y) + x) = n;
		if(n == 0){
			int *neighb = neighborhood(layover, x, y);
			for(int i = 0; i < *neighb; i++){
				uncover(layover, mines, *(neighb + 2*i + 2), *(neighb + 2*i + 1), 1);
			}
			free(neighb);
		}		
	return 0;
	}
}

int check_covered(board* layover){
	int i, j;
	for(i = 0; i < layover->height; i++){
		for(j = 0; j < layover->width; j++){
			if(*(*(layover->cell + i) + j) == -1){
				return 0;
			}
		}
	}
	return 1;
}