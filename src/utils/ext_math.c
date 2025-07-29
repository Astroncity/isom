#include "ext_math.h"

i32 round_to_nearest(i32 val, i32 multiple) {
    if (multiple == 0) return val;

    return ((val + multiple / 2) / multiple) * multiple;
}

i32 round_up_to_nearest(i32 val, i32 n) {
    if (n == 0) return val;

    return ((val + n - 1) / n) * n;
}
i32 round_down_to_nearest(i32 val, i32 n) {
    if (n == 0) return val;

    return (val / n) * n;
}
