# Orchestrator notes

Two parts: (1) a **status snapshot** — overwrite it, don't append history (history lives in
`docs/progress/sessions.tsv`, `history.tsv`, `docs/sessions/sNN.md`, `docs/port/sessions/PNN.md`);
(2) **best practices** for running the agent sessions.

---

## 1. Status snapshot (2026-10-23, after P89)

### Goal
Conker's Bad Fur Day (EU ROM, user-owned) as a **native source port that runs in a web browser**:
full C compiled to wasm32 with Emscripten (TypeScript only for page glue), native Mac/Windows later
from the same C. **Not** N64Recomp / static recompilation, and not the existing US-only recomp ports.

### Numbers
| | functions with C | code bytes | where |
|---|---|---|---|
| Matching decomp (byte-identical) | 3994 / 5915 (67.5%) | 29.3% | branch `eu` — paused since 2026-10-21 |
| Port (matching + NON_MATCHING) | **4918 / 5915 (83.1%)** | **57.2%** | branch `port` (P89); `port-b` = 4897 (P87); merged total higher |
| Asm-only left | ~997 | | ~148 under 60 insns |

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

### Browser build — what works
- Boots from the user's ROM; real game C runs boot, level load, camera, lighting, Conker's model/animation/tail, attachments, text, HUD sprites, sky gradient, breakables, scene loader.
- Playable flow in node and real-time Chrome: walk, fall, respawn + 250-frame respawn scene, warp to 0x2C and back; 0 heap errors (P88).
- TEMPORARY guards in port-web (P88): scene end (func_1501E888) and actor frame blocks (func_1501ECA4) — both now C on port-b (P87); P91 is dropping them.
- Renderer: F3DEX2/F3DEXBG WebGL2, LOD/mip fixed (P78). Blurry near ground is the level data (low texel density), not a bug.
- Arity scanner `tools/port/arity_scan.py` (P79): 111 rows / 56 severity>0 at P88.

### Running now
- P90 (`port`): func_150268BC script event interpreter (3590 lines; P89 map + draft).
- P91 (`port-web`): merge P86–P89 + P87, drop P88 guards, runtime checks.
- P92 (`port-b`): remaining scene-path asm (func_1501FD34, func_1501FF10, ...), game_14FF90.

### Next milestones
1. No TEMPORARY guards in port-web; head turning works (look-target producer).
2. func_150268BC (scripts/cutscenes) as C.
3. Frame-path stubs to zero (blocker list in the latest web session doc); arity rows to zero.
4. Breadth: the ~1000 asm-only functions; then Phase 2B (symbolic data) and native 64-bit build.

### Open items needing care
- Merge order: `port` and `port-b` own disjoint files; both merge into `port-web` (browser session does it). `port-b`→`port` only when `port` is idle.
- Licensing: SDK-derived libultra C in the decomp — fine privately, matters if ever distributed (`port/ultra/LICENSES.md`).
- Container `conker-web-p6` is running and not owned by any current session (user's call).

---

## 2. Best practices for managing the agents

### Session shape
- **One budgeted session per agent**: hard cap ~150 tool calls; at ~135 stop new work and hand off. Long contexts degrade quality; rotate instead.
- Every session ends with: a session doc (`docs/port/sessions/PNN.md`), HANDOFF.md updated (state + next steps), a commit, and a concise report. Never push.
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
