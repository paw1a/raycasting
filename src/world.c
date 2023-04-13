#include "world.h"

static struct vec2 find_player_position(struct tiled_map *map) {
    for (size_t i = 0; i < map->height; i++)
        for (size_t j = 0; j < map->width; j++)
            if (map->data[i * map->width + j] == TILE_TYPE_PLAYER) {
                map->data[i * map->width + j] = 0;
                return (struct vec2){j, i};
            }

    return (struct vec2){map->width / 2, map->height / 2};
}

struct world *create_world(const char *map_filename) {
    FILE *file = fopen(map_filename, "r");
    if (file == NULL) {
        printf("failed to open map file\n");
        return NULL;
    }

    struct tiled_map *map = load_tiled_map(file);
    if (map == NULL) {
        printf("failed to create map\n");
        fclose(file);
        return NULL;
    }

    fclose(file);

    struct world *world = malloc(sizeof(*world));
    if (world == NULL) {
        free_tiled_map(map);
        return NULL;
    }

    world->map = map;
    world->cam_pos = find_player_position(map);
    world->cam_dir = (struct vec2){0, 1};
    world->cam_plane = (struct vec2){0.66f, 0};

    return world;
}

void destroy_world(struct world *world) {
    free_tiled_map(world->map);
    free(world);
}
