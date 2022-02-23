/******************************************************************************
 Name: Matthew Stepan
 File name: test_Bishop.cpp
 ******************************************************************************/
#ifndef TESTBISHOP_H
#define TESTBISHOP_H

#include "Board.h"
#include "Piece.h"
#include "gtest/gtest.h"

class test_Bishop: public testing::Test
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

TEST_F(test_Bishop, testConstructorWhite)
{
    PiecePtr p = new Bishop(WHITE);
    
    EXPECT_EQ(WHITE, p->getColour());
}

TEST_F(test_Bishop, testConstructorBlack)
{
    PiecePtr p = new Bishop(BLACK);
    
    EXPECT_EQ(BLACK, p->getColour());
}

//--------------GET SYMBOL---------------------------------

TEST_F(test_Bishop, testGetSymbolWhite)
{
    PiecePtr p = new Bishop(WHITE);
    char ch = p->getSymbol();

    EXPECT_EQ('B', ch);
}

TEST_F(test_Bishop, testGetSymbolBlack)
{
    PiecePtr p = new Bishop(BLACK);
    char ch = p->getSymbol();

    EXPECT_EQ('b', ch);
}

//---------------GET COLOUR-------------------------------

TEST_F(test_Bishop, testGetColourWhite)
{
    PiecePtr p = new Bishop(WHITE);
    bool col = p->getColour();

    EXPECT_EQ(WHITE, col);
}

TEST_F(test_Bishop, testGetColourBlack)
{
    PiecePtr p = new Bishop(BLACK);
    bool col = p->getColour();

    EXPECT_EQ(BLACK, col);
}

//---------------------CLONE-----------------------------

TEST_F(test_Bishop, testCloneWhite)
{
    PiecePtr p = new Bishop(WHITE),
	theClone;

    theClone = p->clone();

    EXPECT_EQ(p->getColour(), theClone->getColour());
}

TEST_F(test_Bishop, testCloneBlack)
{
    PiecePtr p = new Bishop(BLACK),
	theClone;

    theClone = p->clone();

    EXPECT_EQ(p->getColour(), theClone->getColour());
}

//-------------------CAN MOVE-----------------------------
TEST_F(test_Bishop, testCanMoveNotVertHorDiagKnight)
{
    PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 6,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveUp)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 3;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveDown)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 3;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveLeft)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveRight)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveUpRight)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Bishop, testCanMoveUpLeft)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Bishop, testCanMoveDownRight)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Bishop, testCanMoveDownLeft)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Bishop, testCanMoveBlockedPathEndUpRight)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 5;

    chess.place(p, toX, toY);
    p = new Bishop(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveBlockedPathEndUpLeft)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 1;

    chess.place(p, toX, toY);
    p = new Bishop(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveBlockedPathEndDownRight)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 5;

    chess.place(p, toX, toY);
    p = new Bishop(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveBlockedPathEndDownLeft)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 1;

    chess.place(p, toX, toY);
    p = new Bishop(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveBlockedPathEnRouteUpRight)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 5;

    chess.place(p, toX + 1, toY - 1);
    p = new Bishop(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveBlockedPathEnRouteUpLeft)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 1;

    chess.place(p, toX + 1, toY + 1);
    p = new Bishop(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveBlockedPathEnRouteDownRight)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 5;

    chess.place(p, toX - 1, toY - 1);
    p = new Bishop(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveBlockedPathEnRouteDownLeft)
{
   PiecePtr p = new Bishop(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 1;

    chess.place(p, toX - 1, toY + 1);
    p = new Bishop(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Bishop, testCanMoveCaptureUpRight)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Bishop(BLACK);
    chess.place(p, 3, 3);
    capture = new Bishop(WHITE);
    chess.place(capture, 1, 5);

    success = p->canMove(chess, 3, 3, 1, 5);

    EXPECT_TRUE(success);
}

TEST_F(test_Bishop, testCanMoveCaptureUpLeft)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Bishop(WHITE);
    chess.place(p, 3, 3);
    capture = new Bishop(BLACK);
    chess.place(capture, 1, 1);

    success = p->canMove(chess, 3, 3, 1, 1);

    EXPECT_TRUE(success);
}

TEST_F(test_Bishop, testCanMoveCaptureDownRight)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Bishop(BLACK);
    chess.place(p, 3, 3);
    capture = new Bishop(WHITE);
    chess.place(capture, 5, 5);

    success = p->canMove(chess, 3, 3, 5, 5);

    EXPECT_TRUE(success);
}

TEST_F(test_Bishop, testCanMoveCaptureDownLeft)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Bishop(WHITE);
    chess.place(p, 3, 3);
    capture = new Bishop(BLACK);
    chess.place(capture, 5, 1);

    success = p->canMove(chess, 3, 3, 5, 1);

    EXPECT_TRUE(success);
}


#endif
