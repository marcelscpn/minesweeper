#include "board.h"

#ifndef __STRATEGY_H__
#define __STRATEGY_H__

int s_first_click(board* layover, board* mines, int steps);
int s_recursive(board* layover, board* mines, int steps);
int s_recursive_random(board* layover, board* mines, int steps);

#endif
