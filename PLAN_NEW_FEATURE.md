# New features

Every feature has its own Options toggle, off by default unless noted, and its own commit.
The source list is the ConkerBFDReloaded comparison (2026-10-26). Agent brief: `AGENT_NEW_FEATURE.md`.

| # | Feature | Status |
|---|---|---|
| – | Hold L 3 s to skip any cutscene (ring) | Done P320/P321, default **on** |
| – | Touch controls, rebinding, save import/export, pause on hidden tab | Done |
| 1 | Autosave icon | Done P324 |
| 2 | Toggle crouch / R-Look / walk | Done P324 |
| 3 | Skip intro | Done P324 |
| 4 | Classic / Modern / Custom presets | Done P346 |
| 5 | Health always visible | Done P325 |
| 5 | Always show cash (pause-screen digits) | Done P325, P330 |
| 5 | Show cash "on change" | Not needed: this is what the original game does |
| 6 | Longer breath (2×) | Done P326 |
| 6 | Longer tail spin (2×) | Done P326 |
| 7 | No motion blur / drunken sway | Done P331 |
| 8 | Conker always full detail (LOD) | Done P331 |
| 9 | Separate music / SFX / speech volume | Done P332 |
| 10 | Underwater air meter | Done P332 |
| 11 | Inverted swimming | Done P333 |
| 12 | Rumble (browser gamepad) | Done P333 |
| 13 | Aiming crosshair | Done P334 (first-person aim kinds without a reticle: 0x18) |
| 19 | Free camera | Done P347 (single player, follow camera; never online) |
| 22 | Photo mode | Done P348 (single player, cutscenes too; never online) |
| 16a | Hi-res menus and 2D | Done P349 (render-only, each player's own choice online; in Modern) |
| 16c | Smooth font | Done P356 (font 0 glyph rectangles: bicubic intensity + smoothstep outline in the shader; render-only, each player's own choice online; in Modern) |
| 15 | Widescreen without bars | Done P350 (render-only, logic keeps 4:3, each player's own choice online; in Modern; + option Full-resolution picture) |
| 18 | High frame rate (interpolated) | Done P351 (render-only replays of the last game frame with interpolated matrices; each player's own choice online; in Modern) |
| 21 | Ledge grab | Done P352: the N64 game already has the move (hang anim 0x42, pull-up 0x40, hop, let go) but only on edges the levels mark (flags 0x0E000000, few levels); option "Ledge grab everywhere" (single player, not in Modern) takes every flat static edge, + Z lets go, + shimmy (hang pose). Found on the way: n64mem relocated the acos table's first word (wrong atan2 near axes), fixed |

## Remaining features: effort (reassessed 2026-10-28)

One session is about 150 tool calls. The estimates take into account what exists now: 14 options, the debug build (`docs/port/DEBUGGING.md`), the canvas-resolution path from P335, and 2–4 player online play where the host dictates options.

| # | Feature | Effort | Notes |
|---|---|---|---|
| 4 | Classic / Modern / Custom presets | **Done P346** | Page only (main.js, index.html): a preset sets every option but Online; changing any option switches to Custom. |
| 14 | Language selector (skipped by the user) | Small, 1 session | The game already has `g_settings_language` (settings byte 10) and `text_bank_load` reloads text when it changes. Check which languages the EU ROM really has. It is saved in the EEPROM, so online it follows the host's save. |
| 15 | Widescreen without bars | **Done P350** | Option widescreen: canvas at the window's aspect (4:3..21:9); 3D clip x / k with k-times wider viewports (split screen included), 2D centred 4:3, corner HUD (health, cash, air meter) anchored via port_ws_hud_anchor marks, fills / ghost / pause snapshot to the edges. Logic visibility stays 4:3 (it gates object updates); level geometry and mesh culling are widened render-side (wrapper re-runs into a renderer arena, game memory and stack bytes restored). Proof: nethash on = off (harness blips only), netpair guest widescreen 17943 identical. Limits: characters / props / some effects just outside 4:3 appear late at the sides; sky box face culling not widened; MP per-view HUD stays at its 4:3 place. Also option Full-resolution picture (canvas = CSS size x DPR). |
| 16 | Accurate graphics | Split in two | **16a hi-res menus/2D: Done P349** (texture rectangles centred on the N64 pixel, clamped to what the N64 samples, 4-tap bilinear / crisp point; pause frame snapshot through P335's `uHiRes` path). **16b reflections and other missing effects:** unknown; needs a 1-session audit of what differs from the N64 first. |
| 17 | Texture packs | Medium, 2–3 sessions | The renderer already hashes textures (P193). Needed: a stable hash including palette/TLUT, a dump mode, and loading a pack (zip/IndexedDB) in the page. Render-only, so safe online. |
| 18 | High frame rate (interpolated) | **Done P351** | Option hfr: every animation frame redraws the newest game frame's task with each G_MTX interpolated between the previous and the newest frame (key = static model-DL address / segment matrix / anchor DL + occurrence; slerp + lerp, view eye lerp), recorded cull decisions and textures; snaps on camera cuts (view > 45 deg / 1500 units), teleports, fx tasks (blur, pause frame), level loads (DL hash), new scenes. ~1.2 ms per picture. netpair guest on 14942 identical. Limits: 2D, CPU-built geometry (particles, shadows) at game rate; up to one game frame of extra latency. |
| 19 | Free camera | **Done P347** | Right stick / IJKL / mouse turn yaw and pitch of the N64 follow camera (camera_follow_mode_update); the game's own wall collision places the eye; any other camera (cutscene, look / aim, swim, ride, fixed, scripted, multiplayer) runs unchanged and the stick is the C buttons there. Off online (the camera stick is not in the lockstep input). |
| 20 | Twin-stick / mouse / gyro aim, lock-on | Twin-stick and mouse: medium, 2 sessions. Gyro: +1. Lock-on: hard, 2+ | Aim kinds are known (P334, P341: R aims, Z fires). Mouse needs aim angles written directly, because the N64 stick is 8-bit. Online it must go through the input stream, so mouse aim needs extra input bytes in the netcode. |
| 21 | Ledge grab | **Done P352** | Not a new move: the N64 already catches, hangs, pulls up, hops and lets go, but only on triangles marked as ledges (flags 0x0E000000: e.g. level 1, none on 0x29). Option ledgegrab: collision_ledge_probe takes unmarked static triangles for single-player players (not world objects), unmarked edges need a wall push this frame, the floor 150+ below and Conker not under the triangle; Z lets go, stick left / right shimmies with the game's own probe (stops at ends / corners / walls). No shimmy animation (hang pose slides). |
| 22 | Photo mode | **Done P348** | P / gamepad Back / Photo button. Freeze = a snapshot of the hashed game state (P337's region list + fiber stacks); each photo frame restores it and lets the game build the next frame with the photo camera written into the view (so culling and LOD follow it) and no HUD; leaving restores it again (nethash identical to a run without the pause). PNG at 2x the canvas. Not in the presets (a tool, like Online). Off online. Found on the way: the audio HLE read voice states / ADPCM books from the wrong memory since P337 (fixed). |

Order chosen by the user (2026-10-28): 4, 19, 22, 16a, 15, 18, 21. 14 skipped.
