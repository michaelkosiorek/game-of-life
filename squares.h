#ifndef __SQUARES_H
#define __SQUARES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ALIVE 1
#define DEAD 0

typedef struct SquareTag {
    int state;
    int neighbors;
    // int nextState;
} Square;

Square *makeEmptySquare();
void freeSquare(Square *square);
void drawGame(Square ***board, int boardWidth, int boardHeight);
void setNeighborSum(Square ***board,  int boardWidth, int boardHeight, int sqWidth, int sqHeight);
void assessLife(Square *square);
void makeGlider(Square ***board);
void makeGliderGun(Square ***board);

#endif