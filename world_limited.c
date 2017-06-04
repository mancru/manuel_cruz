#include "world_limited.h"
#include "world_init.h"
#include "world.h"

struct config config;

struct world_limited
{
	struct world super;
};


static void set_cell(struct world *wl, int buf, int x, int y, bool val);
static bool get_cell(const struct world *wl, int x, int y);

struct world_limited * world_limited_alloc(struct config * config)
{
	struct world_limited * wl;
	wl=(struct world_limited *)malloc(sizeof(struct world_limited));
	if (!wl) {
		perror("Limited world could not be allocated\n");
		return NULL;
	}

	wl->super.set_cell = set_cell;
	wl->super.get_cell = get_cell;
	wl = (struct world_limited *)world_init(config, (struct world *)wl);
	if (!wl)
		return NULL;
	return wl;
}

void set_cell(struct world *wl, int buf, int x, int y, bool val)
{
	* (wl->cells[buf] + x*(wl->size_y)+y) = val;
}

bool get_cell(const struct world *wl, int x, int y)
{
	bool cell;
	if (x<0 || x>(wl->size_x-1) || y<0 || y>(wl->size_y-1))
		return DEAD;
	else
		cell = * (wl->cells[0] + x*(wl->size_y)+y);

	return cell;
}
void world_limited_free(struct world_limited * wl)
{
	world_free((struct world *)wl);
}
