void func_15037CCC(f32 *, s32, s32, s32, f32, s32, s32);
void func_15038910(s32, s32, f32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_800C441A;
extern f32 D_800C4408[3];

/*
 * P65: per-frame callback of the current object D_800CC2D0[D_800C3E78] (called twice per frame for Conker).
 * D_800C441A counts the calls of this frame: the first call of a frame is skipped (only sets the counter to 1) for
 * object ids 0x3B / 0x75 / 0x80 / ... (jump table jtbl_80098604, a .late_rodata table: not code), when D_800C35EA == 1,
 * or when the record +0x324 still holds the -99999 "unset" x. Otherwise point D_800C4408 is filled by func_15037CCC
 * (or set to -99999 on a first call without D_800D154C->unk2F8 & 0x100) and passed to func_15038910.
 */
void func_15036FD8(void) {
    struct127 *obj = &D_800CC2D0[D_800C3E78];
    u8 *rec = obj->unk324;
    s32 kind;
    s32 first;
    s32 later;

    if (rec == NULL) {
        return;
    }
    switch (obj->id) {
        case 0x3B:
        case 0x75: case 0x80: case 0x88: case 0x90: case 0x96: case 0x98: case 0x9C:
        case 0x9D: case 0x9F: case 0xA0: case 0xB0: case 0xB1: case 0xB2: case 0xB4:
            if (D_800C441A == 0) {
                D_800C441A = 1;
                return;
            }
            break;
    }
    if (D_800C35EA == 1 && D_800C441A == 0) {
        D_800C441A = 1;
        return;
    }

    first = FALSE;
    later = TRUE;
    if (D_800C441A == 0) {
        kind = 7;
        first = TRUE;
        later = FALSE;
        if (D_800D154C->unk2F8 & 0x100) {
            *(s16 *)(rec + 0x3A) = 0x2D;
            *(s16 *)(rec + 0x40) = 0x40;
        } else if (*(f32 *)rec == -99999.0f) {
            D_800C441A = 1;
            return;
        }
    } else {
        kind = 12;
    }

    if (D_800C441A == 0 && !(D_800D154C->unk2F8 & 0x100)) {
        D_800C4408[0] = -99999.0f;
        D_800C4408[1] = -99999.0f;
        
    } else {
        func_15037CCC(D_800C4408, kind, 0, D_800C3E78, 90.0f, 0xFF, 0);
    }
    func_15038910(kind, 0, D_800C4408, D_800C3E78, first, 0, D_800C441A, 3, 0, 0, 0, later, 0);
    D_800C441A++;
}
