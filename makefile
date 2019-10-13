CFLAGS = -Wall -ansi -pedantic -Werror -std=c89
CC = gcc
OBJ = UserInterface.o FileIO.o gameEngine.o linked_list.o logs.o
HDRS = UserInterface.h FileIO.h gameEngine.h linked_list.h logs.h
EXEC = TicTacToe

ifdef SECRET
CFLAGS += -D SECRET
SECRET : clean $(EXEC)
endif

ifdef EDITOR
CFLAGS += -D EDITOR
EDITOR : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

UserInterface.o : UserInterface.c $(HDRS)
	$(CC) $(CFLAGS) -g UserInterface.c -c

FileIO.o : FileIO.c FileIO.h logs.h
	$(CC) $(CFLAGS) -g FileIO.c -c

gameEngine.o : gameEngine.c gameEngine.h logs.h UserInterface.h
	$(CC) $(CFLAGS) -g gameEngine.c -c

logs.o : logs.c logs.h linked_list.h
	$(CC) $(CFLAGS) -g logs.c -c

linked_list.o : linked_list.c linked_list.h
	$(CC) $(CFLAGS) -g linked_list.c -c

clean:
	rm -f $(EXEC) $(OBJ)
