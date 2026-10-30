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

1. **P361 overlay renderer + font from the ROM**: `port_asset_font` export (font 0 glyphs + metrics as RGBA from the
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
