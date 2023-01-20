OBJ = main.o Pos.o Board.o
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

clean:
		rm -f *.o CChess
