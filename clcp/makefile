# You can build the project just by running `make`. The application can be run with `./game`.
TARGET=game

MODULES=Piece.o Board.o game.o ioutil.o Pawn.o Rook.o Bishop.o Queen.o King.o Knight.o zHandler.o zTransposition.o zSearch.o

CPPFLAGS=-ansi -pedantic-errors -Wall -Wconversion -g 
VERSIONFLAGS=-std=c++2a 


$(TARGET): $(MODULES)
	g++ $(MODULES) -o $(TARGET)

chess: $(MODULES) game.o
	g++ $(MODULES) game.o -o game

clean:
	/bin/rm -f *~ *.o *# $(TARGET) *.txt

all: clean $(TARGET)

Piece.o: Piece.cpp Piece.h Board.h
	g++ $(CPPFLAGS) -c Piece.cpp

Pawn.o: Pawn.cpp Piece.h Board.h
	g++ $(CPPFLAGS) -c Pawn.cpp

King.o: King.cpp Piece.h Board.h
	g++ $(CPPFLAGS) -c King.cpp

Queen.o: Queen.cpp Piece.h Board.h
	g++ $(CPPFLAGS) -c Queen.cpp

Rook.o: Rook.cpp Piece.h Board.h
	g++ $(CPPFLAGS) -c Rook.cpp

Bishop.o: Bishop.cpp Piece.h Board.h
	g++ $(CPPFLAGS) -c Bishop.cpp

Knight.o: Knight.cpp Piece.h Board.h
	g++ $(CPPFLAGS) -c Knight.cpp

Board.o: Board.cpp Board.h Piece.h 
	g++ $(CPPFLAGS) -c Board.cpp

game.o: game.cpp Piece.h Board.h
	g++ $(CPPFLAGS) -c -std=c++11 game.cpp

ioutil.o: ioutil.cpp ioutil.h
	g++ $(CPPFLAGS) -c ioutil.cpp

########################### New Files #####################################

zHandler.o: zHandler.cpp zHandler.h Board.h
	g++ $(CPPFLAGS) $(VERSIONFLAGS) -c zHandler.cpp

zTransposition.o: zTransposition.cpp zTransposition.h
	g++ $(CPPFLAGS) $(VERSIONFLAGS) -c zTransposition.cpp

zSearch.o: zSearch.cpp zSearch.h Board.h
	g++ $(CPPFLAGS) $(VERSIONFLAGS) -c zSearch.cpp
