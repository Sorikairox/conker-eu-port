void func_1510F800(s32);
s32 func_1510FD20(s32 x, s32 z);
void func_151436B4(f32 yaw, f32 pitch, f32 dist, struct17 *out);
s32 func_15157580(void *sprite, s32, f32 alpha, s32, s32, s32 depth, s32, s32);
s32 func_151BF490(f32 yaw, s32 posArg, s32 arg2, u8 arg3, s32 colour, s32 flag, s32 arg6, s32 arg7, s32 arg8);
s32 memcpy(void *, void *, s32);
/* marker_sprite_spawn: spawns a marker at pos facing `angle` (degrees). size 0..2 (3 or more: nothing,
 * returns 0). In the level types with D_800D2E4C->unk19 & 4, or for size 2, it is a HUD-style sprite (texture
 * 0xA2, func_15157580) placed 39 units out along the angle and 40 lower, with sprite size {3, 1, 2}[size], flag
 * 0x10 set when `flag`; the angle, that position and `kind` go to the sprite object + 0x120 (func_151BF0D0
 * turns it). Otherwise the 3D ring particle func_151BF490. Returns the object (0 when none). arg5 / arg6 unused. */
s32 func_151BEE00(f32 *pos, f32 angle, u8 kind, u8 flag, u8 size, s32 arg5, s32 arg6) {
    static const u8 sizes[3] = { 3, 1, 2 };
    struct {
        u8 pad50[4];
        f32 angle;      // +0x54: the 0x18 bytes from here go to the sprite object + 0x120
        f32 pos[3];
        u8 kind;
        u8 pad65[3];
        LivesSprite spr; // +0x68
    } sp;
    f32 dir[3];
    s32 room;
    s32 obj;

    func_1510F800(0);
    room = func_1510FD20((s32) pos[0], (s32) pos[2]);
    if (size >= 3) {
        return 0;
    }
    if ((D_800D2E4C->unk19 & 4) || size == 2) {
        sp.angle = angle;
        sp.spr.u3C = 0;
        sp.spr.u40 = 0;
        sp.spr.u41 = 0;
        sp.spr.x = pos[0];
        sp.spr.y = pos[1];
        sp.spr.z = pos[2];
        sp.kind = kind;
        sp.spr.u50 = room;
        func_151436B4(angle * 0.017453292f, 0.0f, 39.0f, (struct17 *) dir);
        sp.pos[0] = pos[0] + dir[0];
        sp.pos[1] = pos[1] + dir[1] - 40.0f;
        sp.pos[2] = pos[2] + dir[2];
        sp.spr.u38 = sizes[size];
        sp.spr.u0 = (flag ? 0x10 : 0) | 0xE;
        sp.spr.u1 = 1;
        if (D_800BE9F0 == 7) {
            sp.spr.u2 = 6;
        } else {
            sp.spr.u2 = 2;
        }
        sp.spr.u4 = 0xFF;
        sp.spr.u6 = 300;
        sp.spr.texture = 0xA2;
        sp.spr.u14 = 0x620405;
        sp.spr.uC = 8;
        sp.spr.u18 = 0x40200;
        sp.spr.u1C = 0x14;
        sp.spr.u20 = 0x37;
        sp.spr.u24 = 0x80;
        sp.spr.u28 = 0x20;
        sp.spr.u2D = 8;
        sp.spr.color[0] = 0xFF;
        sp.spr.color[2] = 0xFF;
        sp.spr.u3 = 0;
        sp.spr.u10 = 0;
        sp.spr.u2C = 0;
        sp.spr.color[1] = 0xFF;
        sp.spr.color[3] = 0xFF;
        sp.spr.color[4] = 0xFF;
        sp.spr.color[5] = 0xFF;
        sp.spr.color[6] = 0xFF;
        sp.spr.color[7] = 0xFF;
        obj = func_15157580(&sp.spr, 0, 1.0f, 3, 0xFF, 0x18, 0xFF, 1);
        if (obj != 0) {
            memcpy((u8 *) obj + 0x120, &sp.angle, 0x18);
        }
        return obj;
    }
    return func_151BF490(angle, (s32) pos, 3, 0xFF, size, flag, room, 0xFF, 1);
}
