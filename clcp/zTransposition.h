#ifndef TRANSPOSITION_H
#define TRANSPOSITION_H

#include <semaphore.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

using namespace std;

#define TABLE_NAME "ttable"
#define TABLE_ENTRIES 100000

struct Position
{
    char fen[100]; // board state
    int eval;      // evaluation of board state
    bool used;     // whether this entry is used
};

typedef struct
{
    Position lookup[TABLE_ENTRIES]; // array of positions
} TranspositionTable;

TranspositionTable *createTable(const char *name);
TranspositionTable *getTable(const char *name);
void destroyTable(TranspositionTable *table, const char *name);
unsigned long DJBHash(char *str);
void initializeTable(TranspositionTable *table);
void addOpeningMoves(TranspositionTable *table);

#endif