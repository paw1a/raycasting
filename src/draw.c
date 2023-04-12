#include "draw.h"
#include "raycast.h"
#include "map.h"

#include <stdint.h>

void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    int x_offset = 0;
    int y_offset = 0;

    if (x2 - x1 > 0)
        x_offset = -1;
    if (y2 - y1 > 0)
        y_offset = -1;

    SDL_RenderDrawLine(renderer, x1, y1, x2 + x_offset, y2 + y_offset);
}

void fill_rect(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_RenderFillRect(renderer, &rect);
}

void draw_rect(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_RenderDrawRect(renderer, &rect);
}

void draw_top_view_map(SDL_Renderer *renderer, struct map *map) {
    const size_t tile_size = 15;

    for (size_t i = 0; i < map->height; i++) {
        for (size_t j = 0; j < map->width; j++) {
            uint32_t tile = map->data[i * map->width + j];
            switch (tile) {
            case 1:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                break;
            case 2:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                break;
            case 3:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                break;
            case 4:
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                break;
            case 5:
                SDL_SetRenderDrawColor(renderer, 255, 128, 255, 255);
                break;
            default:
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            }

            fill_rect(renderer, j * tile_size, i * tile_size, tile_size, tile_size);
        }
    }
}

void clear_renderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void present_renderer(SDL_Renderer *renderer) {
    SDL_RenderPresent(renderer);
}
