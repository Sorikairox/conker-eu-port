typedef struct { f32 x; f32 y; f32 z; f32 pad[3]; } Ent_151B5128;
typedef struct { u8 pad0[0x10]; u8 flags; u8 pad11[3]; f32 x14; f32 x18; f32 x1C; f32 x20; u8 pad24[0x24]; Ent_151B5128 e[10]; } Obj_151B5128;
extern f32 D_800AA7A4;
s32 func_151B4E8C(Obj_151B5128 *arg0) {
    s32 i;
    f32 f;
    f32 d;

    f = arg0->x14;
    d = -(f - arg0->x20) * D_800AA7A4;
    for (i = 0; i < 10; i++) {
        arg0->e[i].x = f;
        arg0->e[i].y = 0.0f;
        arg0->e[i].z = 0.0f;
        f += d;
    }
    arg0->flags &= ~2;
    return 1;
}
