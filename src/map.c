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

//    for (size_t i = 0; i < map->height; i++) {
//        for (size_t j = 0; j < map->width; j++) {
//            uint32_t tile = map->data[i * map->width + j];
//            SDL_Color color = get_sdl_color(tile);
//            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
//            fill_rect(renderer, j * tile_size, i * tile_size, tile_size, tile_size);
//        }
//    }
//
//    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
//    fill_rect(renderer, (int)(camera->pos.x * tile_size) - camera_size / 2,
//              (int)(camera->pos.y * tile_size) - camera_size / 2, camera_size, camera_size);
//
//    struct vec2 dir = vec2_mul(camera->dir, 1);
//    struct vec2 result = vec2_sum(camera->pos, dir);
//    draw_line(renderer, (int)(camera->pos.x * tile_size), (int)(camera->pos.y * tile_size),
//              (int)(result.x * tile_size), (int)(result.y * tile_size));
//
//    for (size_t i = 0; i < raycaster->screen_width; i++) {
//        struct ray *ray = &raycaster->rays[i];
//        struct vec2 res = vec2_sum(ray->begin, vec2_mul(ray->dir, ray->length));
//        draw_line(renderer, (int)(camera->pos.x * tile_size), (int)(camera->pos.y * tile_size),
//                  (int)(res.x * tile_size), (int)(res.y * tile_size));
//    }

    for (size_t i = 0; i < raycaster->screen_width; i++) {
        struct ray *ray = &raycaster->rays[i];
        int line_height = (int)(SCREEN_HEIGHT / ray->length);
        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_end >= SCREEN_HEIGHT)
            draw_end = SCREEN_HEIGHT - 1;

        SDL_Color color = get_sdl_color(ray->hit_entry);
        if (ray->hit_side == VERTICAL_SIDE) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        draw_line(renderer, i, draw_start, i, draw_end);
    }
}

void free_tiled_map(struct tiled_map *map) {
    free(map);
}
