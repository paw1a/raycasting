#pragma once

#include <SDL.h>

int create_assets(SDL_Renderer *renderer);

#define COLORS_COUNT 11
enum color_type {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 3,
    YELLOW = 4,
    ORANGE = 5,
    PINK = 6,
    WHITE = 7,
    PURPLE = 8,
    FLOOR = 9,
    CEILING = 10
};

SDL_Color assets_get_color(enum color_type type);

#define TEXTURES_COUNT 12
enum texture_type {
    EMPTY = 0,
    BARREL = 9,
    BLUE_STONE = 5,
    COLOR_STONE = 8,
    EAGLE = 1,
    GREEN_LIGHT = 11,
    GREY_STONE = 4,
    MOSSY = 6,
    PILLAR = 10,
    PURPLE_STONE = 3,
    RED_BRICK = 2,
    WOOD = 7
};

struct texture {
    int width;
    int height;
    uint32_t *pixels;
};

struct texture *assets_get_texture(enum texture_type type);
struct texture *assets_load_texture(const char *filename, SDL_Renderer *renderer);
void destroy_assets(void);
