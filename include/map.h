#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "raycast.h"

#define TILE_TYPE_PLAYER 1

struct tiled_map {
    size_t width;
    size_t height;
    uint32_t *data;
};

struct tiled_map *load_tiled_map(FILE *file);
void free_tiled_map(struct tiled_map *map);
