#include "strategy.h"
#include "board.h"

#include <time.h>
#include <stdlib.h> 
#include <stdio.h> 

void print_command(command *inp){
    printf("%c %d %d\n", inp->c, inp->x, inp->y);
}

int parse_command(board* layover, board* mines, command* cmd){
    int ret = 0;
    if(cmd->give_up){
        ret = 3;
    }
    if(cmd->x < 0 || cmd->x >= layover->width || cmd->y < 0 || cmd->y >= layover->height){
        ret = -3;
    }
    switch(cmd->c){
        case 'u':
            switch(uncover(layover, mines, cmd->x, cmd->y, 0)){
                case 1: ret = -1; 
                    break;
                case -1: ret = 1;
                    break;
            }
            break;
        case 'f': 
            if(flag(layover, cmd->x, cmd->y)){
                ret = -2; 
            }
            break;
    }
    free(cmd);
    return ret;
}


strategy_ptr select_strategy(int mode){
    switch(mode){
        case 1:
            return s_first_click;
    }
}

command* s_first_click(board* layover, int steps){
    printf("strategy running...\n");
    command* cmd = (command*)malloc(sizeof(command));
	cmd->c = 'u';
    cmd->x = 0;
    cmd->y = 0;
    cmd->give_up = 1;
    return cmd;
}

