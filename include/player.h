#pragma once
#include "defs.h"
#include "flecs.h"
#include "raylib.h"

ecs_entity_t createPlayer(void);
v2 playerPos(void);
Rect playerRect(void);
