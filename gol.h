#ifndef _GOL_H_
#define _GOL_H_
#define W_SIZE_X 11
#define W_SIZE_Y 11
#define ALIVE 1
#define DEAD 0
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct world {
	bool w1[W_SIZE_X][W_SIZE_Y];
	bool w2[W_SIZE_X][W_SIZE_Y];
};

void world_init(struct world * ptrw);
void world_print(const struct world * ptrw);
void world_step(struct world * ptrw);
int world_count_neighbors(const struct world * ptrw, int x, int y);
bool world_get_cell(const struct world * ptrw, int x, int y);
void world_copy(struct world * ptrw);


#endif
