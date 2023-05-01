#include "zHandler.h"

/*
    This file contains all the higher level functions for the AI turn logic.
    It also contains the functions for multi-threading.

    Multithreading was implemented using a workder pool of pthreads.
    The main thread submits tasks to the worker pool, and the worker pool executes the tasks.
 */

/*
    The go between for the game logic and the AI.
    This function is called when it is the AI's turn.
    It calls the negamax function to find the best move.
    It then returns the best move back to the game, where it is made.

    Input
        The board
        Whose turn it is
        From and to coordinates
            By reference
        The depth of the search
        The number of threads to use
    Output
        Updated from and to coordinates
 */
void aiTurn(Board &b, bool turn, int &fromX, int &fromY, int &toX, int &toY, int depth, int numThreads)
{
    pieceMove nextMove;
    rootNegamax(b, turn, depth, nextMove, -MAX_EVAL, MAX_EVAL, getTable(TABLE_NAME), numThreads);
    fromX = nextMove.fromX;
    fromY = nextMove.fromY;
    toX = nextMove.toX;
    toY = nextMove.toY;
    // cout << "Negamax eval: " << nextMove.eval << endl;

    return;
}

/*
    This function finds all the valid moves for the current player.

    Input
        The board
        Whose turn it is
        A hashmap of arrays of moves
            the key is the from move
            the array values are the possible to moves for each key move
        The number of threads to use
    Output
        Updated hashmap of arrays of moves
 */
void allValidMoves(Board &b, bool turn, map<int, vector<int>> &moves, int numThreads)
{
    int row, col, key;
    PiecePtr p;

    for (row = 0; row < MAXROWS; row++)
    {
        for (col = 0; col < MAXCOLS; col++)
        {
            p = b.getPiece(row, col);
            if (p != NULL)
            {
                if (p->getColour() == turn)
                {
                    key = encodeMove(row, col);
                    moves[key] = vector<int>();

                    // multi-threaded
                    if (numThreads > 1)
                    {
                        Task t = {
                            .b = &b,
                            .p = p,
                            .moves = &moves,
                            .key = key,
                            .row = row,
                            .col = col};

                        submitTask(t);

                        // if (moves[key].size() == 0)
                        // {
                        //     moves.erase(key);
                        // }
                    }

                    // single-threaded
                    else
                    {
                        int pieceMoves = pieceValidMoves(b, p, moves[key], row, col);
                        if (pieceMoves <= 0)
                        {
                            moves.erase(key);
                        }
                    }
                }
            }
            while (taskCount != 0)
            {
            }
        }
    }

    if (numThreads > 1)
    {
        // wait for all threads to finish
        while (taskCount != 0)
        {
        }
    }

    return;
}

/*
    This function finds all the valid moves for a single piece.

    Input
        The board
        A piece pointer for the current piece
        A hashmap of arrays of moves
            the key is the from move
            the array values are the possible to moves for each key move
        The row and column of the piece
    Output
        Updated array of moves
 */
int pieceValidMoves(Board &b, PiecePtr p, vector<int> &moves, int row, int col)
{
    int toRow,
        toCol,
        numMoves = 0;
    for (toRow = 0; toRow < MAXROWS; toRow++)
    {
        for (toCol = 0; toCol < MAXCOLS; toCol++)
        {
            if (p->canMove(b, row, col, toRow, toCol))
            {
                moves.push_back(encodeMove(toRow, toCol));
                numMoves++;
            }
        }
    }
    return numMoves;
}

/*
    Transforms a row and column into a single integer.
    Input
        The row and column
    Output
        The single integer
 */
int encodeMove(int row, int col)
{
    return row * 10 + col;
}

/*
    Transforms a single integer into a row and column.
    Input
        The single integer
        The row and column
            By reference
    Output
        Updated row and column
 */
void decodeMove(int move, int &row, int &col)
{
    row = move / 10;
    col = move % 10;
    return;
}

/*
    Creates each thread, puts them in a wait state.
    When a task is assigned to the task queue the threads are signaled to wake up.
    The first available thread will execute the task.
    Then 1 thread has access to the thread queue at a given time.
    This protection is done using semaphore locks.

    Input
        None are passed into args
    Modified
        Task queue is updated
        Task count is updated
 */
void *startThread(void *args)
{
    while (1)
    {
        Task task;

        pthread_mutex_lock(&mutexQueue);
        while (taskCount == 0)
        {
            pthread_cond_wait(&condQueue, &mutexQueue);
        }

        task = taskQueue[0];
        int i;
        for (i = 0; i < taskCount - 1; i++)
        {
            taskQueue[i] = taskQueue[i + 1];
        }
        taskCount--;
        pthread_mutex_unlock(&mutexQueue);
        executeTask(&task);
    }
}

/*
    Adds a task to the task queue.
    The task queue is protected by a mutex lock.

    Input
        The task to be added
    Modified
        Task queue is updated
        Task count is updated
 */
void submitTask(Task task)
{
    pthread_mutex_lock(&mutexQueue);
    taskQueue[taskCount] = task;
    taskCount++;
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);
}

/*
    Executes a task.
    The task is a pointer to the pieceMoves struct.
        The struct contains the board, piece, moves, key, row, and column.
        The task is to find all the valid moves for a single piece.
            If no moves are found, the key for the piece is removed from the moves hashmap.

    Input
        The task to be executed
    Modified
        The moves hashmap is updated
 */
// void executeTask(Task *task)
void executeTask(Task *task)
{
    int pieceMoves;
    Board b = *(*task).b;
    PiecePtr p = (*task).p;
    map<int, vector<int>> *moves = (*task).moves;
    int key = (*task).key;
    int row = (*task).row;
    int col = (*task).col;
    pieceMoves = pieceValidMoves(b, p, (*moves)[key], row, col);
    // pieceMoves = pieceValidMoves(*(*task).b, (*task).p,
    //                              (*(*task).moves)[(*task).key],
    //                              (*task).row,
    //                              (*task).col);

    // if (pieceMoves <= 0)
    // {
    //     int key = (*task).key;

    //     (*(*task).moves).erase((*task).key);
    // }
}