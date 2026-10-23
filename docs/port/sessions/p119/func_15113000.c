extern u8 D_800C3A7C;
extern f32 D_800D9F3C;   /* default draw distance of the world records */
extern u8 D_800DA030[];  /* per player: 0x40-byte view matrix for func_150A6840 */
extern s32 D_800895E0[]; /* per player: pointer to the visible-list pointer (entries: s16 record index, s16 depth) */
extern u16 D_800DC318[]; /* per player: visible-list length */
s32 func_150859AC(s16 player, s32 field);
s32 func_15022BB0(s32, s32);
s32 func_1503FAF0(u8 *, s16, s16, s32, s32);
s32 func_150A6840(s32 cam, s32 *mtx, f32 x, f32 y, f32 z, f32 r, f32 ry, f32 far);

/* world_records_build_visible: per frame (func_15019130 path, view arg0), for every active player view
 * (func_150859AC(player, 0)) rebuilds the list of visible world-object records (0xA0 bytes, D_800DBEF4[0 ..
 * D_800DC320 - 1]). Records come in groups: a record's +0x70 >> 4 is the number of records following it in the group.
 * For each record the player's bit in +0x6F is cleared; a record takes part unless it is kind 1 (+0x6E), hidden
 * (+0x70 & 8), disabled (!(+0x4F & 1)) or has no model (+0x8A == 0). In mode D_800C35EA[view] == 1, func_15022BB0
 * decides (without D_800C3A7C[view] a refusal skips the record; an acceptance skips the occlusion test below), else
 * records with +0x6C & 0x100 are skipped when func_1503FAF0(+0x98, x, z, player, 0) says they are hidden.
 * func_150A6840 then gives the (absolute) view depth against the far distance (+0x90: 0 = D_800D9F3C, 1 = 40000,
 * D_800D9F3C when the player's object has +0x197 set) and the per-player fade byte +0x8B + player is updated:
 * depth 0 or beyond far: 0 (not visible); within 200 of far: (far - depth) * 255 / 200; nearer: with a near
 * distance +0x88, fades out by D_800BE9E4 * 10 per frame below it and in above it (0 = not visible), without one 0xFF.
 * If any record of a group is visible, every record of the group gets the player's +0x6F bit and an entry
 * (index, depth) in the player's list D_800895E0[player] (length D_800DC318[player]). */
void func_15113000(s32 view) {
    s32 depth[16];
    s32 player;
    s32 cam;
    s32 first;
    s32 last;
    s32 visible;
    s32 bit;
    s32 far;
    s32 step;
    s32 i;
    u8 *rec;
    u8 *mode;
    u8 *alpha;
    u8 *entry;

    for (player = 0; player <= D_80082FA0; player++) {
        cam = D_800BE628 + player * 0x180;
        if (func_150859AC((s16) player, 0) == 0) {
            continue;
        }
        D_800DC318[player] = 0;
        i = 0;
        while (i < D_800DC320) {
            visible = 0;
            first = i;
            last = i + (((u8 *) D_800DBEF4 + i * 0xA0)[0x70] >> 4);
            bit = 1 << player;
            for (; i <= last; i++) {
                rec = (u8 *) D_800DBEF4 + i * 0xA0;
                rec[0x6F] &= ~bit;
                if (rec[0x6E] == 1 || (rec[0x70] & 8) || !(rec[0x4F] & 1) || rec[0x8A] == 0) {
                    continue;
                }
                mode = &D_800C35EA + view;
                if ((&D_800C3A7C)[view] == 0 && *mode == 1 && func_15022BB0(i, view) == 0) {
                    continue;
                }
                if (!(*mode == 1 && func_15022BB0(i, view) != 0)) {
                    if ((*(u16 *) (rec + 0x6C) & 0x100)
                        && func_1503FAF0(rec + 0x98, *(s16 *) (rec + 0x10), *(s16 *) (rec + 0x14), player, 0) != 0) {
                        continue;
                    }
                }
                if ((*(u8 **) ((u8 *) D_800DBFF0 + player * 0x9A0 + 0x3D4))[0x197] != 0) {
                    far = D_800D9F3C;
                } else {
                    far = *(u16 *) (rec + 0x90);
                    if (far == 0) {
                        far = D_800D9F3C;
                    } else if (far == 1) {
                        far = 40000;
                    }
                }
                depth[i - first] = func_150A6840(cam, (s32 *) (D_800DA030 + player * 0x40), *(s16 *) (rec + 0x10),
                                                 *(s16 *) (rec + 0x12) + *(f32 *) (rec + 0x18), *(s16 *) (rec + 0x14),
                                                 *(u16 *) (rec + 0x50), *(u16 *) (rec + 0x52), far);
                if (depth[i - first] < 0) {
                    depth[i - first] = -depth[i - first];
                }
                alpha = rec + 0x8B + player;
                if (depth[i - first] == 0 || depth[i - first] > far) {
                    *alpha = 0;
                    continue;
                }
                if (depth[i - first] >= far - 200) {
                    step = (far - depth[i - first]) * 255 / 200;
                    *alpha = (step > 255) ? 255 : step;
                } else if (*(u16 *) (rec + 0x88) == 0) {
                    *alpha = 0xFF;
                } else {
                    step = D_800BE9E4 * 10;
                    if (depth[i - first] < *(u16 *) (rec + 0x88)) {
                        *alpha = (*alpha > step) ? *alpha - step : 0;
                    } else {
                        *alpha = (*alpha < 0xFF - step) ? *alpha + step : 0xFF;
                    }
                    if (*alpha == 0) {
                        continue;
                    }
                }
                visible |= bit;
            }
            if (visible != 0) {
                for (i = first; i <= last; i++) {
                    ((u8 *) D_800DBEF4 + i * 0xA0)[0x6F] |= bit;
                    entry = *(u8 **) D_800895E0[player] + D_800DC318[player] * 4;
                    ((s16 *) entry)[0] = i;
                    ((s16 *) entry)[1] = depth[i - first];
                    D_800DC318[player]++;
                }
            }
        }
    }
}
