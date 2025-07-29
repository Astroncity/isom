#include "track.h"

#define TRACK_P(x, y)                                                               \
    (v2) { round_to_nearest(x, 16), round_to_nearest(y, 16) }

static i32 round_to_nearest(i32 value, i32 multiple) {
    if (multiple == 0) return value;

    return ((value + multiple / 2) / multiple) * multiple;
}

Track defaultTrack(void) {
    Track t = (Track){{}, 6};
    t.points[0] = TRACK_P(0, 300);
    t.points[1] = TRACK_P(200, 300);
    t.points[2] = TRACK_P(200, 100);
    t.points[3] = TRACK_P(400, 100);
    t.points[4] = TRACK_P(400, 200);
    t.points[5] = TRACK_P(640, 200);

    return t;
}

void renderTrack(Track* t) {
    const u16 thick = 32;
    for (usize i = 0; i < t->len - 1; i++) {
        v2 start = t->points[i];
        v2 end = t->points[i + 1];
        if (end.x == start.x) {
            end.y += (end.y > start.y) ? thick / 2 : -thick / 2;

        } else {
            end.x += thick / 2;
        }
        DrawLineEx(start, end, thick, GRAY);
    }
}
