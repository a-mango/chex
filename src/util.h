//
// Created by acm on 5/6/23.
//

#ifndef CHEX_UTIL_H
#define CHEX_UTIL_H

#include "board.h"

typedef enum LogType {
    CX_LOG_INFO,
    CX_LOG_WARN,
    CX_LOG_ERROR,
} cx_log_type_t;

void cx_log(char const *msg, cx_log_type_t type);
size_t cx_num_bits_set(uint64_t n);
size_t cx_lsb(uint64_t n);
size_t cx_msb(uint64_t n);

#endif//CHEX_UTIL_H
