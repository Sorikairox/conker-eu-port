/*
 * trail_spawn_directed: spawns one trail particle (func_15148310, kind 0, handler pair 1 / 0) of type n at
 * (x, y, z) with sprite `sprite` and tint tint + 3. Its velocity has length speed along the byte angles pitch /
 * yaw (func_151423D8 = byte-angle sine): (speed sin(pitch) sin(yaw - 0x40), -speed sin(pitch - 0x40),
 * speed sin(pitch) sin(yaw)); motion block speed slot = drag, scale = scale, flags 8 (0x28 for type 0xA),
 * 0xFF / 0xFF; fixed render block (0, 1, 0x160600, mode 3 / 0x10 / 0x80 / 0x20, 0, 9). flag goes to argD.
 * The asm leaves some block bytes unwritten (spawn +0x14 / +0x18, motion floor +0x14 and timers +0x1C / +0x1E,
 * render +0x1E): the C clears them.
 */
void func_1514948C(u8 n, f32 x, f32 y, f32 z, s32 tint, s32 yaw, s32 pitch, f32 speed, s32 sprite, f32 drag, f32 scale,
                   u8 flag) {
    struct {
        s32 render[3]; /* sp4C */
        s32 mode[4];
        u8 b0;
        u8 b1;
        u8 pad[2];
    } rb;
    struct {
        f32 speed;     /* sp7C */
        f32 vel[3];
        f32 scale;
        f32 floor;
        u8 flags;
        u8 kind;
        u8 full;
        u8 alpha;
        s16 t0;
        s16 t1;
    } mb;
    struct {
        f32 pos[3];    /* sp9C */
        s16 sprite;
        s16 model;
        s32 count;
        s8 b14;
        u8 tint;
        s32 owner;
    } sb;
    f32 sp = func_151423D8((u8) pitch);
    f32 cp = func_151423D8((pitch - 0x40) & 0xFF);
    f32 sy = func_151423D8((u8) yaw);
    f32 cy = func_151423D8((yaw - 0x40) & 0xFF);
    f32 h;

    sb.count = 1;
    sb.model = 1;
    mb.full = 0xFF;
    mb.flags = (n == 0xA) ? 0x28 : 8;
    mb.kind = n;
    h = speed * sp;
    sb.pos[0] = x;
    sb.pos[1] = y;
    sb.pos[2] = z;
    mb.speed = drag;
    mb.scale = scale;
    sb.tint = tint + 3;
    mb.alpha = 0xFF;
    sb.sprite = sprite;
    mb.vel[0] = h * cy;
    mb.vel[1] = -speed * cp;
    mb.vel[2] = h * sy;
    sb.b14 = 0;
    sb.owner = 0;
    mb.floor = 0.0f;
    mb.t0 = 0;
    mb.t1 = 0;
    rb.render[0] = 0;
    rb.render[1] = 1;
    rb.render[2] = 0x160600;
    rb.mode[0] = 3;
    rb.mode[1] = 0x10;
    rb.mode[2] = 0x80;
    rb.mode[3] = 0x20;
    rb.b0 = 0;
    rb.b1 = 9;
    rb.pad[0] = rb.pad[1] = 0;
    func_15148310((u8 *) &sb, (s32) &mb, 0, 1, 0, 0, 0, 0, 0, 0, 0, (u8 *) &rb, 0, flag, 1);
}
