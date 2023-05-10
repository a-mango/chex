#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "util.h"
#include "log.h"

#define CHEX_VERSION "0.0.1"

/**
 * Entry point for the Chex Chess Engine.
 *
 * @return The exit code.
 *
 * TODO: Add command line arguments
 * TODO: Add UCI support
 * TODO: Add a REPL
 */
int main(void) {
    cx_print_init();

    cx_log(L"Chex Chess Engine", CX_LOG_INFO);
    cx_log(L"Build: "CHEX_VERSION, CX_LOG_INFO);

    cx_board_t *board = cx_board_init();
//    cx_board_fen_load(board, "r7/8/8/8/8/8/7/7R w - - 0 1");
    cx_print_board(board);
    cx_print_sqnum();
    cx_board_free(board);
    return 0;
}

