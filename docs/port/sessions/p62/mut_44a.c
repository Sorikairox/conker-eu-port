extern u16 D_800C5BC0[]; /* vertex block size of each model slot, in 16-byte vertices */
void func_10004074(void *);

/*
 * P62: vertex blocks of object o for variant var: the two frame words o +0x28C + var * 8 (+0 / +4) that
 * func_1502CFEC draws from. The model slot is ((u8 *)o +0x2C4)[var]; its shared block is D_800D19A0[slot] with the
 * user count D_800D1F80[slot]. The sharing mode is (rec +0x10) & 3, rec being the record +0x144 of the parent object
 * o[0x65] - 1 (or o's own when o[0x65] is 0); no record: mode 0; slot 0: mode 2.
 *   both words set, or no shared block: nothing (0);
 *   mode 0: both words share the block (count += 2);
 *   mode 1: word 0 (if 0 or the shared block): the first user shares it (count += 2), later users get a private copy;
 *           then word 1 = word 0;
 *   mode 2: each word that is 0 or the shared block (word 1 also when the two are equal): shared if the count is 0
 *           (count += 1), else a private copy; an allocation failure stops there and, on word 1, gives word 0 back
 *           (free its copy or count -= 1) and clears it;
 *   mode 3: nothing.
 * Returns 1 when an allocation failed, else 0.
 */
s32 func_150844AC(struct127 *o, s32 var) {
    u8 *obj = (u8 *)o;
    u32 *words = (u32 *)(obj + 0x28C + var * 8);
    u8 *rec;
    s32 slot;
    s32 mode;
    u32 *shared;
    u8 *count;
    s32 size;
    s32 failed;
    s32 w;

    if (obj[0x65] != 0) {
        rec = *(u8 **)((u8 *)&D_800CC2D0[obj[0x65] - 1] + 0x144);
    } else {
        rec = *(u8 **)(obj + 0x144);
    }
    slot = (*(u8 **)(obj + 0x2C4))[var];
    mode = 0;
    if (rec != NULL) {
        mode = rec[0x10] & 3;
    }
    if (slot == 0) {
        mode = 2;
    }
    shared = (u32 *)&D_800D19A0 + slot;
    if (words[0] != 0 && words[1] != 0) {
        return 0;
    }
    if (*shared == 0) {
        return 0;
    }
    failed = 0;
    count = (u8 *)D_800D1F80 + slot;

    if (mode == 0) {
        words[1] = *shared;
        words[0] = *shared;
        *count += 2;
    } else if (mode == 1) {
        if (words[0] == 0 || words[0] == *shared) {
            if (*count != 0) {
                size = D_800C5BC0[slot] * 16;
                words[0] = (u32)allocate_memory(size, 1, 2, 2);
                if (words[0] == 0) {
                    failed = 1;
                } else if (words[0] != 0) {
                    bcopy((void *)*shared, (void *)words[0], size);
                } else {
                    words[0] = *shared; /* not reached (the asm has it) */
                }
            } else {
                words[1] = *shared;
                words[0] = *shared;
                *count += 2;
            }
        }
        words[1] = words[0];
    } else if (mode == 2) {
        for (w = 0; w < 2; w++) {
            if (!(words[w] == 0 || words[w] == *shared || (w == 1 && words[0] == words[1]))) {
                continue;
            }
            if (*count != 0) {
                size = D_800C5BC0[slot] * 16;
                words[w] = (u32)allocate_memory(size, 1, 2, 2);
                if (words[w] == 0) {
                    failed = 1;
                    if (w == 1) {
                        if (words[0] != *shared) {
                            func_10004074((void *)words[0]);
                        } else {
                            *count -= 1;
                        }
                        words[0] = 0;
                    }
                }
                if (words[w] != 0) {
                    bcopy((void *)*shared, (void *)words[w], size);
                } else {
                    words[w] = *shared; /* not reached (the asm has it) */
                }
            } else {
                words[w] = *shared;
                *count += 1;
            }
        }
    }
    return failed;
}
