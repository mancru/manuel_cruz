#ifndef _world_limited_h_
#define _world_limited_h_
#include "world_init.h"

struct world_limited
{
	struct world super;
};

/* Public methods */
struct world_limited * world_limited_alloc();

#endif
