#pragma once

#include <math.h>

struct vec2 {
    float x;
    float y;
};

static inline struct vec2 vec2_rotate(struct vec2 v, float angle) {
    struct vec2 result;
    result.x = v.x * cos(angle) - v.y * sin(angle);
    result.y = v.y * sin(angle) + v.y * cos(angle);
    return result;
}
