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

**Free camera (option, off by default):** in single player the camera turns freely around Conker, like in modern 3D
platformers. Off, the controls are exactly the N64's (the right stick and I J K L are the four C buttons).

| Free camera | Gamepad | Keyboard / mouse |
|---|---|---|
| Orbit left / right | right stick left / right | J / L, or move the mouse sideways |
| Look up / down (camera lower / higher) | right stick up / down | I / K, or move the mouse up / down |
| Back behind Conker (C-down, the N64 button) | B / circle, or click the right stick | O |
| Camera distance (C-up) | click the left stick | U |

The mouse turns the camera after a click on the picture (the browser then hides the pointer; Esc gives it back). The
camera stays where you put it and keeps following Conker the N64 way; Conker runs where the camera looks. The
height you chose goes back to the normal one by itself after 2 s without camera input while Conker moves, or at
once with C-down. In cutscenes, look and aim views (R), swimming, vehicles, fixed camera spots and multiplayer the
game's own camera runs as on the N64, and the right stick / I J K L are the C buttons there.

**Photo mode (option, off by default):** press **P** (or the gamepad's **Back / View / Select** button, or the
**Photo** button in the page header) to freeze the game. The HUD disappears and a free camera flies around the frozen
moment; press P again (or Start, or **Exit**) and the game goes on exactly where it stopped. Works in cutscenes too.
Single player only; never online.

| Photo mode | Gamepad | Keyboard / mouse |
|---|---|---|
| Move forward / back / sideways | left stick | W A S D (Ctrl: half speed) |
| Look around | right stick (or the C buttons) | I J K L, or click the picture and move the mouse |
| Up / down | R / Z | E / Q |
| Roll (tilt the picture) | D-pad left / right | arrow left / right |
| Zoom (field of view) | D-pad up / down | arrow up / down, or the mouse wheel |
| Back to the game's own view | B | F |
| Show / hide the HUD | L | R |
| Save the picture (PNG) | A | Space, or **Save PNG** |
| Back to the game | Start or Back | P or Enter, or **Exit** |

The picture is saved as a PNG file (`conker-photo-DATE-TIME.png`, through the browser's download) at twice the
picture's resolution (1280 x 960), without the panel or any page overlay. The camera can go up to 3000 units from where
it started; it does not collide with walls. The sound is paused while photo mode is on. The **Photo mode on / off**
input can be rebound under Controls. A button or stick you still hold when you leave photo mode only reaches the game
after you have let go of it.

## Options

The **Options** button in the page header opens a panel of extras that are not in the original game. Each one is a checkbox, saved in this browser. Off means the game behaves exactly like the N64 original. All of them are off at first except the cutscene skip.

**Presets.** At the top of the panel, **Classic / Modern / Custom** sets all the options at once (everything except *Online multiplayer*, which only shows the Online button, and *Photo mode*, which only adds a key that freezes the game when you press it):

- **Classic**: the original game. Every option off and the three volumes at 100 %, except *Skippable cutscenes (hold L)*, which stays on: it does nothing unless you hold L, and it is on by default. A fresh browser starts as Classic.
- **Modern**: Classic plus the extras that show more or make you wait less without making the game easier or changing the controls: *Skip intro*, *Autosave icon*, *Health always visible*, *Always show cash*, *Underwater air meter*, *Aiming crosshair*, *Conker always full detail* and *Rumble*. Left off on purpose: *Longer breath* and *Longer tail spin* (they make the game easier), the three toggles, *Inverted swimming* and *Free camera* (they change how the game controls: a matter of taste), and *No motion blur / drunk sway* (the blur and sway are part of the story's scenes).
- **Custom**: shown as soon as you change any single option (or a volume). Pick Classic or Modern again to reset every option to that preset.

The choice is saved with the options. In an online game the host's options apply: the panel then shows the host's options and preset, greyed out.

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
| Free camera | off | Single player: the right stick, I J K L or the mouse turn the camera around Conker (orbit and look up / down; see *Free camera* under Controls above). Wherever the game uses another camera (cutscenes, look / aim views, swimming, vehicles, fixed camera spots, multiplayer) its own camera runs and the right stick is the C buttons again. Never used online: an online session always runs with it off. |
| Photo mode | off | P (or the gamepad's Back button, or the Photo button) freezes the game for a photo: the HUD goes away, a free camera moves around the frozen moment (move, look, up / down, roll, zoom), and A or Space saves a PNG at twice the picture's resolution. Leaving it continues the game exactly where it stopped. Works in cutscenes. See *Photo mode* under Controls above. Single player only; never used online (an online session always runs with it off). Off: as on the N64, no photo mode. |
| Inverted swimming | off | Under water, pushing the stick up makes Conker swim up and pulling it down makes him dive. The original steers like a plane: stick up tilts him head-down and dives, stick down tilts him up. Only the swimming controls change; walking, flying and aiming stay as they are. |
| Aiming crosshair | off | In the first-person aim views that the original leaves bare, the game's own small crosshair (the one the other guns use) is drawn in the middle of the screen, which is exactly where the shots go there. In this ROM that is the aim kind 0x18 (hold R with that weapon); the scope, lens, bracket and turret views and the other guns already have their own reticles and are unchanged, and the third-person R-look with a held item gets nothing (its shots are aimed from the hand / mouth, not through a fixed screen point). Takes effect the next time you aim. |
| Rumble (gamepad vibration) | off | The game sees a Rumble Pak in your controller and a connected gamepad vibrates whenever the N64 Rumble Pak would (explosions, hits, heavy effects; the game pulses it on and off by strength). Needs a browser with gamepad vibration (Chrome / Edge, most Xbox and PlayStation pads). Takes effect immediately: switching it on or off makes the game look for the Rumble Pak again at once (before, it waited for the next level or area load). Saves are not affected (they use the cartridge EEPROM). |
| Online multiplayer (experimental) | off | Shows the **Online** button in the page header: play a multiplayer match with up to three friends on other computers, joining with a room code (see Online below). |
| Music / Sound effects / Speech volume | 100 % | Three sliders (0 to 100 %, steps of 5) that set the volume of the music, the sound effects and the spoken dialogue separately. 100 % is the original volume. A change to the speech volume applies from the next spoken line. The page's Vol slider still sets the overall volume. |

While a toggle is latched, a small label (Crouch, R-Look, Walk) shows at the top left of the picture, and the touch Z or R button gets a ring.

## Saves

The game saves to its virtual EEPROM, which the page stores in the browser for this ROM. CONTINUE on the title screen works.

**Saves** in the page lets you export the save as a `.eep` file and import one, either with the button or by dropping the file on the page.

A save is tied to the browser profile. Clearing site data, or using a private window, gives you a fresh game.

## Online (experimental)

Two to four players on their own computers can play a multiplayer match together. Each player needs their own copy of
the EU ROM (only a hash of it is compared, the ROM itself never leaves the browser) and **Chrome**. Player 1 (the host)
makes a **room** and tells the others its short code (chat, phone, Discord...); the game itself then goes directly
between your computers. (The room server only passes the connection details between player 1 and each friend; rooms
close when the game starts and expire after 10 minutes.)

1. Everyone: open https://conker-web-port.netlify.app, load the ROM, but do **not** press Start. In **Options**, switch
   on *Online multiplayer (experimental)*; an **Online** button appears in the header. Open it.
2. Player 1: press **Create room (player 1)**. A code like **K7QXM** appears in big letters (**Copy** copies it): tell
   it to your friends.
3. Players 2 to 4: type the code into the box under it (upper or lower case) and press **Join room**. You get the
   next free controller in the order you join (the first friend is player 2, then 3, then 4) and the status line says
   *you are player N: connecting to player 1…*.
4. Player 1: each friend appears in the panel (*Player N joined · ping … ms*). When everybody has joined, press
   **Start the game (N players)**. The players' computers then connect to each other by themselves (a few seconds),
   and all games start at the same moment of the boot.
5. Player 1 uses the menus as on an N64 (Multi, a mode...). The other players press Start on the "press START" join
   page and pick a character like a second, third or fourth controller. From then on each of you controls your own
   Conker in split screen (two players: top / bottom; three or four: four quarters).

Room messages: *No room with the code …* (a typo, or the room was closed / expired: ask player 1 for a new code),
*Room … is full* (the room already has 4 players), *Player 1 runs a different version of the game* (reload both pages),
*Your ROM is not the same as player 1's* (everyone needs the EU ROM). If the room server cannot be reached, use the
manual codes.

**Manual codes (no room server):** tick *manual codes* in the Online panel. Player 1 presses **Host (player 1)**: a
box *Player 2* appears with a long code to **Copy** and send to player 2 (**Invite another player** makes the code for
players 3 and 4). Each friend presses **Join (players 2 to 4)**, pastes the code, presses **Make my answer code** and
sends that answer back; player 1 pastes it into that player's box and presses **Connect player N**. Then continue at
step 4.

Good to know:
- Both games run the same frames with the same inputs (lockstep). Your input reaches the game a little later than in
  a local game (the *input delay*), so the network has time to carry it to the other computer. By default the host
  measures the ping between every two players when the game starts and picks the delay for the slowest pair (*automatic*, shown in the panel as
  "input delay … ms (auto)"):

  | Ping between the two farthest computers | Input delay (automatic) |
  |---|---|
  | same house / same city (under ~20 ms) | 40 ms (2 frames) |
  | same country (~40 ms) | 60 ms |
  | neighbouring countries (~100 ms) | 80 ms |
  | far away (~130 to 150 ms) | 100 ms |

  Up to about 100 ms of input delay most players do not notice it. Untick *automatic* to set it yourself (player 1,
  before Create room / Host): lower = more responsive, but the game waits more often.
- If another computer is slow or far away, the game pauses briefly ("waiting for player N…" over the picture).
  Waiting often: leave the session, reload all pages and connect again with a higher input delay.
- The session uses player 1's options and player 1's save (unlocks), and saves made during the session are not kept.
- If a player leaves or the connection drops, that player's Conker stands still and the game goes on for the others
  (also when player 1 leaves).
- If two of the guests cannot connect to each other directly, their inputs go through player 1's computer instead
  (the panel says "through player 1"); this only adds a little delay for that pair.
- The Online panel shows which player you are, every other player's ping, how many frames had to wait, and the input
  delay. If it ever says **Desync**, the games no longer show the same thing; the box also says where the two games'
  memory differs. Please report it with the Debug log of every player.
- Switching to another tab or minimising the window is fine: the game keeps running (and keeps the other player
  going) while the page is hidden.

When the codes do not connect ("Could not connect: the two networks do not allow a direct connection"):
- There is no relay server, so each guest's computer must reach player 1's computer directly. This fails behind some company,
  school, hotel and mobile networks and some routers.
- Try another network for one of you: the easiest is a **phone hotspot** for one player (it has a different kind of
  NAT). A home network for both players usually works.
- Reload all pages and make a new room (or new manual codes) for each try: a connection belongs to one attempt, and
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
- **Multiplayer weapons (Deathmatch / Total War):** fixed in P341 (a port bug in how some function calls passed small
  numbers). Walking over a floating weapon now gives it to you: its icon appears top right, B takes it out, Z fires.
  Tested in an online 2-player Bunker game (both test windows on one machine); please report if it still fails for you.

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
