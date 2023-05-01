/******************************************************************************
 File name: Piece.cpp
 ******************************************************************************/
#include "Piece.h"
#include "Board.h"

Piece::Piece(bool col)
{
    colour = col;
}

Piece::~Piece()
{
}

//--------------------------PIECE PUBLIC FUNCTIONS----------------------------

bool Piece::getColour() const
{
    return colour;
}

void Piece::notifyMoved()
{
    return;
}
    

//--------------------------PIECE PROTECTED FUNCTIONS--------------------------

/******************************************************************************
Name:
       	isVertical
Purpose:
        Return whether or not the indicated move is exclusively vertical
Details:
    	If the movement contains any horizontal component, then it is 
	NOT vertical
Input:
        An integer for the x coordinate of the piece to move
                Passed by value
        An integer for the y coordinate of the piece to move
                Passed by value
        An integer for the x coordinate of the proposed move location
                Passed by value
        An integer for the y coordinate of the proposed move location
                Passed by value
Output:
    N/A
Return:
        A boolean indicating
                true == exclusively vertical movement
                false == not exclusively vertical movement
******************************************************************************/
bool Piece::isVertical (int fromX, int fromY, int toX, int toY) const
{
    bool isVert;
    int horizontal,
	vertical;

    horizontal = toY - fromY;
    vertical = toX - fromX;

    if(vertical > 0 || vertical < 0)
    {
	if(horizontal == 0)
	    isVert = true;
	else
	    isVert = false;
    }
    else
    {
	isVert = false;
    }

    return isVert;
}

/******************************************************************************
Name:
       	isHorizontal
Purpose:
        Return whether or not the indicated move is exclusively horizontal
Details:
    	If the movement contains any vertical component, then it is 
	NOT horizontal
Input:
        An integer for the x coordinate of the piece to move
                Passed by value
        An integer for the y coordinate of the piece to move
                Passed by value
        An integer for the x coordinate of the proposed move location
                Passed by value
        An integer for the y coordinate of the proposed move location
                Passed by value
Output:
    N/A
Return:
        A boolean indicating
                true == exclusively horizontal movement
                false == not exclusively horizontal movement
******************************************************************************/
bool Piece::isHorizontal (int fromX, int fromY, int toX, int toY) const
{
    bool isHor;
    int horizontal,
	vertical;
    
    horizontal = toY - fromY;
    vertical = toX - fromX;

    if(horizontal > 0 || horizontal < 0)
    {
	if(vertical == 0)
	    isHor = true;
	else
	    isHor = false;
    }
    else
    {
	isHor = false;
    }

    return isHor;
}

/******************************************************************************
Name:
       	isDiagonal
Purpose:
        Return whether or not the indicated move is exclusively diagonal
Details:
	Movement must be "perfectly" diagonal. The absolute value of the 
	distance travelled in the horizontal direction must be equal to the
	absolute value of the distance travelled in the vertical direction.
		Any other combinations of movement are NOT diagonal
Input:
        An integer for the x coordinate of the piece to move
                Passed by value
        An integer for the y coordinate of the piece to move
                Passed by value
        An integer for the x coordinate of the proposed move location
                Passed by value
        An integer for the y coordinate of the proposed move location
                Passed by value
Output:
    N/A
Return:
        A boolean indicating
                true == diagonal movement
                false == not diagonal movement
******************************************************************************/
bool Piece::isDiagonal (int fromX, int fromY, int toX, int toY) const
{
    bool isDiag;

    if(fromX == toX && fromY == toY)
	isDiag = false;
    else
    {
	if(abs(fromX - toX) == abs(fromY - toY))
	{
	    isDiag = true;
	}
	else
	{
	    isDiag = false;
	}
    }

    return isDiag;
}

/******************************************************************************
Name:
       	isForward
Purpose:
        Return whether or not a movement is in the "forward" direction for
	a Piece
Details:
	Forward is:
		From bottom rows towards the top for white pieces
			row 7 -> row 0
		From top rows towards the bottom for black pieces
			row 0 -> row 7
Input:
        An integer for the x coordinate of the piece to move
                Passed by value
        An integer for the x coordinate of the proposed move location
                Passed by value
Output:
    N/A
Return:
        A boolean indicating
                true == forward movement
                false == not forward movement
******************************************************************************/
bool Piece::isForward (int fromX, int toX) const
{
    int diff;
    bool forward;
    
    diff = toX - fromX;
    
    if(colour == WHITE)
    {
	if(diff < 0)
	    forward = true;
	else
	    forward = false;
    }
    else
    {
	if(diff < 0)
	    forward = false;
	else
	    forward = true;
    }

    return forward;
}

/******************************************************************************
Name:
       	vertDistance
Purpose:
	Calculate the vertical distance from a piece and its proposed move 
	location.
Details:
	Positive and negative values are returned as opposed to the magnitude.
Input:
        An integer for the x coordinate of the piece to move
                Passed by value
        An integer for the x coordinate of the proposed move location
                Passed by value
Output:
    N/A
Return:
	
******************************************************************************/
int Piece::vertDistance (int fromX, int toX) const
{
    return toX - fromX;
}

int Piece::horizDistance (int fromY, int toY) const
{
    return toY - fromY;
}

bool Piece::isPathClear (const Board& b, int fromX, int fromY, int toX, int toY)
    const
{
    int row,
	col,
	vert,
	hor;
    bool isClear = true,
	isVert = isVertical(fromX, fromY, toX, toY),
	isHor = isHorizontal(fromX, fromY, toX, toY),
	isDiag = isDiagonal(fromX, fromY, toX, toY);

    if(isVert)
    {
	vert = vertDistance(fromX, toX);
	if(vert > 0)
	{
	    row = 1;
	    while(row <= vert && isClear == true)
	    {
		if(b.isOccupied(fromX + row, fromY))
		    isClear = false;
		row++;
	    }
	}
	else
	{
	    row = -1;
	    while(row >= vert && isClear == true)
	    {
		if(b.isOccupied(fromX + row, fromY))
		    isClear = false;
		row--;
	    }
	}
    }
    else if(isHor)
    {
	hor = horizDistance(fromY, toY);
	if(hor > 0)
	{
	    col = 1;
	    while(col <= hor && isClear == true)
	    {
		if(b.isOccupied(fromX, fromY + col))
		    isClear = false;
		col++;
	    }
	}
	else
	{
	    col = -1;
	    while(col >= hor && isClear == true)
	    {
		if(b.isOccupied(fromX, fromY + col))
		    isClear = false;
		col--;
	    }
	}
    }
    else if(isDiag)
    {
	vert = vertDistance(fromX, toX);
	hor = horizDistance(fromY, toY);
	if(vert > 0 && hor > 0)
	{
	    row = 1;
	    col = 1;
	    while(row <= vert && isClear == true)
	    {
		if(b.isOccupied(fromX + row, fromY + col))
		    isClear = false;
		row++;
		col++;
	    }
	}
	else if(vert > 0 && hor < 0)
	{
	    row = 1;
	    col = -1;
	    while(row <= vert && isClear == true)
	    {
		if(b.isOccupied(fromX + row, fromY + col))
		    isClear = false;
		row++;
		col--;
	    }

	}
	else if(vert < 0 && hor < 0)
	{
	    row = -1;
	    col = -1;
	    while(row >= vert && isClear == true)
	    {
		if(b.isOccupied(fromX + row, fromY + col))
		    isClear = false;
		row--;
		col--;
	    }
	}
	else if(vert < 0 && hor > 0)
	{
	    row = -1;
	    col = 1;
	    while(row >= vert && isClear == true)
	    {
		if(b.isOccupied(fromX + row, fromY + col))
		    isClear = false;
		row--;
		col++;
	    }
	}
    }
    return isClear;
}
