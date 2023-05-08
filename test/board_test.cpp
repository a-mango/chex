//
// Created by acm on 5/6/23.
//

#include <gtest/gtest.h>

extern "C" {
#include "../src/util.h"
#include "../src/board.h"
#include "../src/print.h"
}

TEST(BoardTest, board_init) {
    cx_board_t *board = cx_board_init();
    EXPECT_NE(board, nullptr);
    EXPECT_EQ(board->pieces[CX_BB_EMPTY], 0x0000FFFFFFFF0000);
    EXPECT_EQ(board->pieces[CX_BB_WHITE_ROOKS], 0b10000001);
    EXPECT_EQ(board->pieces[CX_BB_WHITE_KNIGHTS], 0b01000010);
    EXPECT_EQ(board->pieces[CX_BB_WHITE_BISHOPS], 0b00100100);
    EXPECT_EQ(board->pieces[CX_BB_WHITE_QUEENS], 0b00010000);
    EXPECT_EQ(board->pieces[CX_BB_WHITE_KING], 0b00001000);
    EXPECT_EQ(board->pieces[CX_BB_WHITE_PAWNS], 0b1111111100000000);
    EXPECT_EQ(board->pieces[CX_BB_BLACK_ROOKS], ((uint64_t )0b10000001 << 56));
    EXPECT_EQ(board->pieces[CX_BB_BLACK_KNIGHTS], ((uint64_t )0b01000010 << 56));
    EXPECT_EQ(board->pieces[CX_BB_BLACK_BISHOPS], ((uint64_t )0b00100100 << 56));
    EXPECT_EQ(board->pieces[CX_BB_BLACK_QUEENS], ((uint64_t )0b00010000 << 56));
    EXPECT_EQ(board->pieces[CX_BB_BLACK_KING], ((uint64_t )0b00001000 << 56));
    EXPECT_EQ(board->pieces[CX_BB_BLACK_PAWNS], ((uint64_t )0b1111111100000000 << 40));
    EXPECT_EQ(board->pieces[CX_BB_WHITE], 0xFFFF);
    EXPECT_EQ(board->pieces[CX_BB_BLACK], ((uint64_t )0xFFFF << 48));
    EXPECT_EQ(board->pieces[CX_BB_ALL], 0xFFFF00000000FFFF);
    EXPECT_EQ(board->active_color, CX_WHITE);
    EXPECT_EQ(board->castle_rights, CX_CASTLE_WHITE_KINGSIDE | CX_CASTLE_WHITE_QUEENSIDE |
                                    CX_CASTLE_BLACK_KINGSIDE | CX_CASTLE_BLACK_QUEENSIDE);
    EXPECT_EQ(board->en_passant, 0);
    EXPECT_EQ(board->halfmove_clock, 0);
    EXPECT_EQ(board->fullmove_number, 1);
}

TEST(BoardTest, get_piece) {
    cx_board_t *board = cx_board_init();
    EXPECT_EQ(cx_board_get_piece(board, 0), CX_WHITE_ROOK);
    EXPECT_EQ(cx_board_get_piece(board, 63), CX_BLACK_ROOK);
    EXPECT_EQ(cx_board_get_piece(board, 8), CX_WHITE_PAWN);
    EXPECT_EQ(cx_board_get_piece(board, 48), CX_BLACK_PAWN);
    EXPECT_EQ(cx_board_get_piece(board, 3), CX_WHITE_KING);
    EXPECT_EQ(cx_board_get_piece(board, 17), CX_EMPTY);

    cx_board_free(board);
}

TEST(BoardTest, set_piece) {
    cx_board_t *board = cx_board_init();
    cx_board_fen_load(board, EMPTY_POS);
    cx_board_set_piece(board, 0, CX_WHITE_ROOK);
    cx_board_set_piece(board, 63, CX_BLACK_ROOK);
    cx_board_set_piece(board, 8, CX_WHITE_PAWN);
    cx_board_set_piece(board, 48, CX_BLACK_PAWN);
    EXPECT_EQ(cx_board_get_piece(board, 0), CX_WHITE_ROOK);
    EXPECT_EQ(cx_board_get_piece(board, 63), CX_BLACK_ROOK);
    EXPECT_EQ(cx_board_get_piece(board, 8), CX_WHITE_PAWN);
    EXPECT_EQ(cx_board_get_piece(board, 48), CX_BLACK_PAWN);

    cx_board_free(board);
}

TEST(BoardTest, fen_load) {
    cx_board_t *board = cx_board_init();
    EXPECT_EQ(board->pieces[CX_BB_WHITE_ROOKS], 0b10000001);
    EXPECT_EQ(board->pieces[CX_BB_WHITE_KNIGHTS], 0b01000010);
    EXPECT_EQ(board->pieces[CX_BB_WHITE_BISHOPS], 0b00100100);
    EXPECT_EQ(board->pieces[CX_BB_WHITE_QUEENS], 0b00010000);
    EXPECT_EQ(board->pieces[CX_BB_WHITE_KING], 0b00001000);
    EXPECT_EQ(board->pieces[CX_BB_WHITE_PAWNS], 0b1111111100000000);
    EXPECT_EQ(board->pieces[CX_BB_BLACK_ROOKS], ((uint64_t )0b10000001 << 56));
    EXPECT_EQ(board->pieces[CX_BB_BLACK_KNIGHTS], ((uint64_t )0b01000010 << 56));
    EXPECT_EQ(board->pieces[CX_BB_BLACK_BISHOPS], ((uint64_t )0b00100100 << 56));
    EXPECT_EQ(board->pieces[CX_BB_BLACK_QUEENS], ((uint64_t )0b00010000 << 56));
    EXPECT_EQ(board->pieces[CX_BB_BLACK_KING], ((uint64_t )0b00001000 << 56));
    EXPECT_EQ(board->pieces[CX_BB_BLACK_PAWNS], ((uint64_t )0b1111111100000000 << 40));

    cx_board_fen_load(board, "r7/8/8/8/8/8/7/7R w - - 0 1");
    EXPECT_EQ(cx_board_get_piece(board, 0), CX_WHITE_ROOK);
    EXPECT_EQ(cx_board_get_piece(board, 63), CX_BLACK_ROOK);

    cx_board_free(board);
}

TEST(BoardTest, fen_write) {
    cx_board_t *board = cx_board_init();

    char* fen = cx_board_fen(board);
    EXPECT_STREQ(fen, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w kqKQ - 0 1");

    cx_board_free(board);
}