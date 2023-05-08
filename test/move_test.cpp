#include <gtest/gtest.h>


extern "C" {
#include "../src/board.h"
#include "../src/move.h"
}

class MoveTest : public ::testing::Test {
protected:
    void SetUp() override {
        board = cx_board_init();
        cx_move_init();
    }

    void TearDown() override {
        cx_board_free(board);
    }

    cx_board_t *board;
};


TEST_F(MoveTest, move_init) {
    // TODO: Test move_init correctly
    cx_move_init();
}

TEST_F(MoveTest, move) {
    FAIL();
}

TEST_F(MoveTest, undo) {
    FAIL();
}

TEST_F(MoveTest, move_parse) {
    // Test white pawn
    cx_move_t move = cx_move_parse(board, "a2a3");
    EXPECT_EQ(move & CX_MOVE_FROM, 15);
    EXPECT_EQ((move & CX_MOVE_TO) >> 7, 23);
    EXPECT_EQ((move & CX_MOVE_PIECE) >> 14, CX_WHITE_PAWN);
    EXPECT_FALSE(move & CX_MOVE_PROMOTION);
    EXPECT_FALSE(move & CX_MOVE_CAPTURE);
    EXPECT_FALSE(move & CX_MOVE_EN_PASSANT);
    EXPECT_EQ((move & CX_MOVE_CASTLE) >> 33, 0b11);
    EXPECT_FALSE(move & CX_MOVE_CHECK);
    EXPECT_FALSE(move & CX_MOVE_CHECKMATE);
    EXPECT_FALSE(move & CX_MOVE_STALEMATE);
    EXPECT_EQ((move & CX_MOVE_EP_SQUARE) >> 38, 0);

    // Test black pawn
    move = cx_move_parse(board, "e7e8");
    EXPECT_EQ(move & CX_MOVE_FROM, 51);
    EXPECT_EQ((move & CX_MOVE_TO) >> 7, 59);
    EXPECT_EQ((move & CX_MOVE_PIECE) >> 14, CX_BLACK_PAWN);

    // Test capture
    move = cx_move_parse(board, "e1xg1");
    EXPECT_EQ(move & CX_MOVE_FROM, 3);
    EXPECT_EQ((move & CX_MOVE_TO) >> 7, 1);
    EXPECT_EQ((move & CX_MOVE_PIECE) >> 14, CX_WHITE_KING);
    EXPECT_TRUE(move & CX_MOVE_CAPTURE);

    // Test promotion
    move = cx_move_parse(board, "e7e8q");
    EXPECT_EQ(move & CX_MOVE_FROM, 51);
    EXPECT_EQ((move & CX_MOVE_TO) >> 7, 59);
    EXPECT_EQ((move & CX_MOVE_PIECE) >> 14, CX_BLACK_PAWN);
    EXPECT_EQ((move & CX_MOVE_PROMOTION) >> 19, CX_QUEEN);

    // TODO: test en passant, castling, check, checkmate, stalemate, ep square
}

TEST_F(MoveTest, move_to_str) {

    FAIL();
}