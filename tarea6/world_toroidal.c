#include "world_toroidal.h"
#include "world.h"
#include "world_init.h"

void set_cell_toroidal(struct world_toroidal *wt, int buf, int x, int y, bool val);
bool get_cell_toroidal(const struct world_toroidal *wt, int x, int y);
void fix_coords_toroidal(const struct world_toroidal *wt, int *x, int *y);
void world_toroidal_free(struct world_toroidal *wt);
void toroidal_print(void * w);


struct world_toroidal * world_toroidal_alloc(struct config * config)
{

	struct world_toroidal * wt;
	wt = (struct world_toroidal *)malloc(sizeof(struct world_toroidal));
	if (!wt) {
		perror("Toroidal world could not be allocated\n");
		return NULL;
	}

	// cambia o añade funciones
	wt->super.world_free = (void *)world_toroidal_free; // NO sé si hace falta. Ver función.
	wt->fix_coords_toroidal = fix_coords_toroidal;
	wt->super.set_cell = (void *)set_cell_toroidal;
	wt->super.get_cell = (void *)get_cell_toroidal;

	// inicializar el mundo
	world_init(config, (struct world *)wt);

	return wt;
}

void set_cell_toroidal(struct world_toroidal *wt, int buf, int x, int y, bool val)
{
	* (wt->super.cells[buf] + x*(wt->super.size_y)+y) = val;
}

bool get_cell_toroidal(const struct world_toroidal *wt, int x, int y)
{
	bool cell;
	int * ptrx = &x;
	int * ptry = &y;
	fix_coords_toroidal(wt, ptrx, ptry);
	cell = * (wt->super.cells[0] + x*(wt->super.size_y)+y);
	return cell;
}

void fix_coords_toroidal(const struct world_toroidal *wt, int *x, int *y)
{
	if (*x < 0){
		*x=(wt->super.size_x)-1;
	} else if ( *x >= (wt->super.size_x) ){
		*x=0;
	}

	if (*y < 0){
		*y=(wt->super.size_y)-1;
	} else if ( *y >= (wt->super.size_y) ){
		*y=0;
	}
}

void world_toroidal_free(struct world_toroidal * wt)
{
	if (wt->super.cells[0])
		free(wt->super.cells[0]);
	if (wt->super.cells[1])
		free(wt->super.cells[1]);
	if (wt){ 
		free(wt);
	} else {
		printf("WARNING: wt was not initialised\n");
		exit(-1);
	}
}
