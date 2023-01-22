OBJ = main.o Pos.o Board.o pieces/Pawn.o pieces/King.o pieces/Knight.o pieces/Queen.o pieces/Rook.o  pieces/Bishop.o
CC = g++ -Wall 
LIB = -lncursesw 


CChess:	$(OBJ)
		$(CC) -o CChess $(OBJ) $(LIB)

main.o:	main.cc defs.h
		$(CC) -c main.cc
		
Pos.o: Pos.cc Pos.h defs.h
		$(CC) -c Pos.cc

Board.o: Pos.h Board.h Board.cc defs.h
		$(CC) -c Board.cc
		
pieces/Pawn.o:	pieces/Pawn.cc pieces/Pawn.h defs.h Pos.h Piece.h
		$(CC) -c -o pieces/Pawn.o pieces/Pawn.cc
		
pieces/King.o:	pieces/King.cc pieces/King.h defs.h Pos.h Piece.h
		$(CC) -c -o pieces/King.o pieces/King.cc

pieces/Knight.o: pieces/Knight.cc pieces/Knight.h defs.h Pos.h Piece.h
		$(CC) -c -o pieces/Knight.o pieces/Knight.cc

pieces/Queen.o:	pieces/Queen.cc pieces/Queen.h defs.h Pos.h Piece.h
		$(CC) -c -o pieces/Queen.o pieces/Queen.cc

pieces/Rook.o: pieces/Rook.cc pieces/Rook.h defs.h Pos.h Piece.h
		$(CC) -c -o pieces/Rook.o pieces/Rook.cc

pieces/Bishop.o: pieces/Bishop.cc pieces/Bishop.h defs.h Pos.h Piece.h
		$(CC) -c -o pieces/Bishop.o pieces/Bishop.cc

clean:
		find . -type f -name '*.o' -delete
