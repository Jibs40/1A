CC=gcc
CFLAGS=-W -Wall
SRC=/src/*.c
OBJ=$(SRCS:.c=.o)
NAME=battleship
RM=rm -f
MAKE=/usr/bin/battleship


all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) *.gc*
	$(RM) *.o
	$(RM) my_sokoban

re: fclean all 
