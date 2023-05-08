//
// Created by acm on 5/7/23.
//

#ifndef CHEX_PRINT_H
#define CHEX_PRINT_H

#include <stdio.h>
#include <wchar.h>

#include "board.h"

typedef enum LogType {
    CX_LOG_INFO,
    CX_LOG_WARN,
    CX_LOG_ERROR,
    CX_LOG_DEBUG,
} cx_log_type_t;

void cx_print_init(void);
void cx_print(FILE *stream, wchar_t const *fmt, ...);
void cx_print_board(cx_board_t const *board);
void cx_print_bin(uint64_t n);
void cx_print_bitboard(cx_bitboard_t n);

void cx_log(char const *msg, cx_log_type_t type);
void cx_log_va(wchar_t const *msg, cx_log_type_t type, ...);

#endif  // CHEX_PRINT_H
