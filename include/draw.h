#pragma once

#include "map.h"
#include <SDL.h>

void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
void fill_rect(SDL_Renderer *renderer, int x, int y, int width, int height);
void draw_rect(SDL_Renderer *renderer, int x, int y, int width, int height);

SDL_Color get_sdl_color(uint32_t color_index);
void clear_renderer(SDL_Renderer *renderer);
void present_renderer(SDL_Renderer *renderer);
