#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "raycast.h"

struct tiled_map {
    size_t width;
    size_t height;
    uint32_t *data;
};

struct tiled_map *load_tiled_map(FILE *file);
void draw_top_view_map(SDL_Renderer *renderer, struct tiled_map *map, struct camera *camera,
                       struct raycaster *raycaster);
void free_tiled_map(struct tiled_map *map);
