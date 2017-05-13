#include "gol.h"

void world_init(struct world * ptrw)
{
	
	for (int i=0;i<W_SIZE_X;i++){
		for (int j=0;j<W_SIZE_Y;j++){
			ptrw->w1[i][j]=DEAD;
		}
	}
	/* Patrón del glider: */
	ptrw->w1[0][1]=ALIVE;
	ptrw->w1[1][2]=ALIVE;
	ptrw->w1[2][0]=ALIVE;
	ptrw->w1[2][1]=ALIVE;
	ptrw->w1[2][2]=ALIVE;
}

void world_print(const struct world * ptrw)
{

	bool cell;

	for (int i=0;i<W_SIZE_X;i++){
		for (int j=0;j<W_SIZE_Y;j++){
			cell=ptrw->w1[i][j];
			printf ("%s ", cell ? "#" : ".");
		}
		printf("\n");
	}
}

void world_step(struct world * ptrw)
{

	int v;
	bool cell;

	for (int i = 0; i < W_SIZE_X; i++) {
		for (int j = 0; j < W_SIZE_Y; j++) {
			cell=ptrw->w1[i][j];
			v = world_count_neighbors(ptrw, i, j);//
			ptrw->w2[i][j] = (v==3) || (cell && v==2);
		}
	}
	world_copy(ptrw);
}

int world_count_neighbors(const struct world * ptrw, int x, int y)
{

	int count=0;

	count += world_get_cell(ptrw, x - 1, y - 1);
	count += world_get_cell(ptrw, x - 1, y    );
	count += world_get_cell(ptrw, x - 1, y + 1);
	count += world_get_cell(ptrw, x    , y - 1);
	count += world_get_cell(ptrw, x    , y + 1);
	count += world_get_cell(ptrw, x + 1, y - 1);
	count += world_get_cell(ptrw, x + 1, y    );
	count += world_get_cell(ptrw, x + 1, y + 1);
	
	return count;
}

bool world_get_cell(const struct world * ptrw, int x, int y)
{

	bool cell;

	if (x < 0){
		x=W_SIZE_X-1;
	} else if (x >= W_SIZE_X){
		x=0;
	}

	if (y < 0){
		y=W_SIZE_Y-1;
	} else if (y >= W_SIZE_Y){
		y=0;
	}

	cell=ptrw->w1[x][y];

	return cell;

}

void world_copy(struct world * ptrw)
{
	for (int i=0;i<W_SIZE_X;i++){
		for (int j=0;j<W_SIZE_Y;j++){
			ptrw->w1[i][j]=ptrw->w2[i][j];
		}
	}
}
