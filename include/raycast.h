#pragma once

#include <stdlib.h>
#include "vector.h"
#include "common.h"
#include "map.h"
#include "camera.h"

enum ray_hit_side {
    VERTICAL_SIDE,
    HORIZONTAL_SIDE
};

struct ray {
    struct vec2 begin;
    struct vec2 dir;
    float length;

    enum ray_hit_side hit_side;
    uint32_t hit_entry;
};

struct raycaster {
    size_t screen_width;
    size_t screen_height;
    struct ray *rays;
};

struct raycaster *create_raycaster(size_t screen_width, size_t screen_height);
void update_raycaster(struct raycaster *raycaster, struct tiled_map *map, struct camera *camera);