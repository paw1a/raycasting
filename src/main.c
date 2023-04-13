#include <SDL.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "asset.h"
#include "common.h"
#include "map.h"
#include "minimap.h"
#include "raycast.h"
#include "render.h"
#include "world.h"

#define CAMERA_SPEED 0.2
#define ROTATE_SPEED (2 * (2 * M_PI / 360))

static int init_game_state(struct game_state *state) {
    state->window =
        SDL_CreateWindow("Doom raycasting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (state->window == NULL) {
        printf("failed to create window: %s\n", SDL_GetError());
        return -1;
    }

    state->renderer =
        SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (state->renderer == NULL) {
        printf("failed to create renderer: %s\n", SDL_GetError());
        return -1;
    }

    state->texture = SDL_CreateTexture(state->renderer, SDL_PIXELFORMAT_ABGR8888,
                                       SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (state->texture == NULL) {
        printf("failed to create texture: %s\n", SDL_GetError());
        return -1;
    }

    state->quit = false;
    state->mode = TEXTURED_WORLD_MODE;

    return 0;
}

static void handle_events(struct game_state *state, struct world *world) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            state->quit = true;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                state->quit = true;
                break;
            case SDLK_UP:
                world->cam_pos = vec2_sum(world->cam_pos, vec2_mul(world->cam_dir, CAMERA_SPEED));
                break;
            case SDLK_DOWN:
                world->cam_pos =
                    vec2_sum(world->cam_pos, vec2_mul(vec2_neg(world->cam_dir), CAMERA_SPEED));
                break;
            case SDLK_LEFT:
                world->cam_dir = vec2_rotate(world->cam_dir, ROTATE_SPEED);
                world->cam_plane = vec2_rotate(world->cam_plane, ROTATE_SPEED);
                break;
            case SDLK_RIGHT:
                world->cam_dir = vec2_rotate(world->cam_dir, -ROTATE_SPEED);
                world->cam_plane = vec2_rotate(world->cam_plane, -ROTATE_SPEED);
                break;
            case SDLK_m:
                if (state->mode == MINIMAP_MODE)
                    state->mode = TEXTURED_WORLD_MODE;
                else
                    state->mode = MINIMAP_MODE;
                break;
            }
        }
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to init sdl: %s\n", SDL_GetError());
        return -1;
    }

    struct game_state *state = malloc(sizeof(*state));
    assert(state != NULL);
    if (init_game_state(state)) {
        printf("failed to init game state\n");
        return -1;
    }

    if (create_assets(state->renderer)) {
        printf("failed to create assets\n");
        return -1;
    }

    struct world *world = create_world("assets/map.txt");
    if (world == NULL) {
        printf("failed to create world\n");
        return -1;
    }

    if (create_raycast()) {
        printf("failed to create raycast\n");
        return -1;
    }

    while (!state->quit) {
        handle_events(state, world);

        SDL_Color back = assets_get_color(BLACK);
        SDL_SetRenderDrawColor(state->renderer, back.r, back.g, back.b, back.a);
        SDL_RenderClear(state->renderer);
        memset(state->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

        switch (state->mode) {
        case MINIMAP_MODE:
            draw_minimap(state, world);
            break;
        case TEXTURED_WORLD_MODE:
        case COLORED_WORLD_MODE:
            draw_world(state, world);
            SDL_UpdateTexture(state->texture, NULL, state->pixels, SCREEN_WIDTH * 4);
            SDL_RenderCopy(state->renderer, state->texture, NULL, NULL);
            break;
        }

        SDL_RenderPresent(state->renderer);
        SDL_Delay(10);
    }

    destroy_assets();
    destroy_raycast();
    destroy_world(world);
    SDL_DestroyWindow(state->window);
    SDL_Quit();

    return 0;
}
