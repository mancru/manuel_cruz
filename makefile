CFLAGS = -Wall -Werror -std=c99

.PHONY : all clean

all : tgol

tgol : main.o gol.o config.o
	gcc $(CFLAGS) main.o gol.o config.o -o tgol

main.o : main.c
	gcc $(CFLAGS) -c main.c

config.o : config.c
	gcc $(CFLAGS) -c config.c

gol.o : gol.c
	gcc $(CFLAGS) -c gol.c

clean :
	rm *.o *.out
