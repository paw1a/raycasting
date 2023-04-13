#pragma once

#include "common.h"
#include "vector.h"
#include "world.h"
#include <stdlib.h>

enum ray_hit_side {
    VERTICAL_SIDE,
    HORIZONTAL_SIDE
};

struct ray {
    struct vec2 begin;
    struct vec2 dir;
    float length;

    enum ray_hit_side hit_side;
    uint32_t hit_tile;
    float hit_x;
};

int create_raycast(void);
struct ray *compute_rays(struct world *world);
void destroy_raycast(void);
