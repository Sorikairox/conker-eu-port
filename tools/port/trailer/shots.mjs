// P354 trailer shot list for capture.mjs. Each shot: query (appended to ?app=game&det=1&p103boot=1&mute=1&canvas=...),
// canvas 'WxH' (drawing buffer; with the widescreen option its aspect), start (retrace of the first picture), secs,
// fps (default 60), hfr (interpolate with the High frame rate option), out [w, h] (JPEG size, default the canvas),
// audioFrom (retraces of audio before start, default 40), steps [{ at: retrace, eval: 'page JS' }],
// ticksPerPic (photo mode: no retraces run; N main-loop ticks per picture instead).
// Pads: ?padf=F:BTN:X:Y[:RX:RY],... (absolute retraces, hex buttons: 8000 A, 4000 B, 2000 Z, 1000 Start, 0020 L, 0010 R).
// Test aids used (all in the shipped build, off without their flags): ?warp (P327), ?p352tp* teleport + ?p205goto
// autopilot + ?p352hang (P352), ?p326hcycle (P326), ?photoat / ?photomove (P348), ?netdet + ?padf1..3 (P337).
// Every shot but 'music' has the music off (volmusic:0): the trailer lays one music track under the edit and mixes the
// shots' sound effects in.
const MODERN = 'hires2d:1,widescreen:1,fullres:1,hfr:1,volmusic:0';
const NOHUD = 'healthhud:0,cashhud:0';
// level 0x29 (the first level), Conker runs along the river from the warp start (same pads in run29* shots)
const RUN29 = '&warp=29&padf=100:0:0:0,130:0:0:80,250:0:30:80,330:8000:30:80,338:0:30:80,420:0:-50:70,520:0:0:80,600:8000:0:80,608:0:0:80,700:0:60:60,800:0:0:80,900:0:-60:60,1000:0:0:0';
const SPIN13 = '&warp=13&padf=100:0:0:0&p352tpf=200&p352tpx=790&p352tpy=1900&p352tpz=-3572&p352yaw=180&p205goto=262:20:0:h-1100:-3572&p326hcycle=900&p326=1';
// P355: the new game's opening cutscene (Start at the title, Start on the save slot): credits, then Conker on the throne
// with his monologue from retrace ~8450 ("Well... there I am.") to ~10290 ("...a bad fur day."); the game's own
// "Conker's Bad Fur Day" logo follows at ~10300 and is never shown. Three runs of the same frames: the pictures (with the
// music and effects, no speech), the speech alone (music and effects off) and the full mix (for checking the sum).
const NEWGAME = '&padf=3386:1000:0:0,3401:0:0:0,4458:1000:0:0,4473:0:0:0';
const INTRO = { start: 8240, secs: 42, audioFrom: 60 };
export const SHOTS = {
  // the features part's game music (P355 pick by measurement, musicstat.mjs: loud, steady ~97 BPM loop): level 0x0C with
  // the effects and speech off, Conker standing still
  music_0c: { query: '&warp=0C&opt=volsfx:0,volspeech:0&padf=100:0:0:0', start: 150, secs: 60, fps: 0.5, hfr: false, canvas: '480x270' },
  intro: { query: `${NEWGAME}&opt=hires2d:1,widescreen:1,fullres:1,hfr:1,volspeech:0`, ...INTRO, hfr: true },
  // the same run's music + effects, longer (past the logo, for holding it): audio only, tiny pictures
  intro_audio: { query: `${NEWGAME}&opt=widescreen:1,volspeech:0`, ...INTRO, secs: 48, fps: 1, hfr: false, canvas: '480x270' },
  intro_speech: { query: `${NEWGAME}&opt=widescreen:1,volmusic:0,volsfx:0`, ...INTRO, fps: 2, hfr: false, canvas: '480x270' },
  intro_full: { query: `${NEWGAME}&opt=widescreen:1`, ...INTRO, fps: 2, hfr: false, canvas: '480x270' },
  // music: the title sequence from power-on with Skip intro (rain, Conker walks into the pub, title menu), sound effects off
  music: { query: '&opt=hires2d:1,widescreen:1,skipintro:1,volsfx:0,volspeech:0', start: 40, secs: 70, fps: 4, hfr: false, out: [960, 540] },
  // Conker on level 0x29: modern (16:9, full resolution, hi-res 2D, high frame rate), the same without the high frame
  // rate, and the original look (4:3, 640 x 480, every option off)
  run29: { query: `${RUN29}&opt=${MODERN}`, start: 120, secs: 16, hfr: true },
  run29_30: { query: `${RUN29}&opt=${MODERN},hfr:0`, start: 120, secs: 16, hfr: false },
  run29_n64: { query: `${RUN29}&opt=volmusic:0`, canvas: '640x480', start: 120, secs: 16, hfr: false },
  // ledge grab: level 0x13 crate edge (P352 p352L13climb): teleport, jump at the edge, hang, A = pull up
  ledge13: { query: `&warp=13&opt=${MODERN},ledgegrab:1&padf=100:0:0:0&p352=196&p352n=700&p352tpf=200&p352tpx=777&p352tpy=1900&p352tpz=-3650&p352yaw=90&p205goto=230:20:0:j777:-3950&p352hang=60:8000:0:0:8`,
    start: 215, secs: 7, hfr: true },
  // longer tail spin: level 0x13, jump off the crate stack (y 1880, floor 1335) towards the next stack, A held
  // (helicopter); the same pads with the option off and on, shown side by side
  spin_off: { query: `${SPIN13}&opt=${MODERN},longspin:0`, start: 240, secs: 7, hfr: true },
  spin_on: { query: `${SPIN13}&opt=${MODERN},longspin:1`, start: 240, secs: 7, hfr: true },
  // 4-player Bunker Deathmatch replayed frame by frame with the pads of the net4.sh online session (?netdet: the online
  // determinism mode, all four pads from their scripts); PADS_ENV = net4.sh's pads.env, read by capture.mjs
  // ?netdet fixes every option at its default (the session's vector), so the renderer-only switches (outside the
  // online hash) are turned on from the page after retrace 2
  mp4: { query: '&netdet=1&padmask=F&nethash=1', padsEnv: 'port_work/trailer/net4/pads.env', padShift: 2, start: 6150, secs: 12, hfr: true,
    steps: [{ at: 2, eval: 'Module._port_gfx_widescreen(1), Module._port_gfx_hires_2d(1), Module._port_gfx_hfr(1), 1' }] },
  // hi-res 2D: the pause screen on level 0x29 (Start at 400), with and without the option
  pause_hi: { query: `&warp=29&padf=100:0:0:0,400:1000:0:0,408:0:0:0&opt=${MODERN}`, start: 470, secs: 2, hfr: false },
  pause_lo: { query: '&warp=29&padf=100:0:0:0,400:1000:0:0,408:0:0:0&opt=volmusic:0,widescreen:1', start: 470, secs: 2, hfr: false },
  // free camera: the right stick orbits the camera around Conker on level 0x29
  freecam: { query: `&warp=29&opt=${MODERN},freecam:1&padf=100:0:0:0,200:0:0:0:80:0,520:0:0:0:0:50,600:0:0:0:-80:0,800:0:0:0:0:0`, start: 200, secs: 6, hfr: true },
  // photo mode: frozen game, the photo camera flies around (P348 test aid ?photoat / ?photomove, per tick)
  photo: { query: `&warp=29&opt=${MODERN},photomode:1&padf=100:0:0:0,130:0:0:80,300:0:0:0&photoat=330&photomove=0:1.6:0.15:-0.26:0:0:0.05`, start: 330, secs: 4, hfr: false, ticksPerPic: 1 },
};
// P370: the customisation settings (always on since P369), filmed as a player sees the window (capture.mjs screen
// shots: CDP screenshots, the page's clock stepped with the game). Pad input after the ?padf run comes from the
// ?gmenutest fake standard gamepad (gmenu.js: __gmenuTest.press([[button, frames held, frames after]]), stepped with the
// animation frames); its left stick is set directly (pad.axes). Buttons: 0 A, 1 B, 9 Start, 12-15 D-pad up / down /
// left / right.
const PRESS = (seq) => `__gmenuTest.press(${JSON.stringify(seq)})`;
const STICK = (x, y) => `(navigator.getGamepads()[0].axes[0] = ${x}, navigator.getGamepads()[0].axes[1] = ${y}, 1)`;
const RUN29P = '&warp=29&padf=100:0:0:0,130:0:0:80,250:0:30:80,330:8000:30:80,338:0:30:80,420:0:-50:70,520:P';
// custom: Conker runs (4:3: every option of the picture but Widescreen), Start = the game's pause menu, stick down to its
// CUSTOMISATION SETTINGS row, A opens the menu over the pause; down through Picture / HUD / Gameplay, back up to
// Picture, A, Widescreen OFF -> ON with D-pad right: the picture widens behind the menu; B, B = back to the pause
// menu (now 16:9), Start resumes, the stick runs him on in 16:9.
SHOTS.custom = { query: `${RUN29P}&gmenutest=1&opt=hires2d:1,fullres:1,hfr:1,smoothfont:1,volmusic:0`, screen: [1920, 1080],
  start: 440, secs: 12, hfr: true,
  steps: [
    { at: 520, eval: PRESS([[9, 3, 0]]) },                     // Start: the game's pause menu
    { at: 556, eval: STICK(0, 1) }, { at: 562, eval: STICK(0, 0) },   // stick down: CUSTOMISATION SETTINGS
    { at: 578, eval: PRESS([[0, 3, 0]]) },                     // A: the menu opens over the pause
    { at: 602, eval: PRESS([[13, 3, 9], [13, 3, 9], [13, 3, 12], [12, 3, 9], [12, 3, 0]]) },   // Picture, HUD, Gameplay, back up to Picture
    { at: 672, eval: PRESS([[0, 3, 0]]) },                     // A: the Picture page (Widescreen is its first row)
    { at: 700, eval: PRESS([[15, 3, 0]]) },                    // D-pad right: Widescreen ON
    { at: 750, eval: PRESS([[1, 3, 12], [1, 3, 0]]) },         // B, B: back to the pause menu
    { at: 795, eval: PRESS([[9, 3, 0]]) },                     // Start: resume
    { at: 812, eval: STICK(0.35, 1) }, { at: 900, eval: STICK(-0.5, 0.9) }, { at: 980, eval: STICK(0, 1) },
  ] };
// boot: a player's second visit (the ROM and the game font are kept in the browser): the Press Start screen in the
// game's font (GBoot), Start on the pad, the game boots. prepare: the first visit's page without a ROM (still_first.jpg),
// then one boot (the page keeps the game font ~1 s after it), then the page again without ?app=game.
async function bootPrepare(b, { sleep, url, dir, shotJpeg, log }) {
  const nav = async (u) => { await b.call('Page.navigate', { url: u }); await sleep(500); for (let i = 0; i < 100; i++) { if (await b.ev("document.readyState === 'complete'").catch(() => false)) break; await sleep(200); } };
  await nav(url.replace('romurl=../dev/rom.z64', 'romurl=none'));
  await sleep(2500); await shotJpeg('still_first.jpg');
  await nav(url + '&app=game');
  for (let i = 0; i < 200; i++) { if ((await b.ev('__trailer.q.length && __trailer.frame() >= 0 ? 1 : 0')) === 1) break; await sleep(250); }
  let kept = false;
  for (let f = 100; f <= 1500 && !kept; f += 100) {
    while ((await b.ev(`__trailer.runTo(${f}, 40)`)) < f);
    kept = await b.ev("Object.keys(localStorage).some((k) => /font/i.test(k))");
  }
  log(`first boot: game font kept ${kept} (${await b.ev('Object.keys(localStorage).join(" ")')})`);
  await nav(url);
}
SHOTS.boot = { query: '&gmenutest=1&opt=hires2d:1,widescreen:1,fullres:1,hfr:1,smoothfont:1,skipintro:1,volmusic:0', screen: [1920, 1080],
  preBoot: true, prepare: bootPrepare, ticksPerPic: 1, fps: 50, secs: 16,
  tickSteps: [{ pic: 75, eval: PRESS([[9, 4, 0]]) }] };
// photo: photo mode in the game's style (GPhoto: HUD bottom left, POSE & OUTFIT panel right) over the frozen game, the
// photo camera flying (?photoat / ?photomove per tick); keys like a player (P366 photo_menu_shots.sh): O gives the panel
// the D-pad, down to Model, Enter = the model list, down to 150 Conker in the black coat, Enter: he wears it.
const KEY = (code, type) => `(dispatchEvent(new KeyboardEvent('${type}', { code: '${code}', key: '${code}' })), 1)`;
const TAP = (code, pic) => [{ pic, eval: KEY(code, 'keydown') }, { pic: pic + 3, eval: KEY(code, 'keyup') }];
SHOTS.photo2 = { query: `&warp=29&opt=hires2d:1,widescreen:1,fullres:1,smoothfont:1,volmusic:0,photomode:1&padf=100:0:0:0,130:0:0:80,300:0:0:0&photoat=330&photomove=0.4:1.3:0.05:-0.25:-0.04:0:0`,
  screen: [1920, 1080], start: 330, secs: 9, fps: 50, hfr: false, ticksPerPic: 1,   // the camera circles Conker (right 1.3 units + yaw 0.25 degrees per tick: he stays in the middle)
  tickSteps: [...TAP('KeyO', 60), ...TAP('ArrowDown', 80), ...TAP('ArrowDown', 92), ...TAP('ArrowDown', 104), ...TAP('ArrowDown', 116),
    ...TAP('Enter', 135), ...[0, 1, 2, 3, 4, 5, 6, 7, 8].flatMap((k) => TAP('ArrowDown', 160 + 8 * k)), ...TAP("Enter", 245), ...TAP("KeyH", 330)] };   // H: every menu hidden, the clean picture   // 9 down: 150 Conker, black coat (Heist)
// phone: a phone held upright (390 x 844 CSS pixels at 3x, touch screen): the picture at the top, the game-style touch
// controls below it (prepare: one boot first, so the game font is kept and the faces carry their letters); real touch
// events (CDP) like a thumb: Start = the game's pause, the touch stick down to CUSTOMISATION SETTINGS, A opens the
// menu, the stick moves in it, A opens Picture... (P369: the touch controls work inside the menu, nothing reaches the game)
async function fontPrepare(b, { sleep, url, log }) {
  const nav = async (u) => { await b.call('Page.navigate', { url: u }); await sleep(500); for (let i = 0; i < 100; i++) { if (await b.ev("document.readyState === 'complete'").catch(() => false)) break; await sleep(200); } };
  for (let i = 0; i < 200; i++) { if ((await b.ev('__trailer.q.length && __trailer.frame() >= 0 ? 1 : 0')) === 1) break; await sleep(250); }
  let kept = false;
  for (let f = 100; f <= 1500 && !kept; f += 100) {
    while ((await b.ev(`__trailer.runTo(${f}, 40)`)) < f);
    kept = await b.ev("Object.keys(localStorage).some((k) => /font/i.test(k))");
  }
  log(`first boot: game font kept ${kept}`);
  await nav(url);
}
const T_A = [238, 790], T_START = [195, 628], T_B = [186, 720], T_MENU = [30, 30];
// the menu opened like a phone player does it, with the corner button (the game pauses behind it, so no retraces run:
// the shot steps animation frames, ticksPerPic, with the touches at pictures; one tick = one retrace while the game runs)
const PTAP = (x, y, pic, id = 1) => [{ pic, touch: ['touchStart', x, y, id] }, { pic: pic + 4, touch: ['touchEnd', x, y, id] }];
const PSTICK = (dy, pic, hold = 10, id = 2, dx = 0) => [{ pic, touch: ['touchStart', 90, 764, id] }, { pic: pic + 1, touch: ['touchMove', 90 + dx, 764 + dy, id] },
  { pic: pic + 1 + hold, touch: ['touchEnd', 90 + dx, 764 + dy, id] }];   // one move only: a second CDP touchMove of the same point read as the opposite direction
SHOTS.phone = { query: `${RUN29P}&touch=1&opt=hires2d:1,fullres:1,hfr:1,smoothfont:1,volmusic:0`, screen: [390, 844, 3], mobile: true, prepare: fontPrepare,
  start: 440, secs: 8.4, fps: 50, hfr: false, ticksPerPic: 1, quality: 0.9,
  // corner button, stick down twice (Picture, HUD and information), A, down to Health always visible, stick right (on),
  // B, B: the game goes on with Conker's health shown
  tickSteps: [...PTAP(...T_MENU, 100), ...PSTICK(60, 140), ...PSTICK(60, 165), ...PTAP(...T_A, 195),
    ...PSTICK(60, 228), ...PSTICK(0, 258, 10, 2, 60), ...PTAP(...T_B, 298), ...PTAP(...T_B, 326)] };
