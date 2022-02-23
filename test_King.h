/******************************************************************************
 Name: Matthew Stepan
 File name: test_King.cpp
 ******************************************************************************/
#ifndef TESTKING_H
#define TESTKING_H

#include "Board.h"
#include "Piece.h"
#include "gtest/gtest.h"

class test_King: public testing::Test
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

TEST_F(test_King, testConstructorWhite)
{
    PiecePtr p = new King(WHITE);
    
    EXPECT_EQ(WHITE, p->getColour());
}

TEST_F(test_King, testConstructorBlack)
{
    PiecePtr p = new King(BLACK);
    
    EXPECT_EQ(BLACK, p->getColour());
}

//--------------GET SYMBOL---------------------------------

TEST_F(test_King, testGetSymbolWhite)
{
    PiecePtr p = new King(WHITE);
    char ch = p->getSymbol();

    EXPECT_EQ('K', ch);
}

TEST_F(test_King, testGetSymbolBlack)
{
    PiecePtr p = new King(BLACK);
    char ch = p->getSymbol();

    EXPECT_EQ('k', ch);
}

//---------------GET COLOUR-------------------------------

TEST_F(test_King, testGetColourWhite)
{
    PiecePtr p = new King(WHITE);
    bool col = p->getColour();

    EXPECT_EQ(WHITE, col);
}

TEST_F(test_King, testGetColourBlack)
{
    PiecePtr p = new King(BLACK);
    bool col = p->getColour();

    EXPECT_EQ(BLACK, col);
}

//---------------------CLONE-----------------------------

TEST_F(test_King, testCloneWhite)
{
    PiecePtr p = new King(WHITE),
	theClone;

    theClone = p->clone();

    EXPECT_EQ(p->getColour(), theClone->getColour());
}

TEST_F(test_King, testCloneBlack)
{
    PiecePtr p = new King(BLACK),
	theClone;

    theClone = p->clone();

    EXPECT_EQ(p->getColour(), theClone->getColour());
}

//-------------------CAN MOVE-----------------------------
TEST_F(test_King, testCanMoveNotVertHorDiagKnight)
{
    PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 6,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveUpGreaterThan1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 3;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveDownGreaterThan1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 3;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveLeftGreaterThan1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveRightGreaterThan1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveUpRightGreaterThan1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveUpLeftGreaterThan1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveDownRightGreaterThan1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveDownLeftGreaterThan1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveUp1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 2,
	toY = 3;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveDown1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 4,
	toY = 3;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveLeft1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveRight1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 4;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveUpRight1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 2,
	toY = 4;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveUpLeft1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 2,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveDownRight1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 4,
	toY = 4;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveDownLeft1Square)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 4,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}


TEST_F(test_King, testCanMoveBlockedPathUp)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 2,
	toY = 3;

    chess.place(p, toX, toY);
    p = new King(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveBlockedPathDown)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 4,
	toY = 3;

    chess.place(p, toX, toY);
    p = new King(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveBlockedPathLeft)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 2;

    chess.place(p, toX, toY);
    p = new King(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveBlockedPathRight)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 4;

    chess.place(p, fromX, fromY);
    p = new King(WHITE);
    chess.place(p, toX, toY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveBlockedPathUpRight)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 2,
	toY = 4;

    chess.place(p, toX, toY);
    p = new King(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveBlockedPathUpLeft)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 2,
	toY = 2;

    chess.place(p, toX, toY);
    p = new King(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveBlockedPathDownRight)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 4,
	toY = 4;

    chess.place(p, toX, toY);
    p = new King(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveBlockedPathDownLeft)
{
   PiecePtr p = new King(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 4,
	toY = 2;

    chess.place(p, toX, toY);
    p = new King(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_King, testCanMoveCaptureUp)
{
    PiecePtr p,
	capture;
    bool success;

    p = new King(BLACK);
    chess.place(p, 3, 3);
    capture = new King(WHITE);
    chess.place(capture, 2, 3);

    success = p->canMove(chess, 3, 3, 2, 3);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveCaptureDown)
{
    PiecePtr p,
	capture;
    bool success;

    p = new King(WHITE);
    chess.place(p, 3, 3);
    capture = new King(BLACK);
    chess.place(capture, 4, 3);

    success = p->canMove(chess, 3, 3, 4, 3);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveCaptureLeft)
{
    PiecePtr p,
	capture;
    bool success;

    p = new King(BLACK);
    chess.place(p, 3, 3);
    capture = new King(WHITE);
    chess.place(capture, 3, 2);

    success = p->canMove(chess, 3, 3, 3, 2);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveCaptureRight)
{
    PiecePtr p,
	capture;
    bool success;

    p = new King(WHITE);
    chess.place(p, 3, 3);
    capture = new King(BLACK);
    chess.place(capture, 3, 4);

    success = p->canMove(chess, 3, 3, 3, 4);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveCaptureUpRight)
{
    PiecePtr p,
	capture;
    bool success;

    p = new King(BLACK);
    chess.place(p, 3, 3);
    capture = new King(WHITE);
    chess.place(capture, 2, 4);

    success = p->canMove(chess, 3, 3, 2, 4);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveCaptureUpLeft)
{
    PiecePtr p,
	capture;
    bool success;

    p = new King(WHITE);
    chess.place(p, 3, 3);
    capture = new King(BLACK);
    chess.place(capture, 2, 2);

    success = p->canMove(chess, 3, 3, 2, 2);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveCaptureDownRight)
{
    PiecePtr p,
	capture;
    bool success;

    p = new King(BLACK);
    chess.place(p, 3, 3);
    capture = new King(WHITE);
    chess.place(capture, 4, 4);

    success = p->canMove(chess, 3, 3, 4, 4);

    EXPECT_TRUE(success);
}

TEST_F(test_King, testCanMoveCaptureDownLeft)
{
    PiecePtr p,
	capture;
    bool success;

    p = new King(WHITE);
    chess.place(p, 3, 3);
    capture = new King(BLACK);
    chess.place(capture, 4, 2);

    success = p->canMove(chess, 3, 3, 4, 2);

    EXPECT_TRUE(success);
}


#endif
