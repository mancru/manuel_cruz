#include "world_limited.h"
#include "world_init.h"
#include "world.h"

struct config config;

struct world_limited
{
	struct world super;
};


static void set_cell(struct world_limited *wl, int buf, int x, int y, bool val);
static bool get_cell(const struct world_limited *wl, int x, int y);

struct world_limited * world_limited_alloc(struct config * config)
{
	struct world_limited * wl;
	wl=(struct world_limited *)malloc(sizeof(struct world_limited));
	if (!wl) {
		perror("Limited world could not be allocated\n");
		return NULL;
	}

	wl->super.set_cell = (void *)set_cell;
	wl->super.get_cell = (void *)get_cell;
	world_init(config, (struct world *)wl);
	return wl;
}

void set_cell(struct world_limited *wl, int buf, int x, int y, bool val)
{
	* (wl->super.cells[buf] + x*(wl->super.size_y)+y) = val;
}

bool get_cell(const struct world_limited *wl, int x, int y)
{
	bool cell;
	if (x<0 || x>(wl->super.size_x-1) || y<0 || y>(wl->super.size_y-1))
		return DEAD;
	else
		cell = * (wl->super.cells[0] + x*(wl->super.size_y)+y);

	return cell;
}
void world_limited_free(struct world_limited * wl)
{
	world_free((struct world *)wl);
	free(wl);
}
