#include "board.h"

#ifndef __STRATEGY_H__
#define __STRATEGY_H__

struct command{
    char c;
    int x; 
    int y;
    int give_up;
}; 

typedef struct command command; 
void print_command(command* inp);
int parse_command(board* layover, board* mines, command* input);


typedef command* (*strategy_ptr)(board*, int);

strategy_ptr select_strategy(int mode);
command* s_first_click(board* layover, int steps);

#endif
