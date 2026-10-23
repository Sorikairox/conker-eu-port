/* P124 */
typedef struct {
    void *u0;
    s32 u4;
    s32 u8;
    s32 uC;
    s32 u10;
    s16 u14;
    s16 u16;
    s16 u18;
    s16 pad1A;
    f32 u1C;
    f32 u20;
    s16 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s16 u2E;
    u8 u30; /* effect type: index into D_8008CDC0 (record +0x40) */
    u8 u31;
    u8 u32;
    u8 u33;
    u8 u34;
    u8 u35;
    u8 u36;
    u8 u37;
    u8 u38;
    u8 u39;
    u8 pad3A[2];
} EffectTemplateE48B0;
u8 *func_15169E70(void *, s32);
extern s32 D_80091CD4;
extern s32 D_800BEA58;

// effect_spawn_cross: spawns four type-7 effects (template D_80091CD4, priority arg3) around (arg0, arg1): above and
// below (arg1 -/+ d, flag byte 0 / 8) and left and right (arg0 -/+ d, flag 4 / 0, u16 0x100), where d is the
// distance of arg0 to the nearer screen edge (D_800BEA58 = screen width). arg2 goes to words 0xC and +0x14.
void func_150B7700(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    EffectTemplateE48B0 t;
    s32 d;
    s32 v;

    t.u2A = 0x1000;
    t.u0 = &D_80091CD4;
    t.u8 = (arg0 << 16) | (arg1 & 0xFFFF);
    t.u28 = 0x1000;
    t.uC = arg2;
    t.u14 = arg2;
    t.u18 = 0;
    t.u24 = 0;
    t.u26 = 0;
    t.u2C = 0x10;
    t.u2E = 0x10;
    t.u30 = 7;
    t.u31 = 2;
    t.u32 = 0xFF;
    t.u33 = 0;
    t.u34 = 0;
    t.u35 = 0xFF;
    t.u36 = 7;
    t.u37 = 0x11;
    if (arg0 < (D_800BEA58 >> 1)) {
        d = D_800BEA58 - arg0;
    } else {
        d = arg0;
    }
    v = arg1 - d;
    t.u10 = (arg0 << 16) | (v & 0xFFFF);
    t.u39 = 0;
    t.u16 = 0;
    t.u1C = arg0;
    t.u20 = v;
    func_15169E70(&t, arg3);
    v = arg1 + d;
    t.u10 = (arg0 << 16) | (v & 0xFFFF);
    t.u39 = 8;
    t.u20 = v;
    func_15169E70(&t, arg3);
    v = arg0 - d;
    t.u1C = v;
    t.u10 = (v << 16) | (arg1 & 0xFFFF);
    t.u39 = 4;
    t.u16 = 0x100;
    t.u20 = arg1;
    func_15169E70(&t, arg3);
    v = arg0 + d;
    t.u10 = (v << 16) | (arg1 & 0xFFFF);
    t.u39 = 0;
    t.u1C = v;
    func_15169E70(&t, arg3);
}
