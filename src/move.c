#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "move.h"
#include "log.h"

void cx_move_init(void) {
    cx_log_va(L"%s: initialized moves", CX_LOG_DEBUG, __func__);
}

// Play/undo a move on a board.
void cx_move(cx_move_t move, cx_board_t *board) {
    assert(board != NULL);
    assert(move != CX_MOVE_NULL);

    cx_log_va(L"%s: play move %s", CX_LOG_DEBUG, __func__, cx_move_str(move));
    cx_piece_t piece = cx_board_get_piece(board, CX_MOVE_FROM & move);
    cx_board_set_piece(board, CX_MOVE_FROM & move, CX_EMPTY);
    cx_board_set_piece(board, CX_MOVE_TO & move, piece);

    // TODO: handle promotions, en passant, castling, etc.
    // TODO: add move to history.
}

void cx_undo(cx_move_t move, cx_board_t *board);

// Move generation.
size_t cx_move_gen(cx_board_t *board, cx_move_t *moves);
size_t cx_move_gen_legal(cx_board_t *board, cx_move_t *moves);
size_t cx_move_gen_pseudo_legal(cx_board_t *board, cx_move_t *moves);

// Move parsing.
cx_move_t cx_move_parse(const cx_board_t * board, char const *san_str) {
    assert(san_str != NULL);
    assert(strlen(san_str) == 4);

    // expects SAN format:
    // exd5, e2e4, Bxe5, Nf6, Kf1, O-O, O-O-O, Qe5+, Qxe5, Qe5#, 1-0

    // Iterate over the string
    for (size_t i = 0; i < strlen(san_str); ++i) {

    }

    return CX_MOVE_NULL;
}

char *cx_move_str(const cx_board_t * board, cx_move_t move) {
    assert(move != CX_MOVE_NULL);

    cx_str buffer = calloc(100, sizeof(cx_char));
    if (buffer == NULL) {
        cx_log("calloc failed", CX_LOG_FATAL);
        exit(EXIT_FAILURE);
    }

    return buffer;
}
