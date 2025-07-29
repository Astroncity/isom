#include "ext_math.h"
#include "laser_turret.h"
#include "render.h"
#include "state.h"
#include "tower.h"
#include "track.h"
#include "transform.h"

Color dark, light;
Texture2D grass, wallF, wallR, wallL;

Color hex_to_cl(u32 hex) {
    return (Color){hex >> 16 & 0xFF, hex >> 8 & 0xFF, hex & 0xFF, 255};
}

void draw_tilemap(void) {
    u32 xTiles = 50;
    u32 yTiles = 20;

    u32 i, j = 0;

    for (i = 0; i < xTiles; i++) {
        for (j = 0; j < yTiles; j++) {
            if ((i * 32) > state.screenWidth || (j * 32) > state.screenHeight) {
                break;
            }
            i32 x = i * 32;
            i32 y = j * 32;
            Color c = WHITE;
            Rect r = {x, y, 32, 32};

            if (CheckCollisionPointRec(*state.mouse, r)) {
                c = (Color){200, 200, 200, 255};
            }
            DrawTexture(grass, x, y, c);
        }
    }
}

int main(void) {
    init_engine("Engine Template");
    ECS_IMPORT(state.world, TowerMod);
    dark = hex_to_cl(0x819796);
    light = hex_to_cl(0x202E37);
    grass = LoadTexture("assets/images/grass1.png");
    wallF = LoadTexture("assets/images/wall_front.png");
    wallR = LoadTexture("assets/images/wall_side_right.png");
    wallL = LoadTexture("assets/images/wall_side_left.png");

    Track test = defaultTrack();

    while (!WindowShouldClose()) {
        update_mouse();

        BeginTextureMode(*state.screen);
        ClearBackground(BLACK);

        if (IsMouseButtonPressed(0)) {
            v2 pos = {round_down_to_nearest(state.mouse->x, 32),
                      round_down_to_nearest(state.mouse->y, 32)};
            spawnLaserTurret(pos);
        }

        draw_tilemap();
        renderTrack(&test);
        ecs_progress(state.world, GetFrameTime());

        EndTextureMode();
        draw_window();
    }

    CloseWindow();
    return 0;
}
