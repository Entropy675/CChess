OBJ = main.o Pos.o
CC = g++ -Wall 
LIB = -lncursesw 


CChess:	$(OBJ)
		$(CC) -o CChess $(OBJ) $(LIB)

main.o:	main.cc defs.h
		$(CC) -c main.cc
		
Pos.o: Pos.cc Pos.h defs.h
		$(CC) -c Pos.cc

clean:
		rm -f *.o CChess
