s32 func_15132BBC(void *, s32, s32, s32, s32, s32, s32);
extern u8 D_800A5860[];
s32 memcpy(s32, s32 *, s32);
// record_particle_spawn: spawns particle type 0x2F (func_15132BBC) lasting `life` at the record's point rec[0..2]
// with the angles rec[3..5], scale 1 / 0.02 and the colour of D_800A5860; the 0x14 extra bytes at +0x170 keep
// the record pointer, its point and 0.0.
void func_150F85AC(f32 *rec, s16 life, u8 flag, s32 arg3) {
    struct {
        /* spawn block for func_15132BBC (0x7C bytes) */
        f32 scale[4];
        f32 angle[3];
        f32 one[3];
        f32 pos[3];
        f32 vel[3];
        s32 color[3];
        f32 u4C;
        s32 flags50;
        s16 life;
        s16 type;
        u8 u58;
        u8 pad59[3];
        s32 u5C;
        u8 u60;
        u8 u61;
        u8 u62[7];
        u8 u69;
        u8 u6A;
        u8 pad6B;
        s32 u6C;
        u8 u70;
        u8 pad71;
        s16 u72;
        s16 u74;
        u8 pad76[2];
        s32 u78;
        /* extra data copied to particle +0x170 (0x14 bytes) */
        f32 *rec;
        f32 recPos[3];
        f32 u10;
    } sp;
    s32 i;
    s32 p;

    sp.rec = rec;
    sp.recPos[0] = rec[0];
    sp.recPos[1] = rec[1];
    sp.recPos[2] = rec[2];
    sp.u10 = 0.0f;
    sp.scale[0] = 1.0f;
    sp.scale[1] = 1.0f;
    sp.scale[2] = 0.020000001f; /* 0x3CA3D70B */
    sp.scale[3] = 0.020000001f; /* 0x3CA3D70B */
    sp.angle[0] = rec[3];
    sp.angle[1] = rec[4];
    sp.angle[2] = rec[5];
    sp.one[0] = 1.0f;
    sp.one[1] = 1.0f;
    sp.one[2] = 1.0f;
    sp.pos[0] = rec[0];
    sp.pos[1] = rec[1];
    sp.pos[2] = rec[2];
    sp.vel[0] = 0.0f;
    sp.vel[1] = 0.0f;
    sp.vel[2] = 0.0f;
    sp.color[0] = ((s32 *)D_800A5860)[0];
    sp.color[1] = ((s32 *)D_800A5860)[1];
    sp.color[2] = ((s32 *)D_800A5860)[2];
    sp.u4C = 0.0f;
    sp.flags50 = 0x980;
    sp.life = life;
    sp.type = 0x2F;
    sp.u58 = 0;
    sp.u5C = 0;
    sp.u60 = 0xFF;
    sp.u61 = 0x14;
    for (i = 0; i < 7; i++) {
        sp.u62[i] = 0;
    }
    sp.u6A = 0;
    sp.u6C = 0;
    sp.u70 = 0;
    sp.u72 = 1;
    sp.u74 = 0xFF;
    sp.u78 = 0;
    p = func_15132BBC(&sp, 3, 0xFF, 0, 0xB4, flag, arg3);
    if (p != 0) {
        memcpy(p + 0x170, (s32 *)&sp.rec, 0x14);
    }
}
