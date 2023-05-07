//
// Created by acm on 5/6/23.
//

#include <gtest/gtest.h>

extern "C" {
#include "../src/util.h"
#include "../src/board.h"
#include "../src/print.h"
}

TEST(BoardTest, get_piece) {
    cx_board_t *board = cx_board_init();
    EXPECT_EQ(cx_board_get_piece(board, 0), CX_BLACK_ROOK);
    EXPECT_EQ(cx_board_get_piece(board, 63), CX_WHITE_ROOK);
    EXPECT_EQ(cx_board_get_piece(board, 8), CX_BLACK_PAWN);
    EXPECT_EQ(cx_board_get_piece(board, 48), CX_WHITE_PAWN);
    EXPECT_EQ(cx_board_get_piece(board, 17), CX_EMPTY);

    cx_board_free(board);
}

TEST(BoardTest, fen_load) {
    cx_board_t *board = cx_board_init();
    cx_board_fen_load(board, "k7/8/8/8/8/8/7/7K w - - 0 1");
    cx_print_bitboard(board->pieces[CX_BB_BLACK_KING]);
    EXPECT_EQ(cx_board_get_piece(board, 0), CX_BLACK_KING);
    EXPECT_EQ(cx_board_get_piece(board, 63), CX_WHITE_KING);

    cx_board_free(board);
}

TEST(BoardTest, fen_write) {
    cx_board_t *board = cx_board_init();

    char* fen = cx_board_fen(board);
    EXPECT_EQ(fen, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w kqKQ - 0 1");

    cx_board_free(board);
}