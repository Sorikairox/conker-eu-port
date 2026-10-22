extern void *D_800C3D80[][30];   /* 16-byte block per actor */

/* Clears (0xFF) the 16-byte block of every actor of sequence slot `slot`. */
void func_1501CDA0(s32 slot) {
    s32 i;
    s32 j;

    for (i = 0; i < D_800C3A5A[slot]; i++) {
        for (j = 0; j < 16; j++) {
            ((u8 *)D_800C3D80[slot][i])[j] = 0xFF;
        }
    }
}
