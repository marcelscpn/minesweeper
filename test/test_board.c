#include "test_board.h"
#include "minunittest.h"
#include "board.h"

static char* test_neighborhood_corner(void){
    board* layover = create_layover(3, 4, 0);

}

static char* test_neighborhood_edge(void){

}

static char* test_neighborhood_centre(void){
    
}

static char* test_count_neighboring_indices(void){

}

static char* test_flag_invalid(void){

}

static char* test_flag_unflagged(void){

}

static char* test_flag_flagged(void){

}

static char* test_uncover(void){

}

static char* test_check_covered(void){
    
}

static char* all_tests_board(void){
    mu_run_test(test_neighborhood_corner);
    mu_run_test(test_neighborhood_edge);
    mu_run_test(test_neighborhood_centre);
    mu_run_test(test_count_neighboring_indices);
    mu_run_test(test_flag_invalid);
    mu_run_test(test_flag_unflagged);
    mu_run_test(test_flag_flagged);
    mu_run_test(test_uncover);
    mu_run_test(test_check_covered);
    mu_run_test(all_tests_board);
    return 0;
}