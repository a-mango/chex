//
// Created by acm on 5/7/23.
//

#ifndef CHEX_PRINT_H
#define CHEX_PRINT_H

#include <wchar.h>

#include "board.h"

void cx_print_init(void);
/**
 * Print a formatted string to a stream.
 *
 * @param stream The stream to print to.
 * @param fmt The format string.
 * @param ... The format string arguments.
 */
void cx_print(FILE* stream, wchar_t const *fmt, ...);
void cx_print_board(cx_board_t const *board);
void cx_print_bin(uint64_t n);
void cx_print_bitboard(cx_bitboard_t n);

#endif//CHEX_PRINT_H
