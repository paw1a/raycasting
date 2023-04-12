#pragma once

#include "vector.h"
#include <SDL.h>

struct camera {
    struct vec2 pos;
    struct vec2 dir;
    struct vec2 plane;
    int fov;
};

struct camera *create_camera(float x, float y, int fov);
