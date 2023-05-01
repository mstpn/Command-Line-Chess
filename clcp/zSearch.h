#ifndef ZSEARCH_H
#define ZSEARCH_H

#include "Board.h"
#include <vector>
#include <map>
#include "zHandler.h"
#include "zTransposition.h"
#include <string.h>

typedef struct pieceMove
{
    int eval;   // evaluation of board state
    int fromX;
    int fromY;
    int toX;
    int toY;
}pieceMove;

void rootNegamax(Board &b, bool turn, int depth, pieceMove &nextMove, int alpha, int beta, TranspositionTable *ttable, int numThreads);
int negamax(Board &b, bool turn, int depth, int alpha, int beta, TranspositionTable *table, int numThreads);
pieceMove getMove(vector<pieceMove> moveList, int alpha);



#endif