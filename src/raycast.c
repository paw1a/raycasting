#include "raycast.h"

#include <math.h>

struct raycaster *create_raycaster(size_t screen_width, size_t screen_height) {
    struct raycaster *raycaster = malloc(sizeof(*raycaster) + screen_width * sizeof(struct ray));
    if (raycaster == NULL)
        return NULL;

    raycaster->screen_width = screen_width;
    raycaster->screen_height = screen_height;
    raycaster->rays = (struct ray *)(raycaster + 1);

    return raycaster;
}

void update_raycaster(struct raycaster *raycaster, struct tiled_map *map, struct camera *camera) {
    for (size_t x = 0; x < raycaster->screen_width; x++) {
        float plane_size = 2.0f * x / raycaster->screen_width - 1;
        struct vec2 ray_vec = vec2_sum(camera->dir, vec2_mul(camera->plane, plane_size));

        int map_x = (int)camera->pos.x;
        int map_y = (int)camera->pos.y;

        float delta_x = fabs(1 / ray_vec.x);
        float delta_y = fabs(1 / ray_vec.y);

        float side_dist_x;
        float side_dist_y;
        int step_x;
        int step_y;

        if(ray_vec.x < 0) {
            step_x = -1;
            side_dist_x = (camera->pos.x - map_x) * delta_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - camera->pos.x) * delta_x;
        }

        if(ray_vec.y < 0) {
            step_y = -1;
            side_dist_y = (camera->pos.y - map_y) * delta_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - camera->pos.y) * delta_y;
        }

        bool hit = false;
        enum ray_hit_side side;

        while(!hit)
        {
            if(side_dist_x < side_dist_y) {
                side_dist_x += delta_x;
                map_x += step_x;
                side = VERTICAL_SIDE;
            } else {
                side_dist_y += delta_y;
                map_y += step_y;
                side = HORIZONTAL_SIDE;
            }

            if(map->data[map_y * map->width + map_x] > 0)
                hit = true;
        }

        float ray_length;
        switch (side) {
        case VERTICAL_SIDE:
            ray_length = side_dist_x - delta_x;
            break;
        case HORIZONTAL_SIDE:
            ray_length = side_dist_y - delta_y;
            break;
        default:
            ray_length = 0;
            break;
        }

        struct ray *ray = &raycaster->rays[x];
        ray->begin = camera->pos;
        ray->dir = ray_vec;
        ray->length = ray_length;
        ray->hit_entry = map->data[map_y * map->width + map_x];
        ray->hit_side = side;
    }
}
