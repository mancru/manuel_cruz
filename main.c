#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define W_SIZE_X 11
#define W_SIZE_Y 11
#define ALIVE 1
#define DEAD 0

void world_init(/* Recibo un mundo */);
void world_print(/* Recibo un mundo */);
void world_step(/* Recibo dos mundos */);
int world_count_neighbors(/* Recibo un mundo y unas coordenadas */);
bool world_get_cell(/* Recibo un mundo y unas coordenadas */);
void world_copy(/* Recibo dos mundos */);


void world_init(bool w_x[W_SIZE_X][W_SIZE_Y])
{
	
	for (int i=0;i<W_SIZE_X;i++){
		for (int j=0;j<W_SIZE_Y;j++){
			w_x[i][j]=DEAD;
		}
	}

	/* Patrón del glider: */
	
	w_x[0][1]=ALIVE;
	w_x[1][2]=ALIVE;
	w_x[2][0]=ALIVE;
	w_x[2][1]=ALIVE;
	w_x[2][2]=ALIVE;
	
}

void world_print(bool w_x[W_SIZE_X][W_SIZE_Y])
{

	bool cell;

	for (int i=0;i<W_SIZE_X;i++){
		for (int j=0;j<W_SIZE_Y;j++){
			cell=w_x[i][j];
			cell ? printf("# ") : printf(". ");
		}
		printf("\n");
	}
}

void world_step(bool w_1[W_SIZE_X][W_SIZE_Y], bool w_2[W_SIZE_X][W_SIZE_Y])
{

	// TODO: Recorrer array contando vecinas
	int v;
	bool cell;

	for (int i = 0; i < W_SIZE_X; i++) {
		for (int j = 0; j < W_SIZE_Y; j++) {
			cell=w_2[i][j];
			v = world_count_neighbors(w_1, i, j);
			w_2[i][j] = (v==3) || (cell && v==2);
		}
	}

	world_copy(w_2, w_1);
}

int world_count_neighbors(bool w_x[W_SIZE_X][W_SIZE_Y], int x, int y)
{
	int count=0;

	count += world_get_cell(w_x, x - 1, y - 1);
	count += world_get_cell(w_x, x - 1, y	 );
	count += world_get_cell(w_x, x - 1, y + 1);
	count += world_get_cell(w_x, x    , y - 1);
	count += world_get_cell(w_x, x    , y + 1);
	count += world_get_cell(w_x, x + 1, y - 1);
	count += world_get_cell(w_x, x + 1, y	 );
	count += world_get_cell(w_x, x + 1, y + 1);


	return count;
}

// Accede al array y devuelve la célula de coordenadas (x, y)
// Permite coodenadas fuera de los límites del array
// (-1, 0) --> (W_SIZE_X-1, 0) ó devover DEAD
bool world_get_cell(bool w_x[W_SIZE_X][W_SIZE_Y], int x, int y)
{

	// TODO:
	// if (x < 0)
	// ...
	// else if (x >= W_SIZE_X)
	// ...

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

	cell=w_x[x][y];

	return cell;

}

void world_copy(bool w_y[W_SIZE_X][W_SIZE_Y], bool w_x[W_SIZE_X][W_SIZE_Y])
{
	for (int i=0;i<W_SIZE_X;i++){
		for (int j=0;j<W_SIZE_Y;j++){
			w_x[i][j]=w_y[i][j];
		}
	}
}

int main()
{
	int i = 0;

	bool w_1[W_SIZE_X][W_SIZE_Y];

	bool w_2[W_SIZE_X][W_SIZE_Y];

	world_init(w_1);

	do {
		printf("\033cIteration %d\n", i++);

		world_print(w_1);

		world_step(w_1, w_2);

	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}




