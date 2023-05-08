//
// Created by acm on 5/6/23.
//

#ifndef CHEX_BOARD_H
#define CHEX_BOARD_H

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#define CX_BOARD_SIZE 8
#define CX_BOARD_WIDTH 8
#define CX_BOARD_SQUARE_CNT 64
#define CX_BOARD_SQUARE_NULL 0xFF
// Board squares are counted from bottom right to top left.
#define CX_BOARD_SQUARE(file, rank) (CX_BOARD_WIDTH - (file) - 1 + (rank) * CX_BOARD_WIDTH)
#define CX_BOARD_PIECE_CNT 32

#define CX_BOARD_BITBOARD_CNT 16

#define CX_BIT 1ULL
#define CX_SET_BIT(n, pos) (n |= CX_BIT << pos)

typedef uint8_t  cx_square_t;
typedef uint64_t cx_piece_t;
typedef uint64_t cx_bitboard_t;

typedef struct {
    uint_fast64_t hash;

    uint8_t  en_passant;
    uint8_t  active_color;
    uint16_t castle_rights;
    uint8_t  halfmove_clock;
    uint8_t  fullmove_number;

    cx_bitboard_t pieces[16];
} cx_board_t;

enum CxBitboardOrder {
    CX_BB_EMPTY,
    CX_BB_WHITE_PAWNS,
    CX_BB_WHITE_KNIGHTS,
    CX_BB_WHITE_BISHOPS,
    CX_BB_WHITE_ROOKS,
    CX_BB_WHITE_QUEENS,
    CX_BB_WHITE_KING,
    CX_BB_BLACK_PAWNS,
    CX_BB_BLACK_KNIGHTS,
    CX_BB_BLACK_BISHOPS,
    CX_BB_BLACK_ROOKS,
    CX_BB_BLACK_QUEENS,
    CX_BB_BLACK_KING,
    CX_BB_WHITE,
    CX_BB_BLACK,
    CX_BB_ALL,
};

enum CxPieceType {
    CX_PAWN = 1,
    CX_KNIGHT,
    CX_BISHOP,
    CX_ROOK,
    CX_QUEEN,
    CX_KING,
};

enum CxColor {
    CX_WHITE = CX_BIT << 3,
    CX_BLACK = CX_BIT << 4
};

enum CxPiece {
    CX_EMPTY        = 0,
    CX_WHITE_PAWN   = (CX_WHITE | CX_PAWN),
    CX_WHITE_KNIGHT = (CX_WHITE | CX_KNIGHT),
    CX_WHITE_BISHOP = (CX_WHITE | CX_BISHOP),
    CX_WHITE_ROOK   = (CX_WHITE | CX_ROOK),
    CX_WHITE_QUEEN  = (CX_WHITE | CX_QUEEN),
    CX_WHITE_KING   = (CX_WHITE | CX_KING),
    CX_BLACK_PAWN   = (CX_BLACK | CX_PAWN),
    CX_BLACK_KNIGHT = (CX_BLACK | CX_KNIGHT),
    CX_BLACK_BISHOP = (CX_BLACK | CX_BISHOP),
    CX_BLACK_ROOK   = (CX_BLACK | CX_ROOK),
    CX_BLACK_QUEEN  = (CX_BLACK | CX_QUEEN),
    CX_BLACK_KING   = (CX_BLACK | CX_KING),
};

enum {
    CX_CASTLE_WHITE_KINGSIDE  = CX_BIT << 0,
    CX_CASTLE_WHITE_QUEENSIDE = CX_BIT << 1,
    CX_CASTLE_BLACK_KINGSIDE  = CX_BIT << 2,
    CX_CASTLE_BLACK_QUEENSIDE = CX_BIT << 3,
};

// Bitboard macros.
#define CX_WHITE_PIECES(board) ((board)->pieces[CX_BB_WHITE_PAWNS] | (board)->pieces[CX_BB_WHITE_KNIGHTS] | (board)->pieces[CX_BB_WHITE_BISHOPS] | (board)->pieces[CX_BB_WHITE_ROOKS] | (board)->pieces[CX_BB_WHITE_QUEENS] | (board)->pieces[CX_BB_WHITE_KING])
#define CX_BLACK_PIECES(board) ((board)->pieces[CX_BB_BLACK_PAWNS] | (board)->pieces[CX_BB_BLACK_KNIGHTS] | (board)->pieces[CX_BB_BLACK_BISHOPS] | (board)->pieces[CX_BB_BLACK_ROOKS] | (board)->pieces[CX_BB_BLACK_QUEENS] | (board)->pieces[CX_BB_BLACK_KING])
#define CX_ALL_PIECES(board) (CX_WHITE_PIECES(board) | CX_BLACK_PIECES(board))
#define CX_EMPTY_SQUARES(board) (~(CX_ALL_PIECES(board)))

#define CX_PIECE_COLOR(piece) ((piece) & (CX_WHITE | CX_BLACK))
#define CX_PIECE_TYPE(piece) ((piece) & (CX_PAWN | CX_KNIGHT | CX_BISHOP | CX_ROOK | CX_QUEEN | CX_KING))

extern const char *START_POS;
extern const char *EMPTY_POS;
extern const char *FEN_PIECES;

// Functions.
cx_board_t *cx_board_init(void);
void        cx_board_free(cx_board_t *board);
cx_piece_t  cx_board_get_piece(cx_board_t const *board, uint8_t square);
void        cx_board_set_piece(cx_board_t *board, uint8_t square, cx_piece_t piece);
ssize_t     cx_board_fen_load(cx_board_t *board, char const *fen);
char       *cx_board_fen(cx_board_t const *board);
void        cx_board_update_bitboards(cx_board_t *board);

#endif  // CHEX_BOARD_H
