#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct board{
	int height;
	int width;
	int** cell;
};

typedef struct board board;

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
	//int num = h * w * percentage / 100;
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
        int sum = 0;
        if(x - 1 >= 0 && *(*(layover->cell + y) + x -1) == ind)
                sum += *(*(layover->cell + y) + x - 1);
        if(x - 1 >= 0 && y + 1 < layover->width && *(*(layover->cell + y + 1) + x -1) == ind)
                sum += *(*(layover->cell + y + 1) + x - 1);
        if(y + 1 < layover->width && *(*(layover->cell + y + 1) + x) == ind)
                sum += *(*(layover->cell + y + 1) + x);
        if(x + 1 < layover->height && y + 1 < layover->width && *(*(layover->cell + y + 1) + x + 1) == ind)
                sum += *(*(layover->cell + y + 1) + x + 1);
        if(x + 1 < layover->height && *(*(layover->cell + y) + x + 1) == ind)
                sum += *(*(layover->cell + y) + x + 1);
        if(x + 1 < layover->height && y - 1 >= 0 && *(*(layover->cell + y - 1) + x) == ind)
                sum += *(*(layover->cell + y - 1) + x + 1);
        if(y - 1 >= 0 && *(*(layover->cell + y - 1) + x) == ind)
                sum += *(*(layover->cell + y - 1) + x);
        if(x - 1 >= 0 && y - 1 >= 0 && *(*(layover->cell + y - 1) + x - 1) == ind)
                sum += *(*(layover->cell + y - 1) + x - 1);
        return sum;
}

/*int neighboring_mines(board* mines, int x, int y){
	int sum = 0;
	if(x - 1 >= 0)
		sum += *(*(mines->cell + y) + x - 1);
	if(x - 1 >= 0 && y + 1 < mines->width)
		sum += *(*(mines->cell + y + 1) + x - 1);
	if(y + 1 < mines->width)
		sum += *(*(mines->cell + y + 1) + x);
	if(x + 1 < mines->height && y + 1 < mines->width)
		sum += *(*(mines->cell + y + 1) + x + 1);
	if(x + 1 < mines->height)
		sum += *(*(mines->cell + y) + x + 1);
	if(x + 1 < mines->height && y - 1 >= 0)
		sum += *(*(mines->cell + y - 1) + x + 1);
	if(y - 1 >= 0)
		sum += *(*(mines->cell + y - 1) + x);
	if(x - 1 >= 0 && y - 1 >= 0)
		sum += *(*(mines->cell + y - 1) + x - 1);
	return sum;
}*/


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
		//printf("clicked on mine\n");
		for(i = 0; i < layover->height; i++){
			for(j = 0; j < layover->width; j++){
				if(*(*(mines->cell + i) + j) == 1 && *(*(layover->cell + i) + j) == -1){
					*(*(layover->cell + i) + j) = -3;
					//printf("Mine exploded at %d %d\n", i, j);
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
			if(x - 1 >= 0) 
				uncover(layover, mines, x - 1, y, 1);
			if(x - 1 >= 0 && y + 1 < layover->width)
				uncover(layover, mines, x - 1, y + 1, 1);
			if(y + 1 < layover->width)
				uncover(layover, mines, x, y + 1, 1);
			if(x + 1 < layover->height && y + 1 < layover->width)
				uncover(layover, mines, x + 1, y + 1, 1);
			if(x + 1 < layover->height)
				uncover(layover, mines, x + 1, y, 1);
			if(x + 1 < layover->height && y - 1 >= 0)
				uncover(layover, mines, x + 1, y - 1, 1);
			if(y - 1 >= 0)
				uncover(layover, mines, x, y - 1, 1);
			if(x - 1 >= 0 && y - 1 >= 0)
				uncover(layover, mines, x - 1, y - 1, 1);
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

/*int strategy(board* layover, board* mines, int step){
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
}*/


int main(int argc, char* argv[]){
	if(argc != 5){
		printf("Please specify board size and number of mines\n");
		return 1;
	}	
	int mode, h, w, num;
	sscanf(argv[1], "%d", &mode);
	sscanf(argv[2], "%d", &h);
	sscanf(argv[3], "%d", &w);
	sscanf(argv[4], "%d", &num);
	board* mines = create_new_board(h, w, num);
	board* layover = create_layover(h, w, -1);
	char c;
	int x, y, steps = 0;
	print_layover(mines);
	if(!mode){
		while(1){
			print_layover(layover);
			printf("%d> ", steps);
			scanf(" %c %d %d", &c, &y, &x);
			//printf("INPUT SCANNED: %c %d %d\n", c, x, y);
			if(x < 0 || x >= w || y < 0 || y >= h){
				printf("Coordinates not in range\n");
				steps++;
				continue;	
			}
			if(c == 'f'){
				if(flag(layover, x, y)){
					printf("Cannot flag cells already uncovered\n");
				}
			}
			else if(c == 'u'){
				switch(uncover(layover, mines, x, y, 0)){
					case 1: printf("Cannot uncover cells already uncovered or flagged\n");
						break;
					case -1: printf("You clicked on a mine! Idiot...\n");
						 print_layover(layover);
						 return 0;
				}
			}
			steps++;
			if(check_covered(layover)){
				printf("Game finished, you've found all mines!\n");
			       	print_layover(layover);	
				return 0;
			}
		}
	}
	else{
	/*	while(1){
			print_layover(layover);
			if(strategy(layover, mines,  steps)){
				printf("Computer has finished\n");
			}
			steps++;	
		}
	*/
	printf("Strategy not yet implemented\n");
	}
	return 0;
}


