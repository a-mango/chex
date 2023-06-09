//
// Created by acm on 5/6/23.
//

#include "util.h"

size_t cx_num_bits_set(uint64_t n) {
    size_t count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

size_t cx_lsb(uint64_t n) {
    size_t pos = 0;
    while (!(n & 1)) {
        ++pos;
        n >>= 1;
    }
    return pos;
}

size_t cx_msb(uint64_t n) {
    size_t pos = 63;
    while (!(n & (CX_BIT << pos))) {
        --pos;
    }
    return pos;
}

size_t cx_pop_lsb(uint64_t *n) {
    size_t pos = cx_lsb(*n);
    *n &= *n - 1;
    return pos;
}

size_t cx_pop_msb(uint64_t *n) {
    size_t pos = cx_msb(*n);
    *n &= (*n ^ (CX_BIT << pos));
    return pos;
}
