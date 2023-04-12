#include "map.h"
#include "camera.h"
#include "draw.h"
#include "raycast.h"

struct tiled_map *load_tiled_map(FILE *file) {
    size_t width, height;
    if (fscanf(file, "%zu%zu", &width, &height) != 2) {
        printf("invalid map sizes\n");
        return NULL;
    }

    struct tiled_map *map = malloc(sizeof(*map) + width * height * sizeof(uint32_t));
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

void draw_top_view_map(SDL_Renderer *renderer, struct tiled_map *map, struct camera *camera, struct raycaster *raycaster) {
    const size_t tile_size = 16;
    const size_t camera_size = 10;

    for (size_t i = 0; i < map->height; i++) {
        for (size_t j = 0; j < map->width; j++) {
            uint32_t tile = map->data[i * map->width + j];
            switch (tile) {
            case 1:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                break;
            case 2:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                break;
            case 3:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                break;
            case 4:
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                break;
            case 5:
                SDL_SetRenderDrawColor(renderer, 255, 128, 255, 255);
                break;
            default:
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            }

            fill_rect(renderer, j * tile_size, i * tile_size, tile_size, tile_size);
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    fill_rect(renderer, (int)(camera->pos.x * tile_size) - camera_size / 2,
              (int)(camera->pos.y * tile_size) - camera_size / 2, camera_size, camera_size);

    struct vec2 dir = vec2_mul(camera->dir, 1);
    struct vec2 result = vec2_sum(camera->pos, dir);
    draw_line(renderer, (int)(camera->pos.x * tile_size), (int)(camera->pos.y * tile_size),
              (int)(result.x * tile_size), (int)(result.y * tile_size));

    for (size_t i = 0; i < raycaster->screen_width; i++) {
        struct ray *ray = &raycaster->rays[i];
        struct vec2 res = vec2_sum(ray->begin, vec2_mul(ray->dir, ray->length));
        draw_line(renderer, (int)(camera->pos.x * tile_size), (int)(camera->pos.y * tile_size),
                  (int)(res.x * tile_size), (int)(res.y * tile_size));
    }
}

void free_tiled_map(struct tiled_map *map) {
    free(map);
}
