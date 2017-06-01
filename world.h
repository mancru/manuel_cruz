#ifndef _WORLD_H_
#define _WORLD_H_
#define ALIVE 1
#define DEAD 0
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "config.h"

struct world;
struct world_limited;
struct world_toroidal;
struct config;

struct world *world_alloc(struct config * config);
void world_free(struct world *w);

void world_print(const struct world *w);
void world_iterate(struct world *w);
void world_init (struct config * config, struct world * w);

#endif
