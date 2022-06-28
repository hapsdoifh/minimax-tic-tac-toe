#include "MinimaxFunction.h"

HANDLE MinimaxMutex = CreateMutex(NULL, FALSE, NULL);
int ThreadFinishCnt;

void FillCompressParam(Mparam* ParamIn, int depth, int iniDepth, bool maximizing, char position[BOARDSIZE][BOARDSIZE], char myside, char opponent) {
    ParamIn->depth = depth;
    ParamIn->iniDepth = iniDepth;
    ParamIn->maximizing = maximizing;
    ParamIn->position;
    memcpy(ParamIn->position, position, sizeof(ParamIn->position));
    ParamIn->myside = myside;
    ParamIn->opponent = opponent;
}

void minimax(void* Args) {
    Mparam* CompressedParameter = (Mparam*)Args;
    int depth = CompressedParameter->depth;
    int iniDepth = CompressedParameter->iniDepth;
    bool maximizing = CompressedParameter->maximizing;
    char position[BOARDSIZE][BOARDSIZE];
    memcpy(position, CompressedParameter->position, sizeof(position));
    char myside = CompressedParameter->myside;
    char opponent = CompressedParameter->opponent;
    Mparam* Pointerlist[(BOARDSIZE*BOARDSIZE)];
    Mparam* sizetest[2];
    int pointercount = 0;
    int MaxMin = 0;
    int min = 0;
    int rval[3] = { 0,0,0 };
    int MovableSpace = 0;
    if (depth == CompressedParameter->iniDepth) {
        ThreadFinishCnt = 0;
    }
    char posCpy[BOARDSIZE][BOARDSIZE];
    if (depth <= 0 || analyzeBoard(position, myside) || analyzeBoard(position, opponent) || isBoardFull(position)) { //if the it has reached required depth or a side won
        rval[2] = (depth + 1) * analyzeBoard(position, myside);
        memcpy(CompressedParameter->Rval, rval, sizeof(CompressedParameter->Rval));
        if (depth == (iniDepth - 1)) {
            //printf("Theadended\n");
            DWORD WaitResult;
            WaitResult = WaitForSingleObject(MinimaxMutex, INFINITE);
            if (WaitResult == WAIT_OBJECT_0 || WaitResult == WAIT_ABANDONED) {
                ThreadFinishCnt += 1;
            }
            ReleaseMutex(MinimaxMutex);
            _endthread();

        }
        else {
            return;
        }
    }
    int y = 0;
    int x = 0;
    int first = 0;
    int temp = 0;
    int percent = 0;
    bool CompareCond = false;
    if (maximizing == true) {
        CompareCond = true;
    }
    if (depth == iniDepth - 1) {
        depth = depth;
    }
    for (y = 0; y < BOARDSIZE; y++) {
        for (x = 0; x < BOARDSIZE; x++) {
            if (depth == iniDepth) {
                for (int k = 0; k < 20; k++) {
                    std::cout << "\b";
                }
                std::cout << "percent:" << ((float)percent / BOARDSIZE / BOARDSIZE) * 100;
            }
            if (position[y][x] == 0) {
                if (maximizing) {
                    position[y][x] = myside;
                }else{
                    position[y][x] = opponent;
                }
                Mparam childParam;
                FillCompressParam(&childParam, depth-1, iniDepth, !maximizing, position, myside, opponent);
                if (depth == iniDepth) {
                    MovableSpace++;
                    Pointerlist[pointercount] = (Mparam*) malloc(sizeof(Mparam));
                    memcpy(Pointerlist[pointercount], &childParam, sizeof(childParam));
                    Pointerlist[pointercount]->MyPos[0] = y;
                    Pointerlist[pointercount]->MyPos[1] = x;
                    printf("threadStarted\n");
                    _beginthread(minimax,NULL,(void*)Pointerlist[pointercount]);
                    pointercount++;
                }
                else {
                    minimax((void*)&childParam);
                    temp = *(childParam.Rval + 2);
                    if (first == 0) {
                        MaxMin = temp;
                        first = 1;
                        rval[1] = x;
                        rval[0] = y;
                    }
                    else if (MaxMin == temp) { //this is so the function always pick the one that is > or < never >= or <=
                    }
                    else if ((MaxMin < temp) == CompareCond) {
                        MaxMin = temp;
                        rval[1] = x;
                        rval[0] = y;
                    }
                }
                position[y][x] = 0;
            }
            percent++;
        }
    }
    rval[2] = MaxMin;
    memcpy(CompressedParameter->Rval, rval, sizeof(CompressedParameter->Rval));
    DWORD WaitResult;
    if (depth == (iniDepth - 1)) {
        //printf("Theadended\n");
        DWORD WaitResult;
        WaitResult = WaitForSingleObject(MinimaxMutex,INFINITE);
        if (WaitResult == WAIT_OBJECT_0 || WaitResult == WAIT_ABANDONED) {
            ThreadFinishCnt += 1;
        }
        ReleaseMutex(MinimaxMutex);
        _endthread();

        printf("?>>>\n");
    }
    else if (depth == iniDepth) {
        while (true) {
            WaitResult = WaitForSingleObject(MinimaxMutex, INFINITE);
            if (WaitResult == WAIT_OBJECT_0 || WaitResult == WAIT_ABANDONED) { //wait for mutex then checks if all the threads are finished
                if (ThreadFinishCnt >= MovableSpace){
                    ReleaseMutex(MinimaxMutex);
                    for (int MvCycle = 0; MvCycle < MovableSpace; MvCycle++) {
                        if (MvCycle == 0) {
                            CompressedParameter->Rval[0] = Pointerlist[MvCycle]->MyPos[0];
                            CompressedParameter->Rval[1] = Pointerlist[MvCycle]->MyPos[1];
                            CompressedParameter->Rval[2] = Pointerlist[MvCycle]->Rval[2];
                        }
                        else if (CompressedParameter->Rval[2] == Pointerlist[MvCycle]->Rval[2]) {
                        }
                        else if ((CompressedParameter->Rval[2] < Pointerlist[MvCycle]->Rval[2]) == CompareCond) {
                            CompressedParameter->Rval[0] = Pointerlist[MvCycle]->MyPos[0];
                            CompressedParameter->Rval[1] = Pointerlist[MvCycle]->MyPos[1];
                            CompressedParameter->Rval[2] = Pointerlist[MvCycle]->Rval[2];
                        }
                        free(Pointerlist[MvCycle]);
                    }
                    break;
                }
                else {
                    ReleaseMutex(MinimaxMutex);
                }
            }
        }
    }
    else{ //just normal call, not a individual thread
        return;
    }


    return;
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
    std::cout << "Enter your move (" << axis << " position): ";
    std::cin >> pos;
    pos--;
    return pos;
}