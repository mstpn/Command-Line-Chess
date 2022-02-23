TARGET=game

MODULES=Piece.o Board.o game.o ioutil.o Pawn.o Rook.o Bishop.o Queen.o King.o Knight.o
TESTMODS=test_All.o Board.o Piece.o Pawn.o Rook.o Bishop.o Queen.o King.o Knight.o

CPPFLAGS=-ansi -pedantic-errors -Wall -Wconversion
GCOVFLAGS=-fprofile-arcs -ftest-coverage
#GTFLAGS=-lgtest -lgtest_main
TESTS=test_All
GCOVFILE1=Board
GCOVFILE2=Piece
GCOVFILE3=Pawn
GCOVFILE4=Rook
GCOVFILE5=Bishop
GCOVFILE6=Queen
GCOVFILE7=King
GCOVFILE8=Knight


$(TARGET): $(MODULES)
	g++ $(GTFLAGS) $(MODULES) $(GCOVFLAGS) -o $(TARGET)

$(TESTS): test_All.o test_All.h 
	g++ $(TESTMODS) $(GTFLAGS) $(GCOVFLAGS) -o $(TESTS)

chess: $(MODULES) game.o
	g++ $(GTFLAGS) $(MODULES) game.o $(GCOVFLAGS) -o game

clean:
	/bin/rm -f *~ *.o *# $(TARGET) $(TESTS) *.gcda *.gcov *.gcno *.txt

all: clean $(TARGET) $(TESTS)
	$(TESTS)
	gcov $(GCOVFILE1).cpp 2> /dev/null | grep -A 1 $(GCOVFILE1).cpp
	gcov $(GCOVFILE2).cpp 2> /dev/null | grep -A 1 $(GCOVFILE2).cpp
	gcov $(GCOVFILE3).cpp 2> /dev/null | grep -A 1 $(GCOVFILE3).cpp
	gcov $(GCOVFILE4).cpp 2> /dev/null | grep -A 1 $(GCOVFILE4).cpp
	gcov $(GCOVFILE5).cpp 2> /dev/null | grep -A 1 $(GCOVFILE5).cpp
	gcov $(GCOVFILE6).cpp 2> /dev/null | grep -A 1 $(GCOVFILE6).cpp
	gcov $(GCOVFILE7).cpp 2> /dev/null | grep -A 1 $(GCOVFILE7).cpp
	gcov $(GCOVFILE8).cpp 2> /dev/null | grep -A 1 $(GCOVFILE8).cpp

Piece.o: Piece.cpp Piece.h Board.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c Piece.cpp

Pawn.o: Pawn.cpp Piece.h Board.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c Pawn.cpp

King.o: King.cpp Piece.h Board.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c King.cpp

Queen.o: Queen.cpp Piece.h Board.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c Queen.cpp

Rook.o: Rook.cpp Piece.h Board.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c Rook.cpp

Bishop.o: Bishop.cpp Piece.h Board.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c Bishop.cpp

Knight.o: Knight.cpp Piece.h Board.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c Knight.cpp

Board.o: Board.cpp Board.h Piece.h 
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c Board.cpp

game.o: game.cpp Piece.h Board.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c game.cpp

test_All.o: test_All.cpp Piece.h Board.h $(MODULES)
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c test_All.cpp

ioutil.o: ioutil.cpp ioutil.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c ioutil.cpp
