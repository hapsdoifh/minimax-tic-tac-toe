#include "MinimaxFunction.h"



int* minimax(int depth, bool maximizing, char position[3][3], char myside, char opponent) {
    int max = 0;
    int min = 0;
    int rval[3] = { 0,0,0 };
    char posCpy[3][3];
    if (depth == 0 || analyzePos(position, myside)) { //if the it has reached required depth or a side won
        rval[2] = analyzePos(position, myside);
        return rval;
    }
    int y = 0;
    int x = 0;
    int first = 0;
    int temp = 0;
    if (maximizing == true) {
        for (y = 0; y < 3; y++) {
            for (x = 0; x < 3; x++) {
                if (position[y][x] == 0) {
                    position[y][x] = myside;
                    memcpy(posCpy, position, sizeof(posCpy));
                    temp = *(minimax(depth - 1, !maximizing, posCpy, myside, opponent)+2);
                    position[y][x] = 0;
                    if (first == 0) {
                        max = temp;
                        first = 1;
                        rval[0] = x;
                        rval[1] = y;
                    }
                    else if (max < temp) {
                        max = temp;
                        rval[0] = x;
                        rval[1] = y;
                    }
                }
            }
        }
        rval[2] = max;
        return rval;
    }
    else { //minimizing
        for (y = 0; y < 3; y++) {
            for (x = 0; x < 3; x++) {
                if (position[y][x] == 0) {
                    position[y][x] = opponent;
                    temp = *(minimax(depth - 1, !maximizing, position, myside, opponent)+2);
                    if (first == 0) {
                        min = temp;
                        min = 1;
                        rval[0] = x;
                        rval[1] = y;
                    }
                    else if (max > temp) {
                        min = temp;
                        rval[0] = x;
                        rval[1] = y;
                    }
                }
            }
        }
        rval[2] = min;
        return rval;
    }
}

int analyzePos(char position[3][3], char side) { // 1 is win, 0 is no win
    int x = 0;
    int y = 0;
    int won = 0;
    char opponent = 0;
    char sideCopy = side;
    if (side == Xs) {
        opponent = Os;
    }
    else {
        opponent = Xs;
    }
    do {
        x = 0;
        y = 0;
        for (y = 0; y < 3; y++) {
            if (position[y][x] == sideCopy && position[y][x + 1] == sideCopy && position[y][x + 2] == sideCopy) {
                won = 1;
            }
        }
        for (x = 0; x < 3; x++) {
            if (position[y][x] == sideCopy && position[y + 1][x] == sideCopy && position[y + 2][x] == sideCopy) {
                won = 1;
            }
        }
        if (position[0][0] == sideCopy && position[1][1] == sideCopy && position[2][2] == sideCopy) {
            won = 1;
        }
        if (position[0][2] == sideCopy && position[1][1] == sideCopy && position[2][0] == sideCopy) {
            won = 1;
        }
        if (won) {
            if (sideCopy == side) { //computer side won
                return 1;
            }
            else {
                return -1;
            }
        }
        if (sideCopy == side) // this lets sideCopy switch between opponent and side
            sideCopy = opponent;
        else
            sideCopy = side;
    } while (sideCopy != side);
    return 0;
}

