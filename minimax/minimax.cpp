// minimax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MinimaxFunction.h"


int main()
{   
    char GamePos[3][3] = { 0,0,0,0,0,0,0,0,0 };
    int* i = 0;
    int xpos, ypos;
    char userSide, ComputerSide,goFirstSide = Xs;
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
            i = minimax(8, true, GamePos, ComputerSide, userSide); //checks the best next move
            GamePos[i[1]][i[0]] = ComputerSide;
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
            if (anaylzeSituation(GamePos, ComputerSide)) //if the game ended:
                break;
            i = minimax(8, true, GamePos, ComputerSide, userSide); //checks the best next move
            GamePos[i[1]][i[0]] = ComputerSide;
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
