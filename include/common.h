#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#include "map.h"
#include "camera.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

struct state {
    bool quit;
    SDL_Window *window;
    SDL_Renderer *renderer;
    uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
};
