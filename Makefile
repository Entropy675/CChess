OBJ = obj/ChessGame.o obj/main.o obj/Pos.o obj/MoveBehaviour.o obj/PawnMove.o obj/KingMove.o obj/KnightMove.o obj/PlusMove.o obj/CrossMove.o obj/Piece.o obj/Board.o obj/View.o obj/NcLog.o obj/NcView.o
CC = g++ -Wall -g
LIB = -lncursesw

CChess:	$(OBJ)
	$(CC) -o CChess $(OBJ) $(LIB)

obj/ChessGame.o: src/ChessGame.cc src/ChessGame.h src/NcLog.h src/Board.h src/NcView.h src/defs.h src/MoveBehaviour.h
	$(CC) -c src/ChessGame.cc -o obj/ChessGame.o

obj/main.o: src/main.cc obj/ChessGame.o
	$(CC) -c src/main.cc -o obj/main.o

obj/MoveBehaviour.o: src/MoveBehaviour.cc src/MoveBehaviour.h
	$(CC) -c src/MoveBehaviour.cc -o obj/MoveBehaviour.o

obj/View.o:	src/View.cc src/View.h
	$(CC) -c src/View.cc -o obj/View.o

obj/NcLog.o: src/NcLog.cc src/NcLog.h
	$(CC) -c src/NcLog.cc -o obj/NcLog.o

obj/NcView.o: src/NcView.cc src/NcView.h src/View.h src/Board.h
	$(CC) -c src/NcView.cc -o obj/NcView.o

obj/Pos.o: src/Pos.cc src/Pos.h src/defs.h
	$(CC) -c src/Pos.cc -o obj/Pos.o

obj/Piece.o: src/Piece.cc src/Piece.h src/NcLog.h src/Pos.h src/defs.h
	$(CC) -c src/Piece.cc -o obj/Piece.o

obj/Board.o: src/Board.cc src/Board.h src/Pos.h src/Piece.h src/defs.h src/piece_behav/PawnMove.h src/piece_behav/KingMove.h src/piece_behav/KnightMove.h src/piece_behav/PlusMove.h src/piece_behav/CrossMove.h
	$(CC) -c src/Board.cc -o obj/Board.o

obj/PawnMove.o: src/piece_behav/PawnMove.cc src/piece_behav/PawnMove.h src/Pos.h src/Piece.h src/defs.h src/MoveBehaviour.h
	$(CC) -c src/piece_behav/PawnMove.cc -o obj/PawnMove.o

obj/KingMove.o: src/piece_behav/KingMove.cc src/piece_behav/KingMove.h src/Pos.h src/Piece.h src/defs.h src/MoveBehaviour.h
	$(CC) -c src/piece_behav/KingMove.cc -o obj/KingMove.o

obj/KnightMove.o: src/piece_behav/KnightMove.cc src/piece_behav/KnightMove.h src/Pos.h src/Piece.h src/defs.h src/MoveBehaviour.h
	$(CC) -c src/piece_behav/KnightMove.cc -o obj/KnightMove.o

obj/PlusMove.o:   src/piece_behav/PlusMove.cc src/piece_behav/PlusMove.h src/Pos.h src/Piece.h src/defs.h src/MoveBehaviour.h
	$(CC) -c src/piece_behav/PlusMove.cc -o obj/PlusMove.o

obj/CrossMove.o: src/piece_behav/CrossMove.cc src/piece_behav/CrossMove.h src/Pos.h src/Piece.h src/defs.h src/MoveBehaviour.h
	$(CC) -c src/piece_behav/CrossMove.cc -o obj/CrossMove.o

clean:
		find . -type f -name '*.o' -delete
		rm -f CChess

