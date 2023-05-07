//
// Created by acm on 5/6/23.
//

#include <gtest/gtest.h>

extern "C" {
#include "../src/util.h"
#include "../src/board.h"
}

// Demonstrate some basic assertions.
TEST(BoardTest, get_piece) {
    cx_board_t *board = cx_board_init();
    EXPECT_EQ(cx_board_get_piece(board, 0), CX_BLACK_ROOK);
    EXPECT_EQ(cx_board_get_piece(board, 63), CX_WHITE_ROOK);

    cx_board_free(board);
}
