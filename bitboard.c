#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bitboard.h"

void setSquare(int64_t *b, int rank, int file) {
    *b |= (1LL << (63 - rank*8 - file));
}

Board* fenToBitboard_before(char* fen) {
    Board* b = malloc(sizeof(Board));
    memset(b, 0, sizeof(Board));

    int file = 0;
    int rank = 0;

    for (int i = 0; fen[i] != ' '; i++) {
        if (fen[i] >= '1' && fen[i] <= '8') {
            file += (fen[i] - '0');
        } else if (fen[i] == '/') {
            rank++;
            file = 0;
        } else {
            switch (fen[i]) {
                case 'P':
                    setSquare(&(b->wP), rank, file);
                    break;
                case 'N':
                    setSquare(&(b->wN), rank, file);
                    break;
                case 'B':
                    setSquare(&(b->wB), rank, file);
                    break;
                case 'R':
                    setSquare(&(b->wR), rank, file);
                    break;
                case 'Q':
                    setSquare(&(b->wQ), rank, file);
                    break;
                case 'K':
                    setSquare(&(b->wK), rank, file);
                    break;
                case 'p':
                    setSquare(&(b->bP), rank, file);
                    break;
                case 'n':
                    setSquare(&(b->bN), rank, file);
                    break;
                case 'b':
                    setSquare(&(b->bB), rank, file);
                    break;
                case 'r':
                    setSquare(&(b->bR), rank, file);
                    break;
                case 'q':
                    setSquare(&(b->bQ), rank, file);
                    break;
                case 'k':
                    setSquare(&(b->bK), rank, file);
                    break;
            }
            file++;
        }
    }
    
    return b;
}

Board* fenToBitboard(char* fen) {
    Board* b = malloc(sizeof(Board));
    memset(b, 0, sizeof(Board));

    int file = 0;
    int rank = 0;
    int i = 0;

    while (fen[i] != ' ') {
        if (fen[i] >= '1' && fen[i] <= '8') {
            file += (fen[i] - '0');
        } else if (fen[i] == '/') {
            rank++;
            file = 0;
        } else {
            switch (fen[i]) {
                case 'P':
                    setSquare(&(b->wP), rank, file);
                    break;
                case 'N':
                    setSquare(&(b->wN), rank, file);
                    break;
                case 'B':
                    setSquare(&(b->wB), rank, file);
                    break;
                case 'R':
                    setSquare(&(b->wR), rank, file);
                    break;
                case 'Q':
                    setSquare(&(b->wQ), rank, file);
                    break;
                case 'K':
                    setSquare(&(b->wK), rank, file);
                    break;
                case 'p':
                    setSquare(&(b->bP), rank, file);
                    break;
                case 'n':
                    setSquare(&(b->bN), rank, file);
                    break;
                case 'b':
                    setSquare(&(b->bB), rank, file);
                    break;
                case 'r':
                    setSquare(&(b->bR), rank, file);
                    break;
                case 'q':
                    setSquare(&(b->bQ), rank, file);
                    break;
                case 'k':
                    setSquare(&(b->bK), rank, file);
                    break;
                case ' ':
                    break;
                default:
                    break;
            }
            file++;
        }
        i++;
    }

    i++;
    b->turn = (fen[i] == 'w') ? 0 : 1;
    i += 2;

    if (fen[i] != '-') {
        while (fen[i] != ' ') {
            switch (fen[i]) {
                case 'K':
                    b->wKC = true;
                    break;
                case 'Q':
                    b->wQC = true;
                    break;
                case 'k':
                    b->bKC = true;
                    break;
                case 'q':
                    b->bQC = true;
                    break;
                default:
                    break;
            }
            i++;
        }
    }
    i++; 
    
    if (fen[i] != '-') {
        b->enPassant = fen[i] - 'a';
    }

    return b;
}

void printBoard(Board *b) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((b->wP >> (63 - row*8 - col)) & 1)
                printf("P");
            else if ((b->wN >> (63 - row*8 - col)) & 1)
                printf("N");
            else if ((b->wB >> (63 - row*8 - col)) & 1)
                printf("B");
            else if ((b->wR >> (63 - row*8 - col)) & 1)
                printf("R");
            else if ((b->wQ >> (63 - row*8 - col)) & 1)
                printf("Q");
            else if ((b->wK >> (63 - row*8 - col)) & 1)
                printf("K");
            else if ((b->bP >> (63 - row*8 - col)) & 1)
                printf("p");
            else if ((b->bN >> (63 - row*8 - col)) & 1)
                printf("n");
            else if ((b->bB >> (63 - row*8 - col)) & 1)
                printf("b");
            else if ((b->bR >> (63 - row*8 - col)) & 1)
                printf("r");
            else if ((b->bQ >> (63 - row*8 - col)) & 1)
                printf("q");
            else if ((b->bK >> (63 - row*8 - col)) & 1)
                printf("k");
            else
                printf(".");
            printf(" ");
        }
        printf("\n");
    }
}

void printBitBoard(int64_t num) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            printf("%d", (num >> (63 - row*8 - col)) & 1);
        }
        printf("\n");
    }
}

bool getSquare(int64_t b, int rank, int file) {
    return (bool) ((b >> (63 - rank*8 - file)) & 1LL);

}