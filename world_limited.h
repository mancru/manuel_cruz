#ifndef _world_limited_h_
#define _world_limited_h_
#include "world_init.h"

/* Public methods */
struct world_limited * world_limited_alloc();
void world_limited_free(struct world_limited * wl);

#endif
