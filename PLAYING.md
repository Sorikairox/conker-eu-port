# Playing the browser port yourself

This is how to run the Conker's Bad Fur Day (EU) browser port on this Mac and play it. You don't need any Claude session running for this.

## What you need

- **Docker Desktop.** It must be running; the script starts it if it isn't.
- **Your EU ROM file:** `~/Downloads/Conker's Bad Fur Day (Europe).n64`. The page reads it in the browser and keeps it in the browser's storage. It is never uploaded anywhere and never modified.
- **Chrome.** Other browsers may work but aren't tested.

## Start the game

In Terminal:

```
cd ~/conker
tools/eu_port/play.sh
```

The script:

1. starts Docker Desktop if needed;
2. copies the latest browser build from `~/conker-wt/web/port/build/web` into a new folder, `~/conker-play/build-<date>`;
3. serves that copy at **http://localhost:8070/** and opens it.

Your copy is frozen. The working sessions keep rebuilding their own build and serve it on port 8064, so they can't change your game while you play. Each run of `play.sh` takes a fresh copy of the latest build. `BUILD.txt` in the copy says which port-web commit it is.

In the page:

1. **First time only:** drag the ROM file onto the page, or use the file picker. The status line should say `ROM: Conker EU, SHA-1 ok`. The ROM is then remembered, so later visits skip this step.
2. Click **Start**. Sound only begins after this click; that's a browser rule.
3. Play. **Fullscreen** goes full screen, and **Pause** pauses. The game also pauses by itself when the tab is hidden.

Other commands:

| Command | What it does |
|---|---|
| `tools/eu_port/play.sh again` | Serve your last copy again (no new copy) |
| `tools/eu_port/play.sh stop` | Stop the play server |

## Controls

| N64 | Keyboard |
|---|---|
| Stick | W A S D (hold **Ctrl** for half tilt, e.g. to walk) |
| A (jump) | Space |
| B (context action / attack) | F |
| Z | Q |
| R | E |
| L | R |
| Start | Enter |
| C buttons | I J K L |
| D-pad | Arrow keys |

A gamepad works too; plug it in and press a button. **Controls** in the page lets you rebind keys and gamepad buttons, and **Defaults** resets them.

## Saves

The game saves to its virtual EEPROM, which the page stores in the browser for this ROM. CONTINUE on the title screen works.

**Saves** in the page lets you export the save as a `.eep` file and import one, either with the button or by dropping the file on the page.

A save is tied to the browser profile. Clearing site data, or using a private window, gives you a fresh game.

## What should work (as of 2026-10-25)

- **Single player:** title, new game, the opening and intro scenes, the first room, then level 0x29 (the first gameplay level after the intro):
  - Birdy and his dialogue;
  - the B pads, and swimming;
  - the door route across the river;
  - the "Jumping" hint and the ledges up the pit;
  - the gargoyle scene.
- **Multiplayer:** Race A and B, Total War, Colors and Tank all start and play. Race A has been won and Total War played to the end.
- **Also working:**
  - music and sound, with the music decoder now converted to C;
  - saving and loading.

## Known problems

- **The gargoyle:** it can't be beaten yet. The level script needs the frying pan first, and that part hasn't been reached in testing.
- **The lever:** pulling the lever before the gargoyle bridge (jump and hang on it) is still being worked on.
- **Unconverted functions:** about 6% of the game's functions still run as placeholders. A part of the game that uses one may draw or behave wrongly.
- **Speed:** heavy scenes may run slower than full speed.

## Reporting what you find

Easiest is to tell Claude what you did and what happened, ideally with a screenshot. Useful extra details:

- **Timing:** about how long after Start it happened, or which level/scene you were in.
- **Errors:** anything red in Chrome's DevTools console (View → Developer → JavaScript Console).
- **The build:** `BUILD.txt` from your `~/conker-play/build-*` folder.

## Recording your inputs for a test route

You can record your inputs so the tests can replay the route you played:

1. Add `?padrec=1` to the URL: **http://localhost:8070/?padrec=1**.
2. Play the part you want recorded.
3. In the DevTools console, run `copy(__padrec.join(','))`.
4. Paste the result into a text file and give it to Claude.

## Debug options (optional)

You only need these if Claude asks. Add them to the URL, for example `http://localhost:8070/?det=2`.

| Option | Effect |
|---|---|
| `?det=2` | Deterministic mode: the same inputs give the same result every time. |
| `?padrec=1` | Records your pad inputs (see above). |
| `?eepdump=1` | Prints the save data to the console on each save. |

**Debug** in the page shows the log.
