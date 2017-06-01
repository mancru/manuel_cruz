#ifndef _world_toroidal_h_
#define _world_toroidal_h_
#include "world_init.h"

struct world_toroidal
{
	struct world super;
	void (* fix_coords_toroidal)(const struct world_toroidal *wt, int *x, int *y);
};

/* Public methods */
struct world_toroidal * world_toroidal_alloc(struct config * config);

#endif
