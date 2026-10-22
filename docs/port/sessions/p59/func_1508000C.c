void func_1000D96C(s32, s32, s32);
void func_1000DE1C(s32, s32);
void func_1000E7A0(u32, s32);
void func_1000E8C4(s32);
void func_100109D0(struct127 *arg0);
extern u8 *D_80086F40[];
extern u8 D_8009BC80[][8];
extern s32 D_80041C50[];
extern u8 D_80041D40;
extern s32 D_800D1CE4;

/* Per-frame surface effects of the record's current floor material (ctl = rec->unk31C + 0x58: +4 material set,
 * +5 index, +6 the flags applied last frame). Flags (D_8009BC80[mat][6]): 0x10 scales the model's +0x08 by the
 * D_80041C50 level, and on change 1 = record flag unk2F8 bit 0, 2 = func_1000E7A0 / func_1000E8C4, 4 = ambient
 * loop 0x15 / 0x16 (D_800D1CE4) start / stop, 8 cleared = func_100109D0. */
void func_1508000C(struct127 *rec) {
    u8 *ctl = (u8 *)rec->unk31C + 0x58;
    u8 set = ctl[4];
    u8 flags = 0;
    u8 old;
    u8 changed, gained, lost;
    f32 k;

    if (set != 0) {
        flags = D_8009BC80[D_80086F40[set][ctl[5]]][6];
    }
    if (flags & 0x10) {
        k = ((f32)D_80041C50[D_80041D40 * 16] - 5462.0f) * 1.2f;
        if (k < 0.0f) {
            k = 0.0f;
        }
        rec->unk2D0->unk8 = ((rec->unk2D0->unk18 - 1.0f) * (32768.0f - k)) / 32768.0f;
    }
    old = ctl[6];
    if (flags == old) {
        return;
    }
    changed = flags ^ old;
    gained = changed & flags;
    lost = changed & old;
    if (gained & 1) {
        rec->unk2F8 |= 1;
    } else if (lost & 1) {
        rec->unk2F8 &= ~1;
    }
    if (gained & 2) {
        func_1000E7A0(1, 0);
    } else if (lost & 2) {
        func_1000E8C4(1);
    }
    if (gained & 4) {
        if (D_800D1CE4 == 0) {
            D_800D1CE4 = 0x15;
        } else if (D_800D1CE4++ == 0x17) { /* 0x15 -> 0x16 -> 0x17 -> 0x15 */
            D_800D1CE4 = 0x15;
        }
        func_1000D96C(D_800D1CE4, 0, 0);
    } else if (lost & 4) {
        func_1000DE1C(D_800D1CE4, 0);
    }
    if (lost & 8) {
        func_100109D0(rec);
    }
    ctl[6] = flags;
}
