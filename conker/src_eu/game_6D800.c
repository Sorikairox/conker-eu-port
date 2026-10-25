#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15040350(void *arg0, u32 arg1) {
    s32 i;

    D_800C68A0 = D_800848B0 = 0;
    D_800C68A1 = 0;

    for (i = 0; i < 16; i++) {
        D_800C6860[i] = -1;
    }
    D_800C6860[0] = 0;
    func_150403C8(arg0, arg1, 0);
}

// contains jump relative
#ifdef NON_MATCHING
void func_150ADC50(void);
void func_10008090(void);
void func_15040CC8(u8 *arg0);
s32 func_15040754(struct148 *arg0);

/* debug trap: error code 0x0C00005B in D_8003C8E0, then the break handler */
#define DL_TRAP() (D_8003C8E0 = 0x0C00005B, func_150ADC50())
/* trap, dump the command (func_15040CC8) and stop in func_10008090 with the frame index D_800BE9C0 flipped */
#define DL_STOP(c) (func_15040CC8((u8 *) (c)), DL_TRAP(), D_800BE9C0 = 1 - D_800BE9C0, func_10008090(), \
                    D_800BE9C0 = 1 - D_800BE9C0)

// dl_validate: debug walk over a display list of 8-byte commands until `end` (or, with end 0, until G_ENDDL 0xDF),
// following G_DL (0xDE) branches through the segment table D_800C6860 (at most 20 deep, target must be a cached
// 8-aligned KSEG0 address) and tracking G_MOVEWORD segment writes (index 6) and G_SETTIMG (D_800848B0). Primitives
// (0xE4 / 0xE5 / 0xF6, 1, 5, 6, 7, 0x10-0x1F) mark D_800C68A0 "drawn since pipe sync", G_RDPPIPESYNC clears it; an
// RDP state command (0xE2 / 0xE3 / 0xEA-0xEE / 0xF7-0xF9 / 0xFB-0xFF) while it is set, a failed command check
// (func_150408CC / func_1504082C / func_15040754) or a bad branch stops in the debugger; unknown opcodes trap.
void func_150403C8(void *list, u32 end, s32 parent) {
    u32 *dl = list;
    s32 bad = 0;
    s32 needSync;
    u32 w1;
    u32 addr;

    while (end == 0 ? *(s8 *) dl != (s8) 0xDF : (u32) dl < end) {
        needSync = 0;
        switch (*(u8 *) dl) {
            case 0xDE:
                w1 = dl[1];
                bad = func_150408CC((struct148 *) dl);
                addr = ((w1 & 0xFFFFFF) + D_800C6860[(w1 >> 24) & 0xF]) | 0x80000000;
                if (++D_800C68A1 == 20) {
                    func_15040CC8((u8 *) dl);
                    DL_TRAP();
                }
                if (addr >= 0x80000001 && addr < 0xA0000000 && !(addr & 7)) {
                    func_150403C8((void *) addr, 0, (s32) dl);
                } else {
                    DL_STOP(dl);
                }
                if (D_800C68A1 != 0) {
                    D_800C68A1--;
                } else {
                    DL_TRAP();
                    D_800BE9C0 = 1 - D_800BE9C0;
                    func_10008090();
                    D_800BE9C0 = 1 - D_800BE9C0;
                }
                break;
            case 0xE7:
                D_800C68A0 = 0;
                break;
            case 0xE4:
            case 0xE5:
            case 0xF6:
            case 6:
            case 7:
            case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
            case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31:
                D_800C68A0 = 1;
                break;
            case 5:
                bad = func_1504082C(dl);
                D_800C68A0 = 1;
                break;
            case 1:
                bad = func_15040754((struct148 *) dl);
                break;
            case 0xFD:
                D_800848B0 = dl[1];
                break;
            case 0xFF:
            case 0xE2:
            case 0xE3:
            case 0xEC:
            case 0xED:
            case 0xEE:
            case 0xF7:
            case 0xF8:
            case 0xF9:
            case 0xFB:
            case 0xFC:
            case 0xFE:
            case 0xEA:
            case 0xEB:
                needSync = 1;
                break;
            case 0xDB:
                if (((dl[0] >> 16) & 0xFF) == 6) {
                    D_800C6860[(s32) (dl[0] & 0xFFFF) / 4] = dl[1];
                }
                break;
            case 0xD3: case 0xD4: case 0xD5: case 0xD6:
            case 0xD7: case 0xD8: case 0xD9: case 0xDA:
            case 0xDC: case 0xDD: case 0xDF: case 0xE0: case 0xE1:
            case 0xE6: case 0xE8: case 0xE9:
            case 0xEF: case 0xF0: case 0xF1: case 0xF2: case 0xF3:
            case 0xF4: case 0xF5: case 0xFA:
            case 0: case 2: case 3: case 4: case 8:
                break;
            default:
                DL_TRAP();
                break;
        }
        if (needSync && D_800C68A0) {
            func_15040CC8((u8 *) dl);
            D_800C68A0 = 0;
            DL_TRAP();
            D_800BE9C0 = 1 - D_800BE9C0;
            func_10008090();
            D_800BE9C0 = 1 - D_800BE9C0;
        }
        if (bad) {
            bad = 0;
            DL_STOP(dl);
        }
        dl += 2;
    }
}
#undef DL_STOP
#undef DL_TRAP
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/func_150403C8.s")
#endif

s32 func_1504072C(s32 arg0) {
    if ((arg0 & 7) != 0) {
        return 1;
    }
    return 0;
}

void func_15040748(s32 arg0) {
}

s32 func_15040754(struct148 *arg0) { // overly simple
    s32 temp_a2;
    s32 temp_a1;

    temp_a1 = (arg0->unk0 >> 1) & 0x7F;
    temp_a2 = (arg0->unk0 >> 12) & 0xFF;
    temp_a1 = temp_a1 - temp_a2;

    if (temp_a1 < 0) {
        return 1;
    }
    return func_1504072C(arg0->unk4);
}

void func_150407A0(void) {
}

void func_150407A8(s32 arg0) {
}

void func_150407B4(s32 arg0) {
}

void func_150407C0(s32 arg0) {
}

void func_150407CC(s32 arg0) {
}

void func_150407D8(s32 arg0) {
}

void func_150407E4(s32 arg0) {
}

void func_150407F0(s32 arg0) {
}

void func_150407FC(s32 arg0) {
}

void func_15040808(s32 arg0) {
}

void func_15040814(s32 arg0) {
}

void func_15040820(s32 arg0) {
}

s32 func_1504082C(u32 *arg0) {
    s32 tmp0 = (*arg0 >> 16) & 0xff;
    s32 tmp1 = (*arg0 >> 8) & 0xff;
    s32 tmp2 = (*arg0 >> 0) & 0xff;

    if ((tmp0 & 1) || (tmp1 & 1) || (tmp2 & 1)) {
        return 1;
    } else {
        return 0;
    }
}

void func_1504086C(s32 arg0) {
}

void func_15040878(s32 arg0) {
}

void func_15040884(s32 arg0) {
}

void func_15040890(s32 arg0) {
}

void func_1504089C(s32 arg0) {
}

void func_150408A8(s32 arg0) {
}

void func_150408B4(s32 arg0) {
}

void func_150408C0(s32 arg0) {
}

s32 func_150408CC(struct148 *arg0) {
    return func_1504072C(arg0->unk4);
}

void func_150408F0(s32 arg0) {
}

void func_150408FC(s32 arg0) {
}

void func_15040908(s32 arg0) {
}

void func_15040914(s32 arg0) {
}

void func_15040920(s32 arg0) {
}

void func_1504092C(s32 arg0) {
}

void func_15040938(s32 arg0) {
}

void func_15040944(s32 arg0) {
}

void func_15040950(s32 arg0) {
}

void func_1504095C(s32 arg0) {
}

void func_15040968(s32 arg0) {
}

void func_15040974(s32 arg0) {
}

void func_15040980(s32 arg0) {
}

void func_1504098C(s32 arg0) {
}

void func_15040998(s32 arg0) {
}

void func_150409A4(s32 arg0) {
}

void func_150409B0(s32 arg0) {
}

void func_150409BC(s32 arg0) {
}

void func_150409C8(s32 arg0) {
}

void func_150409D4(s32 arg0) {
}

void func_150409E0(s32 arg0) {
}

void func_150409EC(s32 arg0) {
}

void func_150409F8(s32 arg0) {
}

void func_15040A04(s32 arg0) {
}

void func_15040A10(s32 arg0) {
}

void func_15040A1C(s32 arg0) {
}

void func_15040A28(s32 arg0) {
}

void func_15040A34(s32 arg0) {
}

void func_15040A40(s32 arg0) {
}

void func_15040A4C(void) {
}

void func_15040A54(s32 arg0) {
}

void func_15040A60(s32 arg0) {
}

void func_15040A6C(s32 arg0) {
}

#ifdef NON_MATCHING
extern void (*D_80084840[])(u8 *);
// dl_walk_call_handlers: P259: walks the display list from `dl` (8-byte F3DEX2 commands) while the command pointer
// is <= `end` or a G_DL call is open, and passes every command from `from` up to `end` to its opcode handler
// D_80084840[op]. It resets the segment table D_800C6860 (all -1, segment 0 = 0), records G_MOVEWORD segment
// writes (G_MW_SEGMENT), follows G_DL (0xDE) calls into known segments (unknown segment: skipped) and returns on
// G_ENDDL (0xDF) to the saved command; G_VTX (1) only steps (the asm counts its vertices in an empty loop).
// No callers in the ROM (only the symbol table names it).
void func_15040A78(u8 *dl, u8 *from, u8 *end) {
    u8 *stack[21];
    u8 *cmd;
    u32 w0;
    u32 w1;
    s32 seg;
    s32 depth;
    s32 active;
    s32 i;
    u8 op;

    for (i = 0; i < 16; i++) {
        D_800C6860[i] = -1;
    }
    D_800C6860[0] = 0;
    depth = 0;
    active = FALSE;
    cmd = dl;
    if (end < cmd) {
        return;
    }
    do {
        if (cmd == from) {
            active = TRUE;
        }
        op = cmd[0];
        if (active) {
            D_80084840[op](cmd);
        }
        if (cmd == end) {
            active = FALSE;
        }
        switch (op) {
        case 0xDE: // G_DL
            stack[depth++] = cmd + 8;
            w1 = ((u32 *) cmd)[1];
            seg = (w1 >> 24) & 0xF;
            cmd += 8;
            if (D_800C6860[seg] == -1) {
                depth--;
            } else {
                cmd = (u8 *) (((w1 & 0xFFFFFF) + D_800C6860[seg]) | 0x80000000);
            }
            break;
        case 0xDF: // G_ENDDL
            cmd = stack[--depth];
            break;
        case 0xDB: // G_MOVEWORD
            w0 = ((u32 *) cmd)[0];
            w1 = ((u32 *) cmd)[1];
            if (((w0 >> 16) & 0xFF) == 6) { // G_MW_SEGMENT
                D_800C6860[(s32) (w0 & 0xFFFF) >> 2] = w1;
            }
            cmd += 8;
            break;
        default:
            cmd += 8;
            break;
        }
    } while (cmd <= end || depth > 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/func_15040A78.s")
#endif

extern void (*D_80084840[])(u8 *);

void func_15040CC8(u8 *arg0)
{
  u8 *new_var2;
  s32 i;
  short new_var3;
  u8 *p;
  u8 *new_var;
  i = 0;
  do
  {
    do
    {
      i += 1;
    }
    while (0);
 } while (i < 0x10); i = -0x14; do { new_var2 = (new_var = arg0 + (i * 8)); p = new_var2; D_80084840[*p](p); new_var3 = 1; i += new_var3;
  }
  while (i < 0xA);
  if (D_800848B0 != 0)
  {
    func_1500390C(D_800848B0);
  }
}
// NON-MATCHING: todo
// void func_15040CC8(s32 *arg0) {
//     s32 temp_a0_2;
//     s32 temp_s0;
//     s32 temp_s0_2;
//     s32 *temp_a0;
//     s32 phi_s0;
//     s32 phi_s0_2;
//
//     for (phi_s0 = 0; phi_s0 < 16; phi_s0++)
//     {
//         // just waste time?
//     }
//
//     phi_s0_2 = -0x14;
// loop_3:
//     temp_a0 = arg0[phi_s0_2]; // * 8) + arg0;
//     D_800844B0[*temp_a0](temp_a0);
//     temp_s0_2 = phi_s0_2 + 1;
//     phi_s0_2 = temp_s0_2;
//     if (temp_s0_2 < 0xA) {
//         goto loop_3;
//     }
//     temp_a0_2 = D_800848B0;
//     if (temp_a0_2 != 0) {
//         func_1500390C(temp_a0_2);
//     }
// }

void func_15040D60(s32 arg0) {
}

void func_15040D6C(s32 arg0) {
}

void func_15040D78(s32 arg0) {
}
