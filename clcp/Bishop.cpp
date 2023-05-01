/******************************************************************************
 File name: Bishop.cpp
 ******************************************************************************/
#include "Piece.h"
#include "Board.h"

Bishop::Bishop(bool col):Piece(col)
{
}

Bishop::~Bishop()
{
}

PiecePtr Bishop::clone() const
{
    PiecePtr p;

    p = new Bishop(this->getColour());
    
    return p;
}

char Bishop::getSymbol() const
{
    char symb;

    if(this->getColour() == WHITE)
	symb = 'B';
    else
	symb = 'b';
    
    return symb;
}

bool Bishop::canMove(const Board& b, int fromX, int fromY, int toX, int toY)
    const
{
    PiecePtr p;
    bool validMove = false,
	isDiag = isDiagonal(fromX, fromY, toX, toY);
    int vert = vertDistance(fromX, toX),
	hor = horizDistance(fromY, toY);

    if(fromX >= 0 && fromX < MAXROWS &&
       fromY >= 0 && fromY < MAXCOLS &&
       toX >= 0 && toX < MAXROWS &&
       toY >= 0 && toY < MAXCOLS &&
       (fromX != toX || fromY != toY))
    {
	if(isDiag)
	{
	    //capture attempt
	    p = b.getPiece(toX, toY);
	    if(p != NULL)
	    {
		if(p->getColour() != this->getColour())
		{
		    //up+right
		    if(hor >= 1 && vert <= -1)
		    {
			if(isPathClear(b, fromX, fromY, toX + 1, toY - 1))
			    validMove = true;
		    }
		    //up+left
		    else if(hor <= -1 && vert <= -1)
		    {
			if(isPathClear(b, fromX, fromY, toX + 1, toY + 1))
			    validMove = true;
		    }
		    //down+right
		    else if(hor >= 1 && vert >= 1)
		    {
			if(isPathClear(b, fromX, fromY, toX - 1, toY - 1))
			    validMove = true;
		    }
		    //down+left
		    else if(hor <= -1 && vert >= 1)
		    {
			if(isPathClear(b, fromX, fromY, toX - 1, toY + 1))
			    validMove = true;
		    }
		}
	    }
	    //normal move
	    else
	    {
		if(isPathClear(b, fromX, fromY, toX, toY))
		    validMove = true;
	    }
	    delete p;
	}
    }
    
    return validMove;
}
