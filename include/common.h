#pragma once

#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

enum game_mode {
    MINIMAP_MODE,
    WORLD_MODE
};

struct game_state {
    bool quit;
    enum game_mode mode;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
};
