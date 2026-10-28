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

## Remaining features: effort (reassessed 2026-10-28)

One session is about 150 tool calls. The estimates take into account what exists now: 14 options, the debug build (`docs/port/DEBUGGING.md`), the canvas-resolution path from P335, and 2–4 player online play where the host dictates options.

| # | Feature | Effort | Notes |
|---|---|---|---|
| 4 | Classic / Modern / Custom presets | **Done P346** | Page only (main.js, index.html): a preset sets every option but Online; changing any option switches to Custom. |
| 14 | Language selector (skipped by the user) | Small, 1 session | The game already has `g_settings_language` (settings byte 10) and `text_bank_load` reloads text when it changes. Check which languages the EU ROM really has. It is saved in the EEPROM, so online it follows the host's save. |
| 15 | Widescreen without bars | Medium, 2–3 sessions | Projection (`camera_build_view_matrix` is already wrapped) and culling (`camera_view_test_sphere`). The rest is the work: HUD anchoring, 2D sprites, split screen, framebuffer effects (ghost, lens warp). **Online risk:** `objects_update_visibility` feeds game logic, so a wider view could change what updates. It must be host-dictated, or visibility must stay at 4:3. |
| 16 | Accurate graphics | Split in two | **16a hi-res menus/2D:** small to medium, 1 session, building on P335's `uHiRes` texrect path. **16b reflections and other missing effects:** unknown; needs a 1-session audit of what differs from the N64 first. |
| 17 | Texture packs | Medium, 2–3 sessions | The renderer already hashes textures (P193). Needed: a stable hash including palette/TLUT, a dump mode, and loading a pack (zip/IndexedDB) in the page. Render-only, so safe online. |
| 18 | High frame rate (interpolated) | Hard, 3–5 sessions | Game logic stays at N64 rate; the renderer draws extra frames by interpolating matrices between two game frames. Hard parts: matching objects between frames and detecting camera cuts. Render-only, so lockstep is unaffected. |
| 19 | Free camera | Medium to hard, 2–3 sessions | Previously "hardest": `camera_update_all` and `camera_pivot_follow_update` are wrapped and named, so a basic orbit camera on the right stick is reachable. Hard parts: wall collision, and handing control back in cutscenes and aim modes. The right stick is currently the C buttons, so it needs a mapping choice. |
| 20 | Twin-stick / mouse / gyro aim, lock-on | Twin-stick and mouse: medium, 2 sessions. Gyro: +1. Lock-on: hard, 2+ | Aim kinds are known (P334, P341: R aims, Z fires). Mouse needs aim angles written directly, because the N64 stick is 8-bit. Online it must go through the input stream, so mouse aim needs extra input bytes in the netcode. |
| 21 | Ledge grab | Hardest, 4+ sessions, risky | This is a new move: it needs a fitting animation in the ROM, new player states and collision tests. Recommend dropping it unless an unused animation turns up. |
| 22 | Photo mode | Medium, 1–2 sessions after #19 | Pause the simulation (page pause exists), free camera (#19), hide the HUD, save the canvas. |

Order chosen by the user (2026-10-28): 4, 19, 22, 16a, 15, 18, 21. 14 skipped.
