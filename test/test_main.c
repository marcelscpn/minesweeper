#include "minunittest.h"
#include "test_board.h"
#include "test_strategy.h"
#include <stdlib.h>
#include <stdio.h>

int tests_run;

int main(void){
    char* result_board = all_tests_board();
    char* result_strategy = all_tests_strategy();
    if(result_board != 0){
        printf("%s\n", result);
    }
    else{
        printf("Board.c: All tests passed\n");
    }
    if(result_strategy != 0){
        printf("%s\n", result);
    }
    else{
        printf("Strategy.c: All tests passed\n");
    }
    printf("Tests run: %d\n", tests_run);
    return 0;
}