/******************************************************************************
 Name: Matthew Stepan
 File name: test_Board.cpp
 ******************************************************************************/
#ifndef TESTBOARD_H
#define TESTBOARD_H

#include "Board.h"
#include "Piece.h"
#include "gtest/gtest.h"
#include <sstream>
#include <fstream>

class test_Board: public testing::Test
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

TEST_F(test_Board, testConstructor)
{
    int row,
	col;
    
    for(row = 0; row < MAXROWS; row++)
	for(col = 0; col < MAXCOLS; col++)
	    EXPECT_EQ(NULL, chess.getPiece(row, col));
}


//-------------------PLACE-------------------------------

TEST_F(test_Board, testPlaceXLessThan0)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int x = -1,
	y = 0;
       
    success = chess.place(p, x, y);
    
    EXPECT_FALSE(success);
    
    delete p;
}

TEST_F(test_Board, testPlaceXEqualMAXCOLS)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int x = MAXCOLS,
	y = 0;
       
    success = chess.place(p, x, y);

    EXPECT_FALSE(success);
    
    delete p;
}

TEST_F(test_Board, testPlaceXGreaterThanMAXCOLS)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int x = MAXCOLS + 1,
	y = 0;
       
    success = chess.place(p, x, y);

    EXPECT_FALSE(success);
    
    delete p;
}


TEST_F(test_Board, testPlaceYLessThan0)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int x = 0,
	y = -1;
       
    success = chess.place(p, x, y);

    EXPECT_FALSE(success);
    
    delete p;
}

TEST_F(test_Board, testPlaceYEqualMAXROWS)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int x = 0,
	y = MAXROWS;
       
    success = chess.place(p, x, y);

    EXPECT_FALSE(success);
    
    delete p;
}

TEST_F(test_Board, testPlaceYGreaterThanMAXROWS)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int x = 0,
	y = MAXROWS + 1;
       
    success = chess.place(p, x, y);

    EXPECT_FALSE(success);
    
    delete p;
}

TEST_F(test_Board, testPlaceUnoccupiedSquare)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int x = 1,
	y = 1;
       
    success = chess.place(p, x, y);

    EXPECT_TRUE(success);
}


TEST_F(test_Board, testPlaceOccupiedSquare)
{
    PiecePtr p1 = new Pawn(WHITE),
	p2 = new Pawn(WHITE);
    bool success;
    int x = 1,
	y = 1;
       
    chess.place(p1, x, y);
    success = chess.place(p2, x, y);
    
    EXPECT_FALSE(success);

    delete p2;
}

TEST_F(test_Board, testPlaceBeginningRow)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int x = 1,
	y = 0;
       
    success = chess.place(p, x, y);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testPlaceEndRow)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int x = 1,
	y = MAXROWS - 1;
       
    success = chess.place(p, x, y);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testPlaceBeginningCol)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int x = 0,
	y = 1;
       
    success = chess.place(p, x, y);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testPlaceEndCol)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int x = MAXCOLS - 1,
	y = 1;
       
    success = chess.place(p, x, y);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testPlaceCorner)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int x = 0,
	y = 0;
       
    success = chess.place(p, x, y);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testPlaceMultipleCorner)
{
    PiecePtr p1 = new Pawn(WHITE),
	p2 = new Pawn(WHITE),
	p3 = new Pawn(WHITE),
	p4 = new Pawn(WHITE);
    bool s1,
	s2,
	s3,
	s4;
       
    s1 = chess.place(p1, 0, 0);
    s2 = chess.place(p2, 0, MAXROWS - 1);
    s3 = chess.place(p3, MAXCOLS - 1, 0);
    s4 = chess.place(p4, MAXCOLS - 1, MAXROWS - 1);

    EXPECT_TRUE(s1);
    EXPECT_TRUE(s2);
    EXPECT_TRUE(s3);
    EXPECT_TRUE(s4);
}

TEST_F(test_Board, testPlaceMultipleLine)
{
    PiecePtr p1 = new Pawn(WHITE),
	p2 = new Pawn(WHITE),
	p3 = new Pawn(WHITE),
	p4 = new Pawn(WHITE);
    bool s1,
	s2,
	s3,
	s4;
       
    s1 = chess.place(p1, 0, 0);
    s2 = chess.place(p2, 0, 1);
    s3 = chess.place(p3, 0, 2);
    s4 = chess.place(p4, 0, 3);

    EXPECT_TRUE(s1);
    EXPECT_TRUE(s2);
    EXPECT_TRUE(s3);
    EXPECT_TRUE(s4);
}


TEST_F(test_Board, testPlaceMultipleSquare)
{
    PiecePtr p1 = new Pawn(WHITE),
	p2 = new Pawn(WHITE),
	p3 = new Pawn(WHITE),
	p4 = new Pawn(WHITE);
    bool s1,
	s2,
	s3,
	s4;
       
    s1 = chess.place(p1, 0, 0);
    s2 = chess.place(p2, 0, 1);
    s3 = chess.place(p3, 1, 0);
    s4 = chess.place(p4, 1, 1);

    EXPECT_TRUE(s1);
    EXPECT_TRUE(s2);
    EXPECT_TRUE(s3);
    EXPECT_TRUE(s4);
}

TEST_F(test_Board, testPlaceChessStart)
{
    PiecePtr p1 = new Pawn(WHITE),
	p2 = new Pawn(WHITE),
	p3 = new Pawn(WHITE),
	p4 = new Pawn(WHITE),
	p5 = new Pawn(WHITE),
	p6 = new Pawn(WHITE),
	p7 = new Pawn(WHITE),
	p8 = new Pawn(WHITE),
	p9 = new Pawn(WHITE),
	p10 = new Pawn(WHITE),
	p11 = new Pawn(WHITE),
	p12 = new Pawn(WHITE),
	p13 = new Pawn(WHITE),
	p14 = new Pawn(WHITE),
	p15 = new Pawn(WHITE),
	p16 = new Pawn(WHITE);
	
    bool s1,
	s2,
	s3,
	s4,
	s5,
	s6,
	s7,
	s8,
	s9,
	s10,
	s11,
	s12,
	s13,
	s14,
	s15,
	s16;
	       
    s1 = chess.place(p1, 0, 0);
    s2 = chess.place(p2, 1, 0);
    s3 = chess.place(p3, 2, 0);
    s4 = chess.place(p4, 3, 0);
    s5 = chess.place(p5, 4, 0);
    s6 = chess.place(p6, 5, 0);
    s7 = chess.place(p7, 6, 0);
    s8 = chess.place(p8, 7, 0);
    s9 = chess.place(p9, 0, 1);
    s10 = chess.place(p10, 1, 1);
    s11 = chess.place(p11, 2, 1);
    s12 = chess.place(p12, 3, 1);
    s13 = chess.place(p13, 4, 1);
    s14 = chess.place(p14, 5, 1);
    s15 = chess.place(p15, 6, 1);
    s16 = chess.place(p16, 7, 1);

    EXPECT_TRUE(s1);
    EXPECT_TRUE(s2);
    EXPECT_TRUE(s3);
    EXPECT_TRUE(s4);
    EXPECT_TRUE(s5);
    EXPECT_TRUE(s6);
    EXPECT_TRUE(s7);
    EXPECT_TRUE(s8);
    EXPECT_TRUE(s9);
    EXPECT_TRUE(s10);
    EXPECT_TRUE(s11);
    EXPECT_TRUE(s12);
    EXPECT_TRUE(s13);
    EXPECT_TRUE(s14);
    EXPECT_TRUE(s15);
    EXPECT_TRUE(s16);
}

//-------------------GET PIECE---------------------------

TEST_F(test_Board, testGetPieceNULL)
{
    int x = 0,
	y = 0;
    PiecePtr get;
    
    get = chess.getPiece(x, y);

    EXPECT_EQ(NULL, get);
}

TEST_F(test_Board, testGetPieceXLessThan0)
{
    int x = -1,
	y = 0;
    PiecePtr get;

    get = chess.getPiece(x, y);

    EXPECT_EQ(NULL, get);
}

TEST_F(test_Board, testGetPieceXEqualMAXCOLS)
{
    int x = MAXCOLS,
	y = 0;
    PiecePtr get;

    get = chess.getPiece(x, y);

    EXPECT_EQ(NULL, get);
}

TEST_F(test_Board, testGetPieceXGreaterThanMAXCOLS)
{
    int x = MAXCOLS + 1,
	y = 0;
    PiecePtr get;

    get = chess.getPiece(x, y);

    EXPECT_EQ(NULL, get);
}

TEST_F(test_Board, testGetPieceYLessThan0)
{
    int x = 0,
	y = -1;
    PiecePtr get;

    get = chess.getPiece(x, y);

    EXPECT_EQ(NULL, get);
}

TEST_F(test_Board, testGetPieceYEqualMAXROWS)
{
    int x = 0,
	y = MAXROWS;
    PiecePtr get;

    get = chess.getPiece(x, y);

    EXPECT_EQ(NULL, get);
}

TEST_F(test_Board, testGetPieceYGreaterThanMAXROWS)
{
    int x = 0,
	y = MAXROWS + 1;
    PiecePtr get;

    get = chess.getPiece(x, y);

    EXPECT_EQ(NULL, get);
}

TEST_F(test_Board, testGetPieceNotNULL)
{
    //No way to test in this phase, as a Piece has no values to
    //get and compare between the original and the copy returned
    //by the function
}

//----------------------isOccupied---------------------------

TEST_F(test_Board, testIsOccupiedYes)
{
    bool occupied;
    PiecePtr p = new Pawn(WHITE);

    chess.place(p, 0, 0);
    
    occupied = chess.isOccupied(0, 0);

    EXPECT_TRUE(occupied);
}

TEST_F(test_Board, testIsOccupiedNo)
{
    bool occupied;
    
    occupied = chess.isOccupied(0, 0);

    EXPECT_FALSE(occupied);
}

//----------------------REMOVE--------------------------
TEST_F(test_Board, testRemoveEmpty)
{
    bool success;
    int x = 0,
	y = 0;
    
    success = chess.remove(x, y);

    EXPECT_FALSE(success);
 }

TEST_F(test_Board, testRemoveXLessThan0)
{
    bool success;
    int x = -1,
	y = 0;

    success = chess.remove(x, y);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testRemoveXEqualMAXCOLS)
{
    bool success;
    int x = MAXCOLS,
	y = 0;

    success = chess.remove(x, y);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testRemoveXGreaterThanMAXCOLS)
{
    bool success;
    int x = MAXCOLS + 1,
	y = 0;

    success = chess.remove(x, y);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testRemoveYLessThan0)
{
    bool success;
    int x = 0,
	y = -1;

    success = chess.remove(x, y);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testRemoveYEqualMAXROWS)
{
    bool success;
    int x = 0,
	y = MAXROWS;

    success = chess.remove(x, y);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testRemoveYGreaterThanMAXROWS)
{
    bool success;
    int x = 0,
	y = MAXROWS + 1;

    success = chess.remove(x, y);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testRemoveSingle)
{
    bool success;
    PiecePtr p = new Pawn(WHITE);
    int x = 1,
	y = 1;
    
    chess.place(p, x, y);
    success = chess.remove(x, y);

    EXPECT_TRUE(success);
 }

TEST_F(test_Board, testRemoveRowStart)
{
    bool success;
    PiecePtr p = new Pawn(WHITE);
    int x = 1,
	y = 0;
    
    chess.place(p, x, y);
    success = chess.remove(x, y);

    EXPECT_TRUE(success);
 }

TEST_F(test_Board, testRemoveRowEnd)
{
    bool success;
    PiecePtr p = new Pawn(WHITE);
    int x = 1,
	y = MAXROWS - 1;
    
    chess.place(p, x, y);
    success = chess.remove(x, y);

    EXPECT_TRUE(success);
 }

TEST_F(test_Board, testRemoveColStart)
{
    bool success;
    PiecePtr p = new Pawn(WHITE);
    int x = 0,
	y = 1;
    
    chess.place(p, x, y);
    success = chess.remove(x, y);

    EXPECT_TRUE(success);
 }

TEST_F(test_Board, testRemoveColEnd)
{
    bool success;
    PiecePtr p = new Pawn(WHITE);
    int x = MAXCOLS - 1,
	y = 1;
    
    chess.place(p, x, y);
    success = chess.remove(x, y);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testRemoveCorner)
{
    bool success;
    PiecePtr p = new Pawn(WHITE);
    int x = 0,
	y = 0;
    
    chess.place(p, x, y);
    success = chess.remove(x, y);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testRemoveMultipleCorners)
{
    PiecePtr p1 = new Pawn(WHITE),
	p2 = new Pawn(WHITE),
	p3 = new Pawn(WHITE),
	p4 = new Pawn(WHITE);
    bool s1,
	s2,
	s3,
	s4;
       
    chess.place(p1, 0, 0);
    chess.place(p2, 0, MAXROWS - 1);
    chess.place(p3, MAXCOLS - 1, 0);
    chess.place(p4, MAXCOLS - 1, MAXROWS - 1);
    
    s1 = chess.remove(0, 0);
    s2 = chess.remove(0, MAXROWS -1);
    s3 = chess.remove(MAXCOLS - 1, 0);
    s4 = chess.remove(MAXCOLS - 1, MAXROWS - 1);

    EXPECT_TRUE(s1);
    EXPECT_TRUE(s2);
    EXPECT_TRUE(s3);
    EXPECT_TRUE(s4);
}


TEST_F(test_Board, testRemoveMultipleLine)
{
    PiecePtr p1 = new Pawn(WHITE),
	p2 = new Pawn(WHITE),
	p3 = new Pawn(WHITE),
	p4 = new Pawn(WHITE);
    bool s1,
	s2,
	s3,
	s4;
       
    chess.place(p1, 0, 0);
    chess.place(p2, 0, 1);
    chess.place(p3, 0, 2);
    chess.place(p4, 0, 3);
    
    s1 = chess.remove(0, 0);
    s2 = chess.remove(0, 1);
    s3 = chess.remove(0, 2);
    s4 = chess.remove(0, 3);

    EXPECT_TRUE(s1);
    EXPECT_TRUE(s2);
    EXPECT_TRUE(s3);
    EXPECT_TRUE(s4);
}

TEST_F(test_Board, testRemoveMultipleSquare)
{
    PiecePtr p1 = new Pawn(WHITE),
	p2 = new Pawn(WHITE),
	p3 = new Pawn(WHITE),
	p4 = new Pawn(WHITE);
    bool s1,
	s2,
	s3,
	s4;
       
    chess.place(p1, 0, 0);
    chess.place(p2, 0, 1);
    chess.place(p3, 1, 0);
    chess.place(p4, 1, 1);

    s1 = chess.remove(0, 0);
    s2 = chess.remove(0, 1);
    s3 = chess.remove(1, 0);
    s4 = chess.remove(1, 1);

    EXPECT_TRUE(s1);
    EXPECT_TRUE(s2);
    EXPECT_TRUE(s3);
    EXPECT_TRUE(s4);
}


//----------------------DESTRUCTOR-----------------------

TEST_F(test_Board, testDestructor)
{
    Board* destroyMe = new Board;
    PiecePtr p1 = new Pawn(WHITE);
    char out[6],
	compare[] = "P 0 0";
    ifstream destructTxt;
    
    destroyMe->place(p1, 0, 0);
    delete destroyMe;
    
    destructTxt.open("final_board.txt");
    if(!destructTxt.fail())
    {
	destructTxt.getline(out, 6,'\n');
	EXPECT_STREQ(out, compare);
	destructTxt.close();
    }
}

//-----------------------WRITE-----------------------------

TEST_F(test_Board, testWriteEmpty)
{
    stringstream out,
	emptyBoard;

    emptyBoard << "    0   1   2   3   4   5   6   7   \n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "0 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "1 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "2 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "3 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "4 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "5 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "6 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "7 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
  
    chess.write(out);
    
    EXPECT_EQ(emptyBoard.str(), out.str());
}

TEST_F(test_Board, testWriteWhite)
{
    stringstream out,
	emptyBoard;
    PiecePtr p = new Pawn(WHITE);

    chess.place(p, 2, 2);    

    emptyBoard << "    0   1   2   3   4   5   6   7   \n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "0 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "1 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "2 |   |   | P |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "3 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "4 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "5 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "6 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "7 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
  
    chess.write(out);
    
    EXPECT_EQ(emptyBoard.str(), out.str());
}

TEST_F(test_Board, testWriteBlack)
{
    stringstream out,
	emptyBoard;
    PiecePtr p = new Pawn(BLACK);
    
    chess.place(p, 2, 2);    
    
    emptyBoard << "    0   1   2   3   4   5   6   7   \n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "0 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "1 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "2 |   |   | p |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "3 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "4 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "5 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "6 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";
    emptyBoard << "7 |   |   |   |   |   |   |   |   |\n";
    emptyBoard << "  +---+---+---+---+---+---+---+---+\n";

    chess.write(out);
    
    EXPECT_EQ(emptyBoard.str(), out.str());
}

TEST_F(test_Board, testWriteBlackAndWhite)
{
    stringstream out,
	randomBoard;
    PiecePtr p;

    p = new Pawn(BLACK);
    chess.place(p, 0, 0);
    p = new Pawn(WHITE);
    chess.place(p, 1, 2);
    p = new Pawn(WHITE);
    chess.place(p, 5, 4);
    p = new Pawn(BLACK);
    chess.place(p, 6, 6);
    
    randomBoard << "    0   1   2   3   4   5   6   7   \n";
    randomBoard << "  +---+---+---+---+---+---+---+---+\n";
    randomBoard << "0 | p |   |   |   |   |   |   |   |\n";
    randomBoard << "  +---+---+---+---+---+---+---+---+\n";
    randomBoard << "1 |   |   | P |   |   |   |   |   |\n";
    randomBoard << "  +---+---+---+---+---+---+---+---+\n";
    randomBoard << "2 |   |   |   |   |   |   |   |   |\n";
    randomBoard << "  +---+---+---+---+---+---+---+---+\n";
    randomBoard << "3 |   |   |   |   |   |   |   |   |\n";
    randomBoard << "  +---+---+---+---+---+---+---+---+\n";
    randomBoard << "4 |   |   |   |   |   |   |   |   |\n";
    randomBoard << "  +---+---+---+---+---+---+---+---+\n";
    randomBoard << "5 |   |   |   |   | P |   |   |   |\n";
    randomBoard << "  +---+---+---+---+---+---+---+---+\n";
    randomBoard << "6 |   |   |   |   |   |   | p |   |\n";
    randomBoard << "  +---+---+---+---+---+---+---+---+\n";
    randomBoard << "7 |   |   |   |   |   |   |   |   |\n";
    randomBoard << "  +---+---+---+---+---+---+---+---+\n";
  
    chess.write(out);
    
    EXPECT_EQ(randomBoard.str(), out.str());
}


TEST_F(test_Board, testWriteFullBoard)
{
    stringstream out,
	fullBoard;
    PiecePtr p;
    int row,
	col;

    for(row = 0; row < MAXROWS; row++)
	for(col = 0; col < MAXCOLS; col++)
	{
	    p = new Pawn(WHITE);
	    chess.place(p, row, col);
	}
	    
    fullBoard << "    0   1   2   3   4   5   6   7   \n";
    fullBoard << "  +---+---+---+---+---+---+---+---+\n";
    fullBoard << "0 | P | P | P | P | P | P | P | P |\n";
    fullBoard << "  +---+---+---+---+---+---+---+---+\n";
    fullBoard << "1 | P | P | P | P | P | P | P | P |\n";
    fullBoard << "  +---+---+---+---+---+---+---+---+\n";
    fullBoard << "2 | P | P | P | P | P | P | P | P |\n";
    fullBoard << "  +---+---+---+---+---+---+---+---+\n";
    fullBoard << "3 | P | P | P | P | P | P | P | P |\n";
    fullBoard << "  +---+---+---+---+---+---+---+---+\n";
    fullBoard << "4 | P | P | P | P | P | P | P | P |\n";
    fullBoard << "  +---+---+---+---+---+---+---+---+\n";
    fullBoard << "5 | P | P | P | P | P | P | P | P |\n";
    fullBoard << "  +---+---+---+---+---+---+---+---+\n";
    fullBoard << "6 | P | P | P | P | P | P | P | P |\n";
    fullBoard << "  +---+---+---+---+---+---+---+---+\n";
    fullBoard << "7 | P | P | P | P | P | P | P | P |\n";
    fullBoard << "  +---+---+---+---+---+---+---+---+\n";
  
    chess.write(out);
    
    EXPECT_EQ(fullBoard.str(), out.str());
}

TEST_F(test_Board, testWriteChessStart)
{
    stringstream out,
	chessStart;
    PiecePtr p;
    int row,
	col;

    for(row = 0; row < MAXROWS; row++)
    {
	if(row == 0 || row == 1)
	{
	    for(col = 0; col < MAXCOLS; col++)
	    {
		p = new Pawn(BLACK);
		chess.place(p, row, col);
	    }
	}
	else if(row == 6 || row == 7)
	{
	    for(col = 0; col < MAXCOLS; col++)
	    {
		p = new Pawn(WHITE);
		chess.place(p, row, col);
	    }
	}
    }
    
    chessStart << "    0   1   2   3   4   5   6   7   \n";
    chessStart << "  +---+---+---+---+---+---+---+---+\n";
    chessStart << "0 | p | p | p | p | p | p | p | p |\n";
    chessStart << "  +---+---+---+---+---+---+---+---+\n";
    chessStart << "1 | p | p | p | p | p | p | p | p |\n";
    chessStart << "  +---+---+---+---+---+---+---+---+\n";
    chessStart << "2 |   |   |   |   |   |   |   |   |\n"; 
    chessStart << "  +---+---+---+---+---+---+---+---+\n";
    chessStart << "3 |   |   |   |   |   |   |   |   |\n"; 
    chessStart << "  +---+---+---+---+---+---+---+---+\n";
    chessStart << "4 |   |   |   |   |   |   |   |   |\n"; 
    chessStart << "  +---+---+---+---+---+---+---+---+\n";
    chessStart << "5 |   |   |   |   |   |   |   |   |\n"; 
    chessStart << "  +---+---+---+---+---+---+---+---+\n";
    chessStart << "6 | P | P | P | P | P | P | P | P |\n";
    chessStart << "  +---+---+---+---+---+---+---+---+\n";
    chessStart << "7 | P | P | P | P | P | P | P | P |\n";
    chessStart << "  +---+---+---+---+---+---+---+---+\n";
  
    chess.write(out);

    EXPECT_EQ(chessStart.str(), out.str());
}

//-----------------------Overloaded << Operator----------------

TEST_F(test_Board, testOverloadedRedirection)
{
    stringstream overloadOut,
	writeOut;
    PiecePtr p;

    p = new Pawn(WHITE);
    chess.place(p, 0, 0);
    p = new Pawn(WHITE);
    chess.place(p, 1, 2);
    p = new Pawn(WHITE);
    chess.place(p, 5, 4);
    p = new Pawn(WHITE);
    chess.place(p, 6, 6);

    overloadOut << chess;
    chess.write(writeOut);

    EXPECT_EQ(overloadOut.str(), writeOut.str());
}

//----------------------COPY CONSTRUCTOR------------------------

TEST_F(test_Board, testCopyConstructorEmpty)
{
    stringstream chessOut,
	copyOut;
    Board copyChess = chess;

    chessOut << chess;
    copyOut << copyChess;

    EXPECT_EQ(chessOut.str(), copyOut.str());
}

TEST_F(test_Board, testCopyConstructorRandom)
{
    stringstream chessOut,
	copyOut;
    PiecePtr p;
    
    p = new Pawn(WHITE);
    chess.place(p, 0, 0);
    p = new Pawn(WHITE);
    chess.place(p, 1, 2);
    p = new Pawn(WHITE);
    chess.place(p, 5, 4);
    p = new Pawn(WHITE);
    chess.place(p, 6, 6);
   
    Board copyChess = chess;

    chessOut << chess;
    copyOut << copyChess;

    EXPECT_EQ(chessOut.str(), copyOut.str());
}

TEST_F(test_Board, testCopyConstructorFullBoard)
{
    stringstream chessOut,
	copyOut;
    PiecePtr p;
    int row,
	col;

    for(row = 0; row < MAXROWS; row++)
	for(col = 0; col < MAXCOLS; col++)
	{
	    p = new Pawn(WHITE);
	    chess.place(p, col, row);
	}
   
    Board copyChess = chess;
    
    chessOut << chess;
    copyOut << copyChess;

    EXPECT_EQ(chessOut.str(), copyOut.str());
}

//-----------------OVERLOADED =----------------------
TEST_F(test_Board, testOverloadedAssignmentIdentical)
{
    PiecePtr p = new Pawn(WHITE),
	get;
    int x = 0,
	y = 0;
    bool pieceReturned;

    chess.place(p, x, y);
    chess = chess;

    get = chess.getPiece(x, y);
    if(get == NULL)
	pieceReturned = false;
    else
	pieceReturned = true;

    EXPECT_TRUE(pieceReturned);
    
    delete get;
}

TEST_F(test_Board, testOverloadedAssignmentEmpty)
{
    Board other;
    stringstream chessOut,
	otherOut;
    
    other = chess;
    
    otherOut << other;
    chessOut << chess;

    EXPECT_EQ(chessOut.str(), otherOut.str());
}


TEST_F(test_Board, testOverloadedAssignmentRandom)
{
    Board other;
    PiecePtr p;
    stringstream chessOut,
	otherOut;

    p = new Pawn(WHITE);
    chess.place(p, 0, 0);
    p = new Pawn(WHITE);
    chess.place(p, 1, 2);
    p = new Pawn(WHITE);
    chess.place(p, 5, 4);
    p = new Pawn(WHITE);
    chess.place(p, 6, 6);
    
    other = chess;

    otherOut << other;
    chessOut << chess;

    EXPECT_EQ(chessOut.str(), otherOut.str());
}

TEST_F(test_Board, testOverloadedAssignmentFullBoard)
{
    Board other;
    PiecePtr p;
    stringstream chessOut,
	otherOut;
    int row,
	col;

    for(row = 0; row < MAXROWS; row++)
	for(col = 0; col < MAXCOLS; col++)
	{
	    p = new Pawn(WHITE);
	    chess.place(p, col, row);
	}
    
    other = chess;

    otherOut << other;
    chessOut << chess;

    EXPECT_EQ(chessOut.str(), otherOut.str());
}

//--------------------MOVE-----------------------------------
TEST_F(test_Board, testMoveFromEmpty)
{
    bool success;
    int fromX = 0,
	fromY = 0,
	toX = 1,
	toY = 1;

    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveToEmpty)
{
    PiecePtr p1 = new Pawn(WHITE),
	p2 = new Pawn(WHITE);
    bool success;
    int fromX = 0,
	fromY = 0,
	toX = 1,
	toY = 1;

    chess.place(p1, fromX, fromY);
    chess.place(p2, toX, toY);
    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveToStartingLocation)
{
    PiecePtr p1 = new Pawn(WHITE);
    bool success;
    int fromX = 0,
	fromY = 0,
	toX = 0,
	toY = 0;

    chess.place(p1, fromX, fromY);
    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveFromXLessThan0)
{
    bool success;
    int fromX = -1,
	fromY = 0,
	toX = 1,
	toY = 1;

    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveFromXEqualMAXROWS)
{
    bool success;
    int fromX = MAXROWS,
	fromY = 0,
	toX = 1,
	toY = 1;

    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveFromXGreaterThanMAXROWS)
{
    bool success;
    int fromX = MAXROWS + 1,
	fromY = 0,
	toX = 1,
	toY = 1;
    
    success = chess.move(WHITE, fromX, fromY, toX, toY);
    
    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveFromYLessThan0)
{
    bool success;
    int fromX = 0,
	fromY = -1,
	toX = 1,
	toY = 1;

    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveFromYEqualMAXCOLS)
{
    bool success;
    int fromX = 0,
	fromY = MAXCOLS,
	toX = 1,
	toY = 1;

    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveFromYGreaterThanMAXCOLS)
{
    bool success;
    int fromX = 0,
	fromY = MAXROWS + 1,
	toX = 1,
	toY = 1;

    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveToXLessThan0)
{
    bool success;
    int fromX = 0,
	fromY = 0,
	toX = -1,
	toY = 1;

    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveToXEqualMAXROWS)
{
    bool success;
    int fromX = 0,
	fromY = 0,
	toX = MAXROWS,
	toY = 1;

    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveToXGreaterThanMAXROWS)
{
    bool success;
    int fromX = 0,
	fromY = 0,
	toX = MAXROWS + 1,
	toY = 1;
    
    success = chess.move(WHITE, fromX, fromY, toX, toY);
    
    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveToYLessThan0)
{
    bool success;
    int fromX = 0,
	fromY = 0,
	toX = 1,
	toY = -1;

    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveToYEqualMAXCOLS)
{
    bool success;
    int fromX = 0,
	fromY = 0,
	toX = 1,
	toY = MAXCOLS;

    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveToYGreaterThanMAXCOLS)
{
    bool success;
    int fromX = 0,
	fromY = 0,
	toX = 1,
	toY = MAXROWS + 1;

    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveLeft)
{
    PiecePtr p1 = new Pawn(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 2;

    chess.place(p1, fromX, fromY);
    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveRight)
{
    PiecePtr p1 = new Pawn(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 3,
	toY = 4;

    chess.place(p1, fromX, fromY);
    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveDiagonal)
{
    PiecePtr p1 = new Pawn(WHITE);
    bool success;
    int fromX = 3,
	fromY = 3,
	toX = 4,
	toY = 4;

    chess.place(p1, fromX, fromY);
    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveToRowStart)
{
    PiecePtr p1 = new Pawn(WHITE);
    bool success;
    int fromX = 1,
	fromY = 1,
	toX = 0,
	toY = 1;

    chess.place(p1, fromX, fromY);
    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testMoveToRowEnd)
{
    PiecePtr p1 = new Pawn(BLACK);
    bool success;
    int fromX = 6,
	fromY = 6,
	toX = 7,
	toY = 6;

    chess.place(p1, fromX, fromY);
    success = chess.move(BLACK, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testMoveFromRowStart)
{
    PiecePtr p1 = new Pawn(BLACK);
    bool success;
    int fromX = 0,
	fromY = 1,
	toX = 1,
	toY = 1;

    chess.place(p1, fromX, fromY);
    success = chess.move(BLACK, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testMoveFromRowEnd)
{
    PiecePtr p1 = new Pawn(WHITE);
    bool success;
    int fromX = 7,
	fromY = 6,
	toX = 6,
	toY = 6;

    chess.place(p1, fromX, fromY);
    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testMoveToColStart)
{
    PiecePtr p1 = new Pawn(WHITE);
    bool success;
    int fromX = 1,
	fromY = 1,
	toX = 0,
	toY = 1;

    chess.place(p1, fromX, fromY);
    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testMoveToCorner)
{
    PiecePtr p1 = new Pawn(WHITE);
    bool success;
    int fromX = 1,
	fromY = 0,
	toX = 0,
	toY = 0;

    chess.place(p1, fromX, fromY);
    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testMoveFromCorner)
{
    PiecePtr p1 = new Pawn(WHITE);
    bool success;
    int fromX = 7,
	fromY = 7,
	toX = 6,
	toY = 7;

    chess.place(p1, fromX, fromY);
    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testMoveToAdjacent)
{
    PiecePtr p1 = new Pawn(BLACK),
	p2 = new Pawn(WHITE);
    bool success;

    chess.place(p1, 0, 0);
    chess.place(p2, 1, 1);
    success = chess.move(BLACK, 0, 0, 1, 0);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testMoveFromAdjacent)
{
    PiecePtr p1 = new Pawn(BLACK),
	p2 = new Pawn(WHITE);
    bool success;

    chess.place(p1, 0, 0);
    chess.place(p2, 0, 1);
    success = chess.move(BLACK, 0, 0, 1, 0);

    EXPECT_TRUE(success);
}

TEST_F(test_Board, testMoveMultipleTimes)
{
    PiecePtr p1 = new Pawn(WHITE);
    bool s1,
	s2,
	s3;
    
    chess.place(p1, 7, 7);

    s1 = chess.move(WHITE, 7, 7, 5, 7);
    s2 = chess.move(WHITE, 5, 7, 4, 7);
    s3 = chess.move(WHITE, 4, 7, 3, 7);
    
    EXPECT_TRUE(s1);
    EXPECT_TRUE(s2);
    EXPECT_TRUE(s3);
}

TEST_F(test_Board, testMoveMultiplePieces)
{
    PiecePtr p1 = new Pawn(BLACK),
	p2 = new Pawn(WHITE),
	p3 = new Pawn(WHITE);
    bool s1,
	s2,
	s3;
    
    chess.place(p1, 0, 0);
    chess.place(p2, 1, 1);
    chess.place(p3, 2, 2);
    
    s1 = chess.move(BLACK, 0, 0, 2, 0);
    s2 = chess.move(WHITE, 1, 1, 0, 1);
    s3 = chess.move(WHITE, 2, 2, 0, 2);
    
    EXPECT_TRUE(s1);
    EXPECT_TRUE(s2);
    EXPECT_TRUE(s3);
}

TEST_F(test_Board, testMoveBlackMoveWhite)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 7,
	fromY = 7,
	toX = 5,
	toY = 7;

    chess.place(p, fromX, fromY);
    
    success = chess.move(BLACK, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveWhiteMoveBlack)
{
    PiecePtr p = new Pawn(BLACK);
    bool success;
    int fromX = 7,
	fromY = 7,
	toX = 5,
	toY = 7;

    chess.place(p, fromX, fromY);
    
    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testMoveCapture)
{
    PiecePtr p = new Pawn(WHITE);
    bool success;
    int fromX = 7,
	fromY = 7,
	toX = 6,
	toY = 6;

    chess.place(p, fromX, fromY);
    p = new King(BLACK);
    chess.place(p, toX, toY);

    success = chess.move(WHITE, fromX, fromY, toX, toY);

    EXPECT_TRUE(success);
}

//-----------------------------KING CAPTURE----------------------------------

TEST_F(test_Board, testKingCaptureNoCapture)
{
    PiecePtr p;
    bool success,
	winner;

    p = new King(BLACK);
    chess.place(p, 1, 1);
    p = new King(WHITE);
    chess.place(p, 0, 0);

    success = chess.kingCapture(winner);

    EXPECT_FALSE(success);
}

TEST_F(test_Board, testKingCaptureBlackWins)
{
    PiecePtr p;
    bool success,
	winner;

    p = new King(BLACK);
    chess.place(p, 1, 1);

    success = chess.kingCapture(winner);

    EXPECT_TRUE(success);
    EXPECT_EQ(BLACK, winner);
}

TEST_F(test_Board, testKingCaptureWhiteWins)
{
    PiecePtr p;
    bool success,
	winner;

    p = new King(WHITE);
    chess.place(p, 1, 1);

    success = chess.kingCapture(winner);

    EXPECT_TRUE(success);
    EXPECT_EQ(WHITE, winner);
}


#endif
