#include "world_limited.h"
#include "world_init.h"
#include "world.h"

struct config config;

void set_cell_limited(struct world_limited *wl, int buf, int x, int y, bool val);
bool get_cell_limited(const struct world_limited *wl, int x, int y);
void world_limited_free(struct world_limited * wl);

struct world_limited * world_limited_alloc(struct config * config)
{
	struct world_limited * wl;
	wl=(struct world_limited *)malloc(sizeof(struct world_limited));
	if (!wl) {
		perror("Limited world could not be allocated\n");
		return NULL;
	}

	wl->super.set_cell = (void *)set_cell_limited;
	wl->super.get_cell = (void *)get_cell_limited;
	world_init(config, (struct world *)wl);
	wl->super.world_free = (void *)world_limited_free;
	return wl;
}

void set_cell_limited(struct world_limited *wl, int buf, int x, int y, bool val)
{
	* (wl->super.cells[buf] + x*(wl->super.size_y)+y) = val;
}

bool get_cell_limited(const struct world_limited *wl, int x, int y)
{
	bool cell;
	if (x<0 || y>(wl->super.size_y-1))
		return DEAD;
	else
		cell = * (wl->super.cells[0] + x*(wl->super.size_y)+y);

	return cell;
}
void world_limited_free(struct world_limited * wl)
{
	if (wl->super.cells[0])
		free(wl->super.cells[0]);
	if (wl->super.cells[1])
		free(wl->super.cells[1]);
	if (wl){ 
		free(wl);
	} else {
		printf("WARNING: wl was not initialised\n");
		exit(-1);
	}
}
