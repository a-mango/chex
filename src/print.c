//
// Created by acm on 5/7/23.
//

#include <locale.h>
#include <stdarg.h>
#include <stdio.h>

#include "print.h"
#include "util.h"

// Display settings
#define DEFAULT_STREAM stdout
#define CX_PRIWSTR "ls"
#define CX_PRIWCHAR "lc"

// Eye candy
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   L"\x1b[32m"
#define ANSI_COLOR_YELLOW  L"\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define DEFAULT_COLOR ANSI_COLOR_YELLOW

static const wchar_t *PIECE_SYMBOLS = L".♟♞♝♜♛♚♙♘♗♖♕♔";
static const wchar_t *FILE_SYMBOLS = L"abcdefgh";
static const wchar_t *RANK_SYMBOLS = L"12345678";

void cx_print_init(void) {
    setlocale(LC_ALL, "en_US.UTF-8");
    cx_print(DEFAULT_STREAM, DEFAULT_COLOR);
}

void cx_print(FILE* stream, wchar_t const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfwprintf(stream, fmt, args);
    va_end(args);
}

void cx_print_board(cx_board_t const *board) {
    static const wchar_t* PAD = L" ";

    cx_log("Board:", CX_LOG_INFO);

    // Print the header
    wprintf(L"  ");
    for (int i = 0; i < 8; i++) {
        wprintf(L" %" CX_PRIWCHAR " ", FILE_SYMBOLS[i]);
    }
    wprintf(L"\n");

    // Print the board
    for (int rank = 7; rank >= 0; --rank) {
        wprintf(L"%" CX_PRIWCHAR "  ", RANK_SYMBOLS[rank]);
        for (int file = 0; file < 8; file++) {
            int index = rank * 8 + file;
            cx_piece_t piece = 0;
            if (board->white_pawns & (CX_BIT << index)) {
                piece = CX_WHITE_PAWN;
            } else if (board->white_knights & (CX_BIT << index)) {
                piece = CX_WHITE_KNIGHT;
            } else if (board->white_bishops & (CX_BIT << index)) {
                piece = CX_WHITE_BISHOP;
            } else if (board->white_rooks & (CX_BIT << index)) {
                piece = CX_WHITE_ROOK;
            } else if (board->white_queens & (CX_BIT << index)) {
                piece = CX_WHITE_QUEEN;
            } else if (board->white_king & (CX_BIT << index)) {
                piece = CX_WHITE_KING;
            } else if (board->black_pawns & (CX_BIT << index)) {
                piece = CX_BLACK_PAWN;
            } else if (board->black_knights & (CX_BIT << index)) {
                piece = CX_BLACK_KNIGHT;
            } else if (board->black_bishops & (CX_BIT << index)) {
                piece = CX_BLACK_BISHOP;
            } else if (board->black_rooks & (CX_BIT << index)) {
                piece = CX_BLACK_ROOK;
            } else if (board->black_queens & (CX_BIT << index)) {
                piece = CX_BLACK_QUEEN;
            } else if (board->black_king & (CX_BIT << index)) {
                piece = CX_BLACK_KING;
            } else {
                piece = CX_EMPTY;
            };
            wprintf(L"%" CX_PRIWCHAR "  ", PIECE_SYMBOLS[piece]);
        }
        wprintf(L"%" CX_PRIWCHAR "\n", RANK_SYMBOLS[rank]);
    }

    wprintf(L"  ");
    for (int i = 0; i < 8; i++) {
        wprintf(L" %" CX_PRIWCHAR " ", FILE_SYMBOLS[i]);
    }
    wprintf(L"\n");
}

void cx_print_bin(cx_piece_t n) {
    cx_print(stdout, L"%" CX_PRIWSTR, "0b");
    for (int i = 0; i < 64; i++) {
        wprintf(L"%lu", (n >> (63 - i)) & 1);
    }
    wprintf(L"\n");
}