#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "squares.h"

#define BOARDWIDTH 38 // 38==glidergun
#define BOARDHEIGHT 26 // 26==glidergun
#define MICROTOMILLI 1000
#define STAGE_LENGTH_MICROSECONDS 250*MICROTOMILLI


int main(int argc, char *argv[]) {

    int board_width;
    int board_height;
    if (argc==3) {
        board_width = atoi(argv[1]);
        board_height = atoi(argv[2]);
    } else {
        board_width = BOARDWIDTH;
        board_height = BOARDHEIGHT;
    }

    // array of pointers to pointers to squares
    Square ***board = (Square***)malloc(sizeof(Square**)*board_height);

    // each pointer to pointers in ptr2ptrArr is allocated GAMEWIDTH(10) pointers to squares
    for (int i=0; i < board_height; i++) {
        board[i] = (Square**)malloc(sizeof(Square*)*board_width);
        for (int j=0; j < board_width; j++) {
            board[i][j] = makeEmptySquare();
        }
    }

    //makeGlider(board);
    if (board_height >= 26 && board_width >= 38)
        makeGliderGun(board);
    else {
        printf("Invalid height/width for glider gun.\n");
        exit(0);
    }

    sleep(1);
    while(1) {

        drawGame(board, board_width, board_height); // prints board

        for (int i=0; i < board_height; i++) { // loop to reset neighbor count, set
            for (int j=0; j < board_width; j++) {
                setNeighborSum(board, board_width, board_height, j, i);
            }
        }

        for (int i=0; i < board_height; i++) { // loop to reset neighbor count, set
            for (int j=0; j < board_width; j++) {
                assessLife(board[i][j]);
            }
        }

        usleep(STAGE_LENGTH_MICROSECONDS);
    }



    return 0;
}

