#include "tower.h"

ECS_COMPONENT_DECLARE(Tower);

void TowerModImport(ecs_world_t* world) {
    ECS_MODULE(world, TowerMod);
    ECS_COMPONENT_DEFINE(world, Tower);
}
