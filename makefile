CFLAGS := -Wall -Werror -std=c99

# Rule avoid using Valgrind under Windows. Can be used as a fast way to
# disable the valgrind instruction by changing ifndef (ON) to ifdef (OFF).

ifndef COMSPEC
	CFLAGS += -g
	VFLAGS := --leak-check=full -v
	VINSTR := valgrind $(VFLAGS) ./tgol
endif

.PHONY : all clean valgrind

# valgrind is called if a new tgol is created
tgol : main.o gol.o config.o
	gcc $(CFLAGS) main.o gol.o config.o -o tgol; \
	$(VINSTR)

main.o : main.c
	gcc $(CFLAGS) -c main.c

config.o : config.c
	gcc $(CFLAGS) -c config.c

gol.o : gol.c
	gcc $(CFLAGS) -c gol.c

clean :
	@rm -f *.o *.out

# call it with "make valgrind"
valgrind :
	$(VINSTR)
