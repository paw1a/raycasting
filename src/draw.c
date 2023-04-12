#include "draw.h"

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

SDL_Color get_sdl_color(uint32_t color_index) {
    SDL_Color color;
    switch (color_index) {
    case 1:
        color = (SDL_Color) {255, 0, 0, 255};
        break;
    case 2:
        color = (SDL_Color) {0, 255, 0, 255};
        break;
    case 3:
        color = (SDL_Color) {0, 0, 255, 255};
        break;
    case 4:
        color = (SDL_Color) {255, 255, 255, 255};
        break;
    case 5:
        color = (SDL_Color) {255, 128, 255, 255};
        break;
    default:
        color = (SDL_Color) {0, 0, 0, 255};
        break;
    }

    return color;
}

void clear_renderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void present_renderer(SDL_Renderer *renderer) {
    SDL_RenderPresent(renderer);
}
