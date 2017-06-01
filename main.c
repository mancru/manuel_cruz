#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "world.h"
#include "world_limited.h"
#include "world_toroidal.h"

#include "config.h"

int main(int argc, char *argv[])
{
	struct config config;
	struct world_limited;
	struct world * world;

	if (!config_parse_argv(&config, argc, argv)){
		printf("ERROR\n");
		config_print_usage(argv[0]);
		return EXIT_FAILURE;
	} else if (config.show_help){
		config_print_usage(argv[0]);
		return EXIT_SUCCESS;
	}

	int borders = config.borders_mode;
	void * w = NULL;

	if (borders == CFB_DEFAULT ||
		borders == CFB_TOROIDAL){

		w = world_toroidal_alloc(&config);
		if (!w){
			perror("Can't allocate world");
			exit(EXIT_FAILURE);
		}

	} else if (borders == CFB_LIMITED){

		w = world_limited_alloc(&config);
		if (!w){
			perror("Can't allocate limited world");
			exit(EXIT_FAILURE);
		}
	}

	int iIteracion = 0;
	do {
		printf("\033cIteration %d\n", iIteracion++);
		config_print(&config);
		world_print(w);
		world_iterate(w);
	} while (getchar() != 'q');

	if (w){
		//if (borders == CFB_TOROIDAL){ 
			//world_toroidal_free(w);
		//} else {
			world=(struct world *)w;
			world->world_free(w);
		//}
	}
	return EXIT_SUCCESS;
}
