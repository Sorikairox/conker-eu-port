#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING
void func_1507D4F8(s32); /* P59: was implicitly int */
void func_1507F640(void); /* P60: idle animation, was implicitly int */
s32 func_151AABC4(struct127 *, s32); /* P192: C on port-b (returns 0), was implicit */
s32 func_150CA150(u8 *); /* P204: C on port-b (P201, returns 0), was implicit */
u8 *func_15196438(u8 *, s32, u8, s32); /* P230 (port-b P229): returns the emitter, was implicit */
#endif
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 func_151C0698();   /* still asm; called by func_15070300 */
void func_1507E7E4(struct127 *, u8, u8, u16, s32);
void func_1506BF5C(void);  /* P68 hand C; called by func_1506BF1C */
s32 func_151030B8(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
extern u8 D_eu_80099F30[];
extern u8 D_80099F3C[];
void func_150F9BB0(u8 *, u8, s32);        /* P238: port-b hand C (void); called by func_15071830 */
void func_150FA520(u8 *, u8, u8, s32);    /* P238: port-b hand C (void); called by func_15071998 / func_150719CC / func_15071A00 */
#endif


#ifdef NON_MATCHING
extern s32 D_8008679C;
extern u8 D_80099DF0;
extern u8 D_800C3A82;

f32 func_1506AD30(struct127 *arg0, f32 arg1, s32 arg2) {
    f32 *var_v1;
    f32 var_f0;
    f32 var_f20;
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_v0;
    s32 var_a2;
    struct197 *temp_a1;
    u8 *var_v0;
    u8 temp_v1;
    u8 var_a0;

    var_f20 = arg1;
    temp_s0 = arg2 & 0xFF;
    if (arg0->unk5 == 4) {
        return 0.0f;
    }
    D_800D1878 = 0.0f;
    if (var_f20 < arg0->unkB4) {
        arg0->unk138 = 0;
    }
    D_800D1880 = 1;
    temp_v0 = arg0->unk1C4;
    if (temp_v0 != 0) {
        var_v1 = temp_v0 + (arg0->unk138 * 0xC);
        var_f0 = *var_v1;
        if ((var_f0 <= var_f20) && (1 != 0)) {
loop_8:
            if (var_f0 < 900.0f) {
                D_800D1580 = (*(s32 *)((u8 *)var_v1 + 8));
                D_800D1874 = (*(f32 *)&(D_800D1580));
                temp_a1 = arg0->unk2D0;
                var_a2 = (*(s32 *)((u8 *)temp_a1 + 0x28));
                temp_s2 = var_a2;
                if ((D_800C35EA == 0) || (D_800C3A82 != 0)) {
                    var_a0 = (*(u8 *)((u8 *)((arg0->unk1C4 + (arg0->unk138 * 0xC))) + 7));
                    if ((temp_s0 != 0) && (temp_s0 != 0)) {
                        var_v0 = &D_80099DF0;
loop_14:
                        temp_v1 = *var_v0;
                        if (temp_v1 == 0) {
                            var_a0 = 0;
                        }
                        if (var_a0 != temp_v1) {
                            var_v0 += 1;
                            if (temp_s0 != 0) {
                                goto loop_14;
                            }
                        }
                    }
                    if (var_a0 != 0) {
                        (*(s32 (**)())((u8 *)&D_8008679C + (var_a0 * 4)))(var_a0, temp_a1, var_a2, &D_800D1880);
                        var_a2 = (*(s32 *)((u8 *)(arg0->unk2D0) + 0x28));
                    }
                }
                if (temp_s2 != var_a2) {
                    var_f20 = arg0->unk2D0->unk8;
                } else {
                    arg0->unk138 += 1;
                }
            }
            if (arg0->unk1C4 != 0) {
                var_v1 = arg0->unk1C4 + (arg0->unk138 * 0xC);
                var_f0 = *var_v1;
                if ((var_f0 <= var_f20) && (D_800D1880 != 0)) {
                    goto loop_8;
                }
            }
        }
    }
    return D_800D1878;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506AD30.s")
#endif
void func_1506AF74(void) {
    if ((D_800D154C->unk100 & 8) != 0) {
        D_800D154C->unk100 |= 4;
    }
    D_800D154C->unk100 &= 0xF7;
    func_1505E650(D_800D154C, 0x38, 1.0f, 5.0f, 0.0f, 0.0f, 0);
}

void func_1506AFE0(void) {
    func_1505E650(D_800D154C, 0x48, 1.0f, 5.0f, 0.0f, 0.0f, 0);
}

void func_1506B020(void) {
    D_800D154C->unk1CB = (u8)1;
    func_1505E650(D_800D154C, 0x39, 1.0f, 5.0f, 0.0f, 0.0f, 0);
}

void func_1506B070(void) {
}

void func_1506B078(void) {
    f32 tmp = (D_800D154C->y_position - (D_800D154C->unk118 - 150.0f)) * 0.005f;

    if (tmp < 0.0f) {
        tmp = 1.0f;
    } else {
        tmp +=  1.0f;
    }
    func_1506B100(0xD1, tmp, 4.0f);
}

// triggered when entering water?
void func_1506B100(s32 arg0, f32 arg1, f32 arg2) {
    func_1505E650(D_800D154C, arg0, arg1, arg2, 0.0f, 0.0f, 0);
}

void func_1506B14C(void) {
    func_1505E650(D_800D154C, D_800D154C->unk84.uh + 1, D_800D154C->animation_speed, 3.0f, 0.0f, 0.0f, 0);
}

void func_1506B198(void) {
    func_1505E650(D_800D154C, D_800D154C->unk84.uh + 1, D_800D154C->animation_speed, 3.0f, 0.0f, 0.0f, 1);
}

void func_1506B1E8(void) {
    func_1505E650(D_800D154C, 0x3C, 1.0f, 3.0f, 0.0f, 0.0f, 0);
}

void func_1506B228(void) {
    func_1505E650(D_800D154C, 0x54, 1.0f, 3.0f, 0.0f, 0.0f, 0);
}

void func_1506B268(void) {
    D_800D154C->unk83 = 0;
    D_800D154C->disable_run = 0;
    func_1505E650(D_800D154C, 0xF, 1.0f, 6.0f, 0.0f, 0.0f, 0);
}

void func_1506B2BC(void) {
    struct127 *temp_v0 = func_150721E8(D_800D154C);
    if ((temp_v0 != 0) && (((((s32)temp_v0 - (s32)&D_800CC2D0) / 0x32C) + 1) == D_800CC2D0[0].unk274)) {
        D_800D154C->unk218 = 0;
        D_800D154C->unk232 = (u8)4;
    }
}

void func_1506B328(void) {
    func_1505E650(D_800D154C, 0x3E, 1.0f, 5.0f, 0.0f, 0.0f, 0);
}

void func_1506B368(void) {
}

void func_1506B370(void) {
    // return index of D_800D154C in structs array
    func_1507D4F8(((s32)D_800D154C - (s32)D_800CC2D0) / (s32)sizeof(struct127));
}

void func_1506B3B0(void) {
}

#ifdef NON_MATCHING
extern u8 D_80099DFE;
extern u8 D_80099E03;

void func_1506B3B8(void) {
    u8 sp19;
    s16 temp_t0;
    s32 temp_a3;
    s32 temp_v1;
    s32 var_a0_2;
    s32 var_a2;
    u8 var_a0;

    sp19 = 0;
    var_a0 = sp19;
    temp_t0 = (D_800D154C->unk7A + (D_800D154C->unk1FD << 8)) - func_1505A630(D_800CC2D0->x_position - D_800D154C->x_position, D_800D154C->z_position - D_800CC2D0->z_position, 0);
    temp_v1 = temp_t0 >> 8;
    temp_a3 = temp_v1 & 0xFF;
    var_a2 = temp_v1 & 0xFF;
    if (temp_a3 & 0x80) {
        var_a2 = -temp_a3 & 0xFF;
    }
    if (var_a2 < (s32) D_80099DFC[0][0]) {
        var_a0_2 = 1;
    } else {
        if ((s32) D_80099E03 < var_a2) {
            var_a0 = 5;
        } else if ((s32) D_80099DFE < var_a2) {
            var_a0 = 2;
        }
        if (temp_t0 < 0) {
            var_a0_2 = (var_a0 + 4) & 0xFF;
        } else {
            var_a0_2 = (var_a0 + 3) & 0xFF;
        }
    }
    D_800D154C->unk138 = 0;
    D_800D154C->unk244 = (s16) (*D_80099DFC)[var_a0_2];
    D_800D154C->unk21C = 0x4E20;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B3B8.s")
#endif
// NON-MATCHING: 5% there...
// void func_1506B3B8(void) {
//     u8 sp19;
//     s16 temp_t0;
//     s32 temp_a3;
//     s32 temp_v0;
//     s32 temp_v1;
//     struct127 *temp_a1;
//     struct127 *temp_a1_2;
//     s32 phi_a2;
//     s32 phi_a0;
//     u8 phi_a0_2;
//
//     temp_a1 = D_800D154C;
//     sp19 = 0;
//     temp_a1_2 = D_800D154C;
//     temp_t0 = (temp_a1_2->unk7A + (temp_a1_2->unk1FD << 8)) - func_1505A630(D_800CC2D0[0].x_position - temp_a1->x_position, temp_a1->z_position - D_800CC2D0[0].z_position, temp_a1, 0);
//     temp_v1 = (s32) temp_t0 >> 8;
//     temp_a3 = temp_v1 & 0xFF;
//     phi_a2 = temp_v1 & 0xFF;
//     if ((temp_a3 & 0x80) != 0) {
//         phi_a2 = -temp_a3 & 0xFF;
//     }
//     temp_v0 = phi_a2;
//     if (phi_a2 < (s32) D_80099A3C) {
//         phi_a0 = 1;
//     } else {
//         if ((s32) D_80099A43 < temp_v0) {
//             phi_a0_2 = (u8)5U;
//         } else {
//             phi_a0_2 = sp19;
//             if ((s32) D_80099A3E < temp_v0) {
//                 phi_a0_2 = (u8)2U;
//             }
//         }
//         if ((s32) temp_t0 < 0) {
//             phi_a0 = (phi_a0_2 + 4) & 0xFF;
//         } else {
//             phi_a0 = (phi_a0_2 + 3) & 0xFF;
//         }
//     }
//     temp_a1_2->unk138 = (u8)0;
//     D_800D154C->unk244 = (s16) D_80099A3C[phi_a0]; // + 0x800A0000)->unk-65C4;
//     D_800D154C->unk21C = (u16)0x4E20;
// }

void func_1506B4EC(void) {
    func_1506B3B8();
}

void func_1506B50C(void) {
    D_800D154C->unk21C = 0;
}

void func_1506B520(void) {
    s32 tmp;

    if (D_800D154C->health != 0) {
        if ((D_800D154C->unk31C != 0) && (D_800D154C->unk31C->unk78 == 0x25)) {
            tmp = 427;
        } else {
            tmp = 240;
        }
        func_1505E650(D_800D154C, tmp, 1.5f, 3.0f, 0.0f, 0.0f, 0);
    } else {
        func_1507CD64(D_800D154C, 1);
    }
}

void func_1506B5A4(void) {
}

void func_1506B5AC(void) {
}

void func_1506B5B4(void) {
    D_800D154C->unk1CB = (u8)1;
}

void func_1506B5CC(void) {
    D_800D154C->unk1CB = (u8)1;
}

void func_1506B5E4(void) {
    func_1506160C(D_800D154C, 2, 7, 8, 0);
    D_800D154C->animation_speed = 0.0f;
    D_800D154C->unk2D0->unk10 = 0.0f;
}

void func_1506E8D8(void);

void func_1506B634(u8 arg0) {
    u8 i;
    struct126 *p;

    i = (u32)func_150ADA20() % arg0;
    p = D_800D154C->unk31C;
    if (p->unk16 != 0) {
        if ((D_800BE9F0 == 0x29) && (i == 7)) {
            i = 0;
        }
        p->unkE = D_80099E7C[i];
    } else {
        p->unkE = D_80099E74[i];
    }
    if (D_800D154C->unk31C->unkE == 0xA7) {
        D_800D1580 = 0xFF020144;
        D_800D154C->unk31C->unkC = (func_150ADA20() % 3U) + 2;
        func_1506E8D8();
        D_800D154C->xz_velocity *= 0.2f;
    }
}
// NON-MATCHING: miles away
// void func_1506B634(u8 arg0) {
//     s32 temp_a0;
//     u32 temp_hi;
//     struct126 *temp_a1;
//     s32 phi_a0;
//     s32 phi_a0_2;
//
//     temp_hi = func_150ADA20() % (u32) arg0;
//     temp_a0 = temp_hi & 0xFF;
//     temp_a1 = D_800D154C->unk31C;
//     if (temp_a1->unk16 != 0) {
//         phi_a0 = temp_a0;
//         if (D_800BE9F0 == 0x29) {
//             phi_a0 = temp_a0;
//             if ((temp_hi & 0xFF) == 7) {
//                 phi_a0 = 0;
//             }
//         }
//         temp_a1->unkE = (s16) D_80099ABC[phi_a0]; // + 0x800A0000)->unk-6544;
//         phi_a0_2 = phi_a0;
//     } else {
//         temp_a1->unkE = (s16) D_80099AB4[(temp_hi & 0xFF)]; // + 0x800A0000)->unk-654C;
//         phi_a0_2 = temp_a0;
//     }
//     if (D_800D154C->unk31C->unkE == 0xA7) {
//         D_800D1580 = 0xFF020144; // 4278321476
//         D_800D154C->unk31C->unkC = (func_150ADA20(phi_a0_2, temp_a1, &D_800D154C) % 3U) + 2;
//         func_1506E8D8();
//         D_800D154C->xz_velocity = (f32) (D_800D154C->xz_velocity * D_80099C38);
//     }
// }

void func_1506B740(void) {
    u8 res = func_150ADA20() & 0xFF;

    if ((-10000.0f != D_800D154C->unk118) && (D_800D154C->y_position < D_800D154C->unk118)) {
        D_800D154C->unk31C->unkE = 0x2D0;
    } else {
        if (D_800D154C->unk84.uh == 0xA7) {
            if (D_800D154C->unk31C->unkC == 0) {
                res = 0;
            } else {
                D_800D154C->unk31C->unkC--;
                res = 0xFF;
            }
        }
        if (res < 0x80) {
            func_1506B634(8);
        }
    }
}

void func_1506B7F4(void) {
    D_800D154C->disable_run = 0;
    D_800D154C->unk83 = 0;
    func_1506B634(2);
}

void func_1506B82C(void) {
    D_800D154C->disable_run = 0;
    D_800D154C->unk83 = 0;
    func_1507F640();
}

void func_1506B860(void) {
    func_1506B100(181, 0.6299999952316284f, 5.0f);
}

void func_1506B88C(void) {
    func_1506B100(182, 1.0f, 4.0f);
}

void func_1506B8B4(void) {
    D_800D154C->unk31C->unk78 = (u8)0;
    D_800D154C->disable_run = (u8)0;
    D_800D154C->unk83 = (u8)0;
    func_1507F640();
}

void func_1506B8F4(void) {
    func_1506B100(222, 0.75f, 4.0f);
}

void func_1506B91C(void) {
    func_1506B100(191, 1.0f, 4.0f);
}

void func_1506B944(void) {
    D_800D154C->disable_run = (u8)0;
    D_800D154C->unk83 = (u8)0;
    func_1506B100(0xC5, 1.0f, 4.0f);
}

void func_1506B984(void) {
    func_1506B100(0xAF, 1.0f, 4.0f);
}

void func_1506B9AC(void) {
    D_800D154C->unk244 = (u16)0;
}

void func_1506B9C0(void) {
    struct126 *temp_a0;

    D_800BE720[D_800C3E78] |= 0x4000;
    temp_a0 = D_800D154C->unk31C;
    if (temp_a0 != 0) {
        temp_a0->unk78 = 0;
        D_800D2E60[D_800D1940 >> 3] |=  (1 << (D_800D1940 & 7));
    }
#ifdef NON_MATCHING
    func_1507F640(); /* takes no arguments (a0 is left over) */
#else
    func_1507F640(temp_a0);
#endif
}

void func_1506BA4C(s32 arg0, s32 arg1) {
    if (D_800D1580 == 0) {
        func_100109D0(D_800D154C);
    } else {
        if (D_800D154C->camera == 0) {
            func_10010154(D_800D1580, D_800D154C, 28000, arg0, arg1);
        } else {
            func_10010154(D_800D1580, D_800D154C, 24000, 500, 2500);
        }
    }
}

void func_1506BAD8(s32 arg0, s32 arg1) {
    if (D_800D1580 == 0) {
        func_10010A3C(D_800D154C);
    } else {
        if (D_800D154C->camera == 0) {
            func_10010344(D_800D1580, D_800D154C, 28000, arg0, arg1);
        } else {
            func_10010344(D_800D1580, D_800D154C, 24000, 500, 2500);
        }
    }
}

void func_1506BB64(s32 arg0, s32 arg1) {
    func_10012718(D_800D1582, D_800D154C, 28000, arg0, arg1);
}

void func_1506BBA8(s32 arg0, s32 arg1) {
    if (D_800D154C->camera == 0) {
        func_10010154(D_800D1582, D_800D154C, 14000, arg0, arg1);
    } else {
        func_10010154(D_800D1582, D_800D154C, 12000, 500, 2500);
    }
}

void func_1506BC24(s32 arg0, s32 arg1) {
    if (D_800D154C->camera == 0) {
        func_10010344(D_800D1582, D_800D154C, 0x36B0, arg0, arg1);
    } else {
        func_10010344(D_800D1582, D_800D154C, 0x2EE0, 0x1F4, 0x9C4);
    }
}

void func_1506BCA0(void) {
    D_800D154C->y_velocity = D_800D1580;
}

// ???
s32 func_151EFDD0(void);
void func_1506BCC8(void)
{
  struct127 *p;
  f32 d;
  f32 v;
  if (D_800D154C->interaction_state == 0x16)
  {
    if (D_800D154C->y_position == D_800D154C->unk180)
    {
      D_800D154C->y_velocity = (f32) ((func_151EFDD0() % 8) + D_800D1580);
      if (0.0f != D_800D154C->xz_velocity)
      {
        D_800D154C->y_velocity = D_800D154C->y_velocity * (D_800D154C->xz_velocity / 40.0f);
      }
      else
      {
        D_800D154C->y_velocity = 0.0f;
      }
    }
  }
  else
  {
    p = D_800D154C;
    d = p->y_position - p->unk180;
    if ((d > (-5.0f)) && (d < 5.0f))
    {
      p->y_velocity = (f32) D_800D1580;
    }
  }
}

void func_1506BDE8(void) {
    if (D_800D154C->y_position < -1750.0f) {
        D_800D154C->y_velocity = (f32) D_800D1580;
    }
}

void func_1506BE2C(void) {
    D_800D154C->gravity = D_800D1580;
}

void func_1506BE54(void) {
    D_800D154C->gravity = D_800D1580 * 0.1f;
}

void func_1506BE84(void) {
    D_800D154C->disable_run = 0;
}

void func_1506BE98(void) {
    D_800D154C->target_speed = D_800D1580;
}

void func_1506BEC0(void) {
    D_800D154C->disable_run = D_800D1580;
}

void func_1506BEDC(void) {
    D_800D154C->unkD0 = D_800D1580;
    D_800D154C->unk114 = (f32) ((s32) D_800D1580 >> 8);
}

void func_1506BF1C(void) {
    if (D_800D154C->unk118 <= D_800D154C->y_position) {
        func_1506BF5C();
    }
}

#ifdef NON_MATCHING
/* Script command: play a sound for the current object D_800D154C. Command word D_800D1580:
 *   bits 0..10 sound id, 11..13 how to play it, 14..15 actor condition, 16 "defer", 24..31 actor type.
 * Condition 0x4000: only when the object's actor type (its id, or the alias D_8008704C[...] when
 * D_800D1C90[id]->unk4 is set) equals bits 24..31; 0x8000: only when it differs. With bit 16 the command
 * word + 1 is stored in D_800D1C9C (which is cleared otherwise) and nothing plays.
 * Modes (volume 0x7D00, 500 / 2500 = the distance / time arguments of the sound calls):
 *   0x0000 func_10010154, 0x1000 func_10010344, 0x3000 func_10010630,
 *   0x3800 func_10010154 unless func_1001147C(obj->unk8E) already returns that sound,
 *   0x2000 footstep (at most 1 player, D_80082FA0 < 2): the sound comes from the floor surface
 *          (func_1510FE4C(obj->unk184) -> func_10011EB8, which may also lower the volume; in the air: surface 8;
 *          surface 12 = water while obj->unkCC > -17: func_1000F568(0x9C, 2)); the volume scales with the
 *          fall speed (obj->unk31C's first float, else y_velocity), 0.5 .. 1.0 over 0 .. 10 (water) or 30.
 *          Surface 8 plays with func_10010630, the others with func_10010154. */
extern s32 D_800D1C9C;
extern u8 *D_8008704C[];
s32 func_1000F568(s32, s32);
s32 func_10011EB8(s32 surface, u16 *volume, s32 sound);

void func_1506BF5C(void) {
    s32 cmd = D_800D1580;
    struct127 *obj = D_800D154C;
    s32 sound = cmd & 0x7FF;          /* sp4C, played as its low half */
    s32 want = (u32)cmd >> 24;
    s32 type = obj->id;
    s32 mode;
    s32 surface;
    u16 volume;                       /* sp46 */
    f32 speed;
    f32 limit;
    f32 scale;

    if (D_800D1C90[type]->unk4 != 0) {
        type = *D_8008704C[D_800D1C90[type]->unk5];
    }
    D_800D1C9C = 0;
    if ((cmd & 0xC000) == 0x4000) {
        if (type != want) {
            return;
        }
    } else if ((cmd & 0xC000) == 0x8000) {
        if (type == want) {
            return;
        }
    }
    if (cmd & 0x10000) {
        D_800D1C9C = cmd + 1;
        return;
    }

    volume = 0x7D00;
    mode = cmd & 0x3800;
    if (mode == 0x0000) {
        func_10010154(sound, obj, volume, 500, 2500);
        return;
    }
    if (mode == 0x1000) {
        func_10010344(sound, obj, 0x7D00, 500, 2500);
        return;
    }
    if (mode == 0x3000) {
        func_10010630(sound, obj, 0x7D00, 500, 2500);
        return;
    }
    if (mode == 0x3800) {
        if (func_1001147C(obj->unk8E) != sound) {
            func_10010154(sound, D_800D154C, volume, 500, 2500);
        }
        return;
    }
    if (mode != 0x2000) {
        return;
    }

    /* footstep */
    if (D_80082FA0 >= 2) {
        return;
    }
    surface = func_1510FE4C(obj->unk184);
    if (surface == 12 && -17.0f < D_800D154C->unkCC) {
        sound = func_1000F568(0x9C, 2);
    } else if (D_800D154C->unk118 != -10000.0f && D_800D154C->unk118 >= D_800D154C->y_position) {
        sound = func_10011EB8(8, NULL, sound);
        surface = 8;
    } else {
        sound = func_10011EB8(surface, &volume, sound);
    }
    if (sound == 0) {
        return;
    }
    obj = D_800D154C;
    if (obj->unk31C != NULL) {
        speed = *(f32 *)obj->unk31C;
    } else {
        speed = obj->y_velocity;
    }
    limit = (surface == 12) ? 10.0f : 30.0f;
    if (limit < speed) {
        speed = limit;
    }
    scale = 0.5f / limit;
    if (speed < 0.0f) {
        speed = 0.0f;
    }
    volume = (u32)volume * (speed * scale + 0.5f);
    if (surface == 8) {
        func_10010630(sound, obj, volume, 500, 2500);
        return;
    }
    func_10010154(sound, obj, volume, 500, 2500);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BF5C.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800D1C9C;
s32 func_1000F568(s32, s32);

/*
 * P80: script command "random jump": while the counter D_800D1C9C is not 0, count it down and pick one of up to four
 * 11-bit targets: the counter's own low 11 bits (after the decrement) and the command word's fields 0..10 / 11..21
 * / 22..32; with n = the highest non-zero field (2 / 3 / 4, else 0) the pick is func_1000F568(base, n) - base.
 * A non-zero pick goes into D_800D1580 (with the counter's bits other than 0..10 and 16) and func_1506BF5C runs.
 */
void func_1506C32C(void) {
    s32 v[4];
    s32 n;
    s32 keep;

    if (D_800D1C9C == 0) {
        return;
    }
    D_800D1C9C--;
    v[0] = D_800D1C9C & 0x7FF;
    v[1] = D_800D1580 & 0x7FF;
    v[2] = (D_800D1580 >> 11) & 0x7FF;
    v[3] = (D_800D1580 >> 22) & 0x7FF;
    if (v[3] != 0) {
        n = 4;
    } else if (v[2] != 0) {
        n = 3;
    } else if (v[1] != 0) {
        n = 2;
    } else {
        n = 0;
    }
    if (n != 0) {
        n = func_1000F568(v[0], n) - v[0];
    }
    if (v[n] != 0) {
        keep = D_800D1C9C & 0xFFFEF800;
        D_800D1C9C = keep;
        D_800D1580 = v[n] | keep;
        func_1506BF5C();
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506C32C.s")
#endif

void func_1506C418(void) {
    func_10010A3C(D_800D154C);
}

void func_1506C43C(void) {
    func_100109D0(D_800D154C);
}

// requires jump table
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506C460.s")
// requires jump table
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506CE6C.s")

#ifdef NON_MATCHING
extern f32 D_8009A104;
void func_151A3940(u8 *, u8);

void func_1506D2E8(void) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
    } sp;
    f32 sp2C;
    f32 var_f0;
    struct127 *temp_v0;
    u16 temp_v0_2;

    temp_v0 = func_1505EEF4(func_15083E0C(D_800D1580 & 0xFF));
    if (temp_v0 != NULL) {
        sp2C = 0.0f;
        func_151A3940(temp_v0, 0xFF);
        var_f0 = 0.0f;
        if (D_800D1580 & 0xFF00) {
            var_f0 = D_800D154C->camera->unk780 - 15.0f;
        }
        temp_v0_2 = D_800D154C->unk7A;
        temp_v0->unk78 = temp_v0_2;
        temp_v0->unk7A = temp_v0_2;
        temp_v0->unk76 = temp_v0_2;
        func_1505A184(temp_v0_2 & 0xFFFF, 5000.0f, var_f0, &sp.u40, &sp.u3C, &sp.u38);
        (*(s16 *)((u8 *)(D_800D2104[temp_v0->unk13F]) + 8)) = (s16) (s32) (D_800D154C->x_position + sp.u40);
        (*(s16 *)((u8 *)(D_800D2104[temp_v0->unk13F]) + 0xC)) = (s16) (s32) (D_800D154C->z_position + sp.u3C);
        (*(s16 *)((u8 *)(D_800D2104[temp_v0->unk13F]) + 0xA)) = (s16) (s32) (D_800D154C->y_position + sp.u38);
        temp_v0->unk65 = 0;
        temp_v0->unk218 = NULL;
        if (D_800D1580 & 0xFF00) {
            temp_v0->unk232 = 4;
            temp_v0->xz_scale = 0.25f;
            temp_v0->y_scale = 0.25f;
            temp_v0->y_position = D_800D154C->y_position + 70.0f;
            return;
        }
        temp_v0->unk232 = 2;
        temp_v0->xz_velocity = -15.0f;
        temp_v0->y_velocity = 34.0f;
        temp_v0->xz_scale = 0.5f;
        temp_v0->y_scale = 0.5f;
        temp_v0->gravity = D_8009A104;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D2E8.s")
#endif
// NON-MATCHING: plenty to figure out here
// void func_1506D2E8(void) {
//     f32 sp40;
//     f32 sp3C;
//     f32 sp38;
//     f32 sp2C;
//     u16 temp_v0_2;
//     struct127 *temp_s0;
//     f32 phi_f0;
//
//     temp_s0 = func_1505EEF4(func_15083E0C(D_800D1580 & 0xFF));
//     if (temp_s0 != NULL) {
//         sp2C = 0.0f;
//         func_151A3390(temp_s0, 0xFF);
//         phi_f0 = 0.0f;
//         if ((D_800D1580 & 0xFF00) != 0) {
//             phi_f0 = D_800D154C->camera->unk780 - 15.0f;
//         }
//         temp_v0_2 = D_800D154C->unk7A;
//         temp_s0->unk78 = temp_v0_2;
//         temp_s0->unk7A = temp_v0_2;
//         temp_s0->unk76 = temp_v0_2;
//         func_1505A184(temp_v0_2, 5000.0f, phi_f0, &sp40, &sp3C, &sp38);
//         D_800D2104[temp_s0->unk13F]->unk8 = (s16) (s32) (D_800D154C->x_position + sp40);
//         D_800D2104[temp_s0->unk13F]->unkC = (s16) (s32) (D_800D154C->z_position + sp3C);
//         D_800D2104[temp_s0->unk13F]->unkA = (s16) (s32) (D_800D154C->y_position + sp38);
//         temp_s0->unk65 = (u8)0;
//         temp_s0->unk218 = 0;
//         if ((D_800D1580 & 0xFF00) != 0) {
//             temp_s0->unk232 = (u8)4;
//             temp_s0->unk14C = 0.25f;
//             temp_s0->unk150 = 0.25f;
//             temp_s0->y_position = (f32) (D_800D154C->y_position + 70.0f);
//         } else {
//             temp_s0->unk232 = (u8)2;
//             temp_s0->xz_velocity = -15.0f;
//             temp_s0->y_velocity = 34.0f;
//             temp_s0->unk14C = 0.5f;
//             temp_s0->unk150 = 0.5f;
//             temp_s0->gravity = (f32) D_80099D44;
//         }
//     }
// }

void func_1506D4F4(void) {
    func_1505E650(D_800D154C, D_800D154C->unk84.uh, 0.009999999776482582f, 0.0f, 0.0f, 0.0f, 0);
}

void func_1506D538(void) {
    if (D_800C35EA != 1) {
        func_1507D4F8(D_800C3E78);
    }
}

void func_1506D570(void) {
    D_800D154C->unk6E = 0;
}

#ifdef NON_MATCHING
/* Re-issue the current object's packed command D_800D1580 (bytes 3 and 2, low half = a duration in
 * frames scaled by the speed at unk2D0 + 0x10, 0xFFFF = none) through func_1507E7E4, unless the object
 * is in state 0x2A (P15, hand C). The asm returns junk (a %hi) on the early path, so this is void. */
void func_1506D584(void) {
    struct127 *obj = D_800D154C;
    f32 speed;
    u16 t;

    if (obj->unk70 == 0x2A) {
        return;
    }
    speed = *(f32 *)((u8 *)obj->unk2D0 + 0x10);
    if (speed == 0.0f) {
        speed = D_8009A108;
    }
    t = D_800D1580 & 0xFFFF;
    if (t != 0xFFFF) {
        t = (u32)(t / speed);
    }
    func_1507E7E4(obj, D_800D1580 >> 24, D_800D1580 >> 16, t, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D584.s")
#endif
// ???
void func_1506D6B4(void) {
    s32 var_v0;

    if ((-10000.0f != D_800D154C->unk118) && !(D_800D154C->unk118 < D_800D154C->unk1A6)) {
        if (D_800D154C->health >= 2) {
            var_v0 = 0x2C;
        } else {
            var_v0 = 0x29;
        }
        D_800D1580 = ((var_v0 & 0xFF) << 0x18) | (D_800D1580 & 0xFFFF);
        func_1506D584();
    }
}
void func_1506D74C(void) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    if (D_800D154C->in_water == 0) {
        D_800D154C->gravity = 5.0f;
        D_800D154C->y_velocity = 0.0f;
    }
    D_800D154C->y_position += 70.0f;
    (*(s8 *)((u8 *)D_800D154C + 0x137)) = 0;
    D_800D154C->disable_run = 0;
    func_1505A184(D_800D154C->unk76, (f32) D_800D1580, 0.0f, &sp34, &sp30, &sp2C);
    func_1505E650(D_800D154C, 0xFU, 1.0f, 0.0f, 0.0f, 0.0f, 0);
    D_800D154C->x_position += sp34;
    D_800D154C->z_position += sp30;
    D_800D154C->unk100 |= 2;
    D_800D154C->unk28 = 0.0f;
    D_800D154C->unk83 = 0x14;
    D_800D154C->unk31C->unk44 = 0xC;
    D_800D154C->unk31C->unk54 = 0xA;
}

void func_1506D898(void) {
    D_800D154C->y_position -= 80.0f;
    func_1505E650(D_800D154C, 663, 1.0f, 0.0f, 0.0f, 0.0f, 0);
    D_800D154C->unk100 &= 0xFFDF;
    D_800D154C->unk83 = 0;
    D_800D154C->disable_run = 0;
    D_800D154C->unk31C->unk97 = 0;
    D_800D154C->unk31C->unk44 = 12;
}

void func_1506D934(void) {
    D_800D154C->unk103 = D_800D1580;
}

void func_1506D950(void) {
}

void func_1506D958(s32 arg0) {
    s32 i;
    s32 id;

    id = D_800D1580 & 0xFF;
    arg0 = (D_800D1580 >> 8) & 0xFF;
    for (i = 0; i < 25; i++) {
        if ((D_800CC2D0[i].interaction_state != 0) && (id == D_800CC2D0[i].unkAB) && ((D_800C3E78 + 1) == D_800CC2D0[i].unk65)) {
            D_800CC2D0[i].unk101 &= 0xFFFE;
            D_800CC2D0[i].unk101 |= arg0;
            return;
        }
    }
}

void func_1506DA78(void) {
    D_800D154C->immune = D_800D1580;
}

void func_1506DA94(void) {
    if (D_800D1580 != 0) {
        if ((D_800D154C->unk44 > 20.0f) && (D_800D154C->xz_velocity > 20.0f)) {
            D_800D154C->unk83 = (u8)0;
        }
    }
    func_15174690(D_800C3E78, 0, 24, 0, 409, 4, 170, 0xFF, 0);
}

void func_1506DB30(void) {
    D_800D1890 = (s8) D_800D1580;
    func_15076760();
}

void func_1506DB5C(void) {
    D_800D154C->xz_velocity = (f32) D_800D1580;
}

void func_1506DB84(void) {
    D_800D154C->unk239 = (s8) D_800D1580;
}

void func_1506DBA0(void) {
    D_800D154C->unk1E5 = D_800D1580 & 0xff;
    D_800D154C->unk1E6 = (D_800D1580 >> 8) & 0xff;
}

void func_1506DBD4(void) {
    struct127 *temp_v0 = func_15072208(D_800D154C, 0);
    if (temp_v0 != NULL) {
        func_15054A5C(temp_v0, D_800D154C);
    }
}

void func_1506DC10(void) {
    s32 v;
    s32 a;

    if (((D_800D154C->unk118 - 60.0f) < D_800D154C->y_position) || (-10000.0f == D_800D154C->unk118)) {
        v = func_150ADA20() & 3;
        if (v >= 2) {
            a = v + 0x612;
        } else {
            a = v + 0x8F;
        }
    } else {
        a = 9;
    }
    func_15060A9C(a, D_800D154C);
}

void func_1506DCA4(void) {
    D_800D154C->unk2E8 = D_800D1580;
}

void func_1506DCC0(void) {
    D_800D154C->unk2EC = (s32) D_800D1580;
}

void func_1506DCDC(void) {
    D_800D154C->health = (s8) D_800D1580;
}

void func_1506DCF8(void) {
}

void func_1506DD00(void) {
    struct127 *temp_v1;

    if (D_800D1580 == 0) {
        temp_v1 = D_800D154C;
        temp_v1->unkF8 = (s32) temp_v1->unk144->unk18;
    } else {
        temp_v1 = D_800D154C;
        temp_v1->unkF8 |= D_800D1580;
    }
}

void func_1506DD44(void) {
    D_800D154C->unkF8 &= ~D_800D1580;
}

void func_1506DD6C(void) {
    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->matrix_physics = D_800D1580 & 0x7F;
    }
    if (D_800D1580 == 0) {
        D_800D154C->unk76 = D_800D154C->unk7A;
    }
}

void func_1506DDB8(void) {
}

void func_1506DDC0(void) {
    if (func_15178E50(D_800BE9F0) != 0) {
        func_1516EED4(D_800C3E78, D_800D1580, 0xFF, 0);
    }
}

void func_1506DE04(void) {
    s32 i;
    for(i = 0; i < 2; i++) {
        func_15174690(D_800C3E78, 10, 18, 12, 0x199, 4, 0xAA, 0xFF, 0);
    }
}

// jump table
void func_1506E0EC(void);
void func_1506E2CC(void);
s32 func_150B0290();
s32 func_150B0344(s32);
void func_1516F730(s32, s32, u8, s32);
s32 func_1516F868(u8, s32, s32, s32, u8, s32);
#ifdef NON_MATCHING
void func_15187B50(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7);
#else
s32 func_15187B50(f32, f32, f32, s32, s32, s32, f32, f32);
#endif

void func_1506DE84(void) {
    switch (D_800D1580) {
    case 0:
        if (D_800D154C->unk28 == 0.0f) {
            func_15187B50(D_800D154C->x_position, D_800D154C->y_position, D_800D154C->z_position, 0x1E, 0x1E, 7, 0.1f, 0.1f);
            return;
        }
    default:
        return;
    case 1:
        if ((u32) (func_150ADA20() & 0xFF) < 0x40U) {
            func_15187B50(D_800D154C->x_position, D_800D154C->y_position, D_800D154C->z_position, 0xA, 0x14, 7, 0.03f, 0.02f);
            D_800D1580 = 0x106;
            func_1506BA4C(0x12C, 0x708);
            return;
        }
        break;
    case 2:
        func_1516F730(D_800C3E78, 0x10, 0xFF, 0);
        return;
    case 3:
        func_1516F730(D_800C3E78, 0x28, 0xFF, 0);
        return;
    case 4:
        func_1516F730(D_800C3E78, 0x28, 0xFF, 0);
        return;
    case 5:
        func_1516F868(D_800C3E78, 0x1E, 0x14, 2, 0xFF, 0);
        return;
    case 6:
        func_1516F868(D_800C3E78, 0x12, 0xC, 2, 0xFF, 0);
        return;
    case 7:
        func_1516F868(D_800C3E78, 0x3C, 0x78, 2, 0xFF, 0);
        return;
    case 8:
        func_1506E0EC();
        return;
    case 9:
        func_150B0344(0);
        return;
    case 10:
        func_150B0344(1);
        return;
    case 11:
        func_1506E2CC();
        return;
    case 12:
        func_1516F868(D_800C3E78, 0x12, 0xC, 0, 0xFF, 0);
        return;
    case 13:
        func_150B0290();
        break;
    }
}

#ifdef NON_MATCHING
void func_150A7E40(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);
void func_15187B50(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7);
void func_15170648(f32 *quad, f32 x, f32 z, s32 arg3, f32 size, s32 arg5, s32 arg6, s32 arg7, s32 alpha, s32 arg9);

/*
 * P85: script command 8: as func_1506E2CC (command 11) with a 540 x 540 square (corners (+-270, 0, +-270) through
 * the object matrix +0x1D4, at the object's height +0x180); each corner also goes to func_15187B50 (corner x,
 * transformed y, z, 30, 20, 7, 0.13, 0.1), and func_15170648 gets 4 and the full +0x14C size.
 */
void func_1506E0EC(void) {
    f32 quad[4][3];
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    if (*(void **) ((u8 *) D_800D154C + 0x1D4) == NULL) {
        return;
    }
    x = 270.0f;
    z = 270.0f;
    for (i = 0; i < 4; i++) {
        y = 0.0f;
        func_150A7E40(*(f32 (**)[4]) ((u8 *) D_800D154C + 0x1D4), x, 0.0f, z, &x, &y, &z);
        quad[i][0] = x;
        quad[i][1] = *(f32 *) ((u8 *) D_800D154C + 0x180);
        quad[i][2] = z;
        func_15187B50(x, y, z, 30, 20, 7, 0.13f, 0.1f);
        if (i == 0) {
            z = 270.0f;
            x = -270.0f;
        } else if (i == 1) {
            x = -270.0f;
            z = -270.0f;
        } else if (i == 2) {
            x = 270.0f;
            z = -270.0f;
        }
    }
    func_15170648(&quad[0][0], *(f32 *) ((u8 *) D_800D154C + 0x14), *(f32 *) ((u8 *) D_800D154C + 0x1C), 4,
                  *(f32 *) ((u8 *) D_800D154C + 0x14C), 0, 4, 4, 0xFF, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E0EC.s")
#endif
#ifdef NON_MATCHING
void func_150A7E40(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);
void func_15170648(f32 *quad, f32 x, f32 z, s32 arg3, f32 size, s32 arg5, s32 arg6, s32 arg7, s32 alpha, s32 arg9);

/*
 * P85: script command 11: a 200 x 200 square around the current object (D_800D154C) in its model space
 * (corners (+-100, 0, +-100) through the object matrix +0x1D4, at the object's height +0x180) is passed to
 * func_15170648 with the object position (+0x14 / +0x1C) and half the object's +0x14C size. Nothing without a matrix.
 */
void func_1506E2CC(void) {
    f32 quad[4][3];
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    if (*(void **) ((u8 *) D_800D154C + 0x1D4) == NULL) {
        return;
    }
    x = 100.0f;
    z = 100.0f;
    for (i = 0; i < 4; i++) {
        y = 0.0f;
        func_150A7E40(*(f32 (**)[4]) ((u8 *) D_800D154C + 0x1D4), x, 0.0f, z, &x, &y, &z);
        quad[i][0] = x;
        quad[i][1] = *(f32 *) ((u8 *) D_800D154C + 0x180);
        quad[i][2] = z;
        if (i == 0) {
            z = 100.0f;
            x = -100.0f;
        } else if (i == 1) {
            x = -100.0f;
            z = -100.0f;
        } else if (i == 2) {
            x = 100.0f;
            z = -100.0f;
        }
    }
    func_15170648(&quad[0][0], *(f32 *) ((u8 *) D_800D154C + 0x14), *(f32 *) ((u8 *) D_800D154C + 0x1C), 5,
                  *(f32 *) ((u8 *) D_800D154C + 0x14C) * 0.5f, 0, 4, 4, 0xFF, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E2CC.s")
#endif
#ifdef NON_MATCHING
s32 func_100107F8(struct127 *arg0);
s32 func_10010894(struct127 *arg0);
s32 func_151F2CDC(void);
s32 func_1000F568(s32, s32);
s32 func_150ADA20(void);
extern s32 *D_800BE9C8[];

/* Resolves a sound / event word *slot for a record. Bit 21: conditional on mode (0 / 1: record tests, 2: a global
 * test). Ids >= 2000 come from the per-level table D_800BE9C8[rec->unk288] (high bits kept if set). Bits 24-31 are
 * a random-chance byte, bits 16-20 a variant count. Returns 1 and writes *slot, or 0 when it should not play. */
s32 func_1506E46C(struct127 *rec, s32 *slot, s32 mode) {
    u32 w = *slot;
    u32 id = w & 0x7FFF;
    u32 v;
    u32 hi;

    if (w & 0x200000) {
        if (mode == 0) {
            if (func_100107F8(rec) != 0) {
                return 0;
            }
        } else if (mode == 1) {
            if (func_10010894(rec) != 0) {
                return 0;
            }
        } else if (mode == 2) {
            if (func_151F2CDC() == 1) {
                return 0;
            }
        }
    }
    if (id >= 2000) {
        v = D_800BE9C8[*((u8 *)rec + 0x288)][id - 2000];
        if (v == 0) {
            return 0;
        }
        hi = w & 0xFF200000;
        if (hi != 0) {
            w = hi | (v & 0xFFFFFF);
        } else {
            w = v;
        }
    }
    if ((w >> 16) != 0) {
        u32 variants = (w >> 16) & 0x1F;
        if ((w >> 24) < (u32)(func_150ADA20() & 0xFF)) {
            return 0;
        }
        w &= 0x7FFF;
        if (variants != 0) {
            w = func_1000F568(w, variants);
        }
    }
    *slot = w;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E46C.s")
#endif
void func_1506E5FC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(300, 1800);
    }
}

void func_1506E63C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(100, 800);
    }
}

void func_1506E67C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(190, 1300);
    }
}

void func_1506E6BC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(300, 3000);
    }
}

void func_1506E6FC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(700, 4000);
    }
}

void func_1506E73C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(3000, 8000);
    }
}

void func_1506E77C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BBA8(300, 1800);
    }
}

void func_1506E7BC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BBA8(300, 3000);
    }
}

void func_1506E7FC(void) {
    if (D_800D154C->unk28 == 0.0f) {
        if (D_800D154C->unk107 == 0) {
            func_1506E5FC();
        }
    }
}

void func_1506E848(void) {
    if ((func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) && (func_1000F4D8((u16)D_800D1582) == 0)) {
        func_1506BA4C(0x50, 800);
    }
}

void func_1506E898(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 2) != 0) {
        func_1506BB64(300, 1800);
    }
}

void func_1506E8D8(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(300, 1800);
    }
}

void func_1506E918(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(100, 800);
    }
}

void func_1506E958(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(190, 1300);
    }
}

void func_1506E998(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(300, 3000);
    }
}

void func_1506E9D8(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(700, 4000);
    }
}

void func_1506EA18(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(3000, 8000);
    }
}

void func_1506EA58(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BC24(300, 3000);
    }
}

void func_1506EA98(void) {
    u8 temp_t6;
    struct127 *temp_a1;

    temp_t6 = (D_800D154C->unk13C - 100);
    if (D_800D154C->unk13C != 0) {
        temp_a1 = &D_800CC2D0[temp_t6];
        if (D_800CC2D0[temp_t6].unk13D >= 100) {
            D_800CC2D0[temp_t6].unk13D = (u8)0U;
            D_800CC2D0[temp_t6].xz_velocity = 18.0f;
            D_800CC2D0[temp_t6].y_velocity = 40.0f;
            D_800CC2D0[temp_t6].gravity = 6.0f;
            D_800CC2D0[temp_t6].unk76 = (u16) D_800D154C->unk7A;
            D_800CC2D0[temp_t6].unk65 = (u8)0;
            if (D_800CC2D0[temp_t6].id  == 0x20) {
                D_800CC2D0[temp_t6].unkF8 |= 0x200;
                D_800CC2D0[temp_t6].y_velocity = 0.0f;
                D_800CC2D0[temp_t6].gravity = 0.0f;
                D_800CC2D0[temp_t6].xz_velocity = 0.0f;
            }
            D_800CC2D0[temp_t6].stunned = (u8)0xFE;
            D_800CC2D0[temp_t6].unk105 = (u8)0;
            D_800CC2D0[temp_t6].unk106 = func_1505E7CC(0xC, temp_a1); //, temp_t6);
            D_800CC2D0[temp_t6].unk84.uh = (u16)0xFFFF;
            D_800CC2D0[temp_t6].unk1CC = (f32) 1000000.0f;
            func_1505E874(temp_t6, temp_a1);
            D_800CC2D0[temp_t6].unk25C |= 0x40;
        }
        D_800D154C->unk13C = (u8)0;
    }
}

void func_1506EBC0(void) {
    u8 temp_v0 = (u8)(D_800D154C->unk13C - 100);

    if (D_800D154C->unk13C) {
        if ((s32) D_800CC2D0[temp_v0].unk13D >= 0x64) {
            D_800CC2D0[temp_v0].unk65 = 0;
            D_800CC2D0[temp_v0].unk13D = (u8)0U;
            D_800CC2D0[temp_v0].xz_velocity = 0.0f;
            D_800CC2D0[temp_v0].y_velocity = 0.0f;
            D_800CC2D0[temp_v0].gravity = 6.0f;
            D_800CC2D0[temp_v0].unk1CC = 1000000.0f; // 1000000.0
        }
        D_800D154C->unk13C = 0U;
    }
}

void func_1506EC50(void) {
    if (0.2f < D_800D154C->unk28) {
        if (((D_800D1580 & 0x8000) == 0) || (D_800CC2E8[0] < D_800D154C->y_position)) {
            D_800D1878 = D_800D1580 & 0xFF;
            D_800D1880 = 0;
            D_800D154C->unk138 -= 1;
        }
    }
}

void func_1506ECD0(void) {
    D_800D154C->unk2D0->unk4 |= 0x8000;
}

void func_1506ECF0(void) {
    D_800D154C->unk3A = (s8) D_800D1580;
}

void func_1506ED0C(void) {
    D_800D154C->unk83 = (s8) D_800D1580;
    D_800D154C->unk100 |= 0x10;
    D_800D154C->unk31C->unk31 = (u8)1;
}

void func_1506ED4C(void) {
    D_800D154C->unk100 = (s8) D_800D1580;
}

void func_1506ED68(void) {
    D_800D154C->unkA9 = (u8)5;
    D_800D154C->unk31C->unk31 = (u8)0;
}

void func_1506ED90(void) {
    D_800D154C->unk21C = (s16) D_800D1580;
}

void func_1506EDAC(void) {
    D_800D154C->unkF4 = (s32) D_800D1580;
}

void func_1506EDC8(void) {
    D_800D154C->unkF4 &= ~D_800D1580;
}

void func_1506EDF0(void) {
    D_800D154C->unkF4 |= D_800D1580;
}

void func_1506EE14(void) {
    D_800D154C->unk25C |= D_800D1580;
}

void func_1506EE38(void) {
    D_800D154C->unk25C &= ~D_800D1580;
}

void func_1506EE60(void) {
    s32 temp_a1 = D_800D1580 & 0xFFFF;

    if (D_800D1580 != 0) {
        func_15188D80(D_800D154C, temp_a1, D_800D1580 >> 0x10);
    } else {
        func_1518900C(D_800D154C, temp_a1);
    }
}
// NON-MATCHING: same issue as earlier
// void func_1506EE60(void) {
//     s32 temp_a1;
//     s32 temp_v0;
//
//     temp_v0 = D_800D1580;
//     temp_a1 = temp_v0 & 0xFFFF;
//     if (temp_v0 != 0) {
//         func_15188810(D_800D154C.unk0, temp_a1, temp_v0 >> 0x10);
//         return;
//     }
//     func_15188A9C(D_800D154C.unk154C, temp_a1);
// }

void func_1506EEAC(void) {
    func_151898C0(D_800D154C, D_800D1580);
}

void func_1506EED8(void) {
    D_800D154C->unk24E = (s8) D_800D1580;
}

void func_1506EEF4(void) {
    D_800D154C->unk276 = (D_800D1580 >> 16) & 0xFFFF;
    D_800D154C->unk278 = (D_800D1580 >> 24) & 0xFF;
    D_800D154C->unk282 = D_800D1580 & 0xFFFF;
    D_800D154C->unk284 = 0;
    D_800D154C->unk285 = 0;
    D_800D154C->unk286 = 0;
    D_800D154C->unk287 = 0;
}

// TBD whats goins on here
#ifdef NON_MATCHING
/*
 * P80: script command: +0x282 = 0xFFFF, +0x276 = 5, and the byte pair +0x284 + 2 * i (i = bits 16..23 of the
 * command word D_800D1580) = bits 8..15, bits 0..7.
 */
void func_1506EF5C(void) {
    s32 w = D_800D1580;
    s32 i = ((w >> 16) & 0xFF) * 2;

    *(u16 *) ((u8 *) D_800D154C + 0x282) = 0xFFFF;
    *((u8 *) D_800D154C + 0x276) = 5;
    *((u8 *) D_800D154C + 0x284 + i) = w >> 8;
    *((u8 *) D_800D154C + 0x285 + i) = w;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EF5C.s")
#endif

void func_1506EFB4(void) {
    D_800D154C->unk282 = (u16)0;
}

void func_1506EFC8(s32 arg0) {
    if (D_800D154C->id != 0x8C) {
        func_150BB760(D_800D154C);
    }
}

void func_1506F004(s32 arg0) {
    func_150BCBBC(D_800D154C);
}

void func_1506F02C(s32 arg0) {
    func_150BA4C0(D_800D154C, 0xFF, 0);
}

void func_1506F05C(s32 arg0) {
    func_151925C4(D_800D154C, 0x32, 0xFF, 1);
}

void func_1506F090(s32 arg0) {
    func_151925C4(D_800D154C, -1, 0xFF, 1);
}

void func_1506F0C4(s32 arg0) {
    func_150C1260(D_800D154C, 0);
}

void func_1506F0F0(s32 arg0) {
    func_150C1260(D_800D154C, 1);
}

void func_1506F11C(s32 arg0) {
    func_150BABE0(D_800D154C, 0, 0xFF);
}

void func_1506F14C(s32 arg0) {
    func_150BABE0(D_800D154C, 1, 0xFF);
}

void func_1506F17C(s32 arg0) {
    func_150AEEB0(D_800D154C, 0xFF);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F1A8.s")

void func_1506F524(s32 arg0) {
    func_15197A7C(D_800D154C);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F54C.s")

void func_1506F8C0(s32 arg0) {
    func_1519EF70(D_800D154C, 0, 0);
}

void func_1506F8F0(s32 arg0) {
    struct127* a0;
    func_150E2EA4(a0 = D_800D154C, a0->unique_id, 0x14, -1, 482.0f, -127.0f, -45.0f, 659.0f, -211.0f, -114.0f, 3, 3, 5, 20.0f, (func_150ADA68() * 10.0f) + 40.0f, 0, 0.0f);
}

void func_1506F9C0(s32 arg0) {
    struct127* a0;
    func_150E2EA4(a0 = D_800D154C, a0->unique_id, 0x14, -1, 241.0f, -127.0f, -45.0f, 418.0f, -211.0f, -114.0f, 3, 3, 5, 20.0f, (func_150ADA68() * 10.0f) + 40.0f, 0, 0.0f);
}

void func_1506FA90(s32 arg0) {
    struct127* a0;
    func_150E2EA4(a0 = D_800D154C, a0->unique_id, 0x1A, -1, -181.0f, -218.0f, -1.0f, -681.0f, -584.0f, -2.0f, 3, 3, 5, 20.0f, (func_150ADA68() * 10.0f) + 40.0f, 0, 0.0f);
}

void func_1506FB60(s32 arg0) {
    if (func_151044F4() != 0) {
        func_151C6A28(D_800D154C, (arg0 - 0x13) & 0xFF, 0xFF, 0);
    } else {
        func_151C62D0(D_800D154C, (arg0 - 0x13) & 0xFF, 0, 0, -1, 0xFF, 0);
    }
}

void func_1506FBE8(s32 arg0) {
    func_151A0A10(D_800D154C, 0x46, 0xFF, 0);
}

void func_1506FC1C(s32 arg0) {
    func_151A0A10(D_800D154C, 0x28, 0xFF, 0);
}

void func_1506FC50(s32 arg0) {
    func_1519E688();
}

void func_1506FC74(s32 arg0) {
    func_1519E6BC(D_800D154C);
}

void func_1506FC9C(s32 arg0) {
    func_150B3AB0(D_800D154C, 0xFF);
}

void func_1506FCC8(s32 arg0) {
    func_15196438((u8 *) D_800D154C, 6, 0xFF, 0);
}

void func_1506FCFC(s32 arg0) {
    func_15196438((u8 *) D_800D154C, 5, 0xFF, 0);
}

void func_1506FD30(s32 arg0) {
    struct127* a0;
    func_150E2EA4(a0 = D_800D154C, a0->unique_id, 1, -1, 0.0f, 0.0, 345.0f, 0.0f, 0.0, 414.0f, 3, 3, 5, 20.0f, (func_150ADA68() * 10.0f) + 40.0f, 1, 50.0f);
}

void func_1506FDF0(s32 arg0) {
    func_151AABC4(D_800D154C, 0);
}

void func_1506FE1C(s32 arg0) {
    func_151AABC4(D_800D154C, 1);
}

void func_1506FE48(s32 arg0) {
    func_151AABC4(D_800D154C, 0);
}

void func_1506FE74(s32 arg0) {
    func_151AABC4(D_800D154C, 1);
}

void func_1506FEA0(s32 arg0) {
    func_151AABC4(D_800D154C, 2);
}

void func_1506FECC(s32 arg0) {
    func_151AABC4(D_800D154C, 3);
}

void func_1506FEF8(s32 arg0) {
    func_151AB920(D_800D154C, 0);
}

void func_1506FF24(s32 arg0) {
    func_151AB920(D_800D154C, 1);
}

void func_1506FF50(s32 arg0) {
    func_151AB930(D_800D154C);
}

void func_1506FF78(s32 arg0) {
    func_150CBF80(D_800D154C, 0, 1, 0xFF);
}

void func_1506FFAC(s32 arg0) {
    func_150CBF80(D_800D154C, 1, 1, 0xFF);
}

void func_1506FFE0(s32 arg0) {
    func_150CBF80(D_800D154C, 2, 1, 0xFF);
}

void func_15070014(s32 arg0) {
    func_150CA150((u8 *) D_800D154C);
}

void func_1507003C(s32 arg0) {
    func_151B01B8(D_800D154C, 0);
    func_151B09BC(D_800D154C, 0, 0x3E8, 0xFF, 0);
}

void func_15070084(s32 arg0) {
    func_151AECA0(D_800D154C, 0xFF, 1);
}

void func_150700B4(s32 arg0) {
    func_151B03B8(D_800D154C, 0xFF, 1);
}

void func_150700E4(s32 arg0) {
    func_15193660(D_800D154C, 0xFF, 1);
}

void func_15070114(s32 arg0) {
    func_151937F4(D_800D154C, 0xFF, 1);
}

void func_15070144(s32 arg0) {
    struct198 tmp;
    s32 tmp0;

    tmp.unk0 = 1;
    tmp.unk8 = 0;
    tmp.unkC = 0;
    tmp.unk4 = D_800D154C;

    if (D_800BE9F0 == 0x2B) {
        tmp0 = 3;
    } else {
        tmp0 = 0;
    }
    func_151C0698(D_800D154C, 0, &tmp, tmp0 & 0xFF, 0xFF, 1);
    func_151C1FB8(D_800D154C);
}

void func_150701C4(s32 arg0) {
    func_151C5280(D_800D154C, 0xFF, 1);
}

void func_150701F4(s32 arg0) {
    func_151C9740(D_800D154C, 0xFF, 1);
}

void func_15070224(s32 arg0) {
    Header header;
    Header2 header2;

    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() % 5U) + 4;
    header.unk4 = 0;
    header2.unk0 = D_800D154C->x_position;
    header2.unk4 = D_800D154C->y_position;
    header2.unk8 = D_800D154C->z_position;
    func_151602C0(&header, &header2, (func_150ADA20() % 3U) + 4, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
}
#ifdef NON_MATCHING
s32 func_1506CE6C(struct127 *, u8);
struct127 *func_1507515C(struct127 *, struct127 *, s32);
void func_15145EA4(f32 **, f32 **, void *, s32);
void func_151C1E10(u8 *, u8, s32);
extern s32 D_800E0FFE;

void func_15070300(s32 arg0) {
    struct {
        f32 * u58;
        u8 * u5C;
        f32 u60;
        u8 pad64[0x8];
        f32 u6C;
        f32 u70;
        s32 u74;
        u8 pad78[0x8];
        u8 u80;
        u8 pad81[0xB];
        s32 u8C;
        struct127 * u90;
        struct127 * u94;
        struct127 * u98;
        u8 pad9C[0x4];
        struct127 * uA0;
        u8 padA4[0x3];
        u8 uA7;
        struct127 * uA8;
        u8 padAC[0x3];
        u8 uAF;
    } sp;
    s32 sp50;
    s32 sp4C;
    s32 *temp_t4;
    s32 *temp_t8;
    f32 temp_f18;
    s32 temp_t7;
    s8 temp_v1;
    struct126 *temp_v0_3;
    struct127 *temp_v0_2;
    u8 temp_v0;
    u8 var_a1;
    u8 var_a3;
    u8 var_a3_2;

    sp.uA0 = NULL;
    temp_v0 = D_800D154C->id;
    var_a3 = 1;
    if (temp_v0 == 0x77) {
        temp_t7 = ((s32) (D_800D154C - D_800CC2D0) / 812) & 0xFF;
        sp.uA8 = D_800D154C;
        if ((temp_t7 < 2) && (temp_v1 = *((s8 *)&D_800E0FFE + temp_t7), var_a1 = 1, (temp_v1 != 0))) {
            sp.uA0 = &D_800CC2D0[temp_v1];
        } else {
            var_a1 = 0;
            if (sp.uA8->unk31C->unk197 != 0) {
                var_a1 = 1;
            }
        }
        goto block_10;
    }
    if (temp_v0 == 0x28) {
        temp_v0_2 = func_1507515C(D_800D154C, D_800CC2D0, 1);
        sp.uA8 = temp_v0_2;
        var_a3 = 0;
        var_a1 = 0;
        if (temp_v0_2->unk31C->unk197 != 0) {
            var_a1 = 1;
        }
block_10:
        sp.uAF = var_a1;
        sp.uA7 = var_a3;
        func_151C1FB8(sp.uA8);
        var_a3_2 = var_a3;
        if (sp.uA0 != NULL) {
            sp.uAF = var_a1;
            sp.uA7 = var_a3_2;
            func_151C1FB8(sp.uA0);
        }
        if (D_800BE616 != 0) {
            if (D_800D154C->unk31C->unk128 & 0x10) {
                D_800D1580 = 0xA;
                temp_v0_3 = D_800D154C->unk31C;
                var_a3_2 = 2;
                (*(u16 *)((u8 *)temp_v0_3 + 0x12C)) = (u16) ((*(u16 *)((u8 *)temp_v0_3 + 0x12C)) - 1);
            } else {
                D_800D1580 = 9;
            }
        } else {
            D_800D1580 = 5;
        }
        if (var_a1 != 0) {
            sp.u8C = 3;
            sp.u90 = sp.uA8;
            sp.u94 = sp.uA0;
            sp.u98 = D_800D154C;
            func_151C0698(sp.uA8, sp.uA0, &sp.u8C, var_a3_2, 0xFF, 1);
        } else {
            func_1506CE6C(sp.uA8, var_a1);
        }
        if (D_800D154C->unk1D4 != NULL) {
            temp_t4 = ((u8 *)&D_eu_80099F30);
            if ((D_800D154C->unk74 & 0xF) != 0xF) {
                temp_t8 = ((u8 *)&D_80099F3C);
                (*(s32 *)((u8 *)(&sp.u80) + 0)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0));
                (*(s32 *)((u8 *)(&sp.u80) + 4)) = (s32) (*(s32 *)((u8 *)temp_t4 + 4));
                (*(s32 *)((u8 *)(&sp.u80) + 8)) = (s32) (*(s32 *)((u8 *)temp_t4 + 8));
                (*(s32 *)((u8 *)(&sp.u74) + 0)) = (*(s32 *)((u8 *)temp_t8 + 0));
                (*(s32 *)((u8 *)(&sp.u74) + 4)) = (s32) (*(s32 *)((u8 *)temp_t8 + 4));
                (*(s32 *)((u8 *)(&sp.u74) + 8)) = (s32) (*(s32 *)((u8 *)temp_t8 + 8));
                sp.u6C = (func_150ADA68() * 30.0f) + 40.0f;
                temp_f18 = func_150ADA68() * 2.512f;
                sp.u5C = &sp.u80;
                sp.u58 = &sp.u60;
                sp.u70 = temp_f18 + 3.5900002f;
                func_15145EA4(&sp.u5C, &sp.u58, &D_800D154C->unk1D4->pad0[0x100], 1);
                sp4C = func_150ADA20();
                sp50 = func_150ADA20();
                func_151030B8(D_800D154C, 4U, &sp.u80, &sp.u74, &sp.u6C, ((u32) sp4C % 5U) + 5, ((u32) sp50 % 56U) + 0xC8, (func_150ADA68() * 510.0f) + 1296.0f, &sp.u60, 0xFF, 0, -1, 0xFF, 1);
                func_151C1E10(&sp.u60, 0xFF, 1);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070300.s")
#endif
void func_15070690(s32 arg0) {
    func_150EEE00(D_800D154C, (arg0 - 0x3E) & 0xFF, arg0);
}

void func_150706C4(s32 arg0) {
    func_150EEF40(D_800D154C, (arg0 - 0x3E) & 0xFF, arg0);
}

void func_150706F8(s32 arg0) {
    if ((D_800D154C->unk94 & 0x10) == 0) {
        func_150F03F8(D_800D154C, 0, 0xFF, 1);
    }
    if ((D_800D154C->unk94 & 8) == 0) {
        func_150F03F8(D_800D154C, 1, 0xFF, 1);
    }
}

void func_15070760(s32 arg0) {
    func_150EBEC0(D_800D154C, 0, 0xFF, 1);
}

void func_15070794(s32 arg0) {
    func_150EBEC0(D_800D154C, 1, 0xFF, 1);
}

void func_150707C8(s32 arg0) {
    func_150FDDA0(D_800D154C, 0xFF, 1);
}

void func_150707F8(s32 arg0) {
    func_150FDF38(D_800D154C, 0xFF, 1, 0, 0);
}

void func_15070830(s32 arg0) {
    func_150FE320(D_800D154C, 0xFF, 1);
}

void func_15070860(s32 arg0) {
    func_150FE49C(D_800D154C, 0xFF, 1, 0, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070898.s")

void func_15070C18(s32 arg0) {
    func_15199834(D_800D154C);
}

void func_15070C40(u8 arg0) {
    f32 sp34[3];
    struct127 *var_a0;

    sp34[0] = D_800D154C->x_position;
    sp34[1] = D_800D154C->y_position;
    sp34[2] = D_800D154C->z_position;
    if (D_800D154C->unk124 != 0) {
        var_a0 = &D_800CC2D0[D_800D154C->unk124 - 1];
    } else {
        var_a0 = D_800D154C;
    }
    func_151043C0(var_a0, D_800D154C, sp34, arg0, 0, 0xFF, 0);
}
// NON-MATCHING: missing a move and a branch
// void func_15103E40(s32, s32, s32, u8, u8, u8, u8);
// void func_15070C40(u8 arg0) {
//     struct17 tmp;
//     struct127 *temp_a1;
//     struct127 *phi_a0;
//
//     phi_a0 = temp_a1 = D_800D154C;
//     tmp.unk0 = temp_a1->x_position;
//     tmp.unk4 = temp_a1->y_position;
//     tmp.unk8 = temp_a1->z_position;
//
//     if (temp_a1->unk124) {
//         phi_a0 = &D_800CC2D0[temp_a1->unk124 - 1];
//         func_15103E40(phi_a0, temp_a1, &tmp, arg0, 0, 0xFF, 0);
//     }
// }

void func_15070CDC(s32 arg0) {
    func_15070C40(1);
}

void func_15070D00(s32 arg0) {
    func_15070C40(0);
}

s32 func_151030B8(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
extern struct17 D_80099F48;
extern struct17 D_80099F54;

void func_15070D24(s32 arg0) {
    struct17 a;
    struct17 b;
    f32 f[2];
    f32 pos[3];
    Header header;
    Header2 header2;

    a = D_80099F48;
    b = D_80099F54;
    if ((D_800D154C->unk1D4 != NULL) && ((D_800D154C->unk74 & 0xF) != 0xF)) {
        f[0] = (func_150ADA68() * 101.0f) + 151.0f;
        f[1] = (func_150ADA68() * 4.0f) + 4.0f;
        func_15143134(&a, pos, (u8 *)D_800D154C->unk1D4 + 0x40);
        func_151030B8(D_800D154C, 1, (u8 *)&a, (s32 *)&b, f, (func_150ADA20() % 6U) + 5, (func_150ADA20() % 156U) + 0x64, (func_150ADA68() * 2496.0f) + 3496.0f, pos, 0xFF, 0, -1, 0xFF, 0);
        header.unk0 = 3;
        header.unk1 = -1;
        header.unk2 = (func_150ADA20() % 6U) + 0xA;
        header.unk4 = 0;
        header2.unk0 = pos[0];
        header2.unk4 = pos[1];
        header2.unk8 = pos[2];
        func_151602C0(&header, &header2, (func_150ADA20() % 201U) + 0x37, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 0);
    }
}
void func_151D58E4(s32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6);
extern struct17 D_80099F60;
extern struct17 D_80099F6C;

void func_15070F60(u8 arg0) {
    struct17 a;
    struct17 b;
    f32 f[2];
    f32 pos[3];
    Header header;
    Header2 header2;

    a = D_80099F60;
    b = D_80099F6C;
    if ((D_800D154C->unk1D4 != NULL) && ((D_800D154C->unk74 & 0xF) != 0xF)) {
        f[0] = (func_150ADA68() * 180.0f) + 150.0f;
        f[1] = (func_150ADA68() * 2.0f) + 2.5f;
        func_15143134(&a, pos, (u8 *)D_800D154C->unk1D4 + ((arg0 ? 1 : 2) << 6));
        func_151030B8(D_800D154C, arg0 ? 1 : 2, (u8 *)&a, (s32 *)&b, f, (func_150ADA20() % 5U) + 5, (func_150ADA20() % 156U) + 0x64, (func_150ADA68() * 4000.0f) + 4000.0f, pos, 0xFF, 0, -1, 0xFF, 0);
        header.unk0 = 3;
        header.unk1 = -1;
        header.unk2 = (func_150ADA20() % 5U) + 3;
        header.unk4 = 0;
        header2.unk0 = pos[0];
        header2.unk4 = pos[1];
        header2.unk8 = pos[2];
        func_151602C0(&header, &header2, (func_150ADA20() % 201U) + 0x37, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 0);
        func_151D5404((struct17 *)pos, 506.0f, 1013.0f, 0.0009871668880805373f, 0xF, 0x14, 0xFF, 0);
        func_151D58E4((s32)pos, 506.0f, 1013.0f, 0.0009871668880805373f, 5, 0xFF, 0);
    }
}
void func_15071230(s32 arg0) {
    func_15070F60(0);
}

void func_15071254(s32 arg0) {
    func_15070F60(1);
}

void func_15071278(s32 arg0) {
    func_150FC438(D_800D154C, 0, 1, D_800D154C->unk84.ub[1]);
}

void func_150712AC(s32 arg0) {
    structEU_151D8E18 sp18;

    func_150FEDE0(D_800D154C, 0xFF, 1);
    if (D_800D154C->camera != NULL) {
        sp18.unk0 = 1;
        sp18.unk2 = (func_150ADA20() % 7U) + 10;
        sp18.unk5 = 1 << D_800D154C->camera->unk23D;
        sp18.unk4 = (func_150ADA20() % 7U) + 2;
        sp18.unk6 = -1;
        func_151D8E18(&sp18, 0, 0xFF, 1);
    }
}
void func_15071360(s32 arg0) {
    structEU_151D8E18 sp18;

    if (func_151044F4() != 0) {
        func_150FF604(D_800D154C, 0xFF, 1);
    } else {
        func_150FF2B0(D_800D154C, 0xFF, 1);
    }
    if (D_800D154C->camera != NULL) {
        sp18.unk0 = 1;
        sp18.unk2 = (func_150ADA20() % 5U) + 15;
        sp18.unk5 = 1 << D_800D154C->camera->unk23D;
        sp18.unk4 = (func_150ADA20() & 3) + 3;
        sp18.unk6 = -1;
        func_151D8E18(&sp18, 0, 0xFF, 1);
    }
}

void func_15071434(s32 arg0) {
    func_150FF840(D_800D154C, 1, 0, 0xFF, 1);
}

void func_15071470(s32 arg0) {
    func_150FF840(D_800D154C, 0, 0, 0xFF, 1);
}

void func_150714AC(s32 arg0) {
    func_150FF840(D_800D154C, 0, 1, 0xFF, 1);
}

void func_150714E8(s32 arg0) {
    func_151D5714(D_800D154C, &D_800A2148, &D_800A2154, D_80088BB0, 1.0f, 0xFF, 1);
}

void func_15071544(s32 arg0) {
    func_151D4668(D_800D154C);
    func_151D469C(D_800D154C, 4, 0x78, 0xFF, 1);
}

void func_1507158C(s32 arg0) {
    func_151D4668(D_800D154C);
    func_151D469C(D_800D154C, 2, 0x78, 0xFF, 1);
}

void func_150715D4(s32 arg0) {
    func_151D4668(D_800D154C);
    func_151D469C(D_800D154C, 3, 0x78, 0xFF, 1);
}

void func_1507161C(s32 arg0) {

}

void func_15071628(s32 arg0) {
    func_151D0058(D_800D154C, (arg0 - 0x55) & 0xFF, 0xFF, 1);
}

void func_15071668(s32 arg0) {
    func_151D0024(D_800D154C);
}

void func_15071690(s32 arg0) {
    struct127 *temp_a0;
    s32 pad0;
    s32 sp1C;

    temp_a0 = D_800D154C;
    if ((temp_a0->unk1D4 != 0) && ((temp_a0->unk74 & 0xF) != 0xF)) {
        func_150B60E0(temp_a0, &sp1C);
        func_150B5C38(&sp1C, 0xFF, 1);
    }
}

void func_150716EC(s32 arg0) {
    struct17 tmp;
    struct127 *temp_v0;

    temp_v0 = D_800D154C;
    tmp.unk0 = temp_v0->x_position;
    tmp.unk4 = temp_v0->y_position;
    tmp.unk8 = temp_v0->z_position;
    func_151D5404(&tmp, 1502.0f, 3000.0f, 0.00033333332976326346f, 0xC, 0xF, 0xFF, 0);
}

void func_15071764(s32 arg0) {
    struct127 *sp34 = func_15083E90(18);
    if (sp34 != NULL) {
        func_150F0BEC(sp34);
        func_150F10D4(sp34);
        func_15161E24(sp34, 1, 2, 300, 70, 255, 130, 0, 255, 1);
    }
}

void func_150717E0(s32 arg0) {
    struct {
        struct127 *unk0;
        u8 unk4;
    } sp20;
    struct127 *temp_v0;

    temp_v0 = func_15083E90(0x12);
    if (temp_v0 != NULL) {
        sp20.unk0 = temp_v0;
        sp20.unk4 = temp_v0->unique_id;
        func_151322BC((s32)&sp20, 0x43);
        func_151494E0((s32)&sp20, 0x43);
    }
}
// void func_150717E0(s32 arg0) {
//     u8 sp24;
//     void *sp20;
//     void **sp18;
//     void **temp_a0;
//     void *temp_v0;
//
//     temp_v0 = func_15083E90(0x12);
//     temp_a0 = &sp20;
//     if (temp_v0 != 0) {
//         sp20 = temp_v0;
//         sp18 = temp_a0;
//         sp24 = temp_v0->unk3B;
//         func_15131D4C(temp_a0, 0x43);
//         func_151494E0(temp_a0, 0x43);
//     }
// }

void func_15071830(s32 arg0) {
    func_150F9BB0(D_800D154C, 0xFF, 1);
}

void func_15071860(s32 arg0) {
    func_1519072C(D_800D154C);
}

void func_15071888(s32 arg0) {
    func_151D5714(D_800D154C, &D_800A1FB0, &D_800A1FBC, D_80088B90, 0.7f, 0xFF, 1);
}

void func_150718E4(s32 arg0) {
    f32 sp24[3];
    s32 sp20;

    sp20 = D_80099F78;
    if ((D_800D154C->unk1D4 != NULL) || ((D_800D154C->unk74 & 0xF) == 0xF)) {
        func_15143134(D_800A5860, sp24, (u8 *)D_800D154C->unk1D4 + (((u8 *)&sp20)[func_150ADA20() & 3] << 6));
        sp24[1] = D_800D154C->unk180 + 20.0f;
        func_151C384C(sp24, 0xFF, 1);
    }
}

void func_15071998(s32 arg0) {
    func_150FA520(D_800D154C, 0, 0xFF, 1);
}

void func_150719CC(s32 arg0) {
    func_150FA520(D_800D154C, 1, 0xFF, 1);
}

void func_15071A00(s32 arg0) {
    func_150FA520(D_800D154C, 2, 0xFF, 1);
}

void func_15071A34(s32 arg0) {
    func_151D09A8(D_800D154C, 0xFF, 1);
}

void func_15071A64(s32 arg0) {
    f32 sp4C[3];
    f32 sp28[9];

    if (!(func_150ADA20() & 1) && (D_800D154C->unk1D4 != NULL) && ((D_800D154C->unk74 & 0xF) != 0xF) &&
        (D_800CC2D0[0].stunned != 0) && (D_800CC2D0[0].health > 0)) {
        func_1504715C(sp28, D_800D154C);
        func_15143134(D_80099F7C, sp4C, (u8 *)D_800D154C->unk1D4 + 0x3C0);
        func_151DC484(sp4C, sp28, 0, 0xFF, 1);
    }
}
void func_151DC260(void *arg0, void *arg1, u8 arg2, u8 arg3, s32 arg4);
void func_15152700(void *arg0, void *arg1, void *arg2, s32 arg3, f32 arg4, u8 arg5, u8 arg6, s32 arg7);
extern f32 D_80099F88[3][3];
extern u8 D_80099FAC[];
extern u8 D_80099FC4[];

void func_15071B18(s32 arg0) {
    struct17 pos;
    f32 m[9];
    struct {
        s32 u34;
        s32 u38;
        struct17 u3C;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        s16 u60;
        s16 u62;
        f32 u64;
        f32 u68;
        f32 u6C;
    } s;

    if ((D_800D154C->unk1D4 != NULL) && ((D_800D154C->unk74 & 0xF) != 0xF)) {
        func_15143134(D_80099F88[func_150ADA20() % 3U], &pos, (u8 *)D_800D154C->unk1D4 + 0x1C0);
        func_1504715C(m, D_800D154C);
        if (func_150ADA20() & 1) {
            if (func_150ADA20() & 1) {
                func_151DC260(&pos, m, 0, 0xFF, 1);
            } else {
                func_151DC484(&pos, m, 0, 0xFF, 1);
            }
        }
        if (func_150ADA20() & 1) {
            s32 blk; // fakematch: unused block-scoped local (s69 basic-block boundary) schedules the 10.0f stores

            s.u34 = 8;
            s.u38 = 5;
            s.u3C = pos;
            s.u48 = 0;
            s.u4A = 0xFF;
            s.u4C = -0x40;
            s.u4E = 0x3C;
            s.u50 = 10.0f;
            s.u54 = 10.0f;
            s.u60 = 0x19;
            s.u62 = 0x14;
            s.u58 = -0.97800004f;
            s.u5C = 0.263f;
            s.u64 = 0.096f;
            s.u68 = 0.07f;
            s.u6C = 21.892f;
            func_15152700(&s, D_80099FAC, D_80099FC4, 6, 25.0f, 0, 0xFF, 1);
        }
    }
}

void func_15071D08(s32 arg0) {
    func_150F2230(D_800D154C, 0xFF, 1);
}

void func_15071D38(void) {
    void (*func)(s32);

    func = D_80086150[D_800D1580];
    if (func != 0) {
        func(D_800D1580);
    }
}

void func_15071D78(void) {
    struct127 *tmp;
    struct127 *orig;

    tmp = func_150721E8(D_800D154C);
    if (tmp != NULL) {
        orig = D_800D154C;
        D_800D154C = tmp;
        func_15071D38();
        D_800D154C = orig;
    }
}

void func_15071DC8(void) {
    func_15141A7C(D_800D154C, D_800D1580);
}

void func_15071DF4(void) {
    func_15192800(D_800D154C, D_800D1580);
}

void func_15071E20(void) {
    D_800D154C->unk247 = (s8) D_800D1580;
}

void func_15071E3C(void) {
    D_800D154C->unk248 = (s8) D_800D1580;
}

void func_15071E58(void) {
    D_800D1878 = D_800D1580 & 0xFF;
    D_800D154C->unk244 = (D_800D1580 >> 8) & 0xFF;
    func_1505E650(D_800D154C, D_800D154C->unk244, 1.2000000476837158f, 3.0f, D_800D1878, 0.0f, 0);
}

void func_15071ED4(void) {
    func_1505E650(D_800D154C, 0x59, 1.0f, 3.0f, 0.0f, 0.0f, 0);
}

void func_15071F14(void) {
    func_1505E650(D_800D154C, 0x24, 1.0f, 3.0f, 0.0f, 0.0f, 0);
}

void func_15071F54(void) {
    func_1507C8E0(D_800D154C, D_800D1580);
}

void func_15071F80(void) {
    if (D_800C35EA == 1) {
        D_800D154C->unk138++;
    }
}

void func_15071FB0(void) {
    if (D_800D154C->unk28 == 0.0f) {
        D_800D154C->unk10C = (u16)0;
    }
}

#ifdef NON_MATCHING
extern f32 D_8009A308;
extern f32 D_800CC710;
extern f32 D_800CC714;
extern u16 D_800CC766;
extern s8 D_800CC771;
extern f32 D_800CC8BC;
extern u8 D_800CC964;
extern u8 *D_800CCA08;

void func_15071FDC(void) {
    struct127 *var_v1;
    s32 var_v0;
    s32 var_t1;
    s32 var_t0;
    s32 var_a2;
    s32 sp2C;

    var_t1 = 1;
    var_t0 = 0x194;
    if (D_800D1580 == 0) {
        var_a2 = -1;
        var_v1 = D_800CC2D0;
        var_v0 = 0;
loop_2:
        if ((D_800C3E78 + 1) == var_v1->unk65) {
            var_a2 = var_v0;
        } else {
            var_v0 += 1;
            var_v1 = (struct127 *)((u8 *)var_v1 + (0x32C));
            if (var_v0 != 0x19) {
                goto loop_2;
            }
        }
        if ((var_a2 + 1) == D_800CC964) {
            D_800CC766 = D_800D154C->unk76 + 0x8000;
            D_800CC8BC = D_8009A308;
            goto block_13;
        }
    } else {
        if (D_800D154C->unk2E8 >= 0x71) {
            var_t0 = 0x2E5;
            (*(f32 *)((u8 *)D_800D154C + 0x2E0)) = 0.0f;
        } else {
            var_t0 = 0x32;
            D_800CC766 = D_800D154C->unk76;
            var_t1 = 0;
            if (D_800D154C->unk251 != 0) {
                D_800CC8BC = *D_800CC2E8 + 800.0f;
            }
        }
        D_800D154C->unk2E4 = 0x32;
block_13:
        D_800CC710 = (*(f32 *)((u8 *)D_800D154C + 0x2D8));
        D_800CC714 = (*(f32 *)((u8 *)D_800D154C + 0x2DC));
        sp2C = var_t1;
        *D_800CC30C = (*(f32 *)((u8 *)D_800D154C + 0x2E0));
        D_800CC771 = 1;
        func_1505E650(D_800CC2D0, var_t0 & 0xFFFF, 1.0f, 2.0f, 6.0f, 0.0f, 0);
        (*(s8 *)((u8 *)D_800CCA0C + 0x31)) = (s8) sp2C;
        if (D_800CCA08 != NULL) {
            (*(s32 *)((u8 *)D_800CCA08 + 0x5F0)) = (s32) ((*(s32 *)((u8 *)D_800CCA08 + 0x5F0)) | 0x400);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071FDC.s")
#endif
void func_150721A4(void)
{
  int new_var2;
  int new_var;
  new_var = D_800D1580 & 0xFF;
  new_var2 = (((s32) D_800D1580) >> 8) & 0xFF;
  func_1506160C(D_800D154C, (((s32) D_800D1580) >> 0x10) & 0xFF, new_var, new_var2, 0);
}

struct127 *func_150721E8(struct127 *arg0) {
    return func_15072208(arg0, 0);
}

struct127 *func_15072208(struct127 *arg0, s32 arg1) {
    s32 id = (arg0 - D_800CC2D0) + 1;
    s32 count = 0;
    s32 i;

    for (i = 0; i < 25; i++) {
        if (id == D_800CC2D0[i].unk65) {
            if (count == arg1) {
                return &D_800CC2D0[i];
            }
            count++;
        }
    }
    return NULL;
}

void func_150722F0(void) {
    struct127 *temp_v0 = func_150721E8(D_800D154C);
    if (temp_v0 != 0) {
        s32 tmp0 = D_800D1580 >> 8;
        u16 tmp1 = D_800D1580;
        func_1506160C(temp_v0, 2, tmp0, tmp1, 0);
    }
}

void func_1507233C(void) {
    D_800D154C->unk94 = (s32) ~(D_800D1580 | 1);
}

void func_15072360(void) {
    D_800D154C->unk94 &= ~D_800D1580;
}

void func_15072388(void) {
    D_800D154C->unk94 |= D_800D1580;
}

void func_150723AC(void) {
    struct127 *temp_v0 = func_15083E90(D_800D1583);
    if (temp_v0 != NULL) {
        func_15060F28(temp_v0, 0);
    }
}

void func_150723E0(void) {
    struct127 *temp_v0 = func_15083E90(D_800D1583);
    if ((temp_v0 != 0) && (temp_v0->unk65 != 0)) {
        func_15060F28(temp_v0, 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072420.s")
void func_1507266C(void)
{
  u8 new_var;
  s32 temp_a2;
  struct127 *temp_a1;
  if ((D_800BE616 != 0) || (D_800D154C->unk222 != 0))
  {
    new_var = (u8) D_800D1580;
    temp_a2 = ((s32) D_800D1580) >> 0x10;
    temp_a1 = &D_800CC2D0[D_800D154C->unk222];
    temp_a1->unk65 = D_800C3E78 + 1;
    temp_a1->unk5C = temp_a2;
    temp_a1->unk101 = 4;
    temp_a1->stunned = 0;
    temp_a1->immune = 0xFF;
    temp_a1->unk218 = 0;
    temp_a1->unkE4 = 0;
    temp_a1->unkE6 = 0;
    temp_a1->unk232 = new_var;
    temp_a1->unkEC = 1.0f;
    temp_a1->unkF0 = 1.0f;
    temp_a1->unkDC = 1.0f;
    temp_a1->unkE0 = 1.0f;
    func_151B6150(&D_800CC2D0[D_800C3E78], temp_a1);
  }
}

void func_15072740(void) {
    s32 temp_v0;
    struct127 *temp_v1;

    temp_v0 = D_800D1580 >> 16;
    temp_v1 = &D_800CC2D0[D_800D154C->unk222];
    temp_v1->unk65 = D_800C3E78 + 1;
    temp_v1->unk5C = temp_v0;
    temp_v1->unk101 = 4;
}

void func_150727AC(void) {
    D_800D154C->animation_speed = D_800D1580 * 0.1f;
    D_800D154C->unk2D0->unk10 = D_800D154C->animation_speed;
}

void func_150727F0(void) {
    s32 i;

    for (i = 0; i < 25; i++) {
        if ((D_800CC2D0[i].interaction_state != 0) && ((D_800C3E78 + 1) == D_800CC2D0[i].unk65)) {
            D_800CC2D0[i].unk218 = NULL;
            D_800CC2D0[i].unk232 = D_800D1580;
        }
    }
}

void func_15072918(void) {
    func_15060F28(D_800D154C, 0);
}

void func_15072940(void) {
    func_15060F28(D_800D154C, 1);
}

void func_15072968(void) {
    func_1505E650(D_800D154C, 44, 1.5f, 12.0f, 0.0f, 0.0f, 0);
    D_800D154C->disable_run = 25;
}

void func_150729B4(void) {
    D_800D154C->unk2E4 = D_800D1580;
}

void func_150729D0(void) {
    D_800D154C->unk31C->unk8 = (u16)1;
    func_1507EB4C(D_800D154C, 21);
    func_1506B82C();
}

void func_15072A14(void) {
    D_800D154C->unk31C->unk66 = (u16)0;
    func_1507F640();
}

void func_15072A40(void) {
    D_800D154C->unk31C->unk19B = (u8)0;
    D_800D154C->unk31C->unk78 = (u8)0;
    func_1507F640();
}

void func_15072A7C(void) {
    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->unk1A9++;
        if ((func_150ADA20() & 7) < (u32) D_800D154C->unk31C->unk1A9) {
            func_1505E650(D_800D154C, 394, 1.0f, 4.0f, 0.0f, 0.0f, 0);
        }
    }
}

void func_15072AF8(void) {
    func_1505E650(D_800D154C, D_800D154C->unk84.uh + 1, 1.0f, 6.0f, 0.0f, 0.0f, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072B44.s")
void func_15072DA0(void) {
    D_800D154C->unk2F8 &= 0xFFF8;
    D_800D154C->unk2F8 |= D_800D1580;
}

void func_15072DD8(void) {
    func_15083568(D_800D154C, D_800D1580, 1.0f, 0);

    if ((D_800D154C->unk31C != 0) && (D_800D154C->unk31C->unk11A == 1)) {
        D_800D154C->unk31C->unk11A = (u8)2U;
    }
}

void func_15072E38(void) {
    func_150836CC(D_800D154C, D_800D1580);

    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->unk11A = (u8)0;
    }
}

void func_15072E7C(void) {
    D_800D154C->unk10C = (s16) D_800D1580;
}

void func_15072E98(void) {
    D_800D154C->unk2D0->unk10 *= D_800D1874;
}

void func_15072EC0(void) {
    struct197 *tmp;

    tmp = D_800D154C->unk2D0;
    if (tmp->unk10 < D_800D1874) {
        D_800D154C->unk10C = 0;
    }
}

void func_15072EF4(void) {
    D_800D154C->stunned = (s8) D_800D1580;
}

s32 func_150E1AF0(struct127 *, f32, f32, f32, f32, f32, f32, s32, s32);

void func_15072F10(void) {
    f32 x;
    f32 z;
    f32 y;
    s16 angle;

    angle = D_800D154C->unk1D1 * 200;
    (*(s16 *)((u8 *)D_800D154C->unk31C + 0x24))--;
    func_1505A184(D_800D154C->unk7A - D_800D154C->unk31C->unk12, 2000.0f, angle * 0.005493164f, &x, &z, &y);
    x = x * 5000.0f + D_800D154C->x_position;
    z = z * 5000.0f + D_800D154C->z_position;
    y = y * 5000.0f + D_800D154C->y_position;
    func_150E1AF0(D_800D154C, D_800D154C->x_position, D_800D154C->y_position + D_800D154C->unkD6, D_800D154C->z_position, x, y, z, D_800C3E78, 0x12);
}

void func_eu_1507340C(void) {
}

void func_15073054(void) {
    D_800D154C->unk22E = (s16) D_800D1580;
}

void func_15073070(void) {

}

void func_15073078(void) {
    func_1512D748(0, D_800D1580, 1);
}

void func_150730A4(void) {
    D_800D154C->unk1FF = (u8)3;
    D_800D154C->unk200 = (s8) D_800D1580;
}

void func_150730D0(void) {
    struct127 *temp_v0;

    if (D_800D1580 == 1) {
        temp_v0 = D_800D154C;
        temp_v0->unk2F8 |= 0x100;
    } else {
        temp_v0 = D_800D154C;
        temp_v0->unk2F8 &= 0xFEFF;
      }
}

#ifdef NON_MATCHING
void *func_1505ED34(void);
u8 *func_15159140(u8 *arg0, u8 arg1, s32 arg2);
u8 *func_1515D9F0(s32 arg0);
void *func_1515D9B0(void);

#define O_U8(o, off)  (*(u8 *) ((u8 *) (o) + (off)))
#define O_S16(o, off) (*(s16 *) ((u8 *) (o) + (off)))
#define O_S32(o, off) (*(s32 *) ((u8 *) (o) + (off)))
#define O_F32(o, off) (*(f32 *) ((u8 *) (o) + (off)))

/* Spawns a child object (type 0x21) of `parent` at offset (x, y, z) from joint `joint` (the parent's position when it
 * has no joint matrices or joint == -1), yawed by `angle` degrees from the parent; scale-like fields 0x3C / 0x20 / 0x24
 * = s3c / s20 / s24, byte 0x83 = b83. Returns the new object. */
u8 *func_15073118(struct127 *parent, s32 joint, s32 kind, f32 x, f32 y, f32 z, f32 angle, f32 s3c, f32 s20, f32 s24,
                         s32 b83) {
    struct127 *o = func_1505ED34();
    f32 mf[4][4];
    f32 (*m)[4];
    f32 px, py, pz;
    f32 yaw;
    u32 a;
    s32 i;

    O_F32(o, 0x24) = s24;
    O_F32(o, 0x20) = s20;
    O_F32(o, 0x3C) = s3c;
    O_U8(o, 0x83) = b83;
    if (parent->unk1D4 != NULL && joint != -1) {
        m = (f32 (*)[4]) ((u8 *) parent->unk1D4 + joint * 64);
        if (D_800C42B0 != 0) {
            guMtxL2F(mf, (Mtx *) m);   /* fixed-point joint matrices */
            m = mf;
        }
        func_150A7E40(m, x, y, z, &px, &py, &pz);
    } else {
        px = O_F32(parent, 0x14);
        py = O_F32(parent, 0x18);
        pz = O_F32(parent, 0x1C);
    }
    O_F32(o, 0x14) = px;
    O_F32(o, 0x18) = py;
    O_F32(o, 0x1C) = pz;
    /* yaw in 1/65536 turns; float -> u32 as the asm: <= -1 gives 0xFFFFFFFF */
    yaw = (f32) *(u16 *) ((u8 *) parent + 0x7A) + angle * 182.04445f;
    a = yaw <= -1.0f ? 0xFFFFFFFF : (u32) yaw;
    *(u16 *) ((u8 *) o + 0x7A) = a;
    *(u16 *) ((u8 *) o + 0x76) = a;
    O_S32(o, 0x0) = 0x21;
    O_U8(o, 0x125) = 0xFF;
    O_S32(o, 0xF8) = 2;
    if (kind != 0x42) {
        O_S32(o, 0xF8) = 0x100E;
    }
    O_U8(o, 0x66) = O_U8(parent, 0x66) & 0xC;
    O_S16(o, 0xE4) = 10;
    O_S16(o, 0xE6) = 10;
    O_F32(o, 0xEC) = 1.0f;
    O_F32(o, 0xF0) = 1.0f;
    O_F32(o, 0xDC) = 1.0f;
    O_F32(o, 0xE0) = 1.0f;
    O_F32(o, 0x14C) = 0.5f;
    O_F32(o, 0x150) = 0.5f;
    if (kind == 0x1F) {
        O_F32(o, 0xC8) = 10.0f;
    }
    O_S16(o, 0x278) = kind;
    O_U8(o, 0x5) = 5;
    O_U8(o, 0x3B) = 0xFF - (s32) ((u8 *) o - (u8 *) D_800CC2D0) / 0x32C;
    func_15083568(o, kind, 1.0f, 0);
    for (i = 0; i <= D_80082FA0; i++) {
        O_S32(o, 0x304 + i * 4) = (s32) func_1515D9F0(1);
    }
    if (O_S32(o, 0x300 + i * 4) != 0) {   /* the last slot written (i == 0: the word at 0x300) */
        O_U8(o, 0x301) = 1;
    }
    O_S32(o, 0x314) = (s32) func_1515D9B0();
    func_1514F18C(func_15159140((u8 *) o, 1, 0), o, 0x13);
    return (u8 *) o;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073118.s")
#endif
#ifdef NON_MATCHING
/* Script command: spawn a projectile / effect object from the current object D_800D154C through
 * func_15073118 (owner, type, model, then offsets and speeds; 100 = lifetime). D_800D1580 picks the kind:
 *   0: type 0x17 model 0x1F, flagged 0x1000000 in unkF8. When the owner's camera (unk318) is within 30
 *      of the owner (func_15037988) and a 1-in-5 roll passes, it is aimed at the camera: unk2E4 = 1, no
 *      gravity, heading unk76 / unk7A from func_150484A0 (degrees -> 0x10000 units, -0x4000), vertical
 *      speed = xz speed * dy / horizontal distance. Otherwise unk2E4 = 0.
 *   1: type 0xE model 0x42, offsets jittered by +-20 * owner->unk2E4 / 100.
 *   2: type 9 model 0x35, flagged 0x1000000, unkB8 = 180.
 *   3: type 0xE model 0x88, offsets jittered by +-200.
 * Jitter = (rand % 40 - 20) * scale (func_150ADA20, unsigned modulo). */
s32 func_15037988(s32 index, s32 arg1, s32 arg2, f32 x, f32 y, f32 z, void *out, f32 radius, s32 arg8, s32 arg9);
u8 *func_15073118(struct127 *owner, s32 type, s32 model, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7,
                         f32 arg8, f32 arg9, s32 life);
#define JITTER(scale) ((f32)((s32)((u32)func_150ADA20() % 40) - 20) * (scale))

void func_1507342C(void) {
    struct127 *obj;
    struct127 *shot;
    u8 *cam;
    s32 aim;
    u8 hitInfo[0x20];   /* sp68, filled by func_15037988 */
    f32 dx, dy, dz;
    f32 angle;
    f32 heading;
    f32 dist;
    f32 scale;
    f32 y, x;
    s16 dir;

    if (D_800D1580 == 0) {
        obj = D_800D154C;
        aim = FALSE;
        cam = (u8 *)obj->camera;
        if (func_15037988(obj - D_800CC2D0, 0x17, 0x17, *(f32 *)(cam + 0x2F8), *(f32 *)(cam + 0x2FC),
                          *(f32 *)(cam + 0x300), hitInfo, 30.0f, 0, 0) != 0) {
            if ((u32)func_150ADA20() % 1000 < 200) {
                aim = TRUE;
            }
        }
        shot = (struct127 *) func_15073118(D_800D154C, 0x17, 0x1F, 0.0f, 0.0f, 16.0f, 0.0f, 42.8f, 49.9f, 2.9f, 100);
        shot->unkF8 |= 0x1000000;
        if (!aim) {
            shot->unk2E4 = 0;
            return;
        }
        dx = *(f32 *)(cam + 0x2F8) - shot->x_position;
        dy = *(f32 *)(cam + 0x2FC) - shot->y_position;
        dz = *(f32 *)(cam + 0x300) - shot->z_position;
        angle = func_150484A0(dx, dz) * 57.295776f;
        heading = angle;
        if (180.0f < angle) {
            heading = angle - 360.0f;
        }
        dist = sqrtf(dx * dx + dz * dz);
        shot->gravity = 0.0f;
        shot->unk2E4 = 1;
        shot->y_velocity = shot->xz_velocity * dy / dist;
        dir = (s32)(heading * 182.04445f) - 0x4000;
        shot->unk7A = dir;
        shot->unk76 = dir;
    } else if (D_800D1580 == 1) {
        scale = (f32)D_800D154C->unk2E4 * 0.01f;
        y = 58.4f + JITTER(scale);
        x = 42.8f + JITTER(scale);
        func_15073118(D_800D154C, 0xE, 0x42, 0.0f, 0.0f, 16.0f, JITTER(scale), x, y, 2.9f, 100);
    } else if (D_800D1580 == 2) {
        shot = (struct127 *) func_15073118(D_800D154C, 9, 0x35, 0.0f, 27.3f, 0.0f, 180.0f, 23.4f, 45.2f, 3.5f, 100);
        shot->unkF8 |= 0x1000000;
        shot->unkB8 = 180.0f;
    } else if (D_800D1580 == 3) {
        y = 58.4f + JITTER(10.0f);
        x = 42.8f + JITTER(10.0f);
        func_15073118(D_800D154C, 0xE, 0x88, 0.0f, 0.0f, 16.0f, JITTER(10.0f), x, y, 2.9f, 100);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507342C.s")
#endif

void func_150738E8(void) {
    u8 temp_v0 = (u8)(D_800D154C->unk13C - 100);

    if (D_800D154C->unk13C != 0) {
        D_800D154C->unk13C = 0U;
        D_800CC2D0[temp_v0].unkF8 = 0x8200;
        D_800CC2D0[temp_v0].unk13D = 0;
        D_800CC2D0[temp_v0].unk76 = D_800D154C->unk7A;
        D_800CC2D0[temp_v0].unk65 = 0;
        D_800CC2D0[temp_v0].unk232 = 6;
        D_800CC2D0[temp_v0].unk218 = 0;
        D_800CC2D0[temp_v0].stunned = 0;
        D_800CC2D0[temp_v0].unk7A = 0xE000;
        func_1505E650(D_800D154C, 0x97, 1.0f, 5.0f, 0.0f, 0.0f, 0);
    }
}

void func_150739A4(void) {
    D_800D154C->unk64 = (s8) D_800D1580;
}

void func_150739C0(void) {
    D_800D154C->unk64 -= D_800BE9A0;

    if (D_800D154C->unk64 >= 0) {
        D_800D1880 = 0;
        D_800D154C->unk138--;
        D_800D1878 = D_800D1580;
    }
}

void func_15073A28(void) {
    D_800D154C->unk44 = (f32) D_800D1580;
}

#ifdef NON_MATCHING
s32 func_1505D024(struct127 *, s32, s32, u8);

void func_15073A50(void) {
    s32 sp20;
    struct127 *sp18;
    s32 temp_v0;
    struct127 *temp_a0;

    temp_a0 = &D_800CC2D0[D_800D154C->unk124];
    if (temp_a0->unk65 != 0) {
        temp_v0 = D_800D1580;
        D_800D154C->unk13C = 0;
        temp_a0->immune = 0;
        sp18 = temp_a0;
        sp20 = temp_v0;
        func_1505D024(temp_a0, D_800D1580 & 0xFF00FF, 0, D_800C3E78);
        temp_a0->unk1CC = 100000.0f;
        if (temp_v0 & 0x40000000) {
            temp_a0->unk1CC = D_800D154C->y_position;
        }
        temp_a0->immune = 0x14;
        temp_a0->unk76 = D_800D154C->unk7A + temp_v0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073A50.s")
#endif
void func_15073B38(void)
{
  f32 new_var; // fakematch: permuter temps (new_var/new_var2/new_var3) and ^ 0 set registers and load order
  f32 new_var3;
  f32 new_var2;
  new_var2 = (f32) (D_800D1580 & 0xFFFF);
  new_var = new_var2;
  D_800D154C->unk31C->unkA8 = new_var;
  new_var = (new_var3 = (f32) ((((s32) D_800D1580) >> 0x10) & 0xFF));
  D_800D154C->unk31C->unkAC = (u8) ((u32) new_var);
  D_800D154C->unk31C->unkAD = ((u8) (((s32) D_800D1580) >> 0x18)) ^ 0;
}

void func_15073C28(void) {
    func_1507F640();
}

void func_15073C48(void) {

}

// ???
void func_15073C50(void) {
    D_800D154C->unk224 = (s32)(D_800CC2D0[D_800D154C->unk222].y_position + D_800D1580);
}

void func_15073CB8(void) {
    struct127 *tmp = func_1505F0AC(0x53);
    if ((tmp != 0) && ((u16)tmp->unk244 == 0x1F)) {
        tmp->unk21C = (u16)0;
    }
}

void func_15073CF4(void) {
    func_15062B1C(D_800D154C, (f32) D_800D1580);
}


void func_15073D34(void) {
    func_15062B50(D_800D154C, (f32) D_800D1580);
}

void func_15073D74(void) {
    struct127 *temp_v0;

    temp_v0 = func_15083E90(D_800D1583);
    if (temp_v0 != 0) {
        temp_v0->unk65 = (u8)0;
    }
}

void func_15073DA4(void) {
    s32 tmp;

    if (D_800D1580 != 0) {
        tmp = 18;
    } else {
        tmp = 2;
    }
    func_1506C460(D_800D154C->unk40, 150.0f, 0, 0, 100, tmp, 60.0f, 0.5f, 0, 0, 1);
}

void func_15073E2C(void) {
    func_1506C460(D_800D154C->unk40, 80.0f, 0, 0, 100, 11, 40.0f, 0.5f, 0, 14, 1);
}

void func_15073EA4(void) {
    func_1506C460(D_800D154C->unk40, 60.0f, 0, 0, 100, 12, 40.0f, 0.5f, 0, 14, 1);
}

void func_15073F1C(void) {
    struct126 *temp_v0 = func_1503195C(D_800D154C, 0x3C, 0);
    if (temp_v0 != NULL) {
        temp_v0->unk38 = 2000;
    }
}

void func_15073F54(void) {
}

void func_15073F5C(void) {
    D_800D154C->unk2CB = (s8) D_800D1580;
}

void func_15073F78(void) {
    D_800D154C->unk10B &= ~D_800D1580;
}

#ifdef NON_MATCHING
extern u8 *D_800D252C;
extern f32 D_800CC704;
extern f32 D_800CC70C;
u8 *func_15031C4C(u8 *, s32, s32);
s32 func_15082E44(u8 *, s32, s32, s32, s32);
void func_100100E0(s32, s32, s32, s32, s32, s32);
void func_1506B04C(u8 *, s32, void *);
void func_150F1C5C(u8 *, u8, u8, u8, s32);
s32 func_15033ECC();

/* struct126 (the owner's control block, me->unk31C) fields past the declared ones */
#define CTL_F32(c, off) (*(f32 *) ((u8 *) (c) + (off)))
#define CTL_U16(c, off) (*(u16 *) ((u8 *) (c) + (off)))
/* D_800D2104[obj->unk13F]: the object's model / anim block (s16 x/y/z offsets at +8/+A/+C) */
#define OBJ_MODEL_S16(o, off) (*(s16 *) ((u8 *) (D_800D2104[(o)->unk13F]) + (off)))

// event_spawn_helper_object: event-script command: spawns the helper object of record (arg & 0xFF) next to the
// current object D_800D154C (on its marker point 0x13 / 4 / arg byte 2 or 100 units above it), gives it the owner's
// heading, a throw speed (from the owner's charge +0x19C when D_800BE616 is set, with a launch sound), then applies
// the per-kind setup (0x4A, 0x7B, 0x9A), marks it active (+0x1CA bit 0x80) and stores its state in +0x232.
void func_15073FA0(void) {
    s32 arg = D_800D1580 & 0xFFFF;
    s32 rec;
    s32 n;
    s32 state;
    s32 sel;
    s32 usePos;
    struct127 *me;
    struct127 *obj;
    struct126 *ctl;
    u8 *snd;
    f32 speed;
    s16 angle;
    f32 dx, dy, dz;
    s32 r1, r2, turn;

    rec = func_15083E0C(arg & 0xFF);
    if (rec == -1) {
        return;
    }
    state = 1;
    D_800D252C[rec] = 0;
    n = func_15082E44((u8 *) D_800D20FC + rec * 0x30, rec, 0, 0, 0);
    if (n == 0) {
        return;
    }
    obj = &D_800CC2D0[n - 1];
    obj->unk124 = D_800C3E78 + 1;
    obj->unique_id = D_800C3E78 + 0x96;
    me = D_800D154C;
    speed = 40.0f;
    usePos = TRUE;
    if (me->unk1D4 != NULL) {
        usePos = FALSE;
        switch (me->id) {
        case 0x5A:
            sel = 0x13;
            break;
        case 0x75:
        case 0x80:
            sel = 4;
            break;
        case 0x7B:
            if (arg == 0x10) {
                sel = (D_800D1580 >> 16) & 0xFF;
            } else {
                usePos = TRUE;
            }
            break;
        default:
            usePos = TRUE;
            break;
        }
        if (!usePos) {
            func_15143134(NULL, &obj->x_position, (u8 *) me->unk1D4 + sel * 64);
            me = D_800D154C;
        }
    }
    if (usePos) {
        obj->x_position = me->x_position;
        obj->y_position = me->y_position + 100.0f;
        obj->z_position = me->z_position;
    }
    if (D_800BE616 != 0) {
        state = 5;
        obj->unk2E4 = CTL_U16(me->unk31C, 0x19C);
        me->unk31C->unk19B = 0;
        D_800D154C->unk31C->unk78 = 0;
        obj->gravity = 4.0f;
        me = D_800D154C;
        ctl = me->unk31C;
        speed = (f32) (200 - CTL_U16(ctl, 0x19C)) * 60.0f / 200.0f + 40.0f;
        if ((D_800D1580 >> 16) & 1) {
            speed = 0.0f;
        }
        if (ctl->unk198 != 0) {
            func_1505A184((u16) (s32) ((45.0f - CTL_F32(ctl, 0x170)) * 182.04445f), speed * 4.0f, 0.0f, &dx, &dy, &dz);
            obj->y_velocity = -dy;
        } else {
            obj->y_velocity = 50.0f;
        }
        snd = func_15031C4C((u8 *) me, (me->id == 0x75) ? 0x64 : 0x2C, 0);
        if (snd != NULL) {
            obj->unk8E = *(s32 *) (snd + 0x3C);
            func_100100E0((s32) func_15033ECC, (s32) snd, (s32) D_800D154C, (s32) func_1000EE70, (s32) obj,
                          obj->unique_id);
        }
        me = D_800D154C;
    }

    angle = me->unk7A;
    if (me->unk31C != NULL) {
        angle -= me->unk31C->unk12;
    }
    obj->unk7A = angle;
    obj->unk76 = angle;
    obj->xz_velocity = speed;
    obj->unk1CC = obj->y_position;

    switch (me->id) {
    case 0x4A:
        state = 5;
        obj->xz_velocity = 0.0f;
        func_151A3940((u8 *) obj, 0xFF);
        OBJ_MODEL_S16(obj, 8) = (s16) (s32) D_800CC704;
        OBJ_MODEL_S16(obj, 0xC) = (s16) (s32) D_800CC70C;
        break;
    case 0x7B:
        if (arg == 0x10) {
            state = 7;
            OBJ_MODEL_S16(obj, 8) = (s16) (s32) D_800CC704;
            OBJ_MODEL_S16(obj, 0xA) = 0x3D4;
            OBJ_MODEL_S16(obj, 0xC) = (s16) (s32) D_800CC70C;
            obj->unique_id = 0xFF - (n - 1);
            func_1506B04C((u8 *) obj, 0xC, NULL);
            r1 = func_150ADA20();
            r2 = func_150ADA20();
            func_150F1C5C((u8 *) D_800D154C, r1 & 1, r2 & 3, 0xFF, 1);
        } else if (arg == 0xA) {
            state = 0xE;
            obj->y_position = me->y_position;
        } else {
            state = 4;
            obj->unique_id = 0x12;
            obj->y_position = 1040.0f;
            obj->xz_velocity = 0.0f;
        }
        break;
    case 0x9A:
        turn = (func_150ADA20() & 0xFFF) - 0x800;
        r2 = (s16) ((u32) func_150ADA20() % 800);
        state = 7;
        func_1505A184((u16) (D_800D154C->unk76 + turn), 30.0f - (f32) r2 * 0.01f, 0.0f, &dx, &dy, &dz);
        obj->x_position -= dx;
        obj->z_position -= dy;
        me = D_800D154C;
        obj->xz_velocity = me->xz_velocity * 1.35f + 6.0f;
        obj->immune = 0xFF;
        obj->y_velocity = me->y_velocity;
        obj->y_position = me->y_position - 40.0f;
        obj->unk222 = me->unk222;
        break;
    }
    obj->health |= 0x80;
    obj->unk232 = state;
}
#undef CTL_F32
#undef CTL_U16
#undef OBJ_MODEL_S16
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073FA0.s")
#endif

void func_15074644(void) {
    D_800D154C->unk31C->unk11A = (s8) D_800D1580;
}

void func_15074664(void) {
    if (D_800D154C->unk31C != NULL) {
        if (D_800D1580 == 1) {
            func_10011FDC(5);
        } else if ((u8)D_800D154C->unk31C->unk94 == 1) {
            func_10011FDC(0);
        }
        D_800D154C->unk31C->unk94 = D_800D1580;
    }
}
void func_150746F0(void) {
    struct127 *var_a0 = NULL;

    if (D_800BE616 != 0) {
        var_a0 = D_800D154C;
    } else if (D_800D154C->unk13C != 0) {
        var_a0 = D_800CC2D0;
    }
    if (var_a0 != NULL) {
        if (D_800D1580 >= var_a0->health) {
            var_a0->health = 0;
            D_800D154C->health = 0;
            if (var_a0->interaction_state == 1) {
                var_a0->immune = 0xFF;
                func_1507CD64(var_a0, 6);
            }
        } else {
            var_a0->health -= D_800D1580;
            if (var_a0->unk31C != NULL) {
                if ((var_a0->camera != NULL) && (var_a0->unk31C->unk197 != 0)) {
                    func_1517F9F8(0xFF, 0, 0, 0xB4, 0x14, var_a0->camera->unk23D);
                }
            }
        }
    }
}
// ?
#ifdef NON_MATCHING
void func_150747E4(void) {
    struct127 *temp_a0;
    u8 temp_v0;

    temp_v0 = D_800D154C->unk65;
    if (temp_v0 != 0) {
        temp_a0 = &D_800CC2D0[temp_v0 - 1];
        temp_a0->unk218 = NULL;
        temp_a0->unk232 = (u8) D_800D1580;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150747E4.s")
#endif
void func_15074840(void) {
    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->unk1AA += D_800D1580;
    }
}

void func_15074870(void) {
    D_800D154C->unk24F = (s8) D_800D1580;
}

// ??
#ifdef NON_MATCHING
/*
 * P80: script command: add bits 24..31 of the command word D_800D1580 to the object's byte +0x138 when the flag
 * test (word +0x2E4 + 4 * bits 16..23) & bits 8..15 matches bit 0 (bit 0 set: the flags are clear; clear: any set).
 */
void func_1507488C(void) {
    s32 w = D_800D1580;
    u8 *o = (u8 *) D_800D154C;
    s32 add = w & 1;

    if (*(s32 *) (o + 0x2E4 + ((w >> 16) & 0xFF) * 4) & ((w >> 8) & 0xFF)) {
        add ^= 1;
    }
    if (add) {
        o[0x138] += w >> 24;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507488C.s")
#endif

void func_150748F4(void) {
    D_800CC3D7 = (s8) D_800D1580;
}

void func_1507490C(void) {
    struct127 *tmp;
    u8 temp_v0 = (u8)(D_800D154C->unk13C - 100);

    if (D_800D154C->unk13C != 0) {
        tmp = &D_800CC2D0[temp_v0 & 0xFF];
        if (D_800CC2D0[temp_v0].unk13D >= 0x64) {
            D_800CC2D0[temp_v0].unk232 = D_800D1580;
            D_800CC2D0[temp_v0].unk218 = 0;
            D_800CC2D0[temp_v0].stunned = 0;
        }
    }
}

void func_15074980(void) {
    s32 i;
    f32 dist = D_800D1580 * 8;

    for (i = 0; i < D_8008FD8C; i++) {
        if (func_1505A72C(D_800D154C, &D_800CC2D0[i]) < dist) {
            if (D_800CC2D0[i].unk31C != NULL) {
                D_800CC2D0[i].unk31C->chasing = 20;
            }
        }
    }
}

void func_15074A44(void) {
    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->unk26 = (s8) D_800D1580;
    }
}

void func_15074A6C(void) {
    if (D_800D154C->unk13C == 0) {
        D_800D154C->unk138++;
    }
}

#ifdef NON_MATCHING
void func_15074A94(void) {
    f32 temp_f0;
    f32 temp_f14;
    f32 var_f2;

    temp_f0 = func_1505A72C(D_800CC2D0, D_800D154C);
    if (D_800D154C->unk148 < 0.2f) {
        D_800D154C->unk148 = D_800D154C->unk154;
    }
    if (temp_f0 < 200.0f) {
        var_f2 = 0.3f;
    } else {
        temp_f14 = D_800D154C->unk148;
        if (temp_f0 > 1500.0f) {
            var_f2 = temp_f14;
        } else {
            var_f2 = (((temp_f0 - 200.0f) / 1300.0f) * (temp_f14 - 0.3f)) + 0.3f;
        }
    }
    D_800D154C->unk158 = var_f2;
    D_800D154C->unk154 = D_800D154C->unk158;
    D_800D154C->unk15C = 0.02f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074A94.s")
#endif
// NON-MATCHING: JUSTREG
// void func_15074A94(void) {
//     f32 phi_f2;
//     f32 temp_f0;
//
//     temp_f0 = func_1505A72C(&D_800CC2D0, D_800D154C);
//
//     if (D_800D154C->unk148 < D_8009A0E8) {
//         D_800D154C->unk148 = D_800D154C->unk154;
//     }
//
//     if (temp_f0 < 200.0f) {
//         phi_f2 = D_8009A0EC;
//     } else {
//         if (2.2f < temp_f0) {
//             phi_f2 = D_800D154C->unk148;
//         } else {
//             f32 tmp = 3.3f;
//             phi_f2 = D_800D154C->unk148;
//             phi_f2 = phi_f2 - tmp;
//             phi_f2 = phi_f2 * ((temp_f0 - 200.0f) / 2.4f);
//             phi_f2 = phi_f2 + tmp;
//         }
//     }
//     D_800D154C->unk154 = D_800D154C->unk158 = phi_f2;
//     D_800D154C->unk15C = 593.0f;
// }

void func_15074B7C(void) {
    D_800D1880 = 0;
    D_800D1878 = D_800D1580;

    if (D_800D1580 == 0) {
        D_800D1878 = 0.1f;
        D_800D154C->unk1FC |= 4;
        D_800D154C->unk138 = 0;
    }
}

void func_15074BD8(s32 arg0, s32 arg1, s32 arg2) {
}

void func_15074BEC(s32 arg0, s32 arg1, s32 arg2) {
}

void func_15074C00(s32 arg0, struct127 *arg1, s32 arg2) {
    struct199 tmp; // is this actually 2 structs?

    if (((u8)arg1->unk239 & 0x7F) == 5) {
        func_1504715C(&tmp, arg1);   /* P80: a1 still holds arg1 at the jal; the callee reads the object */
        tmp.unk24 = D_800CC2C0;
        tmp.unk28 = D_800CC2C4;
        tmp.unk2C = D_800CC2C8;
        func_150C04C0(&tmp.unk24, &tmp, 0x16, 1, 0xFF, 0);
    }
}

s32 func_150335C8(u8 *, u8 *, s32, s32, s32, s32);
s32 func_15166688(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15194858(u8 *, u8 *);

// P214: entry of hit-handler table D_80086A34, whose other 36 entries are void (a, b, s32): the NM build takes the
// third (unused) argument too, so the port's indirect call type matches. The extra parameter changes IDO's frame
// (0x10 bytes), so the default build keeps the 2-parameter definition.
#ifdef NON_MATCHING
void func_15074C80(u8 *arg0, u8 *arg1, s32 arg2) {
#else
void func_15074C80(u8 *arg0, u8 *arg1) {
#endif
    s32 var_a2;

    if ((*(u16 *)((u8 *)arg0 + 0x278)) == 0x11) {
        func_15194858(arg0, arg1);
    }
    if (((*(u16 *)((u8 *)arg0 + 0x278)) == 2) || ((*(u16 *)((u8 *)arg0 + 0x278)) == 0x12) || ((*(u16 *)((u8 *)arg0 + 0x278)) == 3) || ((*(u16 *)((u8 *)arg0 + 0x278)) == 6)) {
        if ((*(u8 *)((u8 *)arg1 + 0x1CA)) == 0) {
            if ((*(u16 *)((u8 *)arg0 + 0x278)) == 2) {
                var_a2 = 0x2A;
            } else if ((*(u16 *)((u8 *)arg0 + 0x278)) == 0x12) {
                var_a2 = 0x2F;
            } else if ((*(u16 *)((u8 *)arg0 + 0x278)) == 3) {
                var_a2 = 0x39;
            } else {
                var_a2 = 0x51;
            }
            func_150335C8(arg0, arg1, var_a2, 0xC, 1, 0);
        }
        (*(s8 *)((u8 *)arg0 + 0x1CA)) = 0;
    }
    if ((*(s32 *)((u8 *)arg1 + 0)) == 0x19) {
        func_15166688((s32) (256.0f - (func_150484A0((*(f32 *)((u8 *)arg0 + 0x20)), (*(f32 *)((u8 *)arg0 + 0x3C))) * 40.743664f)), 0xC0 - ((s32) (*(u16 *)((u8 *)arg0 + 0x76)) >> 8), (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s32) (*(f32 *)((u8 *)arg0 + 0x18)), (s32) (*(f32 *)((u8 *)arg0 + 0x1C)), 0x10, 0x14, 0, 0xFF, 0);
    }
}

void func_15074DEC(struct127 *arg0, s32 arg1, s32 arg2) {
    arg0->unk2E8 = 1;
}

void func_15074E04(s32 arg0, s32 arg1, s32 arg2) {
    func_1516FE1C((s32) (arg1 - (s32)&D_800CC2D0) / (s32) sizeof(struct127), 0xB4, 0xFF, 0);
    func_1518D1C0(arg1, 0xB, 0, 1, 0xFF, 0, &D_80099C1C);
}

void func_15074E80(struct127 *arg0, struct127 *arg1, s32 arg2) {
    s8 sp1F = 0;
    func_15194794(arg0, arg1, &sp1F);
    if (arg1->interaction_state == 1) {
        arg0->immune = (u8)0xFF;
        arg1->immune = (u8)0xC8;
        D_800D1580 = 0x60000; // 393216
        func_15072740();
    }
}

void func_15074EE8(struct127 *arg0, struct127 *arg1, s32 arg2) {
    if (arg1->interaction_state == 1) {
        arg0->immune = (u8)0xFF;
        arg1->immune = (u8)0xC8;
        D_800D1580 = 0x70000;
        func_15072740();
    }
}

void func_15074F30(struct127 *arg0, struct127 *arg1, s32 arg2) {
    arg0->unk232 = arg1->unk109;
    arg0->unk218 = 0;
}

void func_15074F48(struct127 *arg0, struct127 *arg1, s32 arg2) {
    f32 dx = -2641.0f - arg0->x_position;
    f32 dz = arg0->z_position - 3039.0f;

    arg1->unk76 = func_1505A630(dx, dz, 0);
    arg1->xz_velocity = sqrtf((dx * dx) + (dz * dz)) * 0.03f;
    func_15194978(arg0, arg1);
}

void func_15074FD4(struct127 *arg0, struct127 *arg1, s32 arg2) {
    if (arg1->interaction_state == 1) {
        arg0->immune = (u8)0xFF;
        arg1->immune = (u8)0xC8;
        D_800D1580 = 0x60000;
        if (arg0->id == 0x8E) {
            D_800D1580 = 0x140000;
        }
        func_15072740();
    }
    func_151942B0(arg0, arg1, arg2);
}

void func_15075050(struct127 *arg0, s32 arg1, s32 arg2) {
    arg0->unkB8 = 5.0f;
    if (arg0->xz_velocity > 0.0f) {
        arg0->unkB8 = -5.0f;
    }
    arg0->gravity = 5.0f;
    arg0->y_velocity = 12.0f;
}

void func_150750A4(struct127 *arg0, s32 arg1, s32 arg2) {
    arg0->gravity = 5.0f;
}

void func_150750C4(struct127 *arg0, struct127 *arg1, u8 *arg2) {

    if ((arg1->id  == 0x88) && ((s32) arg0->unk107 < 0x37)) {
        arg0->unk138 += 3;
    }
    func_15194794(arg0, arg1, arg2);
    if (arg1->id != 0x53) {
        func_15145A50(arg1);
        arg1->health = (u8)0;
        func_1507CD64(arg1, 8);
        *arg2 = (u8)39;
    }
}

#ifdef NON_MATCHING
// player_find_owned_object: the first live object (state != 0, id != 0xFF) of D_800CC2D0[0..25] whose owner byte
// +0x65 is `owner`'s player number + 1, or NULL (P151). The other two arguments are not read.
struct127 *func_1507515C(struct127 *owner, struct127 *unused1, s32 unused2) {
    struct127 *o;
    s32 i;

    for (i = 0; i < 26; i++) {
        o = &D_800CC2D0[i];
        if (o->interaction_state != 0 && o->id != 0xFF && o->unk65 == (owner - D_800CC2D0) + 1) {
            return o;
        }
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507515C.s")
#endif
