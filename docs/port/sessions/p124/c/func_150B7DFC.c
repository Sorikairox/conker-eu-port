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
u8 *func_15169ED8(void *);
extern s32 D_80091CBC;
extern s32 D_80091C98;

// hud_bars_create: (re)creates the effect records D_800D9CB8[5..7] (three type-5 bars from template D_80091CBC at
// y 150 / 170 / 190, alpha 0x80 / 0xFF / 0x80) and [9] (a type-0 effect from D_80091C98 at 230, 170); frees [2]
// first. Returns the last record; sets D_800D9CB0 = 3. The free before [6] / [7] passes D_800D9CB8[5] (as the asm:
// the original source frees the wrong slot there).
s32 func_150B7DFC(void) {
    EffectTemplateE48B0 t;

    if (D_800D9CB8[2] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[2]);
        D_800D9CB8[2] = 0;
    }
    t.u31 = 3;
    t.u2C = 0x40;
    t.u2E = 0x10;
    t.u30 = 5;
    t.u24 = 0;
    t.u26 = 0;
    t.u14 = 0;
    t.u16 = 0;
    t.u18 = 0;
    t.u0 = &D_80091CBC;
    t.u4 = 0;
    t.u8 = 0;
    t.u10 = 0;
    t.u32 = 0xFF;
    t.u33 = 0;
    t.u34 = 0;
    t.u35 = 0x80;
    t.u36 = 7;
    t.u37 = 0x11;
    t.u38 = 1;
    t.u39 = 0;
    t.u28 = 0x1000;
    t.u2A = 0x1000;
    t.u20 = 150.0f;
    t.u1C = 230.0f;
    t.uC = (s32) t.u20;
    if (D_800D9CB8[5] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[5]);
    }
    D_800D9CB8[5] = (s32) func_15169ED8(&t);
    t.u16 = 0x100;
    t.u8 = 0x100;
    t.u35 = 0xFF;
    t.u20 = 170.0f;
    t.uC = (s32) t.u20;
    if (D_800D9CB8[6] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[5]);
    }
    D_800D9CB8[6] = (s32) func_15169ED8(&t);
    t.u16 = 0x200;
    t.u8 = 0x200;
    t.u35 = 0x80;
    t.u20 = 190.0f;
    t.uC = (s32) t.u20;
    if (D_800D9CB8[7] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[5]);
    }
    D_800D9CB8[7] = (s32) func_15169ED8(&t);
    t.u14 = 0;
    t.u16 = 0;
    t.u18 = 0;
    t.u31 = 0;
    t.u2C = 0x58;
    t.u2E = 0x40;
    t.u35 = 0xFF;
    t.u30 = 0;
    t.u0 = &D_80091C98;
    t.u1C = 230.0f;
    t.u20 = 170.0f;
    if (D_800D9CB8[9] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[9]);
    }
    D_800D9CB8[9] = (s32) func_15169ED8(&t);
    D_800D9CB0 = 3;
    return D_800D9CB8[9];
}
