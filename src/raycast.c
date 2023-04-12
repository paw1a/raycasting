#include "raycast.h"
#include "common.h"
#include "world.h"

#include <math.h>

static struct ray *ray_array;

int create_raycast(void) {
    ray_array = malloc(SCREEN_WIDTH * sizeof(struct ray));
    if (ray_array == NULL)
        return -1;

    return 0;
}

struct ray *compute_rays(struct world *world) {
    for (size_t x = 0; x < SCREEN_WIDTH; x++) {
        float plane_size = 2.0f * x / SCREEN_WIDTH - 1;
        struct vec2 ray_vec = vec2_sum(world->cam_dir, vec2_mul(world->cam_plane, plane_size));

        int map_x = (int)world->cam_pos.x;
        int map_y = (int)world->cam_pos.y;

        float delta_x = fabsf(1 / ray_vec.x);
        float delta_y = fabsf(1 / ray_vec.y);

        float side_dist_x;
        float side_dist_y;
        int step_x;
        int step_y;

        if (ray_vec.x < 0) {
            step_x = -1;
            side_dist_x = (world->cam_pos.x - map_x) * delta_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0f - world->cam_pos.x) * delta_x;
        }

        if (ray_vec.y < 0) {
            step_y = -1;
            side_dist_y = (world->cam_pos.y - map_y) * delta_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - world->cam_pos.y) * delta_y;
        }

        bool hit = false;
        enum ray_hit_side side;
        struct ray *ray = &ray_array[x];

        while (!hit) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_x;
                map_x += step_x;
                side = VERTICAL_SIDE;
            } else {
                side_dist_y += delta_y;
                map_y += step_y;
                side = HORIZONTAL_SIDE;
            }

            uint32_t entry = world->map->data[map_y * world->map->width + map_x];
            if (entry > 0) {
                hit = true;
                ray->hit_entry = entry;
            }
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

        ray->begin = world->cam_pos;
        ray->dir = ray_vec;
        ray->length = ray_length;
        ray->hit_side = side;
    }

    return ray_array;
}

void destroy_raycast(void) {
    free(ray_array);
}
