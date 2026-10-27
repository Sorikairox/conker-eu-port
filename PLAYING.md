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

**Multiplayer (War / Deathmatch) controls, as the game code reads them:** B is the context action (it draws the
weapon / item the game has given you; without one it does **not** melee-attack in Total War, Bunker / Deathmatch and
the other War levels), R aims (over-the-shoulder view), Z fires the weapon you hold while aiming, C-down throws a grenade (needs
grenades, the orange squares at the top left). On a gamepad the right stick gives the four C buttons.

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
| No motion blur / drunk sway | off | Turns off the frame-blend motion blur (the blurred, smeared picture when Conker wakes up with his hangover after the opening, and in a slow-motion camera cut; with the option off it now looks as on the N64: a live, trailing blend of the last frames, no longer a frozen, blocky picture) and the drunk camera sway: the swaying camera and the slow stretching of the picture on the title menu (drunk Conker in the bar) and while Conker is drunk. Camera moves that are part of a cutscene's own camera path (the tilted view when Conker wakes up) and the wobble under water are unchanged. |
| Conker always full detail | off | Conker is always drawn with his most detailed model. The original switches him to simpler models once the camera is more than 500 units away, which the follow camera often is while he runs (450 to 650 units). Other characters and objects keep the original level-of-detail rules. |
| Underwater air meter | off | While Conker is under water, a bar at the top of the screen shows the air he has left: full when his head goes under, red in the last quarter, empty when he starts to drown. Works with Longer breath (the bar then empties half as fast). The original only shows the wobbling Conker-face meter on the right, which appears after about 2 s and stops changing at half the air. No bar in shallow water where you cannot run out of air. |
| Inverted swimming | off | Under water, pushing the stick up makes Conker swim up and pulling it down makes him dive. The original steers like a plane: stick up tilts him head-down and dives, stick down tilts him up. Only the swimming controls change; walking, flying and aiming stay as they are. |
| Aiming crosshair | off | In the first-person aim views that the original leaves bare, the game's own small crosshair (the one the other guns use) is drawn in the middle of the screen, which is exactly where the shots go there. In this ROM that is the aim kind 0x18 (hold R with that weapon); the scope, lens, bracket and turret views and the other guns already have their own reticles and are unchanged, and the third-person R-look with a held item gets nothing (its shots are aimed from the hand / mouth, not through a fixed screen point). Takes effect the next time you aim. |
| Rumble (gamepad vibration) | off | The game sees a Rumble Pak in your controller and a connected gamepad vibrates whenever the N64 Rumble Pak would (explosions, hits, heavy effects; the game pulses it on and off by strength). Needs a browser with gamepad vibration (Chrome / Edge, most Xbox and PlayStation pads). Takes effect immediately: switching it on or off makes the game look for the Rumble Pak again at once (before, it waited for the next level or area load). Saves are not affected (they use the cartridge EEPROM). |
| Online multiplayer (experimental) | off | Shows the **Online** button in the page header: play a multiplayer match with a friend on another computer (see Online below). |
| Music / Sound effects / Speech volume | 100 % | Three sliders (0 to 100 %, steps of 5) that set the volume of the music, the sound effects and the spoken dialogue separately. 100 % is the original volume. A change to the speech volume applies from the next spoken line. The page's Vol slider still sets the overall volume. |

While a toggle is latched, a small label (Crouch, R-Look, Walk) shows at the top left of the picture, and the touch Z or R button gets a ring.

## Saves

The game saves to its virtual EEPROM, which the page stores in the browser for this ROM. CONTINUE on the title screen works.

**Saves** in the page lets you export the save as a `.eep` file and import one, either with the button or by dropping the file on the page.

A save is tied to the browser profile. Clearing site data, or using a private window, gives you a fresh game.

## Online (experimental)

Two players on two computers can play a multiplayer match together. Each player needs their own copy of the EU ROM
(only a hash of it is compared, the ROM itself never leaves the browser) and **Chrome**. There is no server: you connect
by copying two codes back and forth (chat, e-mail, Discord...).

1. Both: open the page, load the ROM, but do **not** press Start. In **Options**, switch on *Online multiplayer
   (experimental)*; an **Online** button appears in the header. Open it.
2. Player 1: **Host (player 1)**. A code appears: **Copy** it and send it to player 2.
3. Player 2: **Join (player 2)**, paste the code, **Make my answer code**, **Copy** the answer and send it back.
4. Player 1: paste the answer code and press **Connect**. Both games start by themselves, at the same moment of
   the boot.
5. Player 1 uses the menus as on an N64 (Multi, a mode...). Player 2 presses Start on the "press START" join page and
   picks a character like a second controller. From then on each of you controls your own Conker in split screen.

Good to know:
- Both games run the same frames with the same inputs (lockstep). Your input reaches the game a little later than in
  a local game (the *input delay*), so the network has time to carry it to the other computer. By default the host
  measures the ping when the two of you connect and picks the delay itself (*automatic*, shown in the panel as
  "input delay … ms (auto)"):

  | Ping between the two computers | Input delay (automatic) |
  |---|---|
  | same house / same city (under ~20 ms) | 40 ms (2 frames) |
  | same country (~40 ms) | 60 ms |
  | neighbouring countries (~100 ms) | 80 ms |
  | far away (~130 to 150 ms) | 100 ms |

  Up to about 100 ms of input delay most players do not notice it. Untick *automatic* to set it yourself (player 1,
  before Host): lower = more responsive, but the game waits more often.
- If the other computer is slow or far away, the game pauses briefly ("waiting for the other player…" over the
  picture). Waiting often: leave the session, reload both pages and connect again with a higher input delay.
- The session uses player 1's options and player 1's save (unlocks), and saves made during the session are not kept.
- If a player leaves or the connection drops, that player's Conker stands still and the game goes on.
- The Online panel shows the ping, how many frames had to wait for the other player, and the input delay. If it ever
  says **Desync**, the two games no longer show the same thing; the box also says where the two games' memory
  differs. Please report it with the Debug log of both players.
- Switching to another tab or minimising the window is fine: the game keeps running (and keeps the other player
  going) while the page is hidden.

When the codes do not connect ("Could not connect: the two networks do not allow a direct connection"):
- There is no relay server, so the two computers must reach each other directly. This fails behind some company,
  school, hotel and mobile networks and some routers.
- Try another network for one of you: the easiest is a **phone hotspot** for one player (it has a different kind of
  NAT). A home network for both players usually works.
- Make new codes for each try (reload both pages, Host / Join again): a code belongs to one connection attempt, and
  an old one may no longer match your network address.
- A VPN on one side can block it; switch it off for the session.
- Both players need the same page version: reload both pages if one of you had the page open for a long time
  ("different game builds").

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
- **Multiplayer weapons (Deathmatch / Total War):** walking over a floating weapon makes it disappear (the game's own
  pickup code runs and plays its sound), but no weapon is given, so B / R / Z have nothing to draw or fire. Under
  investigation (P340: the pickup code matches the original; what normally hands over the weapon is not found yet).

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
