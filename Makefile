OBJ = obj/ChessGame.o obj/main.o obj/Pos.o obj/MoveBehaviour.o obj/PawnMove.o obj/KingMove.o obj/KnightMove.o obj/PlusMove.o obj/CrossMove.o obj/Piece.o obj/Board.o obj/View.o obj/NcLog.o obj/NcView.o
CC = g++ -Wall -g
LIB = -lncursesw

CChess:	$(OBJ)
	$(CC) -o CChess $(OBJ) $(LIB)

obj/ChessGame.o: ChessGame.cc ChessGame.h NcLog.h Board.h NcView.h defs.h MoveBehaviour.h
	$(CC) -c ChessGame.cc -o obj/ChessGame.o

obj/main.o: main.cc obj/ChessGame.o
	$(CC) -c main.cc -o obj/main.o

obj/MoveBehaviour.o: MoveBehaviour.cc MoveBehaviour.h
	$(CC) -c MoveBehaviour.cc -o obj/MoveBehaviour.o

obj/View.o:	View.cc View.h
	$(CC) -c View.cc -o obj/View.o

obj/NcLog.o: NcLog.cc NcLog.h
	$(CC) -c NcLog.cc -o obj/NcLog.o

obj/NcView.o: NcView.cc NcView.h View.h Board.h
	$(CC) -c NcView.cc -o obj/NcView.o

obj/Pos.o: Pos.cc Pos.h defs.h
	$(CC) -c Pos.cc -o obj/Pos.o

obj/Piece.o: Piece.cc Piece.h NcLog.h Pos.h defs.h
	$(CC) -c Piece.cc -o obj/Piece.o

obj/Board.o: Board.cc Board.h Pos.h Piece.h defs.h piece_behav/PawnMove.h piece_behav/KingMove.h piece_behav/KnightMove.h piece_behav/PlusMove.h piece_behav/CrossMove.h
	$(CC) -c Board.cc -o obj/Board.o

obj/PawnMove.o: piece_behav/PawnMove.cc piece_behav/PawnMove.h Pos.h Piece.h defs.h MoveBehaviour.h
	$(CC) -c piece_behav/PawnMove.cc -o obj/PawnMove.o

obj/KingMove.o: piece_behav/KingMove.cc piece_behav/KingMove.h Pos.h Piece.h defs.h MoveBehaviour.h
	$(CC) -c piece_behav/KingMove.cc -o obj/KingMove.o

obj/KnightMove.o: piece_behav/KnightMove.cc piece_behav/KnightMove.h Pos.h Piece.h defs.h MoveBehaviour.h
	$(CC) -c piece_behav/KnightMove.cc -o obj/KnightMove.o

obj/PlusMove.o:   piece_behav/PlusMove.cc piece_behav/PlusMove.h Pos.h Piece.h defs.h MoveBehaviour.h
	$(CC) -c piece_behav/PlusMove.cc -o obj/PlusMove.o

obj/CrossMove.o: piece_behav/CrossMove.cc piece_behav/CrossMove.h Pos.h Piece.h defs.h MoveBehaviour.h
	$(CC) -c piece_behav/CrossMove.cc -o obj/CrossMove.o

clean:
		find . -type f -name '*.o' -delete
		rm -f CChess

