#include "world.h"

struct world *create_world(const char *map_filename) {
    FILE *file = fopen(map_filename, "r");
    if (file == NULL) {
        printf("failed to open map file\n");
        return NULL;
    }

    struct vec2 player_pos;
    struct tiled_map *map = load_tiled_map(file, &player_pos);
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
    world->cam_pos = player_pos;
    world->cam_dir = (struct vec2){0, 1};
    world->cam_plane = (struct vec2){0.66f, 0};

    return world;
}

void destroy_world(struct world *world) {
    free_tiled_map(world->map);
    free(world);
}
