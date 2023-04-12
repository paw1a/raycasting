#pragma once

#include "map.h"

struct world {
    struct vec2 cam_pos;
    struct vec2 cam_dir;
    struct vec2 cam_plane;
    struct tiled_map *map;
};

struct world *create_world(char *map_filename);
void destroy_world(struct world *world);
