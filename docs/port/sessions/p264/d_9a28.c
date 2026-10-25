#ifdef NON_MATCHING
struct225 *func_1519C60C(s32 arg0, f32 *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7);
void func_15145EA4(f32 **, f32 **, void *, s32);
extern void (*D_8008FC44[])(u8 *); /* init: func_1519C428, func_1519CEB8, func_1519CEE0, func_1519CF08, func_1519C490 */
extern u16 (*D_8008FC58[])(void);  /* start sound: func_1519C4FC */

/* The 0x154-byte record copied into the spawned object's data (+0x98). */
typedef struct {
    /* 0x000 */ u8 *obj;
    /* 0x004 */ u8 u04;
    /* 0x005 */ u8 node;
    /* 0x006 */ u8 pad06[2];
    /* 0x008 */ f32 at[3];   /* two points in the node's space */
    /* 0x014 */ f32 at2[3];
    /* 0x020 */ u8 u20[0x14];
    /* 0x034 */ s8 initFn;   /* D_8008FC44 index or -1 */
    /* 0x035 */ u8 u35[2];
    /* 0x037 */ s8 soundFn;  /* D_8008FC58 index or -1 */
    /* 0x038 */ u8 u38[2];
    /* 0x03A */ u8 u3A;
    /* 0x03B */ u8 u3B[0x11];
    /* 0x04C */ s32 u4C[0x31]; /* copy of the spec's +0x58..+0x11C */
    /* 0x110 */ f32 pos[3];  /* world positions of at / at2 */
    /* 0x11C */ f32 pos2[3];
    /* 0x128 */ f32 u128;
    /* 0x12C */ f32 u12C;
    /* 0x130 */ u16 voice;
    /* 0x134 */ f32 u134;
    /* 0x138 */ f32 u138;
    /* 0x13C */ f32 u13C;
    /* 0x140 */ f32 u140;
    /* 0x144 */ f32 u144;
    /* 0x148 */ s32 u148;
    /* 0x14C */ f32 u14C;
    /* 0x150 */ u8 flags;
    /* 0x151 */ u8 u151;
    /* 0x152 */ s16 u152;
} Emitter2Record;

/* The request func_15147FF0 reads. */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ s16 kind;
    /* 0x0E */ s16 u0E;
    /* 0x10 */ s32 u10;
    /* 0x14 */ u8 u14;
    /* 0x15 */ u8 u15;
} Emitter2Request;

// spec_emitter_spawn: spawns a type-0x12C emitter object from a spec (arg1: +0 kind byte, +4.. the record head with
// the attach object, node and two local points, +0x50..+0x53 trail parameters, +0x54 flags, +0x58.. the rest of the
// record) with arg0 extra data bytes (func_15147FF0 size arg0 + 0x158, layer / owner arg2 / arg3). Returns 0 when the
// object has no model matrices (+0x1D4) or no object is free. The two points are transformed by the node's matrix
// (func_15145EA4); the first is the spawn position. Spec flags 2 / 4 / 8 / 0x10 become record flags 2 / 4 / 8 / 0x20.
// After copying the record into the new object it stores the start sound's voice (D_8008FC58), runs the init handler
// (D_8008FC44) and, with spec flag 1, starts a trail (func_1519C60C) whose handle goes to +0x148.
u8 *func_15199A28(s32 arg0, u8 *spec, u8 arg2, s32 arg3) {
    Emitter2Record rec;
    Emitter2Request req;
    f32 *src[2];
    f32 *dst[2];
    Emitter2Record *data;
    u8 *e;
    s32 i;
    u8 fl;

    if (*(u8 **) (*(u8 **) (spec + 4) + 0x1D4) == NULL) {
        return NULL;
    }
    req.kind = 0x12C;
    req.u0E = 0x12;
    req.u15 = *(s32 *) spec;
    req.u10 = 0xE;
    req.u14 = 0;
    for (i = 0; i < 0x4C / 4; i++) {
        ((s32 *) &rec)[i] = ((s32 *) (spec + 4))[i];
    }
    src[0] = rec.at;
    src[1] = rec.at2;
    dst[0] = rec.pos;
    dst[1] = rec.pos2;
    func_15145EA4(src, dst, *(u8 **) (rec.obj + 0x1D4) + (rec.node << 6), 2);
    req.pos[0] = rec.pos[0];
    req.pos[1] = rec.pos[1];
    req.pos[2] = rec.pos[2];
    rec.u128 = 0.0f;
    rec.u12C = 0.0f;
    rec.u140 = rec.u3A;
    rec.u144 = -16384.0f;
    for (i = 0; i < 0x31; i++) {
        rec.u4C[i] = ((s32 *) (spec + 0x58))[i];
    }
    rec.u134 = 0.0f;
    rec.u138 = 0.0f;
    rec.u13C = 0.0f;
    rec.u14C = 0.0f;
    fl = spec[0x54];
    rec.flags = ((fl & 0x10) ? 0x20 : 0) | ((fl & 2) ? 2 : 0) | ((fl & 4) ? 4 : 0) | ((fl & 8) ? 8 : 0);
    rec.u152 = 0;
    rec.u151 = 0;

    e = func_15147FF0(&req, arg0 + 0x158, 0x28, 0xC, 0xC, 0xC, 0, 0, 0, arg2, arg3);
    if (e != NULL) {
        data = *(Emitter2Record **) (e + 0x98);
        memcpy(data, &rec, sizeof(Emitter2Record));
        if (rec.soundFn != -1) {
            data->voice = D_8008FC58[rec.soundFn]();
        } else {
            data->voice = 0;
        }
        if (rec.initFn != -1) {
            D_8008FC44[rec.initFn](e);
        }
        if (spec[0x54] & 1) {
            data->u148 = (s32) func_1519C60C((s32) e, req.pos, spec[0x50], spec[0x51], spec[0x52], spec[0x53], arg2, arg3);
        } else {
            data->u148 = 0;
        }
    }
    return e;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15199A28.s")
#endif
