typedef struct { f32 x, y, z; } V3_151B7DA4;
typedef struct { V3_151B7DA4 p; f32 d; u8 a; } Trail_151B7DA4;
typedef struct { u8 *obj; s32 x4; u8 idx; } Info_151B7DA4;
typedef struct {
    u8 pad0[0x10];
    V3_151B7DA4 pos;
    u8 pad1C[9];
    u8 n;
    u8 pad26[6];
    s8 cnt;
    s8 tail;
    s8 head;
    u8 pad2F[0x65];
    Trail_151B7DA4 *buf;
    Info_151B7DA4 *info;
} Obj_151B7DA4;
extern s32 (*D_8008FF30[])(Obj_151B7DA4 *);
f32 func_15143E64(V3_151B7DA4 *);
s32 func_151B7DA4(Obj_151B7DA4 *arg0) {
    Info_151B7DA4 *info = arg0->info;
    Trail_151B7DA4 *buf = arg0->buf;
    V3_151B7DA4 prev;
    V3_151B7DA4 d;
    Trail_151B7DA4 *e;
    f32 f;

    if (D_800BE9E4 > 0) {
        prev = arg0->pos;
        if (!D_8008FF30[info->idx](arg0)) {
            return 0;
        }
        if (info->obj != NULL) {
            *(V3_151B7DA4 *)(info->obj + 0x40) = arg0->pos;
        }
        d.x = arg0->pos.x - prev.x;
        d.y = arg0->pos.y - prev.y;
        d.z = arg0->pos.z - prev.z;
        f = func_15143E64(&d);
        e = &buf[arg0->head];
        e->p = arg0->pos;
        e->d = f;
        e->a = 0xFF;
        arg0->head++;
        if (arg0->n == arg0->head) {
            arg0->head = 0;
        }
        arg0->cnt++;
        if (arg0->tail == arg0->head) {
            arg0->tail++;
            if (arg0->n == arg0->tail) {
                arg0->tail = 0;
            }
            arg0->cnt--;
        }
    }
    return 1;
}
