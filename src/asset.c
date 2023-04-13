#include "asset.h"

#include <SDL.h>
#include <SDL_image.h>

static SDL_Color colors[COLORS_COUNT];
static SDL_Texture *textures[TEXTURES_COUNT];

static void load_colors(void) {
    colors[BLACK] = (SDL_Color){0, 0, 0, 255};
    colors[RED] = (SDL_Color){255, 0, 0, 255};
    colors[GREEN] = (SDL_Color){0, 255, 0, 255};
    colors[BLUE] = (SDL_Color){0, 0, 255, 255};
    colors[YELLOW] = (SDL_Color){255, 255, 0, 255};
    colors[ORANGE] = (SDL_Color){255, 165, 0, 255};
    colors[PINK] = (SDL_Color){255, 192, 200, 255};
    colors[WHITE] = (SDL_Color){255, 255, 255, 255};
    colors[PURPLE] = (SDL_Color){128, 0, 64, 255};
}

int create_assets(SDL_Renderer *renderer) {
    load_colors();

    textures[EMPTY] = NULL;
    textures[BARREL] = assets_load_texture("assets/textures/barrel.png", renderer);
    textures[BLUE_STONE] = assets_load_texture("assets/textures/bluestone.png", renderer);
    textures[COLOR_STONE] = assets_load_texture("assets/textures/colorstone.png", renderer);
    textures[EAGLE] = assets_load_texture("assets/textures/eagle.png", renderer);
    textures[GREEN_LIGHT] = assets_load_texture("assets/textures/greenlight.png", renderer);
    textures[GREY_STONE] = assets_load_texture("assets/textures/greystone.png", renderer);
    textures[MOSSY] = assets_load_texture("assets/textures/mossy.png", renderer);
    textures[PILLAR] = assets_load_texture("assets/textures/pillar.png", renderer);
    textures[PURPLE_STONE] = assets_load_texture("assets/textures/purplestone.png", renderer);
    textures[RED_BRICK] = assets_load_texture("assets/textures/redbrick.png", renderer);
    textures[WOOD] = assets_load_texture("assets/textures/wood.png", renderer);

    for (size_t i = 1; i < TEXTURES_COUNT; i++)
        if (textures[i] == NULL) {
            printf("failed to load textrure with index %zu\n", i);
            return -1;
        }

    return 0;
}

SDL_Color assets_get_color(enum color_type type) {
    return colors[type];
}

SDL_Texture* assets_load_texture(const char *filename, SDL_Renderer *renderer) {
    SDL_Surface* image_surface = IMG_Load(filename);
    if(image_surface == NULL) {
        printf("failed to load image %s: %s\n", filename, IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    if(texture == NULL) {
        SDL_FreeSurface(image_surface);
        printf("failed to create texture from surface: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_FreeSurface(image_surface);

    return texture;
}

SDL_Texture *assets_get_texture(enum texture_type type) {
    return textures[type];
}
