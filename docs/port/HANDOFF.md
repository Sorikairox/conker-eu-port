# Port hand-off (branch `port-web`, worktree `~/conker-wt/web`)

Current-state summary. The per-session history (docs/port/sessions, docs/sessions, the old long hand-off) was deleted
in P329; it is in git history (e.g. `git show b274100a:docs/port/HANDOFF.md`) and on branch `exact-byte-decomp-wip`.
Session notes now go into this file (section "Sessions"), one short entry per session, plus a row in
`docs/progress/sessions.tsv`.

```sh
cd ~/conker-wt/web && eval "$(tools/eu_port/wt.sh env web)"    # CONKER_ROOT, CONKERDEV=conkerdev-web
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
```

## What the repo is now
- The EU game as readable C (`conker/src_eu`, 722 TUs; every function is C except 31 platform-replaced asm-only
  functions listed in `port/symbols/global_asm.tsv` / `tools/port/platform_replaced.tsv`) + headers (`conker/include`,
  libultra internals in `conker/include/libultra/{os,audio,io}`), built for the browser (wasm32, Emscripten) by `port/`.
  No `#pragma GLOBAL_ASM`, no `#ifdef NON_MATCHING` (stripped in P329); `#ifdef PORT` marks deliberate port changes.
- The byte-matching decomp build (IDO + splat + asm + US/debug/ects configs) is gone from port-web. It lives on branch
  `exact-byte-decomp-wip` (pushed by backup_push.sh; never merge it back).
- Names / addresses: frozen `port/symbols/symbols.tsv` (+ segments.tsv, global_asm.tsv, ido_cc.tsv). Game code and
  data are read from the user's ROM at run time (and by the build / difftest: `port/symbols/romimage.py`). Never commit
  ROM bytes.

## Daily commands
- Build: `port/web/run.sh build` (incremental by content; `build clean` for a clean one). Output port/build/web.
- Checks before every commit: `tools/eu_port/check.sh` (~150 s: implicit_scan 0 NM+float, romabs_check 0 FAIL,
  difftest selftest 152/152, census 722 TUs 0 FAIL, web build). Never commit on RED.
- Gameplay test (fast): `tools/port/scripts/warp.sh NAME SECS LEVEL [EXTRA_QUERY]` (?warp: level 0x29 at retrace 38).
- New-game route: `tools/port/scripts/newgame.sh DIR SECS [EXTRA_QUERY]` / `newgame_summary.sh NAME SECS PADF`;
  hold-L regression: `tools/port/scripts/holdl.sh` (opening ends at retrace 5789, level 0x29 at 5795, no traps).
  All browser runs: muted, det=2, one headless Chrome at a time, kill only your own PIDs.
- difftest (IDO 5.3 in the container compiles the candidate, reference = ROM): `tools/port/difftest.sh FUNC [FILE]`,
  registry re-runs `tools/port/reverify.sh FUNC` / `reverify_all.sh` (setups / mutants in `tools/port/testdata/`).
  The 21 registry rows with a HARNESS knob needed the matching build's ELFs and are reported as skipped.
- Renames: docs/RENAMING.md (`tools/eu_port/rename.py`, `apply_names.sh`).
- Deploy after a green check + browser test: `tools/eu_port/deploy_web.sh`; backup: `~/conker/tools/eu_port/backup_push.sh`.

## Reference docs
`docs/port/PLAN.md` (original port plan), `docs/port/MEMORY.md` (wasm memory model), `docs/port/design/P4..P9.md`
(browser harness, PC replacements, gfx interpreter, texture ids, audio HLE; cited by port code comments),
`docs/names/` (naming tables and proposals), `docs/progress/` (session log), `PLAYING.md` (what works).

## Open items
- Online multiplayer: phase 1 done (P338 + P339, docs/design/ONLINE_MULTIPLAYER.md §8, §9): 2-player lockstep over
  WebRTC with copy-paste codes, Online panel (option "Online multiplayer (experimental)"), time sync + send at sampling
  + 4 ms session loop (99.6 % speed at 40+0..20 ms 5 % loss D 3), automatic input delay from the ping, hidden / covered
  page ticks from a Worker, desync report naming the first different 4 KB page + symbols. Tests: netpair.sh (NETSIM_*,
  NETD=auto, HIDE, REALBG, DESYNC_AT/OFF, UI). Next: a real two-machine internet test, then phase 2 (room codes, 3-4
  players).
- Globals not renamed: 562 D_ symbols only declared in conker/include/variables.h (no C use), D_ names that appear
  only in tables / comments, ROM-offset symbols < 0x10000000, and D_ names inside log strings (kept so the wasm stayed
  identical). Some descriptions note wrong declaration comments or US/EU alias pairs (`_alias`) worth merging later.
- port_cdata name strings (n64mem_tab.c) still print the original D_ names (n64mem.py, RENAMED_FROM).
- ?warp is tested on level 0x29 only; other levels may need event state the real route sets.
- The slow-motion camera cut's blur (camera_cut_fade_update, fb_ghost pass 2) was not reached in a test since the
  P335 fix; it uses the same draw as the wake-up blur (fixed), so it should be right.
- fire_burn_update (registry row P206) kills only 46 / 89 m8eac mutants now (P206: 89 / 91); every survivor edits a
  stack record passed to a callee (effect / rumble request blocks). Add ARGMEM setups or find the harness change (P334).
- Aim kinds are only known by number (P334 table in the 69670be3 message); naming them (which is the slingshot, which
  the guns) needs a level route to each weapon pad.
- Route tests `p261 r5g / pan8` (new game -> later levels) were not re-tuned after P319; their pad scripts are in git
  history (docs/port/sessions/p261).
- port-b P317 leftovers (memcpy re-run of 19 registry rows, v0use candidates, random DIFFERs of func_1510E004 /
  func_15141A7C): their lists are in git history (docs/port/sessions/p317); the v0use / arity tools were deleted with
  the matching build.
- Analysis tools that read the matching ELF / asm were deleted in P329 (stubcalls, m2c_sanity, bootpath, priority,
  arity_scan, stride_scan, tablesig, v0use, protocheck, the nmasm harnesses). Rebuild them on port/symbols + the ROM if
  needed. romabs_check's source scan still skips `#ifndef NON_MATCHING` blocks (none left).

## Sessions
### P339 (port-web, 2026-10-27): online multiplayer phase 1 part 2 (time sync, auto delay, hidden tab, desync report)
- ff8ccdce time sync: input for N + D sent the moment it is sampled (pc_net.c -> Module.netAfterTick), session main
  loop on a 4 ms timer, port_net_kick runs the tick when the awaited input arrives, packets repeated once ~8 ms later;
  GGPO-style frame advantage (packets carry retrace + input margin; the peer ahead calls port_net_slow, frame() takes
  it out of the backlog, max 8 %; never needed in the tests). Stats: stat 7 ms slowed, 8 retraces that waited, 9 ms
  waited; netpair.js prints speed + waits. 40+0..20 ms 5 % D3: 79.2 % -> 99.6 % (8397 identical); 80/20 ms 15 % D3:
  65.7 % -> 87.5 % (5199 identical; RTT > D3 window); no netsim 100 % (7442).
- 9ac954a0 auto input delay: host pings 12x over 'ctl' before the session, D = clamp(ceil((median/2 + (p90 -
  median)/2) / 20) + 1, 2, 8); panel checkbox "automatic" (default on), ?netd=auto. Pings 0.8 / 36 / 94 / 134 ms ->
  D 2 / 3 / 4 / 5, all 100 % speed, identical. Panel shows "waits" (retraces) instead of 4 ms stalled ticks.
- 6facf7f1 hidden page: with normal throttling (REALBG=1) a covered guest never started (first main-loop iteration
  waited for rAF; a pre-session hidden pause stuck; page timers ~1 Hz). Fixes: session loop at 250 fps from the first
  tick, pause cleared, Worker ticker while hidden (port_net_background removed). Guest covered + minimised: 100 %, 5467
  identical. Desync report: per-page hash ring (16 points), page vector swap over 'ctl', first different page + symbols
  (conker_netsyms.txt, net_regions.py --syms); ?netdesync=N&netdesyncoff=OFS test: both panels report retrace 3000 and
  page N64 800B0000..800B0FFF with var70059904.
- PLAYING.md Online: automatic delay table, what to do when codes fail (phone hotspot, fresh codes, VPN, same build),
  hidden tab is fine now.
- Every commit: check.sh GREEN, hold-L 5789 / 0x29 at 5795, no traps; deployed. Not done: real two-machine test,
  byte-level desync location; the time-sync slow-down never triggered (margins stayed balanced), so it is untested
  under real clock drift.
### P338 (port-web, 2026-10-27): online multiplayer phase 1 part 1 (2-player online MVP)
- 20c14399 game side: pc_net.c §4 input ring (256 x 4, frame tags; pc_net.o is outside the hash), port_net_session
  (mask, local, D, K) before callMain (forces det, presence mask), local input for N + D sampled at retrace N (page
  local pad, or ?padf with ?netscript=1), pc_pif controller read from the ring, pc_sched frame() barrier
  (port_net_ready), port_net_drop, hash ring every 10 retraces. net.js ring access + ?netloop loopback peer
  (&netlat/&netloss). main.js netCfg (host options / EEPROM image, sandboxed saves, no hidden-tab pause).
  net_regions.py: p205_obj go_n / p240_steer.cfg excluded; conker_netx.txt has its own make rule; deploy ships
  net.js + conker_netx.txt. 4-pad loopback (30 ms, 5 % loss) = offline ?padf run in H for 8114 retraces.
- 156d900b net.js WebRTC: negotiated 'ctl' (reliable) + 'in' (unordered, 0 retransmits), public STUN only,
  copy-paste codes CK1.+base64url(deflate-raw SDP) ~770 chars, hello (build id = SHA-256 of conker.wasm, ROM SHA-256),
  host config, input packets repeating unacked inputs + ack + newest hash, ping, desync event, lost peer -> neutral.
  ?netsim=lat,jit,loss. window.__online API. tools/port/scripts/netpair.sh/.js (two windows, one headless Chrome).
  pc_sched frame() locals renamed (were mode/last/acc/per/now/dt/n).
- 88c794a3 Online panel (option "Online multiplayer (experimental)", default off; ?netpanel=1 test aid): Host / Join,
  codes + Copy, status, retrace / ping / stalls, "waiting for the other player…" overlay, desync box, Leave;
  port_net_background (timer loop while the tab is hidden; untested).
- 42b4cdd6 tests + input delay field: host vs guest identical (H and S) 9937 retraces (no netsim), 8448 (via panel
  buttons), 6801 until the guest left (40 ms + 0..20 jitter + 5 % loss, D 3: ~79 % speed, host went on alone),
  8432 with D 5 (~99 % speed), 3867 with asymmetric 80/20 ms + 15 % loss (~64 %); online host = offline 2-pad ?padf
  run in H. No desync anywhere. Tried + reverted: 6-period backlog catch-up online (worse, 73 %).
- Every commit: check.sh GREEN, hold-L 5789 / 0x29 at 5795, no traps; deployed. Part 2 list: design §8 + Open items.
### P337 (port-web, 2026-10-27): online multiplayer phase 0 (determinism harness + measurements)
- 73d4e325 `?netdet=1` forced online determinism (port/ultra/pc_net.c: det=2, flag whitelist, page writes no pads,
  default options once, blank sandboxed EEPROM) + `?padf1..3` / `?padmask` (pc_pif.c, the 4 channels share one table).
- c9faac16 `?nethash=F` per-retrace hash (pc_nethash.c: static region minus conker_netx.txt from the link map via
  port/tools/net_regions.py, minus GPU read-back ranges; S = fiber stacks), `?nethashstop` + dump, `?netprof`,
  `?netsnap`, `?netnogfx`, `?netgpujunk`; tools/port/nethash_diff.py (first differing retrace, bytes -> symbols),
  tools/port/scripts/netrun.sh (Chrome) / netnode.sh (node) / netmp_pads.py (4-pad Total War session: P1 menus, pads
  2-4 Start at ~5750, split screen from 6545). port/Makefile links with -Wl,-Map (wasm unchanged).
- 85a21fd5 fix: under ?netdet fiber stacks are static slots (heap layout differed Chrome vs node by 0xEB0; stack
  addresses live in game memory).
- Proven: 2 Chrome runs identical 10716 retraces (H and S); 4x throttle + 7 ms timer identical 10722; snapshot
  save/restore every retrace identical 9975; 6x throttle + GPU write-backs replaced by junk identical 9975 (game never
  reads them). Without rendering: static state identical (stacks differ only in dead garbage).
- Open: node vs Chrome differ from retrace 6 in 6 audio-arena words (N64 8007BF88...; not GL: Chrome ?nogl=1 matches
  Chrome). Firefox not installed; Safari needs `safaridriver --enable` (user). Numbers + go/no-go:
  docs/design/ONLINE_MULTIPLAYER.md §7 (phase 1 GO; rollback gate passed on desktop: 0.5 ms/retrace without
  rendering, 11.4 MB snapshot, ~0.4 ms save/restore, ~14 KB dirty per retrace).
- Both code commits: check.sh GREEN, hold-L 5789 / 0x29 at 5795, no traps. Deployed.
### P335 (port-web, 2026-10-27): motion blur fix, rumble takes effect at once
- 19d444bd fix (not an option): the frame-blend ghost (fb_ghost_render: draw g_fb_ghost_image over the frame with
  prim alpha 210, blender IN*a + MEM*(1-a); SETCIMG ghost; copy the screen into it 1:1 in 128 x 16 tiles; SETCIMG
  screen) is a feedback blur at the framebuffer's own size (292 x 216 RGBA16 on the N64: as sharp as the frame).
  Two port bugs: the renderer took the ghost image for a screen image (P161), so the copy wrote the canvas of two
  frames ago into RDRAM and drew it at N64 resolution (the frozen, blocky frame), and fb_ghost_image_draw's
  `image + 0x80000000` (KSEG0 -> physical) named other memory for a wasm pointer (now #ifdef PORT: pointer as is).
  Renderer: "hx" images (gfx_f3dex2.c): a second >= 256-wide 16-bit colour image of a task that is not a game
  framebuffer is an FBO at canvas resolution; screen reads while it is bound come from a canvas snapshot; LOADTILE /
  LOADBLOCK remember the source pixel and 1:1 texrects sample the GL texture per canvas pixel (shader uHiRes).
  ?p335off=1 old behaviour, ?p335log=F logs. camera_read_depth_row's 292 x 1 buffer also goes this way (its RDRAM
  was never written before either). Shots port_work/p326/p335d (ghost 123.0..127.4 s, every shot differs, trails),
  p335nd (nodrunk: no ghost). Renames: params / locals of fb_ghost_copy_draw / fb_ghost_image_draw /
  fb_ghost_render (md5 unchanged).
- 383404a1 rumble: rumble_update (#ifdef PORT) sets g_rumble_probe_request when PORT_OPT_RUMBLE changes, so the
  game's own probe runs that frame (on: pak found, state reset; off: pak gone); pc_pif forgets probe / motor bytes
  while off. Test aid ?p326=1&p335rumble=F&p335rumbleoff=G (p326_probe.c, via port_set_option). Proven on warp 0x29
  with a temporary rumble_request hook (removed): request at 300 (off) nothing, on at 401, request at 450 -> motor
  start 453 + page playEffect, off at 601, request at 650 nothing; no level reload (port_work/p327/p335rum).
- Both: check.sh GREEN, hold-L 5789 / 0x29 at 5795, no traps. Deployed.
### P334 (port-web, 2026-10-27): feature #13 aiming crosshair
- 69670be3 option "Aiming crosshair" ('crosshair', PORT_OPT_AIM_CROSSHAIR 14): the original aim HUD
  (aim_hud_spawn_for_mode) gives every aim kind a reticle except 0x12 / 0x18 / 0x38 / 0x3B; of those only 0x18 uses
  the first-person aim camera (camera_update_aim_mode), whose fire ray (obj_ray_cast_from_ctl, record +0x13C along
  +0x130) is the camera's view axis = screen centre (measured: same origin, same direction within one frame of
  easing). With the option on, that branch spawns the game's own centred crosshair sprite (aim_hud_crosshair_spawn)
  when the aim state is 2; R-look kinds (hand / mouth-aimed shots) are left alone. Shots: port_work/p327/p334o0 (off),
  p334o1 (on), p334_<kind> (original HUD of 14 kinds).
- Test aid: ?p326=1&p334aim=T (p326_probe.c) keeps the fallback pad kind (+0x7C) at T so B takes item kind T on any
  level; ?p334log=1 logs kind / phase / aim / look state and the fire ray vs the camera. Pad: B at 200, R from 450.
- Renames: struct126 unk75 / unk78 / unk11A / unk197 / unk198 -> pad_kind / item_kind / item_phase / aim_state /
  look_state (compile-driven from census errors, port_work/p334/fieldren.py: only accesses clang reported as
  struct126 members change; 3 mutant files follow); locals of aim_hud_spawn_for_mode, aim_hud_crosshair_spawn,
  obj_ray_cast_from_ctl. wasm md5 unchanged by each rename step.
- fire_burn_update re-run (MUT=1 NORAND=1): setups 21/21 EQUIV; m8eac 46 killed / 89, m8eacb 1/4, m8eacc 0/2, 0 not
  applied. P206 had 89/91. All 43 m8eac survivors change stores into stack records handed to callees (smoke / flame /
  crackle / burst effect and rumble request blocks), not the P333-renamed names alone: most likely the known blind spot
  "random EQUIV compares stack records only by class STK" (needs ARGMEM setups, P220). Not re-run on pre-P333 code to
  pin the cause; open item. Mutant files changed here re-run: 15073FA0 74/74, 15072B44 34/34, m4A94 34/40 (its 6
  survivors are on untouched lines).
- check.sh GREEN, hold-L 5789 / 0x29 at 5795, no traps. Deployed.
### P333 (port-web, 2026-10-27): features #11 and #12
- d6ffdbba option "Inverted swimming" ('swiminvert', PORT_OPT_SWIM_INVERT 12): the N64 swims like a plane (stick up
  = target pitch dive * 2.25 > 0 = head-down = dive; down = rise) in swim_water_physics (state 1 in water) and
  player_swim_update (state 0x15: stick * 1.25 -> gravity, y_velocity -= gravity). port_swim_stick_y (pc_os.c) flips
  stick y at those reads only. Measured (river, float flags cleared): off up -> pitch -7.5 (floor-capped head-down),
  down -> -90; on: the mirror. Test aids in p326_probe.c: ?p326nofloat=1, ?p333=1 (swim log), ?p326tpy=Y.
- ca201310 option "Rumble" ('rumble', PORT_OPT_RUMBLE 13): pc_pif.c answers pak commands 0x02/0x03 for blocks
  0x400 (probe, 0x80) and 0x600 (motor) with libultra's data CRC when on; motor changes -> Module.portRumble ->
  vibrationActuator.playEffect('dual-rumble') / reset() in main.js. Other pak addresses and the EEPROM unchanged;
  off = no pak as before. The game probes at level / area start (g_rumble_probe_request). Proven with a temporary
  rumble_request hook (removed) + ?p333pad=1 (fake gamepad that logs playEffect / reset): start 405 / stop 441 ...,
  off: nothing. No natural rumble source was found near the 0x29 start in a few tries (pan, drop from height):
  sources are impacts / explosions / anim-event cam shakes / fire / lightning.
- Renames: structEU_151D8E18 fields -> flags / life / strength / player_mask / update_fn (+ selftest case and 3
  mutant files), D_eu_800E0E30 -> g_rumble_clear_request, locals of rumble_update / rumble_start / rumble_stop /
  rumble_start_strength / rumble_request / player_swim_anim_speed. wasm md5 unchanged by the renames.
- Both: check.sh GREEN, hold-L 5789 / 0x29 at 5795, deployed. reverify: emitter2_flame_update 106/106,
  sinking_platform_update 67/68 (survivor not in the renamed lines), fire_burn_update m8eacb/c keep old survivors.
- Lesson: a field rename by regex over "the function body" must stop at block scope: scene_event_run_b reuses `s`
  with other types in other switch cases (census FAIL caught it; check census 0 FAIL + md5 after such renames).
### P332 (port-web, 2026-10-27): features #10 and #9
- 5b49ac4b option "Underwater air meter" ('airbar', PORT_OPT_AIR_BAR 8): hud_air_bar_draw (game_BC510.c, end of
  hud_draw) draws a bar of the air left, (0x5A1 - air_counter) / 0x5A1, while Conker is in water and the counter
  runs; red in the last quarter. The original only has the face meter (model 0xB9, from 0x5B ticks, shape stops
  changing at counter 720) and bubbles. Works with Longer breath (reads the same counter). struct127 unkB2 ->
  air_counter. Shots: port_work/p327/p332a (on), p332off, p332lb (with longbreath).
- 27967f91 sliders "Music / Sound effects / Speech volume" ('volmusic' / 'volsfx' / 'volspeech', ids 9..11, 0..100 %,
  default 100): port_volume_scale (pc_os.c) in __n_vsVol (sequence voices), SND_VOL155 (sound player) and the MP3
  stream's envelope targets (SPEECH_VOL). Page: OPTIONS rows with range: true, same port_set_option channel.
  Measured on the opening: music x0.49996, sfx x0.24995, speech 0 at 50/25/0; all 0 -> output rms 0.0871 -> 0.0007.
- Test aid: ?p326tpf=F&p326tpx=X&p326tpz=Z teleports Conker (river: 855, -1056); the 0x29 river is float water, so
  air tests still need a temporary hook clearing the float flags in swim_water_physics.
- Lesson: game TUs cannot hand string literals to host helpers (port_flag / port_log saw nothing), and an undefined
  symbol (e.g. a static referenced from a probe) is silently stubbed by gen_stubs: pass test switches through a
  global defined in the game TU.
- Both: check.sh GREEN, hold-L 5789 / 0x29 at 5795, deployed.
### P331 (port-web, 2026-10-27): features #7 and #8
- 2023e2ed option "No motion blur / drunk sway" ('nodrunk', PORT_OPT_NO_DRUNK_FX 6): fb_ghost_set_mode turns every
  frame-blend request off; camera_update_shake and camera_wobble_apply ignore their drunk triggers (camera mode
  0x80000 = title menu, +0x5F0 bit 3 = drunk state); the under-water wobble and cutscene camera-path roll stay.
  Measured on the new game route: menu wobble 0.003 -> 0, menu roll +-2.9 -> 0, wake-up ghost 210/1 -> 0/0.
- 42be5836 option "Conker always full detail" ('conkerlod', PORT_OPT_CONKER_FULL_LOD 7): obj_select_lod gives
  level 0 to the object whose level-0 model is 0 (Conker, models 0..4). Off: level 1 at 529..627 units while
  running; on: level 0 always.
- Both: check.sh GREEN, hold-L 5789 / 0x29 at 5795, deployed. Found the ghost-effect render problem (Open items).
### P330 (port-web, 2026-10-27): global variable names, cash counter images
- Tooling 666e0ef9 (+ fixes 2 later commits): rename.py / apply_names.sh handle `D_` rows (`/* was D_X */` on each
  declaration line, string literals kept, wasm byte-identity enforced; tools/eu_port/wasm_sig.py,
  tools/eu_port/globals_chunks.py -> docs/names/globals.tsv). docs/RENAMING.md "Globals".
- 3920 globals renamed in 4 batches (ebb2912c, be9ad98b, d6348054, 004c464f) from 15 proposal files
  (docs/names/proposals/globals01..15.tsv, written by naming sessions); object-table fields unified to
  `g_objects_<field>` (cf93e1fd). conker.wasm md5 f73eb4a2... unchanged throughout.
- Cash counter 3478fd22: option "Always show cash" draws the pause screen's $ + digit images, half size, top right
  (hud_cash_counter_draw in game_eu_216470.c); the P325 text version is gone. Browser-tested, hold-L OK, deployed.
### P329 (port-web, 2026-10-27): cleanup part 2 of 2
- Step 1 (3771055a): gen_stubs `asm_only()` and difftest `find_file` read `port/symbols/global_asm.tsv` (1892 former
  GLOBAL_ASM functions, 31 asm-only) instead of the pragmas. Same results for all names; md5 unchanged.
- Step 2 (166c8afa): `tools/port/strip_nm.py` stripped 2270 NON_MATCHING blocks and 1892 GLOBAL_ASM pragmas (461
  src_eu files + functions.h / variables.h); -DNON_MATCHING dropped from the port build. difftest splices a candidate
  by top-level items (replaces same-name typedefs / prototypes / data near the function, like the old whole-block
  splice); one selftest case got `//DROP` lines. md5 unchanged, selftest 152/152.
- Step 3 (7cf600ba): deleted the matching build (generated output, configs, vendored splat / asm-processor / IDO
  recomp, conversion-era tools, conker/src US tree; libultra headers moved to conker/include/libultra). check.sh,
  rename.py, apply_names.sh: port mode only. Clean rebuild md5 unchanged, selftest 152/152.
- Step 4: live test inputs moved to `tools/port/testdata/` (1068 registry setups / mutants) and
  `tools/port/scripts/` (newgame.sh, newgame_summary.sh, warp.sh, new holdl.sh); docs/port/sessions, docs/sessions,
  root HANDOFF.md and matching-only docs deleted; P4..P9 design docs kept in docs/port/design.
- conker.wasm md5 f73eb4a25467dc5aa21b8a12cab69699 at every step (same as before P328).
- Step 5: orchestrator.md section 2 rewritten for the port-only layout (matching-build / verify_all / convert rules
  removed, port rules kept), README "how to build" + layout, PLAN.md marked historical. Final: check.sh GREEN;
  holdl.sh: opening ends at 5789, 0x29 at 5795, 0 traps to retrace 9965; warp.sh 29: 0x29 at 38, 0 traps. Deployed.
- Size: tracked files 8450 -> 2103, tracked bytes 325.9 MB -> 21.2 MB; worktree on disk 3.7 GB -> 2.4 GB (of which
  2.1 GB is the gitignored port_work scratch).
- backup_push.sh fast-forwarded `eu` (main checkout ~/conker) to port-web, so ~/conker now has this layout too:
  root HANDOFF.md is gone there (the eu decomp hand-off is in history / on exact-byte-decomp-wip) and the old
  untracked dirs (tools/asm-differ, asm-processor, mips_to_c, n64splat, tools/eu_port/m2c) are left on disk there.
- Follow-ups: rebuild analysis tools on port/symbols if needed (Open items).
