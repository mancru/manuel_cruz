CFLAGS = -Wall -Werror

.PHONY : all clean

all : tgol

tgol : main.c
	gcc main.c gol.c -o tgol

clean :
	rm *.o *.out
