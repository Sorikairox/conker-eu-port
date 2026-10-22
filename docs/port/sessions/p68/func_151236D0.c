/* Per-frame state flags of a struct108 controller (camera / player view), word unk5F0:
 *   0x40  the followed object (unk3D4) is "active": +0x9C set, or +0x95 set while unk3D0 +0x137 is clear
 *   0x400 cleared when unk3D0's unk28 is 0
 *   0x08  unk3D4 +0x08 (s16) non-zero and +0x16 clear
 *   0x80  unk3D4 +0x4E == 2
 *   0x01  "inside": the f32 at +0x360 >= unk2FC, except in mode unk2C == 0x100
 * Then the 0x01 flag (old value vs new value) picks one of the func_1515BFxx calls on channel unk23D.
 * The asm leaves v0 undefined on return and every caller ignores it: void under NM. */
#define F108_F32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define OBJ_U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
void func_151236D0(struct108 *arg0) {
    u8 *obj = (u8 *)arg0->unk3D4;
    s32 wasInside = arg0->unk5F0 & 1;

    if (obj != NULL) {
        if (*(u32 *)(obj + 0x9C) != 0 || (OBJ_U8(obj, 0x95) != 0 && OBJ_U8(arg0->unk3D0, 0x137) == 0)) {
            arg0->unk5F0 |= 0x40;
        } else {
            arg0->unk5F0 &= ~0x40;
        }
        if (arg0->unk3D0->unk28 == 0.0f) {
            arg0->unk5F0 &= ~0x400;
        }
        obj = (u8 *)arg0->unk3D4;
        if (*(s16 *)(obj + 0x8) != 0 && OBJ_U8(obj, 0x16) == 0) {
            arg0->unk5F0 |= 8;
        } else {
            arg0->unk5F0 &= ~8;
        }
        if (OBJ_U8(arg0->unk3D4, 0x4E) == 2) {
            arg0->unk5F0 |= 0x80;
        } else {
            arg0->unk5F0 &= ~0x80;
        }
    }
    if (arg0->unk2FC <= F108_F32(arg0, 0x360) && arg0->unk2C != 0x100) {
        arg0->unk5F0 |= 1;
    } else {
        arg0->unk5F0 &= ~1;
    }

    if (arg0->unk23C != 0) {
        if (arg0->unk5F0 & 1) {
            func_1515BFF0(arg0->unk23D);
        } else {
            func_1515BFB8(arg0->unk23D);
            F108_F32(arg0, 0x7B0) = 0.0f;
        }
        return;
    }
    if (!wasInside && (arg0->unk5F0 & 1)) {
        /* just entered */
        if ((arg0->unk5F0 & 4) || (arg0->unk2C & 0x40000)) {
            func_1515BFF0(arg0->unk23D);
        } else {
            func_1515C01C(arg0->unk23D);
        }
    } else if (wasInside && !(arg0->unk5F0 & 1)) {
        /* just left */
        if ((arg0->unk5F0 & 4) || (arg0->unk2C & 0x40000)) {
            func_1515BFB8(arg0->unk23D);
            F108_F32(arg0, 0x7B0) = 0.0f;
        } else {
            func_1515BFC4(arg0->unk23D);
            func_15124B18(arg0);
        }
    } else if (arg0->unk5F0 & 1) {
        func_1515BF8C(arg0->unk23D);
    } else {
        func_1515BF80(arg0->unk23D);
    }
}
