#ifndef _world_toroidal_h_
#define _world_toroidal_h_
#include "world_init.h"

/* Public methods */
struct world_toroidal * world_toroidal_alloc(struct config * config);
void world_toroidal_free(struct world_toroidal *wt);

#endif
