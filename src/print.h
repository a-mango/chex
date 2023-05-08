//
// Created by acm on 5/7/23.
//

#ifndef CHEX_PRINT_H
#define CHEX_PRINT_H

#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>

#include "board.h"


#define CX_DEFAULT_STREAM stdout
#define CX_PRISTR "s"
#define CX_PRIWSTR "ls"
#define CX_PRIWCHAR "lc"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN L"\x1b[32m"
#define ANSI_COLOR_YELLOW L"\x1b[33m"
#define ANSI_COLOR_BLUE L"\x1b[34m"
#define ANSI_COLOR_MAGENTA L"\x1b[35m"
#define ANSI_COLOR_CYAN L"\x1b[36m"
#define ANSI_COLOR_RESET L"\x1b[0m"
#define DEFAULT_COLOR L""

typedef wchar_t        cx_char;
typedef cx_char       *cx_str;
typedef cx_char const *cx_cstr;

void cx_print_init(void);
void cx_print(FILE *stream, wchar_t const *fmt, ...);
void cx_print_va(FILE *stream, wchar_t const *fmt, va_list args);
void cx_print_board(cx_board_t const *board);
void cx_print_bin(uint64_t n);
void cx_print_bitboard(cx_bitboard_t n);

#endif  // CHEX_PRINT_H
