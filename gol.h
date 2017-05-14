#ifndef _GOL_H_
#define _GOL_H_
#define WORLD_X 11
#define WORLD_Y 11
#define ALIVE 1
#define DEAD 0
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct world;

struct world *world_alloc(int size_x, int size_y);
void world_free(struct world *w);

void world_print(const struct world *w);
void world_iterate(struct world *w);

#endif
