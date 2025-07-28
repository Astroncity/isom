#pragma once
#include "defs.h"
#include "flecs.h"
#include "transform.h"

extern ECS_COMPONENT_DECLARE(Renderable);
extern ECS_COMPONENT_DECLARE(RenderableStatic);
extern ECS_SYSTEM_DECLARE(render_s);
extern ECS_SYSTEM_DECLARE(renderStaticSystem);
extern ecs_entity_t OnCamera;
extern ecs_entity_t PostCamera;

typedef struct {
    u32 renderLayer;
    void (*render)(ecs_entity_t, const Position*);
} Renderable, RenderableStatic;

void RendererImport(ecs_world_t* world);
