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

static void draw_floor_and_ceiling(struct game_state *state, struct world *world) {
    struct texture *floor_texture = assets_get_texture(GREY_STONE);
    struct texture *ceiling_texture = assets_get_texture(WOOD);

    for (size_t y = 0; y < SCREEN_HEIGHT; y++) {
        struct vec2 ray_dir0 = vec2_sub(world->cam_dir, world->cam_plane);
        struct vec2 ray_dir1 = vec2_sum(world->cam_dir, world->cam_plane);

        int p = y - SCREEN_HEIGHT / 2;
        float pos_z = 0.5f * SCREEN_HEIGHT;
        float row_dist = pos_z / p;

        struct vec2 step = vec2_mul(vec2_sub(ray_dir1, ray_dir0), row_dist / SCREEN_WIDTH);
        struct vec2 floor_vec = vec2_sum(world->cam_pos, vec2_mul(ray_dir0, row_dist));

        for (int x = 0; x < SCREEN_WIDTH; x++) {
            int cell_x = (int)floor_vec.x;
            int cell_y = (int)floor_vec.y;

            int floor_texture_x =
                (int)(floor_texture->width * (floor_vec.x - cell_x)) & (floor_texture->width - 1);
            int floor_texture_y =
                (int)(floor_texture->height * (floor_vec.y - cell_y)) & (floor_texture->height - 1);

            int ceiling_texture_x = (int)(ceiling_texture->width * (floor_vec.x - cell_x)) &
                                    (ceiling_texture->width - 1);
            int ceiling_texture_y = (int)(ceiling_texture->height * (floor_vec.y - cell_y)) &
                                    (ceiling_texture->height - 1);

            floor_vec = vec2_sum(floor_vec, step);

            uint32_t floor_color;
            uint32_t ceiling_color;
            if (state->mode == COLORED_WORLD_MODE) {
                SDL_Color color = assets_get_color(FLOOR);
                floor_color = (sdl_color_to_uint32(color) >> 1) & 8355711;

                color = assets_get_color(CEILING);
                ceiling_color = (sdl_color_to_uint32(color) >> 1) & 8355711;
            } else {
                floor_color =
                    floor_texture->pixels[floor_texture_y * floor_texture->width + floor_texture_x];
                floor_color = (floor_color >> 1) & 8355711;

                ceiling_color =
                    ceiling_texture
                        ->pixels[ceiling_texture_y * ceiling_texture->width + ceiling_texture_x];
                ceiling_color = (ceiling_color >> 1) & 8355711;
            }
            state->pixels[y * SCREEN_WIDTH + x] = floor_color;
            state->pixels[(SCREEN_HEIGHT - y - 1) * SCREEN_WIDTH + x] = ceiling_color;
        }
    }
}

void draw_world(struct game_state *state, struct world *world) {
    draw_floor_and_ceiling(state, world);

    struct ray *rays = compute_rays(world);
    for (size_t x = 0; x < SCREEN_WIDTH; x++) {
        struct ray *ray = &rays[x];

        int line_height = (int)(SCREEN_HEIGHT / ray->length);

        int line_begin = MAX(-line_height / 2 + SCREEN_HEIGHT / 2, 0);
        int line_end = MIN(line_height / 2 + SCREEN_HEIGHT / 2, SCREEN_HEIGHT - 1);

        if (state->mode == COLORED_WORLD_MODE) {
            SDL_Color color = assets_get_color(ray->hit_tile);
            if (ray->hit_side == VERTICAL_SIDE) {
                color.r /= 2;
                color.g /= 2;
                color.b /= 2;
            }
            SDL_SetRenderDrawColor(state->renderer, color.r, color.g, color.b, color.a);

            uint32_t color_uint32 = sdl_color_to_uint32(color);
            for (size_t y = line_begin; y <= line_end; y++)
                state->pixels[y * SCREEN_WIDTH + x] = color_uint32;
        } else if (state->mode == TEXTURED_WORLD_MODE) {
            struct texture *texture = assets_get_texture(ray->hit_tile);

            int texture_x = (int)(ray->hit_x * (float)texture->width);
            if (ray->hit_side == VERTICAL_SIDE && ray->dir.x > 0 ||
                ray->hit_side == HORIZONTAL_SIDE && ray->dir.y < 0)
                texture_x = texture->width - texture_x - 1;

            float step = (float)texture->height / line_height;
            float texture_pos = (float)(line_begin - SCREEN_HEIGHT / 2 + line_height / 2) * step;
            for (size_t y = line_begin; y <= line_end; y++) {
                int tex_y = (int)texture_pos & (texture->height - 1);
                texture_pos += step;
                uint32_t color = texture->pixels[texture->height * tex_y + texture_x];
                if (ray->hit_side == VERTICAL_SIDE)
                    color = (color >> 1) & 8355711;
                state->pixels[y * SCREEN_WIDTH + x] = color;
            }
        }
    }
}
