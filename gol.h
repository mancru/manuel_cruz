#ifndef _GOL_H_
#define _GOL_H_
#define ALIVE 1
#define DEAD 0
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "config.h"

struct world;

struct world *world_alloc(struct config * config);
void world_free(struct world *w);

void world_print(const struct world *w);
void world_iterate(struct world *w);

#endif
