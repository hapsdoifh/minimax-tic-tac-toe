#pragma once
#include <string.h>
#define Xs 'x'
#define Os 'o'

typedef struct minimaxinfo {
	int x;
	int y;
	int eval;
} MnmxInfo;


int analyzePos(char position[3][3], char side);
int* minimax(int depth, bool maximizing, char position[3][3], char myside, char opponent);