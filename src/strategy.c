#include "strategy.h"
#include "board.h"

#include <time.h>
#include <stdlib.h> 

int (*strategy_pointer)(board* layover, board* mines, int steps) = NULL;

int s_first_click(board* layover, board* mines, int steps){
	if(step == 0){
		uncover(layover, mines, 0, 0, 0);
		printf("%d> u 0 0\n", step);
		return 0;
	}
	else{
		int i, j, N, n;
		for(i = 0; i < layover->height; i++){
			for(j = 0; j < layover->width; j++){
				if(*(*(layover->cell + j) + i) == 1 && count_neighboring_indices(j, i, -1) == 1){
					
				}	
			}
		}
	}
}