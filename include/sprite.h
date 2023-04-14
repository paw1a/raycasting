#pragma once

#include "asset.h"
#include "vector.h"

struct sprite {
    struct vec2 pos;
    struct texture *texture;
};

#define SPRITES_COUNT 19

void create_sprites(void);
void sort_sprites_by_distance(struct vec2 point);
struct sprite get_sprite(int index);
