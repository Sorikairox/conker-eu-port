/* P124: the 0x3C-byte effect template func_15169ED8 copies into a new effect record (+0x10); same layout as S59A0
 * in game_eu_1231B0.c. m2c had split it into 20 separate stack locals, which clang lays out on its own. */
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
} EffectTemplate1386C0;
u8 *func_15169ED8(void *);
extern s32 D_80091B9C;

// effect_spawn_sum_counter: spawns a type-0xA effect (template D_80091B9C at 228, 252.59) whose words 8 / 0xC
// pack the three arguments (a0 << 16 | a1, a2 << 16 | sum) and whose +0x14 is the sum a0 + a1 + a2.
void func_1510AEB0(s32 arg0, s32 arg1, s32 arg2) {
    EffectTemplate1386C0 t;
    s32 sum;

    sum = arg0 + arg1 + arg2;
    t.u0 = &D_80091B9C;
    t.u30 = 0xA;
    t.u2C = 0x40;
    t.u2E = 0x20;
    t.u28 = 0x18FC;
    t.u2A = 0x1A12;
    t.u36 = 7;
    t.u39 = 0;
    t.u8 = (arg0 << 16) | arg1;
    t.uC = (arg2 << 16) | sum;
    t.u10 = 10000;
    t.u14 = sum;
    t.u18 = 0;
    t.u24 = 0;
    t.u26 = 0;
    t.u31 = 1;
    t.u32 = 0xFF;
    t.u33 = 0xFF;
    t.u34 = 0xFF;
    t.u37 = 0x11;
    t.u35 = 0;
    t.u16 = 0;
    t.u1C = 228.0f;
    t.u20 = 252.59259f;
    func_15169ED8(&t);
}
