/******************************************************************************
 Name: Matthew Stepan
 File name: test_Queen.cpp
 ******************************************************************************/
#ifndef TESTQUEEN_H
#define TESTQUEEN_H

#include "Board.h"
#include "Piece.h"
#include "gtest/gtest.h"

class test_Queen: public testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    Board chess;
};

//------------------CONSTRUCTOR-----------------------

TEST_F(test_Queen, testConstructorWhite)
{
    PiecePtr p = new Queen(WHITE);
    
    EXPECT_EQ(WHITE, p->getColour());
}

TEST_F(test_Queen, testConstructorBlack)
{
    PiecePtr p = new Queen(BLACK);
    
    EXPECT_EQ(BLACK, p->getColour());
}

//--------------GET SYMBOL---------------------------------

TEST_F(test_Queen, testGetSymbolWhite)
{
    PiecePtr p = new Queen(WHITE);
    char ch = p->getSymbol();

    EXPECT_EQ('Q', ch);
}

TEST_F(test_Queen, testGetSymbolBlack)
{
    PiecePtr p = new Queen(BLACK);
    char ch = p->getSymbol();

    EXPECT_EQ('q', ch);
}

//---------------GET COLOUR-------------------------------

TEST_F(test_Queen, testGetColourWhite)
{
    PiecePtr p = new Queen(WHITE);
    bool col = p->getColour();

    EXPECT_EQ(WHITE, col);
}

TEST_F(test_Queen, testGetColourBlack)
{
    PiecePtr p = new Queen(BLACK);
    bool col = p->getColour();

    EXPECT_EQ(BLACK, col);
}

//---------------------CLONE-----------------------------

TEST_F(test_Queen, testCloneWhite)
{
    PiecePtr p = new Queen(WHITE),
	theClone;

    theClone = p->clone();

    EXPECT_EQ(p->getColour(), theClone->getColour());
}

TEST_F(test_Queen, testCloneBlack)
{
    PiecePtr p = new Queen(BLACK),
	theClone;

    theClone = p->clone();

    EXPECT_EQ(p->getColour(), theClone->getColour());
}

//-------------------CAN MOVE-----------------------------
TEST_F(test_Queen, testCanMoveNotVertHorDiagKnight)
{
    PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 6,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveUp)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 3;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveDown)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 3;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveLeft)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveRight)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveUpRight)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveUpLeft)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveDownRight)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveDownLeft)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEndUp)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 3;

    chess.place(p, toX, toY);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEndDown)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 3;

    chess.place(p, toX, toY);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEndLeft)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 1;

    chess.place(p, toX, toY);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEndRight)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 5;

    chess.place(p, fromX, fromY);
    p = new Queen(WHITE);
    chess.place(p, toX, toY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEndUpRight)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 5;

    chess.place(p, toX, toY);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEndUpLeft)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 1;

    chess.place(p, toX, toY);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEndDownRight)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 5;

    chess.place(p, toX, toY);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEndDownLeft)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 1;

    chess.place(p, toX, toY);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEnRouteUp)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 3;

    chess.place(p, toX + 1, toY);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEnRouteDown)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 3;

    chess.place(p, toX - 1, toY);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEnRouteLeft)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 1;

    chess.place(p, toX, toY + 1);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEnRouteRight)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 5;

    chess.place(p, toX, toY - 1);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}


TEST_F(test_Queen, testCanMoveBlockedPathEnRouteUpRight)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 5;

    chess.place(p, toX + 1, toY - 1);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEnRouteUpLeft)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 1;

    chess.place(p, toX + 1, toY + 1);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEnRouteDownRight)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 5;

    chess.place(p, toX - 1, toY - 1);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveBlockedPathEnRouteDownLeft)
{
   PiecePtr p = new Queen(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 1;

    chess.place(p, toX - 1, toY + 1);
    p = new Queen(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Queen, testCanMoveCaptureUp)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Queen(BLACK);
    chess.place(p, 3, 3);
    capture = new Queen(WHITE);
    chess.place(capture, 1, 3);

    success = p->canMove(chess, 3, 3, 1, 3);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveCaptureDown)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Queen(WHITE);
    chess.place(p, 3, 3);
    capture = new Queen(BLACK);
    chess.place(capture, 5, 3);

    success = p->canMove(chess, 3, 3, 5, 3);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveCaptureLeft)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Queen(BLACK);
    chess.place(p, 3, 3);
    capture = new Queen(WHITE);
    chess.place(capture, 3, 1);

    success = p->canMove(chess, 3, 3, 3, 1);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveCaptureRight)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Queen(WHITE);
    chess.place(p, 3, 3);
    capture = new Queen(BLACK);
    chess.place(capture, 3, 5);

    success = p->canMove(chess, 3, 3, 3, 5);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveCaptureUpRight)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Queen(BLACK);
    chess.place(p, 3, 3);
    capture = new Queen(WHITE);
    chess.place(capture, 1, 5);

    success = p->canMove(chess, 3, 3, 1, 5);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveCaptureUpLeft)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Queen(WHITE);
    chess.place(p, 3, 3);
    capture = new Queen(BLACK);
    chess.place(capture, 1, 1);

    success = p->canMove(chess, 3, 3, 1, 1);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveCaptureDownRight)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Queen(BLACK);
    chess.place(p, 3, 3);
    capture = new Queen(WHITE);
    chess.place(capture, 5, 5);

    success = p->canMove(chess, 3, 3, 5, 5);

    EXPECT_TRUE(success);
}

TEST_F(test_Queen, testCanMoveCaptureDownLeft)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Queen(WHITE);
    chess.place(p, 3, 3);
    capture = new Queen(BLACK);
    chess.place(capture, 5, 1);

    success = p->canMove(chess, 3, 3, 5, 1);

    EXPECT_TRUE(success);
}


#endif
