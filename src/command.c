#include "board.h"
#include "strategy.h"

#include <stdio.h>
#include <stdlib.h>

void print_command(command *inp){
    printf("%c %d %d\n", inp->c, inp->x, inp->y);
}

int parse_command(board* layover, board* mines, command* cmd){
    int ret = 0;
    if(cmd->give_up){
        ret = 3;
        goto RET;
    }
    if(cmd->x < 0 || cmd->x >= layover->width || cmd->y < 0 || cmd->y >= layover->height){
        ret = -3;
        goto RET;
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
    RET:
    free(cmd);
    return ret;
}

command* flag_command(int x, int y){
    command* cmd = (command*)malloc(sizeof(command));
    cmd->c = 'f';
    cmd->x = x;
    cmd->y = y;
    cmd->give_up = 0;
    return cmd;
}

command* uncover_command(int x, int y){
    command* cmd = (command*)malloc(sizeof(command));
    cmd->c = 'u';
    cmd->x = x;
    cmd->y = y;
    cmd->give_up = 0;
    return cmd;
}

command* give_up_command(void){
    command* cmd = (command*)malloc(sizeof(command));
    cmd->c = 'x';
    cmd->x = -1;
    cmd->y = -1;
    cmd->give_up = 1;
    return cmd;
}

