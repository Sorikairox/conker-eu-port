//HOIST void func_1505D6F0(struct127 *, s32);
void func_1505D408(struct127 *, struct127 *, f32, f32, f32, f32, f32, s32);
void func_1505D5D0(struct127 *, struct127 *, f32, f32, f32, f32, f32, s32, f32, f32, f32, f32, f32);
extern s8 D_800CC68C;
extern s8 D_800CC68D;

/* Record-vs-record push / contact pass for record idx (rec = &D_800CC2D0[idx]): clears the contact mask
 * D_800CC268 and the D_800CC68C / 68D flags, then tests rec's cylinder (radius unkE4, height offset unkE8, vertical
 * scale unkEC) against the other 25 records (only record 0 when rec->unkF8 has 0x02000000). Overlaps go to
 * func_1505D408; record id 0x34 gets the special box test func_1505D5D0. In multiplayer, a player close to
 * another team's player who holds the flag (+0x78 in the controller) sets its own chase timer (+0x4A = 20). */
void func_1505D6F0(struct127 *rec, s32 idx) {
    struct127 *o;
    u8 *ctl;
    s32 i;
    s32 count;
    f32 radius, scale, x, y, z;
    f32 dx, dy, dz, d2, reach;
    s16 oradius;

    D_800CC268 = 0;
    D_800CC68C = 0;
    D_800CC68D = 0;
    count = 25;
    if (rec->interaction_state == 1) {
        ctl = (u8 *)D_800CC2D0[idx].unk31C;
        if (ctl[0x4E] != 0 || ctl[0x27] != 0) {
            return;
        }
    }
    if (rec->unk13D >= 100 || rec->unkE4 == 0 || rec->unk65 != 0) {
        return;
    }
    if ((rec->unkF8 & 0x01000000) || (rec->unkF8 & 0x4000)) {
        return;
    }
    scale = rec->unkEC;
    x = rec->x_position;
    z = rec->z_position;
    radius = rec->unkE4;
    y = rec->y_position + (s16)rec->unkE8;
    if (rec->unkF8 & 0x02000000) {
        count = 1;
    }
    for (i = 0, o = D_800CC2D0; i < count; i++, o++) {
        if (o->interaction_state == 0) {
            continue;
        }
        oradius = o->unkE4;
        if (oradius < 2) {
            continue;
        }
        if ((o->unkF8 & 0x02000000) && rec->unk127 == 0xFF) {
            continue;
        }
        if ((o->unkF8 & 0x01000000) || i == idx || o->unk65 == idx + 1 || o->unk13D >= 100 || o->unk2FA == 0) {
            continue;
        }
        dx = x - o->x_position;
        dz = z - o->z_position;
        dy = (y - (o->y_position + (s16)o->unkE8)) * ((scale + o->unkEC) * 0.5f);
        if (D_800BE616 != 0 && dx * dx + dy * dy + dz * dz < 30000.0f && rec->interaction_state == 1 &&
            o->interaction_state == 1 && o->unk128 != rec->unk128) {
            ctl = (u8 *)rec->unk31C;
            if (ctl[0x78] == 0 && ((u8 *)o->unk31C)[0x78] != 0) {
                ctl[0x4A] = 20;
            }
        }
        reach = radius + oradius;
        d2 = dx * dx + dy * dy + dz * dz;
        if (d2 < reach * reach) {
            func_1505D408(rec, o, dx, dy, dz, d2, reach, i);
        }
        if (o->id == 0x34) {
            if (o->unk251 == 2) {
                func_1505D5D0(rec, o, x, y, z, scale, radius, i, 120.0f, 250.0f, 120.0f, -130.0f, 0.0f);
            } else {
                func_1505D5D0(rec, o, x, y, z, scale, radius, i, 130.0f, 140.0f, 250.0f, -50.0f, 0.0f);
            }
        }
    }
}
