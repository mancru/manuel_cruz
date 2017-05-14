#include "gol.h"

struct world
{
	bool *cells[2];
	int size_x;
	int size_y;
};

static void fix_coords(const struct world *w, int *x, int *y);
static bool get_cell(const struct world *w, int x, int y);
static void set_cell(struct world *w, int buf, int x, int y, bool val);
static int count_neighbors(const struct world *w, int x, int y);

struct world *world_alloc(int size_x, int size_y)
{
	struct world * w;
	w = (struct world *) malloc (sizeof(struct world));
	if (!w)
		return NULL;

	bool * w1;
	w1 = (bool *) malloc ( size_x * size_y * sizeof(bool) );
	if (!w){
		printf("World 1 could not be allocated!");
		exit(-11);
	}

	bool * w2;
	w2 = (bool *) malloc ( size_x * size_y * sizeof(bool) );
	if (!w){
		printf("World 2 could not be allocated!");
		exit(-12);
	}

	w->size_x = size_x;
	w->size_y = size_y;
	w->cells[0] = w1;
	w->cells[1] = w2;

	for (int i=0;i<size_x;i++){
		for (int j=0;j<size_y;j++){
			* (w1 + i*(w->size_x)+j) = DEAD;
		}
	}
	/* Patrón del glider: */
	* (w1 + 0*(w->size_x) +1) = ALIVE;
	* (w1 + 1*(w->size_x) +2) = ALIVE;
	* (w1 + 2*(w->size_x) +0) = ALIVE;
	* (w1 + 2*(w->size_x) +1) = ALIVE;
	* (w1 + 2*(w->size_x) +2) = ALIVE;

	return w;
}

void world_print(const struct world * w)
{
	bool cell;

	for (int i=0; i < w->size_x ;i++){
		for (int j=0;j < w->size_y ;j++){
			cell = * (w->cells[0] + i*(w->size_x)+j);
			printf ("%s ", cell ? "#" : ".");
		}
		printf("\n");
	}
}

void world_iterate(struct world *w)
{
	int n_alive_neighbors;
	bool cell;
	void * keep_world_address;

	for (int i = 0; i < w->size_x; i++){
		for (int j = 0; j < w->size_y; j++){

			cell = * (w->cells[0] + i*(w->size_x)+j);

			n_alive_neighbors = count_neighbors(w, i, j);

			if ((n_alive_neighbors==3) || (cell && n_alive_neighbors==2)){
				set_cell(w, 1, i, j, ALIVE);
			} else {
				set_cell(w, 1, i, j, DEAD);
			}
		}
	}

	keep_world_address = w->cells[0];
	w->cells[0] = w->cells[1];
	w->cells[1] = keep_world_address;
}

static int count_neighbors(const struct world *w, int x, int y)
{
	int count=0;

	count += get_cell (w, x - 1, y - 1);
	count += get_cell (w, x - 1, y    );
	count += get_cell (w, x - 1, y + 1);
	count += get_cell (w, x    , y - 1);
	count += get_cell (w, x    , y + 1);
	count += get_cell (w, x + 1, y - 1);
	count += get_cell (w, x + 1, y    );
	count += get_cell (w, x + 1, y + 1);
	
	return count;
}

static void set_cell(struct world *w, int buf, int x, int y, bool val)
{
	* (w->cells[buf] + x*(w->size_x)+y) = val;
}

static bool get_cell(const struct world *w, int x, int y)
{
	bool cell;
	int * ptrx = &x;
	int * ptry = &y;

	fix_coords(w, ptrx, ptry);

	cell = * (w->cells[0] + x*(w->size_x)+y);

	return cell;
}

static void fix_coords(const struct world *w, int *x, int *y)
{
	if (*x < 0){
		*x=(w->size_x)-1;
	} else if ( *x >= (w->size_x) ){
		*x=0;
	}

	if (*y < 0){
		*y=(w->size_y)-1;
	} else if ( *y >= (w->size_y) ){
		*y=0;
	}
}

void world_free(struct world *w)
{
	free(w->cells[0]);
	free(w->cells[1]);
	free(w);
}
