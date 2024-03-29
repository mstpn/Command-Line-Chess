/******************************************************************************
 File name: Queen.cpp
 ******************************************************************************/
#include "Piece.h"
#include "Board.h"

Queen::Queen(bool col):Piece(col)
{
}

Queen::~Queen()
{
}

PiecePtr Queen::clone() const
{
    PiecePtr p;

    p = new Queen(this->getColour());
    
    return p;
}

char Queen::getSymbol() const
{
    char symb;

    if(this->getColour() == WHITE)
	symb = 'Q';
    else
	symb = 'q';
    
    return symb;
}

bool Queen::canMove(const Board& b, int fromX, int fromY, int toX, int toY)
    const
{
    PiecePtr p;
    bool validMove = false,
	isVert = isVertical(fromX, fromY, toX, toY),
	isHor = isHorizontal(fromX, fromY, toX, toY),
	isDiag = isDiagonal(fromX, fromY, toX, toY);
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
		else if(isDiag)
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
	    }//end if(colour)
	}//end if(NULL)
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
	    //diagonal move
	    else if(isDiag)
	    {
		if(isPathClear(b, fromX, fromY, toX, toY))
		    validMove = true;
	    }
	}
	delete p;
    }
    
    return validMove;
}
