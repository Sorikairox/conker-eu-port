/* P222: readable C for func_15063AA0 (game_eu_90F50, 179 words; jump table jtbl_80099A98 = EU 0x80099A98). */
void func_1506435C(u8 *arg0, s32 arg1);
void func_151D5DA8(struct127 *obj, u8 which);
s32 func_15082278(u8 *obj, u8 *hit, s32 kind);
s32 func_10010894(struct127 *arg0);
void func_10010558(u16, struct127 *, s32, s32, s32, s32);
void func_1512D854(s32, s32);
void func_15100248(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_15100304(f32 *pos, f32 *dir, u8 flag, s32 arg3);

// object_pending_actions_run: once per frame (game_45B80) for every live object with a controller (+0x31C) whose
// pending-action byte ctl +0x1B4 is set: makes it the current object (D_800C3E78 = slot, D_800D154C = obj) and runs
// bit 0: func_150639D8(obj, 0), bit 2 / bit 3: func_151D5DA8(obj, 0 / 1), bit 1: the action of the controller's item
// kind ctl +0x78 (bit 7 ignored): 0x14 / 0x3F / 0x18 / 0x41 hit reactions (func_1506435C 2 / 0x12 / 6, counter
// ctl +0x1AA, pad rumble), 0x24 the hit record ctl +0xB0 as kind 7 (with a pain voice 0x53B..0x53D unless the
// record says 2 or ctl +0xAF is clear), 0x3B kind 0x10 plus the muzzle sparks (func_15100248 / func_15100304),
// 0x23 kind 8 (rumble off). Then clears ctl +0x1B4. D_800CC2B0 is cleared first.
void func_15063AA0(void) {
    struct127 *obj;
    u8 *ctl;
    u8 kind;
    f32 pos[3];
    f32 dir[3];
    f32 v50[3];
    f32 v44[3];
    s32 i;

    D_800CC2B0 = 0;
    for (i = 0, obj = D_800CC2D0; i < 25; i++, obj++) {
        if (obj->interaction_state == 0 || (ctl = *(u8 **) ((u8 *) obj + 0x31C)) == NULL || ctl[0x1B4] == 0) {
            continue;
        }
        D_800C3E78 = i;
        D_800D154C = obj;
        if (ctl[0x1B4] & 1) {
            func_150639D8((u8 *) obj, 0.0f);
        }
        if ((*(u8 **) ((u8 *) obj + 0x31C))[0x1B4] & 4) {
            func_151D5DA8(obj, 0);
        }
        if ((*(u8 **) ((u8 *) obj + 0x31C))[0x1B4] & 8) {
            func_151D5DA8(obj, 1);
        }
        ctl = *(u8 **) ((u8 *) obj + 0x31C);
        if (ctl[0x1B4] & 2) {
            kind = ctl[0x78] & ~0x80;
            switch (kind) {
            case 0x18:
            case 0x41:
                func_1506435C((u8 *) obj, 6);
                (*(s16 *) ((*(u8 **) ((u8 *) obj + 0x31C)) + 0x1AA))++;
                if (*(s32 *) ((u8 *) obj + 0x318) != 0) {
                    func_1512D854(*(s32 *) ((u8 *) obj + 0x318), 1);
                }
                break;
            case 0x14:
            case 0x3F:
                func_1506435C((u8 *) obj, kind == 0x14 ? 2 : 0x12);
                (*(s16 *) ((*(u8 **) ((u8 *) obj + 0x31C)) + 0x1AA))++;
                if (*(s32 *) ((u8 *) obj + 0x318) != 0) {
                    func_1512D854(*(s32 *) ((u8 *) obj + 0x318), 1);
                }
                break;
            case 0x24:
                if (func_15082278((u8 *) obj, ctl + 0xB0, 7) != 2) {
                    ctl = *(u8 **) ((u8 *) obj + 0x31C);
                    if (ctl[0xAF] != 0) {
                        ctl[0xAF] = 0;
                        if (func_10010894(obj) == 0) {
                            func_10010558((u32) func_150ADA20() % 3 + 0x53B, obj, 0x7D00, 0x320, 0xBB8, 0x19);
                        }
                    }
                }
                if (*(s32 *) ((u8 *) obj + 0x318) != 0) {
                    func_1512D854(*(s32 *) ((u8 *) obj + 0x318), 1);
                }
                break;
            case 0x3B:
                func_15082278((u8 *) obj, ctl + 0xB0, 0x10);
                func_15100248((s32) obj, (s32) pos, (s32) dir, (s32) v50, (s32) v44);
                func_15100304(pos, dir, 0xFF, 1);
                break;
            case 0x23:
                func_15082278((u8 *) obj, ctl + 0xB0, 8);
                if (*(s32 *) ((u8 *) obj + 0x318) != 0) {
                    func_1512D854(*(s32 *) ((u8 *) obj + 0x318), 0);
                }
                break;
            }
        }
        (*(u8 **) ((u8 *) obj + 0x31C))[0x1B4] = 0;
    }
}
