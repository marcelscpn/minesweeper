#include "board.h"
#include "command.h"
#include "strategy.h"

#include "minunit.h"

MU_TEST(test_neighborhood_corner){
    board* layover = create_layover(3, 4, 0);
    int x = 0;
    int y = 0;
    int* n = neighborhood(layover, x, y);
    int n_compare[] = {3, 1, 0, 1, 1, 0, 1};
    int result = memcmp(n, n_compare, sizeof(n_compare));
    mu_assert_int_eq(0, result); 
}

MU_TEST(test_neighborhood_corner2){
    board* layover = create_layover(3, 4, 0);
    int x = 3;
    int y = 2;
    int* n = neighborhood(layover, x, y);
    int n_compare[] = {3, 2, 2, 1, 3, 1, 2};
    int result = memcmp(n, n_compare, sizeof(n_compare));
    mu_assert_int_eq(0, result); 
}

MU_TEST(test_neighborhood_corner3){
    board* layover = create_layover(4, 3, 0);
    int x = 2;
    int y = 3;
    int* n = neighborhood(layover, x, y);
    int n_compare[] = {3, 3, 1, 2, 2, 2, 1}; 
    int result = memcmp(n, n_compare, sizeof(n_compare));
    mu_assert_int_eq(0, result); 
}
MU_TEST(test_neighborhood_edge){
    board* layover = create_layover(3, 4, 0);
    int x = 0;
    int y = 1;
    int* n = neighborhood(layover, x, y);
    int n_compare[] = {5, 2, 0, 2, 1, 1, 1, 0, 1, 0, 0};
    int result = memcmp(n, n_compare, sizeof(n_compare));
    mu_assert_int_eq(0, result); 
}

MU_TEST(test_neighborhood_centre){
    board* layover = create_layover(3, 4, 0);
    int x = 1;
    int y = 1;
    int* n = neighborhood(layover, x, y);
    int n_compare[] = {8, 1, 0, 2, 0, 2, 1, 2, 2, 1, 2, 0, 2, 0, 1, 0, 0};
    int result = memcmp(n, n_compare, sizeof(n_compare));
    mu_assert_int_eq(0, result); 
}

MU_TEST(test_count_neighboring_indices){
    board* layover = create_layover(3, 4, 0);
    *(*(layover->cell)) = 1;
    int n = count_neighboring_indices(layover, 1, 1, 0);
    mu_assert_int_eq(7, n);
}

MU_TEST(test_index_neighborhood){
    board* layover = create_layover(3, 4, 0);
    *(*(layover->cell)) = 1;
    *(*(layover->cell + 1)) = 1;
    int* n = index_neighborhood(layover, 1, 1, 1);
    int n_compare[] = {2, 1, 0, 0, 0};
    int result = memcmp(n, n_compare, sizeof(n_compare));
    mu_assert_int_eq(0, result);
}

MU_TEST(test_index_neighborhood2){
    board* mines = create_layover(5, 5, 0);
    *(*(mines->cell + 2) + 3) = 1;
    board* layover = create_layover(5, 5, -1);
    uncover(layover, mines, 0, 0, 0); 
    int* n = index_neighborhood(layover, 2, 1, 1);
    int n_compare[] = {2, 2, 2, 1, 3};
    int* m = index_neighborhood(layover, 2, 1, -1); 
    int m_compare[] = {1, 2, 3};
    int* N = index_neighborhood(layover, 2, 1, 0);
    int N_compare[] = {5, 1, 1, 2, 1, 0, 3, 0, 2, 0, 1};
    int result  = memcmp(n, n_compare, sizeof(n_compare)); 
    int result2 = memcmp(m, m_compare, sizeof(m_compare)); 
    int result3 = memcmp(N, N_compare, sizeof(N_compare));
    mu_check(result == 0 && result2 == 0 && result3 == 0);
}

MU_TEST(test_remove_neighborhood){
    int A[] = {3, 1, 1, 1, 0, 0, 0};
    int B[] = {1, 1, 1};
    int* n = remove_neighborhood(A, B);
    int n_compare[] = {2, 1, 0, 0, 0};
    int result = memcmp(n, n_compare, sizeof(n_compare));
    mu_assert_int_eq(0, result);
}

MU_TEST(test_flag_invalid){
    board* layover = create_layover(3, 4, 0);
    int result = flag(layover, 0, 0);
    mu_assert_int_eq(1, result);
}

MU_TEST(test_flag_unflagged){
    board* layover = create_layover(3, 4, -1);
    int output = flag(layover, 0, 0);
    int cell = *(*(layover->cell));
    mu_check(output == 0 && cell == -2);
}

MU_TEST(test_flag_flagged){
    board* layover = create_layover(3, 4, -2);
    int output = flag(layover, 0, 0);
    int cell = *(*(layover->cell));
    mu_check(output == 0 && cell == -1);
}

MU_TEST(test_uncover_no_rec){
    board* mines = create_layover(3, 4, 0);
    *(*(mines->cell)) = 1;
    board* layover = create_layover(3, 4, -1);
    int output = uncover(layover, mines, 1, 0, 0);
//    printf("\n");
//    print_layover(mines);
//    print_layover(layover);
    int cell1 = *(*(layover->cell) + 1);
    int cell2 = *(*(layover->cell) + 2);
//    printf("%d, %d, %d", output, cell1, cell2);
    mu_check(output == 0 && cell1 == 1 && cell2 == -1);
}

MU_TEST(test_uncover_invalid){
    board* mines = create_layover(3, 4, 0);
    board* layover = create_layover(3, 4, -1);
    *(*(layover->cell)) = -2;
    int output = uncover(layover, mines, 0, 0, 0);
    mu_assert_int_eq(1, output);
}

MU_TEST(test_uncover_rec){
    board* mines = create_layover(3, 4, 0);
    *(*(mines->cell)) = 1;
    *(*(mines->cell + 2) + 3) = 1;
    board* layover = create_layover(3, 4, -1);
//    printf("\n");
//    print_layover(mines);
//    print_layover(layover);
    uncover(layover, mines, 3, 0, 0);
    int* n = *(layover->cell);
    int n_compare[] = {-1, 1, 0, 0};
    int result = memcmp(n, n_compare, sizeof(n_compare));
    mu_assert_int_eq(0, result);
}

MU_TEST(test_uncover_mine){
    board* mines = create_layover(3, 4, 0);
    *(*(mines->cell)) = 1;
    board* layover = create_layover(3, 4, -1);
    int output = uncover(layover, mines, 0, 0, 0);
    mu_assert_int_eq(-1, output);
}

//MU_TEST(test_check_covered){
//    board* layover 
//}

MU_TEST_SUITE(test_board_suite){
    MU_RUN_TEST(test_neighborhood_corner);
    MU_RUN_TEST(test_neighborhood_corner2);
    MU_RUN_TEST(test_neighborhood_corner3);
    MU_RUN_TEST(test_neighborhood_edge);
    MU_RUN_TEST(test_neighborhood_centre);
    MU_RUN_TEST(test_count_neighboring_indices);
    MU_RUN_TEST(test_index_neighborhood);
    MU_RUN_TEST(test_index_neighborhood2);
    MU_RUN_TEST(test_remove_neighborhood);
    MU_RUN_TEST(test_flag_invalid);
    MU_RUN_TEST(test_flag_unflagged);
    MU_RUN_TEST(test_flag_flagged);
    MU_RUN_TEST(test_uncover_no_rec);
    MU_RUN_TEST(test_uncover_invalid);
    MU_RUN_TEST(test_uncover_rec);
    MU_RUN_TEST(test_uncover_mine);
//    MU_RUN_TEST(test_check_covered);
}

//MU_TEST(test_parse_command_give_up){
//    
//}
//
//MU_TEST(test_parse_command_out_of_range){
//    
//}
//
//MU_TEST(test_parse_command_uncover_flag){
//
//}
//
//MU_TEST_SUITE(test_command_suite){
//    MU_RUN_TEST(test_parse_command_give_up);
//    MU_RUN_TEST(test_parse_command_out_of_range);
//    MU_RUN_TEST(test_parse_command_uncover_flag);
//}
//
//
//MU_TEST_SUITE(test_strategy_suite){
//}

int main(void){
    MU_RUN_SUITE(test_board_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
