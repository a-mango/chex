//
// Created by acm on 5/6/23.
//
#include "board.h"

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print.h"

const char        *START_POS  = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const char        *EMPTY_POS  = "8/8/8/8/8/8/8/8 w - - 0 1";
static const char *FEN_PIECES = " PNBRQKpnbrqk";

cx_board_t *cx_board_init(void) {
    cx_board_t *board = calloc(1, sizeof(cx_board_t));
    if (board == NULL) {
        cx_log("calloc failed", CX_LOG_ERROR);
        exit(EXIT_FAILURE);
    }

    cx_log_va(L"%s: initialized board at address %p", CX_LOG_DEBUG, __func__, (void *)board);
    cx_board_fen_load(board, START_POS);

    return board;
}

void cx_board_free(cx_board_t *board) {
    free(board);
}

cx_piece_t cx_board_get_piece(cx_board_t const *board, uint8_t square) {
    assert(board != NULL);
    assert(square < 64);

    cx_bitboard_t mask = CX_BIT << square;
    // Iterate through the bitboards and find the piece.
    for (size_t i = 1; i < 13; i++) {
        if (board->pieces[i] & mask) {
            if (i < 7)
                return (cx_piece_t)(CX_WHITE | i);
            else
                return (cx_piece_t)(CX_BLACK | (i - 6));
        }
    }
    return CX_EMPTY;
}

void cx_board_set_piece(cx_board_t *board, uint8_t square, cx_piece_t piece) {
    assert(board != NULL);
    assert(square < 64);
    assert(piece != CX_EMPTY);

    cx_bitboard_t mask = CX_BIT << square;
    cx_piece_t board_index = (piece & 0b111) + (piece & 0b1000 ? 0 : 6);
    board->pieces[board_index] |= mask;
}

ssize_t cx_board_fen_load(cx_board_t *board, char const *fen) {
    // TODO: validate FEN string and treat errors appropriately.
    assert(board != NULL);
    assert(fen != NULL);

    cx_log_va(L"%s: import fen string", CX_LOG_DEBUG, __func__);

    // Reset bitboards
    for (size_t i = 0; i < 16; i++) {
        board->pieces[i] = 0;
    }

    // Split the FEN string into its component parts
    char fen_copy[strlen(fen) + 1];  // FIXME: use malloc or fixed size buffer
    strcpy(fen_copy, fen);
    char *parts[6] = {0};
    char *token    = strtok(fen_copy, " ");
    int   i        = 0;
    while (token != NULL && i < 6) {
        parts[i++] = token;
        token      = strtok(NULL, " ");
    }

    // Parse the piece placement section of the FEN string
    char *piece_placement = parts[0];
    int   rank            = 7;
    int   file            = 0;
    for (const char *c = piece_placement; *c != '\0'; c++) {
        if (*c == '/') {
            // Move to the next rank
            --rank;
            file = 0;
        } else if (*c >= '1' && *c <= '8') {
            // Skip empty squares
            file += *c - '0';
        } else {
            // Place the piece on the board
            int    index       = rank * 8 + 7 - file;
            size_t board_index = (size_t)(strchr(FEN_PIECES, *c) - FEN_PIECES);
            cx_log_va(L"%s: piece: %c pos: %d bb: %zu", CX_LOG_DEBUG, __func__, *c, index, board_index);
            board->pieces[board_index] |= CX_BIT << index;
            ++file;
        }
    }

    // Update the aggregate bitboards.
    board->pieces[CX_BB_EMPTY] = CX_EMPTY_SQUARES(board);
    board->pieces[CX_BB_WHITE] = CX_WHITE_PIECES(board);
    board->pieces[CX_BB_BLACK] = CX_BLACK_PIECES(board);
    board->pieces[CX_BB_ALL]   = CX_ALL_PIECES(board);

    // Parse the active color section of the FEN string.
    board->active_color = (parts[1][0] == 'w') ? CX_WHITE : CX_BLACK;
    // Parse the castling availability section of the FEN string.
    board->castle_rights = 0;
    if (strchr(parts[2], 'K') != NULL)
        board->castle_rights |= CX_CASTLE_WHITE_KINGSIDE;
    if (strchr(parts[2], 'Q') != NULL)
        board->castle_rights |= CX_CASTLE_WHITE_QUEENSIDE;
    if (strchr(parts[2], 'k') != NULL)
        board->castle_rights |= CX_CASTLE_BLACK_KINGSIDE;
    if (strchr(parts[2], 'q') != NULL)
        board->castle_rights |= CX_CASTLE_BLACK_QUEENSIDE;
    // Parse the en passant target square section of the FEN string.
    board->en_passant = (uint8_t)atoi(parts[3]);
    // Parse the halfmove clock section of the FEN string.
    board->halfmove_clock = (uint8_t)atoi(parts[4]);
    // Parse the fullmove number section of the FEN string.
    board->fullmove_number = (uint8_t)atoi(parts[5]);

    cx_log_va(L"%s: loaded position %s", CX_LOG_DEBUG, __func__, fen);

    return 0;
}

char *cx_board_fen(cx_board_t const *board) {
    cx_log("Board FEN", CX_LOG_INFO);
    // Export the board into a FEN string.
    assert(board != NULL);

    // Dump the piece placement section of the FEN string.
    char *c = calloc(120, sizeof(char));
    char *p = c;
    for (int rank = 7; rank >= 0; --rank) {
        int empty_squares = 0;
        for (int file = 7; file >= 0; --file) {
            cx_piece_t piece = cx_board_get_piece(board, (uint8_t)(rank * 8 + file));
            if (piece == CX_EMPTY) {
                empty_squares++;
            } else {
                if (empty_squares > 0) {
                    *c++          = (char)('0' + empty_squares);
                    empty_squares = 0;
                }
                *c++ = FEN_PIECES[CX_PIECE_COLOR(piece) == CX_WHITE ? CX_PIECE_TYPE(piece) : CX_PIECE_TYPE(piece) + 6];
            }
        }
        if (empty_squares > 0) {
            *c++ = (char)('0' + empty_squares);
        }
        if (rank > 0) {
            *c++ = '/';
        }
    }
    *c++ = ' ';
    // Dump the active color section of the FEN string.
    *c++ = (board->active_color == CX_WHITE) ? 'w' : 'b';
    *c++ = ' ';
    // Dump the castling availability section of the FEN string.
    if (board->castle_rights & CX_CASTLE_BLACK_KINGSIDE)
        *c++ = 'k';
    if (board->castle_rights & CX_CASTLE_BLACK_QUEENSIDE)
        *c++ = 'q';
    if (board->castle_rights & CX_CASTLE_WHITE_KINGSIDE)
        *c++ = 'K';
    if (board->castle_rights & CX_CASTLE_WHITE_QUEENSIDE)
        *c++ = 'Q';
    if (board->castle_rights == 0)
        *c++ = '-';
    *c++ = ' ';
    // Dump the en passant target square section of the FEN string.
    if (board->en_passant == 0)
        *c++ = '-';
    else
        sprintf(c, "%d", board->en_passant);
    *c++ = ' ';
    // Dump the halfmove and fullmove section of the FEN string.
    sprintf(c, "%d %d", board->halfmove_clock, board->fullmove_number);

    return p;
}
