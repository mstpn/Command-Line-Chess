/******************************************************************************
 Name: Matthew Stepan
 File name: test_Knight.cpp
 ******************************************************************************/
#ifndef TESTKNIGHT_H
#define TESTKNIGHT_H

#include "Board.h"
#include "Piece.h"
#include "gtest/gtest.h"

class test_Knight: public testing::Test
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

TEST_F(test_Knight, testConstructorWhite)
{
    PiecePtr p = new Knight(WHITE);
    
    EXPECT_EQ(WHITE, p->getColour());
}

TEST_F(test_Knight, testConstructorBlack)
{
    PiecePtr p = new Knight(BLACK);
    
    EXPECT_EQ(BLACK, p->getColour());
}

//--------------GET SYMBOL---------------------------------

TEST_F(test_Knight, testGetSymbolWhite)
{
    PiecePtr p = new Knight(WHITE);
    char ch = p->getSymbol();

    EXPECT_EQ('N', ch);
}

TEST_F(test_Knight, testGetSymbolBlack)
{
    PiecePtr p = new Knight(BLACK);
    char ch = p->getSymbol();

    EXPECT_EQ('n', ch);
}

//---------------GET COLOUR-------------------------------

TEST_F(test_Knight, testGetColourWhite)
{
    PiecePtr p = new Knight(WHITE);
    bool col = p->getColour();

    EXPECT_EQ(WHITE, col);
}

TEST_F(test_Knight, testGetColourBlack)
{
    PiecePtr p = new Knight(BLACK);
    bool col = p->getColour();

    EXPECT_EQ(BLACK, col);
}

//---------------------CLONE-----------------------------

TEST_F(test_Knight, testCloneWhite)
{
    PiecePtr p = new Knight(WHITE),
	theClone;

    theClone = p->clone();

    EXPECT_EQ(p->getColour(), theClone->getColour());
}

TEST_F(test_Knight, testCloneBlack)
{
    PiecePtr p = new Knight(BLACK),
	theClone;

    theClone = p->clone();

    EXPECT_EQ(p->getColour(), theClone->getColour());
}

//-------------------CAN MOVE-----------------------------
TEST_F(test_Knight, testCanMoveNotVertHorDiagKnight)
{
    PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 6,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveUp)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 3;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveDown)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 3;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveLeft)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveRight)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveUpRight)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveUpLeft)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveDownRight)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveDownLeft)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveUp2Left1)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveUp2Right1)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 4;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveUp1Right2)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 2,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveDown1Right2)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 4,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveDown2Right1)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 4;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveDown2Left1)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveDown1Left2)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 4,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveUp1Left2)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 2,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveBlockedEndUp2Left1)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 2;

    chess.place(p, toX, toY);
    p = new Knight(WHITE);
    chess.place(p, fromX, fromY);

    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveBlockedEndUp2Right1)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 4;

    chess.place(p, toX, toY);
    p = new Knight(WHITE);
    chess.place(p, fromX, fromY);
   
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveBlockedEndUp1Right2)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 2,
	toY = 5;

    chess.place(p, toX, toY);
    p = new Knight(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveBlockedEndDown1Right2)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 4,
	toY = 5;

    chess.place(p, toX, toY);
    p = new Knight(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveBlockedEndDown2Right1)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 4;

    chess.place(p, toX, toY);
    p = new Knight(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveBlockedEndDown2Left1)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 2;

    chess.place(p, toX, toY);
    p = new Knight(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveBlockedEndDown1Left2)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 4,
	toY = 1;

    chess.place(p, toX, toY);
    p = new Knight(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveBlockedEndUp1Left2)
{
   PiecePtr p = new Knight(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 2,
	toY = 1;

    chess.place(p, toX, toY);
    p = new Knight(WHITE);
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Knight, testCanMoveCaptureUp2Left1)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Knight(BLACK);
    chess.place(p, 3, 3);
    capture = new Knight(WHITE);
    chess.place(capture, 1, 2);

    success = p->canMove(chess, 3, 3, 1, 2);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveCaptureUp2Right1)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Knight(WHITE);
    chess.place(p, 3, 3);
    capture = new Knight(BLACK);
    chess.place(capture, 1, 4);

    success = p->canMove(chess, 3, 3, 1, 4);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveCaptureUp1Right2)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Knight(BLACK);
    chess.place(p, 3, 3);
    capture = new Knight(WHITE);
    chess.place(capture, 2, 5);

    success = p->canMove(chess, 3, 3, 2, 5);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveCaptureDown1Right2)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Knight(WHITE);
    chess.place(p, 3, 3);
    capture = new Knight(BLACK);
    chess.place(capture, 4, 5);

    success = p->canMove(chess, 3, 3, 4, 5);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveCaptureDown2Right1)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Knight(BLACK);
    chess.place(p, 3, 3);
    capture = new Knight(WHITE);
    chess.place(capture, 5, 4);

    success = p->canMove(chess, 3, 3, 5, 4);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveCaptureDown2Left1)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Knight(WHITE);
    chess.place(p, 3, 3);
    capture = new Knight(BLACK);
    chess.place(capture, 5, 2);

    success = p->canMove(chess, 3, 3, 5, 2);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveCaptureDown1Left2)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Knight(BLACK);
    chess.place(p, 3, 3);
    capture = new Knight(WHITE);
    chess.place(capture, 4, 1);

    success = p->canMove(chess, 3, 3, 4, 1);

    EXPECT_TRUE(success);
}

TEST_F(test_Knight, testCanMoveCaptureUp1Left2)
{
    PiecePtr p,
	capture;
    bool success;

    p = new Knight(WHITE);
    chess.place(p, 3, 3);
    capture = new Knight(BLACK);
    chess.place(capture, 2, 1);

    success = p->canMove(chess, 3, 3, 2, 1);

    EXPECT_TRUE(success);
}


#endif
