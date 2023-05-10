#include <stdio.h>
#include "bitboard.h"

#define BUFFER_SIZE 100

typedef struct Move {
    int fileFrom;
    int rankFrom;
    int fileTo;
    int rankTo;
} Move;

typedef struct MoveList {
    Move* start;
    int lastIndex;
    int length;
} MoveList;

MoveList* initMoveList(int length) {
    MoveList* moveList = (MoveList*) malloc(sizeof(MoveList));
    moveList->start = (Move*) malloc(sizeof(Move) * length);
    moveList->lastIndex = -1;
    moveList->length = length;
}

void addMove(MoveList* moveList, Move* move) {
    if (moveList->lastIndex + 1 == moveList->length) {
        moveList->start = realloc(moveList->start, sizeof(Move) * (moveList->length + BUFFER_SIZE));
        moveList->length += BUFFER_SIZE;
    } else if (moveList->lastIndex >= moveList->length) {
        printf("ulta blyat\n");
    }
    moveList->start[moveList->lastIndex+1] = *move;
    moveList->lastIndex++;
}

void printMove(Move* m) {
    printf("%c%d", 'a'+m->fileFrom, 8-m->rankFrom);
    printf("%c%d", 'a'+m->fileTo, 8-m->rankTo);
}



void genKnightMoves(Board* b, MoveList* moveList) {
    int64_t all_black = b->bP | b->bN | b->bB | b->bR | b->bQ | b->bK;
    int64_t all_white = b->wP | b->wN | b->wB | b->wR | b->wQ | b->wK;
    int64_t empty = ~(all_black | all_white);
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {

        }
    }
}


void genPawnMoves(Board* b, MoveList* moveList) {
    int64_t all_black = b->bP | b->bN | b->bB | b->bR | b->bQ | b->bK;
    int64_t all_white = b->wP | b->wN | b->wB | b->wR | b->wQ | b->wK;
    int64_t all = all_black | all_white;

    if (b->turn) {
        int64_t pawns_that_can_move_one_square = b->bP & ((~all) << 8); // DO NOT TOUCH!!!!!!
        int64_t pawns_that_can_move_two_squares = (pawns_that_can_move_one_square & ((~all) << 16));
        int64_t pawns_that_can_capture_to_the_left = b->bP & (all_white << 7);
        int64_t pawns_that_can_capture_to_the_right = b->bP & (all_white << 9);

        printBitBoard(pawns_that_can_capture_to_the_right);

        for (int rank = 1; rank < 7; rank++) {
            for (int file = 1; file < 8; file++) {
                if (getSquare(pawns_that_can_capture_to_the_left, rank, file)) {
                    Move m;
                    m.fileFrom = file;
                    m.rankFrom = rank;
                    m.fileTo = file - 1;
                    m.rankTo = rank + 1;
                    addMove(moveList, &m);
                }
            }
        }

        for (int rank = 1; rank < 7; rank++) {
            for (int file = 0; file < 7; file++) {
                if (getSquare(pawns_that_can_capture_to_the_right, rank, file)) {
                    Move m;
                    m.fileFrom = file;
                    m.rankFrom = rank;
                    m.fileTo = file + 1;
                    m.rankTo = rank + 1;
                    addMove(moveList, &m);
                }
            }
        }

        int rank = 1;
        for (int file = 0; file < 8; file++) {
            if (getSquare(pawns_that_can_move_two_squares, rank, file)) {
                Move m;
                m.fileFrom = file;
                m.rankFrom = rank;
                m.fileTo = file;
                m.rankTo = rank + 2;
                addMove(moveList, &m);
            }
        }
        for (int rank = 1; rank < 7; rank++) {
            for (int file = 0; file < 8; file++) {
                if (getSquare(pawns_that_can_move_one_square, rank, file)) {
                    Move m;
                    m.fileFrom = file;
                    m.rankFrom = rank;
                    m.fileTo = file;
                    m.rankTo = rank + 1;
                    addMove(moveList, &m);
                }
            }
        }
        
    } else {
        int64_t pawns_that_can_move_one_square = b->wP & ((~all) >> 8); // DO NOT TOUCH!!!!!!
        int64_t pawns_that_can_move_two_squares = (pawns_that_can_move_one_square & ((~all) >> 16));
        int64_t pawns_that_can_capture_to_the_left = b->wP & (all_black >> 9);
        int64_t pawns_that_can_capture_to_the_right = b->wP & (all_black >> 7);


        for (int rank = 1; rank < 7; rank++) {
            for (int file = 1; file < 8; file++) {
                if (getSquare(pawns_that_can_capture_to_the_left, rank, file)) {
                    Move m;
                    m.fileFrom = file;
                    m.rankFrom = rank;
                    m.fileTo = file - 1;
                    m.rankTo = rank - 1;
                    addMove(moveList, &m);
                }
            }
        }

        for (int rank = 1; rank < 7; rank++) {
            for (int file = 0; file < 7; file++) {
                if (getSquare(pawns_that_can_capture_to_the_right, rank, file)) {
                    Move m;
                    m.fileFrom = file;
                    m.rankFrom = rank;
                    m.fileTo = file + 1;
                    m.rankTo = rank - 1;
                    addMove(moveList, &m);
                }
            }
        }

        int rank = 6;
        for (int file = 0; file < 8; file++) {
            if (getSquare(pawns_that_can_move_two_squares, rank, file)) {
                Move m;
                m.fileFrom = file;
                m.rankFrom = rank;
                m.fileTo = file;
                m.rankTo = rank - 2;
                addMove(moveList, &m);
            }
        }
        for (rank = 7; rank > 0; rank--) {
            for (int file = 0; file < 8; file++) {
                if (getSquare(pawns_that_can_move_one_square, rank, file)) {
                    Move m;
                    m.fileFrom = file;
                    m.rankFrom = rank;
                    m.fileTo = file;
                    m.rankTo = rank - 1;
                    addMove(moveList, &m);
                }
            }
        }
    }
}

void printArray(MoveList* moveList) {
    for (int i = 0; i <= moveList->lastIndex; i++) {
        printMove(&(moveList->start[i]));
        printf(" ");
    }
    printf("\n");
}


int main() {
    char* fen = "r1bqkbnr/1pp1p1pp/8/pP1pnp2/8/2N5/P1PP1PPP/R1BQKBNR w KQkq a6 0 6";
    Board* chessBoard = fenToBitboard(fen);
    printf("%d\n", chessBoard->enPassant);
    printBoard(chessBoard);
    MoveList* pawnMoves = initMoveList(30);
    genPawnMoves(chessBoard, pawnMoves);
    printArray(pawnMoves);
    free(pawnMoves->start);
    free(pawnMoves);

    return 0;
}

