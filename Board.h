/******************************************************************************
 Name: Matthew Stepan
 File name: Board.h
 ******************************************************************************/
#ifndef BOARD_H
#define BOARD_H

class Board;
#include "Piece.h"
#include <iostream>
using namespace std;

#define MAXROWS 8
#define MAXCOLS 8

typedef Piece* PiecePtr;

/*******************************************************************************

 The "Board" class: represents a m x n tiled board for use with table top games
                    (Chess, checkers, etc).
  
PUBLIC METHOD SPECIFICATION:

Board()
	Default constructor

Board(const Board& other)
	Copy constructor

~Board()
	Destructor

PiecePtr Board::getPiece(int x, int y) const
	Return a pointer to a copy of the piece at a given location if found,
	else NULL
		Used for testing only in this phase

bool isOccupied(int x, int y) const
	Takes a coordinate and returns whether or not this location is already
	occupied.

bool move(int fromX, int fromY, int toX, int toY)
	Move a piece at a given position to a new position

bool place(const PiecePtr& p, int x, int y)
	Place a piece down at a given position

bool remove(int x, int y);
	Remove a piece at a given position
	
void write(ostream& out) const
	Print the board to a given output stream

bool kingCapture(bool& colour) const
	Returns if the game has ended via king capture, and  the colour of the 
	side that as won the game.

Board& operator=(const Board& other)
	Overloaded symbolic "assignment" operator
******************************************************************************/
class Board
{
public:
/******************************************************************************
Name: 
	Board
Purpose:
    Default constructor for the Board class, initializes an empty board.
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    N/A
 ******************************************************************************/  
    Board();

/******************************************************************************
Name: 
	Board
Purpose:
    Copy constructor for the Board class, copies the pieces and their layout
    from the passed Board into a newly initialized Board.
Details:
    N/A
Input:
    A Board object to be copied
        Passed by reference (constant)
Output:
    The unmodified Board that was copied
Return:
    N/A
 ******************************************************************************/
    Board(const Board& other);

/******************************************************************************
Name: 
	~Board
Purpose:
    Destructor for the Board class, clears the board and deallocates the memory
    of any pieces that are on it
Details:
    Only pieces that are currently placed on the board will have their memory
	deallocated.
		All other pieces not placed on the board will need to be 
		deallocated by the client program.
    Additionally, the destructor exports the state of the Board to an external
    text file before it is cleared.
        This file contains the staus of the Board in the format:
            The piece character, a single space, the row coordinate, 
            a single space and the column coordinate.
                e.g.
                    P 1 2
                    P 4 1
Input:
    N/A
Output:
    N/A
Return:
    N/A
 ******************************************************************************/
    ~Board();

/******************************************************************************
Name: 
	getPiece
Purpose:
    Takes a coordinate and returns a pointer to the Piece at that location.
Details:
    If no Piece is found at the location, then NULL is returned
    If a Piece is found at the location, then a pointer to a COPY of that Piece
    is returned
Input:
    An integer representing the x coordinate of a location
        Passed by value
    An integer representing the y coordinate of a location
        Passed by value
Output:
    N/A
Return:
    A pointer to a Piece if one was found at the specified location, else NULL
******************************************************************************/
    PiecePtr getPiece (int x, int y) const;


/******************************************************************************
Name: 
	isOccupied
Purpose:
    Takes a coordinate and returns whether or not this location is already
    occupied.
Details:
Input:
    An integer representing the x coordinate of a location
        Passed by value
    An integer representing the y coordinate of a location
        Passed by value
Output:
    N/A
Return:
    A boolean indicating:
	true  -> a piece was found at the specificed location
	false -> a piece was not found a the specified location
******************************************************************************/
    bool isOccupied(int x, int y) const;
    
/******************************************************************************
Name: 
    move
Purpose:
    Move a piece from one square to another (empty) square.
Details:
    Conditions for a valid move:
	    	Pieces must be within the bounds of the board
		A piece must exist on the "from" square in order to be moved
		A piece must not exist on the "to" square in order to move there
		A piece cannot move to the square that it currently occupies        
		A piece must be of the same colour as the player attempting
		to move it
Input:
	A boolean for the colour of the piece to be moved
		Passed by value
    	An integer for the x coordinate of the from square
		Passed by value
	An integer for the y coordinate of the from square
		Passed by value
	An integer for the x coordinate of the to square
		Passed by value
	An integer for the y coordinate of the to square
		Passed by value	
Output:
    N/A
Return:
    A boolean indicating:
		true  -> There is a piece at the from location and no piece at 
			 the to location
		false -> if true conditions not met
 *****************************************************************************/
    bool move (bool colour, int fromX, int fromY, int toX, int toY);

/******************************************************************************
Name: 
	place
Purpose:
    Places a piece onto an empty location on the board
Details:
    If a Piece already exists at the specified location, then the place does
    not occur, and a false boolean is returned.
Input:
    A pointer to a Piece that will be attempted to be placed
        Passed by reference (constant)
    An integer representing the x coordinate of the location to place the Piece
        Passed by value
    An integer representing the y coordinate of the location to place the Piece
        Passed by value
Output:
    A pointer to the unmodified Piece that was attepted to be placed
Return:
    A boolean indicating:
        true  -> The given location is empty
        false -> The true condition is not met
 ******************************************************************************/
    bool place (const PiecePtr& p, int x, int y);

/******************************************************************************
Name: 
	remove
Purpose:
    Removes a Piece from a specified location onthe board and deallocates its
    memory.
Details:
    A remove is only possible if there exists a Piece on the specified piece
        A false boolean is returned by the function if this is not the case
Input:
    An integer representing the x coordinate of the Piece to remove
        Passed by value
    An integer representing the y coordinate of the Piece to remove
        Passed by value
Output:
    N/A
Return:
    A boolean indicating:
        true  -> There exists a Piece at the specified location
        false -> The true condition was not met
 ******************************************************************************/
    bool remove (int x, int y);

/******************************************************************************
Name: 
	write
Purpose:
    Write the current state of the Board to an output stream.
Details:
    The output will be in the following format:

        0   1   2   3   4   5   6   7   
      +---+---+---+---+---+---+---+---+
    0 |   |   |   |   |   |   |   |   |
      +---+---+---+---+---+---+---+---+
    1 |   | P |   |   |   |   |   |   |
      +---+---+---+---+---+---+---+---+
    2 |   |   |   |   |   |   |   |   |
      +---+---+---+---+---+---+---+---+
    3 |   |   |   | P |   |   |   |   |
      +---+---+---+---+---+---+---+---+
    4 |   |   |   |   |   |   |   |   |
      +---+---+---+---+---+---+---+---+
    5 |   |   |   |   |   | P |   |   |
      +---+---+---+---+---+---+---+---+
    6 |   |   |   |   |   |   |   |   |
      +---+---+---+---+---+---+---+---+
    7 |   |   |   |   |   |   |   |   |
      +---+---+---+---+---+---+---+---+

        Where 'P' indicates a Piece location

Input:
    An output stream to write the Board to
        Passed by reference
Output:
    An update output stream that contains the written Board
Return:
    N/A
 ******************************************************************************/ 
    void write (ostream& out) const;

/******************************************************************************
Name: 
	kingCapture
Purpose:
 	Returns if the game has ended via king capture, and  the colour of the 
	side that as won the game.
Details:
	N/A
Input:
	A boolean for the colour of the side that won, if applicable
		Passed by reference
Output:
    	A boolean true if the game is over via king capture, else false
Return:
    	A boolean with the winning side, if king caputre took place
 ******************************************************************************/
    bool kingCapture(bool& colour) const;

    
/******************************************************************************
Name: 
	operator=
Purpose:
    Overload the assignment operator for the Board class.
Details:
    If the Board that will be copied is the same as the board being copied
    too, then no assignment takes place.
    Else, the Board being copied to is cleared, then a copy of the the Pieces
    and their locations are assigned to it.
Input:
    A Board object that will be assigned to the invoking Board
        Passed by reference (constant)
Output:
    The unmodified Board object passed as input
Return:
    A Board object
 ******************************************************************************/
    Board& operator= (const Board& other);

private:
    PiecePtr grid[MAXROWS][MAXCOLS];

    void initBoard();
    void clearBoard();
    void copyBoard(const Board& other);
    bool canMove (int fromX, int fromY, int toX, int toY) const;
    PiecePtr getSquare(int x, int y) const;
    void writeLine(ostream& out) const;
};

ostream& operator<< (ostream& out, const Board& b);

#endif
