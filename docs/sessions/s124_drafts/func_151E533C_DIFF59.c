typedef struct {
    s8 pad0[5];
    s8 unk5;
    s8 pad6;
    s8 unk7;
    s8 pad8[2];
} S533C;
typedef struct {
    s16 unk0;
    s16 unk2;
} T533C;
extern S533C D_800ABA70[];
extern T533C D_800ABBA0[];
extern u16 D_80090160;
extern s8 D_800901CC;
extern s8 D_800E0EB6;
extern s8 D_800E0EF0;
extern s8 D_800E0EF1;
extern s8 D_800E0EF2;
extern s8 D_800E0EF3;

void func_151E533C(void) {
    s8 lvl;
    s8 n;
    s16 id;

    D_800901CC = 0;
    D_800BEAC1 = 0;
    D_80090144 = 0;
    D_800E0EC0 = 0;
    n = 0;
    lvl = D_800ABA70[(s8)D_80090174[0x42]].unk7;
    D_80090160 &= 0xF369;
    if (D_800ABA70[(s8)D_80090174[0x42]].unk5 >= 0) {
        if (D_800E0EF0 == 1) {
            n = 1;
        }
        if (D_800E0EF1 == 1) {
            n++;
        }
        if (D_800E0EF2 == 1) {
            n++;
        }
        if (D_800E0EF3 == 1) {
            n++;
        }
        n = n >= 2;
    }
    if (lvl < 0 || n != 0) {
        if (lvl == -2 && D_800E0EB6 == 0) {
            D_800E0B94 = 6;
            D_80090120 = 2;
            D_80090160 = 0;
            return;
        }
        id = 0x1D;
        if (n == 0) {
            D_800E0B94 = 3;
        } else {
            D_800E0B94 = 6;
            D_80090120 = 4;
        }
    } else {
        D_800E0B94 = 6;
        id = D_800ABBA0[lvl].unk0;
        D_80090120 = 1;
    }
    D_800D3260 = 0;
    func_1501C710(6, id, 0, 0, 1);
    func_151E5D28();
    D_8008FD8C = 1;
    D_80090130 = 1;
}
