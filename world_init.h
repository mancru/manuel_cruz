#ifndef _WORLD_INIT_H
#define _WORLD_INIT_H
#include "world.h"

struct world
{
	bool *cells[2];
	int size_x;
	int size_y;

	void (* set_cell)(struct world *w, int buf, int x, int y, bool val);
	bool (* get_cell)(const struct world *w, int x, int y);
};

#endif
