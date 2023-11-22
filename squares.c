#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "squares.h"

#define ALIVE 1
#define DEAD 0

Square *makeEmptySquare() {
    Square *emptySquare = malloc(sizeof(Square));
    emptySquare->state = DEAD;
    emptySquare->neighbors = 0;
    // emptySquare->nextState = DEAD;
    return emptySquare;
}

void freeSquare(Square *square) {
    free(square);
}

void drawGame(Square ***board, int boardWidth, int boardHeight) {
    for (int i=0; i < boardHeight; i++) {
        for (int j=0; j < boardWidth; j++) {
            if (board[i][j]->state==ALIVE) printf("■ ");
            else printf("☐ ");
        }
        printf("\n");
    }
    printf("\n");
}

void setNeighborSum(Square ***board, int boardWidth, int boardHeight, int sqWidth, int sqHeight) { 

    int neighborSum=0;

    if (sqHeight == 0) { // top row
        if (sqWidth == 0) { // top left case
            neighborSum += board[1][1]->state + board[1][0]->state + board[0][1]->state;
        } else if (sqWidth == boardWidth-1) { // top right
            neighborSum += board[sqHeight][sqWidth-1]->state + board[sqHeight+1][sqWidth-1]->state + board[sqHeight+1][sqWidth]->state;
        } else { // top row (middle)
            neighborSum += board[sqHeight][sqWidth-1]->state + board[sqHeight][sqWidth+1]->state;
            neighborSum += board[sqHeight+1][sqWidth-1]->state + board[sqHeight+1][sqWidth]->state + board[sqHeight+1][sqWidth+1]->state;
        }
    } else if (sqHeight == boardHeight-1) { // bottom row
        if (sqWidth == 0) { // bottom left
            neighborSum += board[sqHeight-1][sqWidth]->state + board[sqHeight-1][sqWidth+1]->state + board[sqHeight][sqWidth+1]->state;
        } else if (sqWidth == boardWidth-1) { // bottom right
            neighborSum += board[sqHeight-1][sqWidth-1]->state + board[sqHeight-1][sqWidth]->state + board[sqHeight][sqWidth-1]->state;
        } else { // bottom row (middle)
            neighborSum += board[sqHeight-1][sqWidth-1]->state + board[sqHeight-1][sqWidth]->state + board[sqHeight-1][sqWidth+1]->state;
            neighborSum += board[sqHeight][sqWidth-1]->state + board[sqHeight][sqWidth+1]->state;
        }
    } else {
        if (sqWidth==0) { // left middle
            neighborSum += board[sqHeight-1][sqWidth]->state + board[sqHeight-1][sqWidth+1]->state + board[sqHeight][sqWidth+1]->state;
            neighborSum += board[sqHeight+1][sqWidth]->state + board[sqHeight+1][sqWidth+1]->state;
        } else if (sqWidth == boardWidth-1) { // right middle
            neighborSum += board[sqHeight-1][sqWidth-1]->state + board[sqHeight-1][sqWidth]->state + board[sqHeight][sqWidth-1]->state;
            neighborSum += board[sqHeight+1][sqWidth-1]->state + board[sqHeight+1][sqWidth]->state;
        } else { // true middle
            neighborSum += board[sqHeight-1][sqWidth-1]->state + board[sqHeight-1][sqWidth]->state + board[sqHeight-1][sqWidth+1]->state;
            neighborSum += board[sqHeight][sqWidth-1]->state + board[sqHeight][sqWidth+1]->state;
            neighborSum += board[sqHeight+1][sqWidth-1]->state + board[sqHeight+1][sqWidth]->state + board[sqHeight+1][sqWidth+1]->state;
        }
    }
    board[sqHeight][sqWidth]->neighbors = neighborSum;
}

void assessLife(Square *square) {
    int neighbors = square->neighbors;
    if (square->state == DEAD) {
        if (neighbors==3) square->state = ALIVE;
    } else {
        if (neighbors!=2 && neighbors!=3) square->state = DEAD;
    }
}

void makeGlider(Square ***board) {
    board[1][2]->state = ALIVE;
    board[2][3]->state = ALIVE;
    board[3][1]->state = ALIVE;
    board[3][2]->state = ALIVE;
    board[3][3]->state = ALIVE;
}

void makeGliderGun(Square ***board) {
    board[5][1]->state = ALIVE;
    board[5][2]->state = ALIVE;
    board[6][1]->state = ALIVE;
    board[6][2]->state = ALIVE;

    board[5][11]->state = ALIVE;
    board[6][11]->state = ALIVE;
    board[7][11]->state = ALIVE;
    board[4][12]->state = ALIVE;
    board[8][12]->state = ALIVE;
    board[3][13]->state = ALIVE;
    board[9][13]->state = ALIVE;
    board[3][14]->state = ALIVE;
    board[9][14]->state = ALIVE;
    board[6][15]->state = ALIVE;
    board[4][16]->state = ALIVE;
    board[8][16]->state = ALIVE;
    board[5][17]->state = ALIVE;
    board[6][17]->state = ALIVE;
    board[7][17]->state = ALIVE;
    board[6][18]->state = ALIVE;

    board[3][21]->state = ALIVE;
    board[4][21]->state = ALIVE;
    board[5][21]->state = ALIVE;
    board[3][22]->state = ALIVE;
    board[4][22]->state = ALIVE;
    board[5][22]->state = ALIVE;
    board[2][23]->state = ALIVE;
    board[6][23]->state = ALIVE;

    board[1][25]->state = ALIVE;
    board[2][25]->state = ALIVE;
    board[6][25]->state = ALIVE;
    board[7][25]->state = ALIVE;

    board[3][35]->state = ALIVE;
    board[4][35]->state = ALIVE;
    board[3][36]->state = ALIVE;
    board[4][36]->state = ALIVE;
}