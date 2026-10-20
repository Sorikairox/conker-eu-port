s32 memcpy(void *, void *, s32);
void *func_15167A68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5);

typedef struct { f32 x, y, z; s32 pad[3]; } E18;
typedef struct {
    u8 pad0[0x10];
    u8 pad10[2];
    s16 s12;
    u8 pad14[0x4C];
    E18 *end;
    E18 *tbl;
    f32 f68;
    u8 b6C[0x10];
    s32 u7C;
} O7F00;

u8 *func_151A7F00(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    O7F00 *v;

    v = func_15167A68(0x2D, arg3, *(s16 *)(arg0 + 2) * 0x18U + arg1 + 0x80, 1, arg2, 1);
    if (v == NULL) {
        return NULL;
    }
    memcpy((u8 *)v + 0x10, arg0, 0x50);
    v->tbl = (E18 *)((u8 *)v + 0x80);
    v->end = &v->tbl[*(s16 *)(arg0 + 2)];
    v->f68 = 0.0f;
    v->tbl->x = 0.0f;
    v->tbl->y = 0.0f;
    v->tbl->z = 0.0f;
    (v->tbl + *(s16 *)(arg0 + 2))[-1].x = 0.0f;
    (v->tbl + *(s16 *)(arg0 + 2))[-1].y = 0.0f;
    (v->tbl + *(s16 *)(arg0 + 2))[-1].z = 1.0f;
    bzero(v->b6C, 0x10);
    v->u7C = (v->s12 << 6) + 0x140;
    return (u8 *)v;
}
