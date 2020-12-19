#include "board.h"

#ifndef __COMMAND_H__
#define __COMMAND_H__

struct command{
    char c;
    int x; 
    int y;
    int give_up;
}; 

typedef struct command command; 
void print_command(command* inp);
int parse_command(board* layover, board* mines, command* input);
command* flag_command(int x, int y);
command* uncover_command(int x, int y);
command* give_up_command(void);

#endif
