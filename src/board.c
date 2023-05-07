//
// Created by acm on 5/6/23.
//
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "util.h"

static const char    *START_POS = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

cx_board_t *cx_board_init(void) {
    cx_board_t *board = calloc(1, sizeof(cx_board_t));
    if (board == NULL) {
        cx_log("calloc failed", CX_LOG_ERROR);
        exit(EXIT_FAILURE);
    }

    cx_log("Initializing board", CX_LOG_INFO);
    cx_board_fen_load(board, START_POS);

    return board;
}

void cx_board_free(cx_board_t *board) {
    free(board);
}

ssize_t cx_board_fen_load(cx_board_t *board, char const *fen) {
    assert(board != NULL);
    assert(fen != NULL);

    cx_log("Loading FEN", CX_LOG_INFO);
    // Read the FEN string into our bitboards

    // Split the FEN string into its component parts
    char fen_copy[strlen(fen) + 1];
    strcpy(fen_copy, fen);
    char *parts[6];
    char *token = strtok(fen_copy, " ");
    int i = 0;
    while (token != NULL && i < 6) {
        parts[i++] = token;
        token = strtok(NULL, " ");
    }

    // Parse the piece placement section of the FEN string
    char *piece_placement = parts[0];
    int rank = 7;
    int file = 0;
    for (const char *c = piece_placement; *c != '\0'; c++) {
        if (*c == '/') {
            // Move to the next rank
            rank--;
            file = 0;
        } else if (*c >= '1' && *c <= '8') {
            // Skip empty squares
            file += *c - '0';
        } else {
            // Place the piece on the board
            int index = rank * 8 + file;
            cx_bitboard_t *bitboard;
            switch (*c) {
                case 'P':
                    bitboard = &board->white_pawns;
                    break;
                case 'p':
                    bitboard = &board->black_pawns;
                    break;
                case 'N':
                    bitboard = &board->white_knights;
                    break;
                case 'n':
                    bitboard = &board->black_knights;
                    break;
                case 'B':
                    bitboard = &board->white_bishops;
                    break;
                case 'b':
                    bitboard = &board->black_bishops;
                    break;
                case 'R':
                    bitboard = &board->white_rooks;
                    break;
                case 'r':
                    bitboard = &board->black_rooks;
                    break;
                case 'Q':
                    bitboard = &board->white_queens;
                    break;
                case 'q':
                    bitboard = &board->black_queens;
                    break;
                case 'K':
                    bitboard = &board->white_king;
                    break;
                case 'k':
                    bitboard = &board->black_king;
                    break;
            }
            *bitboard |= CX_BIT << index;
            file++;
        }
    }
    return 0;
}

ssize_t cx_board_fen_dump(cx_board_t const *board, char *fen, size_t n) {
    cx_log("Dumping FEN", CX_LOG_INFO);
    // Dump the board into a FEN string
    assert(board != NULL);
    assert(fen != NULL);

    // Dump the piece placement section of the FEN string
    char *piece_placement = fen;
    int rank = 7;
    int file = 0;


    return 0;
}