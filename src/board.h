//
// Created by acm on 5/6/23.
//

#ifndef CHEX_BOARD_H
#define CHEX_BOARD_H

#include <stdint.h>
#include <unistd.h>

#define CX_BOARD_SIZE 8
#define CX_BOARD_WIDTH 8
#define CX_BOARD_SQUARE_CNT 120
#define CX_PRIuPIECE "lu"
#define CX_PRIwPIECE "lc"
#define CX_BIT 1ULL

typedef uint64_t cx_piece_t;
typedef uint64_t cx_bitboard_t;

typedef struct {
    cx_bitboard_t white_pawns;
    cx_bitboard_t white_knights;
    cx_bitboard_t white_bishops;
    cx_bitboard_t white_rooks;
    cx_bitboard_t white_queens;
    cx_bitboard_t white_king;

    cx_bitboard_t black_pawns;
    cx_bitboard_t black_knights;
    cx_bitboard_t black_bishops;
    cx_bitboard_t black_rooks;
    cx_bitboard_t black_queens;
    cx_bitboard_t black_king;
} cx_board_t;

enum {
    CX_EMPTY,
    CX_WHITE_PAWN,
    CX_WHITE_KNIGHT,
    CX_WHITE_BISHOP,
    CX_WHITE_ROOK,
    CX_WHITE_QUEEN,
    CX_WHITE_KING,
    CX_BLACK_PAWN,
    CX_BLACK_KNIGHT,
    CX_BLACK_BISHOP,
    CX_BLACK_ROOK,
    CX_BLACK_QUEEN,
    CX_BLACK_KING,
};

#define CX_PIECE_TYPE(piece) (piece & 0b111)
#define CX_PIECE_COLOR(piece) (piece & 0b11000)

#define CX_PIECE_IS_WHITE(piece) (piece & CX_WHITE)
#define CX_PIECE_IS_BLACK(piece) (piece & CX_BLACK)

cx_board_t *cx_board_init(void);
void cx_board_free(cx_board_t *board);

ssize_t cx_board_print(cx_board_t const *board);

ssize_t cx_board_fen_load(cx_board_t *board, char const *fen);
ssize_t cx_board_fen_dump(cx_board_t const *board, char *fen, size_t n);


#endif//CHEX_BOARD_H
