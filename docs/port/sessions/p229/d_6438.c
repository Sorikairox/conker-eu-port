#ifdef NON_MATCHING
typedef struct { f32 x, y, z; } EmitterVec;

/* D_800A8B80: 0x60-byte emitter kind rows (rodata_inject of the GLOBAL_ASM; referenced by symbol, P129 practice). */
typedef struct {
    /* 0x00 */ s16 kind;        /* request +0xC */
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 u08;
    /* 0x0C */ u8 u0C;
    /* 0x10 */ s32 u10;         /* stored as a byte in the request (+0x15) */
    /* 0x14 */ u8 node;         /* model matrix index (obj +0x1D4 + node * 0x40) */
    /* 0x18 */ EmitterVec at;   /* local points, transformed by the node's matrix */
    /* 0x24 */ EmitterVec at2;
    /* 0x30 */ s8 speedFn;      /* D_8008FC10 index, -1 = none */
    /* 0x31 */ u8 u31;
    /* 0x32 */ u8 u32;
    /* 0x33 */ u8 u33;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 u38;
    /* 0x3C */ s8 initFn;       /* D_8008FC1C index, -1 = none */
    /* 0x3D */ s8 u3D;
    /* 0x3E */ s8 u3E;
    /* 0x3F */ s8 soundFn;      /* D_8008FC30 index (start sound), -1 = none */
    /* 0x40 */ s8 u40;
    /* 0x41 */ s8 u41;
    /* 0x42 */ s8 u42;
    /* 0x44 */ u16 u44;         /* request +0xE */
    /* 0x46 */ u8 u46;
    /* 0x47 */ u8 u47;
    /* 0x48 */ f32 u48;
    /* 0x4C */ u8 u4C;
    /* 0x50 */ f32 u50;
    /* 0x54 */ u8 u54;
    /* 0x58 */ f32 u58;
    /* 0x5C */ u8 u5C[4];
} EmitterKind;

/* The 0x90-byte record copied into the new emitter's +0x98 buffer (func_151991D0 / func_15199200 read +0x66). */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 objId;        /* obj +0x3B */
    /* 0x05 */ u8 node;
    /* 0x06 */ u8 flags;        /* 2 */
    /* 0x07 */ s8 speedFn;
    /* 0x08 */ EmitterVec at;
    /* 0x14 */ EmitterVec at2;
    /* 0x20 */ EmitterVec pos;  /* world points */
    /* 0x2C */ EmitterVec pos2;
    /* 0x38 */ f32 speed;       /* set after the copy from D_8008FC10 */
    /* 0x3C */ f32 u3C;
    /* 0x40 */ f32 u40;
    /* 0x44 */ f32 u44;
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ u8 u50;
    /* 0x51 */ u8 u51;
    /* 0x52 */ u8 u52;
    /* 0x53 */ u8 u53;
    /* 0x54 */ u8 u54;
    /* 0x58 */ f32 u58;
    /* 0x5C */ f32 u5C;
    /* 0x60 */ s8 initFn;
    /* 0x61 */ s8 u61;
    /* 0x62 */ s8 u62;
    /* 0x63 */ s8 soundFn;
    /* 0x64 */ s8 u64;
    /* 0x65 */ s8 u65;
    /* 0x66 */ u16 voice;
    /* 0x68 */ s8 u68;
    /* 0x69 */ u8 u69;
    /* 0x6A */ u8 u6A;
    /* 0x6C */ f32 u6C;
    /* 0x70 */ f32 u70;
    /* 0x74 */ u8 u74;
    /* 0x78 */ f32 u78;
    /* 0x7C */ f32 u7C;
    /* 0x80 */ u8 u80;
    /* 0x84 */ f32 u84;
    /* 0x88 */ f32 u88;
    /* 0x8C */ u8 u8C[4];
} EmitterRecord;

/* The request func_15147FF0 reads (position, kind, life). */
typedef struct {
    /* 0x00 */ EmitterVec pos;
    /* 0x0C */ s16 kind;
    /* 0x0E */ u16 u0E;
    /* 0x10 */ s32 u10;         /* 3 */
    /* 0x14 */ u8 pad14;
    /* 0x15 */ u8 u15;
} EmitterRequest;

void *memcpy(void *, const void *, s32);
extern EmitterKind D_800A8B80[];
extern f32 (*D_8008FC10[])(u8 *);   /* speed: func_15197F68 / func_15197F7C / func_15197FD8 */
extern void (*D_8008FC1C[])(u8 *);  /* init: func_15199954 */
extern u16 (*D_8008FC30[])(void);   /* start sound: func_151991D0 */

// object_emitter_spawn: spawns emitter `kind` (D_800A8B80 row) attached to the object's model node: fills the 0x90-byte
// record (object, node, the row's two local points and their world positions, the row's parameters, the start
// sound's voice handle), asks func_15147FF0 for a 0x90-byte emitter (layer / owner from arg2 / arg3), copies the
// record into it, sets its speed from D_8008FC10 and runs the init handler. Returns the emitter (0 when the object
// or its model matrices are missing, or no emitter is free).
u8 *func_15196438(u8 *obj, s32 kind, u8 arg2, s32 arg3) {
    EmitterRecord rec;
    EmitterRequest req;
    EmitterKind *k;
    EmitterRecord *dst;
    u8 *mtx;
    u8 *e;

    if (obj == NULL) {
        return NULL;
    }
    if (*(u8 **)(obj + 0x1D4) == NULL) {
        return NULL;
    }
    k = &D_800A8B80[kind];
    rec.obj = obj;
    rec.objId = obj[0x3B];
    rec.node = k->node;
    rec.flags = 2;
    rec.speedFn = k->speedFn;
    rec.at = k->at;
    rec.at2 = k->at2;
    rec.u40 = k->u04;
    rec.u48 = k->u08;
    rec.u4C = 0.0f;
    rec.u50 = 0;
    rec.u51 = k->u0C;
    rec.u52 = k->u31;
    rec.u53 = k->u32;
    rec.u54 = k->u33;
    rec.u58 = k->u34;
    rec.u5C = k->u38;
    rec.initFn = k->initFn;
    rec.u61 = k->u3D;
    rec.u62 = k->u3E;
    rec.soundFn = k->soundFn;
    rec.u64 = k->u40;
    rec.u65 = k->u41;
    rec.u68 = k->u42;
    rec.u69 = k->u46;
    rec.u6A = k->u47;
    rec.u6C = k->u48;
    rec.u70 = 0.0f;
    rec.u74 = k->u4C;
    rec.u78 = k->u50;
    rec.u7C = 0.0f;
    rec.u80 = k->u54;
    rec.u84 = k->u58;
    rec.u88 = 0.0f;
    rec.u8C[0] = k->u5C[0];
    rec.u8C[1] = k->u5C[1];
    rec.u8C[2] = k->u5C[2];
    rec.u8C[3] = k->u5C[3];
    req.kind = k->kind;
    req.u0E = k->u44;
    req.u15 = k->u10;

    if (rec.soundFn != -1) {
        rec.voice = D_8008FC30[rec.soundFn]();
    } else {
        rec.voice = 0;
    }

    mtx = *(u8 **)(rec.obj + 0x1D4) + (rec.node << 6);
    func_15143134(&rec.at, &rec.pos, mtx);
    func_15143134(&rec.at2, &rec.pos2, mtx);
    req.pos.x = rec.pos.x;
    req.pos.y = rec.pos.y;
    req.pos.z = rec.pos.z;
    rec.u3C = 0.0f;
    req.u10 = 3;

    e = func_15147FF0(&req, 0x90, 0x24, 2, 2, 2, 0, 0, 0, arg2, arg3);
    if (e != NULL) {
        dst = *(EmitterRecord **)(e + 0x98);
        memcpy(dst, &rec, sizeof(EmitterRecord));
        if (dst->speedFn != -1) {
            dst->speed = D_8008FC10[dst->speedFn](e);
        } else {
            dst->speed = 0.0f;
        }
        if (rec.initFn != -1) {
            D_8008FC1C[rec.initFn](e);
        }
    }
    return e;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196438.s")
#endif
