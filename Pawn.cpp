/******************************************************************************
 Name: Matthew Stepan
 File name: Pawn.cpp
 ******************************************************************************/
#include "Piece.h"
#include "Board.h"

Pawn::Pawn(bool col):Piece(col)
{
    hasMoved = false;
}

Pawn::~Pawn()
{
}

void Pawn::notifyMoved()
{
    hasMoved = true;
}

PiecePtr Pawn::clone() const
{
    PiecePtr p;

    p = new Pawn(this->getColour());
    if(hasMoved)
	p->notifyMoved();
    
    return p;
}

char Pawn::getSymbol() const
{
    char symb;

    if(this->getColour() == WHITE)
	symb = 'P';
    else
	symb = 'p';
    
    return symb;
}

bool Pawn::canMove(const Board& b, int fromX, int fromY, int toX, int toY)
    const
{
    PiecePtr p;
    bool validMove = false,
	isVert = isVertical(fromX, fromY, toX, toY),
	isDiag = isDiagonal(fromX, fromY, toX, toY);
    int vert = vertDistance(fromX, toX),
	hor = horizDistance(fromY, toY);

    if(fromX >= 0 && fromX < MAXROWS &&
       fromY >= 0 && fromY < MAXCOLS &&
       toX >= 0 && toX < MAXROWS &&
       toY >= 0 && toY < MAXCOLS &&
       (fromX != toX || fromY != toY))
    {
	//capture attempt, allow diagonal movement
	if(isDiag)
	{
	    if(isForward(fromX, toX) && (abs(vert) == 1) && (abs(hor) == 1))
		{
		    p = b.getPiece(toX, toY);
		    if(p != NULL)
		    {
			if(p->getColour() != this->getColour())
			    validMove = true;
		    }
		    delete p;
		}
	}
	//normal move
	else if(isVert)
	{
	    if(hasMoved && (abs(vert) == 1))
	    {
		if(isPathClear(b, fromX, fromY, toX, toY))
		{
		    if(isForward(fromX, toX))
		    {
			validMove = true;
		    }
		}
	    }
	    else if(!hasMoved && ((abs(vert) == 1) || (abs(vert) == 2)))
	    {
	    	if(isPathClear(b, fromX, fromY, toX, toY))
	    	{
		    if(isForward(fromX, toX))
		    {
			validMove = true;
		    }
		}
	    }
	}
    }
    
    return validMove;
}
