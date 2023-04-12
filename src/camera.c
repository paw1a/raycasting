#include "camera.h"
#include "draw.h"

#include <SDL.h>

struct camera *create_camera(float x, float y, int fov) {
    struct camera *camera = malloc(sizeof(*camera));
    if (camera == NULL)
        return NULL;

    camera->pos = (struct vec2){x, y};
    camera->dir = (struct vec2){0, 1};
    camera->plane = (struct vec2){0.66f, 0};
    camera->fov = fov;

    return camera;
}
