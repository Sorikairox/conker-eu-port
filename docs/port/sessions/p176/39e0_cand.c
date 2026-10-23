void *allocate_memory(s32 size, s32 arg1, s32 arg2, s32 arg3);
s32 func_1502B6BC(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, ...);
s32 func_1502B7F0(s32 *arg0, s32 arg1, ...);
s32 func_1510D3E0(Gfx *dl, s32 skipResolved, s32 addRef, s32 age, s16 **outList);
s32 func_15004BF0(s32 arg0);
void func_15004CE0(Gfx *arg0, s32 arg1);
void func_15004AAC(u8 *arg0, s32 arg1);
extern u16 D_800BE6C0;
extern u16 D_800BE6C2;
extern u16 D_800BE6C4;
extern s32 D_80089030[][3];        /* per object type: callback +0x38, +0x78, byte +0x92 */
extern u8 D_800A2A90[];            /* per model id: 12-byte display records (multiplayer objects) */
extern u8 **D_800B1260;            /* level model segments, 8-byte entries: word 0 = segment */
extern void *D_800DC300[4];
extern void *D_800DC310;
extern void *D_800DC314;
extern u8 D_800DC3B8;
extern s32 *D_800DC3C4;
extern s32 D_800DC3C8;

#define WOBJ(i) ((u8 *) D_800DBEF4 + (i) * 0xA0)
#define W8(p, o) (*(u8 *) ((u8 *) (p) + (o)))
#define W16(p, o) (*(u16 *) ((u8 *) (p) + (o)))
#define S16(p, o) (*(s16 *) ((u8 *) (p) + (o)))
#define W32(p, o) (*(s32 *) ((u8 *) (p) + (o)))
#define WPTR(p, o) (*(u8 **) ((u8 *) (p) + (o)))
#define WF32(p, o) (*(f32 *) ((u8 *) (p) + (o)))

/* world_objects_load: builds the level's world objects (0xA0-byte records at D_800DBEF4, count D_800DC320) from
 * the level's two 0x44-byte placement lists (asset 2/0xB/level: D_800DBF00 level objects, asset 3/0xC/level/2:
 * D_800DC3C8 multiplayer objects). Per object: position (s16 +0x10..), origin floats, scale, the type's callback
 * table D_80089030 (types < 0xFFFF; 0x28 / 0x42 set the +0x70 bit 2 and keep it for the next multiplayer ones, type
 * 0x16 = "has a callback"), its model: an earlier object with the same key (+0xC / +0x10) shares its vertices /
 * display list, else the model is loaded (func_1502B6BC 3/id, kind 0 in +0x1C) or taken from the level segments
 * D_800B1260 (kind 1 / 2). Then the vertex buffers (+0x20 / +0x24 copies for moving objects, bit 0 of +0x70),
 * the per-object arrays D_800DC310 / 314 / 328 / 32C / 300[4] / 3C4, and object ids +0x72 (func_15004BF0).
 * arg1 is unused. Literal quirks kept: the model segment `seg` is only loaded for kind-0 objects but is also passed
 * to func_15004CE0 for kind 1 / 2 / other objects without a shared model (the asm keeps it in s6 from the previous
 * kind-0 object; uninitialised stack before the first one: NULL here); a type >= 0xFFFF is stored as the callback. */
void func_150039E0(s32 arg0, s32 arg1) {
    s32 bufA;          /* sp+0xA0: level placement list */
    s32 bufB;          /* sp+0x9C: multiplayer placement list */
    s32 found;         /* sp+0xA8 */
    u8 *base;          /* s7: list base so that base + i * 0x44 is object i's placement record */
    u8 *src;
    u8 *obj;
    u8 *prev;
    u8 *seg = NULL;    /* s6 */
    u8 *lseg = NULL;   /* fp */
    u8 *e;
    u8 *s;
    s32 i, j, k;
    s32 link;          /* s4: index + 1 of the object whose model is shared, 0 = none */
    s32 hasCb;         /* sp+0x84 */
    s8 keepBit2;       /* sp+0x8B */
    s32 type;
    s32 id;
    s32 kind;
    s32 nA, nB;

    D_800DC3B8 = 0xFF;
    D_800BE6C2 = 0;
    D_800BE6C4 = 0;
    bufA = 0;
    bufB = 0;
    keepBit2 = 0;
    D_800BE6C0 = 0;
    nA = (u32) func_1502B7F0(&bufA, 2, 0xB, arg0) / 0x44;
    D_800DBF00 = nA;
    D_800DC320 = D_800DBF00;
    nB = (u32) func_1502B7F0(&bufB, 3, 0xC, arg0, 2) / 0x44;
    D_800DC3C8 = nB;
    D_800DC320 = D_800DC320 + nB;
    D_800DBEF4 = allocate_memory(D_800DC320 * 0xA0, 1, 2, 0);
    if (D_800DBEF4 == NULL) {
        D_800DC320 = 0;
        D_800DC3C8 = 0;
        D_800DBF00 = 0;
        return;
    }

    base = (u8 *) bufA;
    for (i = 0; i < D_800DC320; i++) {
        link = 0;
        hasCb = 0;
        if (i == D_800DBF00) {
            base = (u8 *) bufB - i * 0x44;
        }
        obj = WOBJ(i);
        src = base + i * 0x44;
        S16(obj, 0x10) = S16(src, 0);
        S16(obj, 0x12) = S16(src, 2);
        S16(obj, 0x14) = S16(src, 4);
        WF32(obj, 0) = S16(src, 6);
        WF32(obj, 4) = S16(src, 8);
        WF32(obj, 8) = S16(src, 0xA);
        WF32(obj, 0x2C) = WF32(src, 0x20);
        WF32(obj, 0x30) = WF32(src, 0x24);
        WF32(obj, 0x34) = WF32(src, 0x28);
        W32(obj, 0x1C) = W32(src, 0xC);
        W16(obj, 0x88) = 0;
        W8(obj, 0x70) = W8(src, 0x3C) & ~8;
        W8(obj, 0x6E) = W8(src, 0x34);
        W32(obj, 0x3C) = W32(src, 0x18);
        type = W32(src, 0x14);
        if ((u32) type < 0xFFFF) {
            if (type == 0x28 || type == 0x42) {
                W8(obj, 0x70) |= 4;
                keepBit2 = 1;
            }
            W32(obj, 0x38) = D_80089030[W32(src, 0x14)][0];
            W32(obj, 0x78) = D_80089030[W32(src, 0x14)][1];
            W8(obj, 0x92) = D_80089030[W32(src, 0x14)][2];
            if (W32(src, 0x14) == 0x16) {
                hasCb = 1;
            }
        } else {
            W32(obj, 0x38) = type;
            W32(obj, 0x78) = 0;
        }
        S16(obj, 0x5A) = 0;
        S16(obj, 0x5C) = 0;
        S16(obj, 0x5E) = 0;
        W32(obj, 0x7C) = 0;
        W32(obj, 0x80) = 0;
        W32(obj, 0x84) = 0;
        W16(obj, 0x74) = 0;
        W8(obj, 0x4E) = 0;
        W16(obj, 0x6C) = 0;
        W8(obj, 0x73) = 4;
        WF32(obj, 0x60) = 0.0f;
        WF32(obj, 0x64) = 0.0f;
        WF32(obj, 0x68) = 0.0f;
        WF32(obj, 0x18) = 0.0f;
        W8(obj, 0x8A) = 0xFF;
        W8(obj, 0x8E) = 0xFF;
        W8(obj, 0x8D) = 0xFF;
        W8(obj, 0x8C) = 0xFF;
        W8(obj, 0x8B) = 0xFF;
        W8(obj, 0x71) = i;
        W32(obj, 0x94) = 0;
        W32(obj, 0x98) = 0;
        W32(obj, 0x40) = W32(src, 0x38);
        kind = W32(obj, 0x1C);
        if (kind == 0) {
            /* loaded model: share an earlier multiplayer object's model with the same key */
            id = W32(src, 0x10);
            for (j = D_800DBF00; j < i; j++) {
                s = base + j * 0x44;
                if (W32(s, 0xC) == W32(src, 0xC) && W32(s, 0x10) == id && W32(WOBJ(j), 0x1C) != 0) {
                    link = j + 1;
                    break;
                }
            }
            if (link == 0) {
                seg = (u8 *) func_1502B6BC(&found, 0, NULL, 2, 3, id);
                WPTR(obj, 0xC) = seg;
            }
            if (link != 0) {
                prev = WOBJ(link - 1);
                WPTR(obj, 0x28) = WPTR(prev, 0x28);
                W32(obj, 0x1C) = W32(prev, 0x1C);
                W32(obj, 0x9C) = W32(prev, 0x9C);
                W16(obj, 0x16) = W16(prev, 0x16);
                W32(obj, 0x44) = W32(prev, 0x44);
            } else {
                WPTR(obj, 0x28) = seg + 0x28;
                W32(obj, 0x1C) = W32(seg, 0);
                W16(obj, 0x16) = (s32) (W32(seg, 0) - (s32) (seg + 0x28)) >> 4;
                W32(obj, 0x9C) = W32(seg, 8);
                W32(obj, 0x44) = W32(seg, 0x10);
            }
            if (i >= D_800DBF00) {
                e = D_800A2A90 + id * 12;
                W8(obj, 0x4C) = e[0];
                W8(obj, 0x4D) = e[1];
                S16(obj, 0x50) = S16(e, 4);
                S16(obj, 0x52) = S16(e, 2);
                W8(obj, 0x4F) = e[8];
                W8(obj, 0x70) = e[9] & ~8;
                W16(obj, 0x6C) = W16(e, 0xA);
                if (keepBit2 != 0) {
                    W8(obj, 0x70) = (e[9] & ~8) | 4;
                }
                W16(obj, 0x90) = W16(e, 6);
                W8(obj, 0x72) = W8(src, 0x33);
            } else {
                W16(obj, 0x50) = W16(src, 0x2E);
                W16(obj, 0x52) = W16(src, 0x30);
                W8(obj, 0x4F) = W8(src, 0x32);
                W8(obj, 0x4C) = W8(src, 0x2C);
                W8(obj, 0x4D) = W8(src, 0x2D);
                W16(obj, 0x90) = W16(src, 0x40);
                if (W8(src, 0x33) != 0) {
                    W8(obj, 0x72) = W8(src, 0x33);
                } else {
                    W8(obj, 0x72) = func_15004BF0(1);
                }
            }
            if (id == 0x71) {
                W32(obj, 0x40) = 0xE;
            }
            if (W32(obj, 0x38) == 0 && hasCb == 0) {
                W8(obj, 0x6F) = 0x80;
            } else if (W8(obj, 0x6E) == 0) {
                W8(obj, 0x6F) = 0xF;
            } else {
                W8(obj, 0x6F) = 0;
            }
            W16(obj, 0x54) = id;
        } else {
            W16(obj, 0x54) = W32(src, 0x10) | 0x8000;
            if (kind == 1 || kind == 2) {
                /* level-segment model: share an earlier object's with the same key */
                for (j = 0; j < i; j++) {
                    s = base + j * 0x44;
                    if (W32(s, 0xC) == W32(src, 0xC) && W32(s, 0x10) == W32(src, 0x10) && W32(WOBJ(j), 0x1C) != 0) {
                        link = j + 1;
                        break;
                    }
                }
                if (link == 0) {
                    lseg = D_800B1260[W32(src, 0x10) * 2];
                    WPTR(obj, 0x28) = lseg + 0x28;
                    W16(obj, 0x16) = (u32) (W32(lseg, 0) - (s32) (lseg + 0x28)) >> 4;
                    W32(obj, 0x44) = W32(lseg, 0x10);
                    W32(obj, 0x9C) = W32(lseg, 8);
                } else {
                    prev = WOBJ(link - 1);
                    W16(obj, 0x16) = W16(prev, 0x16);
                    WPTR(obj, 0x28) = WPTR(prev, 0x28);
                    W32(obj, 0x44) = W32(prev, 0x44);
                    W32(obj, 0x9C) = W32(prev, 0x9C);
                }
                if (W32(obj, 0x1C) == 2) {
                    W8(obj, 0x6F) = 0;
                } else {
                    W8(obj, 0x6F) = 0x80;
                }
                if (link == 0) {
                    W32(obj, 0x1C) = W32(lseg, 0);
                } else {
                    W32(obj, 0x1C) = W32(WOBJ(link - 1), 0x1C);
                }
                W32(obj, 0xC) = 0;
                W16(obj, 0x6C) = W16(src, 0x3E);
            }
            W16(obj, 0x50) = W16(src, 0x2E);
            W16(obj, 0x52) = W16(src, 0x30);
            W8(obj, 0x4F) = W8(src, 0x32);
            W8(obj, 0x4C) = W8(src, 0x2C);
            W8(obj, 0x4D) = W8(src, 0x2D);
            W16(obj, 0x90) = W16(src, 0x40);
            if (W8(src, 0x33) != 0) {
                W8(obj, 0x72) = W8(src, 0x33);
            } else {
                W8(obj, 0x72) = func_15004BF0(1);
            }
        }
        func_15004AAC(obj, (s32) src);
        if (W32(obj, 0x38) == 0 && hasCb == 0) {
            W8(obj, 0x6F) |= 0x20;
        }
        if (link == 0) {
            func_1510D3E0((Gfx *) WPTR(obj, 0x1C), 0, 1, 0x3F, NULL);
            func_15004CE0((Gfx *) WPTR(obj, 0x1C), (s32) seg);
        }
    }

    /* vertex buffers: moving objects (+0x70 bit 0) get two private copies, the others use the model's */
    for (i = 0; i < D_800DC320; i++) {
        obj = WOBJ(i);
        if (WPTR(obj, 0x28) == NULL) {
            continue;
        }
        if ((W8(obj, 0x70) & 1) == 1) {
            WPTR(obj, 0x20) = allocate_memory(W16(obj, 0x16) << 4, 1, 2, 0);
            WPTR(obj, 0x24) = allocate_memory(W16(obj, 0x16) << 4, 1, 2, 0);
        } else {
            WPTR(obj, 0x24) = WPTR(obj, 0x28);
            WPTR(obj, 0x20) = WPTR(obj, 0x28);
        }
        if (WPTR(obj, 0x28) != WPTR(obj, 0x20)) {
            for (k = 0; k < W16(obj, 0x16); k++) {
                ((u32 *) (WPTR(obj, 0x20) + k * 0x10))[0] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[0];
                ((u32 *) (WPTR(obj, 0x20) + k * 0x10))[1] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[1];
                ((u32 *) (WPTR(obj, 0x20) + k * 0x10))[2] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[2];
                ((u32 *) (WPTR(obj, 0x20) + k * 0x10))[3] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[3];
            }
            if (WPTR(obj, 0x20) != WPTR(obj, 0x24)) {
                for (k = 0; k < W16(obj, 0x16); k++) {
                    ((u32 *) (WPTR(obj, 0x24) + k * 0x10))[0] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[0];
                    ((u32 *) (WPTR(obj, 0x24) + k * 0x10))[1] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[1];
                    ((u32 *) (WPTR(obj, 0x24) + k * 0x10))[2] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[2];
                    ((u32 *) (WPTR(obj, 0x24) + k * 0x10))[3] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[3];
                }
            }
        }
    }

    D_800DC310 = allocate_memory(D_800DC320 << 6, 1, 2, 0);
    D_800DC314 = allocate_memory(D_800DC320 << 6, 1, 2, 0);
    D_800DC328 = allocate_memory(D_800DC320 * 4, 1, 0, 0);
    D_800DC32C = allocate_memory(D_800DC320, 1, 0, 0);
    for (k = 0; k < 4; k++) {
        D_800DC300[k] = allocate_memory(D_800DC320 * 4, 1, 0, 0);
    }
    D_800DC3C4 = allocate_memory(D_800DC320 * 4, 1, 0, 0);
    for (k = 0; k < D_800DC320; k++) {
        D_800DC3C4[k] = 0;
    }
    for (k = D_800DBF00; k < D_800DC320; k++) {
        if (W8(WOBJ(k), 0x72) == 0) {
            W8(WOBJ(k), 0x72) = func_15004BF0(0);
        }
    }
}
#undef WOBJ
#undef W8
#undef W16
#undef S16
#undef W32
#undef WPTR
#undef WF32
