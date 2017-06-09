#include <stdlib.h>

#include "cell.h"
#include "list.h"

static void free_s(void * ptr);

struct cell * cell_add(int x, int y, struct list_head *lh)
{
//#TODO: crea y anyade una celula a la lista lh
	struct cell * cell;
	cell = (struct cell *)malloc(sizeof(struct cell));
	if (!cell)
		return NULL;
	cell->x = x;
	cell->y = y;
	list_add_tail(&(cell->lh), lh);
	return cell;
}

void cell_del(struct cell *cell)
{
//#TODO: borra y saca de la lista la celula c
	list_del(&(cell->lh));
	free_s(cell);
}

static void free_s(void * ptr)
{
	if (ptr)
		free(ptr);
}
