/*
    This file contains all the functions to create and update the shared memory transposition table.
    The table is a struct:
        It contaiins an array of positions that is accessed by a hash function.
            Each position contains the fen string, the evaluation, and a boolean used to determine if the entry is used.
    The table is created and destroyed by the main process in game.cpp
 */
#include "zTransposition.h"

/*
    Creates a shared memory table and returns a pointer to it.

    The size of the shared memory table is:
        ~100mb @ 1000000 entries
        ~10mb @ 100000 entries
            Our current value
        ~1mb & 10000 entries
        ~100kb @ 1000 entries

    The code from the posix shared memory tutorial was used modified to create the table.

    shm_unlink() is used to ensure that the table is removed from previous runs of the program.
        The shared memory segment may not be removed if the program is terminated abnormally,
        and we would open last run's table instead of creating a new one.
        See https://pubs.opengroup.org/onlinepubs/009696699/functions/shm_unlink.html for more info.

    Input:
        The name of the table
    Output:
        A TranspositionTable pointer to the table

 */
TranspositionTable *createTable(const char *name)
{
    shm_unlink(name); // Ensure old table removed in case of abnormal termination
    TranspositionTable *table;
    int fd;
    const int SHARED_MEMORY_SIZE = sizeof(TranspositionTable);

    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SHARED_MEMORY_SIZE);
    table = (TranspositionTable *)mmap(0, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    initializeTable(table);

    return table;
}

/*
    Destroys a shared memory table.

    Input:
        The table to destroy
        The name of the table
    Output:
        None
 */
void destroyTable(TranspositionTable *table, const char *name)
{
    shm_unlink(name);
    munmap(table, sizeof(TranspositionTable));
}

/*
    Gets a pointer to a shared memory table.

    Input:
        The name of the table
    Output:
        A TranspositionTable pointer to the table
 */
TranspositionTable *getTable(const char *name)
{
    TranspositionTable *table;
    int fd;
    const int SHARED_MEMORY_SIZE = sizeof(TranspositionTable);

    fd = shm_open(name, O_RDWR, 0666);
    table = (TranspositionTable *)mmap(0, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    return table;
}

/*
    This is the implementation of the DJB2 hash function, created by Dan Bernstein.
    Instead of writing our own hash function, we use this one because it is fast and has been tested.
    https://theartincode.stanis.me/008-djb2/

    Input
        A string to hash (fen for us)
    Output
        An unsigned long hash value
 */
unsigned long DJBHash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

/*
    Initialize all of the used booleans to false to prevent incorrect hash table conflicts
    Input:
        Transposition table
    Output:
        Updated table
 */
void initializeTable(TranspositionTable *table)
{
    for (int i = 0; i < TABLE_ENTRIES; i++)
    {
        table->lookup[i].used = false;
    }
    addOpeningMoves(table);
}

/*
    Add any opening moves you want to the table here
    I have added 1e4 as the safe opening move for white and 1d4 d5 as the safe opening move for black.

    https://www.dailychess.com/chess/chess-fen-viewer.php is a nice tool to get the fen string for a position
        remember to truncate the fen after the turn character (b or w)

    Input:
        Transposition table
    Output:
        Updated table
 */
void addOpeningMoves(TranspositionTable *table)
{
    char fen[100];
    size_t hash;
    size_t key;

    // WHITE MOVES
    // 1. e4
    strcpy(fen, "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b");
    hash = DJBHash(fen);
    key = hash % TABLE_ENTRIES;
    strcpy(table->lookup[key].fen, fen);
    table->lookup[key].eval = -1000;
    table->lookup[key].used = true;

    // BLACK MOVES
    // 1 d4 d5
    strcpy(fen, "rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w");
    hash = DJBHash(fen);
    key = hash % TABLE_ENTRIES;
    strcpy(table->lookup[key].fen, fen);
    table->lookup[key].eval = -1000;
    table->lookup[key].used = true;

    // Uncomment for black to play the Queen's Gambit
    // // 1 e4 d5
    // strcpy(fen, "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w");
    // hash = DJBHash(fen);
    // key = hash % TABLE_ENTRIES;
    // strcpy(table->lookup[key].fen, fen);
    // table->lookup[key].eval = -1000;
    // table->lookup[key].used = true;
}