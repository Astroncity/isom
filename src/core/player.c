#include "player.h"
#include "flecs.h"
#include "render.h"
#include "state.h"
#include "transform.h"

static Texture2D sprite;
static ecs_entity_t player;
static bool isInit = false;

static void init(void) {
    sprite = LoadTexture("assets/images/player.png");
    //
}

static void render(ecs_entity_t _, const Position* pos) {
    DrawTexture(sprite, pos->x, pos->y, WHITE);
    (void)_;
}

v2 playerPos(void) {
    return *(v2*)ecs_get_id(state.world, player, ecs_id(Position));
    //
}

Rect playerRect(void) {
    v2 pos = playerPos();
    return (Rect){pos.x + 10, pos.y + 1, 17, 30};
}

ecs_entity_t createPlayer(void) {
    assert(!isInit && "Player created twice");
    init();
    player = ecs_new(state.world);
    ecs_set(state.world, player, Position, {0, 0});
    ecs_set(state.world, player, Velocity, {0, 0});
    ecs_set(state.world, player, Renderable, {0, render});
    ecs_add(state.world, player, controllable);
    return player;
}
