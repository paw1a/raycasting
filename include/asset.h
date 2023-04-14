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
    BARREL = 1,
    BLUE_STONE = 2,
    COLOR_STONE = 3,
    EAGLE = 4,
    GREEN_LIGHT = 5,
    GREY_STONE = 6,
    MOSSY = 7,
    PILLAR = 8,
    PURPLE_STONE = 9,
    RED_BRICK = 10,
    WOOD = 11
};

struct texture {
    int width;
    int height;
    uint32_t *pixels;
};

struct texture *assets_get_texture(enum texture_type type);
struct texture *assets_load_texture(const char *filename, SDL_Renderer *renderer);
void destroy_assets(void);
