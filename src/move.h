/**
 * Move related functions.
 * @see https://www.chessprogramming.org/Encoding_Moves
 * Created by acm on 5/6/23.
 *
 * From square (6 bits) - The starting square of the piece being moved.
 * To square (6 bits) - The ending square of the piece being moved.
 * Piece type (4 bits) - The type of the piece being moved.
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
 * 000000  000000  0000   0000 0 0 00 0  0  0  000000
 * From    To      Piece  Prom C E Ca Ck Cm St Ep
 */

#ifndef CHEX_MOVE_H
#define CHEX_MOVE_H

#include <stdint.h>

#include "board.h"

typedef uint64_t cx_move_t;

// clang-format off
#define CX_MOVE_FROM                                          0b111111
#define CX_MOVE_TO                                      0b111111000000
#define CX_MOVE_PIECE_TYPE                          0b1111000000000000
#define CX_MOVE_PROMOTION_PIECE_TYPE            0b11110000000000000000
#define CX_MOVE_CAPTURE                     0b100000000000000000000000
#define CX_MOVE_EN_PASSANT            0b100000000000000000000000000000
#define CX_MOVE_CASTLE              0b11000000000000000000000000000000
#define CX_MOVE_CHECK              0b100000000000000000000000000000000
#define CX_MOVE_CHECKMATE         0b1000000000000000000000000000000000
#define CX_MOVE_STALEMATE        0b10000000000000000000000000000000000
#define CX_MOVE_EP_SQUARE  0b11111100000000000000000000000000000000000
// clang-format on


enum MoveFlags {
    CX_MOVE_FLAG_PROMOTION = 1 << 0,
    CX_MOVE_FLAG_EN_PASSANT = 1 << 1,
    CX_MOVE_FLAG_CASTLE = 1 << 2,
    CX_MOVE_FLAG_CAPTURE = 1 << 3,
};

void cx_move_init(void);
void cx_move(cx_move_t move, cx_board_t *board);
void cx_undo(cx_move_t move, cx_board_t *board);

cx_move_t cx_move_from_str(char const *str);
char *cx_move_to_str(cx_move_t move);

#endif//CHEX_MOVE_H
