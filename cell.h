#ifndef _CELL_H_
#define _CELL_H_

#include "list.h"

struct cell {
	int x,y;
	struct list_head lh;
};

struct cell * cell_add(int x, int y, struct list_head *lh);
void cell_del(struct cell *c);

#endif
