#include "board.h"
#include "command.h"

#ifndef __STRATEGY_H__
#define __STRATEGY_H__


typedef command* (*strategy_ptr)(board*, int);
strategy_ptr select_strategy(int mode);
command* s_first_click(board* layover, int steps);
command* s_simple_search(board* layover, int steps);


#endif
