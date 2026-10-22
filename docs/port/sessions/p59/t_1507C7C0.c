//DROP s32 func_1507C7C0(struct127 *, u16 *, u16 *, u16 *);
//HOIST void func_1507C7C0(struct127 *, u16 *, u16 *, u16 *);
extern u8 D_800B89C4[];
extern f32 D_8009BA58;

/* Collision cylinder of a record: *height (h), *width (w) and *radius (r), each optional, as s16. By state
 * (+0): 0 = 60 / 180, 0x2D (camera-driven) the camera's +0x95C / +0x960, 4 = 3 x unkE4 / 6 x unkE6, 0x2C = 80 / 160;
 * models of kind 5 (+5) unkE4 / 2 x unkE6. Otherwise by id: the players (0-4, 0x3B, 0x75, ...) 60 / 180 with
 * ledge, water and controller variants; a few fixed sizes; anything else unkE4 / 2 x unkE6 unscaled. Records held
 * by a record of id 0x13 (unk13C = 100 + index) are bigger, and the sized kinds scale by unk14C / unk150.
 * The result is not used by any caller (the asm leaves a scratch value in v0); 0 here. */
void func_1507C7C0(struct127 *rec, u16 *height, u16 *width, u16 *radius) {
    u8 *c;
    u8 *cam;
    s32 scaled = 1;
    s32 state = rec->interaction_state;
    f32 h, w, r;
    u8 holder;

    if (state == 0) {
        r = w = 60.0f;
        h = 180.0f;
        goto out;
    }
    if (state == 0x2D) {
        cam = (u8 *)rec->camera;
        h = *(f32 *)(cam + 0x960);
        r = w = *(f32 *)(cam + 0x95C);
        goto out;
    }
    if (state == 4) {
        h = rec->unkE6 * 6.0f;
        r = w = rec->unkE4 * 3.0f;
        goto out;
    }
    if (state == 0x2C) {
        r = w = 80.0f;
        h = 160.0f;
        goto out;
    }
    if (rec->unk5 == 5) {
        r = w = rec->unkE4;
        h = 2.0f * rec->unkE6;
        goto out;
    }
    switch (rec->id) {
    case 0: case 1: case 2: case 3: case 4: case 0x3B:
    case 0x75: case 0x80: case 0x82: case 0x88: case 0x90: case 0x96: case 0x98: case 0x9C:
    case 0x9D: case 0x9F: case 0xA0: case 0xB0: case 0xB1: case 0xB2: case 0xB4:
        c = (u8 *)rec->unk31C;
        if (c != NULL && *(s32 *)(c + 4) != 0) {
            r = w = 60.0f;
            h = 80.0f;
        } else if (c != NULL && c[0x17] != 0) {
            r = w = 70.0f;
            h = 300.0f;
        } else if (rec->in_water != 0) {
            h = 180.0f;
            r = w = 90.0f;
        } else {
            r = w = 60.0f;
            h = 180.0f;
            if (c != NULL) {
                cam = (u8 *)rec->camera;
                if ((cam != NULL && *(s16 *)(cam + 0x73C) != 0) || c[0x197] != 0 || c[0x1B3] != 0) {
                    r = w = 120.0f;
                }
                h = 180.0f + *(u16 *)(c + 0x1A6);
            }
        }
        if (c != NULL && (c[0x4E] & 0xF) == 1 && c[0x4F] == 0 && *(f32 *)((u8 *)rec + 0x3C) < 40.0f) {
            r = w = 110.0f;
            h = 500.0f;
        }
        break;
    case 0x25: case 0x2E:
        h = 70.0f;
        r = w = 90.0f;
        break;
    case 0x36:
        h = D_8009BA58; /* 257 */
        r = w = 90.0f;
        break;
    case 0x9A:
        h = 60.0f;
        r = w = 45.0f;
        scaled = 0;
        break;
    case 0xAC:
        r = w = 30.0f;
        h = 90.0f;
        scaled = 0;
        break;
    case 0x89: case 0xBA:
        h = 60.0f;
        r = w = 30.0f;
        scaled = 0;
        break;
    case 0x53:
        if (D_800BE616 != 0) {
            r = w = 150.0f;
            h = 300.0f;
        } else {
            h = 250.0f;
            r = w = 90.0f;
        }
        break;
    default:
        scaled = 0;
        h = 2.0f * rec->unkE6;
        r = w = rec->unkE4;
        break;
    }
    holder = rec->unk13C;
    /* D_800B89C4[n * 0x32C] is D_800CC2D0[n - 100].id */
    if (holder > 100 && D_800B89C4[holder * 0x32C] == 0x13) {
        r += 120.0f * *(f32 *)((u8 *)rec + 0x14C);
        h += 100.0f * *(f32 *)((u8 *)rec + 0x150);
    }
    if (scaled) {
        h *= *(f32 *)((u8 *)rec + 0x150);
        w *= *(f32 *)((u8 *)rec + 0x14C);
        r *= *(f32 *)((u8 *)rec + 0x14C);
    }
out:
    if (height != NULL) {
        *height = (s16)h;
    }
    if (width != NULL) {
        *width = (s16)w;
    }
    if (radius != NULL) {
        *radius = (s16)r;
    }

}
