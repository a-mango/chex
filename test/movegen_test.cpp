#include <gtest/gtest.h>


extern "C" {
#include "../src/board.h"
#include "../src/move.h"
}

class MoveGenTest : public ::testing::Test {
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


TEST_F(MoveGenTest, move_gen) { FAIL(); }
TEST_F(MoveGenTest, move_gen_legal) { FAIL(); }
TEST_F(MoveGenTest, move_gen_pseudo) { FAIL(); }