//
// Created by acm on 5/7/23.
//

#include "print.h"

#include <locale.h>
#include <stdarg.h>
#include <stdio.h>

#include "util.h"

// Display settings
#define DEFAULT_STREAM stdout
#define CX_PRIWSTR "ls"
#define CX_PRIWCHAR "lc"

// Eye candy
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN L"\x1b[32m"
#define ANSI_COLOR_YELLOW L"\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define DEFAULT_COLOR ""

static const wchar_t *CX_LOG_HEADERS[] = {
    L"["ANSI_COLOR_CYAN"INFO"ANSI_COLOR_RESET"]   ",
    L"["ANSI_COLOR_MAGENTA"WARN"ANSI_COLOR_RESET"]   ",
    L"["ANSI_COLOR_RED"ERROR"ANSI_COLOR_RESET"]  ",
    L"["ANSI_COLOR_YELLOW"DEBUG"ANSI_COLOR_RESET"]  ",
};


static const wchar_t *PIECE_SYMBOLS = L".♟♞♝♜♛♚♙♘♗♖♕♔";
static const wchar_t *FILE_SYMBOLS  = L"abcdefgh";
static const wchar_t *RANK_SYMBOLS  = L"12345678";

void cx_print_init(void) {
    setlocale(LC_ALL, "en_US.UTF-8");
    cx_print(DEFAULT_STREAM, DEFAULT_COLOR);
}

void cx_print(FILE *stream, wchar_t const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfwprintf(stream, fmt, args);
    va_end(args);
}

void cx_log(char const *msg, cx_log_type_t type) {
    wprintf(L"%ls%s\n", CX_LOG_HEADERS[type], msg);
}

void cx_log_va(wchar_t const *msg, cx_log_type_t type, ...) {
    va_list args;
    va_start(args, type);
    wprintf(L"%ls", CX_LOG_HEADERS[type]);
    vwprintf(msg, args);
    wprintf(L"\n");
    va_end(args);
}


void cx_print_board(cx_board_t const *board) {
    wchar_t buffer[8][9] = {0};

    // Iterate over the bitboards.
    for (size_t i = 0; i < 13; ++i) {
        cx_bitboard_t bb = board->pieces[i];
        // Print pieces to buffer using PIECE_SYMBOLS starting with msb
        for (size_t j = 0; j < CX_BOARD_SQUARE_CNT; ++j) {
            if (bb >> (63 - j) & 1)
                buffer[j / 8][j % 8] = PIECE_SYMBOLS[i];
        }
    }
    for (size_t i = 0; i < CX_BOARD_SIZE; ++i)
        wprintf(L"%ls\n", buffer[i]);  // Don't forget to reverse the buffer
}

void cx_print_bin(cx_piece_t n) {
    cx_print(stdout, L"%" CX_PRIWSTR, L"0b");
    for (int i = 0; i < 64; i++)
        wprintf(L"%lu", (n >> (63 - i)) & 1);
    wprintf(L"\n");
}

void cx_print_bitboard(cx_bitboard_t n) {
    // Print the bitboard in square shape using x and . starting with msb.
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0)
            wprintf(L"\n");
        wchar_t symbol = (n >> (63 - i)) & 1 ? 'x' : '.';
        wprintf(L"%c", symbol);
    }
    wprintf(L"\n");
}
