#include "strategy.h"
#include "board.h"
#include "command.h"

#include <time.h>
#include <stdlib.h> 
#include <stdio.h> 

strategy_ptr select_strategy(int mode){
    switch(mode){
        case 1:
            return s_first_click;
        case 2:
            return s_simple_search;
    }
}

command* s_first_click(board* layover, int steps){
    if(steps == 0){
        return uncover_command(0, 0);
    }
    else{
        return give_up_command();
    }
}

command* s_simple_search(board* layover, int steps){
    if(steps == 0){
        return uncover_command(0, 0);
    }
    int n_mines, n_flags;
    int* n_empty_fields;
    command* cmd;
    for(int i = 0; i < layover->height; i++){
        for(int j = 0; j < layover->width; j++){
            n_mines = *(*(layover->cell + i) + j);
            if(n_mines > 0){
                printf("%d,%d, %d\n", i, j, n_mines);
                n_empty_fields = index_neighborhood(layover, i, j, -1);
                n_flags = count_neighboring_indices(layover, i, j, -2);
                if(n_mines - n_flags == *n_empty_fields){
                    int y = *(n_empty_fields + 1);
                    int x = *(n_empty_fields + 2);
                    return flag_command(x, y);
                }
                if(n_mines - n_flags == 0 && *n_empty_fields > 0){
                     int y = *(n_empty_fields + 1);
                     int x = *(n_empty_fields + 2);
                     return uncover_command(x, y);

                }
            }
        }
    }
    return give_up_command();
}
