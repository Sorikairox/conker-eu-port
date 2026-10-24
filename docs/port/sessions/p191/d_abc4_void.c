void func_15142314(Mtx *arg0, s32 arg1, struct17 *arg2);
s32 func_15046C6C(f32 *, s32, f32, f32 *);
void func_1504715C(void *, u8 *);
extern u8 D_800A9350[];   /* bone of each foot: 5, 10, 19, 23 */
extern f32 D_800A93AC[5]; /* splash ring parameters (unk18..unk28 of the func_15154488 block) */
/* ground probe result of func_1504715C / func_15046C6C (HitInfo in game_eu_71E70.c) */
typedef struct {
    f32 y;          /* 0x00: ground height */
    s16 pos[9];     /* 0x04 */
    s32 unk18;
    u8 flags;
    u8 unk1D;
    u8 pad1E[2];
    s32 unk20;
} FootHitAABC4;

// footstep_splash: P191: footstep effect of the player p for foot `foot` (0..3, animation event callbacks
// func_1506FDF0 ... in game_981E0): when p has a model (+0x1D4), takes the foot bone's position (func_15142314, bone
// D_800A9350[foot]), probes the ground from 50 above to 50 below it (func_1504715C / func_15046C6C) and, on a hit,
// spawns a splash sprite at (bone x, ground y, bone z) (func_151DBCBC: light, size 40, 150, the hit's surface) and a
// ring burst there (func_15154488 with D_800A93AC's five parameters). s32 although the asm leaves no defined result:
// game_981E0 calls it without a prototype (implicitly int), so the port needs the int signature; it returns 0.
void func_151AABC4(struct127 *p, s32 foot) {
    struct_eu_15154488 ring;
    struct17 at;
    f32 probe[3];
    FootHitAABC4 hit;
    f32 bone[3];
    u8 light;

    if (p == NULL || *(Mtx **) ((u8 *) p + 0x1D4) == NULL) {
        return;
    }
    light = func_151D8E20();
    func_15142314(*(Mtx **) ((u8 *) p + 0x1D4), D_800A9350[foot & 0xFF], (struct17 *) bone);
    func_1504715C(&hit, (u8 *) p);
    probe[0] = bone[0];
    probe[1] = bone[1] + 50.0f;
    probe[2] = bone[2];
    if (func_15046C6C(probe, 0, probe[1] - 100.0f, (f32 *) &hit) == 0) {
        return;
    }
    at.unk0 = bone[0];
    at.unk4 = hit.y;
    at.unk8 = bone[2];
    func_151DBCBC(light, 40.0f, 150, (s32) hit.pos, &at, 0xFF, 1);
    ring.unk8 = at;
    ring.unk2E = 3;
    ring.unk14 = 2.5f;
    ring.unk2C = 3;
    ring.unk2 = 0xFF;
    ring.unk4 = -0x40;
    ring.unk6 = 0x1A;
    ring.unk0 = 0;
    ring.unk30 = 3;
    ring.unk32 = 1;
    ring.unk34 = 30;
    ring.unk36 = 20;
    ring.unk38 = 155;
    ring.unk3A = 100;
    ring.unk44 = 0x10;
    ring.unk46 = 0xF;
    ring.unk48 = 0;
    ring.unk18 = D_800A93AC[0];
    ring.unk1C = D_800A93AC[1];
    ring.unk20 = D_800A93AC[2];
    ring.unk24 = D_800A93AC[3];
    ring.unk28 = D_800A93AC[4];
    ring.unk3C = light;
    ring.unk40 = 0.0f;
    func_15154488(&ring, &ring.unk8, (s32) &hit, 0xFF, 1);
    return;
}
