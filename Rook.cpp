/******************************************************************************
 Name: Matthew Stepan
 File name: Rook.cpp
 ******************************************************************************/
#include "Piece.h"
#include "Board.h"

Rook::Rook(bool col):Piece(col)
{
}

Rook::~Rook()
{
}

PiecePtr Rook::clone() const
{
    PiecePtr p;

    p = new Rook(this->getColour());
    
    return p;
}

char Rook::getSymbol() const
{
    char symb;

    if(this->getColour() == WHITE)
	symb = 'R';
    else
	symb = 'r';
    
    return symb;
}

bool Rook::canMove(const Board& b, int fromX, int fromY, int toX, int toY)
    const
{
    PiecePtr p;
    bool validMove = false,
	isVert = isVertical(fromX, fromY, toX, toY),
	isHor = isHorizontal(fromX, fromY, toX, toY);
    int vert = vertDistance(fromX, toX),
	hor = horizDistance(fromY, toY);

    if(fromX >= 0 && fromX < MAXROWS &&
       fromY >= 0 && fromY < MAXCOLS &&
       toX >= 0 && toX < MAXROWS &&
       toY >= 0 && toY < MAXCOLS &&
       (fromX != toX || fromY != toY))
    {
	//capture attempt
	p = b.getPiece(toX, toY);
	if(p != NULL)
	{
	    if(p->getColour() != this->getColour())
	    {
		//horizontal capture
		if(isHor)
		{
		    //right
		    if(hor <= -1)
		    {
			if(isPathClear(b, fromX, fromY, toX, toY + 1))
			    validMove = true;
		    }
		    //left
		    else if(hor >= 1)
		    {
			if(isPathClear(b, fromX, fromY, toX, toY - 1))
			    validMove = true;
		    }
		}
		//vertical capture
		else if(isVert)
		{
		    //up
		    if(vert <= -1)
		    {
			if(isPathClear(b, fromX, fromY, toX + 1, toY))
			    validMove = true;
		    }
		    //down
		    else if(vert >= 1)
		    {
			if(isPathClear(b, fromX, fromY, toX - 1, toY))
			    validMove = true;
		    }
		}
	    }
	}
	//normal move
	else
	{
	    //horizontal move
	    if(isHor)
	    {
		if(isPathClear(b, fromX, fromY, toX, toY))
		    validMove = true;
	    }
	    //vertical move
	    else if(isVert)
	    {
		if(isPathClear(b, fromX, fromY, toX, toY))
		    validMove = true;
	    }
	}
	delete p;
    }
    
    return validMove;
}
