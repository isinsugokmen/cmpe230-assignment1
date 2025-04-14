# Makefile

CC = gcc
CFLAGS = -Wall -g
OBJS = main.o parser.o inventory.o alchemy.o bestiary.o

witchertracker: $(OBJS)
	$(CC) $(CFLAGS) -o witchertracker $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o witchertracker
