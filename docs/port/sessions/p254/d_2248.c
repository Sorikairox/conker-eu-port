#ifdef NON_MATCHING
// trail_ribbon_draw: entry 18 of D_8008A644 (`s32 (u8 *, s32 dl, s16 slot)`, dispatcher func_151481BC: returns the
// advanced display list). Draws a path as a textured ribbon: needs 2+ points (+0x2C); gets the slot's vertex buffer
// (func_151D6310 on +0x84, (+0x25 * 32 + 0xA0) bytes; returns `dl` unchanged without one), sets up texture 0xBC of
// D_80090F10, render mode and combine 0x4C. Then from the point before the head +0x2E back to the current point
// +0x2D (ring of +0x25 points of 0x28 bytes at +0x94: xyz, +0x14 alpha, +0x18 texture t, +0x1C half width,
// +0x20 / +0x24 side direction) it emits two vertices per point (+/- side * width, alpha scaled by the owner's
// +0x08) and one quad (4-vertex load + 2 triangles) per segment. When t grows along a segment, the last pair is
// duplicated and the earlier copy's t lowered by 0x2000 (texture wrap). Returns the new display-list end.
s32 func_151D2248(u8 *arg0, s32 dl, s16 slot) {
    u8 *owner;
    u8 *points;
    u8 *p;
    s16 *vtx;
    u32 *gfx;
    s8 flag;
    f32 a[3];
    f32 b[3];
    f32 ax;
    f32 az;
    f32 bx;
    f32 bz;
    f32 ta;
    f32 tb;
    s32 cur;
    s32 next;
    s32 ti;
    u8 alpha_a;
    u8 alpha_b;

    if (*(s8 *) (arg0 + 0x2C) < 2) {
        return dl;
    }
    owner = *(u8 **) (arg0 + 0x98);
    points = *(u8 **) (arg0 + 0x94);
    func_151D6310((s32 *) (arg0 + 0x84), slot, (arg0[0x25] << 5) + 0xA0, (s32 *) &vtx, NULL);
    if (vtx == NULL) {
        return dl;
    }
    flag = 1;
    gfx = (u32 *) func_15142FBC(
        func_1513F4E4(func_15142B7C(func_15142E24((u8 *) dl, &D_80090F10[0xBC], 0, 0, 0, 0, 0xBC, 0, 0, &flag, 3),
                                    0x220005, 0x1D0600),
                      0x4C, &flag),
        D_800D30BC | 0x80000 | 0x2CA0, *(s32 *) (D_800A4EA8 + 0xC) | *(s32 *) (D_800A4EA8 + 8), &flag);

    cur = *(s8 *) (arg0 + 0x2E) - 1;
    if (cur < 0) {
        cur = arg0[0x25] - 1;
    }
    next = cur - 1;
    if (next < 0) {
        next = arg0[0x25] - 1;
    }
    p = points + cur * 0x28;
    a[0] = ((f32 *) p)[0];
    a[1] = ((f32 *) p)[1];
    a[2] = ((f32 *) p)[2];
    alpha_a = (p[0x14] * owner[8]) >> 8;
    ax = *(f32 *) (p + 0x20) * *(f32 *) (p + 0x1C);
    az = *(f32 *) (p + 0x24) * *(f32 *) (p + 0x1C);
    ta = *(f32 *) (p + 0x18);
    p = points + next * 0x28;
    b[0] = ((f32 *) p)[0];
    b[1] = ((f32 *) p)[1];
    b[2] = ((f32 *) p)[2];
    bx = *(f32 *) (p + 0x20) * *(f32 *) (p + 0x1C);
    bz = *(f32 *) (p + 0x24) * *(f32 *) (p + 0x1C);
    tb = *(f32 *) (p + 0x18);
    alpha_b = (p[0x14] * owner[8]) >> 8;

    ti = (s32) ta;
    vtx[0] = (s32) (a[0] + ax);
    vtx[1] = (s32) a[1];
    vtx[2] = (s32) (a[2] + az);
    ((u8 *) vtx)[0xF] = alpha_a;
    vtx[5] = ti;
    vtx[4] = 0x7FF;
    vtx[3] = 0;
    vtx += 8;
    vtx[0] = (s32) (a[0] - ax);
    vtx[1] = (s32) a[1];
    vtx[2] = (s32) (a[2] - az);
    ((u8 *) vtx)[0xF] = alpha_a;
    vtx[5] = ti;
    vtx[4] = 0;
    vtx[3] = 0;
    vtx += 8;
    for (;;) {
        ti = (s32) tb;
        vtx[0] = (s32) (b[0] + bx);
        vtx[1] = (s32) b[1];
        vtx[2] = (s32) (b[2] + bz);
        ((u8 *) vtx)[0xF] = alpha_b;
        vtx[5] = ti;
        vtx[4] = 0x7FF;
        vtx[3] = 0;
        vtx += 8;
        vtx[0] = (s32) (b[0] - bx);
        vtx[1] = (s32) b[1];
        vtx[2] = (s32) (b[2] - bz);
        ((u8 *) vtx)[0xF] = alpha_b;
        vtx[5] = ti;
        vtx[4] = 0;
        vtx[3] = 0;
        vtx += 8;
        gfx[0] = 0x01004008; /* gSPVertex(vtx - 4, 4, 0) */
        gfx[1] = (u32) (vtx - 0x20);
        gfx += 2;
        gfx[0] = 0x06000204; /* gSP2Triangles(0, 1, 2, 2, 3, 1) */
        gfx[1] = 0x00020604;
        gfx += 2;
        if (ta < tb) {
            memcpy(vtx, vtx - 0x10, 0x20);
            (vtx - 0x10)[5] -= 0x2000;
            vtx += 8;
            (vtx - 0x10)[5] -= 0x2000;
            vtx += 8;
        }
        cur = next;
        next--;
        if (next < 0) {
            next = arg0[0x25] - 1;
        }
        if (cur == *(s8 *) (arg0 + 0x2D)) {
            break;
        }
        p = points + next * 0x28;
        b[0] = ((f32 *) p)[0];
        b[1] = ((f32 *) p)[1];
        b[2] = ((f32 *) p)[2];
        bx = *(f32 *) (p + 0x20) * *(f32 *) (p + 0x1C);
        bz = *(f32 *) (p + 0x24) * *(f32 *) (p + 0x1C);
        ta = *(f32 *) (points + cur * 0x28 + 0x18);
        tb = *(f32 *) (p + 0x18);
        alpha_b = (p[0x14] * owner[8]) >> 8;
    }
    return (s32) gfx;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D2248.s")
#endif
