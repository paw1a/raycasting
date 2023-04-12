#pragma once

#include <SDL.h>
#include "map.h"

void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
void fill_rect(SDL_Renderer *renderer, int x, int y, int width, int height);
void draw_rect(SDL_Renderer *renderer, int x, int y, int width, int height);

void clear_renderer(SDL_Renderer *renderer);
void present_renderer(SDL_Renderer *renderer);

void draw_top_view_map(SDL_Renderer *renderer, struct map *map);
