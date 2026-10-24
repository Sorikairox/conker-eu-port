typedef struct {
    s32 count;  // 0x00 points
    s32 u4;     // 0x04
    s32 u8;     // 0x08
    f32 *pts;   // 0x0C (set after the copy)
    f32 params[12]; // 0x10
    u8 kind;    // 0x40
} BoltSpec;     // copied to rec + 0x28
void func_15107678(u8 *rec, s16 lo, s16 hi, f32 jitter);
void *memcpy(void *, const void *, unsigned int);

// bolt_spawn: spawns a bolt record (func_15149130 type 0x3E, 0x48-byte header + (2^depth + 1) points) whose block at
// +0x28 gets the point count, the 12 `params` words and `kind`; the point list (+0x28 + 0x48) runs from `start` to
// `end` and func_15107678 fills the inner points with midpoint displacement (`jitter`). Returns the record or 0.
s32 func_15107518(f32 *start, f32 *end, s32 depth, f32 *params, f32 jitter, u8 kind, u8 arg6, s32 arg7) {
    BoltSpec spec;
    u8 *rec;
    f32 *pts;
    s32 i;

    spec.count = (1 << depth) + 1;
    spec.u8 = 0;
    spec.u4 = 0;
    for (i = 0; i < 12; i++) {
        spec.params[i] = params[i];
    }
    spec.kind = kind;
    // arg 6 is the record size (functions.h types it struct37 *)
    rec = (u8 *) func_15149130(0, -1, 0x3E, -1, 0, 0x30, (struct37 *) (spec.count * 12 + 0x48), arg6, arg7);
    if (rec != NULL) {
        memcpy(rec + 0x28, &spec, sizeof(BoltSpec));
        pts = (f32 *) (rec + 0x28 + 0x48);
        *(f32 **) (rec + 0x28 + 0xC) = pts;
        pts[0] = start[0];
        pts[1] = start[1];
        pts[2] = start[2];
        pts = *(f32 **) (rec + 0x28 + 0xC) + (spec.count - 1) * 3;
        pts[0] = end[0];
        pts[1] = end[1];
        pts[2] = end[2];
        func_15107678(rec, 0, spec.count - 1, jitter);
    }
    return (s32) rec;
}
