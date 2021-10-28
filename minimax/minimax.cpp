// minimax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define Xs 'x'
#define Os 'o'

#include <iostream>

int analyzePos(char position[3][3], char side);

int minimax(int depth, bool maximizing, char position[3][3]) {
    if (depth == 0 || analyzePos(position, Os)) {
        return  analyzePos(position, Os);
    }
    int y = 0;
    int x = 0;
    for (y = 0; y < 3; y++) {
        for (x = 0; x < 3; x++){
        }
    }
    return 0;
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
            if (position[y][x] == sideCopy && position[y+1][x] == sideCopy && position[y+2][x] == sideCopy) {
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

int main()
{
    char PlayerPos[3][3] = { Xs,Xs,Xs,Os,Os,0,0,0,0 };
    std::cout << analyzePos(PlayerPos, Os);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
