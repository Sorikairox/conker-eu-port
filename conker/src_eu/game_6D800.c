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
#pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/func_150403C8.s")

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
