# End-to-end tests: recorded playthroughs (P357)

A person plays the game in the browser with the **input recorder** on, one chapter per recording. The recording holds
every input the game read, the save it started from and the game options; nothing of the ROM. Replaying it headless
must give exactly the same game, retrace by retrace. When a new version of the port plays differently, the replay
reports the first point where it does (retrace, level, what differs) with a picture of both versions.

## Recording a chapter (for the player)

Use **Chrome** on the deployed site (https://conker-web-port.netlify.app) or the local copy, with your ROM loaded.

Once:

1. **Options** → tick **Input recorder (for testing)**. A **Record** button appears in the page header.
2. Optional but wise: **Saves** → **Export .eep** keeps a copy of your save (the game goes on saving while you record).

For each chapter (chapter 1 first):

1. Make sure the save in this browser has the chapter available (for chapter 1 any save works, even none: a new game
   starts with chapter 1).
2. **Record** → type a name, e.g. `chapter 1 hungover`, → **Start recording**. The game starts again from power-on
   (if it was running, the page reloads first) and **● REC** shows under the picture. From now on everything you press
   is recorded, menus included.
3. Go through the boot screens and the title, then pick the chapter with the game's own chapter select (**Chapters** in
   the main menu, then the chapter). For chapter 1 on a fresh save: **New game**.
   Using the chapter select (not Continue) makes every recording start the same way and keeps the chapters independent.
4. Play the chapter normally, at full speed, with sound. You may pause (Esc or the Pause button), switch tabs or
   windows, or let the screen lock: the game simply waits and the recording is not affected. Fullscreen, widescreen,
   high frame rate, hi-res 2D, smooth font, full resolution and the volume slider are fine to change (they only change
   the picture or the sound). The game options are fixed while recording, and free camera and photo mode are off.
5. When the chapter is over (the next chapter's title card shows), press **Record** → **Stop and save**. A file
   `conker-rec-<name>-<date>.ckrec` downloads (a few KB per minute) and is also listed in the panel (the last 10 stay in
   the browser; **Download** gets one again). If the page crashed or was closed while recording, the list has an
   "unfinished" copy that contains everything up to the last 10 seconds.
6. The game keeps running afterwards but still in the recording mode: reload the page before playing on normally, or
   start the next chapter's recording (step 2), which starts from the save the game just wrote.

Send the `.ckrec` files to the developers (or put them into `tests/e2e/recordings/`). They contain your save data (the
2 KB EEPROM image) and no ROM data.

Glitches: if something goes wrong in the game during a recording (a crash, a visible bug, a fall through the floor),
say so with the file; a test recording should be a clean playthrough, so redo it if you can.

## Running the replays (for the developers)

```sh
tools/port/scripts/e2e_replay.sh                      # every *.ckrec in tests/e2e/recordings
tools/port/scripts/e2e_replay.sh path/to/one.ckrec    # one recording
SAVE_REF=1 tools/port/scripts/e2e_replay.sh           # all passed: keep this build as the reference for pictures
```

One muted headless Chrome per recording (never two at once), as fast as the page runs: about 500 retraces per second
(10x real time, a 2.5-minute route in 15 s) on the Mac mini with rendering on. Options (env): `WEB=dir` build to test
(default `port/build/web`), `REF_WEB=dir` reference build for the expected pictures (default `port_work/e2e/ref_web`),
`KEEP=1` go on after the first difference, `SPEED=real` 50 Hz, `STOP=F` stop after retrace F, `EXTRA_Q='&opt=...'`
more page query, `OUT=dir` (default `port_work/e2e`), `TIMEOUT=s`. Exit status 0 = everything identical.

Do not add test flags to the page URL (`?p103boot` and the like): the exact hash H covers the port's test aids' static
state too, so a flag the recording was made without shows as an H difference.

### Reading the result

```
PASS p357-newgame-holdL-walk29.ckrec: 7700 retraces (2:34 of game time) IDENTICAL, 163/163 checkpoints and 770 digests
     matched; 15 s (516 retraces/s, 10.3x real time); same build: H / S compared too
FAIL conker-rec-base-...ckrec: first difference at retrace 6980 (2:19 of game time, 90.6 % of the recording), level 29
     mode 0: game digest G a015abca, the recording has 554092a1 (RNG, level / mode, character records)
     last matching fingerprint at retrace 6970; 147/163 checkpoints matched before; reached retrace 6980 (90.6 %, level 29 mode 0)
     recorded with build 88e508bae2e28a39, this is 9f0299f55e6ccc8e: G / level / mode compared; pictures in
     port_work/e2e/<name>: actual.png expected.png (640x480, 191180 pixels differ, ...)
```

- **retrace**: the game's 50 Hz VI counter from power-on (`retrace / 50` = seconds of game time; pauses do not count).
  The difference happened between "last matching fingerprint" and this retrace (G is checked every 10 retraces, so the
  window is at most 0.2 s of game time).
- **what differs**:
  - `G` (game digest, every 10 retraces): the RNG state `g_random_seed`, level, game mode, `g_world_obj_count` and the
    head of the 26 character records `g_objects` (state, id, position, velocities, unique id). Comparable between any two
    builds: a G difference means the game itself behaves differently.
  - `level` / `frame`: a level or game-mode change happened at another retrace (or not at all); the message names both.
  - `H` / `S` (only when the replaying build is the recording's build): the online state hash of all game memory and of
    the game threads' stacks. A difference in H alone with an equal G means memory the digest does not cover differs
    (look with ?nethash / nethash_diff.py); with another build H and S are not comparable (any change of static data
    moves them) and are skipped.
  - Conker's position (expected and actual) is part of the checkpoint messages.
- **pictures** (`port_work/e2e/<name>/`, never committed: ROM-derived): `actual.png` = this build at the first
  difference; `expected.png` = the reference build replayed to the same retrace; `pixdiff.txt` their pixel difference.
  `chrome.log` is the page log, `result.json` the raw result.
- **how far it got**: the retrace / % / level where it stopped; with `KEEP=1` it runs to the end and counts every
  differing fingerprint.

A difference after a deliberate gameplay change (a bug fix that changes how the game plays) is expected: check the
pictures, then re-record that chapter with the new build.

## How it works

- Recording = a single-player session of the online lockstep machinery (`port/ultra/pc_net.c` sections 1, 4, 5;
  `port_rec_session`) with one local channel and no input delay. It forces the online determinism (det clock = retrace
  count, no wall-time frame budget, virtual audio queue instead of the Web Audio fill level, thread stacks at fixed
  addresses, URL flags whitelisted) while the VI stays paced by the wall clock at 50 Hz, so the game is interactive.
- At the start of each retrace the game samples pad 1 (the page writes it every animation frame, `recSetPad`) and
  hands the value to the page (`Module.recInput`); the controller read of that retrace returns exactly it. A pause or a
  hidden tab stops the retraces, so it costs nothing; a blur releases the keys (recorded as released).
- Fixed for the run: game options (recorded), controller presence (pad 1 only), the Rumble Pak (an option), the EEPROM at
  power-on (recorded). Free camera (its camera stick is not in the packed input) and photo mode (sandboxed retraces) are
  off. Render-only options are outside the hashed state (renderer, P349..P356).
- Replay = the same session with the input taken from the recording (`?replay=URL`), retraces back to back for 40 ms
  per tick (`pc_sched.c`), compared in the page (`main.js` `e2eCheck` / `e2eG`), paused at the first difference.
- Fingerprint cost: a checkpoint (H / S) takes ~6.5 ms (every second); G is cheap.

### File format (`.ckrec`)

gzip of one JSON object:

| field | |
|---|---|
| `format`, `version` | `conker-e2e-recording`, 1 |
| `name`, `created`, `user_agent` | as typed / ISO time / browser |
| `build` | first 16 hex digits of SHA-256(conker.wasm) of the recording page |
| `rom_sha1` | the ROM's SHA-1 (the replay refuses another ROM) |
| `start`, `slot` | `power-on`; the page's save slot |
| `eeprom` | base64 of the 2048-byte EEPROM image at power-on (save data) |
| `options` | the game options (`port_set_option` ones) with their values |
| `view` | page-side options at the start (information only) |
| `check_every`, `g_every` | 50, 10 (retraces) |
| `retraces` | number of recorded retraces |
| `inputs` | base64 of runs: u32 LE packed input (`buttons << 16 \| (u8)stick_x << 8 \| (u8)stick_y`) + LEB128 count; retrace 1 first |
| `g` | base64 of u32 LE G of retraces 10, 20, 30, ... |
| `checks` | `[retrace, H, S, G, level, mode, kind, x, y, z]`; kind 0 periodic, 1 level / mode change, 2 the last retrace (Stop) |
| `complete`, `gaps`, `wall_s`, `paused_s` | false for an unfinished draft; input gaps (0); wall / paused seconds |

Size: ~3 KB per minute with the keyboard (the 2.5-minute test route is 8 KB), at most ~13 KB per minute with an analog
stick that moves every retrace (~0.8 MB per hour).

## Limits

- Chrome on desktop was tested (headless, Metal ANGLE). Other browsers should be equivalent (wasm is deterministic and
  GPU read-backs are outside the state) but are untested; node differs from Chrome in a few audio words (P337).
- Only controller 1 is recorded (single player). Multiplayer split screen would need the other channels in the file.
- Free camera and photo mode cannot be used while recording; the game options cannot change mid-recording.
- A recording always starts at power-on (memory snapshots would contain ROM data).
- Cross-build comparison uses G, which covers the RNG and the character records: a change that only affects other
  memory (world objects that are not characters, HUD state) shows up only once it reaches those, or as an H difference
  within the same build.
- Recording mode itself runs on the det clock like online play (the game reads time as the retrace count), so it is
  not byte-identical to a normal session of the same inputs; that does not matter for the comparison.

## Test aids

- `tools/port/scripts/e2e_record.sh NAME ['STEPS'] [EXTRA_QUERY]`: a recording made through the page's own buttons
  (Options → Input recorder, Record, name, Start recording, Stop and save) with real-time key events at given retraces,
  pauses (Pause button) and a hidden window (`tools/port/scripts/e2e_record.js` documents the steps). The default route
  is the hold-L new game + a walk on level 0x29 (`tests/e2e/recordings/p357-newgame-holdL-walk29.ckrec`).
- `window.__rec` (arm / stop / status / list / lastB64 / draftB64) and `window.__e2e.status()` in the page.
