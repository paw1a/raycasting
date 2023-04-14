#include "sprite.h"

static struct sprite sprites[SPRITES_COUNT];

void create_sprites(void) {
    sprites[0] = (struct sprite){20.5f, 11.5f, assets_get_texture(GREEN_LIGHT)};
    sprites[1] = (struct sprite){18.5f, 4.5f, assets_get_texture(GREEN_LIGHT)};
    sprites[2] = (struct sprite){10.0f, 4.5f, assets_get_texture(GREEN_LIGHT)};
    sprites[3] = (struct sprite){10.0f, 12.5f, assets_get_texture(GREEN_LIGHT)};
    sprites[4] = (struct sprite){3.5f, 6.5f, assets_get_texture(GREEN_LIGHT)};
    sprites[5] = (struct sprite){3.5f, 20.5f, assets_get_texture(GREEN_LIGHT)};
    sprites[6] = (struct sprite){3.5f, 14.5f, assets_get_texture(GREEN_LIGHT)};
    sprites[7] = (struct sprite){14.5f, 20.5f, assets_get_texture(GREEN_LIGHT)};

    sprites[8] = (struct sprite){18.5f, 10.5f, assets_get_texture(PILLAR)};
    sprites[9] = (struct sprite){18.5f, 11.5f, assets_get_texture(PILLAR)};
    sprites[10] = (struct sprite){18.5f, 12.5f, assets_get_texture(PILLAR)};

    sprites[11] = (struct sprite){21.5f, 1.5f, assets_get_texture(BARREL)};
    sprites[12] = (struct sprite){15.5f, 1.5f, assets_get_texture(BARREL)};
    sprites[13] = (struct sprite){16.0f, 1.8f, assets_get_texture(BARREL)};
    sprites[14] = (struct sprite){16.2f, 1.2f, assets_get_texture(BARREL)};
    sprites[15] = (struct sprite){3.5f, 2.5f, assets_get_texture(BARREL)};
    sprites[16] = (struct sprite){9.5f, 15.5f, assets_get_texture(BARREL)};
    sprites[17] = (struct sprite){10.0f, 15.1f, assets_get_texture(BARREL)};
    sprites[18] = (struct sprite){10.5f, 15.8f, assets_get_texture(BARREL)};
}

void sort_sprites_by_distance(struct vec2 point) {
    for (size_t i = 0; i < SPRITES_COUNT - 1; i++) {
        for (size_t j = 0; j < SPRITES_COUNT - i - 1; j++) {
            float dist1 = vec2_len(vec2_sub(point, sprites[j].pos));
            float dist2 = vec2_len(vec2_sub(point, sprites[j + 1].pos));
            if (dist1 < dist2) {
                struct sprite temp = sprites[j];
                sprites[j] = sprites[j + 1];
                sprites[j + 1] = temp;
            }
        }
    }
}

struct sprite get_sprite(int index) {
    return sprites[index];
}
