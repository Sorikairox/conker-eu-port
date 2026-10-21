typedef struct { u16 id; u8 timer; u8 slot; } SfxPend;
#define PEND ((SfxPend *)D_80041F10)

void func_10011310(void) {
    s32 removed;
    s32 j;
    s32 n;
    s32 i;
    struct120 *e;

    removed = 0;
    j = 0;
    n = D_80041F50;
    for (i = 0; i < (s32)D_80041F50; i++) {
        if (PEND[i].timer > 0) {
            PEND[i].timer--;
        } else {
            removed = 1;
            e = &D_800425E0[PEND[i].slot];
            if (e->unk0 == PEND[i].id) {
                e->unk0 = 0;
                e->unk4 = 0;
                if (e->unk8 != NULL) {
                    func_10017594(e->unk8);
                }
                e->unk8 = NULL;
            }
            n--;
        }
        if (j != i) {
            PEND[j] = PEND[i];
        }
        if (removed) {
            j++;
        } else {
            removed = 0;
        }
    }
    D_80041F50 = n;
}
