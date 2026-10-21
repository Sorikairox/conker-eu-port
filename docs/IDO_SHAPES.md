# IDO 5.3 matching recipes (EU Conker, `-O2 -g3 -mips2`)

Read this before matching work. Recipes are grouped by topic; each has one example function
(`func_XXXXXXXX`, look it up in `conker/src_eu/` with `grep -rn`). Entries tagged **RULED OUT** are hypotheses
that were tested and failed: do not repeat them. Entries tagged **OPEN** are shapes with no known recipe.
Session numbers (sNN) point to `docs/sessions/sNN.md` for the original discussion.

Workflow reminders (details in HANDOFF.md and the tool index): always look at the first compile error / the
callee prototypes and call arities **before** restructuring (about two thirds of cheap matches were call fixes);
`m2c/mine func draft.c` prints your asm on one line; `tryall` can screen hundreds of mechanical variants in
minutes; the permuter finishes register/temp/operand-order leftovers (DIFF <= 9) and is a bad tool for wrong structure.
Constructs that only exist to coax the compiler get a `// fakematch: <why>` comment.

## 1. Calls, prototypes, arities

1. **Check the call before the body.** Untouched `a0..a3` that the function reads before a `jal` are pass-through
   arguments of the callee; m2c drops them (`func_15100248`, `func_150DF0D8`, `func_150EF328`, `func_15182CD8`).
   The opposite also happens: m2c invents args when the callee is a C function with fewer params (`func_1516D850`,
   `func_15179108`, `func_15088D24`, `func_150ED7B4`). Read the definition (`protocheck.py --sig f`, `draftcheck.py`) first.
   Count `a0..a3` + stack writes in the ref before suspecting anything exotic: "shape C" `func_150473A0` was just a
   5-param callee, `func_15173298`/`func_1519F928`/`func_15157E08` were missing call args (s26).
2. **Stale register = fewer args.** If the asm sets no register for an argument, call with fewer args (`func_15183EE4`,
   `func_1511ACC0`, `func_150D03A8`). A handler stored as 3-arg in a table that only reads `a0` must be declared 1-arg for the
   C to spill like the ref (`func_150D03A8`). A callee with fewer params than the header: if the ref does not store `a2` at entry,
   it has 2 params; change the header and drop the arg at the single caller if the build stays identical (`func_151B6150`,
   `func_15178E14`; do not use `()` + K&R, it shrinks callers).
3. **Floats in prototypes.** A float following int args goes in `a1/a2/a3` as bits, so the prototype is `(u8, f32, f32)`, not an
   int plus `f12` (`func_1501BFF0`, `func_1504627C`). `lw` of a field into `a1/a2` means the param is `s32`, not `f32`
   (`func_1511C37C`). Float wrapper that passes an untouched `a0/a1`: first params are pointers, floats after an int travel in
   `a2/a3` (`func_150E2EA4`: `(s32, f32, f32, f32, ...)`; `func_150639D8`; `func_15047E70`). A whole family takes `f32 arg2`, so
   its header needs real prototypes: an unprototyped K&R call promotes f32 to double (dispatch family, `func_15045A70`).
   `f32` params after an `s32` are stored/reloaded by `lw`/`lwc1` (`func_1510B8AC`); a callee prototype with an `f32` 3rd param
   gives `mtc1 a3,f12; mfc1 a2,f12` (`func_15157E08`). An f32 stack arg handed on goes through `lw a3,off(sp)`; keep the header's
   `f32 arg4` (`func_15095EA0`). Float args occupy a0..a3 slots, so a stack arg may need dummy `s32 arg4, arg5` (`func_1515A120`).
4. **Narrow prototypes make the prologue.** A `u8`/`s16` callee param fed by the function's own `u8`/`s16` param gives
   `sw a0; andi t6,a0,0xFF; or a0,t6` and `sll/sra` for free (`func_150D07C4/0644`). With `s32` params nothing is truncated. An `s32`
   call result passed to a `u8` param gets `andi`. A `u8` return type on a callee (`func_150ADA20` was `u8`) puts `andi v1,v0,0xFF`
   on every kept use: the ref had `or v1,v0,zero`; fix the header (`s32`, 189 call sites, build unchanged). Wrong `void` prototypes hide a
   return value the ref uses (`func_1513EDE4`, `func_15083568`...): `protocheck.py` finds those. `m2c` types unused call results as
   `s32`; a non-void prototype makes IDO avoid `v0` and shifts allocation, so use `void` where the ref ignores the value (`func_1503F5A0`).
   A prototype whose callee re-truncates only one arg: `(s32, s32, s32, u8)` (`func_1515D4D4`, found via `PERMUTER CHANGED DECL`).
5. **Callee defined/called implicitly later in the same file** = CERR `redeclaration`. Put a forward prototype above the first use
   (`tools/eu_port/fwdproto.sh <file> '<proto;>'`; for `void` functions `void f(void *)`), move the file's later `extern`/prototype lines
   to the head and delete the originals, and edit the file's prototype too when the draft changes a return type (`func_151DE080`,
   `func_1514E128`, `func_15095470`, `func_151E86A4`, `func_15199EF0`, `func_1518FE50`). A name used as a *variable* in the file
   (`extern s32 func_151E5564;`) must become a function prototype first. A callee declared in another file only (`s32 func_151149AC(u8)`)
   needs a forward prototype in the draft, else the `andi a0,a2,0xFF` is missing. Draft prototypes that a later-applied function of the same file defines
   must be dropped (`func_15172474`). Draft `//HOIST` / `//DROP` directives (declfix) do this automatically for clone drafts.
6. **K&R definition** when a C caller passes more args than the callee reads: `void f(arg0) u8 *arg0; { ... }` avoids the
   `number of arguments` clash and keeps both codegens (`func_1507EE9C`). The permuter returns NOSYM on K&R, give it the ANSI form.
   A K&R definition `f(a,b,c) u8 *a; u8 b; s32 c;` makes IDO store all three args at entry (`func_150F2910`, partial).
7. **Caller passes more args than the callee takes**: put the 4-arg prototype in the caller's file, the definition has 3 params
   (`func_151CFE48`, `game_eu_DCEF0.c`).
8. **Varargs**: `func_151F0754`, `func_1502B5C8`, `func_1502B8E0` (printf-like) were skipped; OPEN.
9. **Callee already C with `f32` param and a clone dispatch family**: give it a header prototype (`s32 func_150472F4(u8 *, f32, u8 *);`).
10. **Hand-written asm** (`Handwritten function` marker, `mtc0`, `eret`, `cache`, `sd/ld`, `lwr/swr`) is not C: skip. `-mips2` cannot emit
    `sd/ld/dsll` (`func_150A7B80`, `func_150ADA20` 64-bit PRNG, `func_150DFE40` lwr/swr): `u64` stores become two `sw`; would need a per-file `-mips3` build.

11. **Session 33 additions.** `fwdproto.sh` also fixes a file-local prototype that sits after its first use: delete the later line, insert it at the head (`func_150E3850`, `func_150E3788`, `func_1515F4E4`; callee `f32`/`void` types from the definition,
    `void` for the callee the ref ignores). `extern s32 D_x;` that the draft calls as a function is really a function-pointer table: `extern void (*D_x[])(u8 *);` (`func_15040CC8`, `func_15174F68`, `func_1514D880`).
    A pointer compared with `&D_800D121C` needs `(struct127 *)&D_800D121C`.

12. **Session 34 additions.** An untouched `a0` that the callee receives next to constants is a pass-through 4th argument (`func_15044C54`: `allocate_memory(arg0, 1, 0, 0)`).
    A caller in the same file passing more args than the real callee takes (implicit decl in the file): forward-declare it unprototyped, `fwdproto.sh file 's32 f();'`, and define the real arity (`func_1517F54C`; for a self-redeclaration with a
    3-arg file prototype, replace the file's prototype by `s32 f();` and define 2 params, `func_1509D274`). A callee C definition with `u8` param: drop the explicit `& 0xFF` from the argument, IDO makes the `andi; or a0,t6` itself (`func_15131D98`).
    Callee defined later as a function but drafted as `extern s32 f;`: declare `void f(void);` and pass `(s32 *)f` (`func_150D513C`).

## 2. Stack frame and locals

1. **Declaration order decides slots**: first declared = highest address. A lone 4-byte local before/after a struct moves it by 4
   (`func_1500A6D8`: `struct220 sp48; f32 sp30[6]; s32 temp_v0; u8 sp24[2][3]; s32 i;` found by `stackfix.py`; twin `func_1500A7E8` also needed the
   `unk14` store moved before the `sp48` stores + permuter). `s32 buf[7]; u8 *r;` puts `r` below `buf`; declare `r` first for the higher slot
   (`func_1514DFA8`; `func_1514DEE8` the other way). `stackfix.py` finds orders in tens to hundreds of candidates.
2. **Out-parameter locals are 12-byte vectors**: `s32 spA8[3]`, not `s32 spA8` (`func_150FE320`, `func_150FDDA0`, `func_15150108`: `s32 sp34[3]; s32 sp28[3];`).
   Frame = sizes of locals: check `u8 *sp50[16]`, 8-byte structs (`struct {u8 *unk0; u8 unk4; u8 unk5; s16 unk6;} sp20` for `func_1514F3E0`).
3. **Particle-spawner data-structure form** (recipe B, 7+4 members): `s8 sp48[8]; s32 sp3C[3];` with `*(s16 *)(sp48 + 2) = rand() % N + K;
   sp48[4] = 0; sp18[5] = 1 << (*(u8 **)(arg0 + 0x318))[0x23D];` then `func_151D8E18(sp18, 0, 0xFF, 1)`. `sp[6] = -1` needs `s8` (a `u8`
   array gives `li 255`). Members: `func_151D44C4/45A4`, `func_151C09C8`, `func_151C1E10`, `func_150B64E0`, `func_151C5C54`, `func_151BC494`, `func_150FED54`,
   `func_151001BC`, `func_150FE808`, `func_151C1FB8`. m2c's `sp48/sp49/sp4A/sp4C` byte/half locals passed by address are exactly this.
4. **One-byte local passed by address**: `s8 sp30[8]` / `s8 sp24[4]` array (assign `sp[0]`, pass `sp`) puts the byte at the ref offset
   (`func_150D09D4`, `func_150B42B0`); `u8 sp24[4]` for a `u8` passed by address (4-byte slot).
5. **Named locals take slots even when unused; unnamed spill temps (an `f32` result alive over two calls) go below.** Do not name spilled float
   results: put the calls inline in the argument list (IDO evaluates left to right) and put one unused `s32 pad;` first (`func_150FE320`
   `// fakematch`, found by brute-forcing 5040+1680 declaration orders with `tryall`). Size of a pad for a big frame gap =
   (ref frame - highest used offset)/4: `s32 pad[15];` first (`func_150F9ED0`, fakematch).
6. **A default `var = 0;` before a call that returns** is live across the call and grows the frame by 8: set it after the calls or return constants
   from the branches (`func_150D368C`, frame 0x28 -> 0x20).
7. **A named local used once can grow the frame**: inline the expression (`func_15174AA4`, `func_15101610`: `u8 t` 0x28 -> 0x30). A named `f32` temp
   grew it by 8 (`func_150B00D4`); a named `s16` local for `(s16)arg1` by 8 (`func_15019BB8`, inline the cast).
8. **Variable scope**: declaring `bit`/`sp40` **inside the loop body** puts them at sp+0x44/0x40; function scope gives 0x48/0x4C and pads grow the
   frame (`func_15016588`, lw of an uninitialised local).
9. **Reuse one pointer/local for two unrelated values** (table entry then the spawner result: `func_150139AC`; `arg0` itself: `func_150144B8`) removes a slot.
   A value used twice without a name (`arg1 + 4` written twice) is spilled where a named local would not be (`func_1514FBB0`). `s32 v = *(s16 *)p;
   v = v * arg1;` numbers temps like the ref (`func_1516FEF4`).
10. **Parameter as the temp** (`arg0 = arg0 - 1;` keeps the table index in `a0`, `func_150E3C3C`). `arg0 = func(arg0)` spills into the param home so the frame
    stays 0x18 (`func_150ED750`). Parameter-as-temp otherwise "adds homing" and mostly did not help.
11. **Stack-passed 5th-7th params**: `lw t8,0x18($sp)` in a leaf with a 4-reg prologue is the 7th parameter: add dummy `arg4/arg5` (`func_151C8D5C`).
12. **Unused-param homing**: IDO homes unused `a1/a2` when the prototype has them (`func_150D03A8` SIZE+2 with 3 params); the ROM only homes what the real
    signature has. `s8 arg` makes IDO home `a1`; an `s32` stores the byte directly (`func_1503E1FC`).
13. **Hidden frame bytes** (`func_150144B8`: `tmp.unk1C *= D_80096A38` costs 8 bytes; `func_100046E4`: 16 unused bytes above `OSIoMesg sp68`): `stackfix.py --bisect`
    finds the statement; no declaration change removed the bytes. OPEN.
14. **Spill of a lone slot**: `u8 *next;` declared before `u8 *p = ...` gave slot 0x20 (`func_15179314`, fakematch); `s32 pad;` first moves a spill to 0x18
    (`func_151B9204`); `func_150F83A0` (0x18 vs 0x1C), `func_1514E014` (the ref keeps a real named local above the array: 168 orders tried), `func_1510660C` (frame 0x38 vs 0x30), `func_151C2600`
    (f32 spill 0x30 vs 0x34, DIFF2): OPEN.
15. **Local arrays from `.data`**: non-const `s32 sp1C[2] = {0x38, 0x54};` copies from `.data` (file must own that `.data`); `const` aggregates from `.rodata`;
    declare the struct before the array to get the array lower (s10). Initializer copy of an 8-byte blob: `struct_eu_s32x2 sp18 = D_800A3C40;` (`func_151343AC`).
    Locals the compiler optimises away but the ref keeps in memory: `s32 sp20[2]; s32 sp18[2];` assigned element-wise (`func_15135424`); `u8 sp1C[4]` passed to a 2-arg callee (`func_1519D4E0`).
17. **m2c `spXX` undefined locals = arrays passed by address**: `f32 sp2C[3]; s32 sp28; s32 sp24;` with the vector passed as `sp2C` and a 12-byte copy `*(vertex *)arg4 = *(vertex *)sp2C;` (`func_15107FA0`, `func_151080F8`, `func_150D9304`, `func_1519C38C`
    use `vertex sp4 = *(vertex *)arg1;` for the struct copy); matrix local `f32 sp20[4][4];` (`func_15114E8C`).
16. **`const s32 sp1C[1] = {0x5A}; func_15169260(sp1C, 1, ...)`** needs a `void *` first param and no `(s32)` cast, else the address is computed into `v0` first (`func_15169260` family, s9).

## 3. Control flow and branch shapes

1. **Early return vs else**: `if (x) { ...; return; }` lets the scheduler put the store into the `b` delay slot; `if (x) {...} else {...}` keeps the store before `b`
   and the epilogue `lw ra` takes the slot (`func_150C6BF0`, `func_150C62C0`). `if (c) r = 1; else r = 0;` (explicit else) avoids the `bc1fl ... move v0,v1` epilogue copy
   that `r = 0; if (c) r = 1;` produces (`func_151596F4`). `var = 0; if (c) var = f(); return var;` often wants early returns instead (`func_1001091C`).
2. **Switch**: write the switch on the expression (`switch (x)`, not `temp = x; switch (temp)`) to keep the value in its own register (`switchinline.py`); an explicit empty `case 0:`
   when the table starts at 0 (`func_1501C710`); merged cases `case 0xF: case 0x11:` share a constant register (`func_151A0A10`, `func_15033730`); **case order in the source =
   body layout, not compare order** (`func_1509F764`: write `case 1:` before `case 0:`); switch with a `return` default and common `return 1`: `switch (a1) { case 0xD: ...; break;
   case 0xE: ...; break; default: return f(a0, a1, a2); } return 1;` (`func_1514F6A0`, if-chain gives SIZE-1/-2).
3. **Dispatch template**: `switch (probe(a0, a2, a3)) { case 0: return g(a0, a1, a2, a3); case 1: return 0; case 2: return 1; }` (no default, no trailing return) gives
   `beqz; li at,1; beq; li at,2; beql; b end`; an if-chain gives `bnez/bnel` (DIFF20). Members: `func_15046F70`, `func_15045AF0`, `func_15047274`, `func_15046EF0`, `func_150455FC`.
4. **Handler templates**: `(obj, msg, u8 event)`: "object deleted" (event 0): `id = msg[0]; if (id == obj->ref || obj->b4 == msg->b4) func_1516972C(obj);` (the `id` local is
   required); "swap ids" (event 0x2D): `if (msg[0] == *p) { *p = msg[1]; p[4] = msg->b9; return; } if (msg[1] == *p) { *p = msg[0]; p[4] = msg->b8; }` with `p` set before the event test;
   dispatch `f = D[obj->b4D]; if (f != NULL) f(obj, msg, event);` with all three args passed (`extern void (*D[])(u8 *, u8 *, u8)`); pass-through wrappers need the callee
   prototyped with its u8 params. `arg2 == 0` first family: `if (arg2 == 0) {...} else { v = arg0 + K; if (arg2 == 0x2D) {...} }` with compares `arg1[0] == *(s32 *)v`,
   `arg1[1] == *(s32 *)v` (`func_150C620C`, template `func_1513E084`, `func_1519EAE0`, `func_151AC304`, `func_151A5338`). Table dispatch pairs: `func_150C5970/59C0`.
   Shared variable `a = *(s32 *)arg1;` assigned in both arms.
5. **Search loops**: `while (n && !found) { next = n->unk14; if (k == n->key) found = 1; else n = next; }` then `if (out) *out = n;` (`func_1514F250`, `func_1514F2AC`,
   `func_15031CBC` as do-while inside `if (n != NULL)`): the `next` load is scheduled above the compare. `bnel` index loops `while (!found && i < N) { if (x == tbl[i]) found = 1; else i++; }`:
   `func_15199954/1519C428/1519C490` (matched s30 after permuter). Pointer-table dispatch with range check `v = *(s32 *)(arg1 + 0x1C); if (v >= 0 && v < 3) D[v](arg0, arg1);` (`func_1515F858`).
6. **Clamp** = `if (x > hi) x = hi; else if (x < lo) x = lo;` (the `b L; mov.s` + shared constant register means else-if) (`func_151885BC`, `func_151834C8`).
7. **Loop shapes**: roll back what IDO unrolled: a 4x unrolled loop with remainder prologue (`andi 3`) is `for (i = 0; i < n; i++) if (tbl[i*0x24]) return 1;` (`func_15096DB0`).
   IDO unrolls `for (i = n; i != 0; i--)` with a hoisted pointer at -O2 (`func_151B0454`); `i = 0; i < n` is not unrolled. `u8 i` shows `andi 0xFF`; a `u8` loop
   counter + `u8` callee param gives `v0 = s0 & 0xFF` for free (`func_151D90D4`, `func_150D2564`); s32 form `i += 1; i = i & 0xFF; while (i < 2)` (`func_150F791C`); an `s32 *` array
   walked as `p[i + 2]`, never `(p + i*4)`; `p++` over `struct127 D[]` instead of `+= 0x32C` (`func_1507C370`); array end pointer `var_s0++ ... != (struct127 *)&D_x` (`func_15034AD8`).
   Hoisted `p + n` before the guard: `new_var = p + n; if (n > 0) { end = new_var; do {...} while (end != p); }` (`func_1510DBB0`, permuter). Loop-invariant saved-register order
   (`func_150E909C/96F8`, DIFF10): OPEN. `goto` forms for unrolled loops are worse (`func_15022BB0` DIFF22).
8. **Early-return/`&&` chains**: `&&` chains from m2c often want early returns (`func_1001091C`), several `||` operands: name every load before the test (`func_1518FA0C`),
   plain nested ifs (`func_1509FAD4`), if/else instead of fall-through into a second test (`func_1503E4E4`), `if (s) v = s; else v = f();` with two locals (`func_1511C37C`).
9. **Explicit else beats ternary/default+if** for a `0xFF` default (`func_1503DD2C`: `if (r != NULL) v = r[i]; else v = 0xFF; return v;`); computing `q = p - 0x38` before the NULL
   test keeps an explicit `addiu v1,v0,-0x38`. An `s32` function with no `return` copies `or v1,v0` in the `beqz` delay slot (`func_15014094`; void gives DIFF9); a `s32`
   definition that falls off the end: write no `return` (a `return 0;` adds `move v0,zero`) (`func_15179314`, `func_1514143C`; `void` did not match).
10. **A `0` return type vs `return`**: multiple `return X;` compile to `b end; li v1,X` + `move v0,v1` at -O2 -g3.
11. **Linked list/queue add**: `s32 i = D_count; if (i < N) { p = D_tab + i*16; stores...; D_count = i + 1; }` with the counter store last; params `s32`/`s16` (no `andi`), 5th+ from the stack (`func_1510DDF4`, `func_1517DAE8`).
12. **Unfilled delay slot / `store; jr ra; nop` in 2-case u8 handlers (shape D)**: SOLVED in s69 (see `## s69 recipes`: a declaration in the arm's block). Old notes: (`func_151AEBF0` + 6, ~176 functions). Everything matches once the loaded value is a single shared
    variable `a = *(s32 *)arg1;` assigned inside both arms, but the last arm ends `sw; jr ra; nop` in the ref. RULED OUT: `return;` in the arm or not, `goto done`, empty `else {}`, `s32` return type,
    K&R, switch, if-chain vs else-if, -O2/-O3/-g variants. Probably an instruction after the store that the original compiler deleted. Same for `func_150FE08C`, `func_151590AC`, `func_15163FEC`,
    `func_151D51E8`, `func_15193850`, `func_151B255C`, `func_151B7664`, `func_151A98CC`, and the 43-insn family (`func_150CEBA4`, `func_150D7370`, `func_150F066C`, `func_151937A4`, `func_151BEB08`, `func_150F15A0`, `func_150D7578`:
    ref has an `or a3,a0` copy; if-chain, switch, K&R, shared-pointer-first all tried; permuter best DIFF9). `func_150AEDF8` family (8 members, `arg2 == 0x2D` arm first): `sb; b L; lw ra` where
    mine puts the `sb` in the delay slot; also `func_1519ED88` (DIFF26 with `D_800E0D50 = 0;` after the call). `func_15174E90`, `func_15031C4C`, `func_151B1EC8`: delay-slot variants, OPEN.
13. **An empty `if (x < 0) {}` kept by the ref** (`func_151600E0`): IDO deletes it, also with `volatile`. OPEN. `func_150C7E68`, `func_1517F910` (hoisted `lw`s above the branch): OPEN.

14. **Object-array loops** (`struct127 *p`, `p++`, end `(struct127 *)&D_800D121C`): `p = D_800CC2D0;` must be assigned inside the `if` that guards the loop (`func_150FE290`, permuter). `arg0 - D_800CC2D0` with `struct127 *arg0` is the index; IDO materialises `D_800CC2D0` twice in the ref
    (loop pointer and index base each get their own `lui/addiu`) where mine CSEs: OPEN (`func_150626EC`, `func_1502F6B8`). An empty counting loop kept in a saved register (`func_15040CC8`): OPEN.
15. **Byte read compared with `>= 0`** keeps the `bltz`: `s32 idx = *(u8 *)(p + 0x48); if (idx >= 0)` (`func_150E3A94`). A handler's first-arm `b` delay slot can be changed by an empty `dummy_label: ;` after that arm (permuter, `func_151CB07C`, fakematch); the local `v = arg1[0]` fixes v0 reuse.
    Re-evaluating an `s16` table index inline for the call and testing `-1 != x` (permuter) fixed saved-register roles in `func_1514D880`.

16. **Session 34 (control flow).** A `s0 * 6` index in a `do {} while` is strength-reduced to `s0 += 6`; index a 2D table `D[i][off]` / `D[i][0]` (`extern u8 D[][6]`) to keep the `multiu` per iteration (`func_151E856C`, permuter finished the last 2 words).
    `(i << 3) + (s32)base` instead of `i * 8 + base` stops the same strength reduction (`func_15168E54`, DIFF14 left). A byte loop whose trip count is constant (`!= 0x10`) is unrolled by IDO as `do/while`; the `loop: ...; if (x != 0x10) goto loop;` form keeps the rolled loop (`func_1501CDA0`, DIFF13 left).

## 4. Register allocation, copies and delay slots (the "arg copy" and "reload from home" shapes)

1. **Arg copy in a1/a2/a3 spilled to the a0 home slot (shape A: `or a1,a0,zero ... sw a1,0x20(sp)` around calls)**, delete handlers `if (p->X) f(p->X); ...`
   (`func_150FE1AC`, `func_151BE6E8`): do not copy `arg0` into a named local, use `arg0` itself; define the second pointer **first, at the top**
   (`u8 *v = arg0 + 0x110;`; defined just before its first use it is folded into the load offsets and never lives in a register); compare as a **pointer-typed field** for single-load tests
   (`if (*(struct102 **)(v + 0x28)) f(*(struct102 **)(v + 0x28))` = `lw a0; beqzl a0`) but as `*(s32 *)` for double-load tests (`lw t6; beql t6; ... lw a0`, the first test of those functions).
   Table-call form: `if (*(s32 *)((u8 *)arg0 + 0x154) != 0) { f(*(f32 **)((u8 *)arg0 + 0x154), arg0); }`, `D_8008A33C[*(u8 *)((u8 *)arg0 + 0x168)](arg0)` (`func_151411E4`, `func_15141250`);
   struct-field spelling loads once into a2, wrong. Loop over two slots (`func_151C00DC`): `new_var = arg0 + 0x28; if (*(s32 *)new_var) ...` then a second `v = arg0 + 0x28` (fakematch). `u8 *v = arg0 + 0x170;`
   first, then `v[0x24] |= 5` in the branch (`func_150F527C`). A table call whose index byte is read twice: the second read as `*(volatile s8 *)` (`func_150D0544`, fakematch).
   Callee prototype `(u8 *)` instead of `(s32)` was needed for `lw a0,..; beql a0` (`func_1519F970`). Hit rate for shape A <= 100 insns was 8 of 15.
2. **`or a1,a0` / `or a2,a0` copies of a parameter** (`func_15107B9C`, `func_150C4FD8`, `func_151D1488`): `u8 *p = arg0;` as a *declaration with initializer* copies into `a1`;
   a later assignment `p = arg0;` copies into `a2`. Twin handlers: `if (*(s32 *)(p + K) != 0) func_1516972C(*(struct102 **)(p + K));`.
3. **Reload from the home slot / all args stored at entry (shape C)**: take the address of the parameter through a pointer local: `u8 **q = &arg0;` (fakematch) then `p = *q + 0x28;
   p[0x16] = p[0x16] & 0xFFFD;` in each branch, `*q` for every other use (`func_150C5060`; `func_150D380C`: `p = (*(u8 **)&arg0) + 0x28`; `func_1515D9F0` needed `s32 *q = &arg0`). It must be a real
   `*q` use; `*(&arg0)` is folded away. Only needed when the ref reloads `arg0` in every block: a plain 1-arg function with an `sw a0,N(sp)` entry spill and a reload after a call is normal (`func_15160134`: no `q`).
   **RULED OUT** for `func_150C5060`: `-O1`, `-O3`, `-g3` flags (`-O1` has the right frame/memory args but never fills delay slots), `volatile` pointee, passing `&arg0` to a dummy callee, an extra unused 4th param,
   switch instead of if-chain, K&R (arg0 goes to s0 unless its address is taken), separate pointer locals per branch, hoisting the `arg0` load above the first compare, struct-by-value (not tried), a temp `t = p[0x3E] & 0xFFFD`
   before `p += 0x28` (12 variants).
4. **`volatile` on exactly the parameter the ref stores at entry *and* reloads** (`volatile s32 arg3` in `func_15047978`: `sw a3,0x7C; lw a3,0x7C`; `volatile u8 arg2` in `func_1519E92C`): try per parameter, one at a time.
   A `volatile` arg0 is wrong. `u8 *volatile arg1` etc. get DIFF13 for the `func_150F1B78` family.
5. **`func_150F1B78` family (OPEN, DIFF6)**: `func_150F1B78`, `func_150F7890`, `func_151007B0`, `func_151D7AE8`, `func_151BE65C`... the ref loads `arg1` twice and hoists the 2nd `lw` above the `beq` (uopt does not CSE
   `arg1` across the `||` block in the ref but does in every variant of mine). Best: `q = &arg0; u8 *volatile arg1; volatile u8 arg2; a = *(s32 *)arg1; p = *q + 0x28; t = arg1; if ((a == *(s32 *)p) || (p[4] == t[4]))` = DIFF6
   (register numbering only). **RULED OUT**: `q1 = &arg1`/`*q1` (folded away), `s32 *arg1`, compare order, `!=` forms, permuter 90-700 s.
6. **Arg-copy frames**: `func_150F3794` (frame 0x30 vs 0x28 with identical spill slots), `func_151D16E8`, `func_10003C10` OPEN. `func_151A8B34/8B84`: the ref spills `a0` in the delay slot of each call, mine at entry once there are 3 calls (works
   with 2 calls). `func_150C1B60` (ref stores only a2/a3 home slots), `func_15190A2C` (`v = arg0+0x30` folded instead of kept in `t7` and spilled), `func_151AB06C`, `func_151321F4`, `func_1510DD2C`: OPEN.
7. **Dead `addiu v0,v0,K` that IDO drops** (6+ functions): IDO folds `p + K` into the offsets, but not across `p += K + 1; p--;`: write `p = base; p += K+1; p--;` then address everything with reduced offsets
   `p + (off - K)` (`func_150C6D2C`, `func_151AB730`, `func_150C63FC` K=0x58; `func_150C7E30`, `func_150C7DE0` K=0x1E0; `// fakematch`). `p++; p--;` adds 0. Dead `addiu v1,-0xC` in a jal delay slot (`func_100043B4`): `arg0 -= 2; arg0--;` made it worse, OPEN;
   `func_151C9C8C`, `func_15109100`, `func_15141478`: untried with this recipe.
8. **Indirect call through a table re-reads the index** (IDO CSEs the second `lbu`): `int new_var = 0x25; ... D[arg0[new_var]]` (constant index in a variable) or `u8 *new_var = &arg0[0x2C];` for the second read; keep a local table
   pointer `void (**tab)(u8 *, s32, u8) = D;` (`func_151635A8`, `func_15107C24`, `func_151D7958`; fakematch). A `u8` type for the second of two `= 1` stores stops IDO CSE-ing the constant across a call (`func_151E3A1C`).
9. **Re-load of a field instead of reuse**: `u16 *new_var = (u16 *)(p + 0x6C); if (*new_var) f(*new_var);` (`func_151A625C/629C`); `s32 *t = arg0[i]; if (t) { new_var = arg0[i]; f(new_var, 3); }` (`func_151D5E30`);
   a scalar field re-read instead of a temp (`arg0[0x23E]` in every comparison) removes a `move` (`func_15121C68`); compound assignment on memory fields reloads instead of forwarding:
   `*(f32 *)(p+0x2C) -= *(f32 *)(p+0x2C) * *(f32 *)(p+0x150);` (`func_1514A164`). Reload the loop-invariant instead of a `temp_f2` (`func_150D26DC`).
10. **A constant that must stay in a register** (`v0 = 2; sll t6,v0,4`): `int new_var = 2; int *new_var2 = &new_var; ... (*new_var2) * 16` (`func_1508F060`, fakematch).
11. **Pointer in v0 / roles of v0, v1**: an intermediate pointer kept in `v0` (`lw v0,0x98(a0); lw v1,4(v0)`) needs its own local; a pointer alias declared first and the other read through it (`q = arg0 + 0x28; o = *(u8 **)q;`,
    `func_1510083C`); a block-scope alias `f32 *dst = arg1;` keeps `arg1` out of `a3` (`func_151B44D8`); loop parameter itself as walking pointer plus a `start` copy (`func_1503D774`); a single pointer reused for
    base and `+= 0x58` (`func_1507F2D4`). A global kept in `v0` then moved to `a0`: `if (D) { r = D; f(r); D = 0; }` (`func_1509D464`, `func_15080FE8`). Pointer local initialised before an `if` for a register held across
    both branches (`addiu vX,a0,0x28` in two delay slots). A `u8` local also returned/tested goes to `v0` when declared `s32` (`func_150EC954`); `s32` locals instead of `u8` for loop bounds from byte externs (`func_15082D5C`).
12. **Same register for two unrelated values**: reuse one variable (`func_1519EF74`); a value reloaded instead of CSE'd means the source read it with another type/cast; sqrt result in its own local (`func_1517A220`);
    an arg homed from `arg0 ^ 0` (`(arg0 ^ 0) + 0x28` forces arg0 through its home slot, `func_150D2050`, fakematch); `if (arg0) {}` after a call keeps `arg0` live (`func_151AD110`, `func_1513A594`: `if (*(s32 *)(arg0 + 0x1D4) != 0) { if (arg0) {} }`).
13. **Constant-store order in object-init functions**: the ref has the argument-derived stores first, then the constant (0/1) stores, then the last byte store (`+0x59`); `s16` negated store before the `1`-store
    (`func_1519EEE0`, `func_15172210`, `func_15134DAC`). Statement order generally decides schedule and regs (`func_151927C0`: compute `y` first, then constant stores, then `(y << 16) + y`; `func_15133FC0/F44`, `func_150CFA88`, `func_150FF148`
    hoist the third call argument, `func_1512C5D8` store `0x384` before `0x5CC = 0`, `func_151992B0` load the `0x98` pointer before the test). Spawner store order follows the source (`func_150D2620`).
14. **Merged `jr ra; nop` stub** at the end of a `.s` (screen SIZE-1 with only the stub's words different): add `void func_eu_<addr>(void) {}` after the function (`func_15072F10`, `func_eu_1507340C`).
15. **The `jr ra` delay slot of a one-line leaf** is not filled with `-O2 -g3` but is with `-O2` (`n_cspgetstate`, per-file flags); `func_15173948` (`return arg0;`) would need such a file split. Hidden spills of `a0` like `func_151F0730` (`sw a2` not in the `jal` delay slot, `memcpy(a,b,n) + n`) OPEN.

17. **Session 34 (m2c leftovers).** `spXX` pieces of one vector: `f32 sp28[3]` and pass `sp28`; the stack order that fits is found by `stackfix.py` (declare the block-scope `s32 temp_v0` inside the `if`), then use explicit `if/else` and move one store (`func_1507E1D0`).
    A matrix local `f32 sp24[4][4]` is placed 4 bytes too low (8-aligned); `struct { f32 m[16]; } sp24s;` plus a leading `s32 pad;` gives the ref offsets (`func_15158AFC`, scheduling still differs).
    A 12-byte `lw $at; sw $at` copy is a `*(vertex *)(dst) = *(vertex *)(src);` (`func_150D247C`, `func_1514AA5C`).

## 5. Operand order

1. **Commutative integer ops**: `x += y` vs `x = x + y`, `base + i*size` vs `&((T *)base)[i]`, `(u8 *)p + i*k` vs `i*k + (u8 *)p` change `addu` operand order (`func_150243AC`, `func_15157DD0`, `func_15166774`).
   `ptr + int`: write the add in integer form `(u8 *)((s32)p + (x << 6))` (`func_151D43B4`, `func_15095470`); no help when `p` is the parameter itself (`func_15109140` DIFF12 OPEN). `(x << 6) + y` not `y + (x << 6)` (`func_150F9ED0`).
   `arg0 + *(s32 *)(arg0 + 0x50)` (`addu s0,a0,t6`): `u8 *q = arg0 + 0x50; u8 *p = arg0; p += *(s32 *)q;` (`func_15109034`, `func_150F2A00`); twin `func_151091B8` same shape. The `u8` index read into a `u32` local first (`func_151A53E4`).
   `(u32)arg0 + D*4` (`func_1503F7A0`). `multu` operands swapped (`func_151A4EB0`). `arg0 - D_800CC2D0` with `struct127 *arg0` (not `u8 *`) gives `div 0x32C` (`func_15063894`, `func_151000EC`, `func_15063A54`: both stores through `(*(u8 **)(v + 0x31C))[...]`).
   `u8 *` instead of `s32` for object pointers in loops/compares (`func_15034118`, `func_151C3444`). Pointer arithmetic on a struct pointer scales the offset: `(u8 *)temp_v0 + 0x10` (`func_15172474`, `struct102 *` + 0x10 was +0x400).
   A comma `(0, var)` flips the operands of a `beq` (`func_1502B224`, fakematch).
2. **Float ops**: try both orders of every `+`/`*` and the 4 forms of `a*b + c`. `x * k + y` instead of `y + x * k` (`func_151320EC`), `-a * b` for the negated product; `base + range * rand`: `s[2] + s[4] * func_150ADA68()` (`func_151BE7C0`);
   `addend + (x * sinf(y))` (`func_151B9190`, `func_151B90F0`); `(b*s) + a` writes the product first so IDO loads `b` before `a` (`func_15137F30`, screened 20 other drafts: no other benefit); `a + (b * sinf(x))` for one statement and `(b * sinf(y)) + a`
   for another, 16 combinations via `tryall` (`func_150D368C`); lerp `x += (t - x) * k;` without a temp (`func_150D51D4`), `(v[4] - (b = v[1])) * t + b` with separate locals loads the far operand first (`func_150E7498`); `(f32)s16 + load` (`func_1515C710`, if/else);
   statement order inside a float block (`func_150D18B0`). `x*y + z` operand forms with `m2c/mine` (`func_151B9204`); no named float temp (`func_150B00D4`). Hand-written float code beats m2c: `f32 *v = (f32 *)(arg0 + 0x70); v[1] += ...` (`func_150D0170`),
   `*(f32 *)(arg0 + 0x44) *= k` (`func_150BD498`), `+=` lerps (`func_15052260`), one product temp (`func_151CC190`). `x *= y` `mul.s` operand pairs (`func_150EAA10`, `func_151AAFFC`, `func_150351A4`): IDO canonicalises; `r*f`, `f*r`, `f + r*g`, named temps all give the same order. OPEN.
   Float register numbering in leaf functions (f0/f2/f4 vs f4/f12: `func_150AD930`, `func_150ADDE0`, `func_150ADD90`): -O1/-O3/-mips1 no help. OPEN.
3. **Operand order in compares**: `bnel $v1,$a0`: in the 0x2D arm `arg1[0] == *(s32 *)v`; `bnel t9,v1` swap case (`func_151D2E5C` OPEN). Sign extension: no `sll/sra` for `lh x; subu; sh x` -> `s32 temp` (`func_1503F1B0`); split `temp = load; temp = temp - D;`.

4. **Session 34.** Float `mul.s` with a call result: `f32_field * call()` puts the field in `ft` (`func_15131D98`); integer `(a * D) + b` for the second operand order of `addu`.

## 6. Types, tables, structs

1. **Byte constants >= 0x80** stored through `s8 *` assemble as `-1`/`0xFFC8`: use `u8 *`. `u32` bitfield reads (`bgez` + `0x4F800000` fix-up) need `(u32)` casts on the `s32` field (`func_150142EC`). `(u16)` cast on an s16 table read for `lhu` (`func_1517FA48`).
   `Handlers with u8/u16 params`: IDO homes the arg and re-truncates (`sw a2,8(sp); andi t6,a2,0xFF; move a2,t6`); `m2c/narrow.py`, `u8params.py` produce these; u16 does not always show the `or` (`func_1508220C`).
   Byte vs word reads of a struct field: m2c's `(u8)*(s32 *)p` was really byte `*p` and `*(s32 *)(p + 4)` (`func_1519E764`).
2. **Tables**: `(&D + i*4)` on an `s32` extern scales twice: use an array of function pointers / `u8 D[]` / `*(T *)((u8 *)&D + i*k)` (`func_151073F8`, `func_151D8D90`, `func_1507839C`: `*(f32 *)((u8 *)D_800CC2E8 + i * 0x32C)`).
   Byte tables: `s32 t = *((u8 *)&D + idx * 0x32C);` (an `s32` temp lands in `v0` like the ref, a `u8 t` in `v1`: `func_1503BC4C`, `func_1508F054/EFEC/F0B8`); `extern s8 D[]; D + arg0` for `lb` + compare with -1 (`func_15173218`); small tables `s16 *p` writes
   (`func_150BE938`); struct127 stride 0x32C via `(u8 *)&D_800CC2D0[arg1]` (`func_150BE938`). `s32 *` + `arg1 + temp_v0` scales by 4 (`func_1507EE24`). `u8 *sp50[16]` and a plain `for` instead of `var_s1 += 4` on a `u8 **` (`func_15094CD0`).
   Float table through `((f32 **)&D)[idx % 6U]` (`func_150E7498`); `% 5U` when the asm has `divu` (`func_1515302C`).
3. **A header type can be wrong** (`D_800D9A40` declared `s32` but is `s16 *`): inline `**(s16 **)&D_800D9A40` at each use, no local (`func_150F3978`, fakematch). The function-pointer tables in `.data` of owned files stay in GLOBAL_ASM functions or `ptrtable.py`.
4. **Struct locals / copies**: `struct { f32 x; s16 y; } sp2C;` for a memcpy source with mixed field sizes (`func_150D07C4`); effect spawner struct fields from the stores between the memcpy source and its end (`spawn.py`); aligned array fields (`f32 unk10[3]`, not `u8[0xC]`).
   Missing m2c locals: `&sp28[0]` without a declaration is a matrix `f32 sp28[4][4];` (`func_15114E28`, `func_1511084C`, `func_150F2A98`). m2c "Dereferenced a non-pointer" = store through an `s32` expression: cast `*(f32 *)(...)` (`func_1511AD48`);
   `ptr == s32 arg` = the parameter is really a pointer (`func_150EC954`). Struct types whose fields differ from a clone sibling: rewrite to raw `u8 *` offsets by hand.
5. **`D_800877D0 + 0xFF0` vs named symbol** (`func_1509CF78`): the screen accepts hi/lo relocs whose symbol+addend equals the asm line's symbol address (`_alias_ok`). `D_80042D44` is the low word of the 64-bit `D_80042D40` (`OSTime`).
6. **Pointer `memcpy` prototype** declared after its first use breaks drafts (`redeclaration of memcpy`): move the file's `s32 memcpy(...)` to the top (`game_eu_114640.c`).

## 7. Gfx macros (display-list writers)

1. m2c emits raw words; write the gbi macros (11+ matches): `0xDA380003` = `gSPMatrix(gdl++, sym, G_MTX_NOPUSH|G_MTX_LOAD|G_MTX_MODELVIEW)`, `0xDA380007` = same with `G_MTX_PROJECTION`, `0xDA380005` = `G_MTX_NOPUSH|G_MTX_MUL|G_MTX_PROJECTION`,
   `0xE7000000` = `gDPPipeSync`, `0xDB060020` = `gSPSegment(gdl++, 8, &sym)` (segment = offset/4), `0xF2...` = `gDPSetTileSize(gdl++, t, x>>7, y>>7, lrs, lrt)`, `0xEF..` = `gDPSetOtherMode(H, L)` (`0xEF302C0F`+`4`: `gDPSetOtherMode(gdl++, 0x302C0F, 4)`),
   `0xFC..` = `gDPSetCombine(m0, m1)`, `0xFB..` = `gDPSetEnvColor`, `0xDE000000` = `gSPDisplayList`, `0xDC080008` = `gSPViewport`. Return type `Gfx *` (m2c says void/u8*; `return gdl`). Raw `u32` stores gave SIZE-3.
   Examples: `func_15184114`, `func_1510D338`, `func_15110AC4`, `func_15174200`, `func_150417F8`.
2. Argument order of packed macros follows the *word*: `0xFA00F200` = `gDPSetPrimColor(gdl++, 0xF2, 0, r, g, b, a)` (m = 0xF2, l = 0). RGB from a byte table: repeat `arg3 * 3` in every index expression, no `off` local (DIFF7 vs OK).
3. Fill colour `(GPACK_RGBA5551(r,g,b,1) << 16) | GPACK_RGBA5551(r,g,b,1)` with `u8 r,g,b` stack params; a callee that takes and returns `Gfx *` mid-function: `gdl = f(gdl); ... return g(gdl, ...)`. Non-pointer extra params are `s32` unless the ref `andi`s them.
4. `0xE4/0xE1/0xF1` = `gSPTextureRectangle(gdl++, x << 2, y << 2, (x + 8) << 2, (y + 12) << 2, 0, s, t, 0x400, 0x400)`: write shifts as `<<` (`(x + 8) * 4` is folded to `x*4 + 32`; the ref does `addiu; sll`); keep `col = idx % 8; ... (idx - col) / 8` as locals.
5. `gSPViewport(gdl++, D_800BE628 + arg1 * 0x180 + D_800BE9C0 * 0x10 + 0x40)` with `(s16)arg1` inline (`func_15019BB8`, `func_15019464`: DIFF5 order of the two global loads, OPEN). Misses: `func_1510DE40`, `func_1513B83C`, `func_1513445C` (needs the `Gfx *` proto in `game_eu_15FF50.c`).
6. `gfxfind.py --hints` decodes the macro skeleton from the constants. Remaining Gfx writers (about 160) are large (100-400 insns).

## 8. Rodata, data, strings, literals

1. **Float literals need rodata ownership**: in a file that does not own `.rodata` use the extern the asm names (`D_800A0CB0`, `D_8009F970/74`: each `lwc1` has its own symbol); constants that are `lui $at` immediates (217.0f) are fine as literals. The extern
   can schedule differently from a literal (`func_1515F61C` matched once `game_eu_18B1C0` owned its rodata; `func_1510FDA0` once `game_eu_13C400` did). `apply.py` REJECTs literals in unowned files; `rodata_split.py --own <stem> --resplit` first. `rodata_literals.py` can
   change codegen: keep the externs and check `check_files` after every `--own`. Exact literal bytes matter: `6.283186f` (0x40C90FDC) not 2pi (`func_151CC190`). IDO does not merge equal float literals in a function.
2. **Strings** need `.rodata` ownership too (`func_15197F7C`, `game_eu_1C3530`). `const` local aggregates initialise from `.rodata`, non-const from `.data`.
3. **`rodata_inject` hints**: `// rodata_inject: size 0x24CB34 4` when a compiler-owned item's end is not the next reference; an `extern` stale declaration makes a block "named by C".
4. **Switch jump tables** are generated by the compiler in owned files; `rodata_bounds.py` finds multi-object rodata (late items followed by data = a second object; use `file_split.py`).
5. **`.data` ownership** needed for non-const local array copies from `.data` (`rodata_split.py <stem> <a> <b> --section .data`). A C table that references a GLOBAL_ASM function needs its prototype above the table (`game_36680`).
6. A function that "uses rodata" per `datarefs.py` may merely copy a const local array (`lw` of rodata words) or read a float via an int register.
7. `func_151EF7B0`: matches but is followed by 0x40 bytes of nop padding in its file (`game_eu_21CFC0`): apply.py REJECTs on size; needs the padding split or an asm filler block. OPEN.

## 9. Compiler flags and file-level facts

1. **libultra** is `-O1` in the EU build (stack homes for args, `register u32 saveMask`), libc `string.c`/`ldiv`/`_Litob` `-O2` with `unsigned char`; a **second copy of libultra** lives in the game segment (`game_eu_21D010`..`2205xx`, `-O1`, `#include "controller.h"`); old libultra revisions
   (OSPifRam loops of 16 words, `OS_USEC_TO_CYCLES` spelled `((u64)n * osClockRate) / 1000000LL`, `temp |= 0;` in `__osContDataCrc`). `clones.py` copies matched siblings.
2. Per-function flags were **RULED OUT** as the cause of shape C and delay-slot oddities (-O0, -g, -O1, -O2, -O3 all give wrong sizes); `-g` alone behaves as -O0.
3. `n_cspgetstate` is `-O2` (no -g3) so the `jr ra` slot gets filled.
4. `extern u64` globals get two `lui`s, tentative definitions one: keep the definition in the C file (`init_50A0`, `D_8003B260`).

## 10. Permuter usage

1. Needs `--stack-diffs` (scripted). Do not strip bodies before the target (callee register usage affects codegen); `setup.py` strips only later ones. Score 0 ignores relocation names: `try`/`repair_try.sh` is the authority.
2. Works on **register-only/scheduling/operand-order leftovers (DIFF <= 9)** and hand-improved DIFF2-8 drafts (30-50% solved, 80-200 s, 4-5 jobs, run in the background while drafting); raw m2c DIFF12+ drafts and wrong-structure drafts almost never improve; stuck DIFF1-4 that do not move in 15 min rarely do.
3. Read `PERMUTER CHANGED DECL` lines first: a wrong callee prototype was the whole difference in several cases (`func_1514F18C` void->int fixed 4 functions, `func_1515D4D4`). `volatile` suggestions are noise. Prototype changes need `verify_all.sh --quick` (all files).
4. Strip permuter junk (`do {} while (0)`, `if (!x && !x) {}`, `volatile`, `(0, x)`, `x = x;`, `goto dummy`) before judging structure (`func_15088A68`); but keep what is needed and label it `// fakematch`. Typical needed artefacts: `new_var` constants, `p += K+1; p--;`, comma operators, `(arg0 ^ 0)`, `(x & 0xFFFFFFFFFFFFFFFF)`.
5. Permuter output may change the function's return type (`volatile short`): the real build is the judge. `permute.sh` removes `nm/<func>` at the start, so never pass a draft from that dir for the same function. Give it ANSI, not K&R.
6. **RULED OUT / weak**: raw m2c drafts of the Gfx/short pools (no DIFF<=4); `PERMUTER CHANGED DECL` for `func_1000FA64` arg0 (`u16 -> s32` breaks `init_EB00`).
7. After a clean hand rewrite, `stackfix.py` finds local order/scope (`func_150D02C8`, `func_1507F2D4`, `func_1518AF80`, `func_150F0718`); it does not help frame-size cases, nor pads below (`func_15183EE4` needs a named local at 0x18).

## 11. Pool-level lessons (what to try first)

1. For short functions (<= 70 insns) with an m2c draft: first the call arities and prototypes (section 1), then the family templates (3.3, 3.4, 2.3, 4.1), then statement order/reuse-one-local; ~0.3 matches per attempt.
2. Large (70-150 insns) functions give 3-5x the bytes per call but a third of the match rate: only try drafts with a small local diff (DIFF <= 12 or one register/operand-order issue); skip frame-size/stack cases.
3. Clone drafts (`clones.py`) of matched siblings: 91% for exact skeleton matches, 80% hand-finished for near ones.

## 12. Session 36 recipes (-g audio / libultra files)

1. **Event passed as `&s16`** (m2c: `s16 sp3C; sp3C = 0x4000; n_alEvtqPostEvent(q, &sp3C, ...)`): the event is really a local struct
   `struct { s16 type; void *ptr; u8 pad[8]; } ev;` (type at +0, pointer at +4 of the event, 0x10 bytes). Declare the struct, set `ev.type`/`ev.ptr`, pass `(N_ALEvent *) &ev`
   (`func_10017604`, `func_10017438`; `stackfix.py` finds the pad). No `osSetIntMask` prototype is needed (`func_10017604`).
2. **Drop m2c temps in -g files; pointer chasing with assignment-in-condition.** `temp_t9 = p->next; if (temp_t9 != NULL)` spills the temps in -g; write
   `if ((sp2C = p->next) != NULL) { do { ... } while ((sp2C = *sp2C) != NULL); }` so the value stays in the load register (`func_10019D98`).
3. **`f32 arg1` that arrives in a1** and is read as bits: `f32 sp54; ... bits = *(s32 *)&sp54;` (union-style read of the home slot; `func_16000F8C` got to DIFF5 only).
4. **Do not add prototypes for implicitly declared int callees** that the file already calls without one: a prototype can change the arg handling (s36, `func_10004DB0`); only add them
   when the first compile error asks for it (forward prototype, section 1.5).
5. **EU struct offsets differ from US** (`auxBus` field at +0x40, US sources say 0x1C): use the raw cast read `*(T *)((u8 *)p + 0x40)` (`func_1001DA28`).
6. Near misses: `func_10010E78` (DIFF1, `multu` operand order, drop `& 0xFFFF` on a u16 param), `func_100046E4` (DIFF4, frame 0x90 vs 0x80 from locals), `func_16000F8C` (DIFF5 bits in v0 vs v1).

## 13. Session 39 recipes (CERR-class drafts below 0x130000, short fresh drafts)

1. **Callee called without its argument by a C caller** (`func_15088BFC` calls `func_150889D8()`): K&R definition `s32 f(arg0) struct127 *arg0; {...}`. In a pointer-difference function compute `idx = arg0 - D_800CC2D0;`
   *before* the `D_80087640 == NULL` test, else v0/v1 roles are swapped (`func_150889D8`).
2. **Index search loop that IDO unrolls (`bnel` ladder, SIZE+29)**: `if (n >= 2) { for (;;) { if (match) return i; i++; p++; if (i < n) { continue; } break; } }` keeps it rolled and gives the
   `bnel ... addiu` shape (`func_150889D8`; same loop in `func_15088760`/`func_15088B08`, not matched there). Constant-trip byte tables are unrolled 4x by the ref too: `for (i = 0; i < 0x50; i++) if (arg0 == D[i]) return i; return i;` is exact (`func_15041770`);
   "first free id" = `do { if (id == *((u8 *)D_800D20FC + i * 0x30 + 0x28)) { id++; i = 0; } i++; } while (i < D_800D2520);` (`func_15084208`).
3. **64-bit libcalls** (`__ll_mul`, `__ull_div`, `__ll_lshift` in the asm): `osSetTimer(&t, (25ULL * osClockRate) / 1000000ULL, 0, &mq, (void *)6)` with `extern u64 D_8002C060` (`func_1501BB20`);
   `D_800C3A60[arg0] |= 1ULL << arg1;` and `if ((D_800C3A60[arg0] & (1ULL << arg1)) != 0)` with the shift inline (`func_1501D2C4/D330`; a named `u64 bit` flips the `and` operands). The screen's DIFF1 on the second `lui` is only the alias `D_eu_800C3E84` = `D_800C3A60 + 4`.
4. **m2c prototype for an implicit-int callee with a different arity** (`func_15031C4C` takes 3 args, m2c wrote 2): delete the draft prototype and call it implicitly with the real arguments (`func_150FF550`). A callee defined later in the file with a `void`/other type:
   move the file's prototype to the head (`fwdproto.sh` does not delete the old line, remove it by hand) and fix its type (`func_150334A8`, `func_150AF6E0` `u8 *func_151149AC(u8)`, `func_15022388` `s32` -> `void`).
5. **Node walk template** (`func_150B0290`, sibling of `func_151670C0`): `node = D_800DD2C4; D_800DD5C0++; while (node != NULL) { D_800DD5C8[D_800DD5C0] = node->next; if (D_800C3E78 == ((u8 *)node)[0x3F]) func_1516972C((struct102 *)node); node = D_800DD5C8[D_800DD5C0]; } D_800DD5C0--;`
   (do not paste the m2c `struct102` typedef: redeclaration CERR). Two-list variant `for (i = 0; i < 2; i++) { node = D_800DD280[i][0x27]; ...}` is SIZE-1 only (`func_150E3B5C`: ref ends the outer loop with `bnel` + next iteration's `lb` in the slot).
6. **Early return on NULL, then a plain nested `if` for the tail** (no `else return 0`): `if (s == NULL) return 0; ... if (v != NULL) { ...; if (f <= x) { store } } return 0;` gives the three separate `or v0,zero` sites (`func_150334A8`).
7. **Pointer difference of 0xA0 structs** `(struct131 *)func_151149AC(x) - D_800DBEF4` into a local index `i`, then `D_800DC3C4[i] & 1` (`func_150AF6E0`; inline it in the subscript = DIFF24).
   `(a + off + base - base) / 0x30` needs raw `u8 *` (the header struct is 0x10 bytes) (`func_15083E0C`, DIFF19 left).
8. **Tables**: declare `extern f32 D[]` / `extern u8 D[]` and index (`func_1509E330`, `func_1501C0D0`, `func_1507EF98`, `func_150AF6E0`): the `s32 D; *(&D + i*4)` m2c form is SIZE+n. A 2-level table `((u16 **)D_800BE728[0])[idx][0]` (`func_150EDAF8`).
   Quarter-wave table with negative index (`func_150489B0`): `extern u8 D_8009A7E0[]` and `*(f32 *)(D_8009A7E0 + -(arg0 * 4))` gives `sll; negu` like the ref (`D[-arg0]` gives `negu; sll`), the plain arm needs `s32 i = arg0;`.
   The same file (`game_75E60`) is followed by 16 bytes of nop padding, so `apply.py` REJECTs it (8.7); the matching draft is in `docs/sessions/s39_func_150489B0.c.txt`.
9. **Permuter artifact worth keeping**: `p = p + 0x110; if (!arg0 && !arg0 && !arg0) {}` (empty, `// fakematch`) hoists the `addiu` above the `bnel` (`func_15102D9C/E2C`, local permuter 150 s).
10. **`f32 r = (f32)(u32expr % div); *(f32 *)(p+8) = r;`** puts the u32->f32 `cvt.s.w` result in f0 like the ref; without the named f32 it is f8/f10 (`func_15085098`).
    A `s32 arg2` (not `u8`) avoids `andi` and the home store for an untouched narrow param; `or`-ing `0x80` then storing through a table pointer (`func_15080A20`).
11. **Near misses (all in repair_log)**: `func_150952B0` (two `f32[4][4]` locals land at 0x20/0x60 = frame 0xA0, ref 0x18/0x58 = 0x98; any type/struct/pad gives the same, and `arg0` reload needs `s32 *q = &arg0`),
    `func_1506C32C` (`(&sp24)[a1]` with 4 scalar locals: frame 0x40 vs 0x38), `func_15088B08` (frame 0x30 vs 0x28 although sp18/sp24 sit at the ref offsets), `func_1503DA64` (unnamed spill at 0x20, ref 0x24),
    `func_150A00F0` (array of 12-byte structs, 2+2x4 unroll is right, ref uses a fresh `lui $at` per store), `func_1509B950` (DIFF2 permuter, pad reg v1 vs t0), `func_1509CBD4` (SIZE-1: ref copies `or s1,v0`).
## 14. Session 40 recipes (game >= 0x130000, CERR-class and the 0x2D/0 handler family)

1. **Redeclaration CERR because a caller precedes the definition** (`func_151A5290`, `func_151954B8`, `func_151A7188`): the file calls the function (or the callee) before the definition, so the
   implicit `int` declaration clashes with the C definition. Put the real prototype in the draft head (callee case, `func_151954B8`: `s32 func_1507CD64(struct127 *, s32);`) or `fwdproto.sh` it at the
   file head (caller case; pass the full path `conker/src_eu/X.c`, a bare stem fails silently). A header prototype that disagrees with the draft (`void *arg0` vs `u8 *`) is the same error: take the header signature
   (`func_15169850`, `func_151BCB54`, `func_1514F18C`).
2. **0x2D / 0 handler family** (`func_15169850`, `func_151A5290`, `func_151A9028`, `func_151937A4`, `func_151BEB08`, `func_151BAA18`, `func_151BCB54`, `func_151D2E5C`: key `arg2`, `0` = delete if `*(s32*)(arg1)` or `arg1[4]` matches,
   `0x2D` = swap the key of the object field). Matching recipe: compare `arg2` (u8) directly, no `& 0xFF`; in the `0x2D` branch keep ONE key temp (`temp_a0 = *(s32 *)(arg1 + 0)`) and re-read
   `*(s32 *)(temp_v0 + 0)` at the second compare instead of a second temp (the m2c `temp_v1` costs the register roles); a permuter key temp `new_var = *(s32 *)(arg1 + 0)` in the `0` branch (fakematch) and `s32 temp_t6 = arg2;`
   for the `0x2D` test fix the `v1/t7` roles (`func_151A9028`). The variants where the ref also copies `a0` into `a3` at entry (`func_151937A4`, `func_151BEB08`, `func_151BCB54`: `or a3,a0`, `lw a0` used as a key temp) are OPEN
   (best DIFF11 from the permuter; SIZE-1/+1 by hand).
3. **Natural-source libultra copies**: `func_151DD950` is `osEepromLongRead`; with the real source and a `u8 address` callee parameter (`address++` after the call, `andi` shows up after the increment) it matched at once.
   When a game-segment function is a libultra copy, write the SDK source, do not copy the m2c shape.
4. **Frame pads**: when the diff is only a stack slot (`sw` at 0x1C vs 0x18 / `&sp33` at 0x37 vs 0x33) and `stackfix.py` reports a `pad@... s32 sfpad;` MATCH, take it as a labelled fakematch (`func_1518FA8C`, `func_15192800`).
   `stackfix.py` takes ~2 min on a 45-insn function; run it with `run_in_background` or on small drafts.
5. **`switch` for a 5/6/default chain whose last arm is duplicated dead code** (`addiu v0,3` after the join, `func_15192800`).
6. **Vector copy / f32 operand order** (`func_151D4300`): a 3-word else-branch copy is `*(vertex *)(p + 0x20) = *(vertex *)(p + 0x50)`; `x += y * K` stays `x + (y * K)`; the sinf call `vC * sinf(x)` order fixed both `mul.s` and the frame; drop m2c `sp18 = ...` and `temp_f0` temps.
7. **Table globals typed `s32` scalar in the header** (`D_800A5770`, `D_800DDDAC`, `D_800DDE28`): index through `((s32 *)&D_x)[i]`, never `(s32 *)D_x` (that loads the value as a pointer); `u8 D_x[]` headers need `(s32 *)D_x`.
8. **Operand order of `==` is register-number driven for a loaded temp**: `(arg1->unique_id == arg0)` instead of `(arg0 == arg1->unique_id)` (`func_15142444`), `(t14 == t4)` (`func_151D2E5C`); `(s32)p + (i << 3)` instead of `p + (i << 3)` (`func_15134548`, with `i = (i + 1) & 0xFF` for the u8 loop counter).
9. **Dropping a `var_a0 = arg0` m2c copy** (`func_15110B80`): assign the result to `arg0` itself; the copy cost a `move`.
10. **List append**: `p` plain local (no `sp1C` slot), `while (cur->next != NULL) cur = cur->next; cur->next = p;` (`func_1515DA90`).
11. **OPEN**: `D_800DD280[j][idx]` two-level node searches (`func_151CEBE4` SIZE+1, `func_151A7188` DIFF32): the ref strength-reduces a second pointer in the first and does `i = (i + 1) & 0xFF` late in the second; my `for` forms hoist the increment.

## 15. Session 41 recipes (game < 0x130000: near misses, CERR-class)

1. **"Padding after the file" can be a codegen difference in a *caller*** (`func_150489B0`, apply.py REJECT 0x150 vs 0x160). The sibling `func_15048A40` in the same file calls the function through
   no prototype in the ref (extra `andi`/`move` on the argument = 0x10 bytes). Defining the callee as `f32 func_150489B0(arg0) u8 arg0; {...}` (K&R) plus a K&R forward `f32 func_150489B0();`
   before it reproduces the ref (`// fakematch`). First diff the *neighbouring* functions of a padded file before splitting it.
2. **No base local, one pointer local** (`func_1503A8FC`): `u8 *p = (u8 *)D_800CC2D0[i].unk1D4 + 0x40;` with the other accesses written as `D_800CC2D0[i].field` swaps the v0/v1 roles
   that `struct127 *b = &D_800CC2D0[i]` gave. Same family as `func_1509D49C` (not solved there).
3. **Struct-array indexing keeps an index variable**: `Gfx *p; ... *(s8 *)&p[i]` / `rec_t *p; p = &arg0[i]` stops IDO from strength-reducing `i * 8` into a pointer bump (ref `sll t,i,3; addu t,t,base`
   every iteration; `func_150337A8`, `func_1503D658`). `u8 *` + `i * 8` always gets reduced. Use `s32 v = p->t` (not `s8`) to avoid the extra `sll/sra` re-truncation.
4. **`do {} while` / `for` over a constant trip count unrolls (x4, x16)**; the ref did not unroll: write the loop with `label: ...; if (c) goto label;` (`func_15007440` SIZE+85 -> +5; also
   `func_15022304`: for-loop SIZE+28).
5. **Callee with floats only on the stack**: `mtc1 a3,f12 ... swc1 f12,0x1C(sp)` is just `f32 arg3` being copied to an outgoing stack slot, not an FP argument. Count `sw`s to 0x10..: callee
   `(s32,s32,u8 *,s32,s32,s32,s32,f32,f32,f32,f32,s32)` (`func_1503F8A8`).
6. **K&R callee when one function is called with 4 and 6 args** (`s32 func_1509BE40();`, `func_150C7C70`).
7. **`-x * 7` not `x * -7`** (`negu; sll 3; subu`) and ternary clamp `(x < -45) ? -45 : ((x > 45) ? 45 : x)` (`func_150EDBB8`).
8. **Frame pads**: `s32 pad;` first (`func_150B5E30`, `f32 sp28[3]` after it), `struct127 sp24; s32 pad[2];` for a 0x350 frame (`func_150A3794`; stores still DIFF6). `stackfix.py` finds the order
   (`func_1509C120`: `n, i, sp38[4], sp34`) once the non-stack part is OK; copying a global into a local (`sp34 = D_800D2E4C; if (sp34 == NULL ||`) was what made it OK.
9. **A cached loop bound that the ref reloads only after calls** (`func_150225D0`, `func_15088130`): `n = *cnt;` once, `n = *cnt;` again after the record test/call, loop `while (i < n)`.
10. **OPEN**: `func_1509B950` (DIFF2, pad in t9 vs v1), `func_150E3B5C` (loop tail `bnel`), `func_1507488C` (flag copies `or a1,v1` / `or a1,t8`), `func_15003570` (lbu order 0,3,1,2),
    `func_1503D658` (ref reloads `lb v1`, no CSE with the first check).

## 17. Session 46 recipes (operand order, 0x2D/0 handler family)

See `docs/sessions/s46.md` for the details. Key rule: with two plain memory-expression operands IDO emits `beq/bne/addu/multu` operands in REVERSED source order, while a named local keeps its
source position. Drop the key temp and put the `arg0`/pl field on the left (`pl->unk0 == arg1->unk0`) to get `bnel arg1field,plfield`. The whole 0x2D/0 handler family (`or a3,a0` variants
included) is solved this way; an `s32` return type in the header keeps `v0` live and blocks `bne` delay-slot filling (make it `void`).
## 16. Session 45 recipes (game < 0x130000: the 0x2D/0 handler family, arity fixes)

1. **The 0x2D/0 key handler family** `void f(struct102 *arg0, u8 *arg1, u8 arg2)` (8-byte records `{s32 key; u8 flag; ...}` at `arg0 + K`, `or a3,a0` arg copy, `jal func_1516972C`); solved
   `func_150B5D20`, `func_150CF994` (K=0x28), `func_150F0E0C` (0x170), `func_150D5E7C` (0x28, cond `0||0x2F||3`), `func_150D7370`, `func_150D7578`, `func_150F15A0` (0xA8, 0x2D arm first), `func_150F0D64` (0x60 via `*(u8 **)(arg0 + 0x60)`),
   `func_150DAA8C` (`*(u8 **)(arg0 + 0x98)`, extra 0x44 arm). Recipe: **`u8 *v = (u8 *)arg0 + K;` first** (second pointer defined first gives the `or a3,a0` copy); arm `arg2 == 0`:
   `s32 t = *(s32 *)arg1; if (t == *(s32 *)v || v[4] == arg1[4]) f(arg0);` (loading `t` first fixes the load order); arm `0x2D` with direct compares
   `if (*(s32*)arg1 == *(s32*)v) {*(s32*)v = *(s32*)(arg1+4); v[4] = arg1[9];} else if (*(s32*)(arg1+4) == *(s32*)v) {*(s32*)v = *(s32*)arg1; v[4] = arg1[8];}`.
   Arg2==0 first: plain form OK. 0x2D first (`func_150D7370/7578/15A0`): permuter needs `if (arg1) {}` in the else arm and a no-op `goto end; end: ;` after the second compare. `func_150F0D64`: `a = *(s32 *)arg1;` and no `b`.
   `func_150DAA8C`: `(u16)(cond)` around the 0x44 condition + an unused label after the store. Still open: `func_150FE08C` (leaf, `*v = 0`, DIFF5 after permuter), `func_150EFE90`, `func_150D4ED0`, `func_150FCD98`.
2. **Callee arity from the asm** (again): `func_1502CF24` calls a 5-arg function with `arg0` passed through (`func_1502EF24(u8 *, s32 *, s32 *, s32 *, s32 *)`). A callee the m2c draft calls with
   `()` but whose caller homes both args before the call takes **no args** (`func_15097DDC`: passing them loads `a1`, wrong).
3. **A callee implicitly declared earlier in the same file** (draft is CERR "redeclaration"): `//HOIST <proto>;` first line in the draft (screen.py hoists it after the last `#include`); the return type must match the use (`struct216 *func_1507BB28`).
4. **A field tested for `!= 0` and later passed as a pointer stays in a temp reg** only if tested as `*(s32 *)(p + K) != 0` (pointer-typed test loads into `a0`): `func_1502FC38`. A byte spilled across a call as a word needs `s32 v = p[4]`, not `u8`.
5. **`-10000.0f` compared as `x != c`**: `float new_var; new_var = -10000.0f;` at the top and `x != (0, new_var)` swaps the `c.eq.s` operands (permuter, `func_15033698`; fakematch).
6. **A rodata-owning file changes codegen of literals**: owning `.rodata` of `game_83300` turned `D_80099520` into the literal `0.017453292f` and `func_1505D34C` then got frame 0x28 instead of 0x30 (same C otherwise); I reverted it. `func_1505F188`
   (matching draft, needs `3.3f` and `-10000.0f` literals) is blocked on that: `extern f32 D_800999F4/F8` gives SIZE+1 (loads not CSE'd).
7. **OPEN (kept pointer folded)**: `func_150F2B20`, `func_150B9A40`: the ref keeps `addiu v0,a0,K` as a live pointer used for 3 accesses; `u8 *pp = ...`, `&s->field`, `p += K+1; p--;` all fold it away.
   `func_15062D10`: `s32 *q = &arg1;` (fakematch) with `q[0..2]` reproduces the `a1..a3` home stores; rest is DIFF49.

## s48 recipes (comma operand swap, arg-reload mul.s)

See `docs/sessions/s48.md`. Extends section 17 (s46 operand-order rule).
1. **`(0, local)` flips a commutative operand pair.** `addu`, `multu`, `mul.s`, `beq` with one named-local/call-result operand ignore source order
   (`local * mem` and `mem * local` compile the same); wrap the local in a comma, `mem * (0, local)` or `prod + (0, local)`, to get the other order. Try the 4 forms
   (`(0, x)` on each operand, both positions) with `tryall`. Solved `func_15199200`/`func_1519C52C` (`idx*0x24 + (0, temp_v1)`), `func_151A23E4` (`mem * (0, temp_v1)`),
   `func_151AAFFC` (`mem94 * (0, r)` with `r` the call result). Mark with `// fakematch`. `func_150EAA10`/`func_150351A4` (older DIFF1 mul.s) should try it.
2. **mul.s of a call result and a field** (`func_151AAFFC`): `u8 **q = &arg0; r = f(...); p = *q;` reloads arg0 from its home after the call; loads via `p`, then `p += 0x80`
   and the store uses `p + 8` with the loaded operands written as `p + 8` / `p + 0xC` (relative to the incremented pointer) so the `addiu v0,v0,0x80` is not folded.
3. **A `u8` callee fed by `(x >> 16) - 0x40`**: no `& 0xFF` in the source (`andi t8; or a0,t8` comes from the callee's narrowing) (`func_151AAFFC`, `func_151321F4`).
4. **`beq` of a loaded local and a global** (`func_15172D80`): `if (D_800BE9F0 != *temp_v1)` with no `temp_a1` local gives `lw t2; lb a1; beq t2,a1`.
5. **Float register roles of the s16 lerp family** (`func_151859C4` + 5 siblings): reading the s16 fields inline (no `temp_v0` locals) restores the size and the load order
   (arg1 field first); still open: the quotient lands in `f14` instead of `f0`.
6. **`rlog.sh` and `CONKER_ROOT`**: running `rlog.sh` in a shell without the `wt.sh env` eval appends to the MAIN checkout's repair_log.tsv. Always `eval "$(tools/eu_port/wt.sh env a)"` in the same command.
## 18. Session 47 recipes (game < 0x130000)

1. **0x2D/0 family, more members**: `func_150CEBA4` (0x2D first, K=0x18: the D7370 form unchanged), `func_150FE08C` (leaf, `*(s32 *)v = 0`; permuter: unused label in the 0x2D arm +
   `new_var = v[4] ^ 0`), `func_150FCD98` (second slot at `v + 0x18`, chained `else if (*(s32 *)(v + 0x18) != 0)`; permuter `t == (new_var = *(s32 *)v)` and `arg1[4] == v[4]` operand order).
   Open: `func_150EFE90` (two slots + 0x43 arm, no `or a3,a0` copy: SIZE-1), `func_150D4ED0` (calls `func_15031C4C`; DIFF15), `func_150F8DFC` (0x42/0x3F arms; the copy goes to `arg1` not `arg0`).
2. **`lw s3,0x28(sp)` reload of arg0 in a delete-all-slots loop** (`func_150EFD30/DE0`): shape C `u8 **q = &arg0;` `*q + 0x110` and `func_xxx(*q)` plus m2c's `struct102 *temp_a0 = ...; if (temp_a0 != NULL)` temps (the pointer-typed temps give `lw a0` in the beql).
3. **Cached loop bound reloaded after a call** (`func_1502298C`): `n = *cnt; do { ... if (e->state) { call(); n = *cnt; } ... } while (i < n)` plus a permuter `new_var = &*cnt`. A 2D table
   `extern u8 D_x[][0x19]` stops the `*4` scaling of `arg0 * 25` (use `D_x[arg0]`, not `&D_x + arg0 * 0x19` on an `s32`).
4. **Pointer arithmetic on an `s32 *` global scales by 4** (`func_150848F0`: `*(&D_8008704C + u8 * 4)` was `*16`): write `*(u8 **)(&D_8008704C + idx)`. Callee params `(s32, s32)` instead of `(u8, s32)` remove the `andi` before `or a0,s0`.
   A count that is later added to (`var_s2 += field`) must not get its own `temp_s2`.
5. **Spawner functions with a stack struct passed by address** (`func_150B7964/7A40/7C88`, HUD element creators): the ref keeps every store because the callee gets `&sp`. Declare one local struct whose first member is
   the pointer written at `sp+0x1C/0x24` (fields at the byte offsets from the struct base; `u8` fields for `0xFF`, `s8` gives `-1`), assign in the **ref store order** (the scheduler keeps it), `60.0f/170.0f` stores first so the `lui at`
   constants are hoisted like the ref, and pointer-typed tests `if (*(struct102 **)D_800D9CB8 != NULL)` (`lw a0` directly). `D_800D9CC4` is `D_800D9CB8[3]`. A named `f32 h` (for `trunc.w.s` into an `s32` field) steals a stack slot
   and shifts the struct by 4: use `sp.unkC = sp.unk20`. Open: `func_150B7DFC` (DIFF28 permuter), `func_150B7B9C` (DIFF8: struct declared before `s32 *slot`, frame 0x68 vs 0x60 in the permuter best).
6. **`f32` triple copied through `lwc1/swc1` and passed as `s32`** (`func_150B2974`): `f32 sp3C[3]; sp3C[2] = *(f32 *)(arg0 + 0x1C);` and pass `*(s32 *)&sp3C[2]` (a named `s32 sp44 = ...` loads with `lw`).
7. **`(id = arg0[4]) == D_8009C100`** (`func_1508148C`): assigning in the first compare gives the ref operand order of the `bne`s; the permuter's `& 0xFFFFFFFFu` / `^ 0` chains were all unnecessary.
8. **Leftovers with notes in `repair_log.tsv`**: `func_150C6C3C` (extra 16 stack bytes), `func_1502C8F8` (frame 0x30 vs 0x28), `func_1502B5C8` (varargs, `&arg1` fakematch OK, `sp38/sp40` land at 0x48/0x4C), `func_15077F64` (`t0 = &D_800D154C` live pointer),
   `func_150A3184` (u64 table, frame lacks `s4`), `func_1501E7A8` (loop bound `n*8` computed before the `addiu s0`), `func_15080748` (DIFF8 permuter best), `func_15012370` (DIFF10).

## s49 recipes (operand order, callee arity from m2c protos, SIZE-n loops)

1. **`goto end; end: ;` in the last arm** (`func_150EFE90`, 0x2D arm of the family, SIZE-1): the ref ends the 0x2D arm with an unfilled `sb t2,0xC(v0); b epilogue; lw ra` (target-filled delay slot) instead of `b; sb`. A no-op `goto end; end: ;`
   after the second slot compare in the arm reproduces it (same trick as the s45 0x2D-first members). With two slots the first arm needs **four named locals** loaded in ref order
   (`s32 x = *(s32 *)v; s32 y = *(s32 *)arg1; s32 p = v[4]; s32 q = arg1[4];`, compare `x == y || q == p`): that gives the `v1/a0/a2/t0` registers and the `or a3,a0` copy. Pointer-typed temps are not needed.
2. **m2c prototypes lie about arity and types; read the callee registers.** `func_150D6898` (SIZE+3) called a 9-parameter `(f32, f32, s32, ...)` prototype; the real one is `(s32, f32, s32, f32, f32, s32, s32)` (first arg int => the f32 args travel
   in GPRs: `mfc1 a1,f12`; a 32-bit constant in `a2` via `lui/ori` is an `s32` parameter; the 5th, a float, goes to `0x10(sp)`). `func_15083E20`/`func_150158D0`/`func_1503FAF0` showed the same: pass `(arg0, arg1, arg2)` through, and a callee
   param that is `s32` stops the extra `sll/sra` renormalisation of an `s16` argument (`func_1503FAF0` SIZE+3 -> SIZE+1 with `func_1510F800(s32, s32, s32)`). Then the stack slot of a float spill across a call is fixed by `stackfix.py` (declaration order `temp_f12, sp28, ...`).
3. **Sorted list insert with the mask hoisted** (`func_1509B810`): `key = arg0->unk0 & ~0xFC00;` before the empty-list test (signed `slt` needs the `int` constant `~0xFC00`; `0xFFFF03FF` is unsigned and gives `sltu`), loop as `do { ... } while (i < length)` that falls
   into the shared head-insert code (the m2c `goto`/duplicated return block gave SIZE+8).
4. **Operand order of an address sum** (`func_15019BB8`): `(u8 *)D_800BE628 + arg1 * 0x180 + ...` loads the base before the multiply (the `s32` global + int form multiplied first). Same effect as the s46 reversed-order rule for plain memory operands.
5. **Reload of a loop bound after the call** (`func_1503E00C`, still SIZE+2): the ref keeps `n = *cnt` in `a2` (the third, pass-through argument of the call) and reloads it only on the call path; named `n` lands in `s0`, an expression `*cnt` in the test gives a duplicate `s3/s4`.
   Best drafts `conker/build_port/s49/n5.c`/`q1.c`; use a 3-argument callee `(temp_a1, temp_a1, *cnt)`.
6. **Leftovers**: `func_150B7B9C` DIFF13 -> DIFF10 with `old = *slot; if (old != 0) f(old);` (pointer-typed test keeps a2 free); `func_150D2884` permuter best DIFF9 (`*(s32 *)(arg0 + 0x30) -= D_800BE9E4;` instead of a `temp_t8`,
   no `pad`; only the spill slot 0x30 vs 0x34 and t-register numbering remain); `func_15080748` (subu result lands in `t0` not `v0` whatever the temp form), `func_15013000` (load of `D_800D3094` hoisted above the two stores: no source order change moves it),
   `func_1504BA38` (the permuter's `s8 new_var2 = 0x184` is a truncation bug; clean forms give p/c/b in v0/v1/a1 instead of v1/a1/v0, DIFF27), `func_150C572C` (addiu s0/s1 order, 9 forms), `func_1509B950` (pos in t9 not v1, 6 forms),
   `func_150F8DFC` (ref puts `v = arg0+0x28` in a0 and copies arg0 to a3; every form copies arg1 instead).

## s50 recipes (m2c pointer-stride bugs, stack-passed float args, DIFF1 compare order)

1. **m2c `T *p; p += K` strides by `sizeof(T)`.** `s32 *var_v0_2; var_v0_2 -= 0xC` is 48 bytes, `f32 *var_t2 += 4` is 16, `s32 *var_s0 += 4` is 16 where the asm has `addiu 4`; a byte table walked as `f32 *var_v1 += 1`
   is 4 bytes. Retype the pointer (`u8 *`) or use `p++` / `((u8 *)base)[i + 9]` (`func_15024438`, `func_150893AC`, `func_150EBA04`). A draft whose only fault is this shows up as SIZE-1/-2 with a plausible
   shape: check every `+= K` against the asm increment first.
2. **A `lw aN`/`lui+lw` argument that the draft passes as a constant is usually a different argument**: `func_1501E0C8(arg0, &D_800C3C88)` (pass-through `a0` plus an address in `a1`), `func_151149AC(x, 1)` (the `1` is
   `addiu a1,zero,1`, not `arg1`), `func_151EFDD0()` has no arguments at all (`a0` held `&D_800D154C` for the earlier `lw`; stale register, argfix cannot tell and keeps it).
3. **Callee stack args must be counted from the asm (`sw`/`swc1` to `0x10(sp)`..)**: `func_1514CBE8` takes 12 parameters; `(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8)` with the third a **`lw a2` of an
   `f32` local** (an `f32` parameter loaded from memory travels with `lw`, not `mfc1`) and the fourth `lui a3` an `f32` literal (`251.0f`). The callee's out-parameter may be bigger than m2c's single local:
   `func_1504715C(&sp48)` fills 36 bytes, `f32 sp48[9]; f32 sp6C[3];` gives the frame 0x78 (`func_150CE0C0`). `f32 sp6C[3]` (array) rather than three locals keeps the dead-looking `sp70 = ... + 1000.0f` store, because
   `&sp6C` escapes.
4. **64-bit shift through `__ull_rshift`**: `__ull_rshift(hi, lo, 0, n)` is `u64 >> n`; write `(D_800D3510[arg0 * 3 + (arg1 >> 6)] >> (arg1 & 0x3F)) & 1` with `extern u64 D_800D3510[];` (two `lw`, shift count in `a2:a3 = 0:n`).
   The asm names the second word `D_800D3514`; the screen accepts the alias. Siblings: `func_150A29C8` (DIFF15 after the permuter), `func_150A2FCC` (needs a 3-parameter definition; header and an out-of-slice caller have 4).
5. **DIFF1 `c.eq.s fA,fB` operand order**: `if (v != 0.0f)` gave `c.eq.s f0,f2`, the ref has `f2,f0`; the permuter fixed it in seconds as `if (0.0f != D_800D154C->xz_velocity)` with the load inline (`func_1506BCC8`). Run the
   permuter on every DIFF1-2 whose only diff is a compare operand.
6. **Empty label as scheduling barrier**: the permuter's `dummy_label: ;` before the first of two calls kept a `swc1` out of the `jal` delay slot (`func_150CE0C0`, `// fakematch`).
7. **`y_position == unk180` operand order**: with two plain memory operands the compare loads them in reversed source order; the ref loads `unk180` first, so write `p->y_position == p->unk180` (the m2c form
   `unk180 == y_position` was reversed).
8. **Varargs** (`func_1502B6BC`, DIFF1): `s32 f(s32 *a, s32 b, s32 *c, s32 n, ...)` with `va_list ap; va_start(ap, n);` and `v = va_arg(ap, s32);` evaluated before the `if (*p != 0)` (the increment is unconditional in the
   ref) reproduces everything except one stack slot (`sp44` lands at 0x3C instead of 0x44; `va_list` takes a slot). Best: `conker/build_port/s50/sf2/best.c`.
9. **Not solved, notes**: `func_150EBA04` (frame OK with `s32 pad[2]` first, loop 1's `slti` becomes `bne at,4`), `func_1503EE68` (needs a 4-byte local above `f32 sp50[3]` without growing the frame), `func_1506B3B8`
   (frame 0x30 vs 0x20), `func_1505A250` (ref keeps the `arg2` home store), `func_150DE8AC` (frame 0x68 vs 0x60 with the two `struct_eu_s32x2` locals).
## s51 recipes (lerp operand order, inline pointer sums, clones.py --near)

See `docs/sessions/s51.md`.
1. **`base + prod` versus `prod + base` for an `add.s` of a float lerp** (the s16 clip helper family, 6 functions): the ref is `add.s fD, base, prod` with the quotient staying in `f0`; write `(b - a) * q + a` (product LEFT, base RIGHT).
   `a + (b - a) * q` made IDO swap the operand registers and move the quotient to `f14`. Same idea for the integer part: `(f32)(b - a) * q + (f32)a`. A denominator `(a0 - b0) + (a8 - b8)` vs `(a8 - b8) + (a0 - b0)` changes only the
   load order of `b` (try both). Reloading `*(f32 *)(arg2 + 0)` for the mirrored store is simply `*(f32 *)(arg2 + 8) = *(f32 *)(arg2 + 0)` / `-...`.
2. **`s32 D[]` global used with a byte stride**: `arg0 * 0x14 + D` scales by 4 (the 0x50 shift); write `(u8 *)D + arg0 * 0x14` and **repeat it at each use** instead of a local pointer (the local adds a stack home and 8 frame bytes). A `*(&D_x + arg0)` store
   of a byte flag needs `extern u8 D_x` (an `s32` extern scales the index).
3. **Permute independent trailing stores**: after the frame and registers match, four independent `sw` statements in a spawner/initialiser gave DIFF9 -> OK in 2 of 24 orders (`tryall` on the permutations, three batches of 8).
4. **`u8` compare against a `/ 256` quotient**: `s32 temp = *(u8 *)p; if (x / 256 >= temp)` avoids the `or v1,v0,zero` copy that a `u8 temp` plus `(s32)` cast creates (`func_15172530`).
5. **`clones.py --near 16 --draft --lax` then `screenall build/cln`** gave 5 OK of 74 drafts in the slice (twin handlers, node lookup, key search). CERR on a clone draft is often only a missing forward `extern` (copy it from the template's neighbourhood).
   `apply.py` needs a hand-written `screen.txt` (`OK <func> src_eu/<file>.c`) when the drafts were copied out of the clone directory.
6. **Dead local stores are deleted**: `sp18 = temp_v0;` keeps a pointer live only if something reads it before the call; do not expect an unused named copy to force a spill (`func_151B97C4`).

## s52 recipes (clone hand-finishing, chains, trailing stubs)

See `docs/sessions/s52.md`.
1. **`A = B = 0;` chain assignment** reproduces the "`lui v0/v1` + `addiu` pointers for the chained globals, `lui at` for the others" layout (`func_15195D9C`: `D10 = D14 = 0; D18 = D1C = 0; D20 = -2;`).
   The inner target is stored first. Plain separate statements or arrays do not give it.
2. **Float clamp + scale**: in a file that owns `.rodata`, write the literal (`arg0 >= 32767.0f`), not an `extern f32 D_...` (the extern moved a `lui` before `c.le.s`); scale in place with `arg0 *= 65536.0f; x = (s32) arg0;`
   (`mul.s f12,f12,f4`, `func_1515F5B0`). A sibling that is already matched shows which literal sits where.
3. **Trailing dead `jr ra; nop` after a function** (screen says SIZE-1 but only the last row differs in `V=1 try`): add `void func_eu_<addr>(void) {}` after it (existing recipe 14); `screen.py`/`try` measure only the named function, so
   hand-write the `screen.txt` line and let `apply.py` decide (`func_15178CC0`, `func_15195D20`). If registers differ besides the tail, change the body first (a named local `u8 *p = *(u8 **)(a1 + 0x14);` put the pointer in `v0`).
4. **`(u32)arg1 << 8`** instead of `arg1 << 8` when the ref has `lw a2,home; sll t8,a2,8; ... or a2,t8,zero` (signed shift gave a different schedule); frame pad `s32 sp30[6]` with `&sp30[1]` for a 0x48 frame and `a3 = sp+0x34` (`func_1517AF18`).
5. **Switch with no default and pass-through `a0`**: `switch (D_x) { case 2: f(arg0,1,1,1,arg1,arg2); break; case 16: f(arg0,0xA9,8,0,arg1,arg2); break; }` matched first try from the asm (`func_15171434`); a `u8` param is read with `lbu 0x27(sp)`.
6. **Permuter artifacts** that solved a DIFF18 function-pointer table call: `u8 *new_var = arg0; ... if (!arg0) {} fn(new_var);` (fakematch, `func_151A8B34`/`8B84`). A DIFF18-from-scratch `permute.sh` run (200 s, 3 jobs) is worth it on indirect-call wrappers.
7. **`clones.py --near` yield**: only dist <= 8 drafts are close to usable; for dist > 8 read the ref asm and write the body, using the draft only for file/prototypes. The NEAR header (`asm +x`, `sib -y`) lists what to change.
## s53 recipes (clone-draft finishing)

See `docs/sessions/s53.md`.
1. **A DIFF1 clone draft may be a wrong field offset, not a scheduling problem** (`func_150EAA10`): the `**` line of the word diff showed `lw t9,0x84` vs `0x8C`; the clone copied the
   template's `p + 0xC` where the target multiplies `p[0x84]` (`p + 4` after `p += 0x80`). Read the one differing word before reaching for `(0, local)`.
2. **`s32 i = arg0 * 4;` as a named local keeps the `sw v0,0x18(sp)` spill across a call and the table index in v0** (`func_150DF1A8`: `D_800A10DB[i]` / `D_800A10FB[i]` with `u8 arg0`, `i` computed once);
   the inline `arg0 * 4` twice gave DIFF2.
3. **A global handler/pointer table declared with the callee's pointer type removes the `or a0,v0` copy** (`func_150C572C`: `extern struct102 *D_800D9CF0[]; if (D[i]) func(D[i]); D[i] = 0;` the `sw zero` lands in the `bne` delay slot).
4. **A pure-zero-argument function (`s32 f(void)`) drops the `sw a0,0(sp)` home stores** that named-but-unused clone parameters produce (`func_1507F834`: SIZE+1 -> DIFF8, then DIFF6 with `u8 b = tbl[type][p[5]]; if (b == 0)`).
5. **Many `--near 24..40` clone drafts are junk** (the "template" matches on skeleton only; constants, call counts and float/int types differ): `func_150FB708`, `func_150ADACC` (data decoded as mips3 code), `func_150A7EF4` (a fragment ending in `jr t9`), `func_150226E8`.
   Judge them from the target asm first; a clone draft is worth a try only when its `NEAR n` comment lists at most ~5 differences.

## s54 recipes (typed m2c context, stack-slot layout)

See `docs/sessions/s54.md`.
1. **Typed drafts need typed prototypes**: declfix conforms a draft to the prototype already in the source file, so `u8 *arg0` stays and every field is a raw `(u8 *)arg0 + 0xNN`. `fieldinfer.py --apply-protos`
   retypes the prototypes of hinted asm functions to `struct127 *` (check_files-safe). Pointer fields in a struct must be `u8 *`, not `void *` (`void * + int` is a CERR in IDO).
2. **A `u16` callee result needs no `& 0xFFFF`**: `temp = func_1505A630(...)` (`u16` return) gives the ref's `andi v1,v0,0xFFFF`; `func_1505A184(temp_v1 - 0x3000, ...)` (`u16` first param) gives `addiu a0; andi t2,a0; or a0,t2`
   (`func_150B15D0`). Same family as s48 recipe 3.
3. **One float local for a ternary and an earlier temp** keeps f2 (`temp_f2 = 1000.0f` / `temp_f2 = 1050.0f - temp_f2 * 0.7f`, a separate `var_f2` took f12). A new named float for a product (`p`) grew the frame by 8;
   reusing an existing dead temp (`temp_f2 = (x - 820.0f) * 0.09f; ... *D * (0, temp_f2)`) did not.
4. **Declaration order = stack order, unused locals take a slot**: locals are allocated downward from the frame top in declaration order (first declared = highest), compiler spills go below the block, and an
   *unused* `s32 pad;` declared first still takes the top slot (floats +4, spill 0x40 -> 0x3C, frame may grow by 8). `func_150B15D0`: three address-taken out floats + spill at 0x40 is DIFF1 (floats at 0x4C..0x57),
   a leading pad gives the right float slots but the spill at 0x3C (DIFF2); two pads, an explicit `sp40`, `f32 v[3]`/`v[4]` and all declaration permutations (stackfix, 24 + 120 + 20 variants) do not fix both. OPEN.
5. **m2c `var += 0x32C` on a `struct127 *`** (`func_1502C494`) is still the s50 stride bug (use `++`), and `!= &D_800D121C` compares against a differently typed symbol (cast).
## s55 recipes (larger functions: vector locals, spill names, matrix arrays, arg0 as variable)

1. **m2c scalar vectors lose stores.** `f32 sp38; f32 sp3C; f32 sp40;` with `f(&sp38)` makes IDO drop the stores to `sp3C/sp40` as dead (SIZE-2..-13). Declare one array
   `f32 sp38[3]` (`vecfix.py` does it for the whole pool); this alone fixed `func_15193A24`. A 16-byte `sp88[4]` is right when the ref leaves 4 bytes above the 12-byte vector.
2. **Frame slot positions are declaration order.** The first declared stack-resident local sits at the top; named locals that live in registers still reserve a slot (even unused ones),
   so move a pointer/float name above or below the array to shift it by 4 (`temp_v0` before `sp38[3]` in `func_15193A24`, `temp_f18` before `sp6C` in `func_151A7BC0`,
   `u8 *temp_s0, *temp_s1; s32 spB4[3]; s32 var_s1; f32 spA4[3]; ...` in `func_151922C4`). Compare the first `**` lines of the diff (`sw a2,0xA0(sp)`...) with the ref's top-relative
   offsets, not the absolute ones, when the frame sizes differ.
3. **m2c `spXX = call();` names are unnamed spills in the ref.** Results of calls nested in a later call's argument list are spilled by IDO into the lowest slots; a named local takes a
   different (higher) slot. Inline them into the consuming call (`func_151A7BC0`, `func_151BC920`: `... ((func_150ADA68() * 591.0f) + -600.0f) * 0.001f ...`; `spinline.py`). Keep a separate
   `temp = call();` statement first if the ref calls before it stores constants (`sp6C[0] = 0.0f` after the `rand()` in `func_151BC920`).
4. **A callee with a C definition elsewhere and no header prototype is called as `int f(...)`.** An `f32` argument then goes in `a2/a3` as a double and the call grows by 2-3 insns (SIZE+2).
   Put `void func_15143794(s16, s16, f32, void *);` above the draft (and `f32 func_15144AA8(s32);` for a float return used with `mtc1`/`add.s f0`). Same check as recipe 1.1.
5. **`x = a < b;` as a value** compiles to `or s1,zero,zero; c.lt.s; nop; bc1f L; nop; b L; addiu s1,zero,1` when written `x = (a < b) ? 1 : 0;`, and the `if (a < b) x = 1;` form gives the same
   branch without the `b` (`func_151922C4`).
6. **u8 params: no `& 0xFF`, no `& 0xFF` on the callee argument.** A `u8` callee param (`f32 func_151423D8(u8)`) fed `sp87 - 0x40` gives `addiu a0; andi t9; jal; or a0,t9,zero` (`func_151AF064`);
   writing `(sp87 - 0x40) & 0xFF` fuses the andi into the delay slot. A `u8` param copied into `s1` and then moved to `s6` (`func_15151500`) is a register-choice problem, not a type problem.
7. **A parameter reassigned as the long-lived variable** (`arg0 = arg0 & 1;` after `sp1C = arg0 & 2;`) compiles to `sw a0,home; or a3,a0,zero`, with spill/reload through the param's own home
   slot (`sw a3,0x20(sp)` ... `lw a3,0x20(sp)` around calls) and `sw a3,0x2C(sp)` for the dead 4th param. A separate `var_a3 = arg0 & 1;` loses the `sw a0` at entry (`func_1000B638`, SIZE+2 -> OK).
8. **Matrix-array structs: `((f32 (*)[16])(arg0 + 0x7C))[D_800BE9C0][k]`** (k = 12..14 translation, 0-2/4-6/8-10 scale rows). The m2c form `arg0 + (D_800BE9C0 << 6) + off` never matched;
   the index global is reloaded for every access (u8 global vs f32 stores). Use a local `#define MTX_xxxx(a) ...` / `#undef`. A pointer `u8 *p = arg0 + 0x120` read as `*(f32 *)(p + 0xC)` stays a register
   base only after a `do {} while (0); // fakematch` between two stores (permuter, `func_15157E88`). Used by `func_1515835C`, `func_15157E88`, `func_151D7410`; the same family is open in 6 more files (s55.md).
9. **Float literals in a file that does not own `.rodata` are REJECTed by apply.py** and an `extern f32 D_xxx` instead changes the schedule (`lwc1` hoisted above the `lui`), so own the rodata:
   `rodata_split.py --own <stem> --resplit` (done for `game_eu_1D4CC0`, `game_eu_1E61C0`, `game_eu_204730`), then build and `apply.py`.
10. **Workflow for 100-200 insn drafts**: (a) `ARGFIX=1 m2cfix.py`, (b) `vecfix.py`, `spinline.py`, (c) `rt.sh f draft.c`: if `opshift` shows 0-3 shifts the draft is a permuter case (register
    allocation only); if it shows inserted `jal`/`addiu a0` the callee prototype or the vector shape is wrong; if the `addiu sp` line differs, fix declaration order (recipe 2) first.
    The permuter on 100+ insn functions rarely reaches 0 in 15 minutes unless the diff is a single schedule choice (it solved `func_15157E88` in 20 s and took `func_1515835C` from DIFF54 to DIFF31 in 15 min).


## s56 recipes (matrix/Gfx family, twin spawners, redecl/fnptr tooling)

1. **Gfx writers: type the display-list pointer as `Gfx *` and use the gbi macros** (`gSPMatrix(gdl++, MTX, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW)` = `0xDA380003`,
   `gSPSegment(gdl++, 1, x)` = `0xDB060004`, `gDPPipeSync` = `0xE7000000`, `gDPSetEnvColor(gdl++, r, g, b, a)` = `0xFB000000`, `gSPDisplayList(gdl++, p)`, `gDPSetPrimColor(gdl++, 1, 0, 255, 255, 255, a)`
   = `0xFA000100`, `gSPVertex(gdl++, v, 4, 0)` = `0x01004008`, `gSP1Triangle(gdl++, 0, 1, 2, 0)` = `0x05000204`, `gSPMatrix(..., G_MTX_NOPUSH | G_MTX_MUL | G_MODELVIEW)` = `0xDA380001`).
   The m2c `(*(s32 *)(p + 0) = ...; p + 8 ...)` chains with `u8 *` never reproduce the `or v1,s1,zero; sw w0,0(v1); addiu s1,s1,8` copies; the macros do (`func_15177360` tail,
   `func_15158838` tail, `func_151EC9A0`). `gDPSetEnvColor` drops the `& 0xFF` of the r term (`sll 24` only). Callees that take/return the list become `Gfx *`; a callee defined later in the file with an
   `s32` signature (`func_1517AF18(s32, s32)`) is called as `(Gfx *)func_1517AF18((s32)gdl, x)`.
2. **Matrix pointer indexing with a cast** `guMtxF2L(sp54, (Mtx *)MTX(arg1))`, `MTX(a) = ((f32 (*)[16])((a) + 0x10))[D_800BE9C0]` (all six family members use this; `f32 sp54[16]` for the local matrix, translation
   `sp54[12..14]`, scale loops `[0,1,2,4,5,6,8,9,10] *= k`). `sp54`/`sp94` declaration order: the matrix declared first sits at the higher address.
3. **Compute every float temp first, then do the stores** (`func_151ACDC0`, twin of `func_1514A288`/`func_1514A540`): the scheduler keeps the source order of the *dependent chains* but interleaves
   independent stores; the zero stores `sp4C[6/0x16/0x26/0x36] = 0` go after `temp_f0 = 4C*2C; temp_f14 = 50*30; temp_f2 = D[i]*f0; temp_f12 = D2[i]*f0` and the product of the *two plain memory operands* is written with the
   operands swapped (`f4C * f2C`, `f50 * f30`). Named `f32` locals each reserve a stack slot: declare them **before** a following `u8 sp37` to push it down 4-8 bytes (ref `addiu t6,sp,0x37`), and do not name
   values the ref keeps unnamed (one extra local = +8 frame). `D_800DD608[arg1]` is `extern f32 D[]`, not `*(&s32 + idx*4)`.
4. **`if (p != NULL) { ... } else { return NULL; }` followed by the common tail** gives `b L; or v0,zero,zero; b end` in the middle of the function (ref layout of the three particle twins).
   `memcpy(((u8 **)(arg0 + 0x100))[arg1], arg0 + 0xC0, 0x40)` (array of pointers) gives the `sll/addu/lw 0x100` order; `arg0 + (arg1 * 4) + 0x100` gave a different addu order.
5. **Double `sb` to the same byte (`andi t1,t9,0xFFFC; sb t1; or t2,t1,v0; sb t2`) is a bitfield assignment**: `struct { u8 hi : 6; u8 lo : 2; } *f = (void *)(arg0 + 0x73); f->lo = v;` keeps both stores, plain
   `& 0xFFFC` / `| v` loses the first one (`func_1511E14C`, structure matched, DIFF25 left in the float registers).
6. **A loop var of type `s16`/`s8` stops IDO's strength reduction/unrolling** (and costs a `sll/sra` per use): `i*0xA0` stays a per-iteration `sll/addu/sll` (`func_15188008`, `func_151096A0`: ref keeps
   `i * K` and the counter both; with `s32 i` IDO derives `i` from the byte-offset induction var and drops it). A constant-trip 4x loop unrolls even with the m2c pointer bump; the `label: ...; if (i < 4) goto label;`
   form keeps it rolled but changes `slti/bnez` into `li 4; bne` (`func_15157580`, DIFF19 left).
7. **Locals that must live in memory**: `volatile s32` stack words give the `sw v0,0x4C(sp); sw v0,0x48(sp)` pair (`func_15177360`); a plain `s32 sp50` assigned from the same value is copy-propagated away
   (the ref keeps `or t0,v0,zero; ... sw t0,0x50(sp)` in the jal delay slot: unsolved, 3 statements shape). `s32 a[3]` rounds to 16 bytes (use `[2]` + a scalar).
8. **Reversed memory-operand rule for `|` chains**: `f18 | 0x80000 | 0x2C00 | f2C | f30` keeps the two constants separate (`lui at,8; or; ori 0x2C00`), `f18 | 0x82C00 | ...` folds them; IDO still
   loads `f30` before `f18` unless the chain is split (`func_15158838`: 240 permutations of the 5 terms and the table pair gave DIFF63 at best; the `lw t2,0x24` table index first order is not reachable by reordering).
9. **A function that falls off the end with a stale `v0`** (`func_151846C0`): `return (T *)var_v0;` made IDO move `v0` into `a0` in the loop (extra `or v0,a0`); deleting the return changes the loop shape.
   Not solved, DIFF53.
10. **Tools**: `redeclfix.py f draft.c out.c` (loops `repair_try`; deletes the draft's own prototype/extern for a name reported as `redeclaration of 'X'`, or inserts the real prototype of a callee defined later in the file),
    `fnptrfix.py in out` (m2c `*(s32 *)((u8 *)&TAB + i * 4)(args)` is a deref of the call result: rewrite to `(*(s32 (**)())(...))(args)`), `SCREEN_KEEPC=1 repair_try.sh` keeps the compiled TU
    (`conker/build/rt_<f>/<f>.tu.c`) so the line of a `cfe: Error ... line N` is readable. On the 141 CERR drafts of s55: `redeclfix` 141 -> 97 CERR, `fnptrfix + redeclfix` 97 -> 84; the rest are `spXX` read-only
    stack vectors (36), `Dereferenced a non-pointer` (20, m2c `*(base + idx)` of an `s32` global) and `Unacceptable operand` (11).
## s57 recipes (slice < 0x130000: spawner stack structs, named-local slot order, params)

See `docs/sessions/s57.md`.
1. **Stack-struct spawners** (49 asm callers of `func_15132FBC`, e.g. `func_150CB2D0`/`CBD10`/`CCF8C`/`CE420`, `func_150D2C9C`): m2c emits scalars `s8 sp98; s16 sp9C; f32 sp28[13]; ...` and passes `sp28`. IDO drops the stores to the never-addressed scalars (SIZE-56). `spstruct.py in out`
   merges all `spXX` at or above the lowest array into ONE `struct { ...; } sp` with pads (fields `uXX` named by stack offset) and passes `&sp`: the SIZE-56 drafts become DIFF42/47, i.e. all stores and the schedule are right and only the frame layout is left
   (mine puts the struct 8 bytes higher with an 8-byte hole below, the ref has the same 8 bytes above the struct; 2 pad words, f64 tail, union with f64, named `sp20` all failed; SOLVED in s58: the chained assignment costs a dead temp, see `## s58 recipes`).
2. **9-byte aligned const struct copy**: `struct S9 { u8 a[9]; } sp38; sp38 = D_800A0D60;` gives exactly `lw/lw/sw/lbu/sw/sb` through `$at` (the three-statement s32/s32/u8 form schedules the byte load earlier).
3. **Named locals in registers take slots, and their DECLARATION ORDER decides where the free hole ends up** (`func_150EA3B4`, DIFF3 -> OK): declare the live-across-calls float (`f32 temp_f20;`) BEFORE the stack vectors `s32 sp80[3]; s32 sp74[3];` to get the ref's unused slot above them
   (the permuter had the vectors right but 4 bytes too low). Inline `x = call();` temps that are only consumed as arguments (they become unnamed spills) and save their slots.
4. **`rand() * field` operand order**: when mine gives `mul.s f16,f10,f0` and the ref `mul.s f16,f0,f10`, write the field first (`field * func_150ADA68()`); `(0, call())` did not help here (`func_150EA3B4`).
5. **`f32` literal passed as `0x3F800000`** to an `f32` parameter converts the integer (`lui at,0x4E7E`); write `1.0f` (`func_150891D4`).
6. **Sub-vector `s32 spXX` + `&spXX` to a `float[3]` out parameter**: declare the real 12-byte arrays (`s32 sp88[4]`/`[3]`) or the frame is short by 4 bytes per vector (`func_150891D4`, `func_150EA3B4`).
7. **Stack-passed args of a function that ignores them**: `func_150C76C0` read its 6th parameter (`lw $v1,0x74($sp)`), m2c had dropped the 5th (`arg4`): add the unused `s32 arg4` so the later params land on the right stack slots (DIFF1 -> OK).
8. **`void f(s16, s16, f32, void *)` prototype for `func_15143794`** (the header has `s32 f(s16,s16,s32,u8*)` in one file only): fixes SIZE+2 in every draft that calls it (`func_150E0978`: after the prototype the remaining DIFF35 was frame slots, fixed by inlining the `spXX = call()` temps, recipe 3 of s55).

## s59 recipes (CERR spXX class, bitfield-like stores, frame via s58 rules)

1. **`spXX undefined` CERR drafts**: `tools/eu_port/spdecl.py in out` declares the missing stack names (array when indexed or address-taken, `guMtx*` matrices 16), `extfix.sh` adds missing `extern D_*`; 30 of 36 compile. See `docs/sessions/s59.md`.
2. **m2c `X = spNN;` with `s32 spNN[3]`** stores the address; the ref stores the value: `X = spNN[0];`.
3. **`andi t,v,0xFFFC; sb; or; sb` (double store to one byte)** is `*(u8*)p &= 0xFFFC; *(u8*)p |= v;` (not a bitfield; `0xFC` gives `andi 0xFC`). Plain memory-operand sums load in the order written; swap `a + b` -> `b + a` when the ref loads the second field first (`func_1511E14C`).
4. **12-byte vector copies** from m2c (`f32 +0; s32 +4; s32 +8`) are struct assignments: `typedef struct {f32 x,y,z;} V3; *(V3 *)dst = *(V3 *)src;` gives the `lw/sw` triples.
5. **s58 frame rule applied** (`func_151664F0`): a named float live across a call lives in a compiler temp only when it is NOT named; inline `((f32) arg0) * 0.0174f` twice and declare the other named locals above it (`s32 i; u8 *temp_v0;`) to put them at 0x34/0x30 and the spill at 0x2C.
6. A file's first `.rodata` word can belong to a neighbour (`ff000000` before the float): `rodata_split.py --own` then yields a mismatching section and apply.py REJECTs with no message; compare `conker/conker.eu.bin` at the range start.
## s58 recipes (stack frame layout, the func_15132FBC spawner family)

See `docs/sessions/s58.md` (solves s57 recipe 1's frame hole).
1. **Frame layout at -O2 -g3, bottom up**: outgoing args (>= 0x10), saved regs, compiler temps (8 bytes each, directly below the locals), named locals from the frame TOP down in declaration order.
   The round-to-8 padding goes at the bottom, between the saves and the temps. A gap BELOW the locals that nothing uses is a dead compiler temp, not a missing local: find the statement that creates it
   (one function per "statement removed" variant in one standalone file, `docs/sessions/s58_drafts/cx.sh`) instead of adding pads.
2. **A chained float assignment `a = b = expr;` costs an 8-byte temp** even when the value stays in a register. Write `b = expr; a = b;` (same `swc1` pair). This was the whole s57 spawner hole.
3. **A named float local assigned from an expression and used twice also costs a temp slot** (`f32 t = r() * 3.0f; x = t; y = t;` grew the frame like the chain); inline or use the struct field as the second source.
4. **Spawner struct for `func_15132FBC`** is 0x80 bytes (8 tail bytes after `u9C`) when nothing else is declared above it; with named locals above it (out-params, angle results) a 0x78/0x7C struct plus those names fill the same space.
   15-parameter signature `(s32, s32, f32, f32, f32, s32, s32, s32, s16 arg8, s32..., u8 argE)` so the stack params land on m2c's offsets; `u8 u88` when the ref stores 0xFF.

## s60 recipes (frame slots: which names take slots)
See `docs/sessions/s60.md`.
1. A named pointer that is spilled across a call costs an 8-byte slot; writing the expression out (`D_800CC2D0[arg0].x` repeatedly) makes the spill an unnamed temp and can remove 8 frame bytes (`func_1502C8F8`).
2. Two `s16` locals share one word; a 4-byte local declared before them sits above and moves them down 4 (`s32 lim; s16 a; s16 b;`).
3. For address-taken / spilled locals try all permutations of the other names in one script: the position of the spilled float (`temp_f16` second) or two names above `sp44` decided DIFF2 -> OK (`func_150B15D0`, `func_1502B6BC`).
4. `s32 i; u8 *p;` declared before the stack structs fill the 8 bytes above them (`func_150DE8AC`); a `p = &sp50; p += 1; p--;` forces `&sp50` to be computed twice.
5. `f32 two = 2.0f` takes a slot; inlining gives `add.s`, not `mul.s`.

## s62 recipes (fixchain triage, add.s order, dead stack vectors)
See `docs/sessions/s62.md`.
1. A DIFF1 `add.s fd, fs, ft` operand swap (`x = x + (a - x) * k` gives `prod + x`): write it as a compound assignment `arg->f += (0.0f - arg->f) * 0.2f;` (or `x = x + (...)` with no named `temp_f0`) -> OK (`func_15052590`). The named-local form `temp_f0 + (...)` and its reverse both stay wrong.
2. A m2c vector `f32 sp60; f32 sp64;` where only `&sp60` is passed: the store to sp64 is dropped as dead (SIZE-5, missing `lui/mtc1/mul.s/add.s/swc1`). One array `f32 sp60[2]` restores it (`func_150FE638`, 31 -> 4 after the permuter).
3. Writing a stack struct of s8/s16 fields as separate scalars drops the stores (SIZE-8); a `struct {s8 u44; s8 pad; s16 u46; ...} sp` grows the frame by 8 (0x58 vs 0x50) while `s8 sp44[8]` + `*(s16 *)&sp44[2]` keeps the frame but lands 4 bytes too high (`func_150FCFB0`, DIFF6; the ref has a 4-byte neighbour above the array).
4. `(0, temp_v1) + (idx * 0x24)` flips `addu` to `base + product` when the base is a plain local and the product comes from `mflo` (`func_150B45C8`). An `s8` loop variable that the ref never sign-extends must be `s32` (SIZE+3 -> DIFF). Zero stores to float fields must be `0.0f` (`swc1 $f0`, not `sw $zero`).
## s61 recipes (leading rodata word, named-float slot cost, spawner callers)

1. **File .rodata starting with an unreferenced word** (`func_151664F0`, `game_eu_193D00`): the ROM range is 16-aligned `[0x24C2F0,0x24C300)` = `ff000000, 0.017453292f, 0, 0`. The `ff000000` is a 2-byte string `"\xff"` (padded to 4 by the float) of the file with no code reference. Own the range with `rodata_split.py game_eu_193D00 24C2F0 24C300` (manual form, the `--own` range was wrong because refs() has no ref at 0x24C2F0) and add `const char rodata_pre_193D00[] = "\xff"; // fakematch` at the top of the C file: `const u32 = 0xFF000000` goes to `.data`, the string goes to `.rodata` first. Object `.rodata` is 16-aligned and padded to 16, so an owned range shorter than the object fails section_diff.
2. **A named f32 used 3 times costs 12 bytes of frame (4 slot + 8 temp)**; used once it costs nothing. Two uses of one random float can share one local (`temp_f0 = rand(); ...; temp_f0 = rand();`: the permuter found this in `func_15154DF4`, DIFF16 -> DIFF2).
3. **No spare local for the spawner result**: reuse a dead parameter (`arg5 = func_15132FBC(...); if (arg5) {...} return arg5;`) instead of `temp_v0`/`var_v1` (each named int local is a 4-byte slot below the struct).
4. **Call-site struct pointer**: `func_15132FBC((u8 *)&sp.u2C[5], ...)` (m2c's `&sp2C[5]`); the object copy `memcpy(r + 0x170, &sp, N)` copies the 8/0x14 bytes in front of that pointer; struct = one block covering the prefix floats and the spawner struct.
5. `register f32` does not remove the slot/temp cost.

## s63 recipes (permuter chains, reloaded float temp, rodata of a two-object file)

1. **Chain permuter rounds**: a spawner caller went DIFF95 -> 31 -> 18 -> 5 -> 1 with four consecutive 560 s / 8-job rounds, each restarted from the previous `nm/<f>/best.c` (`cp best.c next.c; permute.sh f next.c 560 8`). One round finding nothing does not mean the draft is stuck; a round that improves usually improves again.
2. **Reload a stored float into the reused float temp** (`temp_f0 = sp.u9C;` before the V3 copy, then `* temp_f0` for the three vector multiplies) reproduces the ref's early `lwc1 f2,0x9C(sp)` (DIFF109 -> 95).
3. The last permuter diff `addiu 0xFF` vs `-1` means the struct member is `s8`: make it `u8` (a `u8` constant 0xFF does not sign-extend).
4. **Float literals of a two-object C file**: find the literal's real ROM address by searching the ROM for the float (`struct.pack('>f', v)`), do not assume the file's rodata start. `file_split.py <stem> --at <first func of the 2nd object> --resplit` (needs a prior full build for `conker.eu.map`) gives the second object its own file that auto-owns its rodata, even when the plain `--dry` says "no clean split point". A manual `rodata_split.py ... --dry` is not dry in this tree: it writes the yaml.
5. A statement like `x += 180.0f; temp = rand();` leaves the store in the delay slot of the call; the ref sometimes has a `nop` there instead (open: unknown trigger, see `func_151D49B8`).
## s64 recipes (named temps take slots, struct copies, int literal keeps mul.s)
See `docs/sessions/s64.md`.
1. **Delete m2c/permuter names before moving declarations**: named pointer temps (`temp_v0 = arg0->unk31C`), named call results and single-use `s16 temp_a0` call arguments take named slots and push the unnamed spills down by 4-8 bytes. Inline them (IDO CSEs the repeated `arg0->field` loads) (`func_150FE638`, `func_150D2884`). A loop counter that lives in a register still takes a slot: declare it before a stack struct to put the struct 4 lower (`func_150FCFB0`).
2. **`lw $at, 0(x); sw $at, K(y); lw tN, 4(x); sw tN; lw $at, 8(x); sw $at`** is a 12-byte struct assignment, not three `s32` copies (`func_150B45C8`; s59 recipe 4).
3. **`x * 2.0f` is folded to `add.s x, x`**; the ref's `lui 0x4000; mtc1; mul.s` comes from the integer literal `x * 2` (`func_150FEB84`).
4. **m2c pointer strides**: check every `p += 1` on a struct pointer against the ref's `addiu` (`func_150891D4` walked bytes; `func_1500B1F4` family: `"?"` string = `f32 D_80096014[]`, `+= 2`).
5. **Call argument untruncated in the ref** (`or a1, a0` where the header says `u8`): the caller saw an `s32` prototype (US note `void func_15056A00(s32, s32, u8)`); the callee narrows itself (`func_15077F64`).
## s66 recipes (block boundaries, typed constants, spawner result local)
See `docs/sessions/s66.md`.
1. **An inner block with a declaration is a basic-block boundary.** `x += 180.0f; { f32 t; t = rand(); ... }` leaves the `jal` delay slot empty (`nop`) where the flat version moves the preceding store into it (`func_151D49B8`, the s63 recipe 5 puzzle). Likewise an `addiu a0, sp, K` (address of a local) that IDO hoists to the top of a block in mine but the ref computes late: put the tail `{ V3 diff; ...; call(&diff) }` in its own block (`func_151452C4`). A bare label (`lbl:`) has the same effect but is a fakematch; `do {} while (0)`, `if (0) {}`, `for (;;) {...; break;}` and `;` do not create the boundary.
2. **Constants of different C types are not CSE'd**: ref `li t7,1; sb t7, X` after a run of `sb v0` stores of the same 1 means X has a different type (`u8` vs the run's `s8`) (`func_151E3864`: `D_800D3260` is `u8`). Same check for an `0xFF` divisor that is not shared with an `0xFF` argument.
3. **Spawner tail** (`obj = func_15132FBC(...); if (obj) memcpy(obj + 0x170, &sp, n); return obj;`): the spill at the frame top (`sw v0, 0xAC(sp)` in the memcpy slot) is the home of a named `s32 obj` **declared before** the stack struct; the struct ends 4 bytes below it. Field-order stores (`u90 = arg7` before `u91 = 6`) fix the t-register numbering (`func_15154DF4`, `func_151B65C0`).
4. A callee whose 4th argument register is never set in the ref has 3 parameters: fix the prototype before anything else (`func_15142314(Mtx *, s32, f32 *)`, `func_15145EA4`).
5. `rodata_inject.py` now keeps an unreferenced nonzero tail after a file's last rodata item as an owner-less item (was a FAIL; `game_eu_201240`, 12 bytes). `RODATA_TAIL_STRICT=1` restores the old check.

## s65 recipes (rodata ownership with foreign refs, arg copies, spawner field order)
See `docs/sessions/s65.md`.
1. **Owning `.rodata` whose leading items are used only by another file** (`game_eu_12C0B0`: vec3s `D_800A1FB0`/`BC` used by `game_981E0`): give the manual range (`rodata_split.py <stem> <start> <end>`); rodata_inject attaches the unreferenced items to a GLOBAL_ASM neighbour and the other file keeps linking through `symbol_addrs`. Late float items named by C fail ("no GLOBAL_ASM neighbour"): write literals instead, with the exact word (`3.7099998f` = 0x406D70A3, `3.71f` is ...A4).
2. **An unexplained 8-byte frame temp can be extra call arguments**: m2c passed scratch floats (f12/f14) as two leading args of `func_1500AF08`; count the outgoing stack stores (`func_1500B1F4`).
3. **Permuter `new_var = arg2` as a real second pointer**: `out = arg2;` used for a copy loop and the stores after it moved the dest IV increment into the `bne` slot and, declared first, filled the slot above the spilled `best` (`func_15045674`). A loop-body pointer declared in block scope (`{ s16 *p; ... }`) differs from function scope.
4. **Spawner struct initialisers** (`func_151530A8` callers): write the stores in **field order** (`tools/eu_port/spsort.py in out`), make fields stored with `li 255` / `li 0xB4` `u8` (m2c's `s8` gives `li -1`), and copy the vec3 argument as a 12-byte struct (`*(V3i *) &sp.u24 = *(V3i *) arg0;`). `docs/sessions/s65_drafts/spawner_fix.py` does the copy and the 0xFF fields (`func_150F0FA4`, `func_150B5C38`).

## s67 recipes (spawner Header locals, scheduling barrier, lerp per-component temp)
See `docs/sessions/s67.md`.
1. **`func_151602C0(&header, &header2, ...)` in a spawner**: m2c folds `Header` (s8,s8,s16,s8; 6 bytes) and `Header2` (3 x s32) and the `f32 pos[3]` they are built from into the stack struct. Declare them as separate locals above the spawner struct, top-down `f32 pos[3]; Header header; Header2 header2;`. Write `pos` first, then `header.unk0..unk4`, then `header2.unkN = pos[N]` (`func_150F8B20`, like the matched `func_15070224`).
2. **Ref `lwc1 f; swc1 f; sb; jal; sb` vs mine `lwc1; sb; sb; jal; swc1`** (the `sb`s fill the load delay in mine): only the permuter's `if ((arg && arg) && arg) {}` before and after the first header store reproduced it (fakematch). `if (arg) {}`, `arg && arg`, `do {} while (0)` and a label all stay DIFF3.
3. **Named locals above a stack struct**: count the bytes between the struct top and the frame top in the ref. 12 bytes = three named scalars declared BEFORE the struct, nothing declared after it (`func_150FF9F4`).
4. **`andi sN, aK, 0xFF` at entry + `sw aK` home** = `u8` parameter passed on unchanged. A cast `(u8) argK` of an `s32` parameter is hoisted below the first branch instead (`func_150FF9F4`, `func_1500B1F4`).
5. **Lerp of a lerp per component** (`func_1500B1F4` family): the ref evaluates x-lerp, then the outer lerp of x, then y... and keeps one float temp. Reusing ONE named `f32 x` for all three components gave the right size where three names x/y/z gave SIZE+2.
6. **`b end` after the last case of a float ladder** = an `if / else if / else` chain, not `cat = 2; if (...) cat = 1;` (`func_1508DCAC`).

## s68 recipes (same-line statements, named temps below a struct)
See `docs/sessions/s68.md`.
1. **Store-order DIFFs: put the statements on one source line.** IDO keeps the store order of statements on different lines; statements on the same line are scheduled as one unit and can come out with stores swapped (`func_15013DE8`: `sp.u50 = 0x6231; sp.u52 = 0x1A4D;` on one line gives `li t0,0x6231; li t1,0x1A4D; sh t1,0x52; sh t0,0x50`). Screen all subsets of adjacent groups joined in one `tryall`. Check permuter outputs for joined lines (it re-prints statements on one line) before keeping its other changes.
2. **Low stack slots reloaded after a call are named locals, not struct fields**: if the call receives `&sp.uNN`, the struct starts at uNN; floats stored below it and reloaded after a call are named `f32` locals declared after the struct (`func_15013DE8`).
3. **`move sN,v0; andi tK,sN,0xFF; ... move sN,tK`** = `u8 a = f() & 0xFF;` (explicit mask on a u8 local; plain `u8 a = f();` gives `andi sN,v0,0xFF`) (`func_150B5568`).
4. **A named float spilled to its home although callee-saved FPRs are free**: IDO's interference is per basic block; if the floats share the block up to the first `divu` zero check, 7 live floats get 6 registers and the last declared one is spilled.
## s69 recipes (shape D = a declaration in the arm)
See `docs/sessions/s69.md`.
1. **Shape D solved**: `store; jr ra; nop` (or `store; b L; lw ra` with the store not in the slot) means the block that ends with that store **declares a local**. A declaration opens a new basic block in IDO, so the jump that follows lives in its own (empty) block and the delay-slot filler finds nothing. Natural forms that work: a used local in the arm (`if (c) { s32 *p = (s32 *)(arg0 + 0x44); *p = 0; }`, `u8 *q = p + 0x10; *q &= ~1;`), per-arm pointer locals (`if (arg2 == 0x17) { u8 *p = arg0 + 0x28; ... } else if (...) { u8 *p = ...; ... }`, `func_151A98CC`); otherwise an unused `s32 t;` (fakematch). Matched this way: `func_151AEBF0`, `func_151D51E8`, `func_151590AC`, `func_151095E4` (switch case block), `func_151A98CC`, `func_1519ED88` (`{ s32 t; D_800E0D50 = 0; }` after the call). The old s51 label fakematches (`dummy_label: ;` after the arm, `func_15193850`, `func_150FE08C`) are the same boundary.
2. Tool: `tools/eu_port/blkvar.py draft.c outprefix` writes one variant per if/else/loop body with `s32 blk_t;` at its top (+ `_ball`); feed the list to `m2c/tryall`. `tools/eu_port/putc.py func draft.c` replaces the function's `GLOBAL_ASM` with the draft.
3. The arm-local declaration only fixes the slot; register roles still need the usual work. In this family: `u8 *v = arg0 + 0x28` at **function** level keeps `addiu v0,a0,0x28` unfolded (`lw 0(v0)`), a per-arm local folds it into offsets (`lw 0x28(a0)`) (`func_151D51E8`, `func_1519ED88`); one shared variable reused in both halves (`a`, `b`, `c`) and `(b = arg1[1]) == c` in the else-if (`func_151B34B4`).
4. **The `or t0,a2` / `or a3,v1` copy family** (`func_151B7664`, `func_151BD7CC`, `func_151BAA18`, ex-s23 blocked): `p = <ptr>; id = p[0]; t = id;` at function level, arm 0 compares `t == arg1[0]` (block-local declaration in its if-body), arm 0x2D does `t = arg1[0]; if (t == *p) {...; return;} if (arg1[1] == *p) {...}` (**re-read `*p`**, not `id`: that is what keeps `t` and `id` in two registers). Found by the permuter on BD7CC (DIFF3) + one tryall. `arg0 + *(s32 *)(arg0 + 0x50) + 0xF8` with the ref's `addu v0,a0,t7` order: `q = arg0; q += *(s32 *)(arg0 + 0x50); q += 0xF8;` (`func_151095E4`, `func_151BAA18`).
5. Still open: `func_151597A0` (`b L; li v1,K` to the next instruction + `or v0,v1`: switch/return/goto/decl variants SIZE-1 or DIFF9), `func_15168B44` (two `sw` to 0x14 that mine dead-store-eliminates; `volatile` keeps it, DIFF15 after permuter). Blkvar does nothing for the matrix drafts `func_15177360` / `func_15188008` (SIZE-1).
## s70 recipes (line-join sweep negative, blkvar sweep positive)
See `docs/sessions/s70.md`.
1. **Line joins (s68 recipe 1) are rare, not a standard first step.** Swept over 143 near-miss functions (5,300 `linejoin.py` variants, incl. all 32 DIFF<=12 logged near misses): 0 cured, results changed in 19 functions, small improvements in 6. Keep it for store-of-constant order DIFFs only.
2. **Blkvar sweep first** (`blkvar.py`, s69): over the same drafts the result changed in 115 of 191 functions and improved 43; 1 OK directly (`func_150E3B5C`: declare the loop's local inside the `for` body). An improved blkvar variant marks the block whose structure is wrong; then write the natural construct: an `else if` chain instead of a default-then-override `if` (`func_15074C80`), index loops `a[i]` instead of pointer walks (`func_150EBA04`), or give the variant to the permuter (`func_150F8DFC`, `func_150E0B78`, `func_150597FC` matched from blkvar starts in 1-2 rounds of 300-400 s).
3. **Pointer-walk vs index loop**: `slti at,sN,K; bnez` loop test (not `li at,K; bne`) + a separate pointer register = `for (i = 0; i < K; i++) ... a[i]` (IDO strength-reduces itself and keeps the `<` test). A loop to a symbol end (`sN != &D_end`) with the start in another register = also an index loop over the array (`func_150EBA04`).
4. Frame 8 bytes too small with everything else right: an unused `s32 pad[2];` declared first fixed `func_150EBA04` (`f64` and `u8[8]` too; after the other locals: no). Fakematch.
5. Pipeline for a whole slice (about 10 min / 3,000 variants): `ljcollect.py l.txt` -> `ljsweep.py l.txt base > base.res` -> `ljpipe.py base.res w > w.txt` -> `ljsweep.py w.txt w > w.res` -> `ljbest.py w.res w/sel.txt`.
## s71 recipes (0x2D/0 handler family: compare order, arg2 copy)
See `docs/sessions/s71.md`.
1. **Second 0x2D compare `bnel arg1[1], key` comes out reversed**: drop the named `t`/`k` and write plain memory compares (`if (*(s32 *)arg1 == *(s32 *)v) {...} else if (*(s32 *)(arg1 + 4) == *(s32 *)v) { ... = *(s32 *)arg1; ...}`), IDO CSEs the loads (`func_15161F4C`, `func_15133AF8`, `func_151B604C`). Alternative: a function-level `s32 *key = (s32 *)(arg0 + K);` read as `*key` in every compare (`func_15159514`, permuter). `(0, k)` and operand swaps of a named `k` do nothing.
2. Then add `s32 blk_t;` (s69 shape D) in the arm whose tail is `store; b L; lw ra` or `b L; <copy of the target insn>`: arm 0 with the `jal` in `func_15161F4C`, the last swap arm elsewhere.
3. **`or v0,a2,zero` copy of the u8 arg2 spilled across a call** = `s32 sel = arg2;` tested in the later arms (`func_15133AF8`); a function-level `t` reused in arm 0 takes `v0` after it.
4. Shape C with two args reloaded (`func_151640C0`): `q = &arg0; r = &arg1;` + named loads; the permuter's `v = *q; v = v + 0x18;` (split add, fakematch) set the v0/v1 roles.
5. OPEN: `func_15187EC0` (ref reloads `arg0` from its home but still hoists the stack-arg loads above the stores, which `&arg0` prevents), `func_15104FF8` (frame 0x48 between my 0x40/0x50).
## s73 recipes (fresh m2c drafts: names, LAX switches)
See `docs/sessions/s73.md`.
1. **Fresh m2c drafts: delete every named temp first** (`temp_v0 = x->id; switch (temp_v0)`, `sp18 = var_a3`, `var_v0 = p->state`): switch on the expression, write `D_800CC2D0[arg0].field` out. Fixed the result register (`func_150DE450`) and an 0x10 frame excess (`func_150348D4`) with no other change.
2. **m2c `/* irregular */` switch drafts are usually small clean switches**: `LAX=1 gensome.sh` keeps them; fix `s8` 0xFF fields to `u8`, `u8 argN` for an `andi aN,0xFF` prologue, compound `|=`/`&=` for m2c `temp_tN = x | K; x = temp; x = temp & ~M`.
3. A dead pointer update kept in the ref (`addiu v1,v1,-8` after the load) = `p -= 2; return p[1] ...;` (the update is the base of the load) (`func_1507ED48`).
4. Shape C + a block-local pointer: `u8 **q = &arg0;` at function level and the derived `s32 *v = *q + K` declared in the if-body fixed a frame 0x28 -> 0x20 (`func_150D2C00`).
5. Blkvar on fresh (unrepaired) drafts: 0 OK in 41 functions. Use it after the naming/typing fixes, not before.
## s72 recipes (compare grids, merged else, per-arm rematerialisation)
See `docs/sessions/s72.md`.
1. **0x2D compare order: grid, then permuter.** One `tryall` over first/second operand order x key form (named `k`, plain memory, `s32 *key`) x default-arm form (`k`, `(k ^ 0)`), then the permuter on the best-register variant (`func_15135480`: grid DIFF3 -> permuter OK; clean result: key-first plain compares, `t = arg1->unk0;` in the second arm). Reuse the grid's arm bodies for siblings in the same file (`func_151347CC` matched with `*key`).
2. **`b L` to the next instruction at the end of both inner arms** = the enclosing `if` has an `else` that IDO merged into the compare chain: `if (a || b || c) { if (x) r = 2; else r = 1; } else { r = 0; } return r;` (`func_151597A0`).
3. **`addiu vN,s0,K` re-materialised in every arm** (often in the arm-test delay slot) = a function-level `u8 *v = arg0 + K;` plus a declaration at the top of the arms (`s32 blk_t;`); each unused declaration adds 4 frame bytes, so match the frame size by how many arms get one (`func_151CD97C`). An arm-local `u8 *v` instead folds K into the offsets.
4. **Arm-local declarations change scheduling too**: `s32 a;`/`s32 b;` declared inside the arms (not at function level) moved `lui/addiu a0,%hi/%lo(D_800CC2D0)` above the `lw` (`func_15156598`).
5. Linked-list push where the ref tests the head in a t-register: re-read the field you just stored (`n->prev = q->head; if (n->prev != NULL) n->prev->next = n;`), not a named head temp (`func_1518B140`).
## s74 recipes (draft gap, jump tables via .rodata, block boundary before a compare)
See `docs/sessions/s74.md`.
1. **Jump-table function blocked by .rodata ownership**: own the range (`rodata_split.py --own <stem>` or the manual `<stem> <start> <end>`), resplit, then write the switch with the case bodies in the order of the table targets (`func_1513DF9C`). A table without a `-min` subtraction (`sltiu at,v0,N` on the raw value) needs a low case (`case 0: break;`, fakematch) (`func_151604A0`).
2. **"Two objects" warnings from constant-index loads**: `lwc1 x, D+0x18` of a C-named `f32` table (`D_800A6964[6]`) looks like a late literal. Mark it `// rodata_inject: inside <rom addr>` in the C file; own the whole range (owning only the late part fails: the object's .rodata is 16-aligned). Named late floats used only by C functions must become exact literals once no GLOBAL_ASM late neighbour is left (9 significant digits, e.g. `0.70000005f`).
3. **Store-before-load at the end of a block**: ref `swc1 f0,0x84(s0); lwc1 f6,0x8(s0)` where mine hoists the compare's load above the store: wrap the last assignment in a block with a declaration (`{ s32 blk_t; x = f(x); }`, s66 boundary) (`func_1511CAD0`).
4. **m2c `(u32) f & 0xFF` into a u8 local** gives `or; andi`; the ref's `andi; or` is the plain `u8 v = f;` (`func_1515F8A8`, `func_1515FB34`).
5. **Frame too big by 8-16 with m2c spill names** (`sp28 = p; sp2C = idx;`): delete them and the named pointer temps; the spills become compiler temps (`func_151733EC`). A pointer the ref spills to a temp slot but uses as a base register must stay unnamed but not inlined (inlining folds the offset; `func_151B92AC` open).
## s75 recipes (struct copies, statement position of an early load)
See `docs/sessions/s75.md`.
1. **m2c `M2C_MEMCPY_ALIGNED` + unrolled `lw/sw` x3 copy loops = plain struct assignments** of a 0x24-byte struct (`a = *arg3; b = *arg3; ... *arg3 = a;`), results in `u8` named locals at the byte slot (`func_150469E8`, typedef `HitInfo`). `LAX=1` gen2 drafts these now.
2. **A global pointer load the ref schedules at the very top** (`lui v0; lw v0` right after the prologue) is the first statement of the source: `p = D_800D154C; sp.u20 = p; sp.u24 = p->unique_id;` (`func_1506F54C`). Placed later, IDO sinks the load to its use.
3. A call whose 4th argument register holds only a `%hi` (`lui a3` reused for `addiu a2,a3,%lo`) is a 3-arg call of an unprototyped callee (`s32 f();`), the other calls pass 4 (`func_15096E78`).
4. Temps spilled across calls in different `case` arms get the ref's separate slots when declared inside the case blocks (`case 1: { struct108 *a; ... }`) (`func_15096E78`).
## s76 recipes (screening context, exhaustive small orders, file families)
See `docs/sessions/s76.md`.
1. **Re-screen a near miss with the callee prototypes it needs**: a draft whose callees are still `GLOBAL_ASM` with no prototype passes `f32` as `double` (SIZE+9 instead of DIFF5, `func_150464C0`); put the prototypes at the top of the draft. Same for a sibling defined later in the file (`func_15046C6C` needs `func_15046750`'s prototype).
2. **Statement-order DIFFs: screen all permutations** (4 statements = 24 variants, one `tryall`): `func_150D7930` (DIFF10 t-register numbering, the `|=` first) and the 12 declaration orders of 3 named locals + pad (`func_150DE52C`, f0 vs f6 reload). Cheaper than reasoning about the register order.
3. **`if (r)` vs `if (r != 0)`** on a `u8` call result moved its spill `sb` from after the first call into the second `jal` delay slot (permuter find, `func_150464C0`).
4. **Base register before index**: `addu v1, base, idx*K` with the base loaded first = `((f32 (*)[5])base)[idx]` array indexing, not `base + idx * 0x14` (`func_150DE52C`).
5. **`lwl/lwr` + `lhu/sh` copy of an aligned 18-byte block** = assignment of a struct with alignment 2 (`struct { s16 v[9]; }`), plain C (`func_150475B0`).
6. **Nested ternary as a call argument**: `bne ..; b L; li a0,2; beql v0,zero,L2; li v0,1; b L2; move v0,zero; li v0,1 (dead)` = `x == K ? 2 : (x != 0 ? 0 : 1)` (the `beql` tests the false arm of `!= 0`) (`func_150A0890`).
7. **A beq chain for a small switch is a plain `switch`**; if its compare constants are CSE'd with stored values, the stored-to variable has another type (`u8`) (`func_1500E738`).
8. **Read the neighbours of a match**: callers and siblings in the same file share the structs and shapes (5 of 11 matches this session were `HitInfo` functions next to `func_150464C0`; two were clones of an already matched function).
9. OPEN: a `jal sqrtf` in game code cannot be written while `gu.h`'s `#pragma intrinsic(sqrtf)` is in scope (`(&sqrtf)(x)` gives `jalr`); an alias symbol works for the call (`func_15047680`).
## s78 recipes (sqrtf call, reciprocal temp, early return value)
See `docs/sessions/s78.md`.
1. **`jal sqrtf` in a file that includes gu.h**: put `#pragma function sqrtf` above the function (undoes `#pragma intrinsic(sqrtf)`; `game/done/game_75950.c` already did this). It stays in effect for the rest of the file: a later function that needs `sqrt.s` takes `#pragma intrinsic(sqrtf)` again. Solves the s76 OPEN 9 without an alias symbol (`func_15047680`).
2. **guLookAt-style normalisation with a zero guard** (`len = sqrtf(..); if (len == 0.0f) len = K; len = 1.0f / len; x *= len;`): a separate `inv` for the reciprocal. Reusing `len` merges the webs and re-allocates the scaled vector to new FPRs (frame +32) (`func_15047680`; same effect on the reflect clone `func_150479F0`).
3. **`li v0,1` scheduled before a switch with `b end` arms and an empty `jr ra; nop`** = `s32 ret = 1; ... return ret;` together with a named pointer local for the switch operand (`u8 *p = ...; switch (p[0x68] - 15)`); either one alone stays DIFF27 (`func_150B6BBC`). A subtraction before the compares (`addiu v1,v1,-15; beql v1,zero`) is `switch (x - 15) { case 0: ... }`, not `case 15`.
4. **A float constant loaded in the first two instructions** (`lui at; lwc1 f0` before the index arithmetic): `f32 k = D_x;` first and the rest of the body in a block with a declaration (s66 boundary) (`func_15034790`).
5. Store-order sweeps over all 24 orders x tail forms in one `tryall` solved a switch-handler twin directly (`func_150D79EC`); do this before any reasoning for small handler families.
## s77 recipes (clean rewrites of permuter bests, eeprom probe, LAX switch drafts)
See `docs/sessions/s77.md`.
1. **Rewrite permuter bests from the ref asm before running more rounds**: 5 of 7 s74 near misses (DIFF2-19 after 2-3 remote rounds) closed as clean source. Loops over global arrays are index loops (`D[i].x`, `for (i = 0; i < 2; i++)` over two parallel tables -> IDO's pointer IVs + `&D_end` compare); an inner array whose start is copied (`lw v0, 0(s7) ... move s0,v0`) is a named `base = D[i]` indexed `base[j * 3 + k]` (`func_1510B930`, `func_151154C4`).
2. **osEepromProbe shape** (`beqz v0, L; lhu t6, type(sp)` then `b end; move v1,zero`): compute `type = st.type & 0xC000;` right after the call, then `if (ret != 0) { ret = 0; } else { switch (type) {...} }` (`func_151DDA10`).
3. **m2c `/* irregular */` switches with `goto block_N`** are plain switches with the shared tail repeated in each case (`ret = 1; break;`); case body order follows the ref layout, `default:` last unless the ref puts its body first (`func_151598E0`, `func_151307F0`).
4. **`move v1,v0; move v0,v1` before the epilogue where the ref has the value in `v0` already**: the s32 function has no `return` (falls off the end with the variable in v0, IDO_SHAPES 3.9) (`func_15195024`, fakematch comment).
5. **Prologue `sw a1; andi t6,a1,0xFF; or a1,t6,zero`** (narrow in place, then `a1` passed on unchanged to several calls) = the callees' prototypes take `u8` (`func_15172164`; with `s32` prototypes IDO narrows into `a3` and copies per call).
6. A spill slot 4 bytes low (0x20 vs 0x24) with two named locals: declare the spilled one first (`u8 *obj; s32 type;`, `func_151307F0`).
## s79 recipes (argument-block families, frame of small spawn helpers)
See `docs/sessions/s79.md`.
1. **Sweep by callee, not only by file**: `grep -l "jal func_X"` over the slice asm for callees whose argument block is already a typed struct (`structEU_151D8E18` for `func_151D8E18`, `struct_eu_EF410` for `func_15134908`, `struct_eu_15154488` for `func_15154488`, `s32 buf[9]` for `func_1504715C(buf, obj)`); write each caller from the ref asm with that struct (7 of 9 s79 matches, most on the first try).
2. **Frame 4 low with one stack struct and nothing else named**: the ref reloads `arg0` from its home; a named copy `u8 *p = arg0;` used for the field addresses fixed it (`func_151B8C18`).
3. **Frame 8 high around a `u8` table lookup** (`kind = D_800A43C6[i * 16]; if (kind == 2) return; ... unk3C = (kind == 1)`): declare `s32 kind`, not `u8` (`func_151382E0`).
4. Lowest store before a `jal func_1504715C` landing in the delay slot where the ref puts the argument copy there: a bare label between the stores and the call (fakematch, s66 recipe 1) matched `func_15194D80`; in `func_15194B3C` the same label also removes an `arg0` copy (SIZE-1), still open.
5. `divu` by a computed divisor needs `% (u32) (x + 1)`; `%` on a plain s32 sum gives `div` + the `-1`/`0x8000` traps (`func_151D5404`).
## s85 recipes (real arity of a shared definition, matrix-column order)
See `docs/sessions/s85.md`.
1. **`sw a3, home` at entry with a 4-param header but a3 never read**: the definition has 3 params. When a caller in a file you may not touch passes 4, make the header prototype unprototyped (`s32 f(); // 3 params ...`) and keep an ANSI 3-param definition; int/pointer args make the caller byte-identical (`func_150A2FCC`). A 4-param definition with an unused `arg3` is SIZE+1 (the store).
2. **Two scan loops with one shared `return -1`** (the first loop's `blez` jumps to the final `li v0,-1`): `if (c) { for ... } else { for ... } return -1;` (`func_150A2FCC`).
3. **Matrix with the translation copied in and the constant column cleared**: write `m[3][0..2] = ...` before `m[0..2][3] = 0; m[3][3] = 1;`; IDO schedules the last load into the call's delay slot (`func_150335C8`).
4. A global byte index that lands in v0 right before a `jal`: name it (`u8 i = D_800BE9C0;`) (`func_150C8C30`).

## s83 recipes (switch operand copy, scan loops, declaration order)
See `docs/sessions/s83.md`.
1. **`move v0,a3` before a compare-chain switch on a param that is also the 4th call argument**: the callee takes only 3 args (a3 merely still holds the value); with the 3-arg prototype the copy disappears. `beq x,7,L; b L` with the shared value set in an earlier delay slot = `case 7: default: v = K;` (`func_150BEEB0`).
2. **Scan loop with `lw base; addu v0,v1,s0` for the tests and `addu a1,s0,v1` for the call**: two forms of the address (struct-typed index for the field tests, `base + i * size` for the argument/return), counter declared before the big stack struct (`func_150A3674`).
3. Stack struct 4 bytes high next to a named pointer/temp: declare the pointer **before** the struct (`func_150A3264`, `func_1506AC24`); a named pointer used across a call and rematerialised as `addiu v0,s0,K` is declared first (`func_150F2B20`).
4. `__ull_rshift` on a u64 table: cast both indices to `u32`; screen DIFF1 on the second word's symbol (`D_800D3514`) is only a relocation name (`func_150A29C8`).

## s81 recipes (varargs loops, unnamed slot pointers, Mtx arrays)
See `docs/sessions/s81.md`.
1. **Counted loop over a memory-resident count** (`&arg` taken by `va_start`) with the decrement stored before the other store in the `bnez` delay slot: `for (; arg1 != 0; arg1--) { ... }`; `if (arg1) do {...} while (--arg1);`, `while (arg1) {...; arg1--;}` and the statement order inside the body all give the reversed store order (`func_1502B020`, `func_1502B7F0`). `sltiu at,a3,2; beqz` = `for (; arg3 > 1; arg3--)` with `u32 arg3` (`func_1502B110`).
2. **Out-param local at the lowest slot** (`addiu a2,sp,0x34` with other named locals above): declare it last (`func_1502B8E0`); with two stack locals sweep only which names go between them (20 variants for 5 names, `func_1502B5C8`).
3. **Frame 8 high with a pointer kept in a register and spilled across calls**: drop the name (`*(s32 **)&D_800D1588[arg0]` repeated; IDO CSEs the address into v1 and spills it to a compiler slot) (`func_1503D950`). Same rule as s64 recipe 1.
4. `addu a1, arg0, idx<<6; addiu a1, a1, 0x78` = `&((Mtx *)(arg0 + 0x78))[D_800BE9C0]`; `arg0 + (D << 6) + 0x78` swaps the t-register roles (`func_150F2A98`).
5. A `jal` in a block followed by stores of the last `pos` element landing in the delay slot: declare the call's buffer inside the block (`case 1: { f32 buf[9]; ... }`), the natural form of the s79 label trick (`func_15076768`).
6. A ternary over two different address sums (`bne; lw base; b; addiu base, 0xA00 / lw base; addiu 0xBC0`) is `c ? *p + 0xA00 : *p + 0xBC0`, not `*p + (c ? 0xA00 : 0xBC0)` (`func_150CB5E0`).

## s80 recipes (callee families via calleefam.py, scheduling barriers)
See `docs/sessions/s80.md`.
1. **`tools/eu_port/calleefam.py --typed --max 100`** lists argument-block families with a hint from a matched caller; a family of near-identical clones (here 10 callers of `func_151AC3F0`) is fastest as a small generator script once the first one matches.
2. **First load scheduled after a global float compare operand** (`lwc1 x; lui; lwc1 D` in the ref, `lui; lwc1 D; lwc1 x` in mine) after `obj = *(u8 **)(arg0 + 0x18)`: the permuter's `if ((obj && obj) && obj) {}` right after the declaration fixes it (fakematch); a real `if (obj->unk31C ...) return;` there does the same naturally.
3. **Slot 4 bytes too high under a struct local**: declare a 4-byte local (`f32 a;` that the function uses anyway) above the struct (`func_15123070`); `u8 *obj` declared before `struct17 pos` (`func_151A9F80`). A named `s32 ret` for a call result takes the slot between the compiler temp and the struct.
4. **`lui v0; addiu v0; sw x,0(v0)` store to a global** = through a named pointer: `u8 **p = &D; *p = x;` and pass `*p` later (`func_151674DC`).
## s82 recipes (matrix callers: frame by names, base + index order)
See `docs/sessions/s82.md`.
1. **Matrix callers** (`f32 mf[4][4]` + `func_150A8050` / `func_150A7E40` / `guMtxF2L`): write `mf[3][k] = ...` and `mf[i][j] *= s` per element (IDO reloads the scale each time); `mf[3][0..2] = vec` before `func_150A7E40` is the "struct copy" m2c shows at `mf + 0x30`. f32 args in GPR slots behind an `s32` prototype: `*(f32 *)&arg2`.
2. **Frame/slot fixes by names**: mf 4/8/12 bytes too high -> declare the other locals (pointer, `f32 z, y, x` outputs, used deltas) **before** `mf`; frame 8 too small with mf at the top -> a used `u8 *p = arg1;` declared **after** mf (`func_151B98C0`); struct copy local 4 high -> two 4-byte names before it (`f32 s; u8 *p;`, `func_15158E90`). Chained loads `**(u8 ***)(*(u8 **)(a + 0x98) + 4)` with v1/t0 in the ref = named `p`, `q` declared before `obj` (`func_151B7C7C`).
3. **`addu rd, base, idx` (base first) for `base + (i << 6)`**: `m = base; m += i << 6;` (`func_151AFA80`, `func_1513418C`); `base + i * 64`, `&base[i << 6]`, casts and `(u32)` all give `idx, base`.
4. Two stores at the end in the ref order `swc1 0x50; swc1 0x4C` but float regs off by one: write the computed store first (`e->4C = 1/(x+x); e->50 = 0;`), IDO schedules the constant store ahead (`func_1513418C`).
5. Repeated `(arg0 + K)[D_idx]` matrix-in-object updates: `((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][i][j] *= c;` reloads the index per statement like the ref (`func_151BF0D0`); the m2c literal `0.92300004f` must be kept as printed (`0.923f` is DIFF1).


## s99 recipes (homed trailing params, file boundary in rodata, spawner templates)
See `docs/sessions/s99.md`.
1. **`sw a2` / `sw a3` homes at entry with no use of the args**: give the definition unused trailing `f32 arg2, u8 arg3` params (s97 recipe 2 again, now for unused ones) (`func_150EAA80`, `func_150EA560`, both `(u8 *, s16, f32, u8)`).
2. **Untried files full of template spawners**: `func_1513092C` + tail-struct members copy the s96 `func_150C65D8` draft (`s96_drafts/`) almost verbatim; a point-pair velocity is `sp.u64 = *(V3 *)arg0;` + `scale * (b - a)` (`func_150EAB4C`, `func_150EA69C`). `func_151602C0` loop spawners: frame by s96 recipe 1 (count the 4-byte gaps between the struct bases in the ref and put that many named scalars there), then statement-order sweeps (`func_150EB090`).
3. **Text OK, `.rodata` short / a zero word between two functions' late literals**: the file is two EU objects; split it at the function after the zero word: `file_split.py <stem> --at FUNC --rodata <rom of the next item>` (`func_150EB090`, `game_eu_1188A0`). Float literals that print as `0.060000002f` in m2c must be written that way.
4. An early `lbu` of a field that is only used at the end comes from `v = p->x;` written as its own statement before `v -= ...` (`func_150EAEC4`).
5. The `&arg0` reload recipe (s97) does not fix the late `mtc1 zero` of `func_150C6494`, nor the 35-insn all-args-homed handlers `func_150F7890`/`func_151007B0`/`func_150F1B78` (those get to DIFF6 with `volatile` arg1/arg2, `s99_drafts/func_150F7890_DIFF6.c`).
OPEN: `func_150EB3A4` SIZE-1 (`addiu v0,s0,24` kept per arm + return-value register), `func_150C6494` DIFF26, `func_150F7890` DIFF6.

## s96 recipes (big spawners: scalar slots, loop-count position, tail structs)
See `docs/sessions/s96.md`.
1. **Named scalars take 4-byte frame slots next to the spawner structs** (even register-allocated ones): when every struct offset is off by 4n with the frame right, move n scalar declarations from below the structs to above them (or vice versa for the frame top); screen all placements in one `tryall` (`func_150E16CC`, `func_150E9E10`).
2. **Constant stores after a `jal`** in the ref: the call's statement comes before them in the source (`i = (rand() & 7) + 5;` above the second struct's constant run, then `for (; i > 0; i--)`) (`func_150E9E10`).
3. **An argument kept in an s-register across a loop where the ref reloads it from its home** (and the ref hoists a struct address into `fp` instead): give the callee prototype the narrow type (`u8`), which frees the register (`func_15132FBC(void *, s32, s32, s32, u8, s32)`).
4. **Spawner + tail struct** (`memcpy(obj + 0xA8, &b, 0x28)`, `func_1513092C`): declare the tail as its own local after the spawner struct, `obj` between them; chain the shared float as `b.scale = sp.u5C = sp.u60 = X` and screen the 6 orders (`func_150C65D8`).
5. **Triple chains**: in `a = b = c = X` the middle target is stored first, the left one second, the right one last (after the next call): `sp.u52 = sp.u56 = sp.u3E = t;` (`func_150E9E10`).
OPEN: `func_150E16CC` DIFF26 (`mtc1 zero,f22` placed late; drafts `docs/sessions/s96_drafts/`), `func_1509BE40`/`BFB0` SIZE+1 (varargs, one `lui at` not shared, frame 8 low).

## s94 recipes (spawner frames by declaration order, block-scoped flags)
See `docs/sessions/s94.md`.
1. **Spill slot of a flag 4 bytes off** (`func_150B8C7C`, s92 DIFF2): permute the order of the scalar names below the stack struct (`s32 obj; s32 b; s32 a;`); `itertools.permutations` over the declaration lines, screened in one loop, found it at once.
2. **A missing `nop` before a loop after `mtc1 zero,f0`** (`func_150E92DC`, SIZE-1): declare the flag variable used only in the loop inside the enclosing `if` block (`if (x > 1.0f) { s32 a; ... do { ... } while (...); }`).
3. **`EC | (v0 | s0)` with EC in the lower t-register**: `sp.u8C |= (u32)(b | a);` (fakematch). Plain `|=`, both orders, parenthesised and a named temp (costs 8 frame bytes) all give `(EC | v0) | s0` or the swapped registers.
4. Angle-vector spawners (`func_151423D8(arg8 - 0x40)`, `func_151423D8(arg8)`, then a random angle `s16 t`): copy `func_150BB978`; `arg8` is `s32` (`lw` + `addiu -0x40` + `andi 0xFF`), the spawner struct is 0x70 bytes (`pad98[0xC]`) when the frame top is right above it.

## s92 recipes (asm-only clusters, func_151308E4 spawners)
See `docs/sessions/s92.md`.
1. **`clones.py --asm-clusters` lists byte-identical asm-only families**; solve the smallest member, then `sed` the name (and field offsets / globals) into the others. s92: `func_150CA57C` x4 (physics step), `func_150C630C`/`C6C3C`, `func_1505EEF4`/`EFD0`/`F0AC` (struct127 scans) all matched at the first or second try.
2. **Peeled + 4x unrolled scan of `D_800CC2D0[25]`** (first element tested with constant addresses, then `v1 = &D[1]` and a counter stepping 4 to 25): `struct127 *p = D_800CC2D0; for (i = 0; i < 25; i++) { if (p->x != 0 && p->f == arg0) return p; p++; }`. `p++` at the end of the body; `for (...; i++, p++)` and index forms are DIFF7 / SIZE-2 (`func_1505EEF4`).
3. **`func_151308E4` spawners** (same 15-param signature as the s58 `func_150CB2D0` family; struct passed as `&sp`, 0x70 bytes, or 0x74 when a `memcpy(obj + 0xA8, &scale, 4)` tail follows): fields stored in m2c's order, 0xFF/0xB0/0xA0 fields `u8`; the duplicated float is `sp.u5C = sp.u60 = X;` or `sp.u60 = sp.u5C = X;` (screen both: they give opposite store orders); `obj` declared **after** `scale` below the struct (`func_150CAF04`). A statement that m2c shows after a run of constant stores but whose call happens before them goes **before** the run (`sp.u88 = (rand * 550 - 1416) * 0.001f` in `func_150C9EB4`).
4. **Flag word `b | 0xE01 | a | 0xC000` with the or-result in a later t-register**: the constant is two flags, `... | 0x8000 | 0x4000` (`func_150B8AA0`). Random flags `a` / `b` are `if (rand() & 1) a = 0x40; else a = 0;` (not `a = 0; if (...) a = 0x40;`, which stores 0 to a home).
5. A float argument computed into `f12` (`add.s f12; mfc1 a2, f12`) is a named `f32 f = ...;` passed by name; inline it goes to an `f8`-class temp (`func_150C9EB4`). `(X * K) * rand()` vs `rand() * (X * K)` flips the `mul.s` operands.
6. `0.0f + vz * s` / `vz * c - 0.0f` survive only with a named zero (`f32 vx = 0.0f;`): the literal is folded away; write the store target as a named `s16 *p = D_x;` set right before the stores (`func_150E4740`).
OPEN: `func_150B8C7C` DIFF2 (spilled flag `a` at 0x24, mine 0x28: unused names and `pad` arrays do not move it; `docs/sessions/s92_drafts/func_150B8C7C_DIFF2.c`), `func_150EB610` DIFF6 (shape C: the ref loads `arg0` twice from its home and computes the call args before the `beqz`; 32 variants + remote permuter 600 s).

## s90 recipes (float literal forms, Rare math helpers)
See `docs/sessions/s90.md`.
1. **`0` and `0.0f` are different constants to IDO 5.3 in float code**: they get separate registers / rematerialisations (`return 0` reuses the compare zero, `return 0.0f` re-emits `mtc1 zero,f0`; a mix of `0.0f` compares and int `0` loop tests moved the parameter into a callee-saved f20). When float zeros sit in the wrong registers or a param is unexpectedly in `f20` (`sdc1 f20` in the ref), sweep the literal form per site (`0` / `0.0f`, `1` / `1.0f`) with one `tryall` (`func_1504A6F0`: 1 of 128 matched; `func_1504A620`: `return 0.0f`).
2. **`x *= 2` is `add.s x,x,x` only when written `x += x`**; `x / 2` in PD source was `x * 0.5f` in Conker (`func_1504A5A0`, `func_1504A620`).
3. **Screening a reference decomp with generated headers**: `tools/eu_port/refcc.sh` defines every undefined identifier with a unique value through a force-included header, iterating until everything compiles (PD 625/625).
4. PD `src/lib/mp3/lib_*.c` (expf / logf / powf) are Conker `func_1504A5A0` / `func_1504A620` / `func_1504A6F0`; PD's mp3 decoder itself is not in Conker (no hit >= 0.6).

## s89 recipes (porting Perfect Dark / known Rare source)

See `docs/sessions/s89.md`.
1. **Perfect Dark shares code with Conker**: `src/lib/mtx.c` and `src/game/quaternion.c` matched almost verbatim. Find more with `tools/eu_port/srcmatch.py <objdir>` over IDO-compiled reference objects; >= 0.85 is real.
2. Conker edits of shared code: dropped stores (`quaternion_to_mtx` has no `m[3][0..2] = 0`), inlined wrappers (`look - pos` into new locals, not the params), regrouped sums (`a - b - c + 1` not `a - (b + c) + 1`).
3. The `store; b L; lw ra` arm tail (s69 shape D) showed up in two PD functions: declare that arm's locals inside the arm (`quaternion_slerp`), or a `dummy: ;` label after the arm when moving declarations grows the frame (`quaternion0f097044`: block f32s took 8 more frame bytes).
4. A local `s32 indices[3] = {1, 2, 0}` whose initializer sits in another file's `.data`: copy it as a 12-byte struct from the extern symbol (`typedef struct { s32 v[3]; } Idx3; Idx3 indices = D_80086390;`, fakematch) instead of owning `.data`.
5. `sqrtf` as `jal`: `#pragma function sqrtf` before the function (place it last in the file or check the later functions).

## s87 recipes (early return, rodata of the last asm user, arity scan)
See `docs/sessions/s87.md`.
1. **`lw tN, home(sp)` reload of an arg at the start of the guarded body** (ref) where mine reuses the register from the test: write `if (!x) return;` + body instead of `if (x) { body }` (`func_150E0C58`, `func_150FB8A4`, `func_150F9D6C`).
2. **apply.py REJECT on a function whose `# rodata_inject` block holds tables it references** and no asm function of the file follows: put `const u32 rodata_<stem>_<func>[] = { exact words };` before the definition; the `D_` names stay absolute symbols. Drop a trailing `0` word that is only alignment (`func_150FE49C`, `func_150FDF38`).
3. **Two uses of `base + i * 12` across calls**: the same form twice is CSE'd and spilled (frame +8, SIZE-n); the ref recomputes, so write the second use in a different form (`D[i]` then `(f32 *)((u8 *)D + i * 12)`) (`func_150E0C58`).
4. **Loop over a stack array with `p == &a[1]` tests and the addresses in s-registers**: separate locals declared in reverse (`struct17 p3, p2, p1, p0;`, `for (p = &p0; p != &p3 + 1; p++)`), not an array; a constant used as `x = d; ... x = -d;` with `neg.s` is a variable (`func_1506E2CC`, partial).
5. `tools/eu_port/arityscan.py --slice lo` lists prototypes with trailing params the asm never reads; confirm with `--callers` (callers must not write the register) and beware pass-through args (unread but forwarded to a callee) (`func_1508849C`, `func_15088E84`).
## s84 recipes (C-owned rodata tables, split symbols, block-scoped locals)
See `docs/sessions/s84.md`.
1. **Last GLOBAL_ASM of a `.rodata`-owning file**: a table the C names (`extern D_x`) has no GLOBAL_ASM left to carry it; define it in C as `const` data with the real values (`const T D_x[N] = {...}`, it goes to `.rodata` before the compiler's late literals) and drop its `undefined_syms.eu.txt` line (`func_151AFA80`).
2. **`lui at` per load vs a shared `lui/addiu` base**: m2c `D_x + 4` loads from one symbol share a base register; the ref's separate `lui at, %hi(D_x + 4)` means two C symbols (`extern f32 D_x, D_x4;`, add `D_x4` to `undefined_syms.eu.txt`) (`func_15177638`).
3. **Base-first `addu` without a new name**: reverse the operands (`(i << 6) + base`, `idx + array[k]`, `x + 0x10 + (i << 6)`) before trying `m = base; m += ...` (that one adds a name, which can move the frame or registers) (`func_15160B74`, `func_1512D5E0`, `func_15177638`).
4. **A stack local 8-16 bytes too high with ret/spill slots right**: declare it inside the block that uses it (`if (...) { V3 out; ... }`) (`func_15160B74`). A phi float (`k = c1 / c2 / 0`) declared after `mf` fills the gap below `mf` instead of growing the frame (`func_1512D5E0`).
5. A `beq v0, -1, <shared return 0 label>` = `if (call != -1) { ... return 1; } return 0;` (`func_151DD588`).

## s86 recipes (libultra from decompals/ultralib)
See `docs/sessions/s86.md`. Reference clone `tools/ultralib` (gitignored; `git clone --depth 1 https://github.com/decompals/ultralib tools/ultralib`).
1. **Write the ultralib source, pick the branch by the asm**: `#if BUILD_VERSION >= VERSION_J` blocks are visible (single vs double `__osEepStatus`, `ptr += 4` vs a 4-step `ptr++` loop, NOP fill loops, `& 0x3FFF) == 0x2000` in aisetnextbuf). This ROM mixes them per file. Then try `SCREEN_OPT=-O1`, default, `-O2`, `-O3` (io -O1 when every local lives on the stack and no delay slot is filled; gu -O2/-O3).
2. **Static vs extern**: a function-/file-scope `static` is addressed with `lui at` at every access; an `extern` gets its address CSE'd into a register (s-reg in loops). When the ref has `lui at` per access of a libultra static, the C needs the real `static` (and the file must own that `.data`, `rodata_split.py <stem> a b --section .data`; turn the neighbouring `rodatabin` blobs of that segment into `databin`, splat links all `.data` before `.rodata`).
3. **Separate symbol for an array end**: `&stack[SIZE]` that equals the address of the next object (`&viEventQueue`) is a different symbol in C and is not CSE'd with it: add the array's start symbol to `undefined_syms.eu.txt` and pass `&D_x[SIZE]`.
4. **-O3 reverses function order** in the object (`game_21D5F0`): write the source in reverse ROM order.
5. Old `FIX32TOF` divides (`/ 65536.0f`, `lui 0x4780`), new multiplies by `1/65536`. Undeclared macros (e.g. `CHECK_IPAGE` missing from `src/libultra/io/controller.h`) compile as implicit calls: define them.

## s88 recipes (identifying unnamed libultra copies, data a libultra file defines)
See `docs/sessions/s88.md`.
1. **Identify unnamed functions by their callees and constants**: `jal memcpy` + `addu v0,v0,n` = proutSprintf (next function = sprintf, calls `_Printf`); a guMtxIdentF call + `2.0f/-2.0f/1.0f` + stack args = guOrthoF/guOrtho; `__osContPifRam` + `__osMaxControllers` loop with `& 0xC0 >> 4` = osContGetReadData; `0xFF,0x23,0x01,0x03` + `__osContAddressCrc` = a mempak/motor pack function (`_MakeMotorData` in old motor.c). Then pick the ultralib version branch by the asm (s86 recipe 1).
2. **A libultra global defined in the same file is addressed differently from an extern**: a `u64` store to an extern takes two `lui at`; to a variable defined in the file (known alignment) one shared `lui at`. Define the variable in C (`u64 osClockRate = ...;`) and own the `.data`; a definition that also has an `undefined_syms.eu.txt` assignment links fine (script value wins, same address). Add the old auto `D_` name to `undefined_syms.eu.txt` (`/* */` comments only: ld scripts reject `//`).
3. **Owning `.data` inside a data blob**: after `rodata_split.py <stem> a b --section .data`, the blob pieces after it must be `rodatabin` (splat links every `.data` piece before every `.rodata` piece of a segment); a later `.rodata` split in the same area then keeps ROM order.
4. **Old libultra I/O wait** is `stat = IO_READ(PI_STATUS_REG); while (stat & 3) stat = IO_READ(PI_STATUS_REG);` (load, test, store in the delay slot, then a separate loop body), not `while ((stat = IO_READ(...)) & 3);`.

## s91 recipes (porting from reference decomps; Perfect Dark mp3)
See `docs/sessions/s91.md`.
1. **Check the reference repos by callee signature**: a struct with a `dmafunc(s32, u8 *, s32, s32)` callback at 0x4 and a 6-slot buffer ring = PD `lib/mp3` (`tools/perfect_dark`). Conker's struct offsets equal PD's `struct asistream`, so the PD source compiles 1:1 at the file's `-g`.
2. **Port flow**: `pdport.py ctx` + `func` -> draft, `try`; on DIFF, `pdport.py relmap` + `rename` (PD globals -> `D_` names), `try` again; always build the ROM after applying (relocation-normalised OK hides swapped symbols).
3. **A file whose functions build local arrays from initialisers needs its `.rodata`**: if the reference also has the file's const tables, compile them alone and compare with the ROM; when identical, define them in C, own the whole range and mark it `// rodata_inject: cdefined a b`.
4. A reference `f32 *` global that the ref indexes with `lui at; addu at; lwc1 %lo(at)` is an array in this game: declare `extern f32 D_x[];`.
5. A `static` local in a gu file (`guRandom` xseed) needs the function in its own file (the containing file had other flags) plus the owned `.data` piece (16-byte aligned start).


## s98 recipes (f32 params in a-regs, &arg compares, stack-struct callers)
See `docs/sessions/s98.md`.
1. **`mtc1 a1,f12; mtc1 a2,f14` and `sw a3; lwc1 f,0x(a3 home)`** at entry = `f32` params after a non-float first param (`func_151AF938`). If a matched C caller declares them `s32`, retype that caller's pass-through params to `f32` (same bytes) instead of casting the call (a function-pointer cast gives `jalr`; a block-scope prototype conflicts with the definition).
2. **All args homed and one of them loaded twice in an `||` condition** (`lw t8,0x24(sp)` and `lw t1,0x24(sp)`): `&arg` for every arg, `*pa` everywhere, then `t = (*pa1)->a == p->a; if (1) {} if (t || (*pa1)->b == p->b)` (fakematch: the empty block splits the first compare off) (`func_151BE65C`).
3. A frame-slot-only DIFF2 (one float spill 8 bytes off) is worth one remote permuter run before declaration sweeps: `func_1519150C` was OK in seconds with `s32 pad; u8 *p; f32 s; f32 c;`.
4. **Stack-struct callers with several structs**: struct fields at the m2c sp offsets, structs declared from the highest address down (plus a top `s32 pad` if the frame has 4 free bytes at the top); then sweep the positions of the statements that read a reloaded arg (`arg0->unique_id`, `= arg0`): they fix both the reload count and the store order (`func_1514E57C`).
5. A rodata float in a file that does not own `.rodata` can be read through the extern `D_800Axxxx` symbol (same `lui/lwc1`); run `needsyms.py --apply`.

## s97 recipes (homed args, empty multi-arg stubs, clip helpers)
See `docs/sessions/s97.md`.
1. **An arg reloaded from its home slot after calls** (`lw s0,0x20(sp)` of arg0 where -O2 would keep it in a register): take its address, `struct210 **pa = &arg0;` and use `*pa` (fakematch) (`func_151C9A84`/`9B88`). Probably the same fix for the s95 open `func_1519150C`/`B1DD8` (`p = arg0 + 0x110` spilled).
2. **Caller homes `sw a2`/`sw a3` at entry and reloads `lw a2` before a call**: the params are not `s32`: a third `f32` param (in a2) and a `u8` param (`andi` + homed) (`func_151A13F0`).
3. **Calls with more args than an empty C stub declares**: give the empty definition the full signature (same bytes) and a prototype above the callers (`func_151A177C`, 28 params).
4. **Template copy spawners** (`spXX = *(T *)(arg0 + 0xYY)` runs into two stack structs): generate a struct with fields at the m2c sp offsets and keep m2c's statement order (`s97_drafts/gen6e68.py`): OK at once.
5. Clip-vertex lerp (`t = a->x / (a->x - b->x)`) goes **before** `out->x = 0.0f;` even though the zero store is scheduled first.

## s95 recipes (spawner hi members, twins, late double alignment)
See `docs/sessions/s95.md`.
1. **`func_151308E4` spawners in the hi slice**: `tools/eu_port/spgen2.py func draft.c docs/sessions/s95_drafts/af04_Ay.c out.c` (m2c struct base shifted onto the s92 template); `func_151B0238` OK as generated. A frame 8 bytes too big with all offsets 4 high = struct 0x70 not 0x74 (`pad98[0xC]`); offsets 4 low with the frame right = struct 0x74.
2. **A product of a global and a literal used three times** (`k = 0.087f * D_x;` then `-argN * k`): the statement's position among the plain stores fixes the load order; sweep it over the neighbouring stores (`func_151A4BE8`: after `sp.u6C = arg2;`).
3. **Twin with library calls renamed**: when a hi twin calls `func_150AD78C`/`func_150AD780` where the lo one calls `sinf`/`cosf`, map them by call order in the asm, not by a sorted diff (`func_15179A38`: the first call is `func_150AD78C`). `check_files` passes either way (relocations); only the full ROM catches it.
4. **u8 nested loops over linked lists with the j/i increments in the exit block** (`beql a0,zero` to `addiu v1,v1,1`): a `next: ;` label at the end of the innermost loop body (permuter, fakematch) (`func_15105C24`).
5. **A GLOBAL_ASM double after a C jump table lands 4 bytes low**: `// rodata_inject: late_align8 <rom addr>` in the C file (asm-processor `.late_rodata_alignment 8`) (debugger_257350).
6. A function a matched caller calls implicitly (int) cannot be defined with a pointer return type: add the real prototype above the caller and check the caller still matches (`func_151A7188`). `s32` (long) is not `int` to cfe either.

## s93 recipes (libc printf family, PD mp3)
See `docs/sessions/s93.md`.
1. **libultra libc was compiled without `-signed`** (plain `char` = `lbu`), the project uses `-signed`: put `#define char unsigned char` inside the function body (after the signature, so prototypes still agree) and `#undef char` after it; make `_Pft.qual` `unsigned char`.
2. **Back-branch delay slot holds a copy of the loop head's first load** (`addiu a3,s2,1; b top+4; lbu s0,0(a3)`) and the preceding `if` uses `beql` into the tail, but mine puts the tail assignment in the `b` delay slot: a `dummy: ;` label after the last statement of the loop body splits the tail block (fakematch; `_Printf` both copies).
3. **Old xprintf scan loop** is GoldenEye's `for (c = *s; (c = *s++) > 0;) { if (c == '%') { s--; break; } }` (`blez` on the loaded byte), not PD/ultralib's `c != 0 && c != '%'`.
4. A string literal in a file that does not own `.rodata` links into a discarded section (`ld: defined in discarded section .rodata`): use the `extern` D_ symbol.
5. A local pointer copy of a `void *` parameter (`_Pft *args = arg0;`) costs a stack slot at `-O2 -g3`: use a macro cast (`#define args ((_Pft *)arg0)`) when the header prototype must stay `void *`.
6. PD mp3 in Conker: `mp3main00043dd0` returns `0` on failure (`if (sp954 == 0)`), `var8009c650` is a pointer (`**`), `sine_block` is `D_800E1268`.

## s107 recipes (gSPSegment loops, flag temps, arg homes)
See `docs/sessions/s107.md`.
1. **gSPSegment loop with the call inside** (`or v1,s2; andi seg; or 0xDB06...; sw; sw v0`): put the call result in a named temp before `gSPSegment(gfx++, i + 1, a)` (inline call makes the macro compute w0 first); loop `i` from 0 with `i + 1` as the segment gives the ref's two strength-reduced counters (`func_150C8B00`).
2. **Frame 8 high with right code**: merge a named temp into another dead scalar (`lvl = func(...)`), then `tryall` the declaration orders (`func_150C8B00`).
3. **Two `andi x,v0,0xFF` from one compare** (one for the `if`, one for the `u8` var spilled with `sb`): `b = cmp; a = b; if ((u8)b)` with `s32 b`, `u8 a` (`func_150F6EDC`).
4. **Arg reloaded from its home (`lw v1,0x88(sp)`) instead of s0**: cut the number of arg uses: derive a sub-pointer once (`p = arg0 + 0x28; m = p[2] * rand`) (`func_150C29F0`).
OPEN: `func_150C29F0` perm DIFF2, `func_150F6EDC` DIFF25, `func_150C8DD0` SIZE-2 (`li s1,5` + `multu`), `func_150F66F8` (frame).
## s105 recipes (lui-able constants from .rodata, extern runs in owned files, emitter structs)
See `docs/sessions/s105.md`.
1. **A float whose low 16 bits are zero (`1655.0f` = 0x44CEE000) loaded with `lui at; lwc1` from `.rodata`**: no literal form gives that (`1655.0f`, `(f32)1655.0`, `1655`, `1655.0` all fold to `lui; mtc1`); a function-scope `static const` gives the code but the wrong `.rodata` position. Use `extern f32 D_x;` (`func_150C2700`).
2. **Externs in a file that owns `.rodata`**: `rodata_inject.py` attaches named externs to the next GLOBAL_ASM function, so a run of externs is fine when it ends right before that function's items; turn the C neighbours in between back into externs to keep the order (`func_150C2804`, `func_150C2898` -> `func_150C29F0`). Check with `rodata_inject.py <stem> --dry`.
3. **Frame 8 bytes too big with identical code** after switching an extern to a literal (`func_150C2898`, `0.001f`) or with a named float temp (`func_150C2558`): keep the extern / write the value into the struct field and reuse the field (no reload).
4. Small spawners with one stack struct: put the statement whose constant is shared (CSE'd, e.g. `6` stored twice) or the stack-arg float (`s.u10 = arg4;`) first; IDO numbers t/f registers in source order of first use, the stores are scheduled anyway (`func_150C2700`).
OPEN: `func_150C2290` DIFF37 / `func_150C2558` SIZE+1 (t-register numbering in the `func_15151FA8` emitter struct).
## s103 recipes (indirect calls, negated constants, small neighbours)
See `docs/sessions/s103.md`.
1. **`lui t9,%hi(f); addiu t9,%lo(f); jalr t9`** to a known function = a call through a cast function pointer: `((s32 (*)(u32, u32 *))func_151EF800)(...)` (`func_150C3D5C`). Writing to a function's code: `((u32 *)&func_10004074)[0] = ...` (`(u32 *)func` without `&` is a cfe error).
2. **`neg.s` of a constant loaded from `.rodata`** (the same constant appears twice in `.rodata`): the source had a local `m = 0.55f;` used as `t = m;` and `t = -m;` (`func_150E0228`); a `-0.55f` literal folds.
3. **A constant materialised straight into the argument register** (`lui a0; ori a0,a0`) and stored to a local: the local is `s32`, not `u32` (`func_150C3D5C`, permuter).
4. `lwr`/`swr` at offset 2 with no `lwl`/`swl` = copy of a 3-byte struct (`typedef struct { u8 a[3]; } Tri3; Tri3 t = D_x;`) (`func_150DFE40`).
5. **A loaded value in `v0`/`a0` instead of a t-register**: give it its own named local (`k = D_800DD835; a = D_800906D4[k + 9];`), declared after the arrays so it does not shift their slots (`func_150E0150`); a command word read into `a0`: `w = g[i].w0;` (`func_150E0350`).
6. Spawner hand drafts (`func_150F6A5C`, `func_150E047C`): `SubX *s = (SubX *)(arg0 + 0x28); obj = s->o;`, then Header/Header2/`u8 col[4]` locals; the frame by declaration order (`s, obj, n, pos, header, header2, col`), and a label barrier from the remote permuter for the last scheduling diff.
OPEN: `func_150E047C` SIZE-1 (`move v0,t6` copy of the reloaded spill), `func_150C2424` (needs game_EF410 `.rodata`), `func_150F03F8` DIFF160.
## s101 recipes (address CSE across calls, volatile homes, unused block locals)
See `docs/sessions/s101.md`.
1. **`&local` held in an s-register / spilled across calls (SIZE+8) when the ref recomputes `addiu aN,sp,K` at each call**: one of the call args carries an int cast (`(s32)pos`); give the callee a pointer param and pass the array uncast (`func_15070F60`).
2. **An arg reloaded from its home at every single use** (even twice in a row): `u8 *volatile arg0` (the s97 `&arg0` pointer only reloads after stores) (`func_150F1C5C`, still DIFF186 for scheduling).
3. **A dead `sw v0` of a call result into a spill slot** with no later load: the result was folded away, e.g. `(func_150ADA20() % 1U) + 0xFF` (`func_150F1C5C`).
4. Constant float stores scheduled late in mine (`10.0f` pair): an unused block-scoped `s32 blk;` at the top of the `if` body (s69) fixed it after the permuter showed a temp there (`func_15071B18`).
5. Field cached in a local gives one load; the ref reloads after stores in one arm: drop the local and write `arg0->x` at every read (`func_150E523C`).
6. Float literals: always check the bits (`57.295776f`, `-0.97800004f`); m2c / `%g` forms round to the neighbour.
OPEN: `func_1501175C` SIZE+1 (`p = obj + 0x28` must get s1 while `obj` spills), `func_15073A50` DIFF2 (frame 8 high), `func_150C8850` SIZE-1, `func_1506D584` DIFF20.
## s100 recipes (add.s operand order, spawner frame size, float setup order)
1. **`add.s d, prod, lo`** (product first) for a `rand * (hi - lo) + lo` range comes from `lo + (hi - lo) * func_150ADA68()`; `func_150ADA68() * (hi - lo) + lo` gives `add.s d, lo, prod` (func_1514A70C).
2. **Spawner frame 8 bytes too big, offsets right relative to the top**: the `func_151308E4` struct is 0x6C (`u8 pad98[0x8]` after `u97`), with two 4-byte scalars declared **above** it (e.g. `u8 *p; s32 r;` then `struct {...} sp;`). The 0x74 template only fits when nothing is declared above it. Scalars get 4-byte slots in declaration order even when they live in registers (func_15193360, func_151B20E4).
3. Floats loaded once before a spawner loop: the order of the setup statements decides the float registers (`sp.u88 = 0.0f; sp.u58 = K1; scale = K2;` gave the ref `f18/f6/f16`). Sweep the permutations with `tryall`.
4. `extern f32 D_800Axxxx` is a memory load and is never hoisted out of a loop; a literal is (into f20-f30). If the ref keeps a rodata constant in a callee-saved float register across the loop, the file must own `.rodata`.

## s117 recipes (rodata ownership pads, list walks, constant registers)
See `docs/sessions/s117.md`.
1. **A matched C function's odd `s32 pad;` can be a compensation for a file that does not own `.rodata`**: after `rodata_split.py --own <stem> --resplit` the frame of a function with a float literal shrinks by 8; remove the pad (`func_1505D34C` in `game_83300`). Run `check_files.py` on the file after any ownership change.
2. Weighted random list walk `n = list; while (n->w < r) { r -= n->w; n = n->next; }`: assign `n` **after** the rand call, or `n` lives across the call in an s-reg (`func_150E909C`).
3. A local constant copy `m = 61.0f; k = m; ... k = -m;` gives `mov.s`/`neg.s` from one materialised constant (s103 recipe for floats), and `r -= c; if (r < d)` gives the in-place `sub.s` (`func_150B0F40`).
4. `u8` loop index times a constant always gave `multu` here (also `(s32)i * 3`, `(u8 *)p + i * 12`); the ref's `sll/subu/sll` for one of two `i*12` terms is unexplained (`func_150FFC60`, open).
OPEN: `func_150FFC60` SIZE-1, `func_150E752C` perm DIFF2, `func_1507E690` SIZE-1, `func_150FB06C` SIZE-4, `func_150E909C` perm DIFF7, `func_1505F188` DIFF14 (perm).
## s114 recipes (shared value stores, sign step, one reused temp, spawner structs)
See `docs/sessions/s114.md`.
1. **One value stored to two struct fields with other stores between (`sh t1,a; sh zero..; sh t1,b`) and the frame 8 too big with a named temp**: `s.a = s.b = expr;` (the left field is stored first) (`func_1514A434`).
2. **Sign step `li v0,1; bgez x,L; nop; b L; li v0,-1`** (the `b` to the next instruction): `if (x < 0) { s = -1; } else { s = 1; }`; `s = 1; if (x < 0) s = -1;`, ternaries and block-local declarations give `bgezl` or extra moves (`func_1517A75C`, not yet a full match; try it on `func_1511B4B8`).
3. **The ref keeps a loaded field, a difference and a later result all in v0**: one `s32 t` reused for all three (`t = A6; ... t = x - v; if (t <= 0) ... t = t - D;`) (`func_1517ADBC`).
4. **Global float address `lui/addiu` in v1 where mine uses v0** (with `li v0,1` for the return scheduled early in the ref): a second name `q = arg0;` used for the later stores (permuter fakematch, `func_1518F5C8`).
5. Spawner arg read from its home slot into v0 (`lh v0,0x5A(sp)`) where mine uses v1: `p2 = &arg2;` and read through `*p2`, plus an `if (arg0) {}` barrier (permuter, `func_151AED60`). Spawner `s.p = arg0` (arg reloaded from its home slot) placement: sweep its position among the stores (`func_151C6750`).
6. Stack locals: the first declared array gets the highest address. `pos[3]` at 0x5C, `vel[3]` at 0x50, `sp48` at 0x48: `f32 pos[3]; f32 vel[3]; u8 *obj; s32 sp48;` (the register pointer fills the gap) (`func_151AA8BC`).
OPEN: `func_151AED60` code OK but `.rodata` 3 zero words between two C functions' items; `func_1518F4C4` DIFF1 (third lerp add order); `func_151DBE80` frame +8.
## s120 recipes (tail recursion, store forwarding, C-defined rodata tables, fn-select if/else)
See `docs/sessions/s120.md`.
1. **A recursive function whose body ends in a loop back to the top, with args re-normalised (`sll/sra`) and a stack-passed arg stored back to its home**: IDO -O2 eliminated the *tail* recursive call. Write both calls (`f(.., lo, mid, ..); f(.., mid, hi, ..);`) and a guard `if (hi - lo < 2 || depth <= 0) return;` (`func_151A88F0`, SIZE-1).
2. **A pointer stored to a field and then used from a register for the next uses, but reloaded after a store through it**: store-to-load forwarding. Write `s->tbl = X; s->end = &s->tbl[n]; s->tbl->x = 0;` (no local `p`; a local is folded into `s + k` offsets) (`func_151A7F00`).
3. **`lui/lwc1 %lo(D_x)` of a value that starts a block of unreferenced data words**: a file-scope const table, not a literal. Define `const u32 D_x[N] = {...};` in C, read `*(f32 *)D_x`, add `// rodata_inject: cdefined <rom a> <rom b>`. IDO emits const data before every float literal (`func_151A8BD4`).
4. **`li s7, A; if (c) { li s7, B; b next }`**: `if (c) fn = B; else fn = A;` (IDO hoists the else store; a plain `fn = A; if (c) fn = B;` gives no branch) (`func_151A929C`).
5. **Same byte field loaded twice (`lb` for a `!= -1` test, `lb` again as a table index)**: use different expressions, `*(s8 *)(p + k) != -1` and `D[(s8)p[k]]` (`func_151A929C`).
6. An arg narrowed by `lbu N+3(sp)` from its home when passed to a `u8` callee slot is an `int`/`s32` param, not `u8` (`func_151473F4`; the permuter found it).
7. Permuter: pycparser parses `n * sizeof(T) + x` as a cast and the base fails to compile ("Bad type name for cast operator"); write `n * 0x18U`.
OPEN: `func_151A7F00` DIFF1 (`addu` order), `func_151A88F0` SIZE-1, `func_151A9670` DIFF2, `func_151473F4` DIFF3, `func_151D1694` DIFF12, `func_151A8DA8` DIFF91, `func_16000590` DIFF23.
## s118 recipes (mul.s order, spill slot via struct tail, hoisted literal = rodata)
See `docs/sessions/s118.md`.
1. **`mul.s d, p, prod` where `prod = obj[0] * K` and `p = *ptr`**: write `*p * (obj[0] * K)`. `(obj[0] * K) * *p` swaps the source registers (`func_151DA938`). Also: the first of two Node14 reads written raw (`*(f32 *)(tbl + i * 0x14)`) gives the swapped `addu` even after a spill reload. Use `((Node14 *)tbl)[i].x` for both (`func_1518A42C`).
2. **Compiler spill slot of a returned pointer (`sw v0,X(sp)` around a memcpy) at the frame top instead of just below a stack struct**: the struct is 4 bytes longer in the source. Add a tail field (`s32 u84;`) and drop pads (`func_151CF05C`).
3. **A float load hoisted out of a loop into a callee-saved FPR (`lwc1 f22` before the loop)**: it is a float literal (`.rodata`), not an extern global. A global would be reloaded after each call. Make the file own `.rodata` (`rodata_split.py --own`) and write the literal (`func_151A9DE4`, `3.1415927f`).
4. Small table copied to the stack with `lw at; sw at; lhu at; sh at` from an extern: `typedef struct { s16 v[3]; } T; extern T D_x; T t = D_x;` works without owning `.data` (`func_151A975C`).
5. A function called through an implicit declaration earlier in the file: a K&R definition must return `int`, not `s32` (`s32` is `long`, so cfe gives "Incompatible function return type").
OPEN: `func_1518CC0C` DIFF3, `func_151473F4` DIFF9 (arg homes), `func_151A9670` DIFF3 (byte local slot), `func_151D1694` DIFF12 (u8 param reloaded by `lbu`).
## s116 recipes (rodata file boundary, Node14 table, spawner arg reuse)
See `docs/sessions/s116.md`.
1. **C function code-OK but unreferenced zero words of `.rodata` between two C functions' items**: if the zeros end on a 16-byte boundary (and the text boundary is 16-aligned), it is an EU object boundary: `file_split.py <stem> --at <func> --rodata <rom> --resplit` (`func_151AED60`).
2. **`multu idx,20` + `addu t,tbl,prod` table read** (`arg0+0x94` table, `s8` index at `arg0+0x2D`): `((Node14 *)tbl)[idx].x/.z` with `typedef struct { f32 x, y, z; s32 a, b; } Node14;`; the raw `*(f32 *)(tbl + idx * 0x14)` gives `addu t,prod,tbl` (`func_1518CAEC`, `func_151AC9B8`).
3. **A position vector built from the table and `arg4`**: write `pos[0] = tbl[i].x; pos[1] = arg4; pos[2] = tbl[i].z;` (x,y,z order); `pos[1]` first loads `arg4` too early (`func_151AC9B8`, `func_1518CC0C`).
4. **A truncated float kept across a call, spilled 4 bytes higher than a named `s32 v` gets**: assign it to an unused int parameter (`arg2 = arg4;`, fakematch) (`func_1518CAEC`, permuter).
5. Third of three lerps with `add.s d, a, prod` like the others: `(b - a) * t + a`, not `a + t * (b - a)` (`func_1518F4C4`).
OPEN: `func_1518A42C` DIFF1 (`addu` order after a spill reload), `func_1518CC0C` DIFF3 (`li a0,20` one slot late), `func_151DA938` DIFF4 (`obj + 0x48` kept in v0).
## s115 recipes (lo rand callers: unsigned modulo, K&R no-arg, CERR rows)
See `docs/sessions/s115.md`.
1. **`divu` for `rand() % n` with a narrow or signed `n`**: write `% (u32)n`; `u8 n` promotes to int and gives `div` + the `-1/0x80000000` break checks (`func_1509F834`, `func_150C851C`).
2. **`or sX,sY,zero` in the rand `jal` delay slot, then `addu sX,sY,hi`**: the source copies first, `v = lo; v += rand() % (u32)range;`. The order of the two loop-invariant lines (`range` before `lo`) sets the t7/t8 numbering (`func_150C851C`).
3. **Function whose `a0` is never homed although a matched caller passes an argument**: the definition takes no params; declare it `void f();` (K&R) in the file and define `void f() {` (`func_150E8EB0`). A global tested twice (`lw` reloaded before the second `beqz`): write the global in both `if`s, not a local.
4. A byte-table loop count loaded straight into an s-register: `s32 n = table[i];` (`u8 n` gives `lbu v0` + move) (`func_1503F2B4`).
5. **randscreen CERR rows are cheap**: implicit declarations (a call earlier in the file), the file's own prototype of a callee, a typedef declared below the pragma. Fix the file's declarations (move the typedef/extern up, add prototypes) and screen again (`func_150C851C`, `func_150E8EB0`).
6. A 5-byte stack copy done with `lw at; sw at; lbu at; sb at` through `t6 = &local` is an IDO initializer template (`u8 ids[5] = {...}`, aligned by the compiler): needs the file to own `.data` (`func_151008C0`, open).
OPEN: `func_150B0F40` SIZE-1, `func_1506E46C` SIZE-6 (spilled `v & 0x7FFF`), `func_1505F188` DIFF27 (f0/f2 roles; literal needs `.rodata`), `func_150E752C` SIZE-1.
## s113 recipes (extern-only late rodata, label barrier, u8 flag args)
See `docs/sessions/s113.md`.
1. **Extern floats in an owned file with no late GLOBAL_ASM neighbour** (s111 recipe 4): `rodata_inject.py` now moves an extern-only late region into the regular `.rodata` of a GLOBAL_ASM neighbour; keep the externs (`func_150BDE34`). `static const f32` goes to `.data` in IDO, never `.rodata`.
2. **`b L` whose delay slot holds the target's first insn (`lbu t8,0xD7(sp)`) instead of the preceding `swc1`**: a label right before the inner switch's last `break` (`dummy: ;`, fakematch) stops IDO from moving the store into the slot (`func_150E7C50`, permuter).
3. **Rand flag pair passed to a `u8` param with a constant** (`or t8,v1,t0; ori t6,t8,9; andi a3,t6,255`): `(u8)((A ? 2 : 0) | (B ? 4 : 0)) | 9` inline in the call; `(... | 9) & 0xFF` puts the `or` in a3 (DIFF10), other groupings DIFF4 (`func_150E7810`).
4. Spawner with a stack struct whose top lies 0x18 below the frame top: `s32 pad[6];` declared first (`func_150E7C50`); for several locals copy the ref offsets by declaration order (first declared = highest).
OPEN: `func_150B3CA8` DIFF95 (all declared locals 4 bytes high, spill temps right), `func_150F0BEC`/`func_150B6314` (2nd flag `andi` t0 vs t3), `func_150BAEF4` DIFF3.
## s111 recipes (K&R callee for array args, struct-member pointer spill, owned-rodata externs)
See `docs/sessions/s111.md`.
1. **`addiu a1,sp,X` spilled to a stack slot and reloaded for later calls (frame +8)** when a local array goes to a fully prototyped `s32` param as `(s32) pos`: declare the callee K&R (`void func_151000EC();`) and pass `pos` uncast; the ref rematerialises the address per call (`func_150FF840`).
2. **A pointer stored to the stack late (`sw v1,X(sp)` in a `jal` delay slot) and reloaded after a memcpy**: it is a member of the stack struct whose tail is memcpy'd (`b.q = q; ... memcpy(r + 0x70, &b.p, 0x58)`), not a spill; declaring it fixes the slot layout (`func_150BE40C`, DIFF21: the reads through `q` still fold to `40(s0)`).
3. **A rand result kept across the next rand inside one call's arguments**: inline both rand calls in the argument list; a named `f32 r` takes a slot 4 bytes too high (`func_150BAEF4`, DIFF5 -> DIFF3).
4. **Extern floats in a file that owns `.rodata`** (`game_eu_EB430`): code can be bit-exact with `extern f32 D_x` but `rodata_inject` FAILs ("named by C code ... define it in C") and apply.py REJECTs; literals give frame +8 (s105 recipe 3), file-scope `const f32 D_x = ...;` did not land in `.rodata`. OPEN for `func_150BDE34`.
OPEN: `func_150F0BEC` / `func_150B6314` (`func_151307F0` flag pair: 2nd `andi` t0 vs t3), `func_150FF840` DIFF25 (loads hoisted above `if (arg1)`), `func_150C1BC0` (needs `game_eu_EF370` `.rodata`).
## s112 recipes (range-0 rand terms, all-inline rands, K&R flag callee, lo + (hi - lo) * rand)
See `docs/sessions/s112.md`.
1. **A rand call whose result is spilled but never used, or `mul.s f, rand, zero` with `mtc1 zero`**: the source had a range-0 random term. Write `(func_150ADA20() % 1U) + 0xFF` (the call and its spill stay, the term folds) (`func_151C5B38`) or `func_150ADA68() * (f32)0 + 0.68f` (`* 0.0f` is folded away completely, `(f32)0` keeps the multiply) (`func_151B0600`).
2. **Spawner with every rand result spilled to consecutive stack words**: put **all** rand calls inline in the callee's argument list (no named temps) and add `s32 pad;` first if the frame is 8 short; screening named vs inline for each rand (2^n x decl orders) found it at once (`func_151AEF34`, `func_151D5BF8`). The header's `s16`/`u8` slot gets no `sll/sra`/`andi` when the value is `(u32)rand % K + C`.
3. **Field lerp from rand, `mul.s f, rand, d; add.s f, prod, lo`**: `lo + (hi - lo) * func_150ADA68()` (both other orders swap one operand) (`func_1518F710`, `func_1518F8F4`). A pointer `p = arg0 + K` that the ref keeps in a register for a later test: `if (p) {}` right after the assignment (permuter fakematch, `func_1518F8F4`).
4. **`li a1,0; c.lt.s; bc1f L; nop; b L; li a1,1` (flag from a float compare) passed unmasked to a `u8` callee param**: `a = (cond) ? 1 : 0;` with `s32 a`, and the callee declared **K&R**: `void func_151AF064();` before the caller and a K&R definition `void func_151AF064(arg0, arg1, arg2) s32 arg0; u8 arg1; u8 arg2; {` (the callee still matches; a `()` declaration next to a prototyped definition is a cfe error) (`func_151AEE40`).
5. Stack word whose byte at +4 is stored before a call that takes `&word`: a local struct `{ u8 *p; u8 b; }` (m2c drops the byte store as dead) (`func_15190770`). Frame 8-16 bytes too big with a named pointer to `arg0[i]` spilled across a call: drop the name and repeat `arg0[arg1]` (`func_151D6310`).
6. Int lerp `x += (s32)((f - x) * K)` with `addu t, x, conv`: `x = (s32)((f - x) * K) + x` (`func_1518F710`). Loop prologue `m = (s32)(arg0 * 8.0f); arg0 *= 0.5f;` hoisted by hand (ref reuses the arg's FPR), `x -= 0x20` split from `x = rand & 0x3F` (`func_1517AF90`).
OPEN: `func_1511B4B8` SIZE+2 (sign step `b` to the same label), `func_1515ACFC` perm DIFF14, `func_151D58E4` SIZE-1 (struct address computed twice).
## s110 recipes (callee prototypes, f32 params passed as words, lerp +=, frame pads)
See `docs/sessions/s110.md`.
1. **Prototype first, by tool**: `tools/eu_port/realproto.py show func_X` lists every prototype of a callee in the matched sources (C definition first, then by file count; `FLAG` = arity / int-float class disagree), `realproto.py fix in.c out.c [file.c]` rewrites a draft with them (header, then the target file's own declaration, then rank 1; unknown types -> `void *`/`s32`). When a callee has no matched prototype, read its arity off the caller's asm: m2c can insert a bogus arg (`func_1516AAA8`: m2c passed `arg0` as the 3rd arg of `func_151722BC`; the ref passes a float in a2 via `mfc1 a2`).
2. **`mtc1 a1,f12` / `lwc1 f16,0x7C(sp)` at the top of a callee whose prototype says `s32`**: the params are really `f32` (after a pointer arg0 the floats travel in a1..a3). Retype the callee *and* the matched caller in the same file (`func_151B53FC(..., f32 arg3, f32 arg4, f32 arg5, ...)` still matched byte for byte, the values only pass through) (`func_151B5454`, `func_151B56A4`).
3. **Lerp `x += (y - x) * K`** written as one compound statement gives `add.s f, x, prod` (x first); m2c's `t = x; x = t + (y - t) * K;` gives the operands swapped. Rand terms of the same function read best as `base + field * func_150ADA68()` (`func_1514C178`).
4. **Frame 8 bytes too small and every stack local 4 bytes low** (common in m2c spawner drafts): one `s32 pad;` declared first (fakematch). A 16-byte gap: `s32 pad[2];` above and `s32 pad2;` between the locals (`func_1511FD20`, `func_1516AAA8`, `func_151B5454`, `func_151B56A4`, `func_151B5590`).
5. `li a2,1` hoisted and shared by `st == 1` and a later `*(s8 *)p = 1` (ref keeps separate `li at,1` / `li t7,1`): declare the loaded state `u32 st;` (permuter) (`func_1511FD20`).
6. A one-byte flag passed by address (`memcpy(ret + 0x58, &flag, 1)`, `sb t9,0x20(sp)` at the *start* of its word): `u8 flag[1]`; a scalar `u8` sits at +3. Spawner float fields: the field stored from `mtc1 zero` gets f4, so its statement (`sp.u38 = 0.0f`) comes first among the float stores; the `arg0[0x3B]` byte load goes right after the two zero words (`func_151B5280`, `func_151B5590`).
7. Frame 8 bytes too big with one address-taken `u8` and a function-pointer call: the declaration order of the fn-pointer temp vs the flag (`s32 (*fp)(...); u8 flag;`) and one pointer temp reused for two `if (p = ...) *(V3 *)(p + 0x40) = ...` struct copies (permuter) (`func_1510660C`).
8. **Loop with two strength-reduced pointers (`move s1,s3; move s0,s4` at the loop top)**: index form `dst = &d[i]; q = src + (i - 1) * 0x34;` inside `for (i = 1; i < n + 1; i++)` (the `n + 1 < 2` head test), the address-taken `f32 s, c` + `s32 pad` block-local in the loop; the s-register order came from a permuter `if (!arg0) {}` barrier; then sweep the 3-4 operand orders of each `a*c + b*s + k` line in one `tryall` (16 + 4 variants; the right one was `k + (b*s + a*c)` for all three) (`func_15106B90`).
OPEN: `func_151AEE40` SIZE-2 (`func_151AF064(s32, u8, u8)` defined later in the file but the call passes the flag unmasked: a cast call gives `jalr`).
## s108 recipes (rand loop counts, real callee prototypes, pointer in rand args)
See `docs/sessions/s108.md`.
1. **Spawner loop count `n = base + rand() % (k + 1)` where the ref's first in-loop rand result lands in the other s-register** (`move s1,v0` vs `move s3,v0`): write it as `n = func_150ADA20(); n = base + (n % (u32)(k + 1));` (permuter, `func_1515423C`, `func_15151500`, `func_15152DE4`).
2. **gensome prototypes of big spawner callees are often wrong** (m2c drops stack args). Take the prototype from a matched caller (`grep -rn 'func_X(' conker/src_eu`) before anything else: `func_151DA6F8` has 18 args, not 15 (`func_15154488`). Two drafts in one file need byte-identical local prototypes, or apply.py REJECTs the second.
3. A stack array 4 bytes below its ref slot with the frame right: declare the register-allocated loop counter `s32 n;` **before** the array (`func_15154488`, `func_1515128C`, `func_151BC6B4` with `ret`).
4. Float rand arg `mul.s f0,f4` (rand first): read the field **through the pointer local** in the argument, `p[8] * func_150ADA68()`, with `p` assigned before the call; `*(f32 *)(arg0 + 0x48)` or the other operand order gives DIFF1 or SIZE+1 (`func_151A951C`).
5. `beq fp,v0` (constant -1 register first) for `if (i != -1)` with `s8 i`: `if (i != 0xFFFFFFFF)` (`func_15152DE4`).
OPEN: `func_151BC6B4` DIFF71 (block-2 struct offsets), `func_151570C4` DIFF2 (frame +8), `func_15141478` SIZE-1 (spilled CSE temp).
## s106 recipes (inline rand args, u8 callee slots, same-line do-while)
See `docs/sessions/s106.md`.
1. **Rand spawner loops (`func_150ADA20`/`func_150ADA68` results feeding one big call)**: when m2c's temps (`temp_s3 = rand(); ... f(temp_s3 % ...)`) leave operand-order diffs (`addu a1,t2,t3`, `mul.s f6,f0,f4` swapped) that no source swap fixes, put **every rand call inline in the argument list** (`f(base + rand() % (n + 1), base2 + field * func_150ADA68(), ...)`): IDO evaluates call arguments left to right, which gives exactly the ref's call order and operand order; write ints as `base + rand() % (n + 1)` and floats as `base + field * func_150ADA68()` (`func_15150258`, `func_15154BF4`). A float flag argument from a rand compare is also inline: `func_150ADA68() < *(f32 *)(arg0 + 0x34)` (no `? 1 : 0`).
2. **`andi s1,a1,0xFF` then `move s5,s1` (SIZE+1) for a `u8` param passed on to a callee** (the ref does `andi s5,a1,0xFF` once): declare the callee's slot `u8` in its prototype (`..., u8, s32)`); with `s32` the value is copied to a second register (`func_15150258`, `func_15154BF4`; same problem as `func_15151500` in the older recipe). A `u8` param that the ref also homes (`sw a1,0x94(sp)`) is still a plain `u8` param.
3. Flag kept in `v0` across `if` blocks (`lbu v0,0(s0)` ... `andi v0,t8,0xFF`): declare it `s32`, not `u8`; `f = arg0[0] |= 1;` placed after the first of the following float stores matches the store order (`func_1514FC58`).
4. Address of a global float (`lui v1; addiu v1` for `D_800BE9A4`) hoisted into the first basic block: a **same-line** `do { t = p[0]; x = ...; } while (0);` (permuter; on separate lines it does not match) (`func_15154A9C`).
5. Stack struct passed to a spawner with a lone `s16` local at sp+0x20 below it: an unused `s16 zp;` declared before it puts it at the right slot (fakematch); the `arg0[0x3B]` byte load scheduled first = that field is the first statement (`func_151BD8A8`).
6. `addu a0,v0,t9` (ret + loaded offset) that no source order gives (mine `addu a0,t9,v0`): `ret + *(s32 *)(ret + 0x50) + ((0, 0xF8))` comma fakematch (permuter, `func_151BA4B0`); `sw a0` of a struct field before an unrelated load: `goto l; l: ;` label barrier.
OPEN: `func_151570C4` DIFF2 (frame +8), `func_1514FE68` SIZE+2.
## s104 recipes (unfolded sub-pointers, returned args, array-of-struct copies, spawner byte triples)
See `docs/sessions/s104.md`.
1. **`addiu v1,a0,K` recomputed after a call and spilled, fields read through v1** (mine folds `arg0 + K` into every offset): the pointer is used *before* the call, e.g. `p = arg0 + 0x18; s = sinf(p[6]);` instead of `sinf(*(f32 *)(arg0 + 0x30))` (`func_15162510`).
2. **Pointer arg held in v0 to the end, stores through v0, no final move** (mine uses v1): the function returns that arg (`return arg2;`) (`func_1514FD78`).
3. `lw at,0(tN); sw at,X(a0)` x3 = a 12-byte struct copy. If `addu tN,base,idx` comes out swapped with byte arithmetic in both orders, index an array of 0x14-byte structs: `((E20 *)base)[i].pos` (`func_151BCBFC`).
4. `lw a0,spill; andi a0,a0,0xFF; sll/sra` for an s16 param from a spilled rand: `r & 0xFF`; `(u8)r` gives `lbu a0,spill+3` (`func_1514FD78`).
5. `move v0,zero` in the delay slot of the `bgez` that picks a flag/count pair: `flag = 0; if (x < 0) { n = 300; } else { flag = 1; n = x; }` (not if/else for both, not inverted) (`func_1510A454`).
6. Spawner frame 8 high with one named float temp stored twice: drop it, `sp.u84 = sp.u88 = expr;` (`sp.u88 = sp.u84 = ...` gives the other store order). Byte fields set to the same constant (0xFF) in different blocks of the struct: the ref's register reuse shows the source grouping; interleave the triples (`u7C, u40, uA2, u7D, u41, ...`), then permuter + two `linejoin.py`/`ljsweep.py` rounds (`func_15157294`).
7. Stack frame vs named float temps (again): every named f32 local costs a slot even when it lives in a register; when the frame is too big, replace temps that are also stored to the struct by the struct fields and keep only the ones never stored (`func_1516295C`: only `c`, `d`).
OPEN: `func_151570C4` DIFF7 (permuter), `func_1516295C` DIFF62 (frame right, scheduling).
## s102 recipes (block-scoped struct initializers, rand-flag type, rodata range start)
See `docs/sessions/s102.md`.
1. **Struct-copy destination address computed before the source address** (ref: `addiu a0,sp,X` / `addiu s5,sp,Y` above `lui/addiu tN,D_x`, even hoisted above a `beql`): the copy is a **block-scoped initializer**, `{ V3 c = D_x; func(&c, &b, ...); }`; a plain `c = D_x;` statement loads the source address first. Block locals sit below the outer ones, so move other scalars (here `base`, `ang`) into the loop block to get the offsets back (`func_151B20E4`).
2. **`move s1,v0; andi t5,s1,1; jal ...; move s1,t5`** for a random flag kept across calls: declare the flag `u8` (or `u16`), `a = func_150ADA20() & 1;`; `s32`/`u32` give `andi s1,v0,1` in the delay slot (SIZE-2) (`func_15192F14`).
3. A `lw` hoisted above an earlier `swc1` to a different stack field in mine but not in the ref: a basic-block boundary between the two statements; `if (!p && !p && !p) {}` (remote permuter, fakematch) worked where `{ s32 blk; }`, `if (1) {}` and `if (p) {}` did not (`func_151B20E4`).
4. `rodata_split.py --own` can start the range 0x10 later than the first `D_` label of the file when the bytes before are another file's jump-table word + padding (the warning "unreferenced nonzero bytes before the range" is then harmless): check the injected `.late_rodata` of the first asm function; a foreign word (e.g. a `0x1519xxxx` text address) means the tool's start was right.
5. `p[i] = p[j] * D + p[i]` vs `p[i] += ...` / `D * p[j]`: each of the 4-7 forms gives a different load order; sweep them in one `tryall` (`func_151621B8`, `s * p[3] + p[0]` for `mul.s f0,f6` + `add.s f4,f8`).
OPEN: `func_151570C4` DIFF62 (h2 loads from the spilled `row[j]` scheduled early in the ref; permuter DIFF16 by recomputing `row = D[i]`), `func_15156700` DIFF62 (switch head OK, struct copy temp at sp+0x30), `func_151BD9EC` DIFF98 (frame fixed with pad 2 + two scalars above; t-register numbering after the flag block, the s98 `func_151925AC` problem).
## s109 recipes (rand spawners in the lo slice: named vs inline rand temps)
See `docs/sessions/s109.md`.
1. **s106 recipe 1 (all rands inline) did not fit any lo-slice spawner tried**; the lo ones name the early rands and inline only the last: `a = rand(); b = rand(); c = rand(); f(..., a & 0xFF, (u8)((b & 1) + (c & 1) * 2), ...)`. The ref spills the named ones (`sw v0,0x50(sp)` in the next `jal` delay slot). `tools/eu_port/inlinerand.py draft.c out` writes the all-inline, all-named and "first k named" variants of an m2c draft for one `tryall` (`func_150BA26C`, `func_150E856C`, `func_150D1714`).
2. **Rand temp slots are allocated top-down in declaration order, and a named-but-unspilled temp still takes a slot**: ref `a` at 0x48, `b` 0x4C, `c` 0x50 (c never stored) under the struct at 0x5C = `Struct s; s32 c; s32 b; s32 a;` (`func_150BA26C`). An extra slot above them can be one more named rand (`r4 = rand(); ... r4 % 156U`, `func_150D1714`).
3. **Dead `sw v0,0x48(sp)` of a rand result that is never read**: the results go into an array, `s32 r[3]; r[0] = rand(); r[1] = rand(); ... (r[0] & 3) + 6` (array stores are not dead-store eliminated; `r[2]` makes the frame right) (`func_150FF1A8`).
4. **`andi tN,v0,0xFF` before a rand result goes to a `u8` call slot**: write the mask, `func_150ADA20() & 0xFF` (the bare call gives `sw v0` directly) (`func_150E9C9C`).
5. **Three vector sums computed before the subtracts** (`add.s f0/f2/f14` then `sub.s`): name them `x`, `y`, `z` and declare them between the two vectors (`f32 a[3]; f32 x, y, z; f32 d[3];` gives the 12-byte gap), and write the IDO-reversed operand order: `x = arg3[0] * arg4 + arg1[0]`, `d[0] = m * (x - a[0])` (`func_150D1714`).
6. **Flag temps of an `a | b | 0x9300` struct field cost 8 frame bytes when named**: reuse the rand temps declared for later (`if (arg4 == -1) b = 0; else b = 1; if (arg5) c = 0x400; else c = 0; s.u0 = c | b | ...;`) (`func_150E856C`, frame fixed, still DIFF56).
7. Two `sh` stores in the wrong order (`func_150C29F0`, s107 DIFF2): a same-line `do { ...; s.u5C = ..; s.u5E = ..; } while (0);` around the preceding statements (local permuter, fakematch; s106 recipe 4 again).
OPEN: `func_150B6314` perm DIFF8 (`func_151307F0` spawner, s92 struct at sp28 with `pad9A[0xA]`; only t-regs of the arg1/arg2 loads), `func_150E856C` perm DIFF56 (arg4/arg5 kept in a0/a1 in the ref), `func_150B87B0` SIZE-6 (loop, hoisted FPR constants).

## s119 recipes (init / libultra builds)
1. **`-mips3` C files** (64-bit `dsll`/`ld`/`sd` code such as ultralib `libc/ll.c`): per-object `MIPSBIT := -mips3 -32`, `OPT_FLAGS := -O1`, and an explicit Makefile rule placed *after* the generic `%.c.o` recipes (an explicit rule earlier in the Makefile becomes the default goal) that runs `$(PYTHON) tools/set_o32abi_bit.py $@` on the object. Then the object links with the `-mips2` ones (`init_eu_26B30`). Lo-slice candidates: the 64-bit rng in `game_DAE50` (`func_150ADA20`: `ld`/`dsll32`, = PD/GE `random()`), `game_eu_D2DB0`, `game_D51B0`.
2. **Rare's libultra fork**: GoldenEye `tools/goldeneye/src/libultrare` (compile with `tools/eu_port/gelu.sh`) differs from ultralib (`__osLeoInterrupt` has the `osDiskExist` check). Map its global names to the EU D_ names with `#define` at the top of the file.
3. **Shared `lui` for several fields of one global** (`osLeoDiskInit`): the ref compiled the global as defined in the file. A tentative definition `OSPiHandle D_80043E50;` (COMMON, resolved by the address in `undefined_syms_auto.txt`) gives it with no data emitted; `extern` gives one `lui` per store.
4. A **chained assignment** `a = b = p;` loads the address of the middle global into a register (`func_10003BD0`); separate statements use `lui at` per store.

## s121 recipes (n_audio / audio manager ports)
1. **Screen Rare references at `-g` too** (`rarescreen.sh`): Conker's `-g` n_audio files (init_1E530..init_22460) are DK64 `src/global_asm/audio` (DK64 builds them `-g`); at `-O1`/`-O2` they only scored 0.6-0.86.
2. **`while (1)` vs `for (;;)`** after a call in a function that never returns: `while (1)` left 7 zero words before the epilogue, `for (;;)` matched (`func_10009400`).
3. Register locals still **reserve stack slots in declaration order** (higher address first): position an address-taken struct by moving its declaration between register locals (`func_10009400`, `func_100095A0`).
4. Two `lui/addiu` of the **same address** = two different symbols in the original (rspboot end / aspMain start): use the second name and add it to `undefined_syms.eu.txt` (`func_100095A0`, `aspMainTextStart`).
5. Inline `alUnlink`/`alLink` as code with **block-scoped `ALLink *ln, *to`** gives the 8 extra frame bytes of libultra-style DMA list code (`func_100099BC`).

## s123 recipes (DK64 n_audio ports at -g)
1. **Port a whole Conker n_audio file from DK64 `src/global_asm/audio` at once**, `#define` the DK64 names to the Conker symbols, and define DK64 struct types locally (`RareSynth`, `RareAuxBus`, `CustomPVoice`, `RareSynConfig`) instead of including `n_libaudio.h` (it clashes with `functions.h`). Then fix only what the object diff shows: Conker's struct offsets (CustomPVoice +8 from 0x28; aux bus stride 0x44; ALSynConfig `outputRate` 0x2C) and frame pads (at `-g` every local has a slot: drop DK64 `pad` locals until the frame matches).
2. When the target's header prototype disagrees with the DK64 signature, rename the header's declaration away: `#define f f_proto` / `#include` / `#undef f` (`n_alFxNew`), rather than changing a shared prototype and every caller.
3. DK64 n_audio float literals are `.rodata` at `-g` even when lui-able: the Conker file must own its `.rodata`; a literal that lives in another object's rodata becomes an `extern f32` (`D_8002CAE8`).
4. Size off by a tail of zero words at the end of a file = file padding: split it as an unnamed `[addr, asm]` yaml segment (`0x229D0`).
5. Conker's envmixer changed DK64's code (pan bit 1, `0xFFFC` masks, `184U`): when ratio is ~0.97 and sizes differ, read the asm around the first real diff and rewrite that block; the rest stays verbatim.

## s125 recipes (DK64 n_audio ports, Conker changes)
1. **Conker N_PVoice = Conker's own `src/libultra/audio/n_synthInternals.h`** (extra `ALLink unk8` at 0x8, so every DK64 `dc_*`/`em_*` offset is +8): port DK64 n_load.c / n_env.c code with the real field names and `#include "n_synthInternals.h"` alone.
2. Conker's additions to DK64 audio code are mostly **early outs and guards**: a NULL table / bad book address -> `aClearBuffer` + return (`n_alAdpcmPull`), DMA result 0 -> reset flags + return, `seqp->state == 3` in the target check. When a 0.9x hit is 10-15 % longer, read the asm between the DK64 landmarks and add the block; the rest stays verbatim.
3. `K0_TO_PHYS(x)` in Conker's headers is not a mask: write `(u32)(x) & 0x1FFFFFFF` when the asm shows `and` with `0x1FFFFFFF`.
4. A `switch` whose `default:` jumps to a shared `return 0` block = `default: break;` + `return 0;` after the switch (an inner `if (...) {...}` in a case must not have its own `break`).
5. IDO `-g` linked-list walk `if (p) do {...} while (p)` = `while (p != NULL) { ...; p = p->next; }`; a `for` loop adds a jump to the bottom test.
6. Inlined `alLink` in `-O2` code that keeps `ln`/`to` in a/v registers with copies (`or a2,v1`) = block-scoped `ALLink *ln, *to` (also fixes 8 frame bytes, cf. s121 recipe 5); the plain macro form gives offset-folded stores.
## s127 recipes (IDO -g n_audio ports: dead code, shared loads, MIN/MAX)
1. **Dead code after an unconditional `b`** (`b L; nop; <compare or calls>; L:`) at `-g` = `if (1) { } else { ... }` (`__n_CSPHandleMIDIMsg`: `else if (chan == 2) {}`; `_n_handleEvent`: two debug prints). `if (0 && x)` / `if (1 || x)` are folded away by cfe and emit nothing.
2. `-g` loads a variable once **within one expression** and reloads it in the next statement: a `beq t7,4 / beq t7,8 / ...` chain on one register in source (unsorted) order is a single `if (a != 4 && a != 8 && ...)`; a `switch` sorts its compares and uses `s0` for a compare tree.
3. `vol = MAX(0, X - 1)` with `MAX(a,b) = a > b ? a : b` gives `bgtz X` -> recompute `X - 1` (the `0` store is laid out first); `X > 0 ? X - 1 : 0` lays out the other way and shares `X`. Use the DK64 macro form literally.
4. `-g` **register numbering** follows the operand order of the comparison: `D_8002BA30 >= D_8002BA2C->maxSounds` vs `D_8002BA2C->maxSounds <= D_8002BA30` changed every later t-register (68 = relocations only vs 236 diff words); try the reference's spelling before anything else (`varsub.sh`).
5. `-g` `while (p) {...; p = p->next;}` puts the store before the test; a `for (p = head; p != NULL; ) {...; p = p->next;}` gives the `beqz; sw` entry plus the reload at the bottom (`__n_CSPVoiceHandler` case 0x19).
6. A function ending in one `b <epilogue>; nop` with no `lw v0` is a non-void function without a `return` (`func_100155A0`); a `return x;` gives `b; lw v0` plus a second `b; nop`.
7. A table read as `lui hi(D_x); negu; sll 2; lw lo(D_x)` = `D_x[-i]` on a symbol placed `0x15C` words past the real table: declare the second symbol and index it with `-i` (`D_8002C310`, `__n_CSPHandleMIDIMsg`).
## s122 recipes (debugger loops, call-arg registers, strength-reduced index loops)
1. **A value sitting in `a1`/`a2` at a `jalr`/`jal` that the callee never seems to need is a call argument.** `func_151A9610`: the table index stays in `a1` through the bounds checks because the call is `D[i](arg0, i)`; with `fn(arg0)` IDO moved it to `v0` (DIFF9).
2. **One `||` chain vs separate early returns.** A param read from its home twice in a row of guards (`lh t1,0x22(sp)` then `lh t2,0x22(sp)`) means separate `if (...) return;` statements; the `||` chain CSEs the load (`func_16001390`, DIFF32 -> DIFF7).
3. **Loop-bottom t-register numbering**: moving the counter decrement out of the `for` header into a statement *before* the pointer step (`for (; y1 > 0;) { ...; y1--; fb += W - x1; }`) renumbered `t1,t9,t0` to the ref's `t9,t1,t2` (`func_16001390`). Try it before a permuter run when only the bottom block differs.
4. **Two s-registers holding the same stack address** (`move s5,t9; move s4,t9`, `t9 = sp+0x78`) = an index loop over a stack array that IDO strength-reduced (`for (i = 9; i >= 0; i--) q = n / pw.v[i]; ... if (i == 0)`), not a pointer loop (the pointer form CSEs `&pw` into one register and hoists it to the prologue). `func_16001044` (draft).
5. **A loop bound equal to a constant used inside the loop** (22 = `prefix == 0x16`) gets hoisted into an s-register with `s32 i`; the ref's `li at,22` each time came from **`u32 i`** (`func_1600078C`, SIZE+1 -> DIFF13).

## s124 recipes (gensome SIZE+-1 leads, struct copies, chained stores, rodata gaps)
1. **`lw at,0(x); sw at,0(y)` triples are struct copies** (`*a = *p` of a `{f32 x, y, z}`), not f32 field assignments (`lwc1/swc1`) (`func_15137C64`, SIZE-1 -> OK).
2. **Store order of one value into several fields**: try chained assignments in all orders (`a = b = c = arg;`); IDO's store sequence follows the chain. A generator over field-group order x chain order (72 variants, one `tryall`) found `func_1515F0F4`.
3. **Byte splits that skip a t-register** each (`t9 -> t1`, `t2 -> t4`) are `(x >> n) & 0xFF` stored to a `u8`, not `(u8)(x >> n)`.
4. **Loop-invariant hoisting**: if the ref computes products before a do-while and mine computes them inside, assign one of them to a named local before the loop (`k = inv * 10.0f;`); IDO then hoists the other invariants too (`func_151CE144`).
5. **Zero words in a file's `.rodata` between two C functions' literals** (seen with `rodiff.py` after a resplit: `32767, 32767, 0, 0, 0.071, ...`) = an object boundary: matching the later function needs a file split, not a padding trick. Check `rodata_inject.py <stem> --dry` and `rodiff.py` before trusting a single-object `check_files.py` (it passed before the resplit).

## s126 recipes (float ulp literals, comma mul.s order, unused-temp add.s order, file split choice)
1. **`[rodata contents differ]` on a lone `lwc1` = the literal is one ulp off**: print the ROM word with `struct.unpack('>f', ...)` and write the `repr` value (`0.19700001f`, not `0.197f`) (`func_151CE144`, DIFF1 -> OK).
2. **`mul.s` operand order, s48 comma trick**: `((0, d) * (inv * k)) * 255.0f` gave `mul.s f6, f12(d), f4(inv*k)` where the 7 plain orders and named temps could not (`func_151CE144`, fakematch).
3. **`add.s` operand order of `x = v + c*D` where `v` is a cached field**: drop the temp (`e->unkC += c * D;` and use `e->unkC` directly in the earlier product) instead of reordering the sum (`func_151CDC24`: 6 operand orders DIFF2..21, no-temp form OK). The loop counter that m2c typed `s8` was `s32` in the source (no `sll/sra 24`).
4. **Two f32 spills in the wrong slots** (`swc1 f0, 0x28` vs `0x20`): sweep the declaration order of all locals (24 permutations, one `tryall`); 2 of 24 matched (`func_151DB97C`). Check the global's type before reading the m2c float arithmetic (`D_800BE9E4` is `s32`: `multu`).
5. **Ambiguous file split point**: when `file_split.py --dry` lists several 16-aligned candidates with no rodata/data evidence between them (`game_eu_18B1C0`: F170, F1B0, F7E0, FDC0), split at the function whose rodata proves it is in the second object (`--at func_1515FDC0 --rodata 0x24BB90`). After the split, fix `build/hand/screen.txt` paths (repair_try records the old file) before `apply.py`.
6. **`rodata_split.py --own` refuses on a `lbux` data table after the late items** (`game_eu_17A800`: byte tables at 0x24B4C4-0x24B558 that two asm functions index): give the file an explicit range ending at the last late item's 16-aligned end (`rodata_split.py game_eu_17A800 0x24AF00 0x24B4C0 --section .rodata --resplit`); the tables stay in `rodatabin`. Enough for a C switch's jump table (`func_1514EF8C`).

## s128 recipes (5-arg callees, `ori` flags, unfilled delay slots, strength-reduced search loops)
1. **A constant loaded at the very top into `a2`/`a3`** (`addiu a2, zero, 4` before any branch) and `a0` untouched until a late `jal` = the callee takes the function's own pointer as arg0 and the constant is a later argument: `func_1513F680(arg0, arg0[0x70], 4, ...)`, not `(arg0[0x70], 4, ...)` (`func_1514A8F0`, SIZE-1 -> OK).
2. **`ori tN, zero, 1` for a byte flag** = IDO folding `0 | 1`: `p[k] = 0; if (cond) p[k] |= 1;` (`= 1`, `1U`, `(u8)1`, `+= 1`, `^= 1` all give `addiu`) (`func_15159140`).
3. **`swc1; b L; nop` where IDO would put the store in the delay slot**: a label after the store (`dummy: ;`, fakematch) blocks the fill (permuter find, `func_151415D4`).
4. **A search loop whose element pointer is set up inside the `blez` guard** (`lw a0, base` after the zero-trip check, then `addiu a0, 0x18`) is an indexed access `arr[i].f` that IDO strength-reduces; an explicit pointer walk initialised in the `for` header hoists the load above the guard (`func_151AE86C`, SIZE-3 -> SIZE-1).
5. **`multu` operand order** follows the source product order: swap `a * b` to `b * a` when only the `multu` registers differ (`func_1519CA54`).
## s132 recipes (-g Acmd builders, -g compare order, else-if tails, -O3 screening)
1. **`-g` display/Acmd lists with one stack slot per command** (`lw t,0(a1); sw t,0x54(sp); lw; addiu 8; sw`, slots descending 0x54, 0x50, ...): each command is its own block with `Acmd *_a = (*cmdp)++;` (what the libaudio `a*` macros expand to). A local `#define CMD(p, a, b) { Acmd *_a = (p)++; _a->words.w0 = (a); _a->words.w1 = (b); }` reproduces it (`func_151F2E88`).
2. **`-g` register numbering shows the evaluation order of a compare**: ref `count -> t9, glob -> t0, sum -> t1, other -> t2` for `slt at, t2, t1` came from `(count + D_800E1220) > D_800E121C`, not `D_800E121C < count + D_800E1220`. Likewise `slt at, t4, t7` with `t7` loaded first = `t7_var > t4_var`.
3. **`-g` dead branches after a `return` mark the if/else structure**: `return 0; b <join>` = an `else` follows; a `b` to the very next instruction = an empty `else {}`; a block ending with `b L; nop` where `L: b end; addiu v0, 1` = `if (A) {...} else if (B) {...; return 0;} else { return 0; } return 1;`. Doubling written `x + x` gives `addu t,t,t` (`x * 2` gives `sll`).
4. `refcc.sh` builds `-O3` since s132 (`-Idir` without a space; with `-O3` `uld` read a separate missing include dir as an input file). Ultralib flags: `-nostdinc -D_FINALROM -DNDEBUG -I /conker/tools/ultralib/include -I .../include/compiler/ido -I .../include/PR -I .../src`.
5. **Hoisting a float constant out of a loop needs a literal**: an extern rodata float (`D_800A8EBC`) is reloaded inside a loop with byte stores, a `2500.0f` literal (file owns `.rodata`) is hoisted like the ref (`func_15198D3C`).
## s130 recipes (game copies of libultra, offset-disambiguated floats, Gfx param, trail updaters)
1. **A "libultra/audio" game file can start with a different libultra object**: `game_21FC90` began with a copy of `io/crc.c` (pre-J, same source as `init_eu_26370.c`) at **`-O1`** (all locals on the stack, but loads scheduled across statements = not `-g`). Split it off by hand (yaml + a Makefile `OPT_FLAGS` line) and keep the `func_` names (`func_151F27E0`).
2. **IDO disambiguates float fields by constant offset from the same base**: `p[0x140] *= p[0x15C]; ... p[0x148] *= p[0x15C];` loads `p[0x15C]` once. m2c temps for such loads are not source; write the plain expressions (`func_15198024`, DIFF52 -> OK).
3. **A read placed later than m2c shows**: if only the registers of a hoisted load differ (`lh t1` vs `t0`), move the read down past the next independent statements (`life = t->unk1E;` after `pos.y +=`, `func_1519D7B0`).
4. **Display-list builders that keep `or v0,a0; addiu a0,8` per command** take the `Gfx *` as the parameter and increment it in place; a local `Gfx *g = (Gfx *)arg0` folds into constant offsets. Colour params without `sw` homes are `s32`, not `u8` (`func_1517F5FC`; update the callers' prototypes and re-check them).
5. **`func_151423D8(u8)` (sin) args computed into a0 and then `andi t, a0, 0xFF; move a0, t`**: pass the int expression without `& 0xFF` (`func_1513384C`).
## s129 recipes (n_audio controller handlers, -O2 frames of register locals)
1. **At `-O2` every declared local gets a stack slot in declaration order (top down), even one that lives only in a register.** A frame where the spilled/aggregate locals sit 4 bytes off with unused words between them (`func_10012020`: unused 0x6C and 0x64 around `master` at 0x68) means register locals (`mode`, `i`) are declared between them: `s32 mode; f32 master; s32 i; F2 vol; F2 freq; f32 scale;` fixed every sp offset at once. Adding `pad` locals instead only grows the frame. The same holds for block-scoped temps: a new `u8 *seq` anywhere moved the compiler spill slots by 4 (`func_10008CE8`).
2. Conker's MIDI controller handlers (`init_19B50`, `D_8002BDA0` table) are the DK64 `__n_CSPHandleMIDIMsg` controller **cases** turned into functions `(seqp, event, chan, byte2)`: `func_1001A030` = the `AL_MIDI_SUSTAIN_CTRL` case verbatim (with `u32 byte2` for the `sltiu 0x40`), so srcmatch never finds them. Port the case body from DK64 n_csplayer.c.
3. `-g` `a == b` of two byte fields loads the right operand first: the ref `lbu t6,0xD; lbu t1,0xE` came from `x.unkE == x.unkD` (`func_1001A508`, DIFF2 -> OK).
4. `abs.s` needs `float fabsf(float); #pragma intrinsic (fabsf)` in files that do not include `functions.h` (n_audio files include only `n_libaudio.h`).
5. `-O2` float lerps `cur + (target - cur) * k` vs `(target - cur) * k + cur`: IDO keeps the source order of `add.s` operands only when `cur` was loaded before the product; after a `sinf` call the operands come out swapped, so write `cur + diff` there (`func_10012020`: 5 of 6 lerps).
6. A local aggregate initialised from `.data` (`lw/sw` pairs from `D_8002BD60`) can be written as `vol = *(F2 *)&D_8002BD60;` when the header declares the symbol with another type.
7. **A pointer loaded into `v0` and copied to `a0` in the `jal` delay slot** (`lw v0,0(s0); beqz v0; nop; jal f; or a0,v0`) where mine loads straight into `a0` = the call argument is the pointer **converted to an int** (`f((s32)p[i])`, callee `void f(s32)`); a local temp instead moves every spill slot (recipe 1). `func_10008CE8`: DIFF ~12 v0/v1 words -> OK.
## s131 recipes (init_EB00 sound callbacks, unrolled search loops)
1. **A block-scoped pointer inside a loop body** (`for (...) { u8 *obj = (u8 *)&D_800DBFF0[i]; ... }`) fixed the last scheduling diff (`addiu a0,a0,0x9A0` moved into the loop's delay slot) where a function-scope `obj` did not (`func_10011BB8`, found by the permuter).
2. `sfx->unk0 = *arg6 = x >> 16;` and `*arg6 = x >> 16; sfx->unk0 = *arg6;` number the t-registers differently (`func_1000ECCC`: the two-statement form matched; its sibling `func_1000EDA0` uses the chained one).
3. A call argument computed **before** other argument loads and the branch that follows (`lw v0,0x184(s0); srl; andi` before `lbu D_80041FD9`) = the value assigned to a local before the call. At `-O2` a new local can add frame bytes: reuse an existing local (`fn`) as the permuter did (`func_10010154`).
4. IDO `-O2` unrolls a simple `for` loop x4 (`andi n,3` remainder loop + main loop) only when the body is small enough: recomputing `dx*dx+dy*dy+dz*dz` in the branches (as m2c shows) gave x2 unrolling; storing it once in `d` and reusing `d` gave the x4 shape. A walking pointer `p++` instead of `pts[i]` gave the target's pointer induction (`func_1000A750`).
## s133 recipes (init_B1B0 / init_EB00 small handlers)
1. **`(x & 1) == 1` vs `x % 2 == 1`**: with `(arg0 & 1) == 1` IDO kept the constant 1 in `v0` and reused it for a later `D = 1;` store; the target compared with `li at,1` (`andi; li at,1; bne`). `u32 arg0` + `arg0 % 2 == 1` matched (`func_1000E7A0`).
2. **An `if (f) x = A; else x = B;` with no initialiser** gives `beqz; or; b L; li x,A` (a branch around an empty else); `x = B; if (f) x = A;` gives no `b` (`func_1000C934`).
3. **Argument kept in its stack home** (`sw a1,0x3C(sp)` at entry, `lw tN,0x3C(sp)` at each use) while mine keeps it in `a1`: take its address once, `if ((&arg1)[0] != NULL)` (fakematch, `func_1000B3D4`).
4. Array-of-struct accesses written as `((T *)base)[i].f` (no pointer local) matched where `T *s = &base[i]` gave register diffs (`func_1000FC18`); for a 357-insn loop the same form produced the target's two induction variables (`i*0x30` in `fp` and the element address in `s0`), a pointer local merged them (`func_10011624` draft).
5. Block-scoped temp again: `if (arg2 >= 2) { s32 d = ...; }` fixed a tail store/branch layout DIFF12 (`func_1000DF68`, permuter). A two-statement `v &= 0xFF00; v = max - v;` fixed a register-only DIFF18 (`func_1000C934`, permuter).

## s134 recipes (pointer-typed args, base pointer kept in an s-reg, homed args)
1. **`multu x, K; sll t, 1; addu t, arg` after `K` was folded nowhere else** = pointer arithmetic on a `u16 *` arg: `(s32)(arg1 + idx * 640)`. Writing `idx * 640 * 2 + arg1` folds to one `1280` constant (`func_1517DC00`, SIZE+2 -> OK).
2. **A base pointer `p = arg0 + K` held in its own s-reg (`addiu s0, s1, K` after the first call) while early accesses use `arg0 + K + off`**: write *every* access of that region through `p` (`p[4] += ...`), not `arg0[0xAC]`; mixing makes IDO fold `p` and drop an s-reg (`func_1515A68C`).
3. **A pointer arg reloaded from its stack home before every use, even twice inside one `a || b`**: declare the parameter `u8 *volatile arg1`; a byte arg homed (`sw a2`) and reloaded once for a late call = `(&arg2)[0]` at that call (`func_15191EF0`, size right, still DIFF31).
4. Unused declared locals still take a frame slot at -O2 (s129 recipe 1): an unused `e` pointer moved the only spilled local from 0x4C to 0x48 (`func_1517DC00`).


## s136 recipes (stack-arg types, s16 params, byte temps)
1. **The types of a many-arg function's parameters can be read from how each stack arg is reloaded**: `lbu off+3(sp)` = u8, `lh off+2` = s16, `lhu off+2` = u16, `lw off` = s32 (arg i is at `frame + 4*i`). A wrong local prototype in the same file must be replaced, and matched callers rechecked: `(s32) arg` casts passed into a now-`s16` slot add `sll/sra` (`func_1516DF0C`, `func_1516FFF8`).
2. **`sll a0,16; sra` at entry into s-regs with no `sw a0` home** = the parameter is declared `s32` and passed to an `s16` prototype parameter inside a loop. If it is declared `s16`, IDO homes it and reloads it with `lh` (`func_15170F24`).
3. **The ref loads a later statement's source before an earlier store** (`lbu t9; sh v1; sb v1; sb t9`): the later statement was written first in the source. Swap the two statements; the stores keep their order (`func_1516DF0C`).
4. **A table byte compared in `v0` instead of a t-reg**: assign it to a `u8` local first (`u8 t = D[i * 0x32C]; if (t == 0x3A)`) (`func_1516F2D8`).
5. A switch whose jump table starts below its lowest real case: the low case shares the default body (`case 9: default:`). Empty cases (`return`) are separate table targets (`func_151CA150`).

## s138 recipes (fade updaters, spawner struct copies, K&R arg registers)
1. **A byte field updated with `slti 255` / `bgez` compares** (fade in/out: `v = p[0x1F]; v += D << 6; if (v >= 0xFF) v = 0xFE;`): the working variable is `s32`, not the `u8` m2c gives (`func_1516F21C`, `func_151702C0`).
2. **Two values in `a0`/`a1` right before a call that takes no arguments**: the source passes them anyway through a K&R declaration (`s32 f(); f(hi, lo)`); m2c's extra call args are a hint, not noise (`func_15170D50`).
3. **m2c spawner drafts with dozens of `spXX` locals and a `memcpy(ret + 0x70, &spB, 0x58)`**: rebuild them as two local structs (template at `&spA`, the 0x58 block at `&spB`); separate locals lose all their stores (SIZE-60..-120). `s138_drafts/spstruct.py` does it (`func_151CB128`).
4. A `u8` param whose word home is reloaded with `andi 0xFF` at entry: declare it `u8` and drop m2c's `& 0xFF` uses.

## s140 recipes (byte-store temps, FP compare order, parked-near-miss permuting)
1. **Two byte stores of one shifted value with the low-byte temp in the wrong t-reg** (`sra t0; sra t9,t0; sb t9; sb t0`, mine t8): `p[k+1] = v & 0xFFFFu;` (fakematch) moves it (`func_1516FE5C`/`FE8C`). Both had to be `void` in the file prototypes first.
2. **`add.s` operands of an FP compare in the wrong order** (`lo + x < dist`): the comma form `(lo + x) < (0, dist)` (permuter) flips them; source operand order alone is canonicalised (`func_151D91B0`). Declaring `f32 *p` before `f32 d[3]` moved the array 4 lower to the ref slot.
3. **A search-loop flag** (`while (!found && i < n)`) that the ref keeps with `andi 0xFF`: declare it `u8` (`func_15143E94`).
4. **Remote permuter on old parked near misses pays**: s139 4/6, s140 4/20 (all DIFF <= 7 starts). Screen all saved drafts at once with `ljsweep.py` (`s140_drafts/collect.py` + `rank.py`), permute the best per function.


## s142 recipes (comma operand order, struct-typed FP access)
1. **Commutative FP op with its operands in the wrong `fs`/`ft` order** (`mul.s f14, f8, f0` vs mine `f0, f8`): source order is canonicalised, but **`x * (0, s)`** puts `s` in `fs`; also fixes the f-register pair (`1.0f - (arg1[5] * (0, dist - lo))`, `func_151D91B0`; `F(0x10) * (0, s)`, `func_1513384C`). Screen all 4 forms (`(0,a)*b`, `a*(0,b)`, ...) per op with tryall; label fakematch.
2. **A call result multiplied by a product** with the product loaded after the call: `s = call(); s = (B * A) * s;` gives the ref load/operand order (`func_1513384C`).
3. **FP register pairs alternating the wrong way (f4/f6, f6/f4) all through a function that uses `p = arg0 + K` with `*(f32 *)(p + n)` casts**: rewrite with a **struct pointer** (`Sub *v = (Sub *)(arg0 + 0x70); v->unk18`). The casts cost DIFF8 / DIFF27; the struct form matched first try (`func_151CD7D4`, `func_151CBF20` game_eu_1F7960).
4. `(a + (*p >> 6)) - K` vs `((*p >> 6) + a) - K` changes the t-register numbering (DIFF12 -> OK, `func_1517BC58`).
5. Chained byte stores `p[6] = (p[0] = v)` store `[0]` first; write `p[0] = (p[6] = v)` for `sb 6; sb 0` (`func_15187EC0`).

## s144 recipes (unrolled 4-loops, frame from array size, struct copies)
1. **Four identical clamp blocks on consecutive globals with unfilled `beqz; nop` delay slots** (and the address of a shared global rebuilt with `lui/addiu` in the first two copies only) are a **fully unrolled constant-4 loop**: `for (i = 0; i < 4; i++) if ((&D)[i] < 0xFF) { v = (&D)[i] + G; if (v >= 0x100) v = 0xFF; (&D)[i] = v; }` matched first try (`func_1516D970`); `for`, `do-while`, `p[i]` all give the same code.
2. **A local array at the wrong offset with the frame otherwise right** (`sp4C` at 0x44 vs 0x4C): enlarge the *lower* array (`s32 sp28[7]` -> `[9]`) and drop the permuter's slot-holding temps (`new_var` float, `u8 **q = &arg0`), which then fit (`func_151479E8`).
3. **`lw/sw` (not `lwc1/swc1`) word copies of three floats** are a struct assignment `*prev = *cur` of a `{f32 x, y, z;}` vector; the `lwc1` stores that follow are field-by-field assignments (`func_1515C518`). For spawners whose `memcpy` size is larger than the visible fields, add trailing fields until `sizeof(b)` matches the `li a2` (`func_151B68D0`: 0x28 -> 0x2C), then a `s32 pad;` between the two struct locals and a trailing pad word in struct A to fix the frame.
4. s142 recipe 1 also works for integer `multu`: `t = p[2] * (0, arg0->x38)` turned the permuter's DIFF1 into OK (`func_151A7E2C`), and the permuter fakes it needed (`unsigned long long` index, `new_var = 0x42`) could then be dropped.
