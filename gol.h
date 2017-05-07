#ifndef _GOL_H_
#define _GOL_H_
#define W_SIZE_X 11
#define W_SIZE_Y 11
#define ALIVE 1
#define DEAD 0
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Funciones para:
 * - Inicializar el mundo.
 * - Imprimirlo.
 * - Verificar el estado de las célucas en un mundo y guardar dicho estado en otro.
 * - Devolver el número de células vecinas vivas.
 * - Devuelve el estado de la célula.
 * - Copia un mundo en otro.
 */

struct world {
	bool w1[W_SIZE_X][W_SIZE_Y];
	bool w2[W_SIZE_X][W_SIZE_Y];
};

void world_init();

void world_print();

void world_step();

int world_count_neighbors();

bool world_get_cell();

void world_copy();

void world_initB();

#endif
