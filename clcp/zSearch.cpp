/*
    This file handles the logic for the negamax alpha beta search. It also contains the logic for selecting a candidate move from the list of moves.

    The overall flow of the search is to take in a board state, turn, and transposition table. We then recursivley evaluate every position and return the best move.

    https://www.chessprogramming.org/Negamax
    The root negamax function is the entry point for the negamax search. It is called with the board, turn, depth, and transposition table. It then calls the negamax function to find the best move. Alpha and beta values are set to the maximum and minimum evaluation values in order to prune the search tree and avoid moves that are too good, or too bad. Negamax is used instead of minimax because it is easier to implement alpha beta pruning.

    Inuput:
        The board
        Whose turn it is
        The depth of the search
        The next move
            By reference
        Alpha and beta values
        The transposition table
        The number of threads to use
    Output:
        Updated next move
        Updated transposition table
 */

#include "zSearch.h"

void rootNegamax(Board &b, bool turn, int depth, pieceMove &nextMove, int alpha, int beta, TranspositionTable *ttable, int numThreads)
{
    map<int, vector<int>> moves; // map of all valid moves

    vector<pieceMove> moveList; // list of top level moves and evaluations

    allValidMoves(b, turn, moves, numThreads);

    // loop all move from positions
    for (auto &&[key, value] : moves)
    {
        // !HERE
        if (moves[key].size() == 0)
        {
            moves.erase(key);
            continue;
        }
        // loop each to position
        for (int i = 0; i < (int)value.size(); i++)
        {
            // Play the move on a copy of the board
            int fromX, fromY, toX, toY;
            decodeMove(key, fromX, fromY);
            decodeMove(value[i], toX, toY);
            Board newBoard;
            newBoard.initBoard();
            newBoard.copyBoard(b);
            bool success = newBoard.move(turn, fromX, fromY, toX, toY);
            if (success == false)
            {
                cout << "Error: move not successful" << endl;
            }

            // recursive call
            int evaluation = -negamax(newBoard, !turn, depth - 1, -beta, -alpha, ttable, numThreads);

            // update moveList
            pieceMove newMove;
            newMove.eval = evaluation;
            newMove.fromX = fromX;
            newMove.fromY = fromY;
            newMove.toX = toX;
            newMove.toY = toY;
            // newMove.firstMoveColour = turn;
            moveList.push_back(newMove);
        }
    }

    // choose best move
    nextMove = getMove(moveList, alpha);

    return;
}

/*
    The recursive negamax function.
    We check the transposition table to see if we have already evaluated this position. If we have, we return the evaluation.

    If we are at depth 0 or the game is over, we are in the recursive base cse.
        We evaluate the position and add it to the transposition table.

    If we are not in the base case, we recursively call negamax on all possible moves from the current position.

    Input:
        The board
        Whose turn it is
        The depth of the search
        Alpha and beta
        The transposition table
        The number of threads to use
    Output:
        The evaluation of the position
        Updated transposition table
 */
int negamax(Board &b, bool turn, int depth, int alpha, int beta, TranspositionTable *ttable, int numThreads)
{
    // check transposition table
    char fen[100];
    b.boardToFEN(fen, turn);
    size_t hash = DJBHash(fen);
    size_t index = hash % TABLE_ENTRIES;

    if (ttable->lookup[index].used == true)
    {
        if (strcmp(ttable->lookup[index].fen, fen) == 0)
        {
            // Transposition table hit for this position
            return ttable->lookup[index].eval;
        }
    }

    // base case
    bool winner;
    if (depth == 0 || b.kingCapture(winner) == true)
    {
        int eval = b.boardEval(turn);
        // add evaluation to transposition table. Use LRU replacement policy, so overwrite
        ttable->lookup[index].used = true;
        strcpy(ttable->lookup[index].fen, fen);
        ttable->lookup[index].eval = eval;
        return eval;
    }

    // recursive case
    map<int, vector<int>> moves;

    allValidMoves(b, turn, moves, numThreads);

    // loop all move from positions
    for (auto &&[key, value] : moves)
    {
        // !HERE
        if (moves[key].size() == 0)
        {
            moves.erase(key);
            continue;
        }
        // loop each to position
        for (int i = 0; i < (int)value.size(); i++)
        {
            // Play the move on a copy of the board
            int fromX, fromY, toX, toY;
            decodeMove(key, fromX, fromY);
            decodeMove(value[i], toX, toY);
            Board newBoard;
            newBoard.initBoard();
            newBoard.copyBoard(b);
            bool success = newBoard.move(turn, fromX, fromY, toX, toY);
            if (success == false)
            {
                cout << "Error: move not successful" << endl;
            }

            // recursive call
            int evaluation = -negamax(newBoard, !turn, depth - 1, -beta, -alpha, ttable, numThreads);

            // update alpha
            //! I think this is what lets us make dumb moves, then have the AI not punish us. Since we would never make a needless sacrifice, it doesn't consider the move, then when we randomize moves, we get a dumb move.
            //* Fixed? By not randomizing when only a small number of moves are available.
            if (evaluation >= beta)
            {
                // beta cut-off, opponent will never allow this move
                return beta;
            }
            if (evaluation > alpha)
            {
                // new best move found
                alpha = evaluation;
            }
        }
    }
    return alpha;
}

/*
    Selects a candidate move from the list of possible moves
    We select the best move, or a random move if there are multiple best moves.
        If there are a small number of moves, we do not randomize (see comments in negamax and below)
    Input:
        The list of possible moves
        The current alpha value
    Output:
        The best move
 */
pieceMove getMove(vector<pieceMove> moveList, int alpha)
{
    vector<pieceMove> bestMoves;
    for (int i = 0; i < (int)moveList.size(); i++)
    {
        if (moveList[i].eval > alpha)
        {
            alpha = moveList[i].eval;
            bestMoves.clear();
            bestMoves.push_back(moveList[i]);
        }
        else if (moveList[i].eval == alpha)
        {
            bestMoves.push_back(moveList[i]);
        }
    }
    int numBest = (int)bestMoves.size();

    // make first move if small number of moves, otherwise randomize
    // this prevents AI from avoiding punishing us when we play dumb moves
    int randomizeCutoff = 5;
    if (numBest <= randomizeCutoff)
    {
        return bestMoves[0];
    }
    else
    {
        srand((unsigned)time(NULL));
        int randomIndex = (int)rand() % numBest;
        return bestMoves[randomIndex];
    }
}