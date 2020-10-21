#include "minunittest.h"

#ifndef __TEST_BOARD_H__
#define __TEST_BOARD_H__

static char* test_create_layover(void);

static char* test_neighborhood_corner(void);
static char* test_neighborhood_edge(void);
static char* test_neighborhood_centre(void);

static char* test_count_neighboring_indices(void);

static char* test_flag_invalid(void);
static char* test_flag_unflagged(void);
static char* test_flag_flagged(void);

static char* test_uncover(void);

static char* test_check_covered(void);

static char* all_tests_board(void);
#endif