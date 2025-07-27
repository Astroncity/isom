#pragma once
#include "defs.h"
#include "flecs.h"
#include "render.h"
#include "transform.h"
#include "window.h"

typedef struct State {
    ecs_world_t* world;
    Font font;
    u32 screenWidth;
    u32 screenHeight;
    v2* mouse;
    RenderTexture2D* screen;
	Camera2D camera;
} State;

extern State state;

void init_engine(const char* window_title);
