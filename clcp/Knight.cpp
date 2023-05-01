/******************************************************************************
 File name: Knight.cpp
 ******************************************************************************/
#include "Piece.h"
#include "Board.h"

Knight::Knight(bool col):Piece(col)
{
}

Knight::~Knight()
{
}

PiecePtr Knight::clone() const
{
    PiecePtr p;

    p = new Knight(this->getColour());
    
    return p;
}

char Knight::getSymbol() const
{
    char symb;

    if(this->getColour() == WHITE)
	symb = 'N';
    else
	symb = 'n';
    
    return symb;
}

bool Knight::canMove(const Board& b, int fromX, int fromY, int toX, int toY)
    const
{
    PiecePtr p;
    bool validMove = false;
    int vert = vertDistance(fromX, toX),
	hor = horizDistance(fromY, toY);

    if(fromX >= 0 && fromX < MAXROWS &&
       fromY >= 0 && fromY < MAXCOLS &&
       toX >= 0 && toX < MAXROWS &&
       toY >= 0 && toY < MAXCOLS &&
       (fromX != toX || fromY != toY))
    {
	p = b.getPiece(toX, toY);
	
	//up 2 left 1
	if(vert == -2 && hor == -1)
	{
	    //normal move
	    if(p == NULL)
		validMove = true;
	    //capture
	    else
	    {
		if(p->getColour() != this->getColour())
		{
		    validMove = true;
		}
	    }
	}
	//up 2 right 1
	else if(vert == -2 && hor == 1)
	{
	    //normal move
	    if(p == NULL)
		validMove = true;
	    //capture
	    else
	    {
		if(p->getColour() != this->getColour())
		{
		    validMove = true;
		}
	    }
	}
	//up 1 right 2
	else if(vert == -1 && hor == 2)
	{
	    //normal move
	    if(p == NULL)
		validMove = true;
	    //capture
	    else
	    {
		if(p->getColour() != this->getColour())
		{
		    validMove = true;
		}
	    }
	}
	//down 1 right 2
	else if(vert == 1 && hor == 2)
	{
	    //normal move
	    if(p == NULL)
		validMove = true;
	    //capture
	    else
	    {
		if(p->getColour() != this->getColour())
		{
		    validMove = true;
		}
	    }
	}
	//down 2 right 1
	else if(vert == 2 && hor == 1)
	{
	    //normal move
	    if(p == NULL)
		validMove = true;
	    //capture
	    else
	    {
		if(p->getColour() != this->getColour())
		{
		    validMove = true;
		}
	    }
	}
	//down 2 left 1
	else if(vert == 2 && hor == -1)
	{
	    //normal move
	    if(p == NULL)
		validMove = true;
	    //capture
	    else
	    {
		if(p->getColour() != this->getColour())
		{
		    validMove = true;
		}
	    }
	}
	//down 1 left 2
	else if(vert == 1 && hor == -2)
	{
	    //normal move
	    if(p == NULL)
		validMove = true;
	    //capture
	    else
	    {
		if(p->getColour() != this->getColour())
		{
		    validMove = true;
		}
	    }
	}
	//up 1 left 2
	else if(vert == -1 && hor == -2)
	{
	    //normal move
	    if(p == NULL)
		validMove = true;
	    //capture
	    else
	    {
		if(p->getColour() != this->getColour())
		{
		    validMove = true;
		}
	    }
	}
	delete p;
    }
    
    return validMove;
}
