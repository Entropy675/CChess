
PATH2SRC = src/
PATH2OBJ = obj/

OBJ = $(PATH2OBJ)ChessGame.o $(PATH2OBJ)Pos.o $(PATH2OBJ)MoveBehaviour.o $(PATH2OBJ)PawnMove.o $(PATH2OBJ)KingMove.o $(PATH2OBJ)KnightMove.o $(PATH2OBJ)PlusMove.o $(PATH2OBJ)CrossMove.o $(PATH2OBJ)Piece.o $(PATH2OBJ)Board.o $(PATH2OBJ)View.o $(PATH2OBJ)Log.o $(PATH2OBJ)NcView.o $(PATH2OBJ)Bitboard.o
CC = g++ -Wall -g
LIB = -lncursesw

# main is kept seperate for the testing makefile
CChess:	$(OBJ) $(PATH2OBJ)main.o
	$(CC) -o CChess $(OBJ) $(LIB) $(PATH2OBJ)main.o 

$(PATH2OBJ)ChessGame.o: $(PATH2SRC)ChessGame.cc $(PATH2SRC)ChessGame.h $(PATH2SRC)Log.h $(PATH2SRC)Board.h $(PATH2SRC)NcView.h $(PATH2SRC)defs.h $(PATH2SRC)MoveBehaviour.h
	$(CC) -c $(PATH2SRC)ChessGame.cc -o $(PATH2OBJ)ChessGame.o

$(PATH2OBJ)main.o: $(PATH2SRC)main.cc $(PATH2OBJ)ChessGame.o
	$(CC) -c $(PATH2SRC)main.cc -o $(PATH2OBJ)main.o

$(PATH2OBJ)MoveBehaviour.o: $(PATH2SRC)MoveBehaviour.cc $(PATH2SRC)MoveBehaviour.h $(PATH2SRC)Bitboard.h  $(PATH2SRC)defs.h
	$(CC) -c $(PATH2SRC)MoveBehaviour.cc -o $(PATH2OBJ)MoveBehaviour.o

$(PATH2OBJ)View.o:	$(PATH2SRC)View.cc $(PATH2SRC)View.h
	$(CC) -c $(PATH2SRC)View.cc -o $(PATH2OBJ)View.o

$(PATH2OBJ)Log.o: $(PATH2SRC)Log.cc $(PATH2SRC)Log.h
	$(CC) -c $(PATH2SRC)Log.cc -o $(PATH2OBJ)Log.o

$(PATH2OBJ)NcView.o: $(PATH2SRC)NcView.cc $(PATH2SRC)NcView.h $(PATH2SRC)View.h $(PATH2SRC)Board.h
	$(CC) -c $(PATH2SRC)NcView.cc -o $(PATH2OBJ)NcView.o

$(PATH2OBJ)Pos.o: $(PATH2SRC)Pos.cc $(PATH2SRC)Pos.h $(PATH2SRC)defs.h
	$(CC) -c $(PATH2SRC)Pos.cc -o $(PATH2OBJ)Pos.o

$(PATH2OBJ)Piece.o: $(PATH2SRC)Piece.cc $(PATH2SRC)Piece.h $(PATH2SRC)Log.h $(PATH2SRC)Pos.h $(PATH2SRC)defs.h
	$(CC) -c $(PATH2SRC)Piece.cc -o $(PATH2OBJ)Piece.o

$(PATH2OBJ)Board.o: $(PATH2SRC)Board.cc $(PATH2SRC)Board.h $(PATH2SRC)Pos.h $(PATH2SRC)Piece.h $(PATH2SRC)Bitboard.h $(PATH2SRC)defs.h $(PATH2SRC)piece_behav/PawnMove.h $(PATH2SRC)piece_behav/KingMove.h $(PATH2SRC)piece_behav/KnightMove.h $(PATH2SRC)piece_behav/PlusMove.h $(PATH2SRC)piece_behav/CrossMove.h
	$(CC) -c $(PATH2SRC)Board.cc -o $(PATH2OBJ)Board.o

$(PATH2OBJ)Bitboard.o: $(PATH2SRC)Bitboard.cc $(PATH2SRC)Bitboard.h $(PATH2SRC)Pos.h $(PATH2SRC)defs.h 
	$(CC) -c $(PATH2SRC)Bitboard.cc -o $(PATH2OBJ)Bitboard.o

$(PATH2OBJ)PawnMove.o: $(PATH2SRC)piece_behav/PawnMove.cc $(PATH2SRC)piece_behav/PawnMove.h $(PATH2SRC)Pos.h $(PATH2SRC)Piece.h $(PATH2SRC)defs.h $(PATH2SRC)MoveBehaviour.h
	$(CC) -c $(PATH2SRC)piece_behav/PawnMove.cc -o $(PATH2OBJ)PawnMove.o

$(PATH2OBJ)KingMove.o: $(PATH2SRC)piece_behav/KingMove.cc $(PATH2SRC)piece_behav/KingMove.h $(PATH2SRC)Pos.h $(PATH2SRC)Piece.h $(PATH2SRC)defs.h $(PATH2SRC)MoveBehaviour.h
	$(CC) -c $(PATH2SRC)piece_behav/KingMove.cc -o $(PATH2OBJ)KingMove.o

$(PATH2OBJ)KnightMove.o: $(PATH2SRC)piece_behav/KnightMove.cc $(PATH2SRC)piece_behav/KnightMove.h $(PATH2SRC)Pos.h $(PATH2SRC)Piece.h $(PATH2SRC)defs.h $(PATH2SRC)MoveBehaviour.h
	$(CC) -c $(PATH2SRC)piece_behav/KnightMove.cc -o $(PATH2OBJ)KnightMove.o

$(PATH2OBJ)PlusMove.o:   $(PATH2SRC)piece_behav/PlusMove.cc $(PATH2SRC)piece_behav/PlusMove.h $(PATH2SRC)Pos.h $(PATH2SRC)Piece.h $(PATH2SRC)defs.h $(PATH2SRC)MoveBehaviour.h
	$(CC) -c $(PATH2SRC)piece_behav/PlusMove.cc -o $(PATH2OBJ)PlusMove.o

$(PATH2OBJ)CrossMove.o: $(PATH2SRC)piece_behav/CrossMove.cc $(PATH2SRC)piece_behav/CrossMove.h $(PATH2SRC)Pos.h $(PATH2SRC)Piece.h $(PATH2SRC)defs.h $(PATH2SRC)MoveBehaviour.h
	$(CC) -c $(PATH2SRC)piece_behav/CrossMove.cc -o $(PATH2OBJ)CrossMove.o

.PHONY: clean
clean:
		find . -type f -name '*.o' -delete
		rm -f CChess
		rm -f log.txt

