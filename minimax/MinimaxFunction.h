#pragma once
#include <string.h>
#include <iostream>
#define Xs 'x'
#define Os 'o'

typedef struct minimaxinfo {
	int x;
	int y;
	int eval;
} MnmxInfo;


int analyzeBoard(char position[3][3], char side);
int* minimax(int depth, bool maximizing, char position[3][3], char myside, char opponent);
int isBoardFull(char position[3][3]);
int anaylzeSituation(char gamePos[3][3], char ComputerSide);
void printBoard(char GamePos[3][3]);
int inputMove(char axis);