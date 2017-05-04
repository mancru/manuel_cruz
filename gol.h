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

void world_init(bool w_x[W_SIZE_X][W_SIZE_Y]);

void world_print(bool w_x[W_SIZE_X][W_SIZE_Y]);

void world_step(bool w_1[W_SIZE_X][W_SIZE_Y], bool w_2[W_SIZE_X][W_SIZE_Y]);

int world_count_neighbors(bool w_x[W_SIZE_X][W_SIZE_Y], int x, int y);

bool world_get_cell(bool w_x[W_SIZE_X][W_SIZE_Y], int x, int y);

void world_copy(bool w_y[W_SIZE_X][W_SIZE_Y], bool w_x[W_SIZE_X][W_SIZE_Y]);

#endif
