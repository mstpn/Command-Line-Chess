/******************************************************************************
 Name: Matthew Stepan
 File name: test_Pawn.cpp
 ******************************************************************************/
#ifndef TESTPAWN_H
#define TESTPAWN_H

#include "Board.h"
#include "Piece.h"
#include "gtest/gtest.h"

class test_Pawn: public testing::Test
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

TEST_F(test_Pawn, testConstructorWhite)
{
    PiecePtr p = new Pawn(WHITE);
    
    EXPECT_EQ(WHITE, p->getColour());
}

TEST_F(test_Pawn, testConstructorBlack)
{
    PiecePtr p = new Pawn(BLACK);
    
    EXPECT_EQ(BLACK, p->getColour());
}

//--------------GET SYMBOL---------------------------------

TEST_F(test_Pawn, testGetSymbolWhite)
{
    PiecePtr p = new Pawn(WHITE);
    char ch = p->getSymbol();

    EXPECT_EQ('P', ch);
}

TEST_F(test_Pawn, testGetSymbolBlack)
{
    PiecePtr p = new Pawn(BLACK);
    char ch = p->getSymbol();

    EXPECT_EQ('p', ch);
}

//---------------------CLONE-----------------------------

TEST_F(test_Pawn, testCloneWhite)
{
    PiecePtr p = new Pawn(WHITE),
	theClone;

    theClone = p->clone();

    EXPECT_EQ(p->getColour(), theClone->getColour());
}

TEST_F(test_Pawn, testCloneBlack)
{
    PiecePtr p = new Pawn(BLACK),
	theClone;

    theClone = p->clone();

    EXPECT_EQ(p->getColour(), theClone->getColour());
}

//-------------------GET COLOUR-----------------------------

TEST_F(test_Pawn, testGetColourWhite)
{
    PiecePtr p = new Pawn(WHITE);
    bool col = p->getColour();

    EXPECT_EQ(WHITE, col);
}

TEST_F(test_Pawn, testGetColourBlack)
{
    PiecePtr p = new Pawn(BLACK);
    bool col = p->getColour();

    EXPECT_EQ(BLACK, col);
}


//-------------------CAN MOVE-----------------------------

TEST_F(test_Pawn, testCanMoveNotVertHorDiagKnight)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 6,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}
TEST_F(test_Pawn, testCanMoveWhiteNoMove1Square)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 7,
	fromY = 7,
	toX = 6,
	toY = 7;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Pawn, testCanMoveWhiteNoMove2Square)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 7,
	fromY = 7,
	toX = 5,
	toY = 7;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Pawn, testCanMoveBlackNoMove1Square)
{
   PiecePtr p = new Pawn(BLACK);
    bool success;
    int fromX = 0,
	fromY = 7,
	toX = 1,
	toY = 7;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Pawn, testCanMoveBlackNoMove2Square)
{
   PiecePtr p = new Pawn(BLACK);
    bool success;
    int fromX = 0,
	fromY = 7,
	toX = 2,
	toY = 7;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Pawn, testCanMoveWhiteHasMoved1Square)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 7,
	fromY = 7,
	toX = 6,
	toY = 7;

    p->notifyMoved();
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Pawn, testCanMoveWhiteHasMoved2Square)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 7,
	fromY = 7,
	toX = 5,
	toY = 7;

    p->notifyMoved();
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveBlackHasMoved1Square)
{
   PiecePtr p = new Pawn(BLACK);
    bool success;
    int fromX = 0,
	fromY = 7,
	toX = 1,
	toY = 7;

    p->notifyMoved();
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Pawn, testCanMoveBlackHasMoved2Square)
{
   PiecePtr p = new Pawn(BLACK);
    bool success;
    int fromX = 0,
	fromY = 7,
	toX = 2,
	toY = 7;

    p->notifyMoved();
    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveBlackWrongDirection)
{
   PiecePtr p = new Pawn(BLACK);
    bool success;
    int fromX = 2,
	fromY = 2,
	toX = 1,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveWhiteWrongDirection)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 2,
	fromY = 2,
	toX = 3,
	toY = 2;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveLeft)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveRight)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveUpRight)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveUpLeft)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 1,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveDownRight)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 5;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveDownLeft)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 5,
	toY = 1;

    chess.place(p, fromX, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveBlockedPathEndWhite)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 7,
	fromY = 7,
	toX = 6,
	toY = 7;

    chess.place(p, fromX, fromY);
    p = new Pawn(WHITE);
    chess.place(p, fromX - 1, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveBlockedPathEndBlack)
{
   PiecePtr p = new Pawn(BLACK);
    bool success;
    int fromX = 0,
	fromY = 0,
	toX = 1,
	toY = 0;

    chess.place(p, fromX, fromY);
    p = new Pawn(WHITE);
    chess.place(p, fromX + 1, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveBlockedPathEnRouteWhite)
{
   PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 7,
	fromY = 7,
	toX = 5,
	toY = 7;

    chess.place(p, fromX, fromY);
    p = new Pawn(WHITE);
    chess.place(p, fromX - 1, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveBlockedPathEnRouteBlack)
{
   PiecePtr p = new Pawn(BLACK);
    bool success;
    int fromX = 0,
	fromY = 0,
	toX = 2,
	toY = 0;

    chess.place(p, fromX, fromY);
    p = new Pawn(WHITE);
    chess.place(p, fromX + 1, fromY);
    
    success = p->canMove(chess, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testCanMoveWhiteCapture)
{
    PiecePtr p;
    bool success;

    p = new Pawn(BLACK);
    chess.place(p, 6, 6);
    p = new Pawn(WHITE);
    chess.place(p, 7, 7);

    success = p->canMove(chess, 7, 7, 6, 6);

    EXPECT_TRUE(success);
}

TEST_F(test_Pawn, testCanMoveBlackCapture)
{
    PiecePtr p;
    bool success;

    p = new Pawn(WHITE);
    chess.place(p, 1, 1);
    p = new Pawn(BLACK);
    chess.place(p, 0, 0);
    
    success = p->canMove(chess, 0, 0, 1, 1);

    EXPECT_TRUE(success);
}

//--------------------NOTIFY MOVED-------------------

TEST_F(test_Pawn, testNotifyMovedWhite)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    
    p->notifyMoved();

    chess.place(p, 7, 7);
    success = chess.move(WHITE, 7, 7, 5, 7);
    
    EXPECT_FALSE(success);
}

TEST_F(test_Pawn, testNotifyMovedBlack)
{
    PiecePtr p = new Pawn(BLACK);
    bool success;

    p->notifyMoved();
    
    chess.place(p, 0, 0);
    success = chess.move(BLACK, 0, 0, 2, 0);
    
    EXPECT_FALSE(success);
}


#endif
