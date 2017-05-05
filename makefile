CFLAGS = -Wall -Werror -std=c99

.PHONY : all clean

all : tgol

tgol : main.o gol.o
	gcc $(CFLAGS) main.o gol.o -o tgol

main.o : main.c
	gcc $(CFLAGS) -c main.c

gol.o : gol.c
	gcc $(CFLAGS) -c gol.c

clean :
	rm *.o *.out
