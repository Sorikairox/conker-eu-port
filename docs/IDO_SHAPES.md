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
12. **Unfilled delay slot / `store; jr ra; nop` in 2-case u8 handlers (shape D)**: OPEN (`func_151AEBF0` + 6, ~176 functions). Everything matches once the loaded value is a single shared
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
