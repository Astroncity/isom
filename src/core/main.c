#include "flecs.h"
#include "render.h"
#include "state.h"
#include "transform.h"
#include "window.h"
#include <raylib.h>
#include <stdio.h>

Color dark, light;

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
            Color c = (i + j) % 2 == 0 ? dark : light;
            DrawRectangle(i * 32, j * 32, 32, 32, c);
        }
    }
}

int main(void) {
    init_engine("Engine Template");
    dark = hex_to_cl(0x819796);
    light = hex_to_cl(0x202E37);

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
