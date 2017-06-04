#include "world_toroidal.h"
#include "world.h"
#include "world_init.h"

struct world_toroidal
{
	struct world super;
};

static void set_cell(struct world *wt, int buf, int x, int y, bool val);
static bool get_cell(const struct world *wt, int x, int y);
static void fix_coords(const struct world *wt, int *x, int *y);

struct world_toroidal * world_toroidal_alloc(struct config * config)
{

	struct world_toroidal * wt;
	wt = (struct world_toroidal *)malloc(sizeof(struct world_toroidal));
	if (!wt) {
		perror("Toroidal world could not be allocated\n");
		return NULL;
	}

	// cambia o añade funciones
	wt->super.set_cell = set_cell;
	wt->super.get_cell = get_cell;

	// inicializar el mundo
	wt = (struct world_toroidal *)world_init(config, (struct world *)wt);

	return wt;
}

void set_cell(struct world *wt, int buf, int x, int y, bool val)
{
	* (wt->cells[buf] + x*(wt->size_y)+y) = val;
}

bool get_cell(const struct world *wt, int x, int y)
{
	bool cell;
	int * ptrx = &x;
	int * ptry = &y;
	fix_coords(wt, ptrx, ptry);
	cell = * (wt->cells[0] + x*(wt->size_y)+y);
	return cell;
}

void fix_coords(const struct world *wt, int *x, int *y)
{
	if (*x < 0){
		*x=(wt->size_x)-1;
	} else if ( *x >= (wt->size_x) ){
		*x=0;
	}

	if (*y < 0){
		*y=(wt->size_y)-1;
	} else if ( *y >= (wt->size_y) ){
		*y=0;
	}
}

void world_toroidal_free(struct world_toroidal * wt)
{
	world_free((struct world *)wt);
}
