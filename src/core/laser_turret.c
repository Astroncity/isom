#include "laser_turret.h"
#include "flecs.h"
#include "state.h"
#include "tower.h"
#define ARENA_MAX 20
#define PRICE 20

static Texture2D base;
static Texture2D head;

typedef struct LaserTurret {
    Tower t;
    v2 pos;
} LaserTurret;

static LaserTurret arena[ARENA_MAX];
static usize count = 0;

void renderTurrets(ecs_iter_t* _) {
    (void)_;
    for (usize i = 0; i < count; i++) {
        DrawTextureV(base, arena[i].pos, WHITE);
        DrawTextureV(head, arena[i].pos, WHITE);
    }
}

static void init(void) {
    base = LoadTexture("assets/images/laser_turret_base.png");
    head = LoadTexture("assets/images/laser_turret_head.png");
    ECS_SYSTEM(state.world, renderTurrets, OnCamera);
}

void sell(usize id) {
    (void)id;
    state.money += PRICE;
    arena[id] = arena[count - 1];
    arena[id].t.id = id;
    count--;
}

void spawnLaserTurret(v2 pos) {
    if (!IsTextureValid(head)) {
        init();
    }

    arena[count] = (LaserTurret){{(Rect){}, count, sell, 20}, pos};
    towers[global_tower_count] = &arena[count].t;
    global_tower_count++;
    count++;
}
