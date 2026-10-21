
typedef struct {
    f32 pos[3];
    u8 pad0C[0x10];
    f32 len;
    u8 pad20[8];
} TrailNode;

typedef struct {
    u8 *ent;
    u8 pad4[0x148];
    f32 step;
} TrailOwner;

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[9];
    u8 count;
    u8 pad26[6];
    s8 u2C;
    s8 end;
    s8 start;
    u8 pad2F[0x65];
    TrailNode *nodes;
    TrailOwner *owner;
} TrailObj;

void func_1519D320(s32 arg0_, f32 arg1, s32 arg2) {
    TrailObj *arg0 = (TrailObj *)arg0_;
    TrailOwner *owner = arg0->owner;
    TrailNode *nodes = arg0->nodes;
    f32 *prev = arg0->pos;
    TrailNode *n;
    f32 step;
    f32 dist;
    f32 next;
    f32 len;
    f32 t;
    s32 i;
    u8 *e;

    if (arg0->u2C >= 2) {
        dist = 0.0f;
        step = owner->step * arg1;
        i = arg0->start;
        next = 0.0f;
        do {
            i--;
            if (i < 0) {
                i = arg0->count - 1;
            }
            n = &nodes[i];
            len = n->len;
            dist += len;
            if (next <= dist) {
                e = owner->ent;
                t = (dist - next) / len;
                func_1505D1C4((prev[0] - n->pos[0]) * t + n->pos[0],
                              (prev[1] - n->pos[1]) * t + n->pos[1],
                              (prev[2] - n->pos[2]) * t + n->pos[2],
                              arg2, (e - (u8 *)D_800CC2D0) / 0x32C, *(u16 *)(e + 0x76), 0, 0);
                next += step;
            }
            prev = n->pos;
        } while (i != arg0->end);
    }
}
