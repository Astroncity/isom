#pragma once
#include "defs.h"
#define MAX_TOWERS 100

typedef struct Tower {
    Rect collider;
    usize id;
    void (*sell)(usize);
    i32 price;
} Tower;

extern Tower* towers[MAX_TOWERS];
extern usize global_tower_count;
