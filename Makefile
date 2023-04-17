OBJ = obj/ChessGame.o obj/main.o obj/Pos.o obj/Board.o obj/View.o obj/NcLog.o obj/NcView.o obj/Piece.o obj/pieces/Pawn.o obj/pieces/King.o obj/pieces/Knight.o obj/pieces/Queen.o obj/pieces/Rook.o obj/pieces/Bishop.o
CC = g++ -Wall -g
LIB = -lncursesw

CChess:	$(OBJ)
	$(CC) -o CChess $(OBJ) $(LIB)

obj/ChessGame.o: ChessGame.cc NcLog.h Board.h NcView.h defs.h
	$(CC) -c ChessGame.cc -o obj/ChessGame.o

obj/main.o: main.cc obj/ChessGame.o
	$(CC) -c main.cc -o obj/main.o

obj/View.o:	View.cc View.h
	$(CC) -c View.cc -o obj/View.o

obj/NcLog.o: NcLog.cc NcLog.h
	$(CC) -c NcLog.cc -o obj/NcLog.o

obj/NcView.o: NcView.cc NcView.h View.h Board.h
	$(CC) -c NcView.cc -o obj/NcView.o

obj/Pos.o: Pos.cc defs.h
	$(CC) -c Pos.cc -o obj/Pos.o

obj/Piece.o: Piece.cc NcLog.h Pos.h defs.h
	$(CC) -c Piece.cc -o obj/Piece.o

obj/Board.o: Board.cc Pos.h Piece.h defs.h pieces/Pawn.h pieces/King.h pieces/Knight.h pieces/Queen.h pieces/Rook.h pieces/Bishop.h
	$(CC) -c Board.cc -o obj/Board.o

obj/pieces/Pawn.o: pieces/Pawn.cc Pos.h Piece.h defs.h
	$(CC) -c pieces/Pawn.cc -o obj/pieces/Pawn.o

obj/pieces/King.o: pieces/King.cc Pos.h Piece.h defs.h
	$(CC) -c pieces/King.cc -o obj/pieces/King.o

obj/pieces/Knight.o: pieces/Knight.cc Pos.h Piece.h defs.h
	$(CC) -c pieces/Knight.cc -o obj/pieces/Knight.o

obj/pieces/Queen.o:	 pieces/Queen.cc Pos.h Piece.h defs.h
	$(CC) -c pieces/Queen.cc -o obj/pieces/Queen.o

obj/pieces/Rook.o:   pieces/Rook.cc Pos.h Piece.h defs.h
	$(CC) -c pieces/Rook.cc -o obj/pieces/Rook.o

obj/pieces/Bishop.o: pieces/Bishop.cc Pos.h Piece.h defs.h
	$(CC) -c pieces/Bishop.cc -o obj/pieces/Bishop.o

clean:
		find . -type f -name '*.o' -delete
		rm -f CChess

