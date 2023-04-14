#pragma once

#include <math.h>

struct vec2 {
    float x;
    float y;
};

static inline float vec2_len(struct vec2 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

static inline struct vec2 vec2_neg(struct vec2 v) {
    return (struct vec2){-v.x, -v.y};
}

static inline struct vec2 vec2_sum(struct vec2 v1, struct vec2 v2) {
    return (struct vec2){v1.x + v2.x, v1.y + v2.y};
}

static inline struct vec2 vec2_sub(struct vec2 v1, struct vec2 v2) {
    return (struct vec2){v1.x - v2.x, v1.y - v2.y};
}

static inline struct vec2 vec2_mul(struct vec2 v, float n) {
    return (struct vec2){v.x * n, v.y * n};
}

static inline struct vec2 vec2_norm(struct vec2 v) {
    return vec2_mul(v, 1 / vec2_len(v));
}

static inline struct vec2 vec2_rotate(struct vec2 v, float angle) {
    struct vec2 result;
    result.x = v.x * cosf(angle) - v.y * sinf(angle);
    result.y = v.x * sinf(angle) + v.y * cosf(angle);
    return result;
}
