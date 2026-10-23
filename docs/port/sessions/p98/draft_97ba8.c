#ifdef NON_MATCHING
extern s32 D_800D3250[];
/* Pushes player `id` back along the direction between its two position vectors (+0x2A4 and +0x2F8): d =
 * normalised direction (func_15048F90 / func_1504917C); both vectors move by d * (-2.5, -2.0, -2.5) times the
 * per-player factor D_800D3250[id]. Only while D_800D2DB4 is set. Returns the record (v0 holds it on both paths;
 * the caller in game_14FF90 declares s32 and ignores it). */
s32 func_15097BA8(s32 id) {
    struct108 *r = &D_800DBFF0[id];
    struct17 *a;
    struct17 *b;
    struct17 d;

    if (D_800D2DB4 != 0) {
        a = (struct17 *) &r->unk2A4;
        b = (struct17 *) &r->unk2F8;
        func_15048F90(a, b, &d);
        func_1504917C(&d, &d);
        a->unk0 += d.unk0 * -2.5f * (f32) D_800D3250[id];
        a->unk4 += d.unk4 * -2.0f * (f32) D_800D3250[id];
        a->unk8 += d.unk8 * -2.5f * (f32) D_800D3250[id];
        b->unk0 += d.unk0 * -2.5f * (f32) D_800D3250[id];
        b->unk4 += d.unk4 * -2.0f * (f32) D_800D3250[id];
        b->unk8 += d.unk8 * -2.5f * (f32) D_800D3250[id];
    }
    return (s32) r;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C4590/func_15097BA8.s")
#endif
