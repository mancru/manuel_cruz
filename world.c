#include <time.h>
#include <stdbool.h>

#include "world.h"
#include "world_init.h"
#include "config.h"
#include "cell.h"
#include "list.h"

#ifndef typeof
#define typeof __typeof__
#endif

struct world;

static const int neighbors_coords[8][2];
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

	w->cells = (bool *)malloc(w->size_x*w->size_y*sizeof(bool));
	if (!w->cells){
		free(w);
		perror("World 1 could not be allocated!\n");
		return NULL;
	}

	//Inicialización de las listas
	INIT_LIST_HEAD(&w->alive_cells);
	INIT_LIST_HEAD(&w->to_kill);
	INIT_LIST_HEAD(&w->to_revive);

	//Inicialización del mundo
	for (int i=0;i<w->size_x;i++){
		for (int j=0;j<w->size_y;j++){
			w->set_cell(w, i, j, DEAD);
		}
	}
	bool status;
	if ( config->init_mode == CFG_DEFAULT || config->init_mode == CFG_GLIDER ){
	/* Patrón del glider: */
		w->set_cell(w, 0, 1, ALIVE);
		w->set_cell(w, 1, 2, ALIVE);
		w->set_cell(w, 2, 0, ALIVE);
		w->set_cell(w, 2, 1, ALIVE);
		w->set_cell(w, 2, 2, ALIVE);
	//Anyadido a la lista
		cell_add(0, 1, &(w->alive_cells));
		cell_add(1, 2, &(w->alive_cells));
		cell_add(2, 0, &(w->alive_cells));
		cell_add(2, 1, &(w->alive_cells));
		cell_add(2, 2, &(w->alive_cells));
	} else if ( config->init_mode == CFG_RANDOM ){
		srand(time(0));
		for (int i = 0; i < w->size_x; i++){
			for (int j = 0; j < w->size_y; j++){
				status = rand()%2;
				if (status == ALIVE){
					w->set_cell(w, i, j, ALIVE);
					cell_add(i, j, &(w->alive_cells));
				}
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
	struct cell *c, *c_aux;
	int n_x, n_y;
	int n_alive_neighbors;

	list_for_each_entry_safe(c, c_aux, &(w->alive_cells), lh){
		// Check current cell
		// TODO: Cuenta las vecinas
		n_alive_neighbors = count_neighbors(w, c->x, c->y);
		// TODO: Si tiene que morir, MUEVE la celula a la lista
		// `to_kill`
		if (n_alive_neighbors!=2 && n_alive_neighbors!=3){
			cell_add(c->x, c->y, &(w->to_kill));
			cell_del(c);
		}

		// Check all neighbors
		for (int i=0; i < 8; i++){
			n_x = c->x + neighbors_coords[i][0];
			n_y = c->y + neighbors_coords[i][1];
			// Si las coordenadas no son validas, no hacemos nada
			if (!w->fix_coords(w, &n_x, &n_y))
				break;

			// TODO: Decide el estado siguiente de esta vecina
			n_alive_neighbors = count_neighbors(w, n_x, n_y);
			if (n_alive_neighbors==3)
				cell_add(n_x, n_y, &(w->to_revive));

			// TODO: SI la vamos a matar -> ANYADIR a `to_kill`
			// TODO: SINO,SI la vamos a matar -> ANYADIR a `to_kill`

		}
	}

	// Kill
	list_for_each_entry_safe(c, c_aux, &w->to_kill, lh){
		// TODO: Mata la célula en el array, sacala de la lista y
		// eliminala
		w->set_cell(w, c->x, c->y, DEAD);
		cell_del(c);
	}

	// Revive
	list_for_each_entry_safe(c, c_aux, &w->to_revive, lh){
		// TODO: SI estaba viva, la revivimos en el array y la MOVEMOS a
		// `alive`
		// TODO: SINO la sacamos de la lista y la eliminamos

		struct cell *c2;
		bool flag_alive = false;
		list_for_each_entry(c2, &(w->alive_cells), lh){
			if (c->x == c2->x && c->y == c2->y){
				flag_alive = true;
				break;
			}
		}
		if (!flag_alive){
			w->set_cell(w, c->x, c->y, ALIVE);
			cell_add(c->x, c->y, &(w->alive_cells));
		}
		cell_del(c);
	}
}

static const int neighbors_coords[8][2] = {
	{-1, -1}, {0, -1}, {1, -1},
	{-1,  0},          {1,  0},
	{-1,  1}, {0,  1}, {1,  1}
};

static int count_neighbors(const struct world *w, int x, int y)
{
	int count = 0;
	for (int i=0; i < 8; i++){
		count += w->get_cell(w,
			x + neighbors_coords[i][0],
			y + neighbors_coords[i][1]
		);
	}
	return count;
}

void world_free(struct world *w)
{
	free(w->cells);
	free(w);
}
