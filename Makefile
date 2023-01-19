OBJ = main.o 
CC = gcc -Wall 
LIB = -lncurses 

CChess:	$(OBJ)
		$(CC) -o CChess $(OBJ) $(LIB)

main.o:	main.cc defs.h
		$(CC) -c main.cc
		
clean:
		rm -f *.o CChess
