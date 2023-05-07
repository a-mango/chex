//
// Created by acm on 5/6/23.
//

#include <gtest/gtest.h>

extern "C" {
#include "../src/util.h"
}

TEST(UtilTest, num_bits_set) {
    uint64_t n = 0b100000000000;
    EXPECT_EQ(cx_num_bits_set(n), 1);

    n = 0b10000001000000;
    EXPECT_EQ(cx_num_bits_set(n), 2);

    n = 0b0;
    EXPECT_EQ(cx_num_bits_set(n), 0);

    n = UINT64_MAX;
    EXPECT_EQ(cx_num_bits_set(n), 64);
}

TEST(UtilTest, lsb) {
    uint64_t n = 0b100000000000;
    EXPECT_EQ(cx_lsb(n), 11);

    n = 0b10000000000000;
    EXPECT_EQ(cx_lsb(n), 13);

    n = 0b1;
    EXPECT_EQ(cx_lsb(n), 0);

    n = 0b1010;
    EXPECT_EQ(cx_lsb(n), 1);
}

TEST(UtilTest, msb) {
    uint64_t n = 0b100000000000;
    EXPECT_EQ(cx_msb(n), 11);

    n = 0b10000000000000;
    EXPECT_EQ(cx_msb(n), 13);

    n = 0b1;
    EXPECT_EQ(cx_msb(n), 0);

    n = 0b1010;
    EXPECT_EQ(cx_msb(n), 3);
}

TEST(UtilTest, pop_lsb) {
    uint64_t n = 0b100000000000;
    EXPECT_EQ(cx_pop_lsb(&n), 11);
    EXPECT_EQ(n, 0b0);

    n = 0b10000000000000;
    EXPECT_EQ(cx_pop_lsb(&n), 13);
    EXPECT_EQ(n, 0b0);

    n = 0b1;
    EXPECT_EQ(cx_pop_lsb(&n), 0);
    EXPECT_EQ(n, 0b0);

    n = 0b1010;
    EXPECT_EQ(cx_pop_lsb(&n), 1);
    EXPECT_EQ(n, 0b1000);
}
