typedef struct Node8D80 { u8 u0; u8 u1; u8 u2; u8 u3; u8 u4; s16 u6; void *u8_; struct Node8D80 *uC; struct127 *u10; s32 u14; } Node8D80;
void *allocate_memory(s32, s32, s32, s32);
void func_10004074(u8 *);
s32 func_1502DE10(u8);
void func_15188FC8();

// object_trail_start: starts (or extends) the trail effect of obj (scene event 5 / 0x2D): an existing node of the
// D_800DF7C8 list for obj gets the longer duration and the new style; else a 0x18-byte node (type 3, 0x14) with a
// zeroed buffer of 0x180 bytes per trail point of the object's kind (func_1502DE10(kind), 0 = no trail) is appended.
void func_15188D80(struct127 *obj, s32 frames, s32 style) {
    Node8D80 *n;
    void *buf;
    s32 count;

    for (n = *(Node8D80 **) D_800DF7C8; n != NULL; n = n->uC) {
        if (obj == n->u10) {
            if (n->u6 < frames) {
                n->u6 = frames;
            }
            n->u4 = style;
            return;
        }
    }
    n = allocate_memory(0x18, 1, 0, 0);
    if (n == NULL) {
        return;
    }
    count = func_1502DE10(((u8 *) obj)[4]);
    if (count == 0) {
        func_10004074((u8 *) n);
        return;
    }
    buf = allocate_memory(count * 0x180, 1, 1, 1);
    if (buf == NULL) {
        func_10004074((u8 *) n);
        return;
    }
    n->u0 = 0;
    n->u1 = 3;
    n->u2 = 0;
    n->u3 = 0x14;
    n->u4 = style;
    n->u8_ = buf;
    n->u10 = obj;
    n->u14 = 0;
    n->u6 = frames;
    bzero(buf, count * 0x180);
    func_15188FC8(n, D_800DF7C8);
}
