#include "board.h"
#include "strategy.h"
#include "command.h"

#include <stdio.h>
#include <stdlib.h>

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
    int steps = 0;
    command* cmd;
    strategy_ptr strategy;
    if(mode){
        strategy = select_strategy(mode);
    }
    while(1){
        print_layover(layover); 
        printf("%d> ", steps);
        if(!mode){
            cmd = (command*)malloc(sizeof(command));
            cmd->give_up = 0;
            scanf(" %c %d %d", &cmd->c, &cmd->y, &cmd->x);
        }
        else{
            //cmd = s_first_click(layover, steps);
            cmd = strategy(layover, steps);
            print_command(cmd);
        }
        switch(parse_command(layover, mines, cmd)){
            case 0:
                break;
            case -1:
                printf("Cannot uncover cells already uncovered or flagged\n");
                break;
            case -2:
                printf("Cannot flag cells already uncovered\n");
                break;
            case -3:
                printf("Coordinates not in range\n");
                break;
            case 1:
                printf("Mine clicked. Dumb!\n");
                print_layover(layover);
                goto RET;
            case 3:
                printf("Computer has given up.\n");
                print_layover(layover);
                goto RET;
        }
        if(check_covered(layover)){
            printf("Game finished, you've found all mines!\n");
            print_layover(layover);	
            goto RET;
        }
        steps++;
    }
    RET:
    printf("It took: %d steps\n", steps);
    free_board(mines);
    free_board(layover);
	return 0;
}
