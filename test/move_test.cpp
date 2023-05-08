#include <gtest/gtest.h>

extern "C" {
#include "../src/move.h"
}

TEST(MoveTest, move_init) {
    cx_move_init();
}