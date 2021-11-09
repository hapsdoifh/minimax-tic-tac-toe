#pragma once
#include <string.h>
#include <iostream>
#define BOARDSIZE 4
#define Xs 'x'
#define Os 'o'


int analyzeBoard(char position[BOARDSIZE][BOARDSIZE], char side);
int* minimax(int depth, int iniDepth, bool maximizing, char position[BOARDSIZE][BOARDSIZE], char myside, char opponent);
int isBoardFull(char position[BOARDSIZE][BOARDSIZE]);
int anaylzeSituation(char gamePos[BOARDSIZE][BOARDSIZE], char ComputerSide);
void printBoard(char GamePos[BOARDSIZE][BOARDSIZE]);
int inputMove(char axis);