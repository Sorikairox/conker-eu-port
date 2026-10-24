#ifdef NON_MATCHING
/* The 0x3C-byte spec func_15134DAC copies into a new type-0x29 effect (+0x18 there). */
typedef struct {
    /* 0x00 */ u8 u00;          /* the object's +0x3B byte */
    /* 0x04 */ u8 *obj;
    /* 0x08 */ u8 u08;          /* 0xC with the flag, else 1 */
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;         /* 20.0 */
    /* 0x20 */ f32 u20;
    /* 0x24 */ u8 u24;
    /* 0x26 */ s16 u26;
    /* 0x28 */ s16 u28;
    /* 0x2A */ s16 u2A;         /* 100 / 200 for hit kinds 8 / 9, else 500 */
    /* 0x2C */ s16 sound;       /* func_1000FA64 handle */
    /* 0x2E */ u8 u2E;
    /* 0x2F */ u8 u2F;          /* 5 when the kind's +0xE is 0, else 6 */
    /* 0x30 */ s8 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ u8 u38;
    /* 0x39 */ s8 u39;
} HitKindEffectSpec;

// object_hit_kind_effect_spawn: unless hit kind `kind`'s D_800A43B8 row has +0xE == 2 (debris only), starts sound
// 0x4FE at the object's position and spawns the type-0x29 hit effect (func_15134DAC) attached to the object; `flag`
// selects variant 0xC (else 1), kinds 8 / 9 get a shorter life (100 when the object's +0x94 has any of bits 1..3, else
// 200; other kinds 500). Returns what the asm leaves in v0: the new effect, or the kind's row when nothing is spawned
// (s32 as game_eu_1C1A20 declares it; every caller ignores it).
s32 func_15138120(struct127 *arg0, s32 kind, u8 flag) {
    HitKindEffectSpec spec;
    u8 *obj = (u8 *)arg0;
    u8 *info = D_800A43B8[kind];

    if (info[0xE] == 2) {
        return (s32)info;
    }
    spec.u00 = obj[0x3B];
    spec.obj = obj;
    spec.u08 = flag ? 0xC : 1;
    spec.u0C = 0.0f;
    spec.u10 = 0.0f;
    spec.u14 = 0.0f;
    spec.u18 = 0.0f;
    spec.u1C = 20.0f;
    spec.u20 = 0.0f;
    spec.u24 = 2;
    spec.u26 = 0x28;
    spec.u28 = 0x10;
    if (kind == 8 || kind == 9) {
        spec.u2A = (*(s32 *)(obj + 0x94) & 0xE) ? 100 : 200;
    } else {
        spec.u2A = 500;
    }
    spec.u2E = 5;
    spec.u2F = (info[0xE] == 0) ? 5 : 6;
    spec.u30 = -1;
    spec.u34 = 1.0f;
    spec.u38 = 0;
    spec.u39 = -1;
    spec.sound = func_1000FA64(0x4FE, (s16)(s32)(*(f32 *)(obj + 0x14)), (s16)(s32)(*(f32 *)(obj + 0x18)),
                               (s16)(s32)(*(f32 *)(obj + 0x1C)), 0x5DC0, 0x258, 0x12C, (s32)&func_1000EBC4,
                               (void *)100, 0, 0, 0);
    return (s32)func_15134DAC((u8 *)&spec, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15138120.s")
#endif
