#include "test_strategy.h"
#include "minunittest.h"
#include "strategy.h"

static char* test_s_first_click(void){

}

static char* all_tests_strategy(void){
    mu_run_test(test_s_first_click);
    return 0;
}