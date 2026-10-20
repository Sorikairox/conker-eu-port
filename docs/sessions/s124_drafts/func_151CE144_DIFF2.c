typedef struct {
    f32 unk0;
    f32 unk4;
    u8 pad8[0xC];
    s16 unk14;
    u8 pad16[6];
} NodeCE144;

s32 func_151CE144(u8 *arg0) {
    NodeCE144 *nodes;
    NodeCE144 *start;
    NodeCE144 *n;
    s32 prev;
    s32 i;
    f32 len;
    f32 inv;
    f32 d;
    f32 k;

    nodes = *(NodeCE144 **)(arg0 + 0x94);
    if (*(s8 *)(arg0 + 0x2C) <= 0) {
        return 1;
    }
    {
        prev = *(s8 *)(arg0 + 0x2E) - 1;
        if (prev < 0) {
            prev = arg0[0x25] - 1;
        }
        start = &nodes[*(s8 *)(arg0 + 0x2D)];
        len = fabsf((prev + nodes)->unk4 - start->unk4);
        if (len == 0.0f) {
            return 1;
        }
        {
            inv = 1.0f / len;
            k = inv * 10.0f;
            i = *(s8 *)(arg0 + 0x2D);
            do {
                n = &nodes[i];
                d = n->unk4 - start->unk4;
                n->unk14 = 0xFF;
                if (d < len * 0.197f) {
                    n->unk14 = (u8)((inv * 5.076142f) * d * 255.0f);
                } else if (len - len * 0.1f < d) {
                    n->unk14 = (u8)((len - d) * k * 255.0f);
                }
                i++;
                if (i >= arg0[0x25]) {
                    i = 0;
                }
            } while (i != *(s8 *)(arg0 + 0x2E));
        }
    }
    return 1;
}
