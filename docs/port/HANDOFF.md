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
- Source-level debugging (P342, docs/port/DEBUGGING.md): `tools/port/scripts/debug_build.sh` builds a DWARF `-O0`
  wasm in its own copy of the tree (port/build-dbg/tree; never touches port/build) and serves it at
  http://localhost:8077/app/index.html?app=game&mute=1&romurl=../dev/rom.z64&warp=29 (`debug_build.sh stop` stops the
  server). Chrome + "C/C++ DevTools Support (DWARF)": breakpoints on C lines. CLion: `compile_commands.json`
  (`tools/port/scripts/gen_compile_commands.py`).
- Renames: docs/RENAMING.md (`tools/eu_port/rename.py`, `apply_names.sh`).
- Deploy after a green check + browser test: `tools/eu_port/deploy_web.sh`; backup: `~/conker/tools/eu_port/backup_push.sh`.

## Reference docs
`docs/port/PLAN.md` (original port plan), `docs/port/MEMORY.md` (wasm memory model), `docs/port/DEBUGGING.md` (debugger), `docs/port/design/P4..P9.md`
(browser harness, PC replacements, gfx interpreter, texture ids, audio HLE; cited by port code comments),
`docs/names/` (naming tables and proposals), `docs/progress/` (session log), `PLAYING.md` (what works).

## Open items
- MP weapons: fixed in P341 (sigs.py dropped zeroext on rewritten calls), proven online in 2-player Bunker
  (netmp_bunker.sh). event_query_world_object fixed in P343 (it was converted with
  six mistakes, see P343).
- Online multiplayer: phase 1 done (P338 + P339, docs/design/ONLINE_MULTIPLAYER.md §8, §9): 2-player lockstep over
  WebRTC with copy-paste codes, Online panel (option "Online multiplayer (experimental)"), time sync, automatic input
  delay, hidden page ticks from a Worker, desync report. Phase 2a done (P344, §10): 2 to 4 players, full mesh with a
  host relay for guest pairs that cannot connect, copy-paste only with the host (star signaling for the mesh), the
  signaler is an interface (N.signal payloads) ready for room codes, lost players stand still for N players (also the
  host). Tests: netpair.sh (PLAYERS=2..4, NETFAIL=A-B, NETSIM_*, LEAVE, UI, PADS=netmp_bunker.sh NET_BUNKER_PLAY /
  NET_BUNKER_DEMO). Phase 2b done (P345, §11): room codes (Create room / Join room) through the Netlify Function
  /api/room on Netlify Blobs (source port/web/netlify, shipped by deploy_web.sh from ~/conker-netlify-fn), manual
  copy-paste codes under "manual codes"; local tests use tools/port/scripts/roomserver.mjs (netpair.sh ROOM=1), never
  the production function. Next: a real multi-machine internet test; maybe a host "kick" for a stranger in the room.
- Globals not renamed: 562 D_ symbols only declared in conker/include/variables.h (no C use), D_ names that appear
  only in tables / comments, ROM-offset symbols < 0x10000000, and D_ names inside log strings (kept so the wasm stayed
  identical). Some descriptions note wrong declaration comments or US/EU alias pairs (`_alias`) worth merging later.
- port_cdata name strings (n64mem_tab.c) still print the original D_ names (n64mem.py, RENAMED_FROM).
- P350 found: the game depends on the static memory layout. HEAD + 512 unused bytes of bss in gfx_f3dex2.o (shifts
  n64_rdram by 0x1000; an 8 MB shift only changes 1 pixel) changes the title menu's character shading and the MP game
  (camera / positions after the 4-pad script). Same build = same behaviour (online is safe), but any static change makes
  "identical to HEAD" checks fail on those scenes. Suspect a wasm pointer masked with 0x7FFFFF / KSEG and re-mapped
  through the n64_rdram mirror. Repro: port_work/p350/headcmp (menu_v12 vs menu_head).
- Single-retrace H blips in ?nethash runs (non-netdet) differ run to run, with or without options; netpair (netdet) shows
  none. Not explained.
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
### P350 (port-web, 2026-10-28): feature #15 Widescreen without bars (+ option Full-resolution picture)
- 36d94dd7 option "Widescreen" (widescreen; page-side, renderer port_gfx_widescreen in gfx_f3dex2.o = outside the online
  hash; in Modern). Canvas = the stage's / screen's aspect (4:3..64:27), 480 rows (?canvas=WxH fixes it). Renderer ws_*:
  N64 picture centred (ws_x2d); perspective draws: clip x / k, viewport k times wider around cx + (centre - cx) * k
  (full-screen views keep every N64 point, split views get their share), G_CULLDL +-k w, scissor mapped likewise (edges
  within 4 px of the screen edge -> canvas edge). 2D: centred 4:3 layout; untextured fills on the screen / view edge and
  per-canvas-pixel full-frame copies (P335 ghost, P349 pause snapshot, now also without hires2d) reach the canvas edge.
  HUD anchors: game C calls port_ws_hud_anchor(gdl, edge) (#ifdef PORT, no game memory change) around hud_health_draw
  (left), air meter + bubbles, cash counter (right); render_player_hud = tag 3 (a player's fades / tint / scope follow
  the widened view). MP per-view HUD (mp_hud_draw_views, text queue) stays centred.
- Logic vs render visibility: objects_update_visibility / obj_update_visibility (camera_view_test_sphere with the 4:3
  planes) gate the whole object update (game_eu_78230.c +0x2FA), animation, fades and model matrices: game state, kept at
  4:3. World records (world_records_build_visible) too. Render-only culling widened without game memory change: wrappers of
  level_dl_visibility_filter and (new) mesh_dl_cull_copy run a wide copy (zoom factor / k) into ws_arena, re-run the
  game's call (same output + vis bytes / zone bits), restore the stack bytes (WS_SCRUB); gfx_run_dl substitutes the copy
  (hash-validated ws_sub entries, dropped after the task).
- gfx_run_task stack scrub (GFX_SCRUB 64 KB, ?p350noscrub=1): the renderer runs on the RCP scheduler fiber, whose whole
  stack is hashed (S) and whose dead bytes game C may read as uninitialised locals; restoring them makes render options
  invisible to game state. noinline body (an inlined body put its frame above the saved SP: S differed).
- Proof: nethash warp 0x29 (moves + pause, 1120x480 + anchors) on vs off: equal except single-retrace H blips, which two
  identical off runs show too (p327/p350fA, fB, fB2); netpair p327/p350_net guest widescreen 854x480, menus -> 4-player
  split screen: 17943 retraces IDENTICAL. Off vs HEAD (p350/headcmp): hud / legal / pause / pause+hires2d identical;
  title menu (34352 px, character shading) and MP (game diverged) differ, exactly as for HEAD + an unused 512-byte static
  in gfx_f3dex2.o (menu_v12): see Open items. check.sh GREEN, hold-L 5789 / 0x29 at 5795, no traps.
- Evidence port_work/p350: a/ (first shots, 21:9), b/ (hud_ws anchors, cut4900/5400/5700/6400/7600 intro + throne
  cutscene, wake6200 ghost blur, wake6700 speech bubble, aim_ws/43 crosshair, photo_ws_2x 1708x960, mp_ws split), shots.sh
  (ws vs 4:3 batch), headcmp.sh, hashcmp.py.
- eb0a257a option "Full-resolution picture" (fullres, page-side, in Modern): canvas = CSS box x devicePixelRatio (<= 2560
  x 1440), ResizeObserver on the stage; P161 write-back of canvases > 1280x960 now via a GPU downscale (was skipped:
  stale pause background). c/pause_1600.png, c/fullres_pause.png.
- Limits: characters, world props and some effects just outside the 4:3 view pop in at the sides (game logic does not
  update them either); sky box faces culled by the game's 80 / 95 deg test may leave the far corners empty at 21:9 (not
  seen); MP per-view HUD at its 4:3 place inside each wider view; letterbox bars not reached in a test (full-width
  fills, so they extend).
### P349 (port-web, 2026-10-28): feature #16a Hi-res menus and 2D
- 11199590 option "Hi-res menus and 2D" (hires2d; page-side, calls port_gfx_hires_2d in gfx_f3dex2.o = outside the
  online hash, so each player's own choice; in Modern). Cause of the soft / offset 2D: texture rectangles sampled
  s(x) = s + dsdx (x - ulx) per canvas pixel (the RDP's top-left-corner rule), i.e. half a texel shifted, blurred to
  the right / down, and the outer half texel of each tile read past the N64's samples (tile seams: GAME 1's "E").
  On: s / t - ds / 2 (canvas pixel centre = N64 pixel centre), rect_hires_axis clamp to the sampled range unless the
  tile goes on by <= 1 texel (image_draw_tiled borders, clamp edge), shader uRHi 1 = 4-tap bilinear, 2 = crisp point
  texels (copy mode / G_TF_POINT). Pause screen: zsnap_take snapshots the fbc canvas copy the pause copies into the z
  image; z-image reads sample it via hx kind 3 (P335 uHiRes); ends on other draws into the z image / depth writes /
  canvas resize. Offscreen N64-size images unchanged, 3D unchanged. ?p349log=F texrect log.
- 3462d4b0 test aids: ?canvas=WxH, audprobe cshot step / PROBE_CSHOT, tools/port/scripts/cshot.sh (frame at a retrace
  via ?nethashstop, pixel-comparable), pngtool.py diff / crop. port_work/p349/shots.sh = the evidence batch.
- Evidence port_work/p349/ev (1280x960: menu, hud, legal, pause, mp _0/_1 + z_*.png crops), p349/b text6650_* (speech
  bubble, hold-L route + autopilot, box opens at retrace 6581), p349/ev640, port_work/p327/p349_photo (2x PNG with hi-res
  HUD). Off = HEAD pixel-identical; gfx CPU ms unchanged (p349/perf); netpair p327/p349_net guest on 11433 IDENTICAL;
  check.sh GREEN, hold-L 5789 / 0x29 at 5795, no traps.
- Found: the pause frozen frame was ~25 % darker than the frame (three RGBA5551 truncations); with the option it keeps
  its colours (off path unchanged). A canvas read at 1920x1440 on the title menu hangs headless Chrome (Metal);
  1280x960 works. ?warp=29 has no Birdy dialogue (needs the route's event state).
- Limits: 2D drawn with triangles (3D-model HUD items such as the health chocolate and the pause screen buttons) is unchanged (3D path);
  tile joins of borderless tiles show a step instead of a ramp over half an N64 pixel; G_TEXRECTFLIP still drawn
  unflipped (as before); the canvas stays 640 x 480 for players (a resolution option would show more of the gain).
### P348 (port-web, 2026-10-28): feature #22 Photo mode (+ audio HLE fix)
- a576c66c fix: aud_dram (port/audio/aud_abi.c) gave 24-bit audio operands a fixed 0x10 top byte; since P337's 12 MB
  fiber pools moved n64_rdram to 0x11711000 they pointed into the unused pools: ADPCM codebooks read as zeros, loop /
  voice states (ADPCM, RESAMPLE, ENVMIXER, FILTER) kept outside game memory. Now the top byte that lands in n64_rdram.
  HEAD vs fix: camera / positions identical, PCM differs (rms 22->29, 64->134, 62->113 in the first 1 s blocks),
  audprobe PASS. Online determinism was not affected (same wrong place on both peers).
- dba56ce1 option "Photo mode" (photomode, PORT_OPT_PHOTO_MODE 16; not in the presets, like Online). P / pad Back /
  Photo button. port/ultra/pc_photo.c: snapshot of the hashed game state (pc_nethash.c port_state_save/restore/hash:
  static region minus conker_netx.txt + live fiber stacks, 11.4 MB; the page now always loads conker_netx.txt); photo
  mode on = frame() runs no game retraces, clock held (pc_os.c port_photo_clock); a photo frame = restore + retraces in a
  sandbox until the game drew a frame built with the photo camera (photo_camera_apply in world_update at start and after
  camera_update_all: view mtx both buffers + roll + camera record eye/at/dir + zoom via camera_projection_update, then
  camera_matrices_refresh_all, so visibility / level culling / LOD follow) and no HUD (game_frame_step, render_overlay_pass);
  no sound / rumble / EEPROM callback / padrec / nethash lines from the sandbox; exit = restore again. Start pose from
  g_view_mtxf[0] (any camera: cutscenes work). 2x PNG: canvas buffer enlarged + port_gfx_resize + port_photo_render.
  Page: photoPoll (pad 1 drives the camera, A save, B reset, L HUD, Start/P exit; held inputs masked after exit),
  overlay #photo, toast, audio suspended. padf cursor can step back (pc_pif.c).
- 1d5e3740 test aid: audprobe.js MS:png:PATH. In the feature: ?photoat=F (first possible retrace from F), ?photofor,
  ?photomove=FWD:RIGHT:UP:YAW:PITCH:ROLL:ZOOM, ?photolog, ?photonodraw, ?photoscale, window.__photo.
- Evidence (port_work/p348/evidence: normal frame, photo start without HUD, up + look down, zoom + roll, HUD toggled,
  saved 1280x960 PNG, after exit, cutscene PNG of Conker on the throne + sheet; runs port_work/p327/p348_*):
  ?nethash A (photo pause at 700, 150 moving frames) vs B: hash at exit = entry, game camera after = start pose, H equal
  for 2132 retraces after the pause except 2 single-retrace blips (B vs B2 of identical runs: 6 such blips = harness
  noise), S differs only by renderer dead bytes on the RCP scheduler stack (fixed-pattern overwrite after gfx tasks
  made A = B in H and S; temporary test, not committed). Option off vs HEAD (+fix): camera, positions, PCM identical.
  netpair p348_net 2p with ?opt=photomode:1: session photomode=0, 7445 IDENTICAL. check.sh GREEN, hold-L 5789 / 0x29 at
  5795, no traps.
- Lessons: a test-flag static in a hashed object (pc_os.o, aud_abi.o) changes the hash by its value (keep experiment
  flags in pc_photo.o, excluded); a malloc'ed URL string shifts the heap and so the fiber stack addresses (hash);
  exports that switch fibers (port_photo_render) return unreliable values to JS (asyncify).
- Limits: photo frames are the game's next frame from the frozen state (one step on); the frame-blend ghost (hangover
  blur) blends with the frozen frame's ghost image; no wall collision for the photo camera (3000-unit range);
  single player only; touch has no dedicated button (header Photo button works); ~7-30 ms per photo frame redraw.
### P347 (port-web, 2026-10-28): feature #19 Free camera
- 14fd1c2f option "Free camera" (freecam, PORT_OPT_FREE_CAMERA 15, PORT_OPT_COUNT 16 -> 24; not in Modern: a control
  choice). Single player: right stick / IJKL / mouse (pointer lock) turn yaw (130 deg/s, +0x37C, so Conker steers by
  it) and pitch (eye on the circle through the N64 eye, elevation -10..70) of the follow camera (mode 1 / 0x800,
  free_camera_update in camera_follow_mode_update; hooks in camera_update_eye_orbit / camera_update_eye_height).
  Walls: the N64 placement code after it (ray casts, freecam_auto_update, eye collision). Hand-back:
  free_camera_allowed (MP, cutscene, pause / snap, not follow mode, look / aim, swim, ride kinds, scripted requests
  other than 0 / 4 / 0xB / 0xD). Input: page -> port_cam_state; pc_pif.c gives the stick to the camera while engaged
  (2-read time-out), else C bits as before (no C until centred after a hand-back). Inputs CAMZOOM (U / L3) and CAMBACK
  (O / R3) = C-up / C-down with the option. ?padf F:BTN:X:Y:RX:RY. Online: forced off (page + port_net_on).
- cc55a3c4 test aids: warp.sh STEPS (keys / click / eval steps), audprobe.sh PROBE_WEB (serve another build dir),
  tools/port/scripts/shots_gif.py (GIF + contact sheet in pure Python). In the feature: ?freecamlog=N, ?p347mouse=1.
- Evidence (port_work/p347, p327/p347_*): off vs HEAD build (port_work/p347/web_head) 213 camera frames identical
  (cmpn_head2 / cmpn_off2); on without camera input identical; new game, stick held from 4500: 1738 camera frames
  identical to off through the opening + wake-up cutscenes, first difference 6957 = free camera takes over
  (cs_on / cs_off); evidence/show.gif + show_sheet.png (360 orbit, look up, top view, C-down recentre),
  wall29_*.png (rock wall), corridor1e_sheet.png (level 0x1E corridor), look29_R_look_view_game_camera.png,
  fixed13_* (level 0x13 pivot camera mode 0x40: stick = C-right, camera unchanged), mouse 600 px = 72 deg, keyboard
  L / I / O; netpair p347_net 2p with ?opt=freecam:1: freecam=0, 5941 identical. check.sh GREEN, hold-L 5789 / 0x29
  at 5795, no traps.
- Seen, not this feature: ?warp=2A traps on the HEAD build too (memory access out of bounds at retrace 38).
- Limits: swimming hand-back only checked in the code (no test route reaches water); ?padrec does not record
  the camera stick; camera_follow_mode_update called twice in one frame (camera restore event) applies that frame's
  input twice; headless Chrome gives no pointer lock (mouse tested through ?p347mouse).
### P346 (port-web, 2026-10-28): feature #4 Classic / Modern / Custom presets
- 5a067a1c page-only (main.js, index.html; conker.wasm unchanged): segmented selector at the top of Options.
  Classic = every option off, volumes 100 %, hold-L skip kept on (its default; a fresh browser is Classic). Modern =
  Classic + skipintro, saveicon, healthhud, cashhud, airbar, crosshair, conkerlod, rumble (off on purpose: longbreath,
  longspin = easier; toggles, swiminvert = taste; nodrunk = story effect). Custom = anything else; 'online' is not in
  the presets. All option changes now go through setOption (presets use the same path as a click); 'opt.preset' saved
  ('custom' after any manual change). Online: at session start the panel shows the host's game options + preset,
  disabled. Test aids ?preset=, ?panel=options, netpair.sh HOSTQ / GUESTQ.
- Evidence (port_work/p346): panel/1_fresh (Classic) 2_modern 3_custom 4_reload_custom 5_classic 6_reload_classic
  (state + localStorage evals in panel/out.txt); game_modern/s_36s.png level 0x29 with health pieces + $0 after
  clicking Modern then Start, game_classic/s_36s.png none; preset/guest_45s.png online guest (fresh store) shows
  Modern greyed, guest log "session options (the host's), preset modern", 2961 retraces identical; preset_classic
  2459 identical. check.sh GREEN, hold-L 5789 / 0x29 at 5795, no traps.
- Seen, not a preset issue: the MP "GAME 1" screen says INSERT RUMBLE PAK with rumble on or off (original screen).
### P345 (port-web, 2026-10-28): online multiplayer phase 2b (room codes)
- 6ef0d56f Netlify Function /api/room (port/web/netlify/functions/room: core.mjs logic, room.mjs on Netlify Blobs
  store conker-rooms): create / join / host poll / offer / guest poll / answer / close; 5-char codes without
  ambiguous characters, slots 2..4 in join order (etag compare-and-swap), host secret + guest tokens, build / ROM
  refused at join, 10 min expiry, delete on Start, size checks, light per-instance rate limit. 885c8a8f net.js
  N.roomCreate / N.roomJoin (same N.signal payloads, 1 s polling, stops when connected / started). 523c2e58 panel:
  Create room (big code + Copy + joined players), Join room (code field), copy-paste under "manual codes".
  eb7063b8 + fix: deploy_web.sh ships the function (deploys from ~/conker-netlify-fn: from ~/conker-site the bundle
  lacked @netlify/blobs). 2c17d91d tests: roomserver.mjs (+ --selftest, 20 cases), netgroup.js ROOM / ROOMCHECK /
  ROOMMAX / ROMFILE, netpair.sh ROOM=1.
- Evidence (port_work/p345, Bunker via the real MULTI route): room2 2p 7952 identical (guest_150s.png), unknown code +
  full room messages; room4ui 4p through the panel 9908 identical (host_10s.png = room code + 3 joined, guest4_190s.png
  4-way split); room4ui2 10352 identical; regression pair2manual 2p copy-paste through the panel + netsim 7929
  identical; room2final 2p UI 2926 identical. Production (prod2): 2 headless pages on conker-web-port.netlify.app,
  room VYXPK, create 4 s (cold), join 4.1 s, unknown code and full room refused, 2402 identical retraces, room deleted
  on Start (later join: unknown); curl: build mismatch refused, close works. check.sh GREEN, hold-L 5789 / 0x29 at
  5795, no traps, conker.wasm unchanged (75b5431b).
- Left: real multi-machine internet test; no kick button (a stranger guessing a code could take a slot before Start);
  a guest whose host link fails keeps its room slot; rate limit is per function instance.
### P344 (port-web, 2026-10-28): online multiplayer phase 2a (3 to 4 players: mesh, host relay, star signaling)
- dd7c6c05 net.js for 2 to 4 players (design §10): host = player 1, each offer names a guest slot 2..4; signaling
  interface N.signal {offer, answer, accept} on payloads {t, ch, sdp} (copy-paste codes wrap them; room codes plug in
  there next); after a guest's link to the host is open, the host forwards the guests' mesh offers / answers over
  'ctl' (star), guests report links + pings, the slowest pair sets D, per-guest config. Mesh: per-receiver packets,
  direct or relayed by the host (type 4) when a guest pair has no direct link; per-pair time sync / hash check /
  desync report; lost player: coordinator (host, else lowest remaining) collects held inputs, fixes F, everyone
  port_net_drop(ch, F). Panel: per-slot boxes, Invite another player, Start the game (N players), per-player pings.
  ?netfailto=P test aid. pc_net.c needed no change (4 channels since P338); conker.wasm unchanged.
- d70a52c1 tools/port/scripts/netgroup.js (was netpair.js; 2..4 windows), netpair.sh PLAYERS / NETFAIL / NETSIM_GUEST3/4
  / LEAVE, netmp_bunker.sh pads 3-4 join (5320 / 5340) + NET_BUNKER_PLAY. d223e7e2 fix: 'drop' frame field renamed
  neutralFrom ('from' = sender, guests dropped from 0). 00a3f949 panel: hide invite/start row after start (.row
  display beat [hidden]). 37283179 mesh wait re-checks on 'in' open (start 9 s -> 1 s).
- Evidence (port_work/p344, real MULTI route into Bunker): 3 players 7928 identical (b3a); 3 with netsim + P2-P3
  relayed 100 %, P2 leaves, 9941 / 10687 identical (b3relay); 4 with netsim + P3-P4 relayed 100 %, 9907 identical
  (b4relay); 4 through the panel buttons, netsim on all, relay, 99.6 %, 13173 identical, P4 leaves (b4ui); final code
  4 + netsim + P2-P4 relayed 98.9 %, 8812 identical (b4final); host leaves a 4-player session: P2 coordinates, guests
  identical (hostleave4). Screens: b3a/guest3_150s.png (3-way), b4relay/guest4_190s.png, b4ui/host_240s.png (panel
  slots + relay), b4ui/guest3_150s.png. Regressions: 2-player UI + 40 ms 5 % netsim 100 %, 8428 identical (pair2ui);
  Bunker weapon demo 7458 identical, P2 holds the weapon (bunker2demo/guest_140s.png). check.sh GREEN, hold-L 5789 /
  0x29 at 5795, no traps. No desync anywhere.
- Left: room codes (phase 2b), a real multi-machine test, host loss breaks relayed guest pairs (dropped after 5 s, a
  partition could make two coordinators), no late join / reconnect.
### P341 (port-web, 2026-10-28): MP weapon pickups fixed (root cause in the port's signature tool)
- Who gives the weapon: event_action_rail command 11 = rail_weapons_update (game_eu_B7840.c), run every game frame by
  the MP level script. Pass 2 finds each pickup slot's world object with world_record_find((u8) +0xEF0[i]) (0x3001..
  0x3010 -> ids 1..16), counts its respawn / hide timers and, when pickup_update wrote the taker (+0x80 = player + 1),
  links the slot to that player (+0xEB0[r]); pass 1 then arms the player: context_action_lock -> pad kind = weapon |
  0x80 (Bunker slots: 0x24 0x23 0x16 0x22 0x16 0x15 0x39 0x18 0x14 9 9 0x21 0x23 0x37 0x8AE 0x8AE; 0x8AE = +3 grenades),
  B draws it (player_item_action -> player_try_begin_action), obj_setup_run gives the model while drawn. P340's ROM
  scans missed it because the records are reached through world_record_find, not g_world_objs (whose EU address is
  0x800DC324; the `was D_800DBEF4` comment is the US name).
- Bug: game_eu_B7840.c declares world_record_find(s32), the definition takes u8. port/tools/sigs.py rewrote the call to
  the canonical i8 but dropped the definition's zeroext; wasm leaves the extension to the caller and LLVM folded the
  (u8) cast away, so the callee compared 0x300B with the id byte: never found, timers frozen at 1, taker never read.
- bb60d4ed fix: sigdb entries keep ret / param zeroext / signext of narrow ints, rewritten calls + declares carry them,
  extension-only mismatches are rewritten (1 site), narrow zeroext results widen with zext; 770 rewritten call sites
  now extend narrow args (sprite2d_spawn 43, collision_floor_probe 33, mdl_particle_spawn 30, text_printf_at 23,
  obj_send_hit 18, sound_pick_variant 18, world_record_find 7, ...), so other subtle bugs may be gone too.
  vbe_build.py re-runs phase 2 when sigs.py changes (before, a sigs.py edit kept the old sigdb.json).
- Proof (offline, real Multi menu route, port_work/p340/dm_pads2.sh + run.sh, ?p340 + teleport): pickup 22 taken at
  6209, taker cleared by the slot code, pad kind 0x89 from 6249; B at 6400 -> item kind 9, phase 2, two guns in hand
  (port_work/p340/p341i/s_130000ms.png, s_134000ms.png). Z firing not separately measured (shots counter added to the
  ?p340 log afterwards). Before the fix: same route, pad kind stays 0.
- 7e6194f0 test aid: ?p340 logs the rail weapon slots ([p341]) and shots; ?p341b=F begin-action conditions.
- Checks: check.sh GREEN, hold-L 5789 / 0x29 at 5795, no traps; netpair (Total War, 180 s) IDENTICAL 8941 retraces,
  100 % speed (no pickup taken in its random play, port_work/p340/p341pair).
- Online proof (part 2): pad 2 never joined Deathmatch because the route pressed its Start at 5751, on page 5 after
  the join page (menu_player_join_page = main page 4, full alpha 5125 .. 5613; found with ?p341m=1); not a port bug.
  ae9cfc92 tools/port/scripts/netmp_bunker.sh (pad 2 Start at 5300; NET_BUNKER_DEMO=1: player 2 runs onto pickup 20,
  weapon 0x14, B at 6500, Z every 60 retraces) + netpair.sh PADS=FILE. Online run
  `NETDIR=p340 PADS=tools/port/scripts/netmp_bunker.sh NET_BUNKER_DEMO=1 netpair.sh p341bunker2 150`: split-screen
  Bunker, IDENTICAL 7502 retraces, player 2 has the weapon icon and fires (port_work/p340/p341bunker2/guest_140s.png;
  guest_142s.png holding it). Same pads offline with ?p340 (port_work/p340/p341off): pad kind 0x94 at 6365, item 0x14
  phase 2 at 6573, shot counter (ctl +0x1AA) 1, 2, 3, 4, 5, 6 for the Z presses. e1c7a791 probe ?p341m=1.

### P343 (port-web, 2026-10-28): event_query_world_object fixed (wrong conversion, 6 mistakes)
- event_query_world_object (game_eu_CC5F0.c, 0x1509F254) = g_event_query_fns[2]: event script queries on world records
  (ids 0x3xxx). Checked against the ROM disassembly (objdump of the romimage.py image) and its jump table at 0x8009F80C
  (cases 19..35). The old C: (1) returned u8, but the ROM returns the full word and event_native_query passes it on as
  s32 -> case 23's 0x2000 marker, case 26's word, the sign of 29..31 (s16 coordinates) and all values > 255 were cut;
  (2) case 34 read +0x7C and +0x84 as s32 (ROM: lwc1 + trunc.w.s on all three fields); (3) case 33 field 1 returned the
  first byte of +0x80 (ROM: lw of the word); (4) case 19 is world_record_touched_by(rec, -1) and (5) case 20
  touched_by(rec, obj_slot_by_spawn(args[2] & 0xFFFF0FFF)), both ran case 21's loop instead; (6) the case 21 loop
  stepped a struct127 pointer by 0x32C elements (ROM: 0x32C bytes = one object). Rewritten as readable C, s32 return,
  locals renamed (`was` comments).
- +0x7C/+0x80/+0x84 is an f32 triple set by event_action_world_object 3 (16.16 fixed) / 4 (raw bits); query 33 returns
  the bits, 34 the truncated values. Which level script uses which subcase was not found: scripts are asset group 20
  (event_load), not decoded statically; a runtime log in event_native_query (n == 3) would answer it.
- difftest: plain --self is blind (record never found); with DIFFTEST_ROMDATA=1 DIFFTEST_ARG=1=12..24,2=80200000
  DIFFTEST_POKE=80200008=0/1/2 DIFFTEST_RET=15114F2C=80180000: new EQUIV 200 trials each; old C DIFFER (case 34 f0
  ref 0x0 cand 0x2; 21 / 19 / 20 call arguments / callee differ). Old candidate in port_work/p343/old_CC5F0.c.
- Checks: check.sh GREEN, hold-L 5789 / 0x29 at 5795, no traps.

### P342 (port-web, 2026-10-27): source-level debugging (DWARF debug build + CLion compile_commands.json)
- `tools/port/scripts/debug_build.sh` [build|serve|stop|cc]: rsyncs conker/ + port/ into port/build-dbg/tree and runs
  the normal `make -C port game web` there with `PORT_DBG_CFLAGS` (`-g` + `-fdebug-prefix-map` from the container path
  /src/port/build-dbg/tree to the worktree host path; srcfix copies map to conker/src_eu) and `PORT_DBG_OPT` (-O0).
  port/Makefile (PC layer -O0 -g, link -g) and port/tools/vbe_build.py (C -> IR with -g, object at -O0 -g) read them;
  unset = release, flags and keys unchanged. Full debug build ~1 min, 21 MB wasm, server on 127.0.0.1:8077 (ROM via
  ?romurl like audprobe.sh). `DBG_REV=HEAD` builds a commit (someone's WIP may not compile), `DBG_NOSYNC=1` skips the copy.
- vbe.py with -g IR: the `$`-anchored IR regexes (k0_*, rcp_io, icall LOADP/STOREP) accept a `, !dbg !N` suffix and keep
  it; `!dbg` attachments of globals go after the align; `dbg_calls` gives calls the passes create a location (else the
  verifier drops the TU's debug info); `dbg_lanes` adds DW_OP_plus_uconst 3 / 2 to scalar 8 / 16-bit locals, params and
  globals (vbe lanes), so they display right. Debug-only (`PORT_DBG_CFLAGS`): `dbg_div` (variable-divisor div/rem ->
  helper with R4300 divide-by-zero results; -O0 ran screen_fade_alpha's fakematch dead `/ d` and trapped) and an -O1 -g
  fallback for game_EF410.c (wasm backend: "Function addresses with offsets not supported" at -O0).
- Verified: every vobj with code has DWARF (14 without are empty TUs); 843 CUs, 6903 functions, 46727 / 47041 variables
  with a location; player_try_begin_action -> /Users/sorikairo/conker-wt/web/conker/src_eu/game_eu_90F50.c:295, `arg3`
  (s8) at fbreg+28 +3; headless Chrome ?warp=29: gameplay level 29 at frame 38, no traps, ~12 frames/s at det=2; a CDP
  breakpoint at DWARF low_pc + code section offset pauses in screen_fade_alpha (caller screen_fade_is_opaque), so the
  addresses survive binaryen's ASYNCIFY pass. compile_commands.json: 766 TUs (722 game, 9 port game-side, 35 PC), host
  clang --target=wasm32-unknown-emscripten -fsyntax-only clean on a 22-TU sample.
- Release unchanged: an isolated release build of HEAD (port/build-dbg/relcheck) and of HEAD + this commit's tooling
  give the same conker.wasm md5 3bf13ec0c5b3408681f846e8b7c43ff2 (census 722 / 0 FAIL); old vs new vbe.py on all 731
  release .ll files: byte-identical .v.ll + .isig. check.sh was not run in the worktree (P341 was building in
  port/build); implicit_scan 0 NM+float, romabs 0 FAIL; census + build ran in the isolated tree. The tooling change
  makes the next release `make` re-run phase 3 of vbe_build once (tool hash), same objects.
- Limits (DEBUGGING.md): sub-word struct fields / arrays display lane-swapped (read with Module.HEAPU8[a ^ 3]); s64/f64
  halves swapped; N64 0x80xxxxxx addresses = &n64_rdram + (a & 0x7FFFFF); asyncify fibers make step-over of yielding
  calls jump threads. player_try_begin_action is not hit by a plain jump (held item / context B action).
### P340 (port-web, 2026-10-27): MP weapon pickup investigation (user report: no weapon after a pickup online)
- Reproduced offline: Deathmatch = "Bunker", level 0x34 (P1 menu: as netmp_pads.py up to the skull list at 4700, then
  stick down at 4900, Start at 5100; gameplay 5947; the route flaked once in ~12 runs). Probe b1020ef9 ?p340=F
  (p340_probe, per retrace from __wrap_objects_run_state_handlers; ?p340tp=I+1&p340tpf=F teleports P1 onto pickup I):
  Bunker has 16 floating pickups (world objects with update pickup_update, kinds 0x39 .. 0x5E), no type-11 (B pad)
  zones, objects: P1 type 0x80, P2 0x75 (idle 2nd pad), 0x8A. Teleport onto pickup 22 (kind 0x39): state 2 -> 3,
  taker +0x80 = 1, gone; the other player took pickup 21. Control block (+0x31C) bytes after the pickup: nothing
  weapon-like changes (pad kind +0x75, item kind +0x78, fallback +0x7C stay 0 for both players for minutes); no event
  action, no obj_setup_run. Same in Total War (0x2D). Logs port_work/p340/dm2, dm4, dm6, dm7; Total War p340/b, c.
- N64 logic read from the code: pickup_update (= ROM: same calls and stores) only sets taker +0x80, plays
  pickup_collect_sound_play and hides itself. ROM scans (port_work/p340/*.py): nothing in .game reads a world object's
  +0x80 together with +0x54 / +0x6E, nothing references pickup_update's address, nothing reads g_world_objs + 0x54.
  Held weapon = ctl item_kind (+0x78), set by player_try_begin_action from pad_kind (+0x75) or the fallback +0x7C when B
  is pressed (obj_ctrl_action_update). Writers: +0x7C only event action 0x7E (event_action_object); +0x75 only
  context_action_set (zone type 11), context_action_lock (event actions 0x26 / 0x27, race) and resets. In MP with a
  weapon kind 0x18 / 0x41 / 0x23 / 0x24: R = aim (aim_state), Z = fire (player update, game_eu_78230.c ~1832); C-down =
  grenade in levels 0x2D / 0x30 / 0x34 / 0x1A / 0x3F (ctl +0x19A count); B melee is disabled in 0x2D / 0x2B / 0x30 /
  0x34 (player_context_action). So the hand-over must be an event script action (0x7E / 0x27) or code not found yet;
  the Bunker / Total War scripts (p174ev) never query the pickups or run 0x7E / 0x27 / 0x26.
- Controls: the page's gamepad already maps the right stick to all four C buttons (main.js gamepadPad); no page bug.
  PLAYING.md: MP controls + known problem.
- Checks: check.sh GREEN, hold-L 5789 / 0x29 at 5795, no traps; netpair 170 s IDENTICAL 8419 retraces. Not fixed.
  Next: find who gives MP weapons (ideas: per-character weapon setup at character select / spawn, the MP level
  script's world-record actions 30F3..30FF at spawn, a stubbed or wrongly converted MP game-mode function; compare
  with an emulator run of the ROM if one becomes available).
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
