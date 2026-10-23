extern u16 D_800BE898[];
extern s16 D_800DDFB0[];
extern u8 D_80096090[];
u8 *func_1502B020(s32 *arg0, s32 arg1, ...);
// ambient_sounds_load: for each of the 15 ambient sound slots (ids at D_800BE4A0, 4-byte stride; 0xFF = empty)
// clears its voice record (D_800DDA90, 16 bytes) and, when D_800BE898[slot] is set or the id is 0x3B, loads the
// sample (func_1502B020 kind 2) into +0 with the 16-byte rounded size in +4 (+0 = NULL when the size or the id's
// length is 0), and sets D_800DDFB0[slot] = { rate * 32 - 1, (length / rate) * 64 / 5 - 1 } (unsigned divisions;
// rate 0 traps like the asm's divu check).
void func_1500AC14(void) {
    u8 *voice = (u8 *) &D_800DDA90;
    u16 *ids = (u16 *) &D_800BE4A0;
    s16 *timing;
    u8 *info;
    s32 slot;
    u32 id;
    s32 size;
    u8 *data;
    u32 length;
    u32 rate;

    for (slot = 0; slot < 15; slot++, voice += 0x10, ids += 2) {
        id = *ids;
        *(s32 *) (voice + 0) = 0;
        *(s32 *) (voice + 8) = 0;
        *(s32 *) (voice + 4) = 0;
        voice[0xC] = 0;
        if (id == 0xFF) {
            continue;
        }
        if (D_800BE898[slot] == 0 && id != 0x3B) {
            continue;
        }
        timing = &D_800DDFB0[slot * 2];
        data = func_1502B020(&size, 2, 0, id);
        info = &D_80096090[id * 10];
        *(u8 **) (voice + 0) = data;
        *(s32 *) (voice + 4) = (size + 15) & ~15;
        length = *(u16 *) (info + 2);
        if (size == 0 || length == 0) {
            length = 0;
            *(s32 *) (voice + 0) = 0;
        }
        rate = info[8];
        timing[0] = (rate << 5) - 1;
        timing[1] = (((length / rate) << 6) / 5) - 1;
    }
}
