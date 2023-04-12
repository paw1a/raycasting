#include "minimap.h"
#include "asset.h"
#include "raycast.h"
#include "world.h"

#include <SDL.h>

static void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    int x_offset = 0;
    int y_offset = 0;

    if (x2 - x1 > 0)
        x_offset = -1;
    if (y2 - y1 > 0)
        y_offset = -1;

    SDL_RenderDrawLine(renderer, x1, y1, x2 + x_offset, y2 + y_offset);
}

static void fill_rect(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_RenderFillRect(renderer, &rect);
}

static void draw_rect(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_RenderDrawRect(renderer, &rect);
}

void draw_minimap(struct game_state *state, struct world *world) {
    struct tiled_map *map = world->map;
    const int tile_size = MIN(SCREEN_WIDTH / map->width, SCREEN_HEIGHT / map->height);
    const int camera_size = tile_size / 2;

    for (size_t i = 0; i < map->height; i++) {
        for (size_t j = 0; j < map->width; j++) {
            uint32_t tile = map->data[i * map->width + j];
            SDL_Color color = colors[tile];
            SDL_SetRenderDrawColor(state->renderer, color.r, color.g, color.b, color.a);

            fill_rect(state->renderer, j * tile_size, i * tile_size, tile_size, tile_size);
        }
    }

    SDL_SetRenderDrawColor(state->renderer, 255, 255, 0, 255);
    fill_rect(state->renderer, (int)(world->cam_pos.x * tile_size) - camera_size / 2,
              (int)(world->cam_pos.y * tile_size) - camera_size / 2, camera_size, camera_size);

    struct ray *rays = compute_rays(world);
    for (size_t i = 0; i < SCREEN_WIDTH; i++) {
        struct ray *ray = &rays[i];
        struct vec2 ray_vec = vec2_sum(ray->begin, vec2_mul(ray->dir, ray->length));

        draw_line(state->renderer, (int)(world->cam_pos.x * tile_size),
                  (int)(world->cam_pos.y * tile_size), (int)(ray_vec.x * tile_size),
                  (int)(ray_vec.y * tile_size));
    }
}
