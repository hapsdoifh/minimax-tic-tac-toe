#pragma once
#include <string.h>
#include <iostream>
#include <windows.h>
#include <process.h>    /* _beginthread, _endthread */
#include <stddef.h>
#include <thread>
#include <stdio.h>
#define BOARDSIZE 4
#define Xs 'x'
#define Os 'o'

typedef struct MinimaxParam {
	int depth;
	int iniDepth;
	bool maximizing;
	char position[BOARDSIZE][BOARDSIZE];
	char myside;
	char opponent;
	int Rval[3];
	int MyPos[2]; //y,x
}Mparam;


int analyzeBoard(char position[BOARDSIZE][BOARDSIZE], char side);
void minimax(void* Vargs);
int isBoardFull(char position[BOARDSIZE][BOARDSIZE]);
int anaylzeSituation(char gamePos[BOARDSIZE][BOARDSIZE], char ComputerSide);
void printBoard(char GamePos[BOARDSIZE][BOARDSIZE]);
int inputMove(char axis);