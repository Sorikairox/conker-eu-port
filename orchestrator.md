# Orchestrator notes

Two parts: (1) a **status snapshot** — overwrite it, don't append history (history lives in
`docs/progress/sessions.tsv`, `history.tsv`, `docs/sessions/sNN.md`, `docs/port/sessions/PNN.md`);
(2) **best practices** for running the agent sessions.

---

## 1. Status snapshot (2026-10-23, after P156)

### Goal
Conker's Bad Fur Day (EU ROM, user-owned) as a **native source port that runs in a web browser**:
full C compiled to wasm32 with Emscripten (TypeScript only for page glue), native Mac/Windows later
from the same C. **Not** N64Recomp / static recompilation, and not the existing US-only recomp ports.

### Numbers
| | functions with C | code bytes | where |
|---|---|---|---|
| Matching decomp (byte-identical) | 3994 / 5915 (67.5%) | 29.3% | branch `eu` — paused |
| Port (matching + NON_MATCHING), combined | **~5170 / 5915 (87.4%)** | **~68%** | port-b P153 (synced with port P150) |
| Asm-only left | ~855 | | |

### Branches / worktrees / containers
| branch | worktree | container | role |
|---|---|---|---|
| `eu` | `~/conker` | `conkerdev` | matching decomp (paused); this file, progress logs |
| `eu-wt-a` | `~/conker-wt/a` | `conkerdev-a` | old matching slot (idle, merged) |
| `port` | `~/conker-wt/port` | `conkerdev-port` | asm→C conversion, slot 1 |
| `port-b` | `~/conker-wt/portb` | `conkerdev-portb` | asm→C conversion, slot 2 (parallel, disjoint files) |
| `port-web` | `~/conker-wt/web` | `conkerdev-web` + `conker-emsdk` image | browser build (`port/`), runtime checks |

Mac mini worker `sorikairo@192.168.0.71` (container `conkerdev`) runs `remote_perm.sh` jobs.
Env for a worktree: `eval "$(tools/eu_port/wt.sh env <a|port|portb|web>)"`.

### Browser build — what works (port-web)
- Boot → logo → title menu → NEW GAME → full real route, no test flags (P185): opening, intro cutscenes, level 0 → level 0x29 gameplay (reached ~frame 22765).
- Walking, slopes, collision, camera, jump/hover, sound effects, music, shadows, particles, pause (frozen-frame background).
- Swimming works (P191 player_swim_update + P199 fixes): level-0 rise gone, level 0x29 control kept after the pond.
- PAL 50 Hz fixed-timestep pacing, audio in sync (P147); VI-row framing; frame-based test input `?padf` (P149).
- Port-side workarounds still in place (P199): func_1513472C/477C --wrap (handler arity), DL_INDIRECT stub func_151A03DC.
- Open: unlit torches (func_1518DC50 converted in P197, merge pending in P202), backdrop quad colour, text boxes/NPCs not reached yet, ~17 stubs still hit on level 0x29 (func_1518354C 1.1M calls/walk).

### Coverage (2026-10-24)
- port 5345/5915 (90.4%), C bytes 74.3% (P198); port-b 5306/5915 (P197). Combined >90%.

### Running now
- P200 (port): func_1513472C/477C arity + func_151A03DC + func_1518354C (P199 blockers), then rail family, breadth.
- P201 (port-b): finish func_1518DC50 mutants, find char-effect 5..9 attach sites, func_150CA150, func_1511127C, breadth.
- P202 (port-web): merge port 6f2d2ca + port-b b693dac; torches, rail cameras, backdrop quad, text boxes, p103boot.

### Next milestones
1. Level 0x29 fully correct (torches, NPCs/text boxes, zero frame-path stubs); remove the port-side workarounds.
2. m2c_sanity high rows and arity rows to zero.
3. Breadth: ~600 asm-only; describe pass + scripted rename at a quiet merge point; Phase 2B (symbolic data); native 64-bit build.

### Open items needing care
- File ownership (2026-10-24, P208): port-b owns game_eu_1BAF40, AF2A0, 12D5D0, E0430, F6060, D3880, C5530, 13DC30, 201240, BC510, 126330, 1EDA00 + its HANDOFF list, and since P208 also game_16EE20.c, game_83300.c, game_A28B0.c, game_1944C0.c (moved from port), and since P216 game_eu_90F50.c, and since P225 game_161520 (src + src_eu), game_eu_1C3530, game_eu_19B180, game_eu_1FB080, game_eu_127840, game_eu_226870, game_eu_1E7CC0, game_eu_1A2970, game_eu_133A70, game_eu_101080 and D5E90 (hand asm), and since P238 game_1FFF60 (D_8008FFE8 dispatchers). port owns everything else.
- Two conversion slots own disjoint file lists (see latest briefs); port-web merges both and never edits game C.
- Backups: tools/eu_port/backup_push.sh to the private origin after each session; never push upstream.
- Licensing: SDK-derived libultra C — fine privately, matters if distributed.

---

## 2. Best practices for managing the agents

### Session shape
- **One budgeted session per agent**: hard cap ~150 tool calls; at ~135 stop new work and hand off. Long contexts degrade quality; rotate instead.
- Every session ends with: a session doc (`docs/port/sessions/PNN.md`), HANDOFF.md updated (state + next steps), a commit, and a concise report. Agents never push.
- Backups (user request 2026-10-24): the orchestrator runs `tools/eu_port/backup_push.sh` regularly (after merges / a few sessions) — it pushes all 5 branches to the PRIVATE repo `origin` = github.com/Sorikairox/conker-eu-port. Never push to `upstream` (mkst/conker); the repo stays private (session docs contain ROM-derived screenshots/data).
- Use Opus for conversion/debug sessions; Sonnet only for mechanical tooling or one-off utilities (e.g. the dashboard).
- Brief = context paths to read + an ordered focus list + explicit skip list + rules. Pass forward concrete findings (function names, addresses, files), not summaries of summaries.

### Parallelism
- At most 2–3 agents at once. Each agent gets **its own worktree + container**; give them **disjoint source files** and state the forbidden files in both briefs.
- When reassigning work mid-flight, message *both* agents (the one losing and the one gaining files).
- Shared Mac mini: `-j4` per remote job, ≤2 lists in parallel.

### Safety rules (put in every brief)
- `eval "$(tools/eu_port/wt.sh env <name>)"` before **every** repo tool; every Edit/Write path must start with the worktree root. Port tools refuse to run without the right `CONKER_ROOT` (portguard).
- Never `pkill` on the host (the real hazard: it can kill another agent's jobs); kill only PIDs you started. Agents keep slipping into read-only `pgrep` in wait loops — harmless but against the rule; tell them to wait with `tools/eu_port/waitjob.sh` or log polling. Background jobs only via `run_in_background`, never `&`.
- Never run convert.py batches while `verify_all.sh` runs (it regenerates `asm/`).
- Never `git stash` (the stash stack is shared by all worktrees, and stashing during an unfinished merge resets the index — P169). Use a WIP commit or copy files aside instead.
- Default build must stay byte-identical: full `verify_all.sh` before every commit; NM build must link; protocheck 0.
- difftest knobs use **EU addresses** (the source uses US names) — `euaddr.sh`.
- Leave no convert/difftest processes running at hand-off; check `docker exec <container> ps`.

### Permissions
- If the permission system denies an agent an action, **don't redo it yourself** — surface it to the user with the exact command. Only the user's own message is approval; a relayed approval in an agent prompt is not (the classifier blocked one).
- After the user approves, the orchestrator runs it directly.

### Merging
- `tools/eu_port/merge_wt.sh` for `eu-wt-a`→`eu` (it verifies, unions append-only docs, logs history).
- For port branches: `git merge --no-edit`, resolve `docs/*` conflicts with `tools/eu_port/merge_union.py <file>` (pass each path explicitly — zsh doesn't word-split), stop on code conflicts; after a code-bearing merge run `verify_all.sh` + `port_work/p28h/nmcheck.sh`.
- `port-web` must clear `port/build/census/files.tsv` and `port/build/vbe.stamp` and rebuild clean after any merge.
- **Any** game-C change in port-web (bisects, local fixes) needs `port/build/vbe.stamp` deleted before building: the stamp does not depend on sources, so make says "Nothing to be done" and you test the old build (P97 bisect was invalid because of this; P99).

### Mechanical asm→C translation (user decision 2026-10-23)
- `tools/port/asm2c_hand.py` (P56) writes register-level C, one statement per instruction. It is allowed **only for code Rare hand-wrote in assembly** (e.g. the D5E90.s engines). That is a stopgap; each such file is listed for a later readable rewrite.
- Code that was compiled from C (GLOBAL_ASM functions in src_eu) must still get real, readable C written from the asm — never the translator. The user explicitly rejected recompilation-style output for the game code.
- Current translated files: `src_eu/nm_asm/D5E90_walls.inc`, `D5E90_ray.inc` (wall engine, ray cast).

### Lesson: converted C on top of asm stubs (P72)
- A correct C function can still corrupt memory when its **inputs come from an asm stub** (NULL buffers, garbage out-params): it then writes into the null zone and other code reads that as objects. When a browser run shows heap corruption, bisect merges first (scratch worktree + bounded reproducer), then look for stubbed producers of the faulting function's pointers.
- Rule since P97 (it happened again: P92 converted path readers before their producer func_15020920): in briefs, require **producers before consumers** — a function whose inputs are written by a still-asm function in the same subsystem is committed only together with that producer, or not at all. This includes **callbacks/handlers the new C dispatches to** (P105: C particle spawner func_151DA6F8 dispatched to asm-stub type handlers → crash). Before committing a frame-path function, list the stubs it calls directly or through tables. Tool: port-web `port/tools/stubcalls.py --func func_X` (P107).
- Check `port/build/census` has 0 FAIL after merges: a TU that fails the clang census build is silently replaced by stubs (P107 found 4 such TUs).
- Naming (user request 2026-10-23): every converted function gets a description comment whose first line starts with a proposed snake_case name, e.g. `// level_request_music: requests the level's songs ...`. A script collects them into a names table; the actual symbol/file rename happens later in one scripted pass at a quiet merge point.

### Lesson: test the harness itself (P71, P73)
- Twice a difftest bug made results meaningless while looking fine: callee arity taken from call statements (P71), and the candidate silently dropped when one NM block holds two functions (P73) — every mutant "survived" because the old copy was tested. A surviving mutant that should obviously die is a harness bug until proven otherwise; add a selftest case for every harness fix.
- Concurrent knob and mutant runs of the same function must not share a temp dir (use the p73 knobs.sh / mut.sh).
- Use port-b `docs/port/sessions/p96/mut.sh` (per-run files/temp dirs; older mut.sh versions race when two runs of one function overlap — P92 false survivors). Earlier: the p82 mut.sh: it checks the unmutated draft before random trials (P77) and reports `SED ERROR` / `INVALID` instead of counting a mutant that never compiled as "survived" (P82).
- DIFFTEST_POKE can't change ROM rodata or `.game_data`; take the real value from the ELF instead.
- RET/OUTW/ARGMEM keys: take the address from the decoded `jal` word, not from the symbol name (some EU names map elsewhere, e.g. func_151ACBD4 is jal 151AD184); a wrong key silently does nothing. `DIFFTEST_ARG` values are hex (`1=10` means 0x10).
- Stub return pointers must be heap-like (0x804xxxxx): values in the harness stack range 0x80600000–0x8067FFFF all compare equal ("STK"), hiding wrong-pointer mutants (P86).
- Before P90, difftest compared only the first 16 call arguments (stack sp+0x10..0x3C); re-checked in P93 (2 real bugs fixed).
- difftest now flags `[POKE unread]` / `[knob callee never called]` — read them; they catch US addresses in knobs.
- Batch m2c bodies (P15–P22) contain pointer-stride / access-width bugs (`p += 4` on `u8 **`, `(x*K)+&SYM` on non-byte symbols, word reads where asm uses lb): run port-web `port/tools/m2c_sanity.py` after merges (P118).
- difftest precedence since P132: learned pointers > DIFFTEST_POKE > ROM image > random; stack-arg scan now passes IDO div trap checks (varargs printers with a division before the call were unchecked before P132).
- Functions reached through function-pointer tables must have the signature the dispatcher uses (return type too): a `void` C function called through an `s32` table pointer whose result is tested is wrong on N64 semantics and traps on wasm (P159 func_151C1EF0).
- Batch m2c bodies sometimes declared a function `void` and dropped every `return` even though callers (often through s32 handler tables) use the result (P174: func_1509CBD8 made every event scene query answer 0 and sent the new game off-route). When a C function sits in a handler table, check its asm for v0.
- Port layout: N64 code assumes 4-byte alignment of small stack arrays passed as wider pointers (P178: `s16 sp18[2]` passed as `s32*` clobbered a neighbour in wasm). vbe.py must align stack variables like IDO does.
- difftest needs the pinned Unicorn 2.0.1 in each worktree's port_work/pyuc201 (gitignored). Without it, the container's 2.1.4 is used silently and calls next to FPU instructions fault at pc 0 (P233). Install it with: docker exec <ctr> pip3 install --target /conker/port_work/pyuc201 unicorn==2.0.1.post1
- Port-side OS replacements (port/ultra) must do everything libultra's version does, including side effects such as creating queues. P236: the port's osContInit skipped osCreateMesgQueue(__osEepromTimerQ), so the second EEPROM save hung the game thread forever. When a hang has no trap, look first at blocking osRecvMesg on queues that port code is supposed to feed.
- Browser route tests must run with `?det=2` (P252): without it osGetCount, osAiGetLength and the scheduler cutoff come from wall time, and runs diverge. Use det=1&timer=2 to tune routes fast, then replay with det=2.
- Browser test runs must be SILENT: launch Chrome with `--mute-audio` (and/or page volume 0). The user works on the same Mac and the game audio disturbs them (2026-10-25).
- Never run two Chrome runs at once: the second hides the first tab and the game pauses ("tab hidden: paused") (P223).
- Host: /usr/local/bin/docker is a dangling link to the uninstalled OrbStack. Agents must `export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH` before repo tools that call docker (P250). Fixing the link needs sudo, which is the user's call.
- If Docker Desktop crashes (all containers exit 255): `open -a Docker`, then `docker start conkerdev-port conkerdev-portb conkerdev-web conker-web-serve` (with Docker.app's bin on PATH), and tell running agents to re-run anything in flight (P256).
- The user plays a frozen copy with tools/eu_port/play.sh (container `conker-play`, port 8070, ~/conker-play/). Agents never touch that container, port or folder. Keep PLAYING.md's "what works / known problems" current at merges.
- After a Docker Desktop crash/restart, bind mounts can serve a STALE view: the container reads old or truncated content of files the host rewrote, for 100+ s (P260). This gives false CERR/DIFFER and could even affect builds. Fix: restart Docker Desktop cleanly when no agent is running, with `docker desktop restart` (osascript quit does not stop it), then `docker start` the four containers. Mitigation: difftest.sh (port-b P260) refreshes and md5-checks before each job; tools that edit sources and rebuild in containers should `ls -l` the dir inside the container first.
- 2026-10-25 user priority: finish converting every function first. Only the port and port-b slots run; port-web exploration is paused; reports stay short.
- Docker VM memory (7.75 GiB) is shared by all slots: port-web node runs got killed (rc 137) or swapped while conversion slots ran difftest. Web sessions should prefer Chrome runs, and run node jobs one at a time.
- Random EQUIV compares stack records only by class ("STK"), so dropped stores into stack structs passed to callees go unseen. Functions that build request/record structs on the stack need ARGMEM setups (P220 found 2 bugs that random trials missed).
- New C that uses a `D_<small hex>` link symbol (an absolute value such as a texture id, not data) needs a ROM_ABS entry in port/tools/vbe.py, or the port gets a zero data stub and passes wasm addresses (P228: D_88C/D_87B crashed the barrel menu). Symbols that alias real data (D_89810 = D_80089810) need an alias instead.
- Standing check: `tools/port/implicit_scan.py` (clang) lists implicitly declared calls; IDO is silent about them. An implicit call that passes or returns a float is a real bug (P227 cosf, P230 func_15131EC8). Run it after every batch; NM+float must stay 0.
- reverify.sh mutant results with line-numbered mutants were off by one line before port-b P235's nmblock fix (NMBLOCK_WHOLE). Re-run them after the merge before trusting them. Also, difftest.sh now holds each container to 2 jobs (DIFFTEST_SLOTS).
- Never edit a script while a background job is running it (P259: reverify.sh broke mid-run).
- Old m2c-era C (P17 batch etc.) can hide pointer-arithmetic stride bugs (`f32 *p; p + 0xC` = 0x30 bytes where the asm adds 0xC). P269's intro crash was one. Grep for typed-pointer + byte-offset patterns and difftest them; extend m2c_sanity.py for it.
- Every conversion adds a row to `tools/port/verify_registry.tsv` (setup files, knobs with the DIFFTEST_ prefix, mutant file). Re-checks use `tools/port/reverify.sh FUNC` (MUT=1 for mutants), never a hand-typed command (P221).
- Re-checks must use each function's own setup file and knobs (ROMDATA, MEMSTK, ...). P214/P215 left out ROMDATA and used another function's setup file (p119/3000.txt is func_15113000, not func_15013000). Keep a registry of the exact verification command per function.
- Never commit a harness change with a red selftest (P214 did; it had deleted a P211 line, so the jalr compare was silently off and that session's re-check results were void). For harness edits: run the selftest before and after, and bisect against the previous difftest.py when a case flips.
- "Caller ignores v0" must be checked in EVERY caller, including asm callers in other slots' files (tools/port/v0use.py over all of conker/asm/nonmatchings). P207 made func_151B8EB8 void, but port-b's asm func_151C0698 stores its v0 (P213).
- Since P211, difftest at a jalr compares every a0-a3/f12-f15 either side wrote since entry (JALRARG_OLD=1 = old). Dispatchers verified before P211 are listed for re-check in port HANDOFF P211. `DIFFTEST_STKFILL=WORD` fills the harness stack (it's zero by default, which hides dropped stores of 0).
- Always check that a mutant file actually differs from the draft (cmp/diff) before counting it. P200's "surviving" mutant was a sed that never applied.
- Plain-C callees are stubs in difftest too (P204): a callee returning a random f0/v0 makes a branch random and lets mutants survive. Give every callee that feeds a branch RETF/RET (+ ARGMEM) in the setups.
- The macOS host sed rejects `0,/re/` address ranges in mutant lines; use `1,/re/`.
- Since P200, DIFFTEST_ARG on a leading float parameter also sets f12/f14 (before, only a0/a1 were set, so float-first setups ran on random values; ARGF_OLD=1 = old). Known hole: a register the caller only passes through to an indirect call (jalr) is invisible to the compare, so a "pass 0 instead of obj" mutant survives. For dispatchers, also check the ELF disassembly at the jalr.
- Lazily mapped harness pages read 0 until something is stored there (P201): a DIFFER that only shows with a bogus pointer (e.g. 0x02000000) can be a load/store-order artefact. Prove it with WLOG/POKE before calling it a bug or dismissing it.
- Since P198 the memory compare includes words written by stub knobs (OUTW/OUTA/OUTB); before that, mutants that dropped a restore after a clobbering stub could survive — re-check "equivalent" restore survivors from older sessions.
- Watch for float bit patterns passed as ints (`0xC61C4000` to an `f32` parameter) — an m2c artefact that is wrong on wasm.

### Lesson: dropped arguments (P75, P78)
- IDO code often leaves a value in a0..a3 and the callee uses it even though the decomp's C call passes nothing (`f()` or a `void (*)(void)` pointer). On N64 it works by accident; in the port the argument becomes 0 → wrong object or NULL writes. Whenever a callee becomes C, check its callers' argument counts (run `tools/port/arity_scan.py` after every merge; output `docs/port/arity_scan.tsv`, a may-analysis: check the asm before fixing a row).

### Recovering after a host restart / power loss
- `open -a Docker`, wait for `docker info`, then `docker start conkerdev-port conkerdev-portb conkerdev-web conker-web-serve`.
- Check each worktree (`git log -1`, `git status`) for uncommitted work, then resume each interrupted agent with SendMessage (its context survives) — tell it the container is fresh, in-flight jobs are gone, and build outputs may be partial.

### Verification culture
- Conversions are accepted only with difftest EQUIV **plus mutants that DIFFER**; anything unreachable is marked UNVERIFIED and runtime-checked in the browser.
- Whole-function harnesses (`tools/port/difftest/nmasm_*.py`) for hand-asm / multi-entry code; compare against real ROM data where possible.
- The browser session is the integration test: after each merge it re-runs the boot, logs stub hits, and feeds an ordered blocker list back to the conversion slots.

### Logging (user wants a retrospective)
- After every session report, append one row to `docs/progress/sessions.tsv` (session, slot, slice, funcs, bytes, tool calls, key result); commit with the next merge.
- Refresh section 1 of this file whenever the status materially changes.
