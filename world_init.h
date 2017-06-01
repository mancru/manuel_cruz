#ifndef _WORLD_INIT_H
#define _WORLD_INIT_H
#include "world.h"

struct world
{
	bool *cells[2];
	int size_x;
	int size_y;

	struct world * (* world_alloc)(struct config * config);
	void (* world_init)(struct config * config, struct world * w);
	void (* world_free)(struct world * w);
	void (* world_iterate)(struct world * w);
	void (* world_print)(const struct world * w);
	int (* count_neighbors)(const struct world *w, int x, int y);
	void (* set_cell)(struct world *w, int buf, int x, int y, bool val);
	bool (* get_cell)(const struct world *w, int x, int y);
};

#endif
