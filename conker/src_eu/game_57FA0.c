#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#include <stdarg.h>

#include "macros.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
typedef struct RomRecCacheEntry {
    /* 0x00 */ u32 key;      /* ROM address | 0x80000000 */
    /* 0x04 */ s32 stamp;    /* D_800C4180 at the last use */
    /* 0x08 */ s32 word0;
    /* 0x0C */ s32 word1;
} RomRecCacheEntry;
extern RomRecCacheEntry D_800C4188[16];
#endif

void func_1502AAF0(void) {
}

void func_1502AAF8(s32 arg0) {
}

#ifdef NON_MATCHING
/* ROM record MRU cache insert (P13, hand C): drops the n oldest of the 16 entries (bcopy down) and appends n
 * records from arg1 (two words each) at the end, keys arg3, arg3 + 8, ..., all stamped arg2. */

void func_1502AB04(s32 arg0, s32 *arg1, s32 arg2, u32 arg3) {
    u32 i;

    if (arg0 != 0) {
        bcopy(&D_800C4188[arg0], &D_800C4188[0], 0x100 - arg0 * 16);
    }
    for (i = 16 - arg0; i < 16; i++) {
        D_800C4188[i].word0 = arg1[0];
        D_800C4188[i].word1 = arg1[1];
        D_800C4188[i].key = arg3;
        D_800C4188[i].stamp = arg2;
        arg1 += 2;
        arg3 += 8;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502AB04.s")
#endif
#ifdef NON_MATCHING
/* P7: difftest EQUIV (128 trials, also with DIFFTEST_OUTPARAMS=1); only the cache-miss path ran (no random key hit) */
/* reads the 8-byte ROM record at arg0 + arg1 * 8 through a 16-entry most-recently-used cache.
 * Returns the record's first word and stores its second in *arg2. */
/* RomRecCacheEntry / D_800C4188: hoisted above (P13) */
extern s32 D_800C4180;   /* use counter */
void func_1502AB04(s32 arg0, s32 *arg1, s32 arg2, u32 arg3);

s32 func_1502AC88(u8 *arg0, s32 arg1, s32 *arg2) {
    u32 key = (u32)(arg0 + arg1 * 8) | 0x80000000;
    RomRecCacheEntry hit;
    u64 raw[6];          /* room for a 16-byte aligned 32-byte DMA buffer */
    u8 *buf;
    s32 *rec;
    s32 i;
    s32 j;

    for (i = 0; i < 16; i++) {
        if (D_800C4188[i].key == key) {
            /* move the hit to the end: most recent */
            hit = D_800C4188[i];
            for (j = i; j < 15; j++) {
                D_800C4188[j] = D_800C4188[j + 1];
            }
            D_800C4188[15] = hit;
            D_800C4188[15].stamp = D_800C4180;
            *arg2 = D_800C4188[15].word1;
            return D_800C4188[15].word0;
        }
    }
    D_800C4180++;
    buf = (u8 *)(((u32)raw + 15) & ~15);
    func_10004514(key & 0x7FFFFFF0, buf, ((key & 0xE) + 0x1F) & ~0xF, 1);
    rec = (s32 *)(buf + (key & 0xF));
    i = rec[0];
    *arg2 = rec[1];
    func_1502AB04(2, rec, D_800C4180, key);   /* add it to the cache */
    return i;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502AC88.s")
#endif
#ifdef NON_MATCHING
/*
 * P65: the last step of func_1502B110 (animation header lookup): DMA the n 8-byte records {offset, size} starting
 * at entry index of the ROM table at base into buf (16-byte aligned block that covers them, starting at the
 * 16-aligned buf + 8), turn each offset into an absolute ROM address (+= base) and return the first record.
 */
s32 func_1502AF04(s32 base, s32 buf, s32 index, u32 n) {
    u32 src = base + index * 8;
    u32 dst = (buf + 8) & ~0xF;
    s32 *rec;
    u32 i;

    func_10004514(src & ~0xF, (void *) dst, ((src & 0xE) + n * 8 + 0xF) & ~0xF, 1);
    rec = (s32 *) (dst + (src & 0xF));
    for (i = 0; i < n; i++) {
        rec[i * 2] += base;
    }
    return (s32) rec;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502AF04.s")
#endif

u8 *func_1502B020(s32 *arg0, s32 arg1, ...) {
    u8 *p;
    s32 v;
    va_list ap;
    s32 ok;

    ok = 1;
    p = D_AB2240;
    va_start(ap, arg1);
    for (; arg1 != 0; arg1--) {
        v = va_arg(ap, s32);
        if (ok != 0) {
            p += func_1502AC88(p, v, &ok);
        }
        ok &= 0x0FFFFFFF;
    }
    if (arg0 != NULL) {
        *arg0 = ok & 0x0FFFFFFF;
    }
    if (ok == 0) {
        return 0;
    }
    return p;
}

s32 func_1502B110(u8 *arg0, s32 arg1, s32 arg2, u32 arg3, ...) {
    s32 v;
    va_list ap;
    s32 ok;
    s32 ret;

    ok = 1;
    ret = 0;
    if (arg0 == NULL) {
        arg0 = D_AB2240;
    }
    va_start(ap, arg3);
    for (; arg3 > 1; arg3--) {
        v = va_arg(ap, s32);
        if (ok != 0) {
            arg0 += func_1502AC88(arg0, v, &ok);
        }
        ok &= 0x0FFFFFFF;
    }
    v = va_arg(ap, s32);
    if (ok != 0) {
        ret = func_1502AF04(arg0, arg2, v, arg1);
    }
    return ret;
}
s32 *allocate_memory(s32, s32, s32, s32);
#ifdef NON_MATCHING // the definition is void (asm: v0 is not a result); one signature for wasm
void func_10004074(s32 *);
#else
s32 func_10004074(s32 *);
#endif
s32 func_10006530(s32 *, s32, u32);
s32 func_150ADC50();

s32 func_1502B224(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  s32 *temp_v0;
  u32 temp_t6;
  s32 sp24;
  u32 temp_v0_2;
  u32 var_s1;
  temp_t6 = ((arg2 & 0x0FFFFFFF) + 1) & (~1);
  var_s1 = temp_t6;
  if ((arg3 != 0) && (((u32) arg3) < temp_t6))
  {
    var_s1 = (u32) arg3;
  }
  if ((arg2 & 0x70000000) == 0x10000000)
  {
    temp_v0 = allocate_memory((s32) var_s1, 1, 2, 2);
    if (temp_v0 == 0)
    {
      return 0;
    }
    func_10004514((s32) arg0, temp_v0, (var_s1 + 0xF) & (~0xF), 1);
    sp24 = (*temp_v0) & 0x7FFFFFFF;
    var_s1 = func_10006530(temp_v0, arg1, D_8003809C);
    if (sp24 != ((0, var_s1))) // fakematch: comma expression flips beq operand order
    {
      D_8003C8E0 = 0x0C000036;
      func_150ADC50();
    }
    func_10004074(temp_v0);
    goto block_10;
  }
  func_10004514((s32) arg0, (u8 *) arg1, (var_s1 + 0xF) & (~0xF), 1);
  block_10:
  return (s32) var_s1;

}
#ifdef NON_MATCHING
/* Asset load: allocate, DMA the record; when (info & 0x70000000) == 0x10000000 the record is packed
 * (first word = unpacked size, rejected when 0 or >= 1000000): unpack it into a second buffer and free
 * the packed copy. *size_out gets the loaded size (0 on failure). */
s32 func_1502B350(u8 *rom, s32 info, s32 *size_out) {
    u32 size = ((info & 0x0FFFFFFF) + 1) & ~1;
    s32 *buf;
    s32 *out;
    u32 n;
    s32 got;

    buf = allocate_memory(size, 1, 2, 2);
    if (buf == NULL) {
        return 0;
    }
    func_10004514((s32) rom, buf, (size + 0xF) & ~0xF, 1);
    if ((info & 0x70000000) != 0x10000000) {
        *size_out = size;
        return (s32) buf;
    }
    n = buf[0] & 0x7FFFFFFF;
    *size_out = n;
    out = NULL;
    got = 0;
    if (n != 0 && n < 1000000) {
        out = allocate_memory(n, 1, 2, 2);
        if (out != NULL) {
            got = func_10006530(buf, (s32) out, D_8003809C);
        }
    }
    func_10004074(buf);
    *size_out = got;
    return (s32) out;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B350.s")
#endif
#ifdef NON_MATCHING
/* Relocates a loaded asset's sub-file table of {s32 offset, u32 info} entries. With count == 0 the
 * table ends at the first entry whose info has bit 31 set. info &= 0x0FFFFFFF; offset becomes
 * base + offset, or 0 when offset == -1 or info == 0. Returns the entry count. */
s32 func_1502B4A8(s32 base, s32 count) {
    s32 *tab = (s32 *) base;
    s32 i;

    if (count == 0) {
        do {
            count++;
        } while (!(tab[(count - 1) * 2 + 1] & 0x80000000));
    }
    for (i = 0; i < count; i++) {
        s32 *e = &tab[i * 2];
        e[1] &= 0x0FFFFFFF;
        e[0] = (e[0] == -1 || e[1] == 0) ? 0 : e[0] + base;
    }
    return count;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B4A8.s")
#endif
s32 func_1502B350(u8 *, s32, s32 *);

s32 func_1502B5C8(s32 *arg0, s32 arg1, ...) {
    s32 *q;
    s32 v;
    u8 *p;
    s32 sp40;
    s32 ret;
    s32 sp38;
    va_list ap;

    q = &sp40;
    if (arg0 != NULL) {
        q = arg0;
    }
    *q = 1;
    p = D_AB2240;
    va_start(ap, arg1);
    if (arg1 != 0) {
        do {
            v = va_arg(ap, s32);
            if (*q != 0) {
                p += func_1502AC88(p, v, &sp38);
            }
            *q = sp38 & 0x0FFFFFFF;
        } while (--arg1 != 0);
    }
    if (*q != 0) {
        ret = func_1502B350(p, sp38, q);
    } else {
        ret = 0;
    }
    return ret;
}
s32 func_1502B350(u8 *, s32, s32 *);
s32 func_1502B4A8(s32, s32);
s32 func_1502B6BC(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, ...) {
    s32 *var_s2;
    s32 v;
    s32 sp44;
    s32 var_s0;
    u8 *var_s0_2;
    s32 sp38;
    va_list ap;
    var_s2 = &sp44;
    if (arg0 != NULL) {
        var_s2 = arg0;
    }
    *var_s2 = 1;
    var_s0_2 = D_AB2240;
    va_start(ap, arg3);
    if (arg3 != 0) {
        do {
            v = va_arg(ap, s32);
            if (*var_s2 != 0) {
                var_s0_2 += func_1502AC88(var_s0_2, v, &sp38);
            }
            *var_s2 = sp38 & 0x0FFFFFFF;
        } while (--arg3 != 0);
    }
    if (*var_s2 != 0) {
        var_s0 = func_1502B350(var_s0_2, sp38, var_s2);
        if ((*var_s2 != 0) && (var_s0 != 0)) {
            arg1 = func_1502B4A8(var_s0, arg1);
        } else {
            arg1 = 0;
        }
        if (arg2 != NULL) {
            *arg2 = arg1;
        }
    } else {
        var_s0 = 0;
    }
    return var_s0;
}

s32 func_1502B7F0(s32 *arg0, s32 arg1, ...) {
    s32 v;
    u8 *p;
    va_list ap;
    s32 ok;
    s32 sp34;

    ok = 1;
    p = D_AB2240;
    va_start(ap, arg1);
    for (; arg1 != 0; arg1--) {
        v = va_arg(ap, s32);
        if (ok != 0) {
            p += func_1502AC88(p, v, &sp34);
        }
        ok = sp34 & 0x0FFFFFFF;
    }
    if (ok != 0) {
        *arg0 = func_1502B350(p, sp34, &ok);
    } else {
        *arg0 = 0;
    }
    return ok;
}
// void func_1502B7F0(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
//     s32 sp38;
//     s32 sp34;
//     s32 temp_s1;
//     s32 offset;
//     s32 i;
//
//     sp38 = 1;
//     offset = &D_00AB1950; // 0xAB1950 - assets offsets table
//     temp_s1 = &arg2;
//
//     i = arg1;
//     if (i != 0) {
//         do {
//             temp_s1 = ALIGN4(temp_s1);
//             if (sp38 != 0) {
//                 offset += func_1502AC88(offset, temp_s1, &sp34);
//             }
//             sp38 = sp34 & 0xFFFFFFF;
//             temp_s1 += 1;
//         } while (i-- != 0);
//     }
//
//     if (sp38 != 0) {
//         *arg0 = func_1502B350(offset, sp34, &sp38);
//     } else {
//         *arg0 = 0;
//     }
// }

s32 func_1502B224(u8 *, s32, s32, s32);

s32 func_1502B8E0(s32 arg0, s32 arg1, s32 arg2, ...) {
    s32 ok;
    u8 *p;
    s32 v;
    va_list ap;
    s32 sp34;

    ok = 1;
    p = D_AB2240;
    va_start(ap, arg2);
    if (arg2 != 0) {
        do {
            v = va_arg(ap, s32);
            if (ok != 0) {
                p += func_1502AC88(p, v, &sp34);
            }
            ok = sp34 & 0x0FFFFFFF;
        } while (--arg2 != 0);
    }
    if (ok != 0) {
        ok = func_1502B224(p, arg0, sp34, arg1);
    }
    return ok;
}


s32 func_1502B9B4(s32 arg0, ...) {
    s32 ok;
    u8 *p;
    s32 v;
    va_list ap;
    s32 sp54;
    s32 *q;
    u8 buf[0x18];
    ok = 1;
    p = D_AB2240;
    va_start(ap, arg0);
    if (arg0 != 0) {
        do {
            v = va_arg(ap, s32);
            if (ok != 0) {
                p += func_1502AC88(p, v, &sp54);
            }
            ok = sp54 & 0x0FFFFFFF;
        } while (--arg0 != 0);
    }
    if (ok != 0) {
        ok = ((sp54 & 0x0FFFFFFF) + 1) & ~1;
        if ((sp54 & 0x70000000) == 0x10000000) {
            q = (s32 *)buf;
            if ((u32)q & 8) {
                q = (s32 *)(buf + 8);
            }
            func_10004514((s32)p, q, 0x10, 1);
            ok = *q;
        }
    }
    return ok;
}
// NON-MATCHING: maybe 50% there?
// s32 func_1502B9B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
//
//     s32 stack2[2];
//     s32 stack1[2];
//     s32 stack0[5];
//
//     s32 more;
//     s32 offset;
//     s32 *tmp;
//     s32 i;
//
//     more = 1;
//     offset = &D_00AB1950;
//     tmp = &arg1;
//
//     for (i = arg0; i != 0; i--) {
//         tmp = ALIGN4(tmp) + 4;
//         if (more != 0) {
//             offset += func_1502AC88(offset, tmp - 4, &stack0);
//         }
//         more = *stack0 & 0xFFFFFFF;
//     }
//
//     if (more != 0) {
//         more = ALIGN2(stack0[0] & 0xFFFFFFF);
//         if ((*stack0 & 0x70000000) == 0x10000000) {
//             if (((s32) &stack1 & 8) != 0) {
//                 *stack1 = &stack2;
//             }
//             func_10004514(offset, stack1, 0x10, 1); // decompress?
//             more = *stack1;
//         }
//     }
//
//     return more;
// }
