s32 func_1510FE58(s32 arg0, s32 arg1, s32 arg2, s32 *arg3);
s32 func_150ADA20(void);

/* rain_spawn_splashes: count times, picks a random point in the 500 x 500 square from the rain centre
 * D_800DD868 (s16 x +0, z +4), finds the ground height there (func_1510FE58 from height 10000; -10000 = no ground)
 * and spawns a splash sprite (texture 0x12, flags 0x9804, size 0x19, 0x80 at +0x8A) on it. The spawn record is one
 * stack struct (func_15168800 copies 0xA8 bytes of it). */
void func_1517A084(s32 count) {
    Spawn9B70 sp;
    s32 cx;
    s32 cz;
    s32 x;
    s32 y;
    s32 z;
    s32 i;

    cx = ((s16 *) D_800DD868)[0];
    cz = ((s16 *) D_800DD868)[2];
    for (i = 0; i < count; i++) {
        x = func_150ADA20() % 500 + cx;
        z = func_150ADA20() % 500 + cz;
        y = func_1510FE58(x, 10000, z, NULL);
        if ((f32) y != -10000.0f) {
            sp.u80 = 0;
            sp.u8A = 0x80;
            sp.u8C = x;
            sp.u8E = y;
            sp.u90 = z;
            sp.u94 = 0x19;
            sp.u92 = 0x19;
            *(s16 *) sp.pad96 = 0;
            sp.uA2 = 0xE;
            sp.uA0 = 0x12;
            sp.u98 = 0x9804;
            sp.uA1 = 0;
            func_1516865C(&sp, 0xFF, 0xFF, 0xFF, 0xFF);
            func_15168800(&sp, 0xFF, 0);
        }
    }
}
