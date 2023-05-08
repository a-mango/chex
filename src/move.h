/**
 * Move related functions.
 * @see https://www.chessprogramming.org/Encoding_Moves
 * Created by acm on 5/6/23.
 *
 * From square (7 bits) - The starting square of the piece being moved.
 * To square (7 bits) - The ending square of the piece being moved.
 * Piece (5 bits) - The type and color the piece being moved.
 * Promotion piece type (4 bits) - If the move is a promotion, the type of the piece being promoted to.
 * Capture (1 bit) - Whether the move captures an opponent's piece.
 * En passant (1 bit) - Whether the move is an en passant capture.
 * Castling (2 bits) - If the move is a castling move, the type of castling (short or long).
 * Check (1 bit) - Whether the move puts the opponent's king in check.
 * Checkmate (1 bit) - Whether the move results in a checkmate.
 * Stalemate (1 bit) - Whether the move results in a stalemate.
 * Ep square (6 bits) - The square that can be captured en passant on the next move.
 *
 * Diagram:
 * msb                                            lsb
 * 0000000  0000000  00000  0000 0 0 00 0  0  0  000000
 * From     To       Piece  Prom C E Ca Ck Cm St Ep
 */

#ifndef CHEX_MOVE_H
#define CHEX_MOVE_H

#include <stdint.h>

#include "board.h"

typedef uint64_t cx_move_t;

enum CxMove {
    CX_MOVE_NULL                 = 0,
    CX_MOVE_FROM                 = 0b1111111,
    CX_MOVE_TO                   = 0b11111110000000,
    CX_MOVE_PIECE                = 0b1111100000000000000,
    CX_MOVE_PROMOTION            = 0b11110000000000000000000,
    CX_MOVE_CAPTURE              = 0b100000000000000000000000000,
    CX_MOVE_EN_PASSANT           = 0b100000000000000000000000000000000,
    CX_MOVE_CASTLE               = 0b11000000000000000000000000000000000,
    CX_MOVE_CHECK                = 0b100000000000000000000000000000000000,
    CX_MOVE_CHECKMATE            = 0b1000000000000000000000000000000000000,
    CX_MOVE_STALEMATE            = 0b10000000000000000000000000000000000000,
    CX_MOVE_EP_SQUARE            = 0b11111100000000000000000000000000000000000000,
};

void cx_move_init(void);

// Play/undo a move on a board.
void cx_move(cx_move_t move, cx_board_t *board);
void cx_undo(cx_move_t move, cx_board_t *board);

// Move generation.
size_t cx_move_gen(cx_board_t *board, cx_move_t *moves);
size_t cx_move_gen_legal(cx_board_t *board, cx_move_t *moves);
size_t cx_move_gen_pseudo(cx_board_t *board, cx_move_t *moves);

// Move parsing.
cx_move_t cx_move_parse(const cx_board_t * board, char const *san_str);
char     *cx_move_str(const cx_board_t * board, cx_move_t move);

#endif  // CHEX_MOVE_H
