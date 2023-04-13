#include "asset.h"

#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>

static SDL_Color colors[COLORS_COUNT];
static struct texture *textures[TEXTURES_COUNT];

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
            printf("failed to load texture with index %zu\n", i);
            return -1;
        }

    return 0;
}

SDL_Color assets_get_color(enum color_type type) {
    assert(type < COLORS_COUNT);
    return colors[type];
}

static uint32_t get_pixel(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (uint8_t *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
    case 1:
        return *p;
    case 2:
        return *(uint16_t *)p;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
        return *(uint32_t *)p;
    default:
        return 0;
    }
}

struct texture *assets_load_texture(const char *filename, SDL_Renderer *renderer) {
    SDL_Surface* surface = IMG_Load(filename);
    if(surface == NULL) {
        printf("failed to load image %s: %s\n", filename, IMG_GetError());
        return NULL;
    }

    struct texture *texture = malloc(sizeof(*texture) + surface->w * surface->h * sizeof(uint32_t));
    if (texture == NULL) {
        SDL_FreeSurface(surface);
        return NULL;
    }

    texture->width = surface->w;
    texture->height = surface->h;
    texture->pixels = (uint32_t *)(texture + 1);

    for (int y = 0; y < texture->height; y++)
        for (int x = 0; x < texture->width; x++)
            texture->pixels[y * texture->width + x] = get_pixel(surface, x, y);

    SDL_FreeSurface(surface);

    return texture;
}

struct texture *assets_get_texture(enum texture_type type) {
    assert(type < TEXTURES_COUNT);
    return textures[type];
}

void destroy_assets(void) {
    for (size_t i = 0; i < TEXTURES_COUNT; i++)
        free(textures[i]);
}
