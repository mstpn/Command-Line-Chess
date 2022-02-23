/******************************************************************************
 Name: Matthew Stepan
 File name: game.cpp
 Purpose:
        Play a game of chess between two human controlled players.
 Details:
	White moves first as in standard chess
	Players enter their moves by use of the coordinate system on the 
	board that is written to console before every move
		A player is required to make a valid move, or enter
       		-1 -1 in order to exit
	The game ends either at the -1 -1 termination, or when one player
	captures the opposing players king
		The players can choose to play again, or exit the program
 Assumptions and limitations:
        Not all of the rules of chess are followed by this program.
		There is no detection of king checking
		Kings may put themselves into check
			Kings may capture the opposing king
		Kings are not required to move themselves out of check
		A player may make any legal moves they wish to on their turn
		Pawn promotion is not handled
		En passant captures are not implemented
		Castling is not implemented
		Stalemate is not detected
 Known bugs:
        N/A
******************************************************************************/
#include "Piece.h"
#include "Board.h"
#include "ioutil.h"
using namespace std;

void initChess(Board& b);
void playerMove(Board& b, bool& turn, bool& stop);
void getMove(bool turn, int& fromX, int& fromY, int& toX, int& toY,
	     bool& stop);

int main()
{
    Board chess;
    bool turn = WHITE,
	stop = false,
	play = true,
	gameOver = false,
	winner,
	eof;

    cout << "\n    ===Welcome to Matt's Chess===" << endl << endl;
    
    initChess(chess);

    while(play)
    {
	//game loop
	cout << chess;
	while(!stop && !gameOver)
	{
	    cout << endl;
	    playerMove(chess, turn, stop);
	    if(!stop)
	    {
		cout << endl << chess;
		gameOver = chess.kingCapture(winner);
	    }
	}
	
	//winner
	if(gameOver)
	{
	    if(winner == WHITE)
	    {
		cout << "\nWhite has captured the opposing king... "
		     << "White wins!\n";
	    }
	    else
	    {
		cout << "\nBlack has captured the opposing king... "
		     << "Black wins!\n";
	    }
	}
	
	//continue playing
	play = readBool("\nWould you like to play again (y/n)? ", eof);
	while(eof)
	{
	    cout << "EOF is not a valid selection... "
		 << "Please try again...\n";
	    play = readBool("\nWould you like to play again (y/n)? ", eof);
	}
	if(play)
	{
	    gameOver = false;
	    stop = false;
	    cout << endl;
	}
    }

    cout << "\nThanks for playing! "
	 << "Come back soon for another Piece of the action!\n\n";
    
    return 0;
}

/******************************************************************************
Name:
        initChess
Purpose:
    	Initializes the board to the default piece configuration of a chess 
	game.
Details:
	The default configuration of the chess board is shown below. 

    0   1   2   3   4   5   6   7  
  +---+---+---+---+---+---+---+---+
0 | r | n | b | q | k | b | n | r |
  +---+---+---+---+---+---+---+---+
1 | p | p | p | p | p | p | p | p |
  +---+---+---+---+---+---+---+---+
2 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
3 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
4 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
5 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
6 | P | P | P | P | P | P | P | P |
  +---+---+---+---+---+---+---+---+
7 | R | N | B | Q | K | B | N | R |
  +---+---+---+---+---+---+---+---+
	White is on the bottom with the upper case letters, and black is on the 
	top with the lowercase letters.    

Input:
	A Board to have pieces placed on it
		Passed by reference
Output:
    	A Board with pieces placed on it in the starting configuration
Return:
    N/A
******************************************************************************/
void initChess(Board& b)
{
    PiecePtr p;
    int row,
	col;

    //pawns
    for(row = 0; row < MAXROWS; row++)
    {
	if(row == 1)
	{
	    for(col = 0; col < MAXCOLS; col++)
	    {
		p = new Pawn(BLACK);
		b.place(p, row, col);
	    }
	}
	else if(row == 6)
	{
	    for(col = 0; col < MAXCOLS; col++)
	    {
		p = new Pawn(WHITE);
		b.place(p, row, col);
	    }
	}
    }
    
    //rooks
    p = new Rook(BLACK);
    b.place(p, 0, 0);
    p = new Rook(BLACK);
    b.place(p, 0, 7);
    p = new Rook(WHITE);
    b.place(p, 7, 0);
    p = new Rook(WHITE);
    b.place(p, 7, 7);

    //knights
    p = new Knight(BLACK);
    b.place(p, 0, 1);
    p = new Knight(BLACK);
    b.place(p, 0, 6);
    p = new Knight(WHITE);
    b.place(p, 7, 1);
    p = new Knight(WHITE);
    b.place(p, 7, 6);

    //bishops
    p = new Bishop(BLACK);
    b.place(p, 0, 2);
    p = new Bishop(BLACK);
    b.place(p, 0, 5);
    p = new Bishop(WHITE);
    b.place(p, 7, 2);
    p = new Bishop(WHITE);
    b.place(p, 7, 5);

    //Queen
    p = new Queen(BLACK);
    b.place(p, 0, 3);
    p = new Queen(WHITE);
    b.place(p, 7, 3);
    
    //King
    p = new King(BLACK);
    b.place(p, 0, 4);
    p = new King(WHITE);
    b.place(p, 7, 4);
    
    return;
}


/******************************************************************************
Name:
        playerMove
Purpose:
	Handles the getting and executing a player move.
Details:
	A player is required to make a valid move, or else exit the game
Input:
	A Board to have pices moved on it
		Passed by reference
	A colour (boolean) to determine which players turn it is.
		Passed by reference
	A boolean indicating whether or not to stop playing the game
Output:
	A board with a moved piece, unmodified if game requested to stop
	The opposite colour as was input
	Boolean true if request to stop was made, else remains false
Return:
    N/A
******************************************************************************/
void playerMove(Board& b, bool& turn, bool& stop)
{
    int fromX,
	fromY,
	toX,
	toY;
    bool success = false,
	eof,
	confirmExit;
        
    do
    {
	getMove(turn, fromX, fromY, toX, toY, stop);
	if(stop)
	{
	    confirmExit = readBool("\nAre you sure you want to exit (y/n)? ",
				   eof);
	    while(eof)
	    {
		cout << "\nEOF is not a valid selection... "
		     << "Please try again...\n";
		confirmExit = readBool("\nAre you sure you want to exit (y/n)? "
				       ,eof);
	    }
	    if(!confirmExit)
	    {
		stop = false;
		cout << endl;
	    }
	}
	else
	{
	    success = b.move(turn, fromX, fromY, toX, toY);
	    if(!success)
	    {
		cout << "\nError... Illegal move... Please try again\n" << endl;
	    }
	    else
	    {
		turn = !turn;
	    }
	}
    }
    while(!stop && !success);
    
    return;
}


/******************************************************************************
Name:
        getMove
Purpose:
	Gets and returns a players proposed move.
Details:
Input:
	A Board to have pices moved on it
		Passed by reference
	A colour to determine which players turn it is.
		Passed by reference
	A boolean indicating whether or not to stop playing the game
Output:
	A board with a moved piece, unmodified if game requested to stop
	The opposite colour as was input
	Boolean true if request to stop was made, else remains false
Return:
    N/A
******************************************************************************/
void getMove(bool turn, int& fromX, int& fromY, int& toX, int& toY,
	     bool& stop)
{
    bool eof,
	validCoords;

    do
    {
	if(turn == WHITE)
	    cout << "White ";
	else
	    cout << "Black ";
	cout << "player please make a move... Enter -1 -1 to exit." << endl;
    
	fromX = readInt("Enter the row of the piece to move: ", eof);
	while(eof)
	{
	    cout << "\nEOF is not a valid row number... Please try again..."
		 << endl;
	    fromX = readInt("Enter the row of the piece to move: ", eof);
	}
	fromY = readInt("Enter the column of the piece to move: ", eof);
	while(eof)
	{
	    cout << "\nEOF is not a valid column number... Please try again..."
		 << endl;
	    fromY = readInt("Enter the column of the piece to move: ", eof);
	}
    
	if(fromX == -1 && fromY == -1)
	    stop = true;
	else
	{
	    toX = readInt("Enter the row of the final piece location: ", eof);
	    while(eof)
	    {
		cout << "\nEOF is not a valid row number... Please try again..."
		     << endl;
		toX = readInt("Enter the row of the final piece location: ",
			      eof);
	    }
	    toY = readInt("Enter the column of the final piece location: ",
			  eof);
	    while(eof)
	    {
		cout << "\nEOF is not a valid column number... "
		     << "Please try again..." << endl;
		toY = readInt("Enter the column of the final piece location: "
			      , eof);
	    }
	    
	    if(toX == -1 && toY == -1)
		stop = true;
	    else if(fromX >= 0 && fromX < MAXROWS &&
	       fromY >= 0 && fromY < MAXCOLS &&
	       toX >= 0 && toX < MAXROWS &&
	       toY >= 0 && toY < MAXCOLS &&
	       (fromX != toX || fromY != toY))
	    {
		validCoords = true;
	    }
	    else
	    {
		validCoords = false;
		cout << "\nError... Invalid coordinates... "
		     << "Please try again...\n" << endl;
	    }
	}
    }
    while(!validCoords && !stop);
    
    return;
}
