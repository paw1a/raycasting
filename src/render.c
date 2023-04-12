#include "render.h"
#include "asset.h"
#include "common.h"
#include "raycast.h"
#include "world.h"

static uint32_t sdl_color_to_uint32(SDL_Color color) {
    uint32_t num = color.r;
    num |= (color.g << 8);
    num |= (color.b << 16);
    num |= (color.a << 24);

    return num;
}

void draw_world(struct game_state *state, struct world *world) {
    struct ray *rays = compute_rays(world);
    for (size_t x = 0; x < SCREEN_WIDTH; x++) {
        struct ray *ray = &rays[x];

        int line_height = (int)(SCREEN_HEIGHT / ray->length);

        int line_begin = MAX(-line_height / 2 + SCREEN_HEIGHT / 2, 0);
        int line_end = MIN(line_height / 2 + SCREEN_HEIGHT / 2, SCREEN_HEIGHT - 1);

        SDL_Color color = colors[ray->hit_entry];
        if (ray->hit_side == VERTICAL_SIDE) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }
        SDL_SetRenderDrawColor(state->renderer, color.r, color.g, color.b, color.a);

        uint32_t color_uint32 = sdl_color_to_uint32(color);
        for (size_t y = line_begin; y <= line_end; y++)
            state->pixels[y * SCREEN_WIDTH + x] = color_uint32;
    }
}
