#pragma once
#include "defs.h"
#include "flecs.h"

extern ECS_COMPONENT_DECLARE(Tower);

typedef struct Tower {
    Rect collider;
    i32 price;
} Tower;

void TowerModImport(ecs_world_t* world);
void sell(ecs_entity_t e);
