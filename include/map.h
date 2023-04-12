#pragma once

#include <stdio.h>
#include <stdlib.h>

struct map {
    size_t width;
    size_t height;
    uint32_t *data;
};

struct map *load_map(FILE *file);
void free_map(struct map *map);
