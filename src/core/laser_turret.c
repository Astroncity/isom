#include "laser_turret.h"
#include "flecs.h"
#include "render.h"
#include "state.h"
#include "tower.h"
#define ARENA_MAX 20
#define PRICE 20

static Texture2D base;
static Texture2D head;

static void render(ecs_entity_t _, const Position* p) {
    (void)_;
    DrawTextureV(base, *(v2*)p, WHITE);
    DrawTextureV(head, *(v2*)p, WHITE);
}

static void init(void) {
    base = LoadTexture("assets/images/laser_turret_base.png");
    head = LoadTexture("assets/images/laser_turret_head.png");
}

void spawnLaserTurret(v2 pos) {
    if (!IsTextureValid(head)) {
        init();
    }

    ecs_entity_t e = ecs_new(state.world);

    ecs_set(state.world, e, Tower, {{}, 20});
    ecs_set(state.world, e, Position, {pos.x, pos.y});
    ecs_set(state.world, e, Renderable, {0, render});
}
