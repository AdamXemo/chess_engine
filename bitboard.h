#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BITBOARD_H_
#define BITBOARD_H_

typedef struct Board {
    int64_t wP;
    int64_t wN;
    int64_t wB;
    int64_t wR;
    int64_t wQ;
    int64_t wK;

    int64_t bP;
    int64_t bN;
    int64_t bB;
    int64_t bR;
    int64_t bQ;
    int64_t bK;

    // 0 - white, 1 - black
    bool turn;

    bool wQC;
    bool wKC;
    bool bQC;
    bool bKC;

    int8_t enPassant;

} Board;

void setSquare(int64_t *b, int rank, int file);

Board* fenToBitboard(char* fen);

void printBoard(Board *b);

void printBitBoard(int64_t num);

bool getSquare(int64_t b, int rank, int file);

#endif