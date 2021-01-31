CC=gcc
RM=rm
my_blockchain: main.c
	$(CC) -o my_blockchain -Wall -Wextra main.c set.c set.h bst.c bst.h string_array.c string_array.h 

clean:
	$(RM) -f my_blockchain