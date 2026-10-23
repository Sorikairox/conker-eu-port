s32 func_151308E4(s32 tmpl, u8 arg1, s32 size, u8 arg3, s32 arg4);
u8 *func_151407D0(void *emit, s32 emitSize, void *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8,
                  s32 arg9);

/* spawn block of func_1513D4B8 / func_151407D0 (0x48 bytes, the func_150113E0 layout) */
typedef struct {
    u8 kind;          /* 0x00 */
    u8 sub;           /* 0x01 */
    u16 flags;        /* 0x02 */
    s16 life;         /* 0x04 */
    u8 pad6[2];
    s32 u8_;          /* 0x08 */
    s32 uC;           /* 0x0C */
    u8 rgba[4];       /* 0x10 */
    f32 size[2];      /* 0x14 */
    f32 pos0[3];      /* 0x1C */
    f32 pos1[3];      /* 0x28 */
    f32 scale[3];     /* 0x34 */
    s32 mode;         /* 0x40 */
    u8 u44[4];        /* 0x44 */
} SpawnBlock0B80;

/* particle template of func_151308E4 (0x70 bytes, the func_15153BA4 layout) */
typedef struct {
    s32 u0;           /* 0x00 */
    s32 u4;           /* 0x04 */
    u16 flags;        /* 0x08 */
    s16 life;         /* 0x0A */
    s32 uC;           /* 0x0C */
    s32 u10;          /* 0x10 */
    u8 colour[8];     /* 0x14: 4 bytes, rgb, alpha */
    u8 u1C;           /* 0x1C */
    u8 kind;          /* 0x1D */
    s16 u1E;          /* 0x1E */
    s16 u20;          /* 0x20 */
    s16 u22;          /* 0x22 */
    f32 u24;          /* 0x24 */
    f32 size[2];      /* 0x28 */
    f32 zero30[10];   /* 0x30 */
    s32 mode;         /* 0x58 */
    u8 pad5C[4];
    u8 u60[6];        /* 0x60 */
    u8 pad66[0xA];
} PartTmpl0B80;

/*
 * The stack blocks of func_15100B80 in one struct so the layout is the N64 one (offsets = original sp offsets).
 * The emitter block (sp12C) is passed with size 0x68, so its last 12 bytes are the first words of the spark
 * payload (sp188: 0.0, 0.0, 10.25): kept that way.
 */
typedef struct {
    struct {                  /* sp54: copied to the glow particle's +0xA8 (8 bytes) */
        u8 *owner;
        u8 zero;
        u8 pad[3];
    } glowPay;
    PartTmpl0B80 glow;        /* sp5C: glow particle (kind 0x15) */
    struct {                  /* spCC: copied to the emitter's +0x170 (8 bytes) */
        u8 *owner;
        u8 zero;
        u8 pad[3];
    } emitPay;
    SpawnBlock0B80 emitSpawn; /* spD4: emitter spawn block (kind 3) */
    u8 pad11C[0x10];
    struct {                  /* sp12C: emitter block (0x5C + the 12 overlapping bytes) */
        f32 range[4];         /* 0x00 */
        f32 u10;              /* 0x10 */
        f32 u14[4];           /* 0x14 */
        u8 pad24[0x24];
        f32 u48;              /* 0x48 */
        u8 pad4C[8];
        u8 u54[5];            /* 0x54 */
        u8 pad59[3];
    } emit;
    struct {                  /* sp188: copied to the spark particle's +0xA8 (0x30 bytes) */
        f32 u0;
        f32 u4;
        f32 size[2];          /* 0x08 */
        f32 u10[2];           /* 0x10 */
        f32 angle[2];         /* 0x18: random [0, 2pi) */
        f32 spin[2];          /* 0x20: random [-0.3, 0.3) */
        u8 *owner;            /* 0x28 */
        u8 zero;              /* 0x2C */
        u8 pad[3];
    } sparkPay;
    PartTmpl0B80 spark;       /* sp1B8: spark particle (kind 0x2B) */
    u8 *lightPay;             /* sp228: copied to the light's +0x18 */
    Header2 lightArg;         /* sp22C */
    Header light;             /* sp238 */
    u8 pad23E[2];
    struct {                  /* sp240: copied to the second record's +0x110 (0x18 bytes) */
        u8 zero;
        u8 pad[0x13];
        u8 *owner;            /* 0x14 */
    } rec2Pay;
    SpawnBlock0B80 rec2Spawn; /* sp258: second record (kind 3) */
    u8 pad2A0[0x17];
    u8 timed;                 /* sp2B7: 0 when life was -1 (300 then) */
    struct {                  /* sp2B8: copied to the main record's +0x110 (0x94 bytes) */
        u8 *obj;              /* 0x00 */
        u8 objType;           /* 0x04: obj[0x3B] */
        u8 pad5[3];
        f32 pos[3];           /* 0x08 */
        f32 dir[3];           /* 0x14 */
        u8 kind;              /* 0x20 */
        s8 objIndex;          /* 0x21: slot in D_800CC2D0 */
        u8 owner23D;          /* 0x22: obj +0x318 byte 0x23D, 0xFF without */
        u8 mode;              /* 0x23: 2 or 0 */
        u8 pad24[0x14];
        f32 param[22];        /* 0x38: [3] is never written */
        u16 sound;            /* 0x90 */
        u8 pad92[2];
    } main;
    SpawnBlock0B80 mainSpawn; /* sp34C: main record (kind 0x59) */
} Frame0B80;

// object_burst_effect_spawn: builds the compound effect of func_15102C3C on obj: a main record (kind 0x59,
// func_1513D4B8 with the 0x94-byte state: obj, pos, dir, kind, the obj slot, sizes arg8..argB, a sound handle from
// func_10010F30 when obj +0x318 is set), and under it (stored in the state at +0x28 .. +0x34) a second record
// (kind 3), a light (func_151602C0), a spark particle (kind 0x2B, random angles / spin), a particle emitter
// (func_151407D0) and a glow particle (kind 0x15). life -1 means 300 ticks and clears the "timed" flag bit 1 of
// every block. rgb = colour of every part. Returns the main record (0 when it could not be created).
s32 func_15100B80(u8 *obj, f32 *pos, f32 *dir, u8 kind, s16 life, u8 r, u8 g, u8 b, f32 arg8, f32 arg9, f32 argA,
                  f32 argB, u8 argC, u8 argD, s32 argE) {
    Frame0B80 f;
    u8 *rec;
    u8 *state;
    s32 bit40;
    s32 bit80;

    if (life == -1) {
        f.timed = 0;
        life = 300;
    } else {
        f.timed = 1;
    }

    /* main record state */
    f.main.objIndex = (s32) (obj - (u8 *) D_800CC2D0) / 812;
    if (*(u8 **) (obj + 0x318) != NULL) {
        f.main.owner23D = (*(u8 **) (obj + 0x318))[0x23D];
    } else {
        f.main.owner23D = 0xFF;
    }
    f.main.obj = obj;
    f.main.kind = kind;
    f.main.objType = obj[0x3B];
    f.main.mode = (argC != 0) ? 2 : 0;
    f.main.pos[0] = pos[0];
    f.main.pos[1] = pos[1];
    f.main.pos[2] = pos[2];
    f.main.dir[0] = dir[0];
    f.main.dir[1] = dir[1];
    f.main.dir[2] = dir[2];
    f.main.param[0] = 0.0f;
    f.main.param[1] = arg8;
    f.main.param[2] = 0.102f;
    f.main.param[4] = arg9;
    f.main.param[5] = argA;
    f.main.param[6] = 0.0f;
    f.main.param[7] = argB;
    f.main.param[8] = -32768.0f;
    f.main.param[9] = 0.0f;
    f.main.param[10] = 0.0f;
    f.main.param[11] = 250.0f;
    f.main.param[12] = 0.0f;
    f.main.param[13] = 25.0f;
    f.main.param[14] = 0.45f;
    f.main.param[15] = 255.0f;
    f.main.param[16] = 0.0f;
    f.main.param[17] = 128.0f;
    f.main.param[18] = 127.0f;
    f.main.param[19] = 0.0f;
    f.main.param[20] = 20.0f;
    f.main.param[21] = 0.4f;
    if (*(u8 **) (obj + 0x318) != NULL) {
        f.main.sound = func_10010F30(0x4D0, 0x7D0, 0x40, 0, 0);
    } else {
        f.main.sound = 0;
    }

    f.mainSpawn.kind = 0x59;
    f.mainSpawn.sub = 1;
    f.mainSpawn.flags = 0x3103;
    f.mainSpawn.u8_ = 0;
    f.mainSpawn.uC = 0;
    f.mainSpawn.rgba[3] = 0xFF;
    f.mainSpawn.pos0[0] = 0.0f;
    f.mainSpawn.pos0[1] = 0.0f;
    f.mainSpawn.pos0[2] = 0.0f;
    f.mainSpawn.pos1[0] = 0.0f;
    f.mainSpawn.pos1[1] = 0.0f;
    f.mainSpawn.pos1[2] = 0.0f;
    f.mainSpawn.scale[0] = 1.0f;
    f.mainSpawn.scale[1] = 1.0f;
    f.mainSpawn.scale[2] = 1.0f;
    f.mainSpawn.size[0] = 100.0f;
    f.mainSpawn.size[1] = 100.0f;
    f.mainSpawn.life = life;
    f.mainSpawn.rgba[0] = r;
    f.mainSpawn.rgba[1] = g;
    f.mainSpawn.rgba[2] = b;
    f.mainSpawn.mode = (f.timed ? 1 : 0) | 0x40000 | 0x80000 | 0x200000 | 0x400000 | 0x80000000;
    f.mainSpawn.u44[0] = 0xFF;
    f.mainSpawn.u44[1] = 0xFF;
    f.mainSpawn.u44[2] = 0;
    f.mainSpawn.u44[3] = 6;
    rec = (u8 *) func_1513D4B8((s32) &f.mainSpawn, (s32) &D_800A4AA0, 0x15, 0x1F, 0, 0x12, 0, 0x94, argD, argE);
    if (rec == NULL) {
        return 0;
    }
    state = rec + 0x110;
    memcpy((s32) state, (s32) &f.main, 0x94);

    /* second record (kind 3), state +0x28 */
    f.rec2Pay.owner = rec;
    f.rec2Pay.zero = 0;
    f.rec2Spawn.kind = 3;
    f.rec2Spawn.sub = 2;
    f.rec2Spawn.flags = 0x3201;
    f.rec2Spawn.u8_ = 0;
    f.rec2Spawn.uC = 0;
    f.rec2Spawn.rgba[3] = 0xFF;
    f.rec2Spawn.size[1] = 0.0f;
    f.rec2Spawn.size[0] = 0.0f;
    f.rec2Spawn.pos0[0] = 0.0f;
    f.rec2Spawn.pos0[1] = 0.0f;
    f.rec2Spawn.pos0[2] = 0.0f;
    f.rec2Spawn.pos1[0] = 0.0f;
    f.rec2Spawn.pos1[1] = 0.0f;
    f.rec2Spawn.pos1[2] = 0.0f;
    f.rec2Spawn.scale[0] = 1.0f;
    f.rec2Spawn.scale[1] = 1.0f;
    f.rec2Spawn.scale[2] = 1.0f;
    f.rec2Spawn.life = life;
    f.rec2Spawn.rgba[0] = r;
    f.rec2Spawn.rgba[1] = g;
    f.rec2Spawn.rgba[2] = b;
    f.rec2Spawn.mode = (f.timed ? 1 : 0) | 0x40000 | 0x80000 | 0x400000;
    f.rec2Spawn.u44[0] = 0xFF;
    f.rec2Spawn.u44[1] = 0xFF;
    f.rec2Spawn.u44[2] = 0;
    f.rec2Spawn.u44[3] = 6;
    *(u8 **) (state + 0x28) =
        (u8 *) func_1513D4B8((s32) &f.rec2Spawn, (s32) &D_800A4AA0, 0, 0, 0, 0x13, 0, 0x18, argD, argE);
    if (*(u8 **) (state + 0x28) != NULL) {
        memcpy((s32) (*(u8 **) (state + 0x28) + 0x110), (s32) &f.rec2Pay, 0x18);
    }

    /* light, state +0x2C */
    f.lightArg.unk0 = 0;
    f.lightArg.unk4 = 0;
    f.lightArg.unk8 = 0;
    f.lightPay = rec;
    f.light.unk0 = (f.timed ? 1 : 0) | 2;
    f.light.unk1 = -1;
    f.light.unk4 = 7;
    f.light.unk2 = life;
    *(struct225 **) (state + 0x2C) = func_151602C0(&f.light, &f.lightArg, 5, r, g, b, 0xFF, 0, 4, argD, argE);
    if (*(struct225 **) (state + 0x2C) != NULL) {
        memcpy((s32) (*(u8 **) (state + 0x2C) + 0x18), (s32) &f.lightPay, 4);
    }

    /* spark particle (kind 0x2B), state +0x24 */
    f.sparkPay.zero = 0;
    f.sparkPay.u0 = 0.0f;
    f.sparkPay.u4 = 0.0f;
    f.sparkPay.size[1] = 10.250001f; /* 0x41240001 */
    f.sparkPay.size[0] = 10.250001f;
    f.sparkPay.u10[1] = 2.7500002f;  /* 0x40300001 */
    f.sparkPay.u10[0] = 2.7500002f;
    f.sparkPay.owner = rec;
    f.sparkPay.angle[0] = func_150ADA68() * 6.2831855f;
    f.sparkPay.angle[1] = func_150ADA68() * 6.2831855f;
    f.sparkPay.spin[0] = func_150ADA68() * 0.59999996f + -0.29999998f; /* 0x3F199999, 0xBE999999 */
    f.sparkPay.spin[1] = func_150ADA68() * 0.59999996f + -0.29999998f;
    f.spark.kind = 0x2B;
    f.spark.flags = 0x3303;
    f.spark.u0 = 0x200005;
    f.spark.colour[0] = 0xFF;
    f.spark.colour[2] = 0xFF;
    f.spark.life = life;
    f.spark.u4 = 0;
    f.spark.uC = 0;
    f.spark.u10 = 0;
    f.spark.colour[1] = 0xFF;
    f.spark.colour[3] = 0xFF;
    f.spark.colour[7] = 0xFF;
    f.spark.u1C = 0xFF;
    f.spark.size[1] = 0.0f;
    f.spark.size[0] = 0.0f;
    f.spark.zero30[0] = 0.0f;
    f.spark.zero30[1] = 0.0f;
    f.spark.zero30[2] = 0.0f;
    f.spark.zero30[3] = 0.0f;
    f.spark.zero30[4] = 0.0f;
    f.spark.zero30[5] = 0.0f;
    f.spark.zero30[6] = 0.0f;
    f.spark.zero30[7] = 0.0f;
    f.spark.zero30[8] = 0.0f;
    f.spark.zero30[9] = 0.0f;
    f.spark.u1E = 1;
    f.spark.u20 = 0xFF;
    f.spark.u22 = 1;
    f.spark.colour[4] = r;
    f.spark.colour[5] = g;
    f.spark.colour[6] = b;
    f.spark.u24 = 1.0f;
    bit40 = (func_150ADA20() & 1) ? 0x40 : 0;
    bit80 = (func_150ADA20() & 1) ? 0x80 : 0;
    f.spark.mode = bit80 | (f.timed ? 1 : 0) | bit40 | 0xC000;
    f.spark.u60[0] = 6;
    f.spark.u60[1] = 6;
    f.spark.u60[2] = 0xB;
    f.spark.u60[3] = 0xFF;
    f.spark.u60[4] = 0;
    f.spark.u60[5] = 1;
    *(s32 *) (state + 0x24) = func_151308E4((s32) &f.spark, 1, 0x30, argD, argE);
    if (*(s32 *) (state + 0x24) != 0) {
        memcpy(*(s32 *) (state + 0x24) + 0xA8, (s32) &f.sparkPay, 0x30);
    }

    /* particle emitter (spawn kind 3), state +0x30 */
    f.emitPay.owner = rec;
    f.emitPay.zero = 0;
    f.emitSpawn.kind = 3;
    f.emitSpawn.sub = 3;
    f.emitSpawn.flags = 0x3403;
    f.emitSpawn.u8_ = 0;
    f.emitSpawn.uC = 0;
    f.emitSpawn.rgba[3] = 0xFF;
    f.emitSpawn.size[0] = 100.0f;
    f.emitSpawn.size[1] = 100.0f;
    f.emitSpawn.pos0[0] = 0.0f;
    f.emitSpawn.pos0[1] = 0.0f;
    f.emitSpawn.pos0[2] = 0.0f;
    f.emitSpawn.pos1[0] = 0.0f;
    f.emitSpawn.pos1[1] = 0.0f;
    f.emitSpawn.scale[0] = 1.0f;
    f.emitSpawn.scale[1] = 1.0f;
    f.emitSpawn.scale[2] = 1.0f;
    f.emitSpawn.life = life;
    f.emitSpawn.rgba[0] = r;
    f.emitSpawn.rgba[1] = g;
    f.emitSpawn.rgba[2] = b;
    f.emitSpawn.pos1[2] = 500.0f;
    f.emitSpawn.mode = (f.timed ? 1 : 0) | 0x2012 | 0x20000 | 0x40000 | 0x80000 | 0x400000;
    f.emitSpawn.u44[1] = 0xFF;
    f.emitSpawn.u44[0] = 0xFF;
    f.emitSpawn.u44[2] = 0;
    f.emitSpawn.u44[3] = 6;
    f.emit.u14[3] = 1e-06f;
    f.emit.u14[2] = 0.0f;
    f.emit.range[3] = 0.0f;
    f.emit.u54[0] = 0;
    f.emit.u54[1] = 0;
    f.emit.u54[2] = 0;
    f.emit.u54[3] = 0;
    f.emit.u48 = 1.0f;
    f.emit.u54[4] = 1;
    f.emit.range[1] = 60.000004f; /* 0x42700001 */
    f.emit.range[0] = 60.000004f;
    f.emit.u10 = 0.5f;
    f.emit.u14[0] = 0.5f;
    f.emit.u14[1] = 0.3f;
    f.emit.range[2] = 0.0f;
    *(u8 **) (state + 0x30) = func_151407D0(&f.emit, 0x68, &f.emitSpawn, 0, 0, 0, 0, 0, argD, argE);
    if (*(u8 **) (state + 0x30) != NULL) {
        memcpy((s32) (*(u8 **) (state + 0x30) + 0x170), (s32) &f.emitPay, 8);
    }

    /* glow particle (kind 0x15), state +0x34 */
    f.glow.kind = 0x15;
    f.glow.flags = 0x3203;
    f.glowPay.owner = rec;
    f.glow.u0 = 0x200005;
    f.glow.colour[0] = 0xFF;
    f.glow.colour[2] = 0xFF;
    f.glow.life = life;
    f.glowPay.zero = 0;
    f.glow.u4 = 0;
    f.glow.uC = 0;
    f.glow.u10 = 0;
    f.glow.colour[1] = 0xFF;
    f.glow.colour[3] = 0xFF;
    f.glow.colour[7] = 0xFF;
    f.glow.u1C = 0xFF;
    f.glow.size[1] = 125.0f;
    f.glow.size[0] = 125.0f;
    f.glow.zero30[0] = 0.0f;
    f.glow.zero30[1] = 0.0f;
    f.glow.zero30[2] = 0.0f;
    f.glow.zero30[3] = 0.0f;
    f.glow.zero30[4] = 0.0f;
    f.glow.zero30[5] = 0.0f;
    f.glow.zero30[6] = 0.0f;
    f.glow.zero30[7] = 0.0f;
    f.glow.zero30[8] = 0.0f;
    f.glow.zero30[9] = 0.0f;
    f.glow.u1E = 1;
    f.glow.u20 = 0xFF;
    f.glow.u22 = 1;
    f.glow.colour[4] = r;
    f.glow.colour[5] = g;
    f.glow.colour[6] = b;
    f.glow.u24 = 1.0f;
    bit40 = (func_150ADA20() & 1) ? 0x40 : 0;
    bit80 = (func_150ADA20() & 1) ? 0x80 : 0;
    f.glow.mode = bit80 | (f.timed ? 1 : 0) | bit40 | 0xC000;
    f.glow.u60[0] = 6;
    f.glow.u60[1] = 6;
    f.glow.u60[2] = 0xFF;
    f.glow.u60[3] = 0xFF;
    f.glow.u60[4] = 1;
    f.glow.u60[5] = 5;
    *(s32 *) (state + 0x34) = func_151308E4((s32) &f.glow, 1, 8, argD, argE);
    if (*(s32 *) (state + 0x34) != 0) {
        memcpy(*(s32 *) (state + 0x34) + 0xA8, (s32) &f.glowPay, 8);
    }
    return (s32) rec;
}
