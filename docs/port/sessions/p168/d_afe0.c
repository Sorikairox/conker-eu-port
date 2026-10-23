s32 func_151F2CDC(void);
void func_1516D1C8(u8 *box);
extern u16 D_800BEB30[]; /* buttons pressed this frame, per player (0x8000 A, 0x4000 B) */
extern f32 D_800A7138;   /* 1 / 3: open speed */

#define TB_T(box) (*(TextAD20 **)((box) + 0x10))
#define TB_S16(box, o) (*(s16 *)((box) + (o)))
#define TB_F32(box, o) (*(f32 *)((box) + (o)))

// text_box_update: per-frame update of a text box (D_8008B848 kind 0x51, record of func_1516AD20). Closes the box at
// once when the descriptor's +0x2B is set and D_800C35EA is not 1. +0x15 is the state: 1 open (style 2: the 3-dot
// "more" variant, starts at 8), 2 grow (+0x28 scale up by +0x2C per frame, line fades in after 0.75), 4 wait
// (45 per frame from 180), 8 the dots fade in one by one, 0x10 line fade-in, 0x20 shown (waits for A / B, the
// "no B" / "last line" / timed flags of the descriptor, or a +0x100 request), 0x40 line fade-out then the next line
// or 0x80, 0x80 shrink and close (callback with 0x1000, player's record flag cleared, box freed). Descriptor flag
// 0x400 skips the timed steps. The callback gets (descriptor, line, state) with 0x2000 (next line) / 0x4000 (shown)
// / 0x1000 (closed) set in the flags meanwhile. Always ends with func_1516D1C8 (screen position).
void func_1516AFE0(u8 *box) {
    TextAD20 *t;
    u8 *pl;
    s32 skip;
    s32 w;
    s32 h;
    s32 unused;
    s32 flags;
    u16 pad;

    t = TB_T(box);
    pl = (u8 *) D_800DBFF0;
    skip = t->flags & 0x400;
    if (((u8 *) t)[0x2B] != 0 && D_800C35EA != 1) {
        ((u8 *) t)[8] = 0;
        func_1516972C((struct102 *) box);
        return;
    }
    TB_F32(box, 0x40) = TB_F32(box, 0x5C);
    TB_F32(box, 0x44) = TB_F32(box, 0x60);
    switch (box[0x15]) {
    case 1:
        TB_S16(box, 0x16) = 0;
        TB_S16(box, 0x18) = 0;
        TB_F32(box, 0x2C) = skip ? 1.0f : D_800A7138;
        if (TB_T(box)->flags & 2) {
            box[0x1D] = 0;
            box[0x1C] = 0;
            box[0x1B] = 0;
            box[0x1E] = 2;
            TB_S16(box, 0x16) = 4;
            TB_S16(box, 0x18) = 10;
            box[0x15] = 8;
            TB_F32(box, 0x28) = 1.0f;
            func_1516D1C8(box);
            box[0xE] = 1;
            TB_F32(box, 0x70) = TB_F32(box, 0x5C);
        } else {
            box[0x15] = 2;
        }
        TB_F32(box, 0x30) = 1.0f;
        TB_F32(box, 0x34) = 1.0f;
        box[0x1A] = 0;
        break;
    case 2:
        func_15042BC4(*(u8 **) (box + 0x24), &w, &h, &unused);
        TB_F32(box, 0x30) = w >> 1;
        TB_F32(box, 0x34) = h >> 1;
        TB_F32(box, 0x28) = TB_F32(box, 0x28) + TB_F32(box, 0x2C) * D_800BE9A4;
        if (skip) {
            TB_S16(box, 0x18) = 0;
        }
        if (0.75f < TB_F32(box, 0x28) && TB_S16(box, 0x18) == 0) {
            TB_S16(box, 0x18) = 10;
        }
        if (TB_S16(box, 0x18) != 0) {
            TB_S16(box, 0x18) -= D_800BE9A0;
            if (TB_S16(box, 0x18) < 0) {
                TB_S16(box, 0x18) = 0;
            }
            box[0x1A] = (u32) ((10.0f - TB_S16(box, 0x18)) / 10.0f * 255.0f);
        }
        if (1.0f < TB_F32(box, 0x28)) {
            TB_F32(box, 0x28) = 1.0f;
            box[0x15] = 4;
            TB_S16(box, 0x16) = 180;
        }
        box[0xE] = 1;
        break;
    case 4:
        if (skip) {
            TB_S16(box, 0x16) = 0;
        }
        TB_S16(box, 0x16) -= D_800BE9A0 * 45;
        if (TB_S16(box, 0x16) < 0) {
            TB_S16(box, 0x16) = 0;
        }
        TB_S16(box, 0x18) -= D_800BE9A0;
        if (TB_S16(box, 0x18) < 0) {
            TB_S16(box, 0x18) = 0;
        }
        box[0x1A] = (u32) ((10.0f - TB_S16(box, 0x18)) / 10.0f * 255.0f);
        if (TB_S16(box, 0x16) == 0) {
            box[0x15] = 0x10;
        }
        break;
    case 8:
        TB_S16(box, 0x16) -= D_800BE9A0;
        if (TB_S16(box, 0x16) < 0) {
            TB_S16(box, 0x16) = 0;
        }
        box[0x1B + box[0x1E]] = (u32) ((4.0f - TB_S16(box, 0x16)) / 4.0f * 170.0f);
        if (TB_S16(box, 0x16) == 0) {
            box[0x1E]--;
            if (box[0x1E] < 101) {
                TB_S16(box, 0x16) = 4;
            } else {
                box[0x15] = 0x10;
                TB_S16(box, 0x18) = 10;
            }
        }
        break;
    case 0x40:
        TB_S16(box, 0x16) -= D_800BE9A0;
        if (TB_S16(box, 0x16) < 0) {
            TB_S16(box, 0x16) = 0;
        }
        if (skip) {
            TB_S16(box, 0x16) = 0;
        }
        box[0x1A] = (u32) (TB_S16(box, 0x16) / 10.0f * 255.0f);
        if (TB_S16(box, 0x16) == 0) {
            ((s8 *) box)[0x20]++;
            if (((s8 *) box)[0x20] < TB_T(box)->lines) {
                *(u8 **) (box + 0x24) = func_1516CDE8((s32 *) TB_T(box), ((s8 *) box)[0x20], box[0xD]);
                TB_S16(box, 0x18) = 10;
                box[0x15] = 0x10;
                TB_T(box)->flags |= 0x2000;
                if (TB_T(box)->callback != NULL) {
                    TB_T(box)->callback((s32) TB_T(box), ((s8 *) box)[0x20] - 1, box[0x15]);
                }
                TB_T(box)->flags &= ~0x2000;
            } else {
                TB_S16(box, 0x18) = 5;
                box[0x15] = 0x80;
                TB_F32(box, 0x28) = 1.0f;
                TB_F32(box, 0x2C) = 0.25f;
            }
        }
        if (!skip) {
            break;
        }
        /* fallthrough: skipping goes on with the line fade-in */
    case 0x10:
        func_15042BC4(*(u8 **) (box + 0x24), &w, &h, &unused);
        TB_F32(box, 0x30) = w >> 1;
        TB_F32(box, 0x34) = h >> 1;
        TB_S16(box, 0x18) -= D_800BE9A0;
        if (TB_S16(box, 0x18) < 0) {
            TB_S16(box, 0x18) = 0;
        }
        if (skip) {
            TB_S16(box, 0x18) = 0;
        }
        box[0x1A] = (u32) ((10.0f - TB_S16(box, 0x18)) / 10.0f * 255.0f);
        if (TB_S16(box, 0x18) == 0) {
            box[0x15] = 0x20;
            TB_S16(box, 0x16) = TB_T(box)->width;
            TB_T(box)->flags |= 0x4000;
        }
        if (!skip) {
            break;
        }
        /* fallthrough */
    case 0x20:
        skip = 0;
        if (TB_T(box)->flags & 0x4000) {
            if (TB_T(box)->callback != NULL) {
                TB_T(box)->callback((s32) TB_T(box), ((s8 *) box)[0x20], box[0x15]);
            }
            TB_T(box)->flags &= ~0x4000;
        }
        TB_S16(box, 0x16) -= D_800BE9A0;
        if (TB_S16(box, 0x16) < 0) {
            TB_S16(box, 0x16) = 0;
        }
        flags = TB_T(box)->flags;
        if ((flags & 0x10) && box[0x14] == 0) {
            if (flags & 0x20) {
                if (func_151F2CDC() != 0) {
                    goto request;
                }
                flags = TB_T(box)->flags;
            }
            if ((flags & 0x80) && TB_T(box)->lines == ((s8 *) box)[0x20] + 1) {
                pad = D_800BEB30[0];
                if (pad & 0x4000) {
                    box[0x20] = -1;
                    skip = 1;
                    D_800D1994 = 0;
                } else if (pad & 0x8000) {
                    skip = 1;
                }
            } else {
                pad = D_800BEB30[0];
                if (pad & 0x8000) {
                    skip = 1;
                } else if (!(flags & 0x40) && (pad & 0x4000)) {
                    box[0x20] = TB_T(box)->lines;
                    skip = 1;
                }
            }
        }
    request:
        flags = TB_T(box)->flags;
        if (flags & 0x100) {
            TB_T(box)->flags = flags & ~0x100;
            skip = 1;
            flags = TB_T(box)->flags;
        }
        if (!(flags & 0x200) && skip) {
            TB_S16(box, 0x16) = 10;
            box[0x15] = 0x40;
        }
        break;
    case 0x80:
        if (TB_T(box)->flags & 2) {
            TB_S16(box, 0x18) -= D_800BE9A0;
            if (TB_S16(box, 0x18) < 0) {
                TB_S16(box, 0x18) = 0;
            }
            box[0x1B] = box[0x1C] = box[0x1D] = (u32) (TB_S16(box, 0x18) / 5.0f * 85.0f);
        } else {
            TB_F32(box, 0x28) = TB_F32(box, 0x28) - TB_F32(box, 0x2C) * D_800BE9A4;
        }
        if (TB_F32(box, 0x28) < 0.0f || TB_S16(box, 0x18) == 0) {
            TB_F32(box, 0x28) = 0.0f;
            box[0x15] = 0;
            box[0x20] = 0;
            TB_T(box)->flags |= 0x1000;
            if (TB_T(box)->callback != NULL) {
                TB_T(box)->callback((s32) TB_T(box), ((s8 *) box)[0x20], box[0x15]);
            }
            TB_T(box)->flags &= ~0x1000;
            D_800CC8D3[TB_T(box)->player * 0x32C] = 0;
            *(s16 *) (pl + 0x6CC) = 0;
            ((u8 *) TB_T(box))[8] = 0;
            func_1516972C((struct102 *) box); /* the box is freed; func_1516D1C8 below still runs on it, as on N64 */
        }
        break;
    }
    func_1516D1C8(box);
}
