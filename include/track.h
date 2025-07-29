#pragma once
#include "defs.h"

typedef struct Track {
    v2 points[10];
    const usize len;
} Track;

Track defaultTrack(void);
void renderTrack(Track* t);
