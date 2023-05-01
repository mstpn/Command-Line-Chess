#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include "Board.h"
#include "ioutil.h"
#include "Piece.h"
#include <vector>
#include <map>
#include "zSearch.h"

#define MAX_EVAL 100000

extern int taskCount;
extern pthread_mutex_t mutexQueue;
extern pthread_cond_t condQueue;

struct Task
{
    Board *b;
    PiecePtr p;
    map<int, vector<int>> *moves;
    int key;
    int row;
    int col;
};

extern Task taskQueue[];

using namespace std;

void aiTurn(Board &b, bool turn, int &fromX, int &fromY, int &toX, int &toY, int depth, int numThreads);
void allValidMoves(Board &b, bool turn, map<int, vector<int>> &moves, int numThreads);
int pieceValidMoves(Board &b, PiecePtr p, vector<int> &moves, int row, int col);
int encodeMove(int row, int col);
void decodeMove(int move, int &row, int &col);
void executeTask(Task *task);
void *startThread(void *args);
void submitTask(Task task);

#endif