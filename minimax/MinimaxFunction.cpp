#include "MinimaxFunction.h"



int* minimax(int depth, int iniDepth, bool maximizing, char position[BOARDSIZE][BOARDSIZE], char myside, char opponent) {
    int max = 0;
    int min = 0;
    int rval[3] = { 0,0,0 };
    if (depth == 0) {
        depth = 0;
    }
    char posCpy[BOARDSIZE][BOARDSIZE];
    if (depth == 0 || analyzeBoard(position, myside) || analyzeBoard(position,opponent)||isBoardFull(position)) { //if the it has reached required depth or a side won
        rval[2] = (depth+1) * analyzeBoard(position, myside);
        return rval;
    }
    int y = 0;
    int x = 0;
    int first = 0;
    int temp = 0;
    int percent = 0;
    if (maximizing == true) {
        for (y = 0; y < BOARDSIZE; y++) {
            for (x = 0; x < BOARDSIZE; x++) {
                if (depth == iniDepth) {
                    for (int k = 0; k < 20; k++) {
                        std::cout << "\b";
                    }
                    std::cout << "percent:"<< ((float)percent/BOARDSIZE/BOARDSIZE)*100 ;
                }
                if (position[y][x] == 0) {
                    position[y][x] = myside;
                    memcpy(posCpy, position, sizeof(posCpy));
                    temp = *(minimax(depth - 1, iniDepth, !maximizing, posCpy, myside, opponent)+2);
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
                percent++;
            }
        }
        rval[2] = max;
        return rval;
    }
    else { //minimizing
        for (y = 0; y < BOARDSIZE; y++) {
            for (x = 0; x < BOARDSIZE; x++) {
                if (position[y][x] == 0) {
                    position[y][x] = opponent;
                    memcpy(posCpy, position, sizeof(posCpy));
                    temp = *(minimax(depth - 1, iniDepth, !maximizing, posCpy, myside, opponent)+2);
                    position[y][x] = 0;
                    if (first == 0) {
                        min = temp;
                        first = 1;
                        rval[0] = x;
                        rval[1] = y;
                    }
                    else if (min > temp) {
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

int analyzeBoard(char position[BOARDSIZE][BOARDSIZE], char side) { // 1 is win, 0 is no win
    int x = 0;
    int connect = 0;
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
        connect = 1;
        for (x = 0; x < BOARDSIZE; x++) {
            if (position[x][x] != sideCopy) {
                connect = 0;
            }
        }
        if (connect == 1) {
            won = 1;
        }
        x = 0;

        connect = 1;
        for (x = 0; x < BOARDSIZE; x++) {
            if (position[x][BOARDSIZE - 1 - x] != sideCopy) {
                
                connect = 0;
            }
        }
        if (connect == 1) {
            won = 1;
        }
        x = 0;

        for (y = 0; y < BOARDSIZE; y++) {
            connect = 1;
            for (x = 0; x < BOARDSIZE; x++) {
                if (position[y][x] != sideCopy) {
                    connect = 0;
                }
            }
            if (connect) {
                break;
            }
        }
        if (connect == 1) {
            won = 1;
        }
        y = 0;
        x = 0;

        for (x = 0; x < BOARDSIZE; x++) {
            connect = 1;
            for (y = 0; y < BOARDSIZE; y++) {
                if (position[y][x] != sideCopy) {
                    connect = 0;
                }
            }
            if (connect) {
                break;
            }
        }
        if (connect == 1) {
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

int isBoardFull(char position[BOARDSIZE][BOARDSIZE]) {
    int full = 1;
    for (int y = 0; y < BOARDSIZE; y++) {
        for (int x = 0; x < BOARDSIZE; x++) {
            if (position[y][x] == 0) {
                return 0; // board is not full
            }
        }
    }
    return 1;
}

int anaylzeSituation(char GamePos[BOARDSIZE][BOARDSIZE], char ComputerSide) {
    if (analyzeBoard(GamePos, ComputerSide) != 0 || isBoardFull(GamePos)) {
        if (analyzeBoard(GamePos, ComputerSide)) { // the computer won
            std::cout << "Computer Won!";
        }
        else if (isBoardFull(GamePos)) {
            std::cout << "It's a tie!";
        }
        else {
            std::cout << "Oh wow you won, there's something wrong with the program!";
        }
        return 1;
    }
    else {
        return 0;
    }
}

void printBoard(char GamePos[BOARDSIZE][BOARDSIZE]) {
    std::cout << "\n ";
    for (int j = 0; j < BOARDSIZE; j++) {
        std::cout << "|" << j + 1;
    }
    std::cout << "\n";
    for (int j = 0; j < BOARDSIZE; j++) {
        std::cout << j + 1 << "|"; // output y-coordinates
        for (int k = 0; k < BOARDSIZE; k++) {
            if (GamePos[j][k] == 0) {
                std::cout << "_";
            }
            std::cout << GamePos[j][k];
            std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int inputMove(char axis) { //returns a size 2 array whre [0] is x, and [1] is y
    int pos;
    std::cout << "Enter your move ("<< axis << " position): ";
    std::cin >> pos;
    pos--;
    return pos;
}