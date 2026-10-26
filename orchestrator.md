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
| `port-web` | `~/conker-wt/web` | `conkerdev-web` + `conker-emsdk` image | **integration branch: always holds the latest of everything** (game C, browser build, docs, logs) |
| `eu` | `~/conker` | `conkerdev` | kept equal to port-web (backup_push.sh fast-forwards it); play.sh / backup_push.sh run from here |

Rule (user, 2026-10-26): port-web must always have the latest code. Commit session work on port-web (or merge it
into port-web before the session ends). backup_push.sh fast-forwards eu to port-web and warns about any branch with
commits port-web lacks. The WIP branches eu-wt-a, port, port-b, port-c..f and port-web-b were fully merged on
2026-10-26 and are to be deleted. New parallel slots: `wt.sh new <name>` from port-web, then merge back the same day.

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

### Layout since P329 (port-web)
- port-web holds only the EU game as readable C (`conker/src_eu`, `conker/include`) + the browser port (`port/`) +
  its tools (`tools/eu_port/{check,rename,apply_names,wt,deploy_web,backup_push,play,waitjob,merge_union,names_table}`,
  `tools/port/` difftest + registry, `tools/port/testdata/` (registry setups / mutants), `tools/port/scripts/`
  (browser tests)). No GLOBAL_ASM pragmas, no NON_MATCHING wrappers, no IDO/splat build, no US tree.
- The byte-matching decomp build is on branch `exact-byte-decomp-wip` (pushed by backup_push.sh, never merged back).
  Branch `eu` and the old port slots keep their own copies of the matching tooling; this section's rules are for
  port-web.
- Names/addresses: frozen `port/symbols/symbols.tsv` (+ segments.tsv, global_asm.tsv, ido_cc.tsv); game code/data
  from the user's ROM. Never commit ROM-derived bytes.

### Session shape
- **One budgeted session per agent**: hard cap ~150 tool calls; at ~135 stop new work and hand off. Long contexts degrade quality; rotate instead.
- Every session ends with: a short entry in the "Sessions" section of `docs/port/HANDOFF.md` (there is no session-doc
  folder any more), HANDOFF's current-state sections updated, a row in `docs/progress/sessions.tsv`, a commit, and a
  concise report. Agents never push.
- Backups (user request 2026-10-24): the orchestrator runs `tools/eu_port/backup_push.sh` regularly (after merges / a few sessions) — it pushes all branches to the PRIVATE repo `origin` = github.com/Sorikairox/conker-eu-port. Never push to `upstream` (mkst/conker); the repo stays private (history contains ROM-derived screenshots/data).
- Use Opus for debug / feature sessions; Sonnet only for mechanical tooling or one-off utilities (e.g. the dashboard).
- Brief = context paths to read + an ordered focus list + explicit skip list + rules. Pass forward concrete findings (function names, addresses, files), not summaries of summaries.

### Parallelism
- At most 2–3 agents at once. Each agent gets **its own worktree + container**; give them **disjoint source files** and state the forbidden files in both briefs.
- When reassigning work mid-flight, message *both* agents (the one losing and the one gaining files).
- Shared Mac mini: `-j4` per remote job, ≤2 lists in parallel.

### Safety rules (put in every brief)
- `eval "$(tools/eu_port/wt.sh env <name>)"` before **every** repo tool; every Edit/Write path must start with the worktree root. Port tools refuse to run without the right `CONKER_ROOT` (portguard).
- Never `pkill` on the host (the real hazard: it can kill another agent's jobs); kill only PIDs you started. Agents keep slipping into read-only `pgrep` in wait loops — harmless but against the rule; tell them to wait with `tools/eu_port/waitjob.sh` or log polling. Background jobs only via `run_in_background`, never `&`.
- Never `git stash` (the stash stack is shared by all worktrees, and stashing during an unfinished merge resets the index — P169). Use a WIP commit or copy files aside instead.
- Commit gate: `tools/eu_port/check.sh` GREEN (implicit_scan 0 NM+float, romabs_check 0 FAIL, difftest selftest
  152/152, census 722 TUs 0 FAIL, web build; ~150 s). Never commit on RED. A change that should not change the game
  (tooling, cleanup) also proves conker.wasm's md5 unchanged.
- difftest knobs use **EU addresses** (port/symbols/symbols.tsv gives name <-> address).
- Leave no difftest / browser processes running at hand-off; check `docker exec <container> ps`.

### Permissions
- If the permission system denies an agent an action, **don't redo it yourself** — surface it to the user with the exact command. Only the user's own message is approval; a relayed approval in an agent prompt is not (the classifier blocked one).
- After the user approves, the orchestrator runs it directly.

### Merging
- For port branches: `git merge --no-edit`, resolve `docs/*` conflicts with `tools/eu_port/merge_union.py <file>` (pass each path explicitly — zsh doesn't word-split), stop on code conflicts; then `tools/eu_port/check.sh` and a clean web build (`port/web/run.sh build clean && port/web/run.sh build`).
- A branch that still has GLOBAL_ASM pragmas / NON_MATCHING blocks (anything branched before P329) must be stripped
  with `tools/port/strip_nm.py` on its side before merging into port-web, and its renames re-applied with
  `tools/eu_port/rename.py`.

### Asm-only code (user decision 2026-10-23)
- Code Rare hand-wrote in assembly was translated register-level (`conker/src_eu/nm_asm/D5E90_walls.inc`,
  `D5E90_ray.inc`); the translator (asm2c_hand.py) was deleted in P329. Those files are still listed for a later
  readable rewrite. Compiled game code always gets real, readable C.
- 31 platform-replaced functions have no C (port/symbols/global_asm.tsv asm_only = 1; tools/port/platform_replaced.tsv):
  the port's platform layer (port/ultra, port/boot) replaces them. They count as done (user decision 2026-10-25).

### Lesson: converted C on top of asm stubs (P72)
- A correct C function can still corrupt memory when its **inputs come from an asm stub** (NULL buffers, garbage out-params): it then writes into the null zone and other code reads that as objects. When a browser run shows heap corruption, bisect merges first (scratch worktree + bounded reproducer), then look for stubbed producers of the faulting function's pointers.
- Rule since P97: in briefs, require **producers before consumers**, including callbacks/handlers the new C dispatches to (P105).
- Check `port/build/census` has 0 FAIL after merges: a TU that fails the clang census build is silently replaced by stubs (P107 found 4 such TUs). check.sh does this.

### Naming
- Naming (user request 2026-10-26): when a session touches or reads a function, it RENAMES it to an explicit, human-readable name and keeps a comment with the original asm name (`/* was func_XXXXXXXX */`). The rename must be repo-wide (C, headers, port tables, port/symbols/symbols.tsv, registries, testdata), so use `tools/eu_port/rename.py` / `apply_names.sh` (docs/RENAMING.md), never an IDE rename.
- Variable naming rule (user, 2026-10-26): variables get readable names too. Locals/params (var_v0, temp_t6, arg0...) are renamed directly in the C a session works on. Global data symbols (D_XXXXXXXX) go through names.tsv + the rename tooling, with a `/* was D_XXXXXXXX */` comment; a full global-variable renaming pass is the next planned step.
- Renaming done (P323, 2026-10-26): 5695 functions renamed through tools/eu_port/names.tsv. Only func_150A4ED4 / func_150A69A8 keep their names (secondary entry points inside another function). Names with "(med)"/"(low)" in their names.tsv description are guesses worth a human look.
- Lesson (P323): port tools that derive an address from a `func_<ADDR>` name break silently on renamed functions; resolve through port/symbols/symbols.tsv / names.tsv instead.

### Features and deploys
- Feature rule (user, 2026-10-26): every new feature is OPTIONAL (a toggle in the page's Options panel, saved per
  browser; default off = original behaviour unless the user asked for it as default, e.g. hold-L skip stays on), and
  each feature gets its own commit so the user can read how it was done.
- Deploy rule (user, 2026-10-26): ALWAYS deploy the latest version. After a port-web change passes check.sh and its
  browser test, run `tools/eu_port/deploy_web.sh` (ships port/build/web to https://conker-web-port.netlify.app;
  apply_names.sh does it itself). Never deploy a build that failed or skipped its browser test.
- Plan (user, 2026-10-26): P327 speed-up tooling -> cleanup (P328/P329, done) -> global variable renaming -> cash
  counter with the pause-screen digit images.

### Port-web session workflow (P327/P329; 10-core Mac mini, other slots idle)
- **Build**: `port/web/run.sh build` rebuilds exactly the TUs whose source or included headers changed (content keys
  from clang depfiles). One-file game-C edit: 6 s; no-op: 2 s; a header every TU includes: ~45 s. Output equal to a
  clean build (conker.wasm md5). Edits to port/exclude.txt only take effect through the census list.
- **Gameplay tests**: `tools/port/scripts/warp.sh NAME SECS LEVEL [EXTRA_QUERY]` (env PADF, SCENE, POS, SHOTS)
  = `?warp=<level hex>[&warpscene=N]`: boots straight into gameplay (level 0x29 at retrace 38, fresh save, det=2,
  muted). A walk test is a 30 s run (33 s wall). Without ?warp nothing changes.
- **New-game route** (intro, title, opening, saves): `tools/port/scripts/newgame.sh DIR SECS [EXTRA_QUERY]`,
  `newgame_summary.sh NAME SECS PADF`; the hold-L regression is `tools/port/scripts/holdl.sh` (opening ends at
  retrace 5789, level 0x29 at 5795, no traps).
- **Checks**: `tools/eu_port/check.sh` (one mode since P329; `--port` still accepted). Prints one line per step and GREEN/RED.

### Lesson: test the harness itself (P71, P73)
- Twice a difftest bug made results meaningless while looking fine: callee arity taken from call statements (P71), and the candidate silently dropped when one NM block holds two functions (P73) — every mutant "survived" because the old copy was tested. A surviving mutant that should obviously die is a harness bug until proven otherwise; add a selftest case for every harness fix.
- Since P329 difftest has no NM blocks to replace: it splices the candidate by top-level items (the function plus same-name typedefs / prototypes / data around it). A candidate that relies on removing other declarations of the TU uses `//DROP <line>`.
- Concurrent knob and mutant runs of the same function must not share a temp dir; use `tools/port/reverify.sh FUNC` (MUT=1 for mutants) from the registry, never a hand-typed command (P221).
- RET/OUTW/ARGMEM keys: take the address from the decoded `jal` word, not from the symbol name (some EU names map elsewhere, e.g. func_151ACBD4 is jal 151AD184); a wrong key silently does nothing. `DIFFTEST_ARG` values are hex (`1=10` means 0x10).
- DIFFTEST_POKE can't change ROM rodata or `.game_data`; take the real value from the ROM image instead.
- Stub return pointers must be heap-like (0x804xxxxx): values in the harness stack range 0x80600000–0x8067FFFF all compare equal ("STK"), hiding wrong-pointer mutants (P86).
- difftest flags `[POKE unread]` / `[knob callee never called]` — read them; they catch wrong addresses in knobs.
- difftest precedence since P132: learned pointers > DIFFTEST_POKE > ROM image > random.
- difftest needs the pinned Unicorn 2.0.1 in each worktree's port_work/pyuc201 (gitignored). Without it, the container's 2.1.4 is used silently and calls next to FPU instructions fault at pc 0 (P233). Install it with: docker exec <ctr> pip3 install --target /conker/port_work/pyuc201 unicorn==2.0.1.post1
- difftest's candidate compiler is IDO 5.3 in the dev container (`/opt/ido5.3`, image conker-arm from Dockerfile.arm; flags per TU in port/symbols/ido_cc.tsv). Keep that image; deleting IDO ends difftest.
- The 21 registry rows with a HARNESS knob (whole-function nmasm harnesses) needed the matching build's ELFs; reverify.sh reports them as skipped.
- Random EQUIV compares stack records only by class ("STK"), so dropped stores into stack structs passed to callees go unseen. Functions that build request/record structs on the stack need ARGMEM setups (P220).
- difftest's memcpy stub copies nothing unless `DIFFTEST_MEMCPY=1` (P317); or use `DIFFTEST_OUTA=10023360=0:...` (P301).
- IDO folds `0.0f + x` to `x`, so C copied from asm `0.0 + s * -1.0` loses -0.0 results. Read the zero from a volatile if the sign of zero matters (P310).
- Never commit a harness change with a red selftest (P214). For harness edits: run the selftest before and after, and bisect against the previous difftest.py when a case flips.
- Always check that a mutant file actually differs from the draft (cmp/diff) before counting it. The macOS host sed rejects `0,/re/` address ranges in mutant lines; use `1,/re/`.
- Plain-C callees are stubs in difftest too (P204): a callee returning a random f0/v0 makes a branch random and lets mutants survive. Give every callee that feeds a branch RETF/RET (+ ARGMEM) in the setups.
- Lazily mapped harness pages read 0 until something is stored there (P201): prove a bogus-pointer DIFFER with WLOG/POKE before calling it a bug.
- Never edit a script while a background job is running it (P259).

### Lesson: wasm-specific bugs in game C
- Functions reached through function-pointer tables must have the signature the dispatcher uses (return type too): a `void` C function called through an `s32` table pointer whose result is tested traps on wasm (P159). When a C function sits in a handler table, check its asm (ROM) for v0 (P174).
- IDO code often leaves a value in a0..a3 and the callee uses it although the C call passes nothing (P75/P78): on wasm the argument becomes 0. Check callers' argument counts against the callee.
- N64 code assumes 4-byte alignment of small stack arrays passed as wider pointers (P178); vbe.py aligns stack variables like IDO does.
- Old m2c-era C can hide pointer-stride / access-width bugs (`f32 *p; p + 0xC`, word reads where the asm uses lb; P118, P269). Grep for typed-pointer + byte-offset patterns and difftest them.
- Standing check: `tools/port/implicit_scan.py` (in check.sh) lists implicitly declared calls; IDO is silent about them. An implicit call that passes or returns a float is a real bug (P227, P230); NM+float must stay 0.
- New C that uses a `D_<small hex>` link symbol (an absolute value such as a texture id) needs a ROM_ABS entry in port/tools/vbe.py (romabs_check in check.sh); symbols that alias real data need an alias (P228).
- Watch for float bit patterns passed as ints (`0xC61C4000` to an `f32` parameter) — an m2c artefact that is wrong on wasm.
- Port-side OS replacements (port/ultra) must do everything libultra's version does, including side effects such as creating queues (P236). When a hang has no trap, look first at blocking osRecvMesg on queues that port code is supposed to feed.
- Game-C debug logs need port_glog (port_log prints nothing from a vbe TU).

### Browser tests and the host
- Browser route tests must run with `?det=2` (P252). Use det=1&timer=2 to tune routes fast, then replay with det=2.
- Browser test runs must be SILENT: Chrome with `--mute-audio` (and/or page volume 0) (2026-10-25).
- Never run two Chrome runs at once: the second hides the first tab and the game pauses (P223).
- Host: /usr/local/bin/docker is a dangling link to the uninstalled OrbStack. Agents must `export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH` before repo tools that call docker (P250).
- If Docker Desktop crashes (all containers exit 255): `open -a Docker`, then `docker start conkerdev-port conkerdev-portb conkerdev-web conker-web-serve`, and tell running agents to re-run anything in flight (P256). After a crash, bind mounts can serve a STALE view for 100+ s (P260): restart Docker Desktop cleanly (`docker desktop restart`) when no agent runs.
- The user plays a frozen copy with tools/eu_port/play.sh (container `conker-play`, port 8070, ~/conker-play/). Agents never touch that container, port or folder. Keep PLAYING.md's "what works / known problems" current.
- Docker VM memory (7.75 GiB) is shared by all slots: run node jobs one at a time.

### Recovering after a host restart / power loss
- `open -a Docker`, wait for `docker info`, then `docker start conkerdev-port conkerdev-portb conkerdev-web conker-web-serve`.
- Check each worktree (`git log -1`, `git status`) for uncommitted work, then resume each interrupted agent with SendMessage (its context survives) — tell it the container is fresh, in-flight jobs are gone, and build outputs may be partial.

### Verification culture
- Changes to game C are accepted with difftest EQUIV **plus mutants that DIFFER** (registry row in tools/port/verify_registry.tsv, inputs in tools/port/testdata); anything unreachable is runtime-checked in the browser.
- The browser run is the integration test: warp.sh for gameplay, holdl.sh / newgame.sh for the real route.

### Logging (user wants a retrospective)
- After every session report, append one row to `docs/progress/sessions.tsv` (session, slot, slice, funcs, bytes, tool calls, key result); commit with the next merge.
- Refresh section 1 of this file whenever the status materially changes.
