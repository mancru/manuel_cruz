CFLAGS := -Wall -Werror -std=c99

# Rule avoid using Valgrind under windows
ifndef COMSPEC
	CFLAGS += -g
	VFLAGS := --leak-check=full --track-origins=yes --show-leak-kinds=all -v
	VINSTR := valgrind $(VFLAGS) ./tgol config.txt
endif

.PHONY : all clean valgrind gdb woflags

# valgrind is called if a new tgol is created
tgol : main.o world.o cell.o config.o world_toroidal.o world_limited.o
	gcc $(CFLAGS) main.o world.o cell.o config.o world_toroidal.o world_limited.o -o tgol; \
	$(VINSTR)

main.o : main.c
	gcc $(CFLAGS) -c main.c

world_limited.o : world_limited.c
	gcc $(CFLAGS) -c world_limited.c

world_toroidal.o : world_toroidal.c
	gcc $(CFLAGS) -c world_toroidal.c

config.o : config.c
	gcc $(CFLAGS) -c config.c

world.o : world.c
	gcc $(CFLAGS) -c world.c

cell.o : cell.c
	gcc $(CFLAGS) -c cell.c

clean :
	@rm -f *.o *.out tgol

# called it with "make valgrind"
valgrind :
	valgrind $(VFLAGS) ./tgol
# called it with "make gdb"
gdb :
	gdb -tui tgol

# build without error flags "make gdb"
woflags : main.o world.o config.o world_toroidal.o world_limited.o
	gcc -std=99 main.o world.o config.o world_toroidal.o world_limited.o -o tgol; \
	$(VINSTR)
