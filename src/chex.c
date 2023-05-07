#include <locale.h>
#include <stdio.h>

#include "board.h"
#include "util.h"
#include "print.h"

#define CHEX_VERSION "0.0.1"

int main(void) {
    cx_print_init();

    cx_log("Chex Chess Engine", CX_LOG_INFO);
    cx_log("Build: "CHEX_VERSION, CX_LOG_INFO);

    cx_board_t *board = cx_board_init();
    cx_print_board(board);

    cx_board_free(board);
    return 0;
}
