#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

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
