typedef struct { u8 a[3]; } Tri3;
typedef struct { u8 pad[0x14]; u8 u14; u8 pad2[0x1F]; } S34;
extern Tri3 D_80088D24;

s32 func_150DFE40(s32 arg0) {
    Tri3 t = D_80088D24;

    if (((S34 *)D_800D34B8)[t.a[arg0]].u14 != 0) {
        return 1;
    }
    return 0;
}
