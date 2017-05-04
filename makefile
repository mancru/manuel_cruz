CFLAGS = -Wall -Werror

.PHONY : all clean

all : gol main tgol clean

tgol : main.o gol.o
	gcc main.o gol.o -o tgol

main : main.c
	gcc -c main.c

gol : gol.c
	gcc -c gol.c

clean :
	rm *.o *.out
