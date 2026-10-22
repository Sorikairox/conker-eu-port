# Orchestrator notes

Two parts: (1) a **status snapshot** — overwrite it, don't append history (history lives in
`docs/progress/sessions.tsv`, `history.tsv`, `docs/sessions/sNN.md`, `docs/port/sessions/PNN.md`);
(2) **best practices** for running the agent sessions.

---

## 1. Status snapshot (2026-10-23, after P63)

### Goal
Conker's Bad Fur Day (EU ROM, user-owned) as a **native source port that runs in a web browser**:
full C compiled to wasm32 with Emscripten (TypeScript only for page glue), native Mac/Windows later
from the same C. **Not** N64Recomp / static recompilation, and not the existing US-only recomp ports.

### Numbers
| | functions with C | code bytes | where |
|---|---|---|---|
| Matching decomp (byte-identical) | 3994 / 5915 (67.5%) | 29.3% | branch `eu` — paused since 2026-10-21 |
| Port (matching + NON_MATCHING) | **4804 / 5915 (81.2%)** | **51.6%** | branch `port-b` (P47); `port` = 4803 |
| Asm-only left | 1111 | | ~157 under 60 insns |

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
- Boots from the user's ROM (dropped into the page, never leaves the browser); real game C runs the
  boot, level load (inflater, level loader, visibility build/walk), camera chain, lighting.
- Renders **level 0x21 from the game's own camera, lit by the game's lights** (P46 screenshot).
- **Player walks and the camera follows** (P49) — via TEMPORARY overrides of func_15059C84 (integrator) and func_1504C0E8 (partial); then made real C by P50; floor, landing, gravity, wall engine and ray cast are C (P53–P56).
- **Conker is drawn AND animated by the game's own code** (P61/P63: idle, walk, run, skid, fall, land, death; walk.gif). Walks, falls, respawns, level warp works. Coverage 4845/5915 (81.9%), 53.6% bytes (port P62).
- TEMPORARY PC versions still in port-web: func_1502AF04, func_1510E908, func_150A69E0 (P63), func_1000480C cartridge mapping; P62 converted func_150A9B0C/func_150A9E64/func_150844AC (drop on next merge).
- Fiber scheduler (ASYNCIFY), virtual big-endian memory, function-pointer trampolines, F3DEX2/F3DEXBG
  WebGL2 renderer (blender, fog, 3-point filter), CPU audio ABI incl. MP3 voices, Web Audio out,
  keyboard + gamepad via PIF model, EEPROM saves in IndexedDB, page UX (drop zone, pause, volume).
- Node and real-time Chrome run 600+ frames with 0 heap errors.

### Running now
- **P48** (`port`): object update loop func_1502C1D4 → func_1502E228/func_1502E7B4 (Conker's model pointer obj+0x1D4) — files game_eu_595D0.c, 13C400, ABEA0, 1ACBC0, 6EDC0.
- **P50** (`port-b`): func_15056B08 (call #2 DIFFER), walk handler's 3 UNVERIFIED branches, walk-path stubs, ray casts func_150ACEA0 / func_150A44A4 — files game_eu_78230.c, game_83300.c, game_14FF90.c.

### Next milestones (in order)
1. Conker's model drawn (object loop, P48).
2. Real movement C replacing P49's overrides: func_15059C84, func_1504C0E8, gravity func_1505A770, floor func_1510EED0/func_150A44A4, walls func_15044950 + func_150AB6D0/func_150AC8C4 (in raw asm/D5E90.s), func_15021834.
3. Remaining frame-path stubs: func_15041A9C (boot text), func_15180AF0.
4. Breadth: the 1111 asm-only functions; then Phase 2B (symbolic data) and native 64-bit build.

### Open items needing care
- Merge order: `port-b` → `port` only when the `port` worktree is idle; then `port` (or `port-b`) → `port-web`.
- `port-web` carries TEMPORARY PC overrides/wrappers (see its HANDOFF "Browser build"); remove each when the game C lands.
- Licensing: SDK-derived libultra C in the decomp (e.g. `game_eu_21DCD0.c`) — fine privately, matters if ever distributed (`port/ultra/LICENSES.md`).

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
- Never `pgrep`/`pkill` on the host; kill only PIDs you started. Background jobs only via `run_in_background`, never `&`.
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

### Mechanical asm→C translation (user decision 2026-10-23)
- `tools/port/asm2c_hand.py` (P56) writes register-level C, one statement per instruction. It is allowed **only for code Rare hand-wrote in assembly** (e.g. the D5E90.s engines). That is a stopgap; each such file is listed for a later readable rewrite.
- Code that was compiled from C (GLOBAL_ASM functions in src_eu) must still get real, readable C written from the asm — never the translator. The user explicitly rejected recompilation-style output for the game code.
- Current translated files: `src_eu/nm_asm/D5E90_walls.inc`, `D5E90_ray.inc` (wall engine, ray cast).

### Verification culture
- Conversions are accepted only with difftest EQUIV **plus mutants that DIFFER**; anything unreachable is marked UNVERIFIED and runtime-checked in the browser.
- Whole-function harnesses (`tools/port/difftest/nmasm_*.py`) for hand-asm / multi-entry code; compare against real ROM data where possible.
- The browser session is the integration test: after each merge it re-runs the boot, logs stub hits, and feeds an ordered blocker list back to the conversion slots.

### Logging (user wants a retrospective)
- After every session report, append one row to `docs/progress/sessions.tsv` (session, slot, slice, funcs, bytes, tool calls, key result); commit with the next merge.
- Refresh section 1 of this file whenever the status materially changes.
