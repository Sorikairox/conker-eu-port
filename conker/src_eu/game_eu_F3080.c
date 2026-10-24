#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
f32 func_15143E64(f32 *);
s32 memcpy(u8 *, s32, s32);

u8 *func_150C5870(s32 arg0, s32 arg1) {
    struct {
        f32 u20;
        f32 u24;
        f32 u28;
        u8 * u2C;
    } sp;
    u8 *temp_v0;

    temp_v0 = func_15167A68(0x46, 0, arg1 + 0xC8, 1, 0xFFU, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp.u2C = temp_v0;
    memcpy(temp_v0 + 0x18, arg0, 0x24);
    sp.u20 = (*(f32 *)((u8 *)temp_v0 + 0x18)) - (*(f32 *)((u8 *)temp_v0 + 0x24));
    sp.u24 = (*(f32 *)((u8 *)temp_v0 + 0x1C)) - (*(f32 *)((u8 *)temp_v0 + 0x28));
    sp.u28 = (*(f32 *)((u8 *)temp_v0 + 0x20)) - (*(f32 *)((u8 *)temp_v0 + 0x2C));
    (*(f32 *)((u8 *)sp.u2C + 0xC0)) = func_15143E64(&sp.u20);
    (*(s32 *)((u8 *)sp.u2C + 0x10)) = 1;
    (*(s32 *)((u8 *)sp.u2C + 0x14)) = 0;
    return sp.u2C;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C5870.s")
#endif
void func_150C5930(struct102 *arg0) {
    func_15169804(arg0);
}

void func_150C5950(struct102 *arg0) {
    func_15169824(arg0);
}

extern void (*D_80088B58[2])(void);
void func_150C5970(u8 *arg0) {
    s32 idx = *(u8 *)(arg0 + 0x38);

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 2) {
        idx = 0;
    }
    D_80088B58[idx]();
}

extern void (*D_80088B60[2])(void);
void func_150C59C0(u8 *arg0) {
    s32 idx = *(u8 *)(arg0 + 0x38);

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 2) {
        idx = 0;
    }
    D_80088B60[idx]();
}

void func_150C5A10(struct102 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0xC8));
    func_150C5930(arg0);
}

void func_150C5A3C(struct102 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0xC8));
    func_150C5950(arg0);
}

#ifdef NON_MATCHING
extern s32 (*D_80088B00[])(u8 *); /* motion handlers (func_150C6088, func_150C60D4) (index obj +0x30, -1 = none); 0 = remove the object */

/* object_motion_step: for an active object (flag word +0x10 bit 0), runs its motion handler D_80088B00[+0x30] (if
 * any); when the handler returns 0 the object is removed (func_1516972C). Otherwise, if the offset position +0x18 -
 * +0x24 (f32[3] each) changed across the handler, its length (func_15143E64) is stored in +0xC0. Table record word
 * 0x8008C680 (update slot), like its neighbours `void (struct102 *)`. */
void func_150C5A68(struct102 *obj) {
    u8 *o = (u8 *) obj;
    f32 dx, dy, dz;
    f32 d[3];
    u8 remove = 0;

    if (!(*(s32 *) (o + 0x10) & 1)) {
        return;
    }
    dx = *(f32 *) (o + 0x18) - *(f32 *) (o + 0x24);
    dy = *(f32 *) (o + 0x1C) - *(f32 *) (o + 0x28);
    dz = *(f32 *) (o + 0x20) - *(f32 *) (o + 0x2C);
    if (*(s8 *) (o + 0x30) != -1) {
        if (D_80088B00[*(s8 *) (o + 0x30)](o) == 0) {
            remove = 1;
        }
    }
    if (!remove) {
        d[0] = *(f32 *) (o + 0x18) - *(f32 *) (o + 0x24);
        d[1] = *(f32 *) (o + 0x1C) - *(f32 *) (o + 0x28);
        d[2] = *(f32 *) (o + 0x20) - *(f32 *) (o + 0x2C);
        if (d[0] != dx || d[1] != dy || d[2] != dz) {
            *(f32 *) (o + 0xC0) = func_15143E64(d);
        }
    }
    if (remove) {
        func_1516972C(obj);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C5A68.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C5BA4.s")

s32 func_150C6088(u8 *arg0) {
    u8 **temp_v1 = (u8 **)(arg0 + 0xC8);

    if (**(s32 **)(arg0 + 0xC8) == 0) {
        return 0;
    }
    *(f32 *)(arg0 + 0x24) = *(f32 *)(*temp_v1 + 0x14);
    *(f32 *)(arg0 + 0x28) = *(f32 *)(*temp_v1 + 0x18);
    *(f32 *)(arg0 + 0x2C) = *(f32 *)(*temp_v1 + 0x1C);
    return 1;
}

s32 func_150C60D4(u8 *arg0)
{
  u8 *temp_t0;
  u8 *temp_v0;
  u8 *temp_v1;
  temp_v0 = arg0;
  temp_v0 = temp_v0 + 0xC8;
  if ((*(*((s32 **) (((u8 *) arg0) + 0xC8)))) == 0)
  {
    return 0;
  }
  temp_v1 = *((u8 **) (((u8 *) temp_v0) + 0));
  if ((*((u8 *) (((u8 *) temp_v0) + 4))) != (*((u8 *) (((u8 *) temp_v1) + 0x3B))))
  {
    return 0;
  }
  ;
  if ((*((u8 **) (((u8 *) temp_v1) + 0x1D4))) == 0)
  {
    *((f32 *) (((u8 *) arg0) + 0x24)) = (f32) (*((f32 *) (((u8 *) temp_v1) + 0x14)));
    *((f32 *) (((u8 *) arg0) + 0x28)) = (f32) (*((f32 *) (((u8 *) (*((u8 **) (((u8 *) temp_v0) + 0)))) + 0x18)));
    *((f32 *) (((u8 *) arg0) + 0x2C)) = (f32) (*((f32 *) (((u8 *) (*((u8 **) (((u8 *) temp_v0) + 0)))) + 0x1C)));
  }
  else
  {
    func_15143134(temp_v0 + 8, arg0 + 0x24, ((*((u8 *) (((u8 *) temp_v0) + 5))) << 6) + (((s32) (*((u8 **) (((u8 *) temp_v1) + 0x1D4)))) ^ 0));
  }
  return 1;
}

void func_150C6174(s32 arg0) {
    func_1514D3B0(arg0, 0x15, 1, 0);
}

void func_150C619C(s32 arg0) {
    func_1514D3B0(arg0, 0x15, 2, 0);
}

void func_150C61C4(u8 *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(u8 *, s32, u8) = D_80088B68[arg0[0x38]];

    if (temp_v0 != NULL) {
        temp_v0(arg0, arg1, arg2);
    }
}

void func_150C620C(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v = arg0 + 0xC8;
    if (arg2 == 0) {
        if ((*(s32 *)v == arg1[0]) || (v[4] == ((u8 *)arg1)[4])) {
            func_1516972C(arg0);
        }
    } else {
        v = arg0 + 0xC8;
        if (arg2 == 0x2D) {
            if (arg1[0] == *(s32 *)v) {
                *(s32 *)v = arg1[1];
                v[4] = ((u8 *)arg1)[9];
            } else if (arg1[1] == *(s32 *)v) {
                *(s32 *)v = arg1[0];
                v[4] = ((u8 *)arg1)[8];
            }
        }
    }
}
