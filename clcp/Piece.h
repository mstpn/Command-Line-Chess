/******************************************************************************
 File name: Piece.h
******************************************************************************/
#ifndef PIECE_H
#define PIECE_H

class Piece;
#include "Board.h"
#include <iostream>
#include <cmath>
using namespace std;

#define WHITE true
#define BLACK false

typedef Piece* PiecePtr;

/*******************************************************************************

 The "Piece" class: represents a Piece that is placed upon a Board object.

PUBLIC METHOD SPECIFICATION:

Piece (bool col)
	Constructor that creates a Piece with a specified colour

virtual ~Piece()
   	Destructor for a Piece

bool getColour() const
	Return the colour of a Piece

virtual void notifyMoved()
	Return whether or not the Piece has moved (for applicable Pieces)
    
virtual PiecePtr clone() const = 0
	Create a duplicate of the invoking piece and return a pointer to that 
	copy

virtual char getSymbol() const = 0
	Get the symbol representing that Piece

virtual bool canMove(const Board& b, int fromX, int fromY, int toX, int toY)
   const = 0
	Determine whether the proposed move is valid for the given Piece.	


******************************************************************************/
class Piece
{
public:
/******************************************************************************
Name:
        Piece
Purpose:
	Constructor that creates a Piece with a specified colour
Details:
	Colours
		true == white
		false == black
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/
    Piece (bool col);
    
/******************************************************************************
Name:
       ~Piece
Purpose:
	Destructor for a Piece
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/
    virtual ~Piece();

/******************************************************************************
Name:
       getColour
Purpose:
	Return the colour of a Piece
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    	A boolean with the colour of the Piece
		true == white
		false == black
******************************************************************************/    
    bool getColour() const;

/******************************************************************************
Name:
       notifyMoved
Purpose:
	Return whether or not the Piece has moved (for applicable pieces)
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    	A boolean indicating true if the piece has moved, else false
******************************************************************************/        
    virtual void notifyMoved();

/******************************************************************************
Name:
        clone
Purpose:
    	Create a duplicate of the invoking piece and return a pointer to that
	copy.
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    	A pointer to the copy of the Piece that was cloned
******************************************************************************/            
    virtual PiecePtr clone() const = 0;

/******************************************************************************
Name:
        getSymbol
Purpose:
    	Get the symbol representing the invoking piece
Details:
    	Lower case symbols returned for black pieces, upper case symbols
	returned for white pieces.
Input:
    N/A
Output:
    N/A
Return:
	A character with the symbol for the piece.
******************************************************************************/               
    virtual char getSymbol() const = 0;

/******************************************************************************
Name:
        canMove
Purpose:
    	Determine whether the propsed move is valid for the given Piece.
Details:
	Each Piece subclass will have its own definition of what constitutes
	a valid move.
Input:
    	A Board object that holds all possible pieces
		Passed by Reference (constant)
	An integer for the x coordinate of the piece to move
		Passed by value
	An integer for the y coordinate of the piece to move
		Passed by value
	An integer for the x coordinate of the proposed move location
		Passed by value
	An integer for the y coordinate of the proposed move location
		Passed by value
Output:
    	A boolean indicating whether the move is valid
		true == valid move
		false == invalid move
Return:
	A character with the symbol for the piece.
******************************************************************************/                   
    virtual bool canMove(const Board& b, int fromX, int fromY, int toX, int toY)
	const = 0;
    
private:
    bool colour;

protected:
    bool isVertical (int fromX, int fromY, int toX, int toY) const;
    bool isHorizontal (int fromX, int fromY, int toX, int toY) const;
    bool isDiagonal (int fromX, int fromY, int toX, int toY) const;
    bool isForward (int fromX, int toX) const;
    int vertDistance (int fromX, int toX) const;
    int horizDistance (int fromY, int toY) const;
    bool isPathClear (const Board& b, int fromX, int fromY, int toX, int toY)
	const;
};








class King : public Piece
{
public:
/******************************************************************************
Name:
        King
Purpose:
	Constructor that creates a King with a specified colour
Details:
	Colours
		true == white
		false == black
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/
    King(bool col);

/******************************************************************************
Name:
       ~King
Purpose:
	Destructor for a King
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/
    virtual ~King();
    
/******************************************************************************
Name:
        clone
Purpose:
    	Create a duplicate of the invoking piece and return a pointer to that
	copy.
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    	A pointer to the copy of the Piece that was cloned
******************************************************************************/    
    virtual PiecePtr clone() const;

/******************************************************************************
Name:
        getSymbol
Purpose:
    	Get the symbol representing the invoking piece
Details:
    	'K' for white king, 'k' for black king
Input:
    N/A
Output:
    N/A
Return:
	A character with the symbol for the piece.
******************************************************************************/    
    virtual char getSymbol() const;

/******************************************************************************
Name:
        canMove
Purpose:
    	Determine whether the propsed move is valid for the given Piece.
Details:
        A king can move 1 square in any direction (horizontal, vertical,
        diagonal)
	To determine if a king may capture a piece
		There must exist a piece of opposing colour at the destination
		square
		The piece must be exaclty one square in any direction of the 
		king
		The path from the king square to the destination square must 
		be clear
			This must be checked for all degrees of king movement
				+horiz
				-horiz
				+vert
				-vert
				+horiz & +vert
				+horiz & -vert
				-horiz & +vert
				-horiz & -vert	   	
	The king is NOT subject to any tests as to whether or not it is 
	moving into check
		The king may make any legal directional move of its piece
		irregardless of chess rules
Input:
    	A Board object that holds all possible pieces
		Passed by Reference (constant)
	An integer for the x coordinate of the piece to move
		Passed by value
	An integer for the y coordinate of the piece to move
		Passed by value
	An integer for the x coordinate of the proposed move location
		Passed by value
	An integer for the y coordinate of the proposed move location
		Passed by value
Output:
    	A boolean indicating whether the move is valid
		true == valid move
		false == invalid move
Return:
	A character with the symbol for the piece.
******************************************************************************/    
    virtual bool canMove(const Board& b, int fromX, int fromY, int toX, int toY)
	const;
};









class Queen : public Piece
{
public:
/******************************************************************************
Name:
        Queen
Purpose:
	Constructor that creates a Queen with a specified colour
Details:
	Colours
		true == white
		false == black
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/
    Queen(bool col);
/******************************************************************************
Name:
       ~Queen
Purpose:
	Destructor for a Queen
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/    
    virtual ~Queen();
    
/******************************************************************************
Name:
        clone
Purpose:
    	Create a duplicate of the invoking piece and return a pointer to that
	copy.
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    	A pointer to the copy of the Piece that was cloned
******************************************************************************/    
    virtual PiecePtr clone() const;

/******************************************************************************
Name:
        getSymbol
Purpose:
    	Get the symbol representing the invoking piece
Details:
    	'Q' for white queen, 'q' for black queen.
Input:
    N/A
Output:
    N/A
Return:
	A character with the symbol for the piece.
******************************************************************************/    
    virtual char getSymbol() const;

/******************************************************************************
Name:
        canMove
Purpose:
    	Determine whether the propsed move is valid for the given Piece.
Details:
        A queen can move multiple squares in any direction.
	To determine if a queen may capture a piece
		There must exist a piece of opposing colour at the destination
		square
		The path from the queen square to the destination square must 
		be clear
			This must be checked for all degrees of queen movement
				+horiz
				-horiz
				+vert
				-vert
				+horiz & +vert
				+horiz & -vert
				-horiz & +vert
				-horiz & -vert	   	
Input:
    A Board object that holds all possible pieces
		Passed by Reference (constant)
	An integer for the x coordinate of the piece to move
		Passed by value
	An integer for the y coordinate of the piece to move
		Passed by value
	An integer for the x coordinate of the proposed move location
		Passed by value
	An integer for the y coordinate of the proposed move location
		Passed by value
Output:
    	A boolean indicating whether the move is valid
		true == valid move
		false == invalid move
Return:
	A character with the symbol for the piece.
******************************************************************************/    
    virtual bool canMove(const Board& b, int fromX, int fromY, int toX, int toY)
	const;
};









class Bishop : public Piece
{
public:
/******************************************************************************
Name:
        Bishop
Purpose:
	Constructor that creates a Bishop with a specified colour
Details:
	Colours
		true == white
		false == black
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/
    Bishop(bool col);

/******************************************************************************
Name:
       ~Bishop
Purpose:
	Destructor for a Bishop
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/    
    virtual ~Bishop();
    
/******************************************************************************
Name:
        clone
Purpose:
    	Create a duplicate of the invoking piece and return a pointer to that
	copy.
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    	A pointer to the copy of the Piece that was cloned
******************************************************************************/    
    virtual PiecePtr clone() const;

/******************************************************************************
Name:
        getSymbol
Purpose:
    	Get the symbol representing the invoking piece
Details:
    	'B' for white bishop, 'b' for black bishop
Input:
    N/A
Output:
    N/A
Return:
	A character with the symbol for the piece.
******************************************************************************/    
    virtual char getSymbol() const;

/******************************************************************************
Name:
        canMove
Purpose:
    	Determine whether the propsed move is valid for the given Piece.
Details:
        A bishop can move multiple squares diagonally
	To determine if a bishop may capture a piece
		There must exist a piece of opposing colour at the destination
		square
		The path from the bishop square to the destination square must 
		be clear
			This must be checked for all degrees of bishop movement
				+horiz & +vert
				+horiz & -vert
				-horiz & +vert
				-horiz & -vert				
Input:
    	A Board object that holds all possible pieces
		Passed by Reference (constant)
	An integer for the x coordinate of the piece to move
		Passed by value
	An integer for the y coordinate of the piece to move
		Passed by value
	An integer for the x coordinate of the proposed move location
		Passed by value
	An integer for the y coordinate of the proposed move location
		Passed by value
Output:
    	A boolean indicating whether the move is valid
		true == valid move
		false == invalid move
Return:
	A character with the symbol for the piece.
******************************************************************************/    
    virtual bool canMove(const Board& b, int fromX, int fromY, int toX, int toY)
	const;
};









class Knight : public Piece
{
public:
/******************************************************************************
Name:
        Knight
Purpose:
	Constructor that creates a Knight with a specified colour
Details:
	Colours
		true == white
		false == black
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/
    Knight(bool col);

/******************************************************************************
Name:
       ~Knight
Purpose:
	Destructor for a Knight
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/    
    virtual ~Knight();
    
/******************************************************************************
Name:
        clone
Purpose:
    	Create a duplicate of the invoking piece and return a pointer to that
	copy.
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    	A pointer to the copy of the Piece that was cloned
******************************************************************************/    
    virtual PiecePtr clone() const;

/******************************************************************************
Name:
        getSymbol
Purpose:
    	Get the symbol representing the invoking piece
Details:
    	'N' for white knight, 'n' for black knight
Input:
    N/A
Output:
    N/A
Return:
	A character with the symbol for the piece.
******************************************************************************/    
    virtual char getSymbol() const;

/******************************************************************************
Name:
        canMove
Purpose:
    	Determine whether the propsed move is valid for the given Piece.
Details:
        A knight can move two squares horizontally then one square
        vertically. OR it may move two squares vertically and then one 
        square horizonatally.
        A knight may "jump" over other pieces en route to its destination
        square.
		Don't need to check for pieces that are in its movement path
	A knight may capture any piece that is of opposing colour at its
	destination square.
Input:
    	A Board object that holds all possible pieces
		Passed by Reference (constant)
	An integer for the x coordinate of the piece to move
		Passed by value
	An integer for the y coordinate of the piece to move
		Passed by value
	An integer for the x coordinate of the proposed move location
		Passed by value
	An integer for the y coordinate of the proposed move location
		Passed by value
Output:
    	A boolean indicating whether the move is valid
		true == valid move
		false == invalid move
Return:
	A character with the symbol for the piece.
******************************************************************************/    
    virtual bool canMove(const Board& b, int fromX, int fromY, int toX, int toY)
	const;
};









class Rook : public Piece
{
public:
/******************************************************************************
Name:
        Rook
Purpose:
	Constructor that creates a Rook with a specified colour
Details:
	Colours
		true == white
		false == black
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/
    Rook(bool col);

/******************************************************************************
Name:
       ~Rook
Purpose:
	Destructor for a Rook
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/
    virtual ~Rook();
    
/******************************************************************************
Name:
        clone
Purpose:
    	Create a duplicate of the invoking piece and return a pointer to that
	copy.
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    	A pointer to the copy of the Piece that was cloned
******************************************************************************/    
    virtual PiecePtr clone() const;

/******************************************************************************
Name:
        getSymbol
Purpose:
    	Get the symbol representing the invoking piece
Details:
    	'R' for white rook, 'r' for black rook
Input:
    N/A
Output:
    N/A
Return:
	A character with the symbol for the piece.
******************************************************************************/
    virtual char getSymbol() const;

/******************************************************************************
Name:
        canMove
Purpose:
    	Determine whether the propsed move is valid for the given Piece.
Details:
        A rook can move multiple squares horizonally, or move multiple
        squares vertically.
	To determine if a rook may capture a piece
		There must exist a piece of opposing colour at the destination
		square
		The path from the rook square to the destination square must 
		be clear
			This must be checked for all degrees of rook movement
				+horiz
				-horiz
				+vert
				-vert
Input:
    	A Board object that holds all possible pieces
		Passed by Reference (constant)
	An integer for the x coordinate of the piece to move
		Passed by value
	An integer for the y coordinate of the piece to move
		Passed by value
	An integer for the x coordinate of the proposed move location
		Passed by value
	An integer for the y coordinate of the proposed move location
		Passed by value
Output:
    	A boolean indicating whether the move is valid
		true == valid move
		false == invalid move
Return:
	A character with the symbol for the piece.
******************************************************************************/    
    virtual bool canMove(const Board& b, int fromX, int fromY, int toX, int toY)
	const;
};








class Pawn : public Piece
{
public:
/******************************************************************************
Name:
        Pawn
Purpose:
	Constructor that creates a Pawn with a specified colour
Details:
	Colours
		true == white
		false == black
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/
    Pawn(bool col);

/******************************************************************************
Name:
       ~Pawn
Purpose:
	Destructor for a Pawn
Details:
    N/A
Input:
    N/A
Output:
    N/A
Return:
    N/A
******************************************************************************/    
    virtual ~Pawn();

/******************************************************************************
Name:
       notifyMoved
Purpose:
	Return whether or not the Pawn has moved.
Details:
    The pawn may move 2 squares if it has not moved before.
Input:
    N/A
Output:
    N/A
Return:
    	A boolean indicating true if the piece has moved, else false
******************************************************************************/
    virtual void notifyMoved();

/******************************************************************************
Name:
        clone
Purpose:
    	Create a duplicate of the invoking piece and return a pointer to that
	copy.
Details:
        The pawn needs to have a copy of the "hasMoved" value assigned to
        the new object.
Input:
    N/A
Output:
    N/A
Return:
    	A pointer to the copy of the Piece that was cloned
******************************************************************************/
    virtual PiecePtr clone() const;

/******************************************************************************
Name:
        getSymbol
Purpose:
    	Get the symbol representing the invoking piece
Details:
    	'P' for white pawn, 'p' for black pawn
Input:
    N/A
Output:
    N/A
Return:
	A character with the symbol for the piece.
******************************************************************************/    
    virtual char getSymbol() const;

/******************************************************************************
Name:
        canMove
Purpose:
    	Determine whether the propsed move is valid for the given Piece.
Details:
        A pawn may move one square "forward" vertically if it has previously
        moved, or else may move two squares "forward" vertically if it has 
        not previously moved.
        A pawn may move one square forward diagonally if doing so captures
        an opposing piece.
            "Forward"
                White pawns may move from the bottow rows towards the top
                    row 6 -> row 0
                Black pawns may move from the top rows towards the bottom
                    row 1 -> row 7
Input:              
    	A Board object that holds all possible pieces
		Passed by Reference (constant)
	An integer for the x coordinate of the piece to move
		Passed by value
	An integer for the y coordinate of the piece to move
		Passed by value
	An integer for the x coordinate of the proposed move location
		Passed by value
	An integer for the y coordinate of the proposed move location
		Passed by value
Output:
    	A boolean indicating whether the move is valid
		true == valid move
		false == invalid move
Return:
	A character with the symbol for the piece.
******************************************************************************/    
    virtual bool canMove(const Board& b, int fromX, int fromY, int toX, int toY)
	const;
private:
    bool hasMoved;
};



#endif
