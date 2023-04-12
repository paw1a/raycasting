#include <SDL.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "camera.h"
#include "draw.h"
#include "map.h"
#include "raycast.h"
#include "common.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to init sdl: %s\n", SDL_GetError());
        return -1;
    }

    struct state *state = malloc(sizeof(*state));
    assert(state != NULL);

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

    FILE *file = fopen("../assets/map.txt", "r");
    if (file == NULL) {
        printf("failed to open map file\n");
        return -1;
    }

    struct tiled_map *map = load_tiled_map(file);
    if (map == NULL) {
        printf("failed to create map\n");
        return -1;
    }
    fclose(file);

    struct camera *camera = create_camera(map->width / 2, map->height / 2, 60);
    if (camera == NULL) {
        printf("failed to create camera\n");
        return -1;
    }

    struct raycaster *raycaster = create_raycaster(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (raycaster == NULL) {
        printf("failed to create raycaster\n");
        return -1;
    }

    SDL_Event event;
    while (!state->quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state->quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                const float camera_speed = 0.2f;

                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    state->quit = true;
                    break;
                case SDLK_UP:
                    camera->pos = vec2_sum(camera->pos, vec2_mul(camera->dir, camera_speed));
                    break;
                case SDLK_DOWN:
                    camera->pos =
                        vec2_sum(camera->pos, vec2_mul(vec2_neg(camera->dir), camera_speed));
                    break;
                case SDLK_LEFT:
                    camera->dir = vec2_rotate(camera->dir, -24.0f / 360);
                    camera->plane = vec2_rotate(camera->plane, -24.0f / 360);
                    break;
                case SDLK_RIGHT:
                    camera->dir = vec2_rotate(camera->dir, 24.0f / 360);
                    camera->plane = vec2_rotate(camera->plane, 24.0f / 360);
                    break;
                }
            }
        }

        clear_renderer(state->renderer);

        update_raycaster(raycaster, map, camera);
        draw_top_view_map(state->renderer, map, camera, raycaster);

        present_renderer(state->renderer);
        SDL_Delay(10);
    }

    SDL_DestroyWindow(state->window);
    SDL_Quit();

    return 0;
}
