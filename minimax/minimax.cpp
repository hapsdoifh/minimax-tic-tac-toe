// minimax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MinimaxFunction.h"


int main()
{   
    char PlayerPos[3][3] = { 0,0,0,0,0,0,0,0,0 };
    int* i = 0;
    int xpos, ypos;
    while (true) {
        i = minimax(8, true, PlayerPos, Xs, Os);
        PlayerPos[i[1]][i[0]] = Xs;
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (PlayerPos[j][k] == 0) {    
                    std::cout << "_";
                }
                std::cout << PlayerPos[j][k];
                std::cout << " ";
            }
            std::cout << "\n";
        }
        if (analyzePos(PlayerPos, Xs) != 0) {
            std::cout << "Game over!";
            break;
        }
        std::cout << "Enter your move";
        std::cin >> xpos;
        std::cin >> ypos;
        PlayerPos[ypos][xpos] = Os;
    }
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
