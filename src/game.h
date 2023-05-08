#ifndef CHEX_GAME_H
#define CHEX_GAME_H

#include "board.h"
#include "move.h"


#define CX_GAME_MOVE_MAX 1024

typedef enum {
    CX_ONGOING,
    CX_WHITE_CHECKMATE,
    CX_BLACK_CHECKMATE,
    CX_WHITE_RESIGNS,
    CX_BLACK_RESIGNS,
    STALEMATE,
    CX_DRAW,
    CX_DRAW_FORCED,
} cx_game_status_t;

typedef struct {
    cx_game_status_t status;
    cx_board_t       board;
    cx_move_t        moves[CX_GAME_MOVE_MAX];
    size_t           move_cnt;
    size_t           move_idx;
} cx_game_t;

#endif  // CHEX_GAME_H
