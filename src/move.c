#include "move.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

void cx_move_init(void) {
    cx_log_va(L"%s: initialized moves", CX_LOG_DEBUG, __func__);
}

// Play/undo a move on a board.
void cx_move(cx_move_t move, cx_board_t *board) {
    assert(board != NULL);
    assert(move != CX_MOVE_NULL);

    cx_log_va(L"%s: play move %s", CX_LOG_DEBUG, __func__, cx_move_str(board, move));

    cx_square_t from       = CX_MOVE_FROM & move;
    cx_square_t to         = CX_MOVE_TO & move;
    cx_piece_t  piece_from = cx_board_get_piece(board, from);
    cx_board_set_piece(board, from, CX_EMPTY);
    cx_board_set_piece(board, to, CX_EMPTY);

    if (CX_MOVE_PROMOTION & move) {
        cx_piece_t promotion = CX_MOVE_PROMOTION & move;
        cx_board_set_piece(board, to, promotion);
    } else if (CX_MOVE_CASTLE & move) {
        cx_square_t rook_from       = CX_MOVE_CASTLE & move;
        cx_square_t rook_to         = CX_MOVE_CASTLE & move;
        cx_piece_t  piece_rook_from = cx_board_get_piece(board, rook_from);
        cx_board_set_piece(board, rook_from, CX_EMPTY);
        cx_board_set_piece(board, rook_to, CX_EMPTY);
        cx_board_set_piece(board, rook_to, piece_rook_from);
    } else if (CX_MOVE_EN_PASSANT & move) {
        cx_square_t ep_from       = (cx_square_t)(CX_MOVE_EN_PASSANT & move);
        cx_square_t ep_to         = (cx_square_t)(CX_MOVE_EN_PASSANT & move);
        cx_piece_t  piece_ep_from = cx_board_get_piece(board, ep_from);
        cx_board_set_piece(board, ep_from, CX_EMPTY);
        cx_board_set_piece(board, ep_to, CX_EMPTY);
        cx_board_set_piece(board, ep_to, piece_ep_from);
    } else {
        // Regular move.
        cx_board_set_piece(board, to, piece_from);
    }

    if (board->active_color == CX_BLACK)
        board->fullmove_number++;

    board->active_color = !board->active_color;

    // Set en passant square.
    if (piece_from == CX_WHITE_PAWN && (from >= 8 && from < 16) && to == from + 16) {
        board->en_passant = to - 8;
    } else if (piece_from == CX_BLACK_PAWN && (from >= 48 && from < 56) && to == from - 16) {
        board->en_passant = to + 8;
    } else {
        board->en_passant = CX_BOARD_SQUARE_NULL;
    }

    // If a capture occurred or a pawn moved, reset halfmove clock.
    if (move & CX_MOVE_CAPTURE || piece_from == CX_WHITE_PAWN || piece_from == CX_BLACK_PAWN) {
        board->halfmove_clock = 0;
    } else {
        board->halfmove_clock++;
    }

    // TODO: check if move disables castling.
    // TODO: add move to history.
}

void cx_undo(cx_move_t move, cx_board_t *board);

// Move generation.
size_t cx_move_gen(cx_board_t *board, cx_move_t *moves);
size_t cx_move_gen_legal(cx_board_t *board, cx_move_t *moves);
size_t cx_move_gen_pseudo(cx_board_t *board, cx_move_t *moves);

// Move parsing.
cx_move_t cx_move_parse(const cx_board_t *board, char const *san_str) {
    assert(san_str != NULL);
    assert(strlen(san_str) > 3 && strlen(san_str) < 6);
    cx_log_va(L"%s: parse move %s", CX_LOG_DEBUG, __func__, san_str);

    // expects SAN format:
    // exd5, e2e4, Bxe5, Nf6, Kf1, O-O, O-O-O, Qe5+, Qxe5, Qe5#, 1-0

    cx_move_t move = CX_MOVE_NULL;
    // Special moves
    if (strcmp(san_str, "O-O") == 0) {
        // TODO: castle kingside
    } else if (strcmp(san_str, "O-O-O") == 0) {
        // TODO: castle queenside
    }

    // From parsing
    cx_piece_t piece;
    if (strchr(FEN_PIECES, san_str[0])) {
        // from piece found, use fen_pieces to find piece
    } else {
        // use fen_files and fen_ranks to find from square / piece
        size_t file = (size_t)(wcschr(FILE_SYMBOLS, san_str[0]) - FILE_SYMBOLS);
        size_t rank = (size_t)(wcschr(RANK_SYMBOLS, san_str[1]) - RANK_SYMBOLS);
        cx_square_t from = CX_BOARD_SQUARE(file, rank);
        move |= CX_MOVE_FROM & from;
        piece = cx_board_get_piece(board, from);
        move |= CX_MOVE_PIECE & (piece << 14);
    }

    // Check if move is a capture
    if (strchr(san_str, 'x')) {
        move |= CX_MOVE_CAPTURE;
    }

    // To parsing
    size_t file = (size_t)(wcschr(FILE_SYMBOLS, san_str[2]) - FILE_SYMBOLS);
    size_t rank = (size_t)(wcschr(RANK_SYMBOLS, san_str[3]) - RANK_SYMBOLS);
    move |= CX_MOVE_TO & (CX_BOARD_SQUARE(file, rank) << 7);

    // TODO: handle promotion, castling perm and en passant

    return move;
}

char *cx_move_str(const cx_board_t *board, cx_move_t move) {
    assert(move != CX_MOVE_NULL);

    cx_str buffer = calloc(100, sizeof(cx_char));
    if (buffer == NULL) {
        cx_log(L"calloc failed", CX_LOG_FATAL);
        exit(EXIT_FAILURE);
    }

    // TODO: implement move string generation

    return buffer;
}
