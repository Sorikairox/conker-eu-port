// anim_event_effect_spawn: animation event 0x32 (func_150268BC): when all five pointers are set and span != 0, spawns
// a type 0x17 effect record (func_1513D524 with flags 0x401, 0x243A, colour 0xC8 x4, lifetime span, group arg6 and
// arg7) and links it to its sources: +0x110 = a0, +0x114 = a1, +0x118 = a2, +0x11C = a4, +0x120 = a3 (P195).
typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ s16 flags;
    /* 0x04 */ s16 span;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ s32 w8;
    /* 0x0C */ s32 wC;
    /* 0x10 */ u8 rgba[4];
    /* 0x14 */ u8 pad14[0x40 - 0x14];
    /* 0x40 */ s32 w40;
    /* 0x44 */ u8 b44;
    /* 0x45 */ u8 b45;
    /* 0x46 */ u8 pad46[2];
} EffSpawn150DBA98;

void func_150DBA98(u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *a4, s16 span, u8 arg6, s32 arg7) {
    EffSpawn150DBA98 spec;
    u8 *rec;

    if (a0 == NULL || a1 == NULL || a2 == NULL || a3 == NULL || a4 == NULL || span == 0) {
        return;
    }
    spec.type = 0x17;
    spec.wC = 0x243A;
    spec.w40 = 0x401;
    spec.b44 = 0xFF;
    spec.w8 = 0;
    spec.span = span;
    spec.b45 = 0xFF;
    spec.rgba[0] = 0xC8;
    spec.rgba[1] = 0xC8;
    spec.rgba[2] = 0xC8;
    spec.rgba[3] = 0xC8;
    spec.flags = 0x401;
    rec = (u8 *) func_1513D524((s32) &spec, 0, 0xA, 0, 8, 0, 0x14, arg6, arg7);
    if (rec != NULL) {
        *(u8 **) (rec + 0x110) = a0;
        *(u8 **) (rec + 0x114) = a1;
        *(u8 **) (rec + 0x118) = a2;
        *(u8 **) (rec + 0x11C) = a4;
        *(u8 **) (rec + 0x120) = a3;
    }
}
