/******************************************************************************
 Name: Matthew Stepan
 File name: test_Rook.cpp
 ******************************************************************************/
#ifndef TESTROOK_H
#define TESTROOK_H

#include "Board.h"
#include "Piece.h"
#include "gtest/gtest.h"

class test_Rook: public testing::Test
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

TEST_F(test_Rook, testConstructorWhite)
{
    PiecePtr p = new Rook(WHITE);
    
    EXPECT_EQ(WHITE, p->getColour());
}

TEST_F(test_Rook, testConstructorBlack)
{
    PiecePtr p = new Rook(BLACK);
    
    EXPECT_EQ(BLACK, p->getColour());
}

//--------------GET SYMBOL---------------------------------

TEST_F(test_Rook, testGetSymbolWhite)
{
    PiecePtr p = new Rook(WHITE);
    char ch = p->getSymbol();

    EXPECT_EQ('R', ch);
}

TEST_F(test_Rook, testGetSymbolBlack)
{
    PiecePtr p = new Rook(BLACK);
    char ch = p->getSymbol();

    EXPECT_EQ('r', ch);
}

//---------------GET COLOUR-------------------------------

TEST_F(test_Rook, testGetColourWhite)
{
    PiecePtr p = new Rook(WHITE);
    bool col = p->getColour();

    EXPECT_EQ(WHITE, col);
}

TEST_F(test_Rook, testGetColourBlack)
{
    PiecePtr p = new Rook(BLACK);
    bool col = p->getColour();

    EXPECT_EQ(BLACK, col);
}

//---------------------CLONE-----------------------------

TEST_F(test_Rook, testCloneWhite)
{
    PiecePtr p = new Rook(WHITE),
	theClone;

    theClone = p->clone();

    EXPECT_EQ(p->getColour(), theClone->getColour());
}

TEST_F(test_Rook, testCloneBlack)
{
    PiecePtr p = new Rook(BLACK),
	theClone;

    theClone = p->clone();

    EXPECT_EQ(p->getColour(), theClone->getColour());
}

//-------------------CAN MOVE-----------------------------
TEST_F(test_Rook, testCanMoveNotVertHorDiagKnight)
{
    PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 6,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveUp)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 3;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Rook, testCanMoveDown)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 3;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Rook, testCanMoveLeft)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Rook, testCanMoveRight)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Rook, testCanMoveUpRight)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveUpLeft)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveDownRight)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveDownLeft)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveBlockedPathEndUp)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 3;

    chess.place(p, toX, toY);
    p = new Rook(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveBlockedPathEndDown)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 3;

    chess.place(p, toX, toY);
    p = new Rook(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveBlockedPathEndLeft)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 1;

    chess.place(p, toX, toY);
    p = new Rook(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveBlockedPathEndRight)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 5;

    chess.place(p, fromX, fromY);
    p = new Rook(WHITE);
    chess.place(p, toX, toY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveBlockedPathEnRouteUp)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 3;

    chess.place(p, toX + 1, toY);
    p = new Rook(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveBlockedPathEnRouteDown)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 3;

    chess.place(p, toX - 1, toY);
    p = new Rook(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveBlockedPathEnRouteLeft)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 1;

    chess.place(p, toX, toY + 1);
    p = new Rook(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveBlockedPathEnRouteRight)
{
   PiecePtr p = new Rook(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 5;

    chess.place(p, toX, toY - 1);
    p = new Rook(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Rook, testCanMoveCaptureUp)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Rook(BLACK);
    chess.place(p, 3, 3);
    capture = new Rook(WHITE);
    chess.place(capture, 1, 3);

    success = p->canMove(chess, 3, 3, 1, 3);

    EXPECT_TRUE(success);
}

TEST_F(test_Rook, testCanMoveCaptureDown)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Rook(WHITE);
    chess.place(p, 3, 3);
    capture = new Rook(BLACK);
    chess.place(capture, 5, 3);

    success = p->canMove(chess, 3, 3, 5, 3);

    EXPECT_TRUE(success);
}

TEST_F(test_Rook, testCanMoveCaptureLeft)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Rook(BLACK);
    chess.place(p, 3, 3);
    capture = new Rook(WHITE);
    chess.place(capture, 3, 1);

    success = p->canMove(chess, 3, 3, 3, 1);

    EXPECT_TRUE(success);
}

TEST_F(test_Rook, testCanMoveCaptureRight)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Rook(WHITE);
    chess.place(p, 3, 3);
    capture = new Rook(BLACK);
    chess.place(capture, 3, 5);

    success = p->canMove(chess, 3, 3, 3, 5);

    EXPECT_TRUE(success);
}


#endif
