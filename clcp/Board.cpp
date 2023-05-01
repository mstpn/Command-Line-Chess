/******************************************************************************
 File name: Board.cpp
 ******************************************************************************/
#include "Board.h"
#include <fstream>

//-----------------PUBLIC FUNCTIONS----------------------

Board::Board()
{
	initBoard();
}

Board::Board(const Board &other)
{
	initBoard();
	copyBoard(other);
}

Board::~Board()
{
	ofstream outfile;
	int row,
		col;

	outfile.open("final_board.txt");
	if (!outfile.fail())
	{
		for (row = 0; row < MAXROWS; row++)
		{
			for (col = 0; col < MAXCOLS; col++)
			{
				if (getSquare(row, col) != NULL)
				{
					outfile << 'P' << ' ' << row << ' ' << col << '\n';
				}
			}
		}
		outfile.close();
	}

	clearBoard();
}

PiecePtr Board::getPiece(int x, int y) const
{
	PiecePtr p;

	if (x >= 0 && x < MAXROWS &&
		y >= 0 && y < MAXCOLS)
	{
		if (grid[x][y] == NULL)
			p = NULL;
		else
		{
			p = grid[x][y]->clone();
		}
	}
	else
	{
		p = NULL;
	}

	return p;
}

bool Board::isOccupied(int x, int y) const
{
	bool occupied;
	PiecePtr p;

	p = getPiece(x, y);

	if (p == NULL)
		occupied = false;
	else
		occupied = true;

	delete p;

	return occupied;
}

bool Board::move(bool colour, int fromX, int fromY, int toX, int toY)
{
	bool success;
	PiecePtr p;

	p = getPiece(fromX, fromY);

	if (p != NULL)
	{
		if (p->getColour() == colour)
		{
			success = p->canMove(*this, fromX, fromY, toX, toY);
			if (success)
			{
				// capture
				if (grid[toX][toY] != NULL)
				{
					delete grid[toX][toY];
					grid[toX][toY] = grid[fromX][fromY];
					grid[fromX][fromY] = NULL;
				}
				// normal move
				else
				{
					grid[toX][toY] = grid[fromX][fromY];
					grid[fromX][fromY] = NULL;
				}
				if (grid[toX][toY]->getSymbol() == 'P' || grid[toX][toY]->getSymbol() == 'p')
				{
					grid[toX][toY]->notifyMoved();
				}
			}
		}
		else
		{
			success = false;
			/*
			A function that decides the human players colour
			 */
		}
	}
	else
	{
		success = false;
	}
	delete p;

	return success;
}

bool Board::place(const PiecePtr &p, int x, int y)
{
	bool success;

	if (x >= 0 && x < MAXROWS &&
		y >= 0 && y < MAXCOLS)
	{
		if (getSquare(x, y) == NULL)
		{
			grid[x][y] = p;
			success = true;
		}
		else
		{
			success = false;
		}
	}

	return success;
}

bool Board::remove(int x, int y)
{
	bool success;

	if (x >= 0 && x < MAXROWS &&
		y >= 0 && y < MAXCOLS)
	{

		if (getSquare(x, y) == NULL)
		{
			success = false;
		}
		else
		{
			delete grid[x][y];
			grid[x][y] = NULL;
			success = true;
		}
	}
	return success;
}

void Board::write(ostream &out) const
{
	int row,
		col;
	char chCol;
	PiecePtr p;

	for (row = 0; row < MAXROWS; row++)
	{
		if (row == 0)
		{
			out << "    ";
			for (col = 0; col < MAXCOLS; col++)
			{
				chCol = (char)(col + 'A');
				out << chCol << "   ";
			}
			out << "\n";
			writeLine(out);
		}
		for (col = 0; col < MAXCOLS; col++)
		{
			if (col == 0)
			{
				out << abs(row - 8) << " |";
			}
			p = getPiece(row, col);
			// print the piece if there is one
			if (p != NULL)
			{
				// char symbol[21];
				// symbol[0] = p->getSymbol();
				// whiteBG(symbol);
				// out << " " << symbol << " |";
				out << " " << p->getSymbol() << " |";
			}
			else
			{
				out << "   |";
			}
			delete p;
		}
		out << "\n";
		writeLine(out);
	}

	return;
}

bool Board::kingCapture(bool &colour) const
{
	bool capture = false,
		 whiteKing = false,
		 blackKing = false;
	int row,
		col;
	PiecePtr p;

	for (row = 0; row < MAXROWS; row++)
	{
		for (col = 0; col < MAXCOLS; col++)
		{
			p = getPiece(row, col);
			if (p != NULL)
			{
				if (p->getColour() == WHITE && p->getSymbol() == 'K')
					whiteKing = true;
				else if (p->getColour() == BLACK && p->getSymbol() == 'k')
					blackKing = true;
			}
			delete p;
		}
	}

	if (whiteKing && !blackKing)
	{
		capture = true;
		colour = WHITE;
	}
	else if (!whiteKing && blackKing)
	{
		capture = true;
		colour = BLACK;
	}

	return capture;
}

Board &Board::operator=(const Board &other)
{
	if (this != &other)
	{
		clearBoard();
		copyBoard(other);
	}

	return (*this);
}

//-----------------PRIVATE FUNCTIONS-----------------------

/******************************************************************************
Name:
	initBoard
Purpose:
	Initializes the board to an empty state.
Details:
	The board is initialized to be completely empty, not set up for a specific
	game.
		That is handled by the client code.
Input:
	N/A
Output:
	N/A
Return:
	N/A
 ******************************************************************************/
void Board::initBoard()
{
	// clearBoard();
	int row,
		col;

	for (row = 0; row < MAXROWS; row++)
	{
		for (col = 0; col < MAXCOLS; col++)
		{
			if (getSquare(row, col) != NULL)
			{
				grid[row][col] = NULL;
			}
		}
	}

	return;
}

/******************************************************************************
Name:
	clearBoard
Purpose:
	Removes all pieces from the board and deallocates their memory.
Details:
	Only pieces that are currently placed on the board will have their memory
	deallocated.
		All other pieces not placed on the board will need to be
		deallocated by the client program.
Input:
	N/A
Output:
	N/A
Return:
	N/A
 ******************************************************************************/
void Board::clearBoard()
{
	int row,
		col;

	for (row = 0; row < MAXROWS; row++)
	{
		for (col = 0; col < MAXCOLS; col++)
		{
			remove(row, col);
		}
	}

	return;
}

/******************************************************************************
Name:
	copyBoard
Purpose:
	Copy the pieces and layout of another board to the current board.
Details:
	The current board will have their own set of pieces allocated from memory.
		Their contents and position on the board will be identical to
		the copied board, but they will be a different obejct in memory
		than the original piece.
	This function does not clear or initialize the current board state
	beforecopying.
		A call to initBoard or clearBoard should be made before this
		function is called.
Input:
	An object of type Board that is to be copied.
		Passed by reference (const).
Output:
	The unmodified Board that was copied byt the function.
Return:
	N/A
 ******************************************************************************/
void Board::copyBoard(const Board &other)
{
	int row,
		col;
	PiecePtr p;

	for (row = 0; row < MAXROWS; row++)
	{
		for (col = 0; col < MAXCOLS; col++)
		{
			if (other.getSquare(row, col) != NULL)
			{
				p = other.getPiece(row, col);
				place(p, row, col);
			}
		}
	}

	return;
}

/******************************************************************************
Name:
	getSquare
Purpose:
	Return a pointer to the piece at a specified location on the board.
Details:
	No handling of OOB coordinates.
Input:
	An integer representing the x coordinate of a board location
		Passed by value
	An integer representing the y coordinate of a board location
		Passed by value
Output:
	N/A
Return:
	A pointer to the piece at the specified board location
 ******************************************************************************/
PiecePtr Board::getSquare(int x, int y) const
{
	return grid[x][y];
}

/******************************************************************************
Name:
	writeLine
Purpose:
	Helper function for the write public member function that outputs a row
	dividing line to an output stream.
Details:
	N/A
Input:
	An output stream
		Passed by reference
Output:
	An output stream with the row dividing line added to it.
Return:
	N/A
 ******************************************************************************/
void Board::writeLine(ostream &out) const
{
	int col;

	out << "  ";
	for (col = 0; col < MAXCOLS; col++)
	{
		out << "+---";
		if (col == MAXCOLS - 1)
		{
			out << "+\n";
		}
	}

	return;
}

//-----------------------OTHER FUNCTIONS-----------------------

/******************************************************************************
Name:
	operator<<
Purpose:
	Overload the insertion operator to handle the Board type
Details:
	N/A
Input:
	An output stream where the Board is written to
		Passed by reference
	An object of type Board that is to be written.
		Passed by reference (const).
Output:
	An output stream that has had the Board written to it
Return:
	An output stream
 ******************************************************************************/
ostream &operator<<(ostream &out, const Board &b)
{
	b.write(out);

	return out;
}

/*
See https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation

The maximum FEN string is ~90 characters, we will use 100 to be safe
	Ours will be even less, since we don't need to store castling &
	en passant information

The FEN string is in the following format:
	<board layout> <turn> 

Input
	fen string to write back to
		Passed by reference
	whose turn it is
		Passed by value
Output
	N/A
 */
void Board::boardToFEN(char fen[100], bool turn)
{
	int row,
		col,
		emptyCount = 0,
		fill = 0;

	for (row = 0; row < MAXROWS; row++)
	{
		for (col = 0; col < MAXCOLS; col++)
		{
			if (getPiece(row, col) != NULL)
			{
				if (emptyCount > 0)
				{
					fen[fill++] = (char)(emptyCount + '0');
					emptyCount = 0;
				}
				fen[fill++] = getPiece(row, col)->getSymbol();
			}
			else
			{
				emptyCount++;
			}
		}
		if (emptyCount > 0)
		{
			fen[fill++] = (char)(emptyCount + '0');
			emptyCount = 0;
		}
		if (row < MAXROWS - 1)
		{
			fen[fill++] = '/';
		}
	}
	fen[fill++] = ' ';
	if (turn == WHITE)
	{
		fen[fill++] = 'w';
	}
	else
	{
		fen[fill++] = 'b';
	}
	fen[fill++] = NULLCHAR;

	return;
}

/*
	Evaluate the position on the board using a simple piece weight heuristic.
	Input
		boolean turn for the color of the player whose turn it is
	Output
		An integer representing the value of the board for the player whose turn it is
			Values are relative to the player whose turn it is
 */
int Board::boardEval(bool turn)
{
	int row,
		col,
		black,
		white,
		eval;
	char symbol;
	PiecePtr p;

	// Piece weights
	int pawn = 1;
	int bishop = 3;
	int knight = 3;
	int rook = 5;
	int queen = 9;
	int king = 90;

	black = white = 0;

	for (row = 0; row < MAXROWS; row++)
	{
		for (col = 0; col < MAXCOLS; col++)
		{
			p = getPiece(row, col);

			if (p != NULL)
			{
				symbol = p->getSymbol();
				switch (symbol)
				{
				case 'P':
					white += pawn;
					break;
				case 'B':
					white += bishop;
					break;
				case 'N':
					white += knight;
					break;
				case 'R':
					white += rook;
					break;
				case 'Q':
					white += queen;
					break;
				case 'K':
					white += king;
					break;
				case 'p':
					black += pawn;
					break;
				case 'b':
					black += bishop;
					break;
				case 'n':
					black += knight;
					break;
				case 'r':
					black += rook;
					break;
				case 'q':
					black += queen;
					break;
				case 'k':
					black += king;
					break;
				}
			}
		}
	}
	eval = white - black;
	if (turn == BLACK)
		eval *= -1;

	return eval;
}
