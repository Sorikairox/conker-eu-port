typedef struct N06AC { u8 pad0[4]; struct N06AC *prev; struct N06AC *next; u8 padC[0xC]; u8 pri; u8 pad19[7]; s32 val; u8 pad24[0xE4]; } N06AC;
s32 func_151406AC(s32 arg0, s32 arg1, s32 arg2, s16 arg3) {
    s32 pad[2];
    N06AC head;
    N06AC **slot;
    N06AC *a;
    N06AC *p;
    N06AC *t;
    N06AC *b;
    N06AC *v;
    N06AC *next;
    s32 key;

    if (arg3 != 0) {
        return arg0;
    }
    slot = (N06AC **)&D_800DD280[arg2][arg1];
    head.pri = 0;
    head.val = 0;
    p = *slot;
    head.next = p;
    p->prev = &head;
    if (p != NULL) {
        a = p->next;
        if (a != NULL) do {
            b = a->prev;
            next = a->next;
            key = (a->pri << 8) + (a->val >> 16);
            for (v = b; v != NULL; v = v->prev) {
                if (key >= (v->pri << 8) + (v->val >> 16)) {
                    if (v != b) {
                        b->next = next;
                        t = a->next;
                        if (t != NULL) {
                            t->prev = a->prev;
                        }
                        t = v->next;
                        a->next = t;
                        if (t != NULL) {
                            t->prev = a;
                        }
                        a->prev = v;
                        v->next = a;
                    }
                    break;
                }
            }
            a = next;
        } while (next != NULL);
    }
    *slot = head.next;
    head.next->prev = NULL;
    return arg0;
}
