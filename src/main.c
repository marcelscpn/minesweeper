#include "board.h"
#include "strategy.h"

#include <stdio.h>

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