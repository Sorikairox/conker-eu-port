#ifdef NON_MATCHING
/* func_1513D2F0's particle spec and func_151407D0's spawn block (0x58 bytes). */
typedef struct {
    /* 0x00 */ u8 texture;
    /* 0x01 */ u8 u01;
    /* 0x02 */ s16 texSet;
    /* 0x04 */ s16 life;
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ u8 color[4];
    /* 0x14 */ f32 halfW;
    /* 0x18 */ f32 halfH;
    /* 0x1C */ s32 angle[3];
    /* 0x28 */ s32 vel[3];
    /* 0x34 */ f32 scale[3];
    /* 0x40 */ s32 flags;
    /* 0x44 */ u8 u44;
    /* 0x45 */ u8 u45;
    /* 0x46 */ u8 u46;
    /* 0x47 */ u8 u47;
    /* 0x48 */ s32 u48;
    /* 0x4C */ u8 u4C;
    /* 0x4D */ u8 pad4D[0xB];
} PartSpecF9BB0;

/* func_151407D0's emitter block (filled up to 0x5A; the call passes size 0x78). */
typedef struct {
    /* 0x00 */ f32 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 u08;
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ s32 u24[8];
    /* 0x44 */ s32 u44;
    /* 0x48 */ f32 u48;
    /* 0x4C */ s16 u4C[4];
    /* 0x54 */ u8 u54[4];
    /* 0x58 */ u8 u58;
    /* 0x59 */ s8 u59;
    /* 0x5A */ u8 pad5A[2];
} EmitF9BB0;

/* 0x5C bytes copied to each particle's +0x110. */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 room;
    /* 0x05 */ u8 index;
    /* 0x08 */ f32 u08;
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 u38;
    /* 0x3C */ f32 u3C;
    /* 0x40 */ f32 scale[4];
    /* 0x50 */ u8 *group;
    /* 0x54 */ f32 midY;
    /* 0x58 */ u8 u58;
} PartExtraF9BB0;

/* 0x18 bytes copied to each emitter's +0x170. */
typedef struct {
    /* 0x00 */ s16 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ u8 *group;
    /* 0x0C */ u8 index;
    /* 0x10 */ u8 *obj;
    /* 0x14 */ u8 room;
} EmitExtraF9BB0;

/* 0x18 bytes copied to the group object's +0x28; the effects are recorded in it. */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 room;
    /* 0x08 */ u8 *part[2];
    /* 0x10 */ u8 *emit[2];
} GroupF9BB0;

struct260 *func_15149130(s16 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, struct37 *arg6, u8 arg7, s32 arg8);
void *func_1513D2F0(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB);
u8 *func_151407D0(void *emit, s32 emitSize, void *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8, s32 arg9);
s32 func_151D8E18(structEU_151D8E18 *arg0, s32 arg1, u8 arg2, s32 arg3);
s32 func_15160A58(u8 *, u8, void *, u8, s16, s32, s32, s32, s32, s32, s32, s8, s32, u8, u8, s32);
s32 func_150ADA20(void);
void *memcpy(void *, const void *, size_t);
extern s32 D_800A4AA0;
extern s32 D_800A2090;
extern f32 D_800A2130;
extern f32 D_800A2134;
extern f32 D_800A2138;
extern f32 D_800A213C;
extern f32 D_800A2140;
extern f32 D_800A2144;
extern f32 D_eu_800A2148;
extern f32 D_800A214C;
extern f32 D_800A2150;
extern f32 D_eu_800A2154;
extern f32 D_800A2158;
extern f32 D_800A215C;
extern f32 D_800A2160;

// object_aura_spawn: creates a group object (func_15149130 kind 0x46, 0x18-byte block {obj, obj+0x3B}) and, when it
// exists, two particles (func_1513D2F0 texture 0x5F, D_800A4AA0 list, random blend 1 / 3) and two emitters
// (func_151407D0 texture 0x60, 0x2A) around `obj`, each told its index, the object, its room byte and the group
// (particles at +0x110 also get the mid height (obj +0x14C + +0x150) / 2); the group records them at +0x30 / +0x38.
// Always then calls func_151D8E18 {1, 0x46, 8, 1, -1} and func_15160A58 (D_800A2090, 3, 0x46, 0x28).
// `alpha` / `owner` are passed to every spawner.
void func_150F9BB0(u8 *obj, u8 alpha, s32 owner) {
    structEU_151D8E18 shake;
    EmitExtraF9BB0 ee;
    PartSpecF9BB0 spawn;
    struct {
        EmitF9BB0 emit; /* func_151407D0 reads 0x78 bytes: on into spec */
        PartSpecF9BB0 spec;
        PartExtraF9BB0 extra; /* kept next to spec as in the asm frame */
    } fr;
    GroupF9BB0 init;
    u8 *group;
    GroupF9BB0 *g;

    init.obj = obj;
    init.room = obj[0x3B];
    init.part[0] = NULL;
    init.part[1] = NULL;
    init.emit[0] = NULL;
    init.emit[1] = NULL;
    group = (u8 *)func_15149130(0x46, -1, 0x4D, -1, 1, 0x33, (struct37 *)0x18, alpha, owner);
    if (group != NULL) {
        g = (GroupF9BB0 *)(group + 0x28);
        memcpy(g, &init, 0x18);

        fr.extra.u58 = 0;
        fr.extra.obj = obj;
        fr.extra.midY = (*(f32 *)(obj + 0x14C) + *(f32 *)(obj + 0x150)) * 0.5f;
        fr.extra.u08 = D_800A2130;
        fr.extra.u10 = D_800A2134;
        fr.extra.u18 = D_800A2138;
        fr.extra.u0C = D_800A213C;
        fr.extra.room = obj[0x3B];
        fr.extra.u24 = 0.0f;
        fr.extra.u28 = 0.0f;
        fr.extra.u38 = 0.0f;
        fr.spec.halfW = 0.0f;
        fr.spec.halfH = 0.0f;
        fr.extra.u3C = 0.0f;
        fr.extra.scale[2] = 1.0f;
        fr.extra.scale[0] = 1.0f;
        fr.extra.scale[3] = 1.0f;
        fr.extra.scale[1] = 1.0f;
        fr.spec.texture = 0x5F;
        fr.spec.u01 = 8;
        fr.spec.texSet = 0x2203;
        fr.spec.life = 300;
        fr.spec.u08 = 0;
        fr.spec.u0C = 0;
        fr.spec.color[0] = 0xFF;
        fr.spec.color[1] = 0xFF;
        fr.spec.color[2] = 0xFF;
        fr.spec.color[3] = 0xFF;
        fr.extra.u14 = D_800A2140;
        fr.extra.u20 = D_800A2144;
        fr.extra.u1C = D_eu_800A2148;
        fr.extra.u2C = 160.0f;
        fr.extra.u30 = 95.0f;
        fr.extra.u34 = D_800A214C;
        fr.extra.group = group;
        fr.spec.angle[0] = ((s32 *)D_800A5860)[0];
        fr.spec.angle[1] = ((s32 *)D_800A5860)[1];
        fr.spec.angle[2] = ((s32 *)D_800A5860)[2];
        fr.spec.vel[0] = ((s32 *)D_800A5860)[0];
        fr.spec.vel[1] = ((s32 *)D_800A5860)[1];
        fr.spec.vel[2] = ((s32 *)D_800A5860)[2];
        fr.spec.scale[0] = 1.0f;
        fr.spec.scale[1] = 1.0f;
        fr.spec.scale[2] = 1.0f;
        fr.spec.flags = 0x40EC0000;
        fr.spec.u44 = 0;
        fr.spec.u45 = 0xFF;
        fr.spec.u46 = 0;
        fr.spec.u47 = 7;
        fr.spec.u48 = 0;
        for (fr.extra.index = 0; fr.extra.index < 2; fr.extra.index++) {
            g->part[fr.extra.index] = func_1513D2F0(&fr.spec, (s32)&D_800A4AA0, 0, 0x25, 0, 0x1D,
                                              ((func_150ADA20() & 1) ? 2 : 0) + 1, 0, 0, 0x5C,
                                              alpha, owner);
            if (g->part[fr.extra.index] != NULL) {
                memcpy(g->part[fr.extra.index] + 0x110, &fr.extra, 0x5C);
            }
        }

        ee.u00 = 0;
        ee.u04 = 1.0f;
        ee.obj = obj;
        ee.group = group;
        ee.room = obj[0x3B];
        fr.emit.u24[0] = -1;
        fr.emit.u24[4] = -1;
        fr.emit.u24[1] = -1;
        fr.emit.u24[5] = -1;
        fr.emit.u24[2] = -1;
        fr.emit.u24[6] = -1;
        fr.emit.u24[3] = -1;
        fr.emit.u24[7] = -1;
        fr.emit.u59 = -1;
        fr.emit.u00 = D_800A2150;
        fr.emit.u04 = D_800A2150;
        fr.emit.u08 = D_eu_800A2154;
        fr.emit.u0C = D_eu_800A2154;
        fr.emit.u10 = D_800A2158;
        fr.emit.u14 = D_800A2158;
        fr.emit.u18 = 1.0f;
        fr.emit.u44 = 0;
        fr.emit.u48 = 1.0f;
        fr.emit.u4C[0] = 0;
        fr.emit.u4C[1] = 0;
        fr.emit.u4C[2] = 0;
        fr.emit.u4C[3] = 0;
        fr.emit.u54[0] = 0;
        fr.emit.u54[1] = 0;
        fr.emit.u54[2] = 0;
        fr.emit.u54[3] = 0;
        fr.emit.u58 = 0xF;
        spawn.texture = 0x60;
        spawn.u01 = 3;
        spawn.texSet = 0x2203;
        spawn.life = 300;
        spawn.u08 = 0;
        spawn.u0C = 0;
        spawn.color[0] = 0xFF;
        spawn.color[1] = 0xFF;
        spawn.color[2] = 0xFF;
        spawn.color[3] = 0xFF;
        spawn.halfW = 100.0f;
        spawn.halfH = 100.0f;
        fr.emit.u1C = D_800A215C;
        fr.emit.u20 = D_800A2160;
        spawn.angle[0] = ((s32 *)D_800A5860)[0];
        spawn.angle[1] = ((s32 *)D_800A5860)[1];
        spawn.angle[2] = ((s32 *)D_800A5860)[2];
        spawn.vel[0] = ((s32 *)D_800A5860)[0];
        spawn.vel[1] = ((s32 *)D_800A5860)[1];
        spawn.vel[2] = ((s32 *)D_800A5860)[2];
        spawn.scale[0] = 1.0f;
        spawn.scale[1] = 1.0f;
        spawn.scale[2] = 1.0f;
        spawn.flags = 0xCD2002;
        spawn.u44 = 0xFF;
        spawn.u45 = 0xFF;
        spawn.u46 = 0;
        spawn.u47 = 7;
        spawn.u48 = 0;
        spawn.u4C = 0xFF;
        for (ee.index = 0; ee.index < 2; ee.index++) {
            g->emit[ee.index] = func_151407D0(&fr.emit, 0x78, &spawn, 0, 0x2A, 0, 0, -1, alpha, owner);
            if (g->emit[ee.index] != NULL) {
                memcpy(g->emit[ee.index] + 0x170, &ee, 0x18);
            }
        }
    }
    shake.unk0 = 1;
    shake.unk2 = 0x46;
    shake.unk5 = 1;
    shake.unk4 = 8;
    shake.unk6 = -1;
    func_151D8E18(&shake, 0, alpha, owner);
    func_15160A58(obj, 1, &D_800A2090, 3, 0x46, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, alpha, owner);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150F9BB0.s")
#endif
