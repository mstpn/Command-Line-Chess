/******************************************************************************
 File name: game.cpp
 Purpose:
	Play a game of chess between a human and an AI
 Details:
	To play a game of chess, the user must first choose a colour to play
	as. The user may also choose to play against the AI or have the AI play
	against itself. The user may also choose the difficulty of the AI. The
	difficulty is determined by the depth of the search tree. The user may
	also choose the number of threads to use for the AI. After a game is over,
	the user may choose to play again.

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
#include <cctype>
#include <string.h>
#include "zHandler.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include "zTransposition.h"
#include "poll.h"

using namespace std;

#define THREAD_NUM 4 // number of threads to use
#define DEPTH_MOD 1	 // the offset of difficulty to depth
#define STDIN 0		 // stdin file descriptor

// Multi-threading variables
Task taskQueue[1000];
int taskCount = 0;
pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

void initChess(Board &b);
void playerMove(Board &b, bool &turn, bool &stop, bool humanColour, int depth, int numThreads, bool selfPlay);
void getMove(Board &b, bool turn, bool humanColour, int &fromX, int &fromY, int &toX, int &toY, bool &stop, int depth, int numThreads, bool selfPlay);
void parseANMove(int &row, int &col, bool &stop, const char prompt[]);
void chooseColour(bool &humanColour, bool &selfPlay);
void coordToAN(int x, int y, char an[2]);
int getDepth();
void gameConfig(bool &humanColour, int &depth, int &numThreads, bool &selfPlay);

int main()
{
	Board chess;
	bool turn = WHITE,
		 stop = false,
		 play = true,
		 gameOver = false,
		 winner,
		 eof,
		 humanColour,
		 selfPlay = false;
	int numThreads,
		depth;
	TranspositionTable *ttable = createTable(TABLE_NAME);

	gameConfig(humanColour, depth, numThreads, selfPlay);

	// create thread pool
	vector<pthread_t> th(numThreads);
	pthread_mutex_init(&mutexQueue, NULL);
	pthread_cond_init(&condQueue, NULL);
	for (int i = 0; i < numThreads; i++)
	{
		if (pthread_create(&th[i], NULL, &startThread, NULL) != 0)
		{
			perror("Failed to create the thread");
		}
	}

	// initialize board for chess
	initChess(chess);
	// game loop
	while (play)
	{
		cout << chess;
		while (!stop && !gameOver)
		{
			cout << endl;
			playerMove(chess, turn, stop, humanColour, depth, numThreads, selfPlay);
			if (!stop)
			{
				cout << endl
					 << chess;
				gameOver = chess.kingCapture(winner);
			}
		}

		// winner
		if (gameOver)
		{
			if (winner == WHITE)
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

		// continue playing
		play = readBool("\nWould you like to play again (y/n)? ", eof);
		while (eof)
		{
			cout << "EOF is not a valid selection... "
				 << "Please try again...\n";
			play = readBool("\nWould you like to play again (y/n)? ", eof);
		}
		if (play)
		{
			gameOver = false;
			stop = false;
			turn = WHITE;
			initChess(chess);
			cout << endl;
			chooseColour(humanColour, selfPlay);
			depth = getDepth();
			if(selfPlay)
			{
				cout << "Press ENTER to pause the game at any time" << endl << endl;
			}
		}
	}

	destroyTable(ttable, TABLE_NAME);

	cout << "\nThanks for playing! "
		 << "Come back soon for another Piece of the action!\n\n";

	// thread cleanup (make seperate function eventually)
	if (numThreads > 1)
	{
		for (int i = 0; i < numThreads; i++)
		{
			pthread_cancel(th[i]);
		}
		pthread_mutex_destroy(&mutexQueue);
		pthread_cond_destroy(&condQueue);
	}
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
void initChess(Board &b)
{
	b.clearBoard();
	PiecePtr p;
	int row,
		col;

	// pawns
	for (row = 0; row < MAXROWS; row++)
	{
		if (row == 1)
		{
			for (col = 0; col < MAXCOLS; col++)
			{
				p = new Pawn(BLACK);
				b.place(p, row, col);
			}
		}
		else if (row == 6)
		{
			for (col = 0; col < MAXCOLS; col++)
			{
				p = new Pawn(WHITE);
				b.place(p, row, col);
			}
		}
	}

	// rooks
	p = new Rook(BLACK);
	b.place(p, 0, 0);
	p = new Rook(BLACK);
	b.place(p, 0, 7);
	p = new Rook(WHITE);
	b.place(p, 7, 0);
	p = new Rook(WHITE);
	b.place(p, 7, 7);

	// knights
	p = new Knight(BLACK);
	b.place(p, 0, 1);
	p = new Knight(BLACK);
	b.place(p, 0, 6);
	p = new Knight(WHITE);
	b.place(p, 7, 1);
	p = new Knight(WHITE);
	b.place(p, 7, 6);

	// bishops
	p = new Bishop(BLACK);
	b.place(p, 0, 2);
	p = new Bishop(BLACK);
	b.place(p, 0, 5);
	p = new Bishop(WHITE);
	b.place(p, 7, 2);
	p = new Bishop(WHITE);
	b.place(p, 7, 5);

	// Queen
	p = new Queen(BLACK);
	b.place(p, 0, 3);
	p = new Queen(WHITE);
	b.place(p, 7, 3);

	// King
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
	A boolean for the human colour
		True if human is white, false if human is black
		Passed by reference
	A boolean for self play
		True if self play, false if not
		Passed by reference
Output:
	A board with a moved piece, unmodified if game requested to stop
	The opposite colour as was input
	Boolean true if request to stop was made, else remains false
Return:
	N/A
******************************************************************************/
void playerMove(Board &b, bool &turn, bool &stop, bool humanColour, int depth, int numThreads, bool selfPlay)
{
	int fromX,
		fromY,
		toX,
		toY,
		stopAI;
	bool success = false,
		 eof,
		 confirmExit;

	// uncomment to print out posistion evaluation
	// char fen[100];
	// b.boardToFEN(fen, turn);
	// cout << "Board Eval: " << b.boardEval(WHITE) << endl;
	// cout << fen << endl << endl;

	do
	{
		if (selfPlay)
		{
			// use posix poll() to check stdin while remaining non-blocking
			// https://man7.org/linux/man-pages/man2/poll.2.html
			pollfd fd[] = {STDIN, POLLIN, 0};
			stopAI = poll(fd, 1, 0);
			if (stopAI > 0)
			{
				cin.clear();
				cin.ignore(10000, '\n');
				char c[1];
				readString("\nnext move: <enter>, quit: <q> ", c, 1, 0, eof);
				if (strcmp(c, "q") == 0)
				{
					stop = true;
					break;
				}
				cout << endl;
			}
		}

		getMove(b, turn, humanColour, fromX, fromY, toX, toY, stop, depth, numThreads, selfPlay);
		if (stop)
		{
			confirmExit = readBool("\nAre you sure you want to exit (y/n)? ",
								   eof);
			while (eof)
			{
				cout << "\nEOF is not a valid selection... "
					 << "Please try again...\n";
				confirmExit = readBool("\nAre you sure you want to exit (y/n)? ", eof);
			}
			if (!confirmExit)
			{
				stop = false;
				cout << endl;
			}
		}
		else
		{
			success = b.move(turn, fromX, fromY, toX, toY);
			if (!success)
			{
				cout << "\nError... Illegal move... Please try again\n"
					 << endl;
			}
			else
			{
				turn = !turn;
			}
		}
	} while (!stop && !success);

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
	A boolean for human colour
		True if human is white, false if human is black
		Passed by reference
	Integer for number of threads to use
		Passed by reference
	boolean for self play
		True if self play, false if not
		Passed by reference
Output:
	A board with a moved piece, unmodified if game requested to stop
	The opposite colour as was input
	Boolean true if request to stop was made, else remains false
Return:
	N/A
******************************************************************************/
void getMove(Board &b, bool turn, bool humanColour, int &fromX, int &fromY, int &toX, int &toY, bool &stop, int depth, int numThreads, bool selfPlay)
//  X -> row
//  Y -> col
{
	bool validCoords;
	char moveFrom[] = "Enter the piece to move: ";
	char moveTo[] = "Enter the location to move the piece: ";

	do
	{
		// Player's move
		if (!selfPlay && turn == humanColour)
		{
			if (turn == WHITE)
				cout << "White ";
			else
				cout << "Black ";
			cout << "player please make a move... Enter -1 to exit." << endl;

			parseANMove(fromX, fromY, stop, moveFrom);

			if (stop)
				break;

			parseANMove(toX, toY, stop, moveTo);

			if (stop)
				break;

			if (fromX >= 0 && fromX < MAXROWS &&
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
					 << "Please try again...\n"
					 << endl;
			}
		}
		// AI move
		else
		{
			aiTurn(b, turn, fromX, fromY, toX, toY, depth, numThreads);
			char fromAN[3];
			char toAN[3];
			coordToAN(fromX, fromY, fromAN);
			coordToAN(toX, toY, toAN);

			// Make the game followable by adding a delay
			if (selfPlay)
			{
				sleep(2);
			}

			if (turn == WHITE)
				cout << "White ";
			else
				cout << "Black ";
			cout << "moves: " << fromAN << " -> " << toAN << endl;

			// Always valid, checked in AI turn
			validCoords = true;
		}

	} while (!validCoords && !stop);

	return;
}

/*
	Converting from algebraic notation to coordinates
	Input
		x coordinate
		y coordinate
		char array to store the algebraic notation
	Output
		updated char array with the algebraic notation
 */
void coordToAN(int x, int y, char an[3])
{
	an[0] = (char)(y + 'A');
	an[1] = (char)((-1 * (x - 7)) + '1');
	an[2] = '\0';
	return;
}

/*
	Parse algebraic notation move and convert to coordinates
	If the user enters -1, the game will stop, and the stop boolean will be set to true
	Input
		Row coordinate
		Column coordinate
		Stop boolean
		Prompt to display to user
	Output
		Updated row coordinate
		Updated column coordinate
		Updated stop boolean
 */
void parseANMove(int &row, int &col, bool &stop, const char prompt[])
{
	char move[2];
	bool eof;
	char charCol;

	readString(prompt, move, 2, 2, eof);

	// User wants to stop the game
	if (strcmp("-1", move) == 0)
	{
		stop = true;
		return;
	}

	charCol = (char)tolower(move[0]);
	row = abs(move[1] - '0' - 8);

	switch (charCol)
	{
	case 'a':
		col = 0;
		break;
	case 'b':
		col = 1;
		break;
	case 'c':
		col = 2;
		break;
	case 'd':
		col = 3;
		break;
	case 'e':
		col = 4;
		break;
	case 'f':
		col = 5;
		break;
	case 'g':
		col = 6;
		break;
	case 'h':
		col = 7;
		break;
	default:
		col = 100;
	}

	// cout << move << " -> "
	// 	 << "col: " << col << " row: " << row << endl;

	return;
}

/*
	Prompts the user for a difficulty level, and converts it to a depth for the AI to search to
	Input
		N/A
	Output
		Depth to search to
 */
int getDepth()
{
	int difficulty;
	bool eof;
	cout << "Difficulty:" << endl
		 << "\tEasy moves are instantaneous" << endl
		 << "\tNormal moves take a few seconds" << endl
		 << "\tHard moves may take 30-60s+ in some positions." << endl;
	char prompt[] = "Enter difficulty from 1-3 (easy/normal/hard): ";
	do
	{
		difficulty = readInt(prompt, eof);
	} while (difficulty < 1 || difficulty > 3);
	cout << endl;

	return difficulty + DEPTH_MOD;
}

/*
	Handles the configuration setup of the initial game state.
	What difficulty level to play at, number of threads to use, and the
	colour to play as, or whether to watch self play (AI vs AI).
	Input
		Colour to play as
		Depth to search to
		Number of threads to use
		Whether to watch self play
	Output
		Updated colour to play as
		Updated depth to search to
		Updated number of threads to use
		Updated whether to watch self play
 */
void gameConfig(bool &humanColour, int &depth, int &numThreads, bool &selfPlay)
{
	bool eof;
	unsigned int processorCount;
	// Print welcome message
	cout << "\n\t\tWelcome to THREADULATOR Chess" << endl
		 << endl
		 << endl
		 << endl;

	// Determine number of threads to use
	// https://en.cppreference.com/w/cpp/thread/thread/hardware_concurrency
	processorCount = thread::hardware_concurrency();
	if (processorCount == 0 || processorCount == 1)
	{
		// no multithreading on single core or undected CPUs
		numThreads = 1;
	}
	else
	{
		// assume hyperthreading on > 1 core CPUs
		numThreads = processorCount * 2;
	}

	cout << "Your CPU has " << processorCount;
	if (processorCount == 0 || processorCount == 1)
	{
		cout << " core, so no multithreading will be used." << endl;
		numThreads = 1;
	}
	else
	{
		cout << " cores" << ", and " << numThreads << " threads have been automatically assigned to THREADULATOR." << endl;
	}
	cout << "Manaul selection (1 - 32), or 0 to continue with automatic assignment.\n";
	int manualThreads;
	do
	{
		manualThreads = readInt("Number of threads: ", eof);
	} while (eof || (manualThreads < 0 || manualThreads > 32));
	cout << endl;
	if (manualThreads != 0)
	{
		numThreads = manualThreads;
	}

	// Give information about the game
	cout << "This program does NOT implement the following rules of chess:" << endl
		 << "        - En passant captures" << endl
		 << "        - Castling" << endl
		 << "        - Pawn promotion" << endl
		 << "        - Check detection" << endl
		 << "        - Stalemate detection" << endl
		 << endl;
	cout << "Moves are made using Algebraic Notation (AN)" << endl
		 << "Enter the coordinates of the piece you wish to move (upper or lower case)" << endl
		 << "Then enter the coordinates of the square you wish to move it to" << endl
		 << "For example, to move the white pawn at e2 to e4:" << endl
		 << "\te2 -> ENTER" << endl
		 << "\te4 -> ENTER" << endl
		 << "Enter -1 to exit the program" << endl
		 << endl;

	// get players colour
	chooseColour(humanColour, selfPlay);
	// get depth (difficulty)
	depth = getDepth();
	// initialize chess board

	if (!selfPlay)
	{
		cout << "You are playing as " << (humanColour ? "white" : "black") << endl
			 << "The " << (humanColour ? "white" : "black") << " pieces are on the top of the board" << endl
			 << "Capital letters represent white pieces, lowercase letters represent black pieces" << endl
			 << "You are playing on difficulty ";
		switch (depth)
		{
		case 1:
			cout << "2 (easy)";
			break;
		case 2:
			cout << "3 (normal)";
			break;
		case 3:
			cout << "4 (hard)";
			break;
		}
		cout << endl
			 << endl
			 << "Good luck!" << endl
			 << endl;
	}
	else
	{
		cout << "Press ENTER to pause the game at any time" << endl;
		cout << "Enjoy the AI v AI game!" << endl
			 << endl;
	}

	return;
}

/*
	A function that decides the human players colour, or whether to watch self play.
	Input
		Colour to play as
		Whether to watch self play
	Output
		Updated colour to play as
		Updated whether to watch self play
 */
void chooseColour(bool &humanColour, bool &selfPlay)
{
	bool eof;
	char choice[1];
	readString("Would you like play as white, black, random, or watch an AI match? (w/b/r/a): ", choice, 1, 1, eof);

	// loop while choice is not valid, using strcmp
	while (strcmp(choice, "w") != 0 && strcmp(choice, "b") != 0 && strcmp(choice, "r") != 0 && strcmp(choice, "a") != 0)
	{
		readString("Invalid input. Please enter w, b, r, or a: ", choice, 1, 1, eof);
	}
	if (strcmp(choice, "w") == 0)
	{
		humanColour = WHITE;
	}
	else if (strcmp(choice, "b") == 0)
	{
		humanColour = BLACK;
	}
	else if (strcmp(choice, "r") == 0)
	{
		humanColour = rand() % 2;
	}
	else if (strcmp(choice, "a") == 0)
	{
		selfPlay = true;
	}

	cout << endl;

	return;
}