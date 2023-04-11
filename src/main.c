#include <SDL.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH  1080
#define SCREEN_HEIGHT 720

struct window_state {
    bool quit;
    SDL_Window *window;
    SDL_Renderer *renderer;
    unsigned int pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
};

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to init sdl: %s\n", SDL_GetError());
        return -1;
    }

    struct window_state *state = malloc(sizeof(*state));
    assert(state != NULL);

    state->window = SDL_CreateWindow("Doom raycasting", SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                     SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (state->window == NULL) {
        printf("failed to create window: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(state->window, -1,
                                                SDL_RENDERER_ACCELERATED |
                                                    SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("failed to create renderer: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Event event;
    while (!state->quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state->quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    state->quit = true;
                    break;
                }
            }
        }
    }

    SDL_DestroyWindow(state->window);
    SDL_Quit();

    return 0;
}
