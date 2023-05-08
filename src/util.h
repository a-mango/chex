//
// Created by acm on 5/6/23.
//

#ifndef CHEX_UTIL_H
#define CHEX_UTIL_H

#include <stdarg.h>
#include <wchar.h>

#include "board.h"

size_t cx_num_bits_set(uint64_t n);
size_t cx_lsb(uint64_t n);
size_t cx_msb(uint64_t n);
size_t cx_pop_lsb(uint64_t *n);
size_t cx_pop_msb(uint64_t *n);

#endif  // CHEX_UTIL_H
