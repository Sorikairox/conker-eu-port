# Native-feeling menus (plan, P360)

User goal: "make all of our menus and options feel native to the game, rather than added in the webpage". Every
page-added menu, option and panel should end up inside the game's own look, opened from the game's own pause / title
flow (or one key / button), and driven with the pad like the game's menus.

Step 1 is done (P360, commit b7b32847): the game fills the whole window (4:3 centred, letter / pillarboxed; the window's
aspect with Widescreen), and every page control moved into one translucent menu drawer (Esc or the corner button),
lightly styled like the game. This document is the plan for the rest.

## 1. Inventory: what the page adds today

From `port/web/index.html` and `port/web/main.js` (P360 state). "Kind" = how the option touches the game
(WEB_PORT_ORCHESTRATOR.md section 9): **G** game-logic option (game C reads it via `port_option`, host's vector
online), **R** render / page-side option (each player's own, outside the online hash), **T** tool (off online), **P**
page / platform action.

### A. Session and system actions (drawer header)
| Control | Kind | Notes |
|---|---|---|
| Start (and the new Press Start screen) | P | boots the wasm game; one module per page load |
| Pause / Resume | P | page pause (`port_set_paused`); not the game's pause menu |
| Fullscreen (F11, Alt+F, double click) | P | Fullscreen API on the whole page |
| Touch (on-screen controls) | P | stick, A B Z L R, C buttons, Start |
| Photo (P, gamepad Back) | T | freezes the game; photo HUD bottom left + Pose & Outfit panel |
| Volume (master) | P | page gain (`portVolume`) |
| status line / toasts | P | ROM check, running, crashed |
| Debug: console, Scheduler demo, Dump threads | P | developer only |

### B. Options panel (`OPTIONS` table, main.js; presets Classic / Modern / Custom)
| Group | Options | Kind |
|---|---|---|
| Picture | Widescreen, Full-resolution picture, High frame rate, Hi-res menus and 2D, Smooth font | R |
| HUD / information | Autosave icon (page), Health always visible, Always show cash, Underwater air meter, Aiming crosshair | page R / G |
| Gameplay / difficulty | Skippable cutscenes (hold L), Skip intro, Longer breath, Longer tail spin, Ledge grab everywhere, No motion blur / drunk sway, Conker always full detail | G |
| Controls | Toggle crouch, Toggle R-Look, Toggle walk, Inverted swimming, Free camera, Rumble | page (latches) / G |
| Sound | Music / Sound effects / Speech volume (sliders) | G |
| Tools (not in presets) | Online multiplayer, Input recorder, Photo mode | T (they only show a button / key) |
| Presets | Classic, Modern, Custom | P |

### C. Controls panel
Key and gamepad bindings per N64 input (+ free-camera C-up / C-down, Photo), Defaults, connected-pad list, key hint.

### D. Saves panel
Export .eep, Import .eep (reloads the game), status line. EEPROM persists automatically in IndexedDB.

### E. Online panel (net.js, experimental)
Create room / Join room (room code), manual copy-paste codes (Host / Join, offer / answer textareas, Invite, Accept
per slot), input delay (automatic / frames), Start the game, Leave, status / peers / ping info, desync report;
in-game overlay "waiting for the other players".

### F. Input recorder panel
Name, Start recording (reboots), Stop and save, the last 10 recordings (download / delete), REC badge over the game.

### G. Photo mode (in-game overlays already)
Photo HUD (help, info, Save PNG, Exit), Pose & Outfit panel (pose, animation, frame, speed, model, items, face,
materials: hide / texture / tint), toast, flash. Gamepad navigation exists (right stick click = panel focus).

### H. Small game overlays (already over the picture)
Hold-L skip ring, autosave floppy, latch labels, "click to enable sound", PAUSED, REC badge, net wait.

### I. First-run screens
ROM picker (drop zone / file button, privacy note), Press Start screen, "Another ROM...".

## 2. Where each group belongs in the game

The game's own menus (conker/src_eu/game_eu_20B730.c and neighbours):
- **Title menu**: `title_press_start_page` (Conker at the title), `title_slot_page` (save slots),
  `title_chapter_select_page`, `menu_mode_select_page` (multi), `main_settings_page` (the game's **OPTIONS** page:
  `settings_list_draw`, 28 items selected by a mask from `g_settings_set_item_masks`, values `g_settings[i]` with
  min / max, ring or column layout, cursor arrows, value fade, `settings_save` to EEPROM), multiplayer pages
  (`menu_player_join_page`, `main_players_page`, `menu_team_select_page`, `menu_level_start_page`).
- **Pause menu**: `game_pause_update` (CONTINUE / RESTART / QUIT with confirmation, `g_menu_cursor`,
  `g_pause_simple`), with the frozen-frame background.
- Text: `text_printf_at` / `text_set_color` / `text_set_flags` / `text_set_scale`, font 0 glyphs
  (`g_font_textures`, `g_font_metrics`), HUD images (`hud_image_draw`, `hud_tex_rect_scaled`).

| Group | Target | Why |
|---|---|---|
| B Picture, HUD, Gameplay, Sound, Controls toggles, presets | **Title menu OPTIONS page**: a second page "PORT OPTIONS" (or extra rows) next to the game's own settings; also reachable from the **pause menu** as an "OPTIONS" entry for the render options | that is where the game puts its own settings; render options are safe to change mid-game |
| B game-logic options while in a level | pause menu, but changes take effect as today (some at next level / next start); greyed out online for guests | the option vector is the host's online |
| C Controls (bindings) | game-styled overlay page "CONTROLS" from the OPTIONS page | needs free key capture (keyboard / pad), which the N64 menus never had |
| D Saves export / import | game-styled overlay on the title menu (slot page: "EXPORT / IMPORT SAVE") | file pickers / downloads are browser actions |
| E Online | title menu: a new entry next to MULTI ("ONLINE"), as a game-styled overlay page (room code entry with an on-screen keyboard / pad letter picker; status) | the session must exist before the game boots into it; text entry |
| F Recorder | developer tool: stays in the drawer (tools section) | not for players |
| G Photo mode | already in-game; restyle the HUD and the Pose & Outfit panel as a game overlay | keep its pad navigation |
| A Fullscreen, Touch, Volume, Pause | Fullscreen / Volume: OPTIONS page rows; Touch: automatic + a row; Pause: the game's own pause (Start) plus the page pause only for hidden tabs | the page pause button disappears once the game's pause hosts the menu |
| A Debug | stays in the drawer (developer section, behind ?debug=1) | developers only |
| I First run | the Press Start screen stays a page (no ROM yet = no game assets); restyle once a ROM is cached (title art from the ROM) | without the ROM nothing of the game can be drawn |

The drawer stays as the fallback until every group has moved (and later as the developer / recovery menu).

## 3. How to render

Two ways, chosen per group:

1. **The game's own menu code from C** (`#ifdef PORT` additions next to `main_settings_page` / `game_pause_update`):
   a port page appended to the title menu's page table, drawn with `text_printf_at` and the cursor / fade code of
   `settings_list_draw`, items read from a port-side table (label, values, `port_option` id). Most native look (the
   real font, colours, sounds, fades, pad handling).
   Costs: it changes game memory (menu state, text queue, `g_settings_*`) so it is **not allowed online** unless every
   peer runs it in lockstep (see section 5); the game's text strings come from ROM text banks, so new labels need a
   port string table (through the same glyph path, `text_char_to_glyph`; check which characters font 0 has first). Best for
   the title-menu OPTIONS page in single player.
2. **A page overlay in the game's style**: HTML / canvas over the picture, using the game's own font glyphs and menu
   textures read from **the player's ROM at run time** (the port already decodes them: font 0's glyph buffer, HUD
   images). The page asks the wasm for the decoded RGBA (a new `port_asset_*` export, outside the hash), draws
   bitmap text on a 2D canvas layer with the same scale / colour / drop shadow, and plays the game's menu sounds
   through a port hook. **No ROM-derived assets are ever committed or deployed**: everything is decoded in the
   player's browser from their ROM. Never touches game state, so it is safe online and while the game is paused.
   Best for Controls, Saves, Online, photo mode, and the pause-menu options page.

A shared piece for both: a small **menu-model** layer in main.js (items, values, enabled / locked / "takes effect at
next start" flags, presets) that the drawer, the overlay and the C page all read, so the options table stays the
single source of truth (`OPTIONS`).

## 4. Input

- Pad navigation as in the game's menus: stick / D-pad up-down moves, left-right changes values (column layout,
  `settings_list_draw arg1 == 0`), A confirms, B goes back, Start closes; repeat delay like `g_pause_input_delay`.
  Keyboard: the bound keys (arrows / WASD, Space = A, F = B, Enter = Start); mouse / touch: click / tap on rows.
- While an overlay menu is open, pad 1's input goes to the menu, not to the game (photo mode already does this:
  `photoPoll` / `photoMaskAfter`, inputs still held when the menu closes reach the game only after release).
- One entry key outside the game's flow: Esc (and the corner button, and a gamepad button not used by the game, e.g. Home where the
  browser passes it; Back is Photo). Inside the game: an "OPTIONS" row in the pause menu, "PORT OPTIONS" in the title OPTIONS page.
- Focus: keyboard focus back on the canvas when an overlay closes (done in P360 for the drawer).

## 5. Online determinism constraints

- Online and in recordings, game logic must see exactly the same inputs and option vector on every peer. Game-logic
  options are the **host's vector**, fixed at session start (`optionsLocked`); render options are each player's own.
- So during an online session (or a recording / replay):
  - menus must not write game memory outside the option vector: no C menu pages (they write menu state and the text
    queue, which are hashed), no `port_set_option` changes for game-logic options; use the page-overlay renderer
    (section 3.2) only.
  - a menu must not pause or stall the game (the session never pauses; the overlay draws over the running game, pad
    1's input goes to the overlay and the lockstep gets "no buttons" for this player meanwhile, like a dropped pad).
  - render options (widescreen, hfr, hi-res 2D, smooth font, fullres, volume) can change at any time.
  - game-logic options show the host's values, disabled for guests (as the drawer does now: `showSessionOptions`).
- In single player, the C title-menu page is fine (it is the game's own state, like its real OPTIONS page); still keep
  "option off = exact N64 behaviour" and prove a session without the page open is byte-identical (nethash / e2e).
- Test every step with `e2e_replay.sh` (recordings must stay identical) and `netpair.sh UI=1` (IDENTICAL).

## 6. Proposed order of sessions

1. **P361 overlay renderer + font from the ROM** (DONE, commits f23baadd, 89823bde; see "Status" below): `port_asset_font` export (font 0 glyphs + metrics as RGBA from the
   wasm, never saved), a page `GameText` canvas layer (bitmap text, colours, drop shadow, scale), the menu-model layer
   over `OPTIONS`, pad / keyboard navigation module. Restyle the drawer's look with it (titles in the game font).
2. **P362 in-game Options overlay**: a game-styled OPTIONS overlay (pages: Picture, HUD, Gameplay, Controls toggles,
   Sound, presets) opened by Esc / the corner button / a free gamepad button (Back is Photo); drawer keeps the rest. Online-safe by design.
3. **P363 pause-menu entry**: an "OPTIONS" row in `game_pause_update` (single player; `#ifdef PORT`, option-gated) that
   opens the overlay; online the overlay opens from Esc only (never via game memory).
4. **P364 title-menu PORT OPTIONS**: a page in the title flow (beside `main_settings_page`) drawn by the game's C menu
   code for single player, sharing the menu model; proves "off = N64" with e2e.
5. **P365 Controls + Saves overlays**: rebinding with pad navigation and key capture; save export / import from the
   slot page overlay.
6. **P366 Online overlay**: ONLINE entry beside MULTI, room code entry with a pad letter picker, status / peers /
   desync screens as game overlays; net wait / desync messages in the game font.
7. **P367 photo mode restyle**: photo HUD and Pose & Outfit in the overlay style (pad navigation kept).
8. **P368 cleanup**: drawer reduced to developer tools (Debug, Recorder, fallback); touch controls styled; first-run
   screens use title art from a cached ROM; PLAYING.md updated.

## 7. Status

- **P361 done** (option *Game-style menu (Esc)*, key `nativemenu`, default off, not in the presets; port/web/gmenu.js):
  - Font: read from the running game (`port_font_info` / `port_font_glyph` in port/gfx/gfx_f3dex2.c, read-only) rather
    than a separate ROM decode: the game already decoded font 0 from the player's ROM at boot. 95 glyphs, I8 with 16
    levels, upper case + digits + punctuation + Latin-1 accents (lower case maps to upper case). Bytes sit at
    address ^ 3 in the mirror; odd glyph rows carry the TMEM x ^ 4 swap. Pixel look (bilinear, like the N64 picture)
    or smooth (P356's Catmull-Rom + smoothstep cut, 8x atlas) following the *Smooth font* option.
  - Menu model (`MenuModel`): sections Picture / HUD and information / Gameplay / Controls / Sound / Tools over
    `OPTIONS` (an unlisted option lands in Tools), toggles, sliders (5 % steps), the Classic / Modern preset, help,
    lock reasons. Changes go through `setOption` / `applyPreset` and refresh the drawer.
  - Overlay (`GMenu`): OPTIONS page (preset, sections, Page menu = the drawer, Back to game) + one page per section;
    the game's red title, selected row on a red band with a pulsing `>` cursor, others dimmed (like
    `settings_list_draw`), ON in the game's yellow, paged help, footer. Esc / ☰ / pad Home open it; pad 1 goes to the
    menu (the game gets an idle pad); single player pauses like the drawer; online / recording / replay never pause.
  - Not done: the game's menu sounds (they would go through the game's hashed sound state; none played), the game's
    button icons (A / B / Start pictures are sprites, not font glyphs: the footer spells the buttons), menu frame
    textures (the game's options page has none: text over the 3D scene, so a dark band stands in for it).
  - Tests: tools/port/scripts/gmenu_shots.sh (keys at 1280x720 on the title, fake pad at 1920x1080 widescreen in
    play); `?gmenuopen=S` test aid; netpair UI=1 with the menu open on the guest IDENTICAL; e2e replay PASS with the
    menu open during the replay.
- **P362 done** (commits c287ee42, d805bb0a, d8f6ca34, bdff9f8c, 5c8aa3ca, the ?gmenupad test aid; still option
  `nativemenu`, default off):
  - The overlay covers everything a player needs: main page Preset / Picture / HUD / Gameplay / Controls / Sound /
    Saves / Fullscreen / Photo mode / Online / Record / Tools / Page menu (developer) / Back to game.
  - Controls: Keyboard keys and Gamepad buttons pages (every INPUTS row, Defaults) with capture: keyboard = the next
    keydown (Esc cancels, Backspace unbinds), pad = the first button pressed after every button was up (Esc / 6 s
    cancel); shared with the drawer through main.js bindSet / bindReset. Touch controls toggle. The arrows, Enter, Esc
    and Backspace always drive the menu whatever the bindings.
  - Sound: Master volume (page gain, main.js setVolume shared with the drawer slider; ?mute=1 keeps it at 0 and locked).
    Saves: Export / Import (the drawer has no delete). Fullscreen toggle. Photo mode / Online / Record rows turn their
    tool option on and start photo mode or open the drawer's panel (room codes need text entry: still the drawer).
  - Browser rule: fullscreen and file pickers need a key press or click (a gamepad press is no user activation); the
    menu checks navigator.userActivation.isActive and says "press Enter or click this line" instead of failing.
  - Pad entry for every browser: hold the pad's Photo button (Back / Select by default) 500 ms. It is a page input,
    never an N64 one, so it cannot leak into the game, the lockstep input or a recording (Start + Back would leak
    Start). With the option on, a short press starts photo mode on release; a press in the menu closes it.
  - Legibility: "." / "," get 1.5 units more advance (the font's 2-unit advance put the dot into the next digit:
    "1.5" read "15"), and are drawn at least 0.85 x in the pixel look; help text 0.7 x; footer button faces drawn as
    shapes (blue A, green B, a D-pad cross).
  - Tests: gmenu_shots.sh keys (rebinding Stick up to T, then W does not move Conker and T walks him 1000+ units) and
    pad (hold-Back entry, A = Y capture, Back closes, tap = photo mode) at 1280x720 / 1920x1080 widescreen; netpair UI=1
    with ?gmenupad on the guest (hold entry online) 7473 retraces IDENTICAL; e2e replay PASS, also with ?gmenupad.
  - Readiness (P362's view): ready to become the default once the user has tried it with a real gamepad (only fake
    pads in headless Chrome so far) and on a phone (touch: pointer events, not tested on a device). Gaps: no game
    sounds; Online room-code entry and Record still open the drawer.
- **P363 done** (commits a58c5a00 feature, 54c1b6c0 test script; still option `nativemenu`, default off):
  - The game's own pause menu (game_pause_update, `#ifdef PORT`) has an **OPTIONS** row: font 0 through the game's text
    queue (text_printf_at, drop shadow, scale 1.2), bright / dark green like the item pictures (QUIT / CONT.. are
    pictures, text ids through "#", so only their colours can be matched). Story: centred under PAUSED below QUIT /
    CONT..; multiplayer: under CONTINUE (not screenshotted: the local MP route is ~6000 retraces of menu pad scripts).
    Stick down reaches it, up leaves it; A asks the page (port_gmenu_request_open -> port_gmenu_take_request) to open
    GMenu with open('pause'): no page pause on top, "Back to pause" row, chosen A masked, pad 1 idle, held buttons masked
    after close, so the pause menu is back exactly as it was (OPTIONS still selected).
  - Gate: the page's switch port_set_gmenu_row (option on, game running, no netCfg / recCfg / NETDET) AND C's own
    check (!port_net_on && !port_rec_mode && !port_net_det()). Off = N64: e2e p357 IDENTICAL off and on, netpair UI=1
    with the option on both peers 7923 retraces IDENTICAL (row never on).
  - Tests: tools/port/scripts/pause_options_shots.sh (keys; 1280x720 and 1920x1080 widescreen); evidence port_work/p363.
- **P364 done** (commits e0c9b622 feature, 18252ed0 test script; still option `nativemenu`, default off):
  - Title menu rows, drawn and gated like P363's: **save slot pages** (title_slot_page, GAME1..3: under NEW GAME for an
    empty slot, under PLAY / ERASE for a used one; hidden during the erase question) and **MULTI mode pages**
    (menu_mode_select_page: under SET-UP, reached from SET-UP). Both are reachable by the stick like the game's own items,
    so both were done. Choosing one sends request 2; the page opens GMenu with open('title'): no page pause (title music,
    animation and 3D keep running, pad 1 idle), A masked, "Back to title"; closing returns to the page with OPTIONS
    selected. The game's item is unlit meanwhile (NEW GAME has no dark picture: half alpha).
  - Online: the page also switches the rows off while an online session is being set up (PortNet.t.role), besides
    netCfg / recCfg / NETDET; C keeps its own check. netpair UI=1 (which drives the MULTI pages) 8423 IDENTICAL with the
    option on; e2e p357 IDENTICAL off and on.
  - Finding: text nodes land ~1.1 x / ~1.125 x further from the top-left corner than picture nodes with the same
    numbers; the shared helper port_menu_options_row_draw takes picture coordinates (P363's pause row is now centred).
  - Not done: a row inside the game's own title OPTIONS page (title_press_start_page / settings_list_draw, titlePage 1),
    which would be the most native place but needs a port item in settings_list_draw's 28-item model; the chapter page.
- **Next** (the original P365 "Controls + Saves overlays" was done in P362; proposed new order):
  1. **P365 Online overlay**: the Online row opens a game-style ONLINE page instead of the drawer: Create room / Join
     room, a pad letter picker for the 5-character room code (unambiguous alphabet), status / players / ping, Start,
     Leave, the desync report and the "waiting for players" overlay in the game font. Must stay page-only (no game
     memory), as sessions start before boot.
  2. **P366 photo mode restyle**: photo HUD + Pose & Outfit panel drawn with GameText in the overlay style (keep the pad
     navigation and the hashed-state restore).
  3. **P367 sounds + game OPTIONS page row**: menu move / choose sounds for GMenu (local only: through a port hook that
     plays the game's 0x62D / 0x500 when no session is hashed, silent online), and an "OPTIONS" (port) item in the
     game's own title OPTIONS page (title_press_start_page) if settings_list_draw can take a port row cleanly.
  4. **P368 cleanup + default**: drawer reduced to developer tools (Debug, Recorder, manual codes); touch controls
     styled; first-run screens with title art from a cached ROM; PLAYING.md; ask the user to try a real gamepad / phone
     and decide nativemenu's default.
