#ifndef _WORLD_INIT_H
#define _WORLD_INIT_H
#include "world.h"
#include "list.h"

struct world
{
	bool *cells;
	int size_x;
	int size_y;

	void (* set_cell)(struct world *w, int x, int y, bool val);
	bool (* get_cell)(const struct world *w, int x, int y);
	bool (* fix_coords)(const struct world *w, int *x, int *y);

	struct list_head alive_cells;
	struct list_head to_kill;
	struct list_head to_revive;
};	

#endif
