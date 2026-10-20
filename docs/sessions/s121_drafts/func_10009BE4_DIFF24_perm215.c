typedef struct {
    s32 unk0;
    struct54 *firstUsed;
    s32 unk8;
    s32 unkC;
    struct54 *firstFree;
} VNodeState;
#define vstate (*(VNodeState *)&D_800406A0)
void func_10009BE4(struct54 *n) {
    VNodeState *st = &vstate;
    if ((s32) n & 1) {
        D_8003C8E0 = 0x0F000004;
        func_150ADC50();
        return;
    }
    *(u32 *) n->unkC = n->unk8;
    if (n == st->firstUsed) {
        vstate.firstUsed = n->unk0;
    }
    if (n->unk0) n->unk0->unk4 = n->unk4;
    if (n->unk4) n->unk4->unk0 = n->unk0;
    if (st->firstFree) {
        struct54 *to = st->firstFree;
        n->unk0 = to->unk0;
        n->unk4 = to;
        if (to->unk0) to->unk0->unk4 = n;
        to->unk0 = n;
    } else {
        vstate.firstFree = n;
        n->unk0 = NULL;
        n->unk4 = NULL;
    }
}
