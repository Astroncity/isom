#include "state.h"

State state = {0};
static bool is_init = false;

void init_engine(const char* window_title) {
    is_init = true;

    state.world = ecs_init();
    state.screenWidth = 640;
    state.screenHeight = 360;
    state.mouse = malloc(sizeof(v2));
    state.screen = init_window(window_title);
    state.font = LoadFontEx("assets/fonts/munro.ttf", 24, NULL, 0);
    SetTextureFilter(state.font.texture, TEXTURE_FILTER_POINT);

    state.camera = (Camera2D){};
    state.camera.zoom = 1;

    ECS_IMPORT(state.world, Transform);
    ECS_IMPORT(state.world, Renderer);
}
