#include "map.h"

struct map *load_map(FILE *file) {
    size_t width, height;
    if (fscanf(file, "%zu%zu", &width, &height) != 2) {
        printf("invalid map sizes\n");
        return NULL;
    }

    struct map *map =
        malloc(sizeof(*map) + width * height * sizeof(uint32_t));
    if (map == NULL)
        return NULL;

    map->width = width;
    map->height = height;
    map->data = (uint32_t *)(map + 1);

    for (size_t i = 0; i < map->height; i++) {
        for (size_t j = 0; j < map->width; j++) {
            uint32_t tile;
            if (fscanf(file, "%u", &tile) != 1) {
                printf("corrupted map data\n");
                return NULL;
            }

            map->data[i * map->width + j] = tile;
        }
    }

    return map;
}

void free_map(struct map *map) {
    free(map);
}
