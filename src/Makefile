# Variables
CC	= gcc -g
DEBUG	= -DDEBUG=1 -g
CFLAGS	= -Wall -std=c11 -c
LFLAGS	= -Wall

# Default target
all: ChessGame

######################### Generate object files #######################
# Target for MovieLab.o
Piece.o: Piece.c Piece.h
	$(CC) $(CFLAGS) -lm Piece.c -o Piece.o
Board.o: Board.c Board.h
	$(CC) $(CFLAGS) Board.c -o Board.o
Chess.o: Chess.c
	$(CC) $(CFLAGS) Chess.c -o Chess.o
Moves.o: Moves.c Moves.h
	$(CC) $(CFLAGS) Moves.c -o Moves.o


# Target for FileIO.o
# FileIO.o: FileIO.c FileIO.h Constants.h
# 	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

######################### Generate the executable #####################
# Target for MovieLab
ChessGame: Chess.o Piece.o Board.o Moves.o	
	$(CC) Chess.o Piece.o Board.o Moves.o -o ChessGame
	mv ChessGame ../bin/ChessGame 

######################### Generate archive ############################
tar:
	

###############################  others  ##############################
# Target for clean-up
clean: 
	rm -f *.o
	rm -f ChessGame
# Target for making .o Files
ofiles: Piece.o Chess.o Board.o Moves.o
#Target to enable -std=c11
enableCC:
	scl enable devtoolset-7 tcsh

