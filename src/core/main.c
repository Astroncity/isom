#include "flecs.h"
#include "player.h"
#include "render.h"
#include "state.h"
#include "transform.h"
#include "window.h"
#include <raylib.h>
#include <stdio.h>

Color dark, light;
Texture2D grass;

Color hex_to_cl(u32 hex) {
    return (Color){hex >> 16 & 0xFF, hex >> 8 & 0xFF, hex & 0xFF, 255};
}

i32 round_to_nearest(i32 value, i32 multiple) {
    if (multiple == 0) return value;

    return ((value + multiple / 2) / multiple) * multiple;
}

void draw_tilemap(void) {
    u32 xTiles = 50;
    u32 yTiles = 20;

    u32 i, j = 0;
    bool tile_selected = false;
    v2 plr_pos = playerPos();
    plr_pos.x = round_to_nearest(plr_pos.x, 32);
    plr_pos.y = round_to_nearest(plr_pos.y, 32);
    Rect plr = {plr_pos.x, plr_pos.y, 17, 30};

    for (i = 0; i < xTiles; i++) {
        for (j = 0; j < yTiles; j++) {
            if ((i * 32) > state.screenWidth || (j * 32) > state.screenHeight) {
                break;
            }
            i32 x = i * 32;
            i32 y = j * 32;
            Color c = WHITE;
            Rect r = {x, y, 32, 32};

            if (!tile_selected && CheckCollisionRecs(r, plr)) {
                c = (Color){200, 200, 200, 255};
                tile_selected = true;
            }
            DrawTexture(grass, x, y, c);
        }
    }
}

int main(void) {
    init_engine("Engine Template");
    dark = hex_to_cl(0x819796);
    light = hex_to_cl(0x202E37);
    createPlayer();
    grass = LoadTexture("assets/images/grass1.png");

    while (!WindowShouldClose()) {
        update_mouse();

        BeginTextureMode(*state.screen);
        ClearBackground(BLACK);

        draw_tilemap();
        ecs_progress(state.world, GetFrameTime());

        EndTextureMode();
        draw_window();
    }

    CloseWindow();
    return 0;
}
