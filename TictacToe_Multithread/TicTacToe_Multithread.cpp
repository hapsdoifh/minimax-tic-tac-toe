// minimax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MinimaxFunction.h"

int main()
{
    char GamePos[BOARDSIZE][BOARDSIZE] = { Os,0,0,0,Xs,0,0,0,0 };
    memset(GamePos, 0, sizeof(GamePos));
    int* i = 0;
    int xpos, ypos;
    char userSide, ComputerSide, goFirstSide = Xs;
    int CalcDepth = 0;
    std::cout << "Pick depth of calculation:";
    std::cin >> CalcDepth;
    std::cout << "Pick your side (x / o):";
    std::cin >> userSide;
    if (userSide == Xs) {
        ComputerSide = Os;
    }
    else {
        ComputerSide = Xs;
    }
    while (true) {
        if (ComputerSide == goFirstSide) {
            Mparam CompressedParam;
            CompressedParam.depth = CalcDepth;
            CompressedParam.iniDepth = CalcDepth;
            CompressedParam.maximizing = true;
            CompressedParam.position;
            memcpy(CompressedParam.position, GamePos, sizeof(CompressedParam.position));
            CompressedParam.myside = ComputerSide;
            CompressedParam.opponent = userSide;
            minimax((void*)&CompressedParam); //checks the best next move
            i = CompressedParam.Rval;
            GamePos[i[0]][i[1]] = ComputerSide;
            printBoard(GamePos);
            if (anaylzeSituation(GamePos, ComputerSide)) //if the game ended:
                break;
            xpos = inputMove('X');
            ypos = inputMove('Y');
            GamePos[ypos][xpos] = userSide;
            printBoard(GamePos);
            if (anaylzeSituation(GamePos, ComputerSide)) //if the game ended:
                break;
        }
        else {
            xpos = inputMove('X');
            ypos = inputMove('Y');
            GamePos[ypos][xpos] = userSide;
            printBoard(GamePos);            
            Mparam CompressedParam;
            CompressedParam.depth = CalcDepth;
            CompressedParam.iniDepth = CalcDepth;
            CompressedParam.maximizing = true;
            CompressedParam.position;
            memcpy(CompressedParam.position, GamePos, sizeof(CompressedParam.position));
            CompressedParam.myside = ComputerSide;
            CompressedParam.opponent = userSide;
            if (anaylzeSituation(GamePos, ComputerSide)) //if the game ended:
                break;
            minimax((void*)&CompressedParam); //checks the best next move
            i = CompressedParam.Rval;
            GamePos[i[0]][i[1]] = ComputerSide;
            printBoard(GamePos);
            if (anaylzeSituation(GamePos, ComputerSide)) //if the game ended:
                break;
        }

    }
    return 0;
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
