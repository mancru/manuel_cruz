#include <time.h>
#include <stdbool.h>
#include "world.h"
#include "world_init.h"
#include "config.h"

struct world;

static int count_neighbors(const struct world *w, int x, int y);

struct world *world_alloc(struct config * config)
{
	struct world * w;
	w = (struct world *)malloc(sizeof(struct world));
	if (!w)
		return NULL;

	return w;
}

struct world *world_init(struct config * config, struct world * w)
{
	w->size_x = config->size_x;
	w->size_y = config->size_y;

	w->cells[0] = (bool *)malloc(w->size_x*w->size_y*sizeof(bool));
	if (!w->cells[0]){
		free(w);
		perror("World 1 could not be allocated!\n");
		return NULL;
	}

	w->cells[1] = (bool *)malloc(w->size_x *w->size_y*sizeof(bool));
	if (!w->cells[1]){
		free(w->cells[0]);
		free(w);
		perror("World 2 could not be allocated!\n");
		return NULL;
	}

	//Inicialización del mundo
	for (int i=0;i<w->size_x;i++){
		for (int j=0;j<w->size_y;j++){
			w->set_cell(w, 0, i, j, DEAD);
		}
	}

	if ( config->init_mode == CFG_DEFAULT || config->init_mode == CFG_GLIDER ){
	/* Patrón del glider: */
		w->set_cell(w, 0, 0, 1, ALIVE);
		w->set_cell(w, 0, 1, 2, ALIVE);
		w->set_cell(w, 0, 2, 0, ALIVE);
		w->set_cell(w, 0, 2, 1, ALIVE);
		w->set_cell(w, 0, 2, 2, ALIVE);
	} else if ( config->init_mode == CFG_RANDOM ){
		srand(time(0));
		for (int i = 0; i < w->size_x; i++){
			for (int j = 0; j < w->size_y; j++){
				w->set_cell(w, 0, i, j, rand()%2);
			}
		}
	}
	return w;
}

void world_print(const struct world * w)
{
	bool cell;
	for (int i=0; i < w->size_x ;i++){
		for (int j=0;j < w->size_y ;j++){
			cell = w->get_cell(w, i, j);
			printf ("%s ", cell ? "#" : ".");
		}
		printf("\n");
	}
}

void world_iterate(struct world *w)
{
	int n_alive_neighbors;
	bool cell;
	bool * keep_world_address;
	for (int i = 0; i < w->size_x; i++){
		for (int j = 0; j < w->size_y; j++){
			cell = w->get_cell(w, i, j);
			n_alive_neighbors = count_neighbors(w, i, j);
			if ((n_alive_neighbors==3) || (cell && n_alive_neighbors==2)){
				w->set_cell(w, 1, i, j, ALIVE);
			} else {
				w->set_cell(w, 1, i, j, DEAD);
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
	count += w->get_cell (w, x - 1, y - 1);
	count += w->get_cell (w, x - 1, y    );
	count += w->get_cell (w, x - 1, y + 1);
	count += w->get_cell (w, x    , y - 1);
	count += w->get_cell (w, x    , y + 1);
	count += w->get_cell (w, x + 1, y - 1);
	count += w->get_cell (w, x + 1, y    );
	count += w->get_cell (w, x + 1, y + 1);
	return count;
}

void world_free(struct world *w)
{
	free(w->cells[0]);
	free(w->cells[1]);
	free(w);
}
