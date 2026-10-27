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

**Skipping cutscenes:** hold **L** (the **R** key, or the L touch button) for 3 seconds to skip any cutscene, even the first time you see it. A ring around an L badge at the bottom right of the picture fills up while you hold it. The original game only allows this for scenes already seen; this is a deliberate change in the browser build only, and your save is unaffected. Start skips the boot intro. You can turn this off under **Options** (see below).

**Phones and tablets:** on-screen touch controls appear by themselves (the **Touch** button toggles them). The game is also online at https://conker-web-port.netlify.app (you still need your own ROM).

A gamepad works too; plug it in and press a button. **Controls** in the page lets you rebind keys and gamepad buttons, and **Defaults** resets them.

## Options

The **Options** button in the page header opens a panel of extras that are not in the original game. Each one is a checkbox, saved in this browser. Off means the game behaves exactly like the N64 original. All of them are off at first except the cutscene skip.

| Option | Default | What it does |
|---|---|---|
| Skippable cutscenes (hold L) | on | Hold L for 3 s to skip any cutscene, even one you have not seen (and Start skips the boot intro). Off: the original rules (only scenes you have seen, and L skips at once). |
| Autosave icon | off | A small save icon blinks in the top right corner of the picture for about 1.5 s whenever the game writes its save. |
| Toggle crouch | off | Z works as a switch: press once to crouch and stay crouched, press again to stand up. Works for the key, the gamepad button and the touch button. |
| Toggle R-Look | off | R works as a switch in the same way: press once for R-Look, press again to end it. |
| Toggle walk (half tilt) | off | The half-tilt key (Ctrl) works as a switch: press once to walk, press again to run. While it is on, the stick of every input (keys, gamepad, touch) is at half tilt. |
| Skip intro | off | The game starts straight at the title menu, without the boot logos, legal pages and intro. Saves load as usual. Takes effect the next time you press Start. |
| Health always visible | off | The chocolate (health) pieces stay at the top left during play. Original: they slide in only when your health changes and leave after about 5 s. Cutscenes still hide them. |
| Always show cash | off | Your cash total ("$ N", in the same green as the game's own cash pop-up) stays at the top right during play. Original: the total only pops up above Conker when he gets cash, and on the pause screen. Hidden in cutscenes and while paused. |
| Longer breath | off | Conker can stay under water about twice as long before he starts to drown (about 58 s instead of 29 s); the air meter empties at half speed. Once the air is gone, drowning works as in the original. |
| Longer tail spin | off | Holding A during the helicopter tail spin (A, then A again in the air) keeps Conker hovering about twice as long before he drops (about 4 s instead of 2 s). Releasing A early, and the hover's slow descent, are unchanged. |
| No motion blur / drunk sway | off | Turns off the frame-blend motion blur (the blurred, smeared picture when Conker wakes up with his hangover after the opening, and in a slow-motion camera cut) and the drunk camera sway: the swaying camera and the slow stretching of the picture on the title menu (drunk Conker in the bar) and while Conker is drunk. Camera moves that are part of a cutscene's own camera path (the tilted view when Conker wakes up) and the wobble under water are unchanged. |
| Conker always full detail | off | Conker is always drawn with his most detailed model. The original switches him to simpler models once the camera is more than 500 units away, which the follow camera often is while he runs (450 to 650 units). Other characters and objects keep the original level-of-detail rules. |

While a toggle is latched, a small label (Crouch, R-Look, Walk) shows at the top left of the picture, and the touch Z or R button gets a ring.

## Saves

The game saves to its virtual EEPROM, which the page stores in the browser for this ROM. CONTINUE on the title screen works.

**Saves** in the page lets you export the save as a `.eep` file and import one, either with the button or by dropping the file on the page.

A save is tied to the browser profile. Clearing site data, or using a private window, gives you a fresh game.

## What should work (as of 2026-10-26)

- **Single player:** title, new game, the opening and intro scenes, the first room, then level 0x29 (the first gameplay level after the intro):
  - Birdy and his dialogue;
  - the B pads, and swimming;
  - the door route across the river;
  - the "Jumping" hint and the ledges up the pit;
  - the gargoyle scene;
  - pulling the lever (jump and hang on it), which opens the doors to the mushroom cave (level 0x2E), and the Frying Pan training there (hit the walking mushroom with B), which sends you back to level 0x29.
- **Multiplayer:** Race A and B, Total War, Colors and Tank all start and play. Race A has been won and Total War played to the end.
- **Also working:**
  - music and sound, with the music decoder now converted to C;
  - saving and loading.
- **All of the game's code is now C** (100% converted, 2026-10-26). The build you get from `play.sh` runs only converted game code; the intro and Race A were re-tested on it.

## Known problems

- **The gargoyle:** beating it (climb back up after the Frying Pan training and hit it with B) hasn't been reached in testing yet.
- **Test routes:** on the latest build the automated level 0x29 test route falls at one of the gaps before the lever, so the lever / Frying Pan part was not re-checked. It worked in testing on earlier builds. Playing it by hand should work.
- **Newly converted code:** the last functions were converted just now and have only had a short browser test (intro, Race A). Parts of the game that weren't tested may draw or behave wrongly; please report them.
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
