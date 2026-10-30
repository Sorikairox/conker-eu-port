// Page glue for the Conker wasm32 port. The ROM is supplied by the user and never leaves the browser
// (cached in IndexedDB). Two wasm apps: the scheduler demo and the game; one per page load.
// P27: ROM drop zone, input (keyboard + Gamepad API -> PIF pad state), EEPROM saves in IndexedDB,
// fullscreen / pause / volume, debug console behind a toggle, audio resume on the first gesture.
'use strict';
const EU_SHA1 = 'ee7bc6656fd1e1d9ffb3d19add759f28b88df710';
const $ = (id) => document.getElementById(id);
const Q = new URLSearchParams(location.search);
// P337 online multiplayer phase 0: ?netdet=1 = forced online determinism (port/ultra/pc_net.c). The page then writes no
// pad state (pads come from the ?padf scripts / the input ring only), sends the default options vector once (no ?opt, no
// saved options, no changes during the run) and boots with a blank EEPROM that is never persisted.
const NETDET = /[?&]netdet(=1)?(&|$)/.test(location.search);
// P338 online multiplayer phase 1: netCfg = the lockstep session this page boots into (port/web/net.js, pc_net.c), or
// null (the normal game). { mask: channels in the session, local: this peer's channels, delay: D retraces, hashEvery: K,
// options: the host's game options {key: value}, eeprom: the host's EEPROM image (Uint8Array) or null = blank,
// loop: loopback test peer {lat, loss} }. Test aid: ?netloop=1[&netmask=HEX][&netd=D][&netlat=MS][&netloss=PCT] runs a
// session against a loopback peer in this page that plays the ?padf1..3 scripts (with &netscript=1 pad 1 plays ?padf).
let netCfg = null;
// P357 input recorder: recCfg = the recording / replay this page boots into (port/ultra/pc_net.c section 5), or null.
// { mode: 'record' | 'replay', options: the game options {key: value} (fixed for the run), name, ... } (see "input recorder" below)
let recCfg = null;
const e2e = { ended: false };   // P357 replay state (filled by e2eBegin); ended = the replay is over: the game stays paused
if (Q.get('netloop')) netCfg = { mask: parseInt(Q.get('netmask') || 'F', 16), local: 1, delay: +(Q.get('netd') || 3), hashEvery: 10,
  options: null, eeprom: null, loop: { lat: +(Q.get('netlat') || 0), loss: +(Q.get('netloss') || 0) } };
const out = $('console');
let romBytes = null, romSha1 = null, romOk = false;
let running = null, M = null;

function log(s, cls) {
  const line = document.createElement('div');
  line.textContent = s;
  if (cls) line.className = cls;
  else if (/^PASS|\] PASS/.test(s)) line.className = 'pass';
  else if (/^FAIL|\] FAIL|RuntimeError|Aborted/.test(s)) line.className = 'fail';
  else if (/^\[stub/.test(s)) line.className = 'stub';
  out.appendChild(line);
  if (out.childNodes.length > 5000) out.removeChild(out.firstChild);
  if (!$('p-debug').hidden) out.scrollTop = out.scrollHeight;
  console.log(s);
}
// P360: the status line lives in the menu drawer; while the drawer is closed, a message that matters (an error, or anything
// before the game runs) also shows for a few seconds as a toast over the picture (it never moves the picture)
let toastTimer = 0;
function toast(s, cls, ms = 3500) {
  const t = $('toast'); t.textContent = s; t.className = cls || '';
  clearTimeout(toastTimer); toastTimer = setTimeout(() => t.classList.add('out'), ms);
}
const status = (s, cls) => {
  const e = $('status'); e.textContent = s; e.className = cls || '';
  if ((cls === 'bad' || !running) && !document.body.classList.contains('drawer')) toast(s, cls, cls === 'bad' ? 8000 : 3500);
};
const store = {   // localStorage can throw (private mode, blocked storage): never required
  get(k, d) { try { const v = localStorage.getItem(k); return v === null ? d : JSON.parse(v); } catch (e) { return d; } },
  set(k, v) { try { localStorage.setItem(k, JSON.stringify(v)); } catch (e) { /* ignore */ } },
};

// ---------------------------------------------------------------- panels
function toggle(name, on) {
  const b = $('t-' + name), p = $('p-' + name);
  on = on === undefined ? p.hidden : on;
  p.hidden = !on; b.setAttribute('aria-pressed', String(on));
  $('side').hidden = ['controls', 'saves', 'options', 'online', 'rec', 'debug'].every((n) => $('p-' + n).hidden);
  if (name === 'debug') { store.set('debug', on); if (on) out.scrollTop = out.scrollHeight; }
}
for (const n of ['controls', 'saves', 'options', 'online', 'rec', 'debug']) $('t-' + n).onclick = () => toggle(n);
if (['controls', 'saves', 'options', 'online', 'rec'].includes(Q.get('panel'))) { toggle(Q.get('panel'), true); setTimeout(() => drawerSet(true), 0); }   // P346 test aid: ?panel=options (P360: opens the menu)
if (Q.get('debug') === '1' || (Q.get('debug') !== '0' && store.get('debug', false))) toggle('debug', true);

// ---------------------------------------------------------------- P360 menu drawer
// The game fills the window; every page control lives in #drawer, a translucent panel over the left of the picture,
// opened by Esc or the corner button #menu-btn (which fades out with the mouse cursor after a few idle seconds of play).
// Opening it pauses a single-player game (like a pause menu; never an online session, never a replay); closing it
// resumes the game if the drawer paused it and gives the keyboard focus back to the canvas.
const drawerOpen = () => $('drawer').classList.contains('open');
let drawerPaused = false;
function drawerSet(on) {
  if (on === drawerOpen()) return;
  $('drawer').classList.toggle('open', on);
  document.body.classList.toggle('drawer', on);
  $('drawer-shade').hidden = !on;
  $('menu-btn').setAttribute('aria-expanded', String(on));
  if (on) {
    if (running === 'game' && !netCfg && !userPaused && !(recCfg && recCfg.mode === 'replay')) { drawerPaused = true; setPaused(true); }
    setTimeout(() => { if (drawerOpen()) $('drawer-close').focus({ preventScroll: true }); }, 200);   // after the slide-in (hidden until then)
    if (document.pointerLockElement && document.exitPointerLock) document.exitPointerLock();
  } else {
    if (drawerPaused && userPaused) setPaused(false);
    drawerPaused = false;
    keysDown.clear();
    $('canvas').focus();
  }
  idleKick();
}
$('menu-btn').onclick = () => { if (!(window.GMenu && GMenu.wanted() && GMenu.open())) drawerSet(true); };   // P361: the game-style menu when that option is on
$('drawer-close').onclick = () => drawerSet(false);
$('drawer-shade').onclick = () => drawerSet(false);   // a click on the picture beside the drawer closes it
// the corner button and the cursor hide after 2.5 s without mouse movement while the game runs (shown again on movement)
let idleTimer = 0;
function idleKick() {
  document.body.classList.remove('idle');
  clearTimeout(idleTimer);
  idleTimer = setTimeout(() => { if (running === 'game' && !drawerOpen() && !document.body.classList.contains('touch')) document.body.classList.add('idle'); }, 2500);
}
for (const ev of ['mousemove', 'pointerdown', 'touchstart']) window.addEventListener(ev, idleKick, { passive: true });
// Start (key, gamepad or touch button) on the Press Start screen starts the game
let readyPrev = true;
function readyPoll(p) {
  const st = (p.b & N64.START) !== 0;
  if (st && !readyPrev && !running && romOk && !$('ready').hidden && !drawerOpen()) start('game');
  readyPrev = st;
}
$('ready-start').onclick = () => start('game');
$('ready-rom').onclick = () => { $('ready').hidden = true; $('drop').hidden = false; };

// ---------------------------------------------------------------- options (P324)
// Every port-only feature is optional. One row per option: key (localStorage 'opt.KEY'), label, default, help text,
// and `game`: the PORT_OPT_* id (port/ultra/port_options.h) when game C reads the option through port_option(id);
// those are pushed to the game with port_set_option before it starts and on every change. Defaults off = the
// original game, except where the user asked otherwise.
// Test aid: ?opt=KEY:1,KEY:0 overrides options for this page load (not saved).
const OPTIONS = [
  { key: 'online', label: 'Online multiplayer (experimental)', def: false,
    help: 'Shows the Online button: 2 to 4 players on their own computers play a multiplayer match together (player 1 makes a room, the others join with its code; manual copy-paste codes also work).' },
  // P357: a tool like Online / Photo mode (not in the presets): shows the Record button (docs/port/E2E.md)
  { key: 'recorder', label: 'Input recorder (for testing)', def: false,
    help: 'Shows the Record button: records everything you press from power-on (with your save and options) into a small file that the developers replay automatically to find the first point where a new version of the port plays differently. While recording, the game runs in the same exact-timing mode as online play; free camera and photo mode are off and the game options are fixed.' },
  // P361: page-side, a tool like the ones above (not in the presets): Esc / the corner button open the game-style menu
  // (port/web/gmenu.js) instead of the page menu drawer. Default off (NATIVE_MENUS.md step P361); the drawer stays.
  { key: 'nativemenu', label: 'Game-style menu (Esc)', def: false,
    help: 'Esc, the corner button (or a gamepad\'s Home button, where the browser passes it) open the options as a menu drawn over the game in the game\'s own font (smooth with Smooth font), driven like the game\'s menus: D-pad, stick or arrows move, left / right change a value, A, Start, Enter or Space choose, B, Esc or Backspace go back; the mouse and touch work too. Its "Page menu" line opens this page menu (bindings, saves, online, recorder). Online and while recording the game keeps running behind it and the host\'s game options are shown locked. Off: Esc opens this page menu.' },
  { key: 'skipcut', label: 'Skippable cutscenes (hold L)', def: true, game: 0,
    help: 'Hold L for 3 s to skip any cutscene, even one not seen yet (also Start on the boot intro). Off: the N64 rules (only scenes already seen, L skips at once).' },
  { key: 'saveicon', label: 'Autosave icon',  def: false,
    help: 'A small save icon blinks in the top right corner of the picture for 1.5 s whenever the game writes its save.' },
  { key: 'togglecrouch', label: 'Toggle crouch', def: false,
    help: 'Z (key, pad button or touch button) latches: one press crouches and keeps crouching, the next press stands up.' },
  { key: 'togglerlook', label: 'Toggle R-Look', def: false,
    help: 'R latches the same way: one press turns R-Look on, the next press turns it off.' },
  { key: 'togglewalk', label: 'Toggle walk (half tilt)', def: false,
    help: 'The half-tilt key latches: one press walks (half stick), the next press runs again. Applies to every stick input of pad 1.' },
  { key: 'skipintro', label: 'Skip intro', def: false, game: 1,
    help: 'Start straight at the title menu: no boot logos, legal pages or intro. Takes effect at the next start.' },
  { key: 'healthhud', label: 'Health always visible', def: false, game: 2,
    help: 'The chocolate (health) pieces stay on screen during play. Off: as on the N64, they slide in only when your health changes.' },
  { key: 'cashhud', label: 'Always show cash', def: false, game: 3,
    help: 'Your cash total stays in the top right corner during play, drawn with the pause screen\'s $ and digit images. Off: as on the N64, it only pops up above Conker when he gets cash (and on the pause screen).' },
  { key: 'longbreath', label: 'Longer breath', def: false, game: 4,
    help: 'Conker can stay under water about twice as long before he starts to drown (the air meter empties at half speed). Off: the N64 air time.' },
  { key: 'longspin', label: 'Longer tail spin', def: false, game: 5,
    help: 'Holding A during the helicopter tail spin (A, then A again in the air) keeps Conker hovering about twice as long before he drops. Off: the N64 hover time.' },
  // P352: game option 17. Not in Modern: it changes how the game plays (like the longer breath / tail spin).
  { key: 'ledgegrab', label: 'Ledge grab everywhere', def: false, game: 17,
    help: 'Single player: when Conker jumps or falls against a wall just short of its top, he catches the edge and hangs from it on any ledge, not only on the few the levels mark for it. Hanging: A pulls him up, stick towards the wall hops up, stick back or Z lets go, stick left / right shimmies along the edge (in the hang pose: the game has no shimmy animation). He does not catch edges less than about 150 units above the floor below, edges of moving objects or water, or anything in multiplayer. Off: as on the N64 (only marked ledges, no Z, no shimmy).' },
  { key: 'nodrunk', label: 'No motion blur / drunk sway', def: false, game: 6,
    help: 'Turns off the frame-blend motion blur (the hangover wake-up after the opening, a slow-motion camera cut) and the drunk camera sway and screen stretching (drunk Conker, the title menu). The under-water wobble stays. Off: as on the N64.' },
  { key: 'conkerlod', label: 'Conker always full detail', def: false, game: 7,
    help: 'Conker is always drawn with his most detailed model. Off: as on the N64, he switches to simpler models once the camera is more than 500 units away (the normal follow camera is often 450 to 650 units behind him, more while running).' },
  // P349: page-side (no `game` id): the renderer's own switch (port_gfx_hires_2d), each player's choice even online.
  { key: 'hires2d', label: 'Hi-res menus and 2D', def: false,
    help: 'Menus, HUD, text, title and pause screens and other flat pictures are drawn sharp at the picture\'s full resolution: each texel sits exactly where the N64 shows it (no half-texel blur), tiled pictures join without seams, scaled text and icons show the detail of their textures, blocky (unfiltered) pictures keep even, crisp texels, and the frozen game picture behind the pause menu stays at full resolution. Same layout and colours as the N64; 3D is not changed. Off: as before (2D sampled the N64 way, half a texel off at this resolution).' },
  // P356: page-side (port_gfx_smooth_font in the renderer, outside the online hash): each player's own choice online.
  { key: 'smoothfont', label: 'Smooth font', def: false,
    help: 'The game\'s text (speech bubbles and dialogue, menu lines, the legal page, subtitles and other printed text) is drawn with smooth, clean curved edges at the picture\'s full resolution instead of big blurred pixels: each letter keeps the game font\'s shape, size, place and colours. Only the font\'s letters change; words drawn as pictures (GAME 1, PAUSED, the HUD digits), icons and other pictures stay as they are. Best with Full-resolution picture. Off: the N64 font pixels, magnified.' },
  // P350: page-side too (port_gfx_widescreen in the renderer, outside the online hash): each player's own choice online.
  { key: 'widescreen', label: 'Widescreen', def: false,
    help: 'The picture fills a wide window (16:9, 16:10, up to 21:9: the shape of the game area, or of the screen in fullscreen) and the 3D view sees further to the left and right, instead of a 4:3 picture with black bars. Nothing is stretched. Menus, text and the pause screen keep their N64 place in the middle, the health, cash and air meter move to the corners, fades and the pause background cover the whole width. The game itself still works with its 4:3 view (nothing plays differently, safe online): characters and some effects just outside the 4:3 view are only drawn once they come close to it. Off: the 4:3 N64 picture.' },
  // P351: page-side (the canvas size; the renderer follows it), each player's own choice online.
  { key: 'fullres', label: 'Full-resolution picture', def: false,
    help: 'The game is drawn at the real resolution of its place on your screen (the size of the picture times the display\'s pixel ratio, at most 2560 x 1440), instead of 640 x 480 scaled up: sharper 3D edges and textures, and with Hi-res menus and 2D, sharper menus and text. Same picture otherwise. Needs a faster graphics card at large sizes. Off: 640 x 480 (or 480 rows high in widescreen).' },
  // P351: page-side (port_gfx_hfr in the renderer, outside the online hash): each player's own choice online.
  { key: 'hfr', label: 'High frame rate (smooth motion)', def: false,
    help: 'The picture is redrawn at your display\'s refresh rate (60, 120, 144 Hz ...) instead of the game\'s 12 to 25 frames per second: the camera, Conker, characters and moving objects glide smoothly between two game frames. The game itself runs exactly as before. The picture runs up to one game frame (40 to 80 ms) behind, camera cuts and teleports jump as before, and the HUD, text, particles and shadows still move at the game\'s rate. Needs more graphics work (each picture is drawn again). Off: as on the N64, one picture per game frame.' },
  { key: 'airbar', label: 'Underwater air meter', def: false, game: 8,
    help: 'While Conker is under water, a bar at the top of the screen shows the air he has left: full when he dives, red in the last quarter, empty when he starts to drown. Works with Longer breath. Off: as on the N64, only the wobbly air bubble meter, which appears after about 2 s and already looks empty at half the air.' },
  { key: 'rumble', label: 'Rumble (gamepad vibration)', def: false, game: 13,
    help: 'The game sees a Rumble Pak in each controller and your gamepad vibrates when the N64 one would (hits, explosions, heavy landings), if the browser supports gamepad vibration (Chrome / Edge with most Xbox and PlayStation pads). Takes effect at the next level or area load. Off: as now, no Rumble Pak. Saves are not affected.' },
  { key: 'crosshair', label: 'Aiming crosshair', def: false, game: 14,
    help: 'Shows the game\'s small crosshair in the middle of the screen in the first-person aim views that have none (R with the weapon kind 0x18), where the shots go. Takes effect the next time you aim. Off: as on the N64, no crosshair there; the other weapons keep their own reticles.' },
  { key: 'freecam', label: 'Free camera', def: false, game: 15,
    help: 'Single player: the right stick (or I J K L, or the mouse after a click on the picture) turns the camera freely around Conker: left / right orbits, up / down looks up / down, and Conker runs where the camera looks. The camera stays where you put it; C-down (pad B / circle, right stick click, or O) swings it back behind Conker, and the left stick click or U is C-up (camera distance). In cutscenes, look / aim views, swimming, vehicles, fixed camera spots and multiplayer the game\'s own camera runs and the right stick is the C buttons again. Never used online. Off: as on the N64, the right stick is the four C buttons.' },
  { key: 'photomode', label: 'Photo mode', def: false, game: 16,
    help: 'P (or the gamepad\'s Back / View button, or the Photo button above the picture) freezes the game and frees the camera, and hides the HUD. Move with the stick (WASD), look with the C buttons / right stick (IJKL) or the mouse (click the picture), R / Z (E / Q) up / down, D-pad left / right (arrows) roll, D-pad up / down (arrows) or the mouse wheel zoom, B (F) back to the game\'s view, L (R) shows the HUD. A (Space) or the Save button saves a PNG at twice the picture\'s resolution. P, Start (Enter) or Exit go back to the game exactly where it was. Works in cutscenes. Single player only, never online. Off: as on the N64, no photo mode.' },
  { key: 'swiminvert', label: 'Inverted swimming', def: false, game: 12,
    help: 'Under water, pushing the stick up makes Conker swim up and pulling it down makes him dive. Off: as on the N64, which steers like a plane: up dives, down rises.' },
  // P332: sliders (range: true): the value 0..100 (%) goes to the game through the same port_set_option channel.
  { key: 'volmusic', label: 'Music volume', def: 100, range: true, game: 9,
    help: 'Volume of the music (the sequenced songs), 0 to 100 %. 100 % = as on the N64.' },
  { key: 'volsfx', label: 'Sound effects volume', def: 100, range: true, game: 10,
    help: 'Volume of the sound effects (footsteps, hits, ambience, short grunts), 0 to 100 %. 100 % = as on the N64.' },
  { key: 'volspeech', label: 'Speech volume', def: 100, range: true, game: 11,
    help: 'Volume of the spoken dialogue (the MP3 voice streams), 0 to 100 %. 100 % = as on the N64.' },
];
const optOverride = {};
for (const kv of (Q.get('opt') || '').split(',')) {
  const [k, v] = kv.split(':'), o = OPTIONS.find((x) => x.key === k);
  if (k) optOverride[k] = o && o.range ? Math.max(0, Math.min(100, parseInt(v, 10) || 0)) : v === '1';
}
// P346 presets. Every option except 'online' (it only shows the Online button) belongs to them.
// Classic = the N64 game: every option off, volumes 100 %, except the hold-L cutscene skip, kept at its default (on):
//   it changes nothing unless L is held, a fresh browser is then exactly Classic, and the user chose it on by default.
// Modern = Classic + the options that add information or remove waiting without making the game easier or changing
//   how it controls: skip intro, autosave icon, health / cash always visible, air meter, crosshair, full-detail Conker,
//   rumble, (P349) hi-res menus and 2D (a sharper picture with the N64's layout and colours), (P356) smooth font (the
//   same letters with clean edges instead of magnified pixels: picture only) and (P350) widescreen (more
//   of the scene at the sides; the game logic keeps its 4:3 view), (P351) the full-resolution picture and (P351) the high
//   frame rate (smooth motion between game frames; costs about one game frame of extra delay, which suits this game). Left off on purpose: longer breath / tail spin (easier), toggle crouch / R-Look / walk and inverted
//   swimming (control tastes), no motion blur / drunk sway (part of the story's scenes), free camera (P347: it changes
//   what the right stick and IJKL do, a control choice like the toggles).
// Custom = anything else. The preset shown is stored in 'opt.preset' (changing one option stores 'custom'); a stored
// Classic / Modern whose values no longer match (a ?opt override, an option added later) is shown as what matches.
// P348: 'photomode' is not in the presets either: like 'online' it only adds a tool (a key that freezes the game for a
// photo) and changes nothing until it is used, so picking Classic or Modern neither turns it on nor off.
const PRESET_KEYS = OPTIONS.filter((o) => !['online', 'photomode', 'recorder', 'nativemenu'].includes(o.key)).map((o) => o.key);   // P357: recorder = a tool; P361: nativemenu too
const PRESET_MODERN_ON = ['skipcut', 'skipintro', 'saveicon', 'healthhud', 'cashhud', 'airbar', 'crosshair', 'conkerlod', 'rumble', 'hires2d', 'smoothfont', 'widescreen', 'fullres', 'hfr'];
const PRESETS = {
  classic: { label: 'Classic', help: 'The original N64 game: every extra off, volumes 100 %. Only the hold-L cutscene skip stays on (it does nothing unless you hold L).',
    values: (o) => (o.range ? 100 : o.key === 'skipcut') },
  modern: { label: 'Modern', help: 'Classic plus extras that show more or wait less without making the game easier: skip intro, autosave icon, health and cash always visible, underwater air meter, aiming crosshair, Conker always full detail, rumble, hi-res menus and 2D, smooth font, widescreen, full-resolution picture, high frame rate.',
    values: (o) => (o.range ? 100 : PRESET_MODERN_ON.includes(o.key)) },
  custom: { label: 'Custom', help: 'Your own mix: pick Classic or Modern to set every option at once.' },
};
// P346 test aid: ?preset=classic|modern = that preset's values as ?opt overrides for this page load (not saved);
// explicit ?opt pairs still win.
if (Q.get('preset') === 'classic' || Q.get('preset') === 'modern')
  for (const o of OPTIONS) if (PRESET_KEYS.includes(o.key) && !(o.key in optOverride)) optOverride[o.key] = PRESETS[Q.get('preset')].values(o);
const optCache = {};   // opt() is read every animation frame by the input code: cache, refreshed on change
const opt = (key) => {
  if (key in optCache) return optCache[key];
  const o = OPTIONS.find((x) => x.key === key);
  if (NETDET) return (optCache[key] = o.def);   // P337: the session's fixed options vector
  if (recCfg && (key === 'freecam' || key === 'photomode')) return (optCache[key] = false);   // P357: not part of the recorded input
  if (recCfg && o.game !== undefined) return (optCache[key] = key in recCfg.options ? recCfg.options[key] : o.def);   // P357: fixed for the recording
  if (netCfg && key === 'freecam') return (optCache[key] = false);   // P347: the camera stick is not in the lockstep input
  if (netCfg && key === 'photomode') return (optCache[key] = false);   // P348: a frozen game would stall every other player
  if (netCfg && o.game !== undefined) return (optCache[key] = netCfg.options && key in netCfg.options ? netCfg.options[key] : o.def);   // P338: the host's
  return (optCache[key] = key in optOverride ? optOverride[key] : store.get('opt.' + key, o.def));
};
let optionsLocked = false;   // P337: under ?netdet the vector is sent once before callMain, never changed afterwards
function sendOption(o) {
  if (optionsLocked) return;
  if (o.game !== undefined && M && M._port_set_option) M._port_set_option(o.game, o.range ? opt(o.key) | 0 : opt(o.key) ? 1 : 0);
}
const optionChanged = {};   // key -> callback for page-side options that need to react at once
// P346: one way to change an option, used by the panel's inputs and by the presets: drops a ?opt override, caches,
// saves (unless `save` is false: a slider while dragging), sends game options to the game (sendOption, which does nothing
// once a session's options are locked) and runs the option's page-side reaction.
function setOption(o, value, save = true) {
  delete optOverride[o.key]; optCache[o.key] = value;
  if (save) store.set('opt.' + o.key, value);
  sendOption(o);
  if (optionChanged[o.key]) optionChanged[o.key](value);
}
// under a session only the game options (the host's) count: the page-side ones (autosave icon, toggles) stay each player's
const presetMatches = (name) => PRESET_KEYS.every((k) => { const o = OPTIONS.find((x) => x.key === k); return (netCfg && o.game === undefined) || opt(k) === PRESETS[name].values(o); });
const presetShown = () => {   // under a session the host's options decide: show what they match
  const kept = netCfg || NETDET || recCfg ? null : (Q.get('preset') || store.get('opt.preset', null));
  if (kept === 'custom') return 'custom';
  if (PRESETS[kept] && presetMatches(kept)) return kept;
  return presetMatches('classic') ? 'classic' : presetMatches('modern') ? 'modern' : 'custom';
};
const optionInputs = {};   // key -> the panel's <input>, so presets and the host's session options can update it
function showOptionValue(o) {   // the input (and slider percentage) shows opt(key)
  const input = optionInputs[o.key];
  if (o.range) { input.value = opt(o.key); input.nextPercent.textContent = ` ${input.value} %`; } else input.checked = opt(o.key);
}
function showPreset() {
  const name = presetShown();
  for (const n of Object.keys(PRESETS)) $('preset-' + n).setAttribute('aria-checked', String(n === name));
  $('preset-help').textContent = PRESETS[name].help;
  return name;
}
function applyPreset(name) {   // the selector: Classic / Modern set every preset option, Custom keeps them
  if (optionsLocked) return;
  store.set('opt.preset', name);
  if (name !== 'custom') for (const k of PRESET_KEYS) {
    const o = OPTIONS.find((x) => x.key === k), v = PRESETS[name].values(o);
    if (opt(k) !== v || k in optOverride) setOption(o, v);
    showOptionValue(o);
  }
  log(`[options] preset ${name}: ` + PRESET_KEYS.map((k) => `${k}=${+opt(k)}`).join(' '));
  showPreset();
}
const optionPicked = (o) => { if (PRESET_KEYS.includes(o.key)) { store.set('opt.preset', 'custom'); showPreset(); } };
for (const n of Object.keys(PRESETS)) $('preset-' + n).onclick = () => applyPreset(n);
// P346: a session (netCfg: the host's game options) or ?netdet locks the game options: the panel shows the values the
// game runs with, and their inputs and the presets are disabled (port_set_option would not take a change any more).
function showSessionOptions() {
  for (const o of OPTIONS) {
    showOptionValue(o);
    const locked = optionsLocked && o.game !== undefined;
    optionInputs[o.key].disabled = locked;
    optionInputs[o.key].parentElement.classList.toggle('locked', locked);
    optionInputs[o.key].parentElement.title = locked ? (netCfg ? "Online: the game uses player 1's (the host's) options" : recCfg ? 'Fixed while recording (reload the page to change it)' : 'Fixed for this run') : '';
  }
  for (const n of Object.keys(PRESETS)) $('preset-' + n).disabled = optionsLocked;
  log(`[options] session options (${netCfg ? "the host's" : recCfg ? 'recording' : 'fixed'}), preset ${showPreset()}: ` + OPTIONS.filter((o) => o.game !== undefined).map((o) => `${o.key}=${+opt(o.key)}`).join(' '));
}
(function renderOptions() {
  for (const o of OPTIONS) {
    // P346: row / input / text (were l / c / t)
    const row = document.createElement('label'), input = document.createElement('input'), text = document.createElement('span');
    optionInputs[o.key] = input; input.id = 'opt-' + o.key;
    if (o.range) {   // P332 slider: 0..100 %, sent while dragging, saved on release
      input.type = 'range'; input.min = 0; input.max = 100; input.step = 5;
      input.nextPercent = document.createElement('b');
      input.oninput = () => { setOption(o, +input.value, false); input.nextPercent.textContent = ` ${input.value} %`; };
      input.onchange = () => { setOption(o, +input.value); optionPicked(o); log(`[options] ${o.key} ${input.value}`); };
      text.textContent = o.label; text.appendChild(input.nextPercent);
    } else {
      input.type = 'checkbox';
      input.onchange = () => { setOption(o, input.checked); optionPicked(o); log(`[options] ${o.key} ${input.checked ? 'on' : 'off'}`); };
      text.textContent = o.label;
    }
    showOptionValue(o);
    const h = document.createElement('small'); h.textContent = o.help; text.appendChild(h);
    if (o.range) row.append(text, input); else row.append(input, text);
    $('options').appendChild(row);
  }
  showPreset();
})();

// ---------------------------------------------------------------- IndexedDB (ROM cache, saves)
let dbp = null;
function db() {
  if (!dbp) dbp = new Promise((res, rej) => {
    const r = indexedDB.open('conker-port', 3);   // P357: version 3 adds 'recordings'
    r.onupgradeneeded = () => {
      const d = r.result;
      if (!d.objectStoreNames.contains('rom')) d.createObjectStore('rom');
      if (!d.objectStoreNames.contains('saves')) d.createObjectStore('saves');
      if (!d.objectStoreNames.contains('recordings')) d.createObjectStore('recordings');   // P357 input recordings
    };
    r.onerror = () => rej(r.error);
    r.onsuccess = () => res(r.result);
  });
  return dbp;
}
async function idb(storeName, mode, fn) {
  const d = await db();
  return new Promise((res, rej) => {
    const tx = d.transaction(storeName, mode);
    const q = fn(tx.objectStore(storeName));
    tx.oncomplete = () => res(q && q.result);
    tx.onerror = () => rej(tx.error);
  });
}

// ---------------------------------------------------------------- ROM: byte order, SHA-1, drop zone
function toZ64(b) {
  const m = (b[0] << 24 | b[1] << 16 | b[2] << 8 | b[3]) >>> 0;
  if (m === 0x80371240) return b;
  const o = new Uint8Array(b.length);
  if (m === 0x37804012) { for (let i = 0; i < b.length; i += 2) { o[i] = b[i + 1]; o[i + 1] = b[i]; } return o; } // .v64
  if (m === 0x40123780) { for (let i = 0; i < b.length; i += 4) { o[i] = b[i + 3]; o[i + 1] = b[i + 2]; o[i + 2] = b[i + 1]; o[i + 3] = b[i]; } return o; } // .n64
  throw new Error('not an N64 ROM (magic ' + m.toString(16) + ')');
}
async function sha1(b) {
  if (!crypto.subtle) return '?';
  const h = new Uint8Array(await crypto.subtle.digest('SHA-1', b));
  return Array.from(h, (x) => x.toString(16).padStart(2, '0')).join('');
}
async function setRom(bytes, from) {
  romBytes = toZ64(bytes);
  romSha1 = await sha1(romBytes);
  romOk = romSha1 === EU_SHA1;
  const mb = (romBytes.length / 1048576).toFixed(0);
  if (romOk) status(`ROM: Conker EU, SHA-1 ok (${mb} MB, ${from})`, 'ok');
  else status(`ROM SHA-1 ${romSha1.slice(0, 12)}… is not the EU ROM (${from})`, 'bad');
  $('drop').hidden = romOk;
  $('ready').hidden = !romOk || !!running;   // P360: the Press Start screen
  $('start').disabled = !!running || !romOk;
  $('eep-export').disabled = !romOk;
  return romOk;
}
async function takeFile(f) {
  if (!f) return;
  try {
    const ok = await setRom(new Uint8Array(await f.arrayBuffer()), f.name);
    if (ok) await idb('rom', 'readwrite', (s) => s.put(romBytes, 'eu')).catch(() => {});
  } catch (err) { status('ROM: ' + err.message, 'bad'); log('ROM: ' + err.message, 'fail'); }
}
$('rom').addEventListener('change', (e) => takeFile(e.target.files[0]));
// iOS greys out files whose extension has no known type (.z64 / .n64 / .eep), so no filter there;
// the ROM is checked by SHA-1 anyway
const IOS = /iPad|iPhone|iPod/.test(navigator.userAgent) || (navigator.platform === 'MacIntel' && navigator.maxTouchPoints > 1);
if (IOS) {
  for (const id of ['rom', 'eep-import']) $(id).removeAttribute('accept');
}
{
  const dz = $('drop');
  const over = (on) => (e) => { e.preventDefault(); dz.classList.toggle('over', on); };
  document.addEventListener('dragover', over(true));
  document.addEventListener('dragleave', (e) => { if (!e.relatedTarget) dz.classList.remove('over'); });
  document.addEventListener('drop', (e) => {
    e.preventDefault(); dz.classList.remove('over');
    const f = e.dataTransfer && e.dataTransfer.files[0];
    if (!f) return;
    if (/\.eep$/i.test(f.name)) importEep(f); else if (!running) takeFile(f);
  });
}

// ---------------------------------------------------------------- input -> PIF pad state
// N64 button bits (PR/os_cont.h)
const N64 = { A: 0x8000, B: 0x4000, Z: 0x2000, START: 0x1000, DU: 0x0800, DD: 0x0400, DL: 0x0200, DR: 0x0100,
              L: 0x0020, R: 0x0010, CU: 0x0008, CD: 0x0004, CL: 0x0002, CR: 0x0001 };
const INPUTS = [  // [id, label]; stick directions are pseudo-buttons
  ['UP', 'Stick up'], ['DOWN', 'Stick down'], ['LEFT', 'Stick left'], ['RIGHT', 'Stick right'], ['HALF', 'Half tilt'],
  ['A', 'A'], ['B', 'B'], ['Z', 'Z'], ['L', 'L'], ['R', 'R'], ['START', 'Start'],
  ['CU', 'C up'], ['CD', 'C down'], ['CL', 'C left'], ['CR', 'C right'],
  ['DU', 'D-pad up'], ['DD', 'D-pad down'], ['DL', 'D-pad left'], ['DR', 'D-pad right'],
  ['CAMZOOM', 'Free camera: C up (distance)'], ['CAMBACK', 'Free camera: C down (behind Conker)'],
  ['PHOTO', 'Photo mode on / off'],   // P348: page input, not an N64 button
];
const DEFAULT_KEYS = { UP: 'KeyW', DOWN: 'KeyS', LEFT: 'KeyA', RIGHT: 'KeyD', HALF: 'ControlLeft',
  A: 'Space', B: 'KeyF', Z: 'KeyQ', L: 'KeyR', R: 'KeyE', START: 'Enter',
  CU: 'KeyI', CD: 'KeyK', CL: 'KeyJ', CR: 'KeyL', DU: 'ArrowUp', DD: 'ArrowDown', DL: 'ArrowLeft', DR: 'ArrowRight',
  CAMZOOM: 'KeyU', CAMBACK: 'KeyO', PHOTO: 'KeyP' };
// W3C Standard Gamepad: 0 A/cross, 1 B/circle, 2 X/square, 3 Y/triangle, 4 LB, 5 RB, 6 LT, 7 RT,
// 8 back, 9 start, 10 / 11 stick clicks, 12-15 d-pad. Left stick = N64 stick, right stick = C-buttons (P347: or the
// free camera's stick with that option on; CAMZOOM / CAMBACK only act with the option on).
const DEFAULT_PAD = { A: 0, B: 2, Z: 6, L: 4, R: 5, START: 9, CD: 1, CL: 3, DU: 12, DD: 13, DL: 14, DR: 15, CAMZOOM: 10, CAMBACK: 11, PHOTO: 8 };
let keyMap = Object.assign({}, DEFAULT_KEYS, store.get('keys', {}));
let padMap = Object.assign({}, DEFAULT_PAD, store.get('padbuttons', {}));
const keysDown = new Set();
let listening = null; // [kind, id, button] while remapping

const STICK = 80;   // typical full deflection of an N64 stick (raw range about +-85)
// unit-disc vector -> N64 counts inside the octagonal gate: 80 on the axes, (70, 70) at the corners
function octagon(x, y) {
  const m = Math.min(1, Math.hypot(x, y)), ax = Math.abs(x), ay = Math.abs(y), mx = Math.max(ax, ay);
  if (m < 1e-6) return [0, 0];
  const k = m * STICK * (1 - 0.125 * Math.min(ax, ay) / mx) / mx;
  return [Math.round(x * k), Math.round(y * k)];
}
// P347 option "Free camera": the four C inputs (IJKL, the right stick) become one camera stick {cx, cy} (N64 counts,
// y up) that goes to pc_pif.c (port_cam_state) instead of C bits; pc_pif.c gives it to the free camera, or turns it
// back into C buttons wherever the free camera does not hold the camera. CAMZOOM / CAMBACK give C-up / C-down then.
const C_BITS = N64.CU | N64.CD | N64.CL | N64.CR;
function keyboardPad() {
  let b = 0, x = 0, y = 0, cx = 0, cy = 0;
  const on = (id) => keyMap[id] && keysDown.has(keyMap[id]);
  for (const [id] of INPUTS) if (N64[id] && on(id)) b |= N64[id];
  x = (on('RIGHT') ? 1 : 0) - (on('LEFT') ? 1 : 0);
  y = (on('UP') ? 1 : 0) - (on('DOWN') ? 1 : 0);
  let [sx, sy] = octagon(x, y);
  if (on('HALF') && !opt('togglewalk')) { sx = Math.round(sx / 2); sy = Math.round(sy / 2); }  // latched: see applyLatches
  if (opt('freecam')) {
    cx = ((b & N64.CR) ? STICK : 0) - ((b & N64.CL) ? STICK : 0);
    cy = ((b & N64.CU) ? STICK : 0) - ((b & N64.CD) ? STICK : 0);
    b = (b & ~C_BITS) | (on('CAMZOOM') ? N64.CU : 0) | (on('CAMBACK') ? N64.CD : 0);
  }
  return { present: true, b, x: sx, y: sy, half: !!on('HALF'), cx, cy, photo: !!on('PHOTO'), nav: !!on('CAMBACK') };   // P358 nav: photo panel focus
}
function gamepadPad(gp) {
  let b = 0;
  const pressed = (i) => gp.buttons[i] && (gp.buttons[i].pressed || gp.buttons[i].value > 0.5);
  for (const id in padMap) if (N64[id] && pressed(padMap[id])) b |= N64[id];
  const ax = (i) => (gp.axes[i] || 0);
  // left stick: radial dead zone 0.15, rescaled, N64 y is up-positive
  let x = ax(0), y = -ax(1), m = Math.hypot(x, y);
  if (m < 0.15) { x = y = 0; } else { const s = Math.min(1, (m - 0.15) / 0.85) / m; x *= s; y *= s; }
  const [sx, sy] = octagon(x, y);
  // P348 photo mode: its on / off button and the right stick as an analog look stick (N64 counts, y up)
  const photo = padMap.PHOTO !== undefined && pressed(padMap.PHOTO);
  const nav = padMap.CAMBACK !== undefined && pressed(padMap.CAMBACK);   // P358: photo panel focus (right stick click)
  let lx = ax(2), ly = -ax(3), lm = Math.hypot(lx, ly);
  if (lm < 0.2) { lx = ly = 0; } else { const s = Math.min(1, (lm - 0.2) / 0.8) / lm; lx *= s; ly *= s; }
  const look = { rx: Math.round(lx * STICK), ry: Math.round(ly * STICK) };
  if (opt('freecam')) {   // P347: right stick -> the camera stick (radial dead zone 0.2, rescaled, 80 counts at full)
    let rx = ax(2), ry = -ax(3), rm = Math.hypot(rx, ry);
    if (rm < 0.2) { rx = ry = 0; } else { const s = Math.min(1, (rm - 0.2) / 0.8) / rm; rx *= s; ry *= s; }
    // C buttons bound to pad buttons (C-down on B / circle, C-left on Y / triangle) stay buttons
    b |= (padMap.CAMZOOM !== undefined && pressed(padMap.CAMZOOM) ? N64.CU : 0) | (padMap.CAMBACK !== undefined && pressed(padMap.CAMBACK) ? N64.CD : 0);
    return { present: true, b, x: sx, y: sy, cx: Math.round(rx * STICK), cy: Math.round(ry * STICK), photo, nav, ...look };
  }
  // right stick -> C-buttons
  if (ax(2) > 0.5) b |= N64.CR; if (ax(2) < -0.5) b |= N64.CL;
  if (ax(3) > 0.5) b |= N64.CD; if (ax(3) < -0.5) b |= N64.CU;
  return { present: true, b, x: sx, y: sy, photo, nav, ...look };
}
// ---------------------------------------------------------------- touch controls (phones / tablets)
// Floating stick: the first touch in the left zone sets the centre, dragging up to STICK_PX gives full tilt.
// Buttons hold their bit while touched; each uses its own pointer, so several can be held at once.
const touch = { b: 0, x: 0, y: 0, stickId: null, cx: 0, cy: 0 };
const STICK_PX = 50;
function setTouch(on) {
  $('touch').hidden = !on;
  document.body.classList.toggle('touch', on);
  $('t-touch').setAttribute('aria-pressed', String(on));
  store.set('touch', on);
  if (!on) { touch.b = touch.x = touch.y = 0; touch.stickId = null; }
}
const capture = (el, e) => { try { el.setPointerCapture(e.pointerId); } catch (_) { /* synthetic or already gone */ } };
(function initTouch() {
  for (const el of document.querySelectorAll('#touch .tb')) {
    const bit = N64[el.id.slice(3)];
    const ids = new Set();
    const down = (e) => {
      e.preventDefault(); capture(el, e); ids.add(e.pointerId);
      touch.b |= bit; el.classList.add('on'); if (navigator.vibrate) navigator.vibrate(8);
    };
    const up = (e) => { ids.delete(e.pointerId); if (!ids.size) { touch.b &= ~bit; el.classList.remove('on'); } };
    el.addEventListener('pointerdown', down);
    for (const ev of ['pointerup', 'pointercancel', 'lostpointercapture']) el.addEventListener(ev, up);
  }
  const zone = $('tk-stick'), base = $('tk-base'), knob = $('tk-knob');
  const place = (x, y) => { const r = zone.getBoundingClientRect(); base.style.left = (x - r.left) + 'px'; base.style.top = (y - r.top) + 'px'; };
  const rest = () => { const r = zone.getBoundingClientRect(); place(r.left + 90, r.top + r.height - 80); knob.style.transform = ''; };
  const move = (e) => {
    if (e.pointerId !== touch.stickId) return;
    let dx = e.clientX - touch.cx, dy = e.clientY - touch.cy;
    const m = Math.hypot(dx, dy);
    if (m > STICK_PX) { dx *= STICK_PX / m; dy *= STICK_PX / m; }
    knob.style.transform = `translate(${dx}px, ${dy}px)`;
    let x = dx / STICK_PX, y = -dy / STICK_PX;
    if (Math.hypot(x, y) < 0.12) x = y = 0;   // small dead zone
    [touch.x, touch.y] = octagon(x, y);
  };
  zone.addEventListener('pointerdown', (e) => {
    e.preventDefault();
    if (touch.stickId !== null) return;
    capture(zone, e);
    touch.stickId = e.pointerId; touch.cx = e.clientX; touch.cy = e.clientY;
    place(e.clientX, e.clientY); knob.style.transform = '';
  });
  zone.addEventListener('pointermove', move);
  const end = (e) => { if (e.pointerId !== touch.stickId) return; touch.stickId = null; touch.x = touch.y = 0; rest(); };
  for (const ev of ['pointerup', 'pointercancel', 'lostpointercapture']) zone.addEventListener(ev, end);
  window.addEventListener('resize', () => { if (touch.stickId === null) rest(); });
  $('touch').addEventListener('contextmenu', (e) => e.preventDefault());
  $('t-touch').onclick = () => { setTouch($('touch').hidden); if (!$('touch').hidden) rest(); };
  const coarse = window.matchMedia && matchMedia('(pointer: coarse)').matches;
  setTouch(Q.get('touch') ? Q.get('touch') === '1' : store.get('touch', coarse));
  rest();
})();

// ---------------------------------------------------------------- P324 toggle options (crouch / R-Look / walk)
// With a toggle option on, the bound input of pad 1 (keyboard, first gamepad and touch merged) latches: each new
// press (raw input goes from up to down) flips the latch, and the game sees the button held / the stick at half
// tilt for as long as the latch is on, whatever the raw input does in between. Off: the raw input passes through
// unchanged and any latch is dropped. Small labels in #latches show which latches are on.
const LATCHES = [
  { key: 'togglecrouch', bit: N64.Z, name: 'Crouch' },
  { key: 'togglerlook', bit: N64.R, name: 'R-Look' },
  { key: 'togglewalk', bit: 0, name: 'Walk' },   // bit 0 = the half-tilt pseudo-button (stick at half)
];
const latch = {}, latchPrev = {};
let latchText = '';
function applyLatches(p, halfHeld) {
  for (const l of LATCHES) {
    const raw = l.bit ? (p.b & l.bit) !== 0 : halfHeld;
    if (!opt(l.key)) latch[l.key] = false;
    else if (raw && !latchPrev[l.key]) latch[l.key] = !latch[l.key];
    latchPrev[l.key] = raw;
    if (!opt(l.key)) continue;
    if (l.bit) p.b = latch[l.key] ? p.b | l.bit : p.b & ~l.bit;
    else if (latch[l.key]) { p.x = Math.round(p.x / 2); p.y = Math.round(p.y / 2); }
  }
  const txt = LATCHES.filter((l) => latch[l.key]).map((l) => l.name).join(' ');
  if (txt !== latchText) {
    latchText = txt; $('latches').textContent = '';
    for (const n of txt ? txt.split(' ') : []) { const e = document.createElement('span'); e.textContent = n; $('latches').appendChild(e); }
    $('latches').hidden = !txt;
    for (const l of LATCHES) if (l.bit) { const tb = $('tk-' + (l.bit === N64.Z ? 'Z' : 'R')); tb.classList.toggle('latched', !!latch[l.key]); }
  }
  return p;
}

// P347 option "Free camera": mouse look. With the option on, a click on the picture captures the mouse (pointer
// lock; Esc releases it) and its movement turns the free camera (pc_pif.c sums it until the next controller read).
const mouseLook = { dx: 0, dy: 0 };
$('canvas').addEventListener('click', () => {
  if ((opt('freecam') || photo.state === 2) && running === 'game' && !document.body.classList.contains('touch') && document.pointerLockElement !== $('canvas') && $('canvas').requestPointerLock) {
    try { const r = $('canvas').requestPointerLock(); if (r && r.catch) r.catch(() => {}); } catch (_) { /* not allowed here */ }
  }
});
document.addEventListener('mousemove', (e) => {
  // ?p347mouse=1 (test aid): count mouse movement without pointer lock (headless Chrome does not grant it)
  const locked = document.pointerLockElement === $('canvas') || Q.get('p347mouse');
  if (locked && photo.state === 2) { photo.mx += e.movementX | 0; photo.my += e.movementY | 0; }   // P348 photo camera
  else if (locked && opt('freecam')) { mouseLook.dx += e.movementX | 0; mouseLook.dy += e.movementY | 0; }
});
const KEYHINT = $('keyhint').textContent;
optionChanged.freecam = (on) => {
  if (!on && document.pointerLockElement && document.exitPointerLock) document.exitPointerLock();
  $('keyhint').textContent = on ? KEYHINT.replace('IJKL C-buttons', 'IJKL / mouse free camera · U / O C-up / down') : KEYHINT;
};
optionChanged.freecam(opt('freecam'));

// ---------------------------------------------------------------- P348 option "Photo mode" (port/ultra/pc_photo.c)
// The PHOTO input (P, the gamepad's Back button, the Photo button) asks the game to freeze (port_photo_request); the
// game answers through port_photo_status (2 = on). While it is on, pad 1's input does not go to the game: it moves the
// photo camera (port_photo_input, every animation frame, in world units and degrees), and A saves the picture. The
// game draws photo frames from its frozen state with that camera (pc_photo.c). Leaving it (PHOTO, Start, Exit) puts
// the game back exactly where it was; buttons or a stick still held then reach the game only after they were released.
// Mouse: a click on the picture captures it (pointer lock) to look around; the wheel zooms.
const photo = { state: 0, prevB: 0, prevKey: false, hud: false, mx: 0, my: 0, wheel: 0, last: 0, busy: false,
  maskB: 0, maskStick: false, toastTimer: null, scale: Math.max(1, Math.min(4, +(Q.get('photoscale') || 2))), png: null };
const PHOTO_WHY = { 1: 'Photo mode is off in Options', 2: 'no photo mode online', 3: 'photo mode needs the 3D view of a single-player game (not a menu, the pause screen, split screen or loading)',
  4: 'photo mode is not available (conker_netx.txt did not load)', 5: 'not enough memory for photo mode' };
function photoToast(text) {
  $('photo-toast').textContent = text; $('photo-toast').hidden = false;
  clearTimeout(photo.toastTimer); photo.toastTimer = setTimeout(() => { $('photo-toast').hidden = true; }, 2500);
}
function photoRequest(on) {
  if (!M || !M._port_photo_request || running !== 'game') return;
  if (on && (!opt('photomode') || netCfg || NETDET || recCfg || userPaused)) return;
  const r = M._port_photo_request(on ? 1 : 0);
  log(`[photo] ${on ? 'start' : 'leave'} requested (state ${r})`);
  if (on) photo.asked = performance.now();
}
function photoShow(on) {
  document.body.classList.toggle('photo', on);
  $('photo').hidden = !on;
  lookShow(on);   // P358
  $('photo-btn').setAttribute('aria-pressed', String(on));
  if (!on && document.pointerLockElement && document.exitPointerLock && !opt('freecam')) document.exitPointerLock();
  applyPause();   // the sound is off while photo mode is on
}
// one animation frame of pad 1 while photo mode may be on; true = photo mode has the input (do not send it to the game)
function photoPoll(d) {
  if (!M || !M._port_photo_status || running !== 'game') return false;
  const st = M._port_photo_status(), was = photo.state, now = performance.now();
  if (d.photo && !photo.prevKey && !userPaused) photoRequest(!(st === 2 || st === 1));
  photo.prevKey = !!d.photo;
  photo.state = st;
  if (st === 2 && was !== 2) { photo.hud = false; photo.mx = photo.my = photo.wheel = 0; photo.prevB = d.b; photo.last = now; rumbleStopAll(); photoShow(true); log('[photo] on'); }
  if (st !== 2 && was === 2) { photo.maskB = d.b; photo.maskStick = true; photoShow(false); log('[photo] off'); }
  if (st < 0 && photo.asked) { photoToast(PHOTO_WHY[-st] || 'photo mode did not start'); log(`[photo] not started: ${PHOTO_WHY[-st]}`); photo.asked = 0; }
  if (st === 2) photo.asked = 0;
  if (st !== 2) return st === 1 || st === 3;
  const dt = Math.min(0.1, (now - photo.last) / 1000);
  let b = d.b, fresh = b & ~photo.prevB;
  photo.last = now; photo.prevB = b;
  const panel = lookTick(dt, d, fresh);   // P358 Pose / Outfit panel; with its focus on it has the D-pad and A
  b &= ~panel; fresh &= ~panel;
  if (fresh & N64.START) { photoRequest(false); return true; }
  if (fresh & N64.A) photoCapture();
  let flags = 0;
  if (fresh & N64.B) flags |= 2;                   // back to the game's view
  if (fresh & N64.L) photo.hud = !photo.hud;
  if (photo.hud) flags |= 1;
  // look: the free camera's stick (IJKL / right stick with that option), else the analog right stick, else the C buttons
  const lx = d.cx || d.rx || ((b & N64.CR) ? STICK : 0) - ((b & N64.CL) ? STICK : 0);
  const ly = d.cy || d.ry || ((b & N64.CU) ? STICK : 0) - ((b & N64.CD) ? STICK : 0);
  const fwd = d.y / STICK * 500 * dt, right = d.x / STICK * 500 * dt;
  const up = (((b & N64.R) ? 1 : 0) - ((b & N64.Z) ? 1 : 0)) * 350 * dt;
  const dyaw = lx / STICK * 90 * dt + photo.mx * 0.15, dpitch = ly / STICK * 60 * dt - photo.my * 0.15;
  const droll = (((b & N64.DR) ? 1 : 0) - ((b & N64.DL) ? 1 : 0)) * 45 * dt;
  const zoom = Math.exp((((b & N64.DD) ? 1 : 0) - ((b & N64.DU) ? 1 : 0)) * 0.9 * dt) * Math.pow(1.1, photo.wheel / 100);
  photo.mx = photo.my = photo.wheel = 0;
  M._port_photo_input(fwd, right, up, dyaw, dpitch, droll, zoom, flags);
  if (now - (photo.infoAt || 0) > 200) {
    photo.infoAt = now;
    const I = (i) => M._port_photo_info(i);
    $('photo-info').textContent = `field of view ${I(7).toFixed(0)}° · roll ${I(5).toFixed(0)}° · ${I(8).toFixed(0)} units from the start · HUD ${photo.hud ? 'shown' : 'hidden'}`;
  }
  return true;
}
function photoMaskAfter(d) {   // after photo mode: held buttons / a deflected stick stay off until released
  if (photo.maskB) { photo.maskB &= d.b; d.b &= ~photo.maskB; }
  if (photo.maskStick) {
    if (Math.abs(d.x) < 10 && Math.abs(d.y) < 10 && !d.cx && !d.cy) photo.maskStick = false;
    else { d.x = d.y = 0; d.cx = d.cy = 0; }
  }
}
// A / Save: the picture as a PNG at photo.scale times the canvas resolution (default 2: 1280 x 960). The canvas's drawing
// buffer is enlarged, the photo frame drawn again at that size (the renderer scales every N64 pixel), copied, and the
// canvas set back. Test aid: ?photoscale=N (1..4); window.__photo.pngB64() = the last PNG as base64.
async function photoCapture() {
  if (photo.busy || photo.state !== 2) return;
  photo.busy = true;
  const c = $('canvas'), w0 = c.width, h0 = c.height, k = photo.scale;
  let blob = null;
  try {
    if (k !== 1) { c.width = w0 * k; c.height = h0 * k; M._port_gfx_resize(c.width, c.height); }
    M._port_photo_render();   // switches fibers (asyncify): its return value is not reliable, ask port_photo_info(9)
    const drawn = M._port_photo_info(9) > 0, ms = M._port_photo_info(10);
    blob = await new Promise((res) => c.toBlob(res, 'image/png'));
    log(`[photo] picture ${c.width} x ${c.height}${drawn ? '' : ' (no new frame drawn)'} in ${ms.toFixed(0)} ms: ${blob ? blob.size : 0} bytes`);
  } finally {
    if (k !== 1) { c.width = w0; c.height = h0; M._port_gfx_resize(w0, h0); M._port_photo_render(); }
    photo.busy = false;
  }
  if (!blob) { photoToast('the picture could not be saved'); return; }
  photo.png = blob;
  const t = new Date(), p2 = (n) => String(n).padStart(2, '0');
  const name = `conker-photo-${t.getFullYear()}${p2(t.getMonth() + 1)}${p2(t.getDate())}-${p2(t.getHours())}${p2(t.getMinutes())}${p2(t.getSeconds())}.png`;
  const a = document.createElement('a');
  a.href = URL.createObjectURL(blob); a.download = name;
  document.body.appendChild(a); a.click(); a.remove();
  setTimeout(() => URL.revokeObjectURL(a.href), 10000);
  $('photo-flash').classList.remove('go'); void $('photo-flash').offsetWidth; $('photo-flash').classList.add('go');
  photoToast(`saved ${name} (${w0 * k} x ${h0 * k})`);
}
window.__photo = {
  status: () => (M && M._port_photo_status ? M._port_photo_status() : 0),
  enter: () => photoRequest(true), leave: () => photoRequest(false), capture: () => photoCapture(),
  info: () => (M ? [0, 1, 2, 3, 4, 5, 6, 7, 8].map((i) => +M._port_photo_info(i).toFixed(2)) : null),
  // P358 test aids: the look (pose / outfit) as the page sets it, and the game's reports (pc_photo.c LK_* / R_*)
  move: (fwd, right, up, yaw, pitch, zoom) => { M._port_photo_input(fwd, right, up, yaw || 0, pitch || 0, 0, zoom || 1, 0); },
  // P358: the page's own look (what the panel shows): patch = fields of the look (mats: {model: {key: {hide, tint, amt, tex}}}); null = Reset
  lookPage: (patch) => { if (patch === null) Object.assign(look, LOOK_DEFAULT()); else { const m = patch.mats; delete patch.mats; Object.assign(look, patch);
    for (const mo in m || {}) { look.mats[mo] = look.mats[mo] || {}; for (const k in m[mo]) look.mats[mo][k] = Object.assign({ hide: false, tint: '#ff3030', amt: 0, tex: -1 }, look.mats[mo][k], m[mo][k]); } }
    lookPush(); lookBuild(); return JSON.stringify(look).slice(0, 300); },
  lookSet: (k, i, v) => { M._port_photo_look_set(k, i, v); }, lookInfo: (w, i) => M._port_photo_look_info(w, i || 0),
  lookDump: () => { const I = (w, i) => M._port_photo_look_info(w, i || 0), r = (w, n) => [...Array(n).keys()].map((i) => I(w, i));
    return `model ${I(3)} anims ${I(0)} (bad ${r(1, I(0)).reduce((a, b) => a + b, 0)}) playing ${I(20)} @${I(21) / 100} group [${r(4, I(5))}] own att [${r(8, I(9)).map((k) => (k >> 8) + '/' + (k & 255))}] items ${[...Array(63).keys()].map((i) => (i + 1) + ':' + I(6, i + 1) + '/' + I(7, i + 1)).join(' ')}`; },
  lookState: () => { const I = (w, i) => M._port_photo_look_info(w, i || 0), r = (w, n) => [...Array(n).keys()].map((i) => I(w, i));
    return `drawn ${I(10)} dls ${I(11)} mask ${I(12)} frames ${I(2)} err ${I(22)} face [${r(19, 4)}] mats ${r(14, I(13)).map((k, i) => k + ':' + I(15, i)).join(' ')} tex ${r(17, I(16)).map((id, i) => i + '=' + id + '/' + (I(18, i) >> 16) + 'x' + (I(18, i) & 0xFFFF)).join(' ')}`; },
  pngB64: () => new Promise((res) => {
    if (!photo.png) return res('');
    const r = new FileReader(); r.onload = () => res(String(r.result).split(',')[1] || ''); r.readAsDataURL(photo.png);
  }),
};
$('photo-btn').onclick = () => { const on = !(photo.state === 2 || photo.state === 1); drawerSet(false); photoRequest(on); };   // P360: from the menu drawer
$('photo-save').onclick = () => { $('canvas').focus(); photoCapture(); };   // focus back: Space must not press the button again
$('photo-exit').onclick = () => { $('canvas').focus(); photoRequest(false); };
$('canvas').addEventListener('wheel', (e) => { if (photo.state === 2) { e.preventDefault(); photo.wheel += e.deltaY; } }, { passive: false });
optionChanged.photomode = (on) => {
  $('photo-btn').hidden = !on || !!netCfg;
  if (!on && photo.state === 2) photoRequest(false);
};
optionChanged.photomode(opt('photomode'));
// P358: names of what Conker's data holds, as far as identified (docs: PLAYING.md photo mode). Animation ids of his bank
// (model 0 and the models of his skeleton group), models of that group, item lists (g_setup_cmd_lists), materials.
// Animation names come from the code that starts them (player_move_animation, obj_jump_swim_glide_update,
// player_swim_update, player_hit_reaction, player_idle_animation, ...); '?' = the code's context, not checked by eye.
const PHOTO_ANIM_NAMES = {
  0x000: 'default', 0x002: 'item idle', 0x005: 'put down', 0x007: 'hurt (kind 2)', 0x00C: 'walk', 0x00E: 'idle variant',
  0x00F: 'stand (idle)', 0x011: 'swim fast', 0x013: 'hurt (kind 1)', 0x014: 'step to grab', 0x016: 'walk (slow)?',
  0x017: 'swim carrying', 0x018: 'float under water', 0x019: 'walk (slow)', 0x01E: 'hurt (kind 14)', 0x01F: 'swim backwards',
  0x021: 'stop', 0x022: 'swim stroke', 0x024: 'hurt (kind 4/5, drowning?)', 0x025: 'idle variant', 0x028: 'hurt (kind 3)',
  0x02B: 'run (chased)', 0x02C: 'idle variant', 0x02F: 'hurt (kind 10)', 0x032: 'jump', 0x037: 'double jump', 0x038: 'fall / let go',
  0x03A: 'idle (holding)', 0x03B: 'high fall', 0x03E: 'idle variant', 0x040: 'ledge pull-up', 0x042: 'ledge hang', 0x043: 'jump (from glide)?',
  0x044: 'idle (holding)', 0x04B: 'land', 0x04E: 'walk (state 0x17)?', 0x058: 'hurt (kind 0)', 0x065: 'push', 0x066: 'push 2',
  0x06D: 'swim (surface)', 0x07E: 'walk carrying (kind 9)', 0x07F: 'knocked down', 0x0A5: 'slide push', 0x0CB: 'tread water carrying',
  0x0CC: 'tread water (surface)', 0x0CE: 'swim stroke 2', 0x0D0: 'turn', 0x0D1: 'tread water', 0x0D6: 'drop', 0x0E8: 'walk carrying (kind 0x16)',
  0x0E9: 'helicopter tail spin', 0x0EA: 'ledge climb', 0x0EB: 'long jump (Z)', 0x0EC: 'walk carrying', 0x0ED: 'walk carrying (kind 0x15)',
  0x0F8: 'run carrying', 0x101: 'turn 2', 0x111: 'walk (kind 0x19)', 0x112: 'run (kind 0x19)', 0x123: 'walk (kind 0x21)', 0x124: 'run (kind 0x21)',
  0x158: 'walk (kind 0x24)', 0x159: 'run (kind 0x24)', 0x15B: 'walk (kind 0x22)', 0x15C: 'run (kind 0x22)', 0x161: 'walk (kind 0x23)',
  0x162: 'run (kind 0x23)', 0x16F: 'hurt (kind 7)', 0x170: 'hurt (kind 6/8/15)', 0x178: 'walk (kind 0x26)', 0x179: 'run (kind 0x26)',
  0x19E: 'jump holding (kind 0x21)', 0x1B0: 'run (kind 0x2D)', 0x1B1: 'walk (kind 0x2D)', 0x1E1: 'walk (kind 0x38)', 0x1E2: 'run (kind 0x38)',
  0x1EC: 'walk (kind 0x39)', 0x1ED: 'run (kind 0x39)', 0x1F5: 'walk (kind 0x37)', 0x1F6: 'run (kind 0x37)', 0x1FB: 'walk (kind 0x3A)',
  0x221: 'hit reaction', 0x223: 'walk (kind 0x3B)', 0x224: 'run (kind 0x3B)', 0x22C: 'run carrying (kind 9)', 0x279: 'high jump',
  0x283: 'crouch (Z)?', 0x28E: 'turn 3', 0x297: 'ledge drop down', 0x2C6: 'walk carrying (kind 0x16) 2', 0x2D4: 'death (kind 11)',
  0x2D6: 'death (kind 12)', 0x2D8: 'death (kind 13)', 0x302: 'walk (2)', 0x303: 'run (2)', 0x34F: 'idle (end)?',
};
// all 187 models (object types), named in P359 from the code (functions that test the type), the levels whose setup
// lists / loaded models hold them, and photo-mode renders looked at one by one; '(guess)' = not certain
// (docs/port/photo_models.tsv: confidence and evidence per model)
const PHOTO_MODEL_NAMES = {
  0: 'Conker', 1: 'Conker, detail 2', 2: 'Conker, detail 3', 3: 'Conker, detail 4', 4: 'Conker, detail 5', 5: 'wasp',
  6: 'Rare logo', 7: 'bee with crown (guess)', 8: 'Bullfish', 9: 'dark slab (water / rock piece) (guess)',
  10: 'catfish', 11: 'unknown (no animation bank)', 12: 'claw on a pole (guess)', 13: 'hay pile with eyes',
  14: 'corn sack with eyes', 15: 'spiky ball creature, purple', 16: 'rolling boulder',
  17: 'spearman, purple vest (guess)', 18: 'gun turret with searchlight', 19: 'beehive, small',
  20: 'spearman with flag (guess)', 21: 'wooden crate with eyes', 22: 'caveman', 23: 'hedgehog (big face) (guess)',
  24: 'metal crate with face, angry', 25: 'paper scroll (guess)', 26: 'black spiky creature, purple stripes (guess)',
  27: 'green leaf / shard (guess)', 28: 'metal pipe', 29: 'grey cord (guess)',
  30: 'metal crate with face, eyelashes', 31: 'wooden pallet', 32: 'cheese with eyes', 33: 'bull',
  34: 'Marvin the mouse', 35: 'beehive, large', 36: 'water surface', 37: 'dung ball', 38: 'pincer on a bone (guess)',
  39: 'conker (chestnut) shell (guess)', 40: 'tank', 41: 'frog in armour (guess)', 42: 'unknown (no animation bank)',
  43: 'furnace / boiler (guess)', 44: 'paint pot with eyes', 45: 'paint brush', 46: 'dark boulder (guess)',
  47: 'white rope / cord (guess)', 48: 'metal plate (guess)', 49: 'big brown creature (guess)',
  50: 'red hexagonal ring (guess)', 51: 'lava rock (explosive) (guess)',
  52: 'blue gremlin carrying a barrel (guess)', 53: 'white bones / claws (guess)', 54: 'raptor, purple',
  55: 'unknown (draws nothing here)', 56: 'rock bouncer (bow tie)', 57: 'wooden tower, striped legs (guess)',
  58: 'fire imp', 59: 'thin figure in black (guess)', 60: 'checkered pickup with eyes (guess)', 61: 'imp, black',
  62: 'pink worm (guess)', 63: 'green leaf (guess)', 64: 'skull and debris (guess)', 65: 'small wooden peg (guess)',
  66: 'blue gremlin in black armour with gun (guess)', 67: 'faint mesh / web (guess)', 68: 'dung beetle',
  69: 'Haybot', 70: 'spiky ball creature, blue', 71: 'robot spider (guess)', 72: 'unknown (no animation bank)',
  73: 'wooden trough / frame (guess)', 74: 'periscope gun turret (guess)', 75: 'Haybot robot core (guess)',
  76: 'spiky ball creature, green', 77: 'grenade', 78: 'two black pipes (guess)', 79: 'missile with eyes (guess)',
  80: 'bat, brown (hanging)', 81: 'pedestal with wires (guess)', 82: 'spiky mine with cigar',
  83: 'baby dinosaur (big jaws) (guess)', 84: 'caveman, big (stone club)', 85: 'empty slot', 86: 'N64 logo piece',
  87: 'money bag', 88: 'SHC squirrel soldier', 89: 'red pelt / cloth (guess)', 90: 'Tediz',
  91: 'SHC squirrel soldier, goggles', 92: 'wire strands (guess)', 93: 'black block (guess)',
  94: 'Experiment (xenomorph)', 95: 'Tediz pieces (guess)', 96: 'metal weight on chain',
  97: 'metal weight on chain 2', 98: 'unknown (no animation bank)', 99: 'small blue and red bits (guess)',
  100: 'caveman with bone club', 101: 'small red head on blue (guess)', 102: 'wooden crate with eyes, dark',
  103: 'bomber plane', 104: 'unknown (no animation bank)', 105: 'cavewoman (guess)', 106: 'bone',
  107: 'blue tusked fish (guess)', 108: 'sunflower', 109: 'queen bee head (honeycomb) (guess)',
  110: 'grey cord 2 (guess)', 111: 'N64 logo', 112: 'Gregg the Grim Reaper', 113: 'money bag, dark',
  114: 'Berri (purple bikini)', 115: 'long dark pipe (guess)', 116: 'Tediz 2', 117: 'teddy bear 2 (his skeleton)',
  118: 'Panther King (guess)', 119: 'tank 2', 120: 'olive creature (big head) (guess)', 121: 'cow',
  122: 'Tediz variant (no animation bank) (guess)', 123: 'Tediz buzzsaw spider', 124: 'small bird (guess)',
  125: 'stick / match (guess)', 126: 'torch (guess)', 127: 'barrel', 128: 'Conker, army helmet',
  129: 'iris hatch (guess)', 130: 'mech suit', 131: 'missile', 132: 'red button (guess)',
  133: 'red-cross sign (guess)', 134: 'weasel henchman, sunglasses', 135: 'SHC Sergeant',
  136: 'caveman, red pelt (his skeleton) (guess)', 137: 'bomb', 138: 'cannon robot (guess)',
  139: 'Birdy the scarecrow', 140: 'key with eyes', 141: 'Tediz nurse', 142: 'gargoyle', 143: 'raptor',
  144: 'caveman (his skeleton)', 145: 'fat cave woman (guess)', 146: 'Great Mighty Poo', 147: 'sweetcorn with eyes',
  148: 'unknown small shard (guess)', 149: 'tree branch hand (guess)', 150: 'Conker, black coat (Heist)',
  151: 'Berri (Heist catsuit)', 152: 'Heist lobby guard (guess)', 153: 'Professor von Kriplespac',
  154: 'bat, green eyes', 155: 'bat, yellow eyes', 156: 'villager, hat and moustache (guess)',
  157: 'villager, glasses and red jacket (guess)', 158: 'spiky dome mine (guess)',
  159: 'villager, black jacket (guess)', 160: 'villager woman, purple dress (guess)', 161: 'small red top (guess)',
  162: 'black spikes (guess)', 163: 'unknown (draws nothing here)', 164: 'Count Batula',
  165: 'dinosaur, orange (guess)', 166: 'stalk with eyes (guess)', 167: 'Conker wrapped up (guess)',
  168: 'striped flag \'2\' (guess)', 169: 'red cloth (guess)', 170: 'lightning bolt', 171: 'dinosaur egg',
  172: 'rolling ball, orange', 173: 'wasp 2', 174: 'wasp 3', 175: 'wasp 4',
  176: 'officer in green uniform (his skeleton) (guess)', 177: 'teddy bear (his skeleton)',
  178: 'Grim Reaper (his skeleton)', 179: 'mouse, spotted (guess)', 180: 'skeleton',
  181: 'grey brute in white shirt (guess)', 182: 'bloody teeth (guess)', 183: 'weasel band: double bass',
  184: 'weasel band: saxophone', 185: 'weasel band: drums', 186: 'bomb, grey (guess)' };
// setup command lists (held items / gear), by eye on Conker at level 0x29; the others show nothing on him there
const PHOTO_ITEM_NAMES = { 2: 'big blade', 4: 'cloth (cyan)', 20: 'nuclear warhead', 22: 'pistol', 23: 'gas mask', 24: 'striped bazooka',
  25: 'big gun barrel', 33: 'bone club', 35: 'green cap', 37: 'black mask', 40: 'machete', 41: 'throwing knives', 46: 'chain',
  48: 'sunglasses', 49: 'scythe and cloak', 50: 'black hat', 51: 'net', 54: 'crate with a blade', 55: 'red cape', 60: 'yellow helmet',
  62: 'leaf crown' };
// materials (texture entries, face slots, untextured groups) of model 0, by hiding each one (P358)
const PHOTO_MAT_NAMES = { 0: { 13: 'fur (head, tail)', 5: 'hoodie (side)', 6: 'hoodie (front)', 1: 'shoes', 4: 'legs', 2: 'muzzle',
  83: 'mouth', 64: 'eyelids 1', 65: 'eyelids 2', 66: 'eye 1', 67: 'eye 2' } };

// ---------------------------------------------------------------- P358 photo mode: Pose and Outfit (the "look")
// The page only chooses; pc_photo.c keeps the choice (port_photo_look_set) and the game applies it inside the photo
// frames (game_eu_15A210.c photo_look_*), so it never reaches the game itself: leaving photo mode restores the game
// exactly as it was (the snapshot), whatever was chosen here. What Conker is made of comes back as reports
// (port_photo_look_info). The choices are remembered for this browser session (sessionStorage 'photo.look') and
// applied again whenever photo mode starts. Gamepad / keyboard: O (the right stick click) gives the panel the D-pad:
// up / down choose a control, left / right change it, A presses it; O again gives the D-pad back to the camera.
const LK = { ANIM: 0, FRAME: 1, MODEL: 2, ITEM: 3, ATT_HIDE: 4, DL_HIDE: 5, DL_SHOW: 6, FACE: 7, MAT_HIDE: 8, MAT_TINT: 9, MAT_TEX: 10 };
const LR = { ANIM_COUNT: 0, ANIM_BAD: 1, FRAMES: 2, MODEL: 3, GROUP: 4, GROUP_N: 5, ITEM_KIND: 6, ITEM_ASSET: 7, ATT: 8, ATT_N: 9,
  DRAWN_MODEL: 10, DL_N: 11, DL_MASK: 12, MAT_N: 13, MAT_KEY: 14, MAT_TRIS: 15, TEX_N: 16, TEX_ID: 17, TEX_WH: 18, FACE: 19,
  ANIM_GAME: 20, FRAME_GAME: 21, ERR: 22 };
const LOOK_FPS = 25;   // animation frames per second when playing (the game steps about one frame per PAL field pair x 1.2)
const LOOK_DEFAULT = () => ({ anim: -1, frame: 0, play: false, speed: 1, model: -1, items: [0, 0, 0, 0], attHide: [], dlHide: 0, dlShow: 0,
  face: [-1, -1, -1, -1], mats: {}, min: false });
const look = (() => {
  try { const v = JSON.parse(sessionStorage.getItem('photo.look') || 'null'); if (v && typeof v === 'object') return Object.assign(LOOK_DEFAULT(), v); } catch (e) { /* no storage */ }
  return LOOK_DEFAULT();
})();
const lookUi = { built: false, drawn: -2, matSig: '', nav: false, focus: 0, prevNav: false, lastInfo: 0, frames: 0 };
function lookSave() { try { sessionStorage.setItem('photo.look', JSON.stringify(look)); } catch (e) { /* ignore */ } }
const lkInfo = (w, i) => (M && M._port_photo_look_info ? M._port_photo_look_info(w, i || 0) : 0);
const hex3 = (n) => '0x' + n.toString(16).toUpperCase().padStart(3, '0');
function animLabel(i) { const n = PHOTO_ANIM_NAMES[i]; return hex3(i) + (n ? ' ' + n : ''); }
function modelLabel(m) { return m + ' ' + (PHOTO_MODEL_NAMES[m] || 'model'); }
function itemLabel(n) {
  const k = lkInfo(LR.ITEM_KIND, n), a = lkInfo(LR.ITEM_ASSET, n);
  return (PHOTO_ITEM_NAMES[n] || ((k & 1) ? 'object ' : 'model ') + a) + ' (list ' + n + ')';
}
function matLabel(model, key) {
  const named = (PHOTO_MAT_NAMES[model] || {})[key];
  if (named) return named;
  if (key >= 80) return 'untextured ' + (key - 79);
  if (key >= 64) return ['eyelids 1', 'eyelids 2', 'eye 1', 'eye 2'][key - 64];
  return 'texture ' + lkInfo(LR.TEX_ID, key);
}
// everything chosen -> pc_photo.c (the next photo frame shows it)
function lookPush() {
  if (!M || !M._port_photo_look_set) return;
  const S = (k, i, v) => M._port_photo_look_set(k, i, v);
  S(-1, 0, 0);
  if (look.anim >= 0) { S(LK.ANIM, 0, look.anim); S(LK.FRAME, 0, Math.round(look.frame * 100)); }
  if (look.model >= 0) S(LK.MODEL, 0, look.model);
  look.items.forEach((v, i) => v && S(LK.ITEM, i, v));
  look.attHide.slice(0, 16).forEach((v, i) => S(LK.ATT_HIDE, i, v));
  if (look.dlHide) S(LK.DL_HIDE, 0, look.dlHide);
  if (look.dlShow) S(LK.DL_SHOW, 0, look.dlShow);
  look.face.forEach((v, i) => v >= 0 && S(LK.FACE, i, v));
  const mats = look.mats[lkInfo(LR.DRAWN_MODEL)] || {};
  for (const key in mats) {
    const m = mats[key];
    if (m.hide) S(LK.MAT_HIDE, +key, 1);
    if (m.amt > 0) { const c = parseInt((m.tint || '#ff0000').slice(1), 16); S(LK.MAT_TINT, +key, ((c << 8) | Math.round(m.amt * 2.55)) >>> 0 | 0); }
    if (m.tex >= 0) S(LK.MAT_TEX, +key, m.tex);
  }
  lookSave();
}
function lookChanged() { lookPush(); lookRefreshValues(); }
function el(tag, attrs, ...kids) {
  const e = document.createElement(tag);
  for (const k in attrs || {}) { if (k === 'on') for (const ev in attrs.on) e.addEventListener(ev, attrs.on[ev]); else if (k in e) e[k] = attrs[k]; else e.setAttribute(k, attrs[k]); }
  for (const c of kids) if (c != null) e.append(c);
  return e;
}
function row(label, ...kids) { return el('div', { className: 'lk-row' }, label != null ? el('span', {}, label) : null, ...kids); }
function selectOf(options, value, onchange, title) {
  const s = el('select', { title: title || '', on: { change: () => onchange(+s.value) } });
  for (const [v, t] of options) s.append(el('option', { value: String(v), textContent: t }));
  s.value = String(value);
  return s;
}
// the whole panel (photo mode starts, Reset, or the drawn model changed)
function lookBuild() {
  const P = $('photo-look');
  P.textContent = '';
  P.classList.toggle('min', !!look.min);
  P.append(el('div', { className: 'lk-head' }, el('b', { textContent: 'POSE & OUTFIT' }),
    el('span', {}, el('button', { textContent: 'Reset', title: 'Back to the game\'s own pose and outfit', on: { click: () => { const m = look.min; Object.assign(look, LOOK_DEFAULT(), { min: m }); lookPush(); lookBuild(); } } }),
      ' ', el('button', { textContent: look.min ? '+' : '–', title: 'Show / hide this panel', on: { click: () => { look.min = !look.min; lookSave(); lookBuild(); } } }))));
  // Pose
  const n = lkInfo(LR.ANIM_COUNT), opts = [[-1, 'original pose (' + animLabel(lkInfo(LR.ANIM_GAME)) + ')']];
  for (let i = 0; i < n; i++) if (!lkInfo(LR.ANIM_BAD, i)) opts.push([i, animLabel(i)]);
  const animSel = selectOf(opts, look.anim, (v) => { look.anim = v; look.frame = 0; lookChanged(); }, 'Conker\'s animation (' + (opts.length - 1) + ' with data)');
  animSel.id = 'lk-anim';
  const step = (d) => { const i = opts.findIndex((o) => o[0] === look.anim); const j = Math.max(0, Math.min(opts.length - 1, i + d)); look.anim = opts[j][0]; look.frame = 0; lookChanged(); };
  P.append(el('h4', { textContent: 'POSE' }),
    row('animation', animSel),
    row(null, el('button', { textContent: '◀ anim', on: { click: () => step(-1) } }), el('button', { textContent: 'anim ▶', on: { click: () => step(1) } }),
      el('button', { id: 'lk-play', textContent: look.play ? 'pause' : 'play', title: 'Play the animation in a loop', on: { click: () => { look.play = !look.play; lookSave(); lookRefreshValues(); } } })),
    row('frame', el('input', { type: 'range', id: 'lk-frame', min: '0', max: '1', step: '1', value: String(Math.floor(look.frame)),
      on: { input: (e) => { look.frame = +e.target.value; look.play = false; lookChanged(); } } }), el('span', { id: 'lk-frame-n', className: 'lk-note' })),
    row(null, el('button', { textContent: '◀ frame', on: { click: () => { look.frame = Math.max(0, Math.floor(look.frame) - 1); look.play = false; lookChanged(); } } }),
      el('button', { textContent: 'frame ▶', on: { click: () => { look.frame = Math.floor(look.frame) + 1; if (lookUi.frames && look.frame >= lookUi.frames) look.frame = 0; look.play = false; lookChanged(); } } }),
      el('span', {}, 'speed'), selectOf([[0.25, '¼'], [0.5, '½'], [1, '1×'], [2, '2×']], look.speed, (v) => { look.speed = v; lookSave(); })));
  // Outfit: model
  P.append(el('h4', { textContent: 'OUTFIT' }));
  const g = [];
  for (let i = 0; i < lkInfo(LR.GROUP_N); i++) g.push(lkInfo(LR.GROUP, i));
  const own = lkInfo(LR.MODEL);
  const others = [];   // models with a skeleton of their own: drawn with their own animation bank (ids of the pose list differ)
  for (let m = 0; m < 187; m++) if (!g.includes(m)) others.push([m, modelLabel(m) + ' (own skeleton)']);
  P.append(row('model', selectOf([[-1, 'his own: ' + modelLabel(own)], ...g.filter((m) => m !== own).map((m) => [m, modelLabel(m)]), ...others], look.model,
    (v) => { look.model = v; look.dlHide = look.dlShow = 0; lookChanged(); }, 'Models that share Conker\'s skeleton and animations (loaded from the ROM for the photo only)')));
  // items (setup lists)
  const items = [[0, '—']];
  for (let i = 1; i <= 63; i++) if (lkInfo(LR.ITEM_KIND, i)) items.push([i, itemLabel(i)]);
  for (let s = 0; s < 4; s++) P.append(row(s ? '' : 'items', selectOf(items, look.items[s], (v) => { look.items[s] = v; lookChanged(); }, 'Held items / gear: the game\'s attachment lists, put on Conker for the photo')));
  // his own attachments
  const na = lkInfo(LR.ATT_N);
  if (na) for (let i = 0; i < na; i++) {
    const key = lkInfo(LR.ATT, i);
    const cb = el('input', { type: 'checkbox', checked: !look.attHide.includes(key), on: { change: () => { look.attHide = look.attHide.filter((k) => k !== key); if (!cb.checked) look.attHide.push(key); lookChanged(); } } });
    P.append(row(i ? '' : 'he carries', cb, el('span', { className: 'lk-note' }, 'model ' + (key >> 8) + ' (list ' + (key & 255) + ')')));
  }
  // display lists of the drawn model (the game's own part mask)
  const drawn = lkInfo(LR.DRAWN_MODEL), ndl = lkInfo(LR.DL_N);
  if (ndl > 1) {
    const r = row('parts');
    for (let k = 0; k < ndl && k < 32; k++) {
      const hiddenByGame = (lkInfo(LR.DL_MASK) >> k) & 1;
      const cb = el('input', { type: 'checkbox', title: 'display list ' + k + (hiddenByGame ? ' (the game hides it)' : ''),
        checked: hiddenByGame ? !!((look.dlShow >> k) & 1) : !((look.dlHide >> k) & 1),
        on: { change: () => { const b = 1 << k; if (hiddenByGame) look.dlShow = cb.checked ? look.dlShow | b : look.dlShow & ~b; else look.dlHide = cb.checked ? look.dlHide & ~b : look.dlHide | b; lookChanged(); } } });
      r.append(cb);
    }
    P.append(r);
  }
  // face textures (segments 6 / 7 / 0xA / 0xB)
  const ntex = lkInfo(LR.TEX_N), tex = [];
  for (let i = 0; i < ntex; i++) tex.push({ i, id: lkInfo(LR.TEX_ID, i), w: lkInfo(LR.TEX_WH, i) >> 16, h: lkInfo(LR.TEX_WH, i) & 0xFFFF });
  ['eyelids 1', 'eyelids 2', 'eye 1', 'eye 2'].forEach((name, s) => {
    const cur = lkInfo(LR.FACE, s), t = tex[cur];
    const same = tex.filter((x) => !t || (x.w === t.w && x.h === t.h));
    P.append(row(name, selectOf([[-1, 'the game\'s (texture ' + (t ? t.id : '?') + ')'], ...same.map((x) => [x.i, 'texture ' + x.id + ' (' + x.w + '×' + x.h + ')'])], look.face[s],
      (v) => { look.face[s] = v; lookChanged(); }, 'The face texture the game puts into this slot every frame')));
  });
  // materials of the drawn model: shown / tint colour + strength / texture
  const nm = lkInfo(LR.MAT_N);
  if (nm) {
    P.append(el('h4', { textContent: 'MATERIALS · ' + modelLabel(drawn) }), el('div', { className: 'lk-note', textContent: 'shown · texture · tint colour · tint %' }));
    const mats = (look.mats[drawn] = look.mats[drawn] || {});
    for (let i = 0; i < nm; i++) {
      const key = lkInfo(LR.MAT_KEY, i), m = (mats[key] = mats[key] || { hide: false, tint: '#ff3030', amt: 0, tex: -1 });
      const t = key < 64 ? tex[key] : null;
      const texOpts = [[-1, matLabel(drawn, key) + ' · ' + lkInfo(LR.MAT_TRIS, i) + ' tris']];
      if (t) for (const x of tex) if (x.i !== key && x.w === t.w && x.h === t.h) texOpts.push([x.i, '→ texture ' + x.id]);
      P.append(el('div', { className: 'lk-mat' },
        el('input', { type: 'checkbox', checked: !m.hide, title: 'shown', on: { change: (e) => { m.hide = !e.target.checked; lookChanged(); } } }),
        selectOf(texOpts, m.tex, (v) => { m.tex = v; lookChanged(); }, t ? 'Draw it with another texture of the same size' : 'Face slots and untextured parts keep their texture'),
        el('input', { type: 'color', value: m.tint, title: 'tint colour', on: { input: (e) => { m.tint = e.target.value; if (!m.amt) m.amt = 60; lookChanged(); } } }),
        el('input', { type: 'range', min: '0', max: '100', step: '5', value: String(m.amt), title: 'tint strength (0 = none)', style: 'width: 44px', on: { input: (e) => { m.amt = +e.target.value; lookChanged(); } } })));
    }
  }
  if (lkInfo(LR.ERR)) P.append(el('div', { className: 'lk-note', textContent: ['', 'that model could not be loaded here', 'that animation could not start', ''][lkInfo(LR.ERR)] || '' }));
  lookUi.built = true; lookUi.drawn = drawn;
  lookUi.matSig = drawn + ':' + nm + ':' + ntex + ':' + lkInfo(LR.DL_N) + ':' + na;
  lookRefreshValues();
}
function lookRefreshValues() {
  const f = $('lk-frame'), fr = lkInfo(LR.FRAMES);
  lookUi.frames = look.anim >= 0 ? fr : 0;
  if (f) { f.max = String(Math.max(0, lookUi.frames - 1)); f.value = String(Math.floor(look.frame)); f.disabled = look.anim < 0; }
  if ($('lk-frame-n')) $('lk-frame-n').textContent = look.anim >= 0 ? Math.floor(look.frame) + ' / ' + Math.max(0, lookUi.frames - 1) : '—';
  if ($('lk-play')) $('lk-play').textContent = look.play ? 'pause' : 'play';
  if ($('lk-anim') && +$('lk-anim').value !== look.anim) $('lk-anim').value = String(look.anim);
}
// photo mode on: every animation frame (photoPoll). Plays the animation, rebuilds the panel when the game reports
// another model / material set (a frame after a model change), and runs the gamepad / keyboard panel focus.
function lookTick(dt, d, fresh) {
  if (!lookUi.built) { lookPush(); lookBuild(); }
  const now = performance.now();
  if (now - lookUi.lastInfo > 250) {
    lookUi.lastInfo = now;
    const sig = lkInfo(LR.DRAWN_MODEL) + ':' + lkInfo(LR.MAT_N) + ':' + lkInfo(LR.TEX_N) + ':' + lkInfo(LR.DL_N) + ':' + lkInfo(LR.ATT_N);
    if (sig !== lookUi.matSig) { lookPush(); lookBuild(); }
    else lookRefreshValues();
  }
  if (look.play && look.anim >= 0 && lookUi.frames > 1) {
    look.frame = (look.frame + dt * LOOK_FPS * look.speed) % (lookUi.frames - 1);
    M._port_photo_look_set(LK.FRAME, 0, Math.round(look.frame * 100));
    if ($('lk-frame')) { $('lk-frame').value = String(Math.floor(look.frame)); $('lk-frame-n').textContent = Math.floor(look.frame) + ' / ' + (lookUi.frames - 1); }
  }
  // panel focus: O / right stick click toggles; the D-pad and A then work the panel (returned mask: bits the camera must not see)
  if (d.nav && !lookUi.prevNav) { lookUi.nav = !lookUi.nav; $('photo-look').classList.toggle('nav', lookUi.nav); if (lookUi.nav && look.min) { look.min = false; lookBuild(); } lookFocus(0); }
  lookUi.prevNav = !!d.nav;
  if (!lookUi.nav) { document.querySelectorAll('#photo-look .nav-focus').forEach((e) => e.classList.remove('nav-focus')); return 0; }
  if (fresh & N64.DD) lookFocus(1);
  if (fresh & N64.DU) lookFocus(-1);
  const e = lookFocusEl();
  if (e && (fresh & (N64.DL | N64.DR))) {
    const dir = (fresh & N64.DR) ? 1 : -1;
    if (e.tagName === 'SELECT') { e.selectedIndex = Math.max(0, Math.min(e.options.length - 1, e.selectedIndex + dir)); e.dispatchEvent(new Event('change')); }
    else if (e.type === 'range') { e.value = String(+e.value + dir * (+e.step || 1)); e.dispatchEvent(new Event('input')); }
    else if (e.type === 'checkbox') { e.checked = !e.checked; e.dispatchEvent(new Event('change')); }
    lookFocus(0);
  }
  if (e && (fresh & N64.A)) { if (e.type === 'checkbox') { e.checked = !e.checked; e.dispatchEvent(new Event('change')); } else if (e.tagName === 'BUTTON') e.click(); lookFocus(0); }
  return N64.DU | N64.DD | N64.DL | N64.DR | N64.A;
}
function lookFocusables() { return Array.from($('photo-look').querySelectorAll('select, input, button')).filter((e) => e.offsetParent !== null && e.type !== 'color'); }
function lookFocusEl() { const l = lookFocusables(); return l[Math.max(0, Math.min(l.length - 1, lookUi.focus))]; }
function lookFocus(d) {
  const l = lookFocusables();
  if (!l.length) return;
  lookUi.focus = (lookUi.focus + d + l.length) % l.length;
  l.forEach((e, i) => e.classList.toggle('nav-focus', i === lookUi.focus));
  l[lookUi.focus].scrollIntoView({ block: 'nearest' });
}
function lookShow(on) {
  $('photo-look').hidden = !on;
  if (on) { lookUi.built = false; lookUi.nav = false; $('photo-look').classList.remove('nav'); }
}

const SKIP_ARC = 2 * Math.PI * 27;
$('skiparc').style.strokeDasharray = String(SKIP_ARC);
let lastPadText = '';
function pollInput() {
  const gps = (navigator.getGamepads ? Array.from(navigator.getGamepads()) : []).filter((g) => g && g.connected);
  if (listening && listening[0] === 'pad') {
    for (const gp of gps) gp.buttons.forEach((bt, i) => { if (bt.pressed && listening) finishListen(i); });
  }
  // pad 0 = keyboard merged with the first gamepad; pads 1-3 = further gamepads
  const pads = [keyboardPad(), null, null, null];
  const halfHeld = pads[0].half;   // the half-tilt key (P324 walk toggle)
  if (touch.b || touch.x || touch.y) { const k = pads[0]; pads[0] = { present: true, b: k.b | touch.b, x: k.x || touch.x, y: k.y || touch.y, cx: k.cx, cy: k.cy, photo: k.photo, nav: k.nav }; }
  gps.forEach((gp, i) => {
    const g = gamepadPad(gp);
    if (i === 0) { const k = pads[0]; pads[0] = { present: true, b: k.b | g.b, x: k.x || g.x, y: k.y || g.y, cx: k.cx || g.cx, cy: k.cy || g.cy, photo: k.photo || g.photo, nav: k.nav || g.nav, rx: g.rx, ry: g.ry }; }
    else if (i < 4) pads[i] = g;
  });
  readyPoll(pads[0]);   // P360: Start on the Press Start screen
  if (window.GMenu && GMenu.poll(pads[0])) pads[0] = { present: true, b: 0, x: 0, y: 0, cx: 0, cy: 0 };   // P361: the game-style menu has pad 1: the game (and online the lockstep, the recorder) gets an idle pad
  if (photoPoll(pads[0])) { requestAnimationFrame(pollInput); return; }   // P348: photo mode takes pad 1's input
  photoMaskAfter(pads[0]);   // P348: inputs still held from photo mode reach the game only once released
  applyLatches(pads[0], halfHeld);
  const txt = gps.length ? gps.map((g, i) => `pad ${i + 1}: ${g.id.slice(0, 40)}${g.mapping === 'standard' ? '' : ' (non-standard mapping)'}`).join('\n') : 'no gamepad (press a button on it to connect)';
  if (txt !== lastPadText) { $('pads').textContent = txt; lastPadText = txt; }
  if (M && M._port_skip_progress) {  // P321: ring while L is held over a skippable cutscene
    const pr = M._port_skip_progress(), ring = $('skipring');
    if (pr > 0) $('skiparc').style.strokeDashoffset = String(SKIP_ARC * (1 - Math.min(1, pr)));
    if (ring.hasAttribute('hidden') !== !(pr > 0)) ring.toggleAttribute('hidden', !(pr > 0));  // SVG: no .hidden property
  }
  if (netCfg && window.PortNet && PortNet.M) PortNet.setLocalPad(pads[0].b, pads[0].x, pads[0].y);   // P338: this peer's pad -> the ring
  else if (recCfg) { if (recCfg.mode === 'record' && M && M._port_net_addr) recSetPad(pads[0]); }   // P357: the recorded pad (a replay plays the file)
  else if (M && M._port_pad_state && !NETDET) {   // P337: under ?netdet the pads come only from the frame-indexed scripts
    const p = M._port_pad_state() >> 2, H = M.HEAP32;
    for (let i = 0; i < 4; i++) {
      const d = pads[i];
      H[p + i * 4] = i === 0 || d ? 1 : 0;
      H[p + i * 4 + 1] = d ? d.b : 0; H[p + i * 4 + 2] = d ? d.x : 0; H[p + i * 4 + 3] = d ? d.y : 0;
    }
    if (M._port_cam_state) {   // P347 free camera: camera stick per pad, mouse movement added up until the game reads it
      const c = M._port_cam_state() >> 2;
      for (let i = 0; i < 4; i++) { const d = pads[i]; H[c + i * 4] = d && d.cx || 0; H[c + i * 4 + 1] = d && d.cy || 0; }
      if (mouseLook.dx || mouseLook.dy) { H[c + 2] += mouseLook.dx; H[c + 3] += mouseLook.dy; mouseLook.dx = mouseLook.dy = 0; }
    }
  }
  if (M && M._port_gfx_hfr_vsync) M._port_gfx_hfr_vsync();   // P351: online the game loop is a 4 ms timer: one smooth picture per animation frame
  requestAnimationFrame(pollInput);
}
requestAnimationFrame(pollInput);
const boundCodes = () => new Set(Object.values(keyMap));
const typing = (e) => /^(INPUT|TEXTAREA|SELECT)$/.test(e.target.tagName) && e.target.type !== 'range';
window.addEventListener('keydown', (e) => {
  if (listening && listening[0] === 'key') { e.preventDefault(); if (e.code !== 'Escape') finishListen(e.code); else finishListen(null); return; }
  if (window.GMenu && GMenu.key(e)) { e.preventDefault(); return; }   // P361: Esc / Backspace go back in the game-style menu
  if (e.code === 'Escape' && !drawerOpen() && !document.fullscreenElement && window.GMenu && GMenu.wanted() && GMenu.open()) { e.preventDefault(); return; }
  // P360: Esc opens / closes the menu drawer (in real fullscreen the browser takes Esc to leave it: the corner button then)
  if (e.code === 'Escape' && (drawerOpen() || !document.fullscreenElement)) { e.preventDefault(); drawerSet(!drawerOpen()); return; }
  if (typing(e)) return;
  if (e.code === 'F11' || (e.code === 'KeyF' && e.altKey)) { e.preventDefault(); fullscreen(); return; }
  if (!running && romOk && !$('ready').hidden && !drawerOpen() && e.code === 'Enter') { e.preventDefault(); start('game'); return; }   // P360 Press Start
  keysDown.add(e.code);
  if (running && boundCodes().has(e.code)) e.preventDefault();  // no page scrolling on Space / arrows
});
window.addEventListener('keyup', (e) => { keysDown.delete(e.code); });
window.addEventListener('blur', () => keysDown.clear());

// remap panel
const keyName = (c) => !c ? '—' : c.replace(/^(Key|Digit)/, '').replace(/^Arrow/, 'Arrow ');
const padName = (i) => i === undefined || i === null ? '—' : ['A', 'B', 'X', 'Y', 'LB', 'RB', 'LT', 'RT', 'Back', 'Start', 'LS', 'RS', 'D↑', 'D↓', 'D←', 'D→', 'Home'][i] || 'btn ' + i;
function renderBinds() {
  const tb = $('binds');
  tb.textContent = '';
  for (const [id, label] of INPUTS) {
    const tr = document.createElement('tr');
    const k = document.createElement('button'), g = document.createElement('button');
    k.textContent = keyName(keyMap[id]);
    k.onclick = () => startListen('key', id, k);
    const stickDir = ['UP', 'DOWN', 'LEFT', 'RIGHT', 'HALF'].includes(id);
    g.textContent = stickDir ? (id === 'HALF' ? '—' : 'left stick') : padName(padMap[id]);
    g.disabled = stickDir;
    if (!stickDir) g.onclick = () => startListen('pad', id, g);
    const td0 = document.createElement('td'); td0.textContent = label;
    const td1 = document.createElement('td'), td2 = document.createElement('td');
    td1.appendChild(k); td2.appendChild(g);
    tr.append(td0, td1, td2); tb.appendChild(tr);
  }
}
function startListen(kind, id, btn) {
  if (listening) listening[2].classList.remove('listen');
  listening = [kind, id, btn];
  btn.classList.add('listen');
  btn.textContent = kind === 'key' ? 'press a key… (Esc clears)' : 'press a pad button…';
}
function finishListen(v) {
  const [kind, id] = listening;
  listening = null;
  if (kind === 'key') {
    for (const k in keyMap) if (v && keyMap[k] === v) delete keyMap[k];   // one N64 input per key
    if (v) keyMap[id] = v; else delete keyMap[id];
    store.set('keys', diff(keyMap, DEFAULT_KEYS));
  } else {
    for (const k in padMap) if (padMap[k] === v) delete padMap[k];
    padMap[id] = v;
    store.set('padbuttons', diff(padMap, DEFAULT_PAD));
  }
  renderBinds();
}
function diff(m, d) {  // stored = differences from the defaults (null = unbound)
  const o = {};
  for (const k of new Set([...Object.keys(m), ...Object.keys(d)])) if (m[k] !== d[k]) o[k] = m[k] === undefined ? null : m[k];
  return o;
}
function cleanMap(m) { for (const k in m) if (m[k] === null) delete m[k]; return m; }
cleanMap(keyMap); cleanMap(padMap);
$('bind-reset').onclick = () => { keyMap = Object.assign({}, DEFAULT_KEYS); padMap = Object.assign({}, DEFAULT_PAD); store.set('keys', {}); store.set('padbuttons', {}); renderBinds(); };
renderBinds();

// ---------------------------------------------------------------- EEPROM saves
const slot = Q.get('slot') || '0';
const saveKey = () => `${romSha1}/eeprom/${slot}`;
let eepTimer = null, eepWrites = 0;
const eepStatus = (s) => { $('eep-status').textContent = s; };
function eepBytes() {
  const n = M._port_eeprom_size(), p = M._port_eeprom_ptr();
  return M.HEAPU8.slice(p, p + n);
}
// P324 option "Autosave icon": the game wrote an EEPROM block (portEepDirty, once per block): show the icon and keep
// it up until 1.5 s after the last block of this save.
let saveIconTimer = null;
function flashSaveIcon() {
  if (!opt('saveicon')) return;
  $('saveicon').toggleAttribute('hidden', false);  // SVG: no .hidden property
  clearTimeout(saveIconTimer);
  saveIconTimer = setTimeout(() => $('saveicon').toggleAttribute('hidden', true), 1500);
}
async function persistEeprom() {
  eepTimer = null;
  if (!M || !romSha1 || saveBlocked) return;
  const b = eepBytes();
  if (Q.get('eepdump')) log(`[eepdump] ${eepWrites} ${Array.from(b, (x) => x.toString(16).padStart(2, '0')).join('')}`);  // P240 TEST: hex image per save (feed back with ?eephex=)
  try { await idb('saves', 'readwrite', (s) => s.put(b, saveKey())); log(`[eep] saved ${b.length} bytes to IndexedDB (${saveKey()}), ${eepWrites} block writes`); eepStatus(`Saved ${new Date().toLocaleTimeString()} (slot ${slot}).`); }
  catch (e) { log('[eep] save failed: ' + e, 'fail'); eepStatus('Save failed: ' + e); }
}
let saveBlocked = false;  // set when the save could not be read: never overwrite it with a blank EEPROM
async function loadEeprom(Mod) {
  try {
    const hx = Q.get('eephex');   // P240 TEST ?eephex=HEX (4096 hex digits, e.g. from an [eepdump] line): boot with this EEPROM
    if (hx) {
      const n = Mod._port_eeprom_size(), p = Mod._port_eeprom_ptr(), m = Math.min(n, hx.length >> 1);
      for (let i = 0; i < m; i++) Mod.HEAPU8[p + i] = parseInt(hx.substr(i * 2, 2), 16);
      log(`[eep] loaded ${m} bytes from ?eephex`); return;
    }
    // IndexedDB can stall (headless --virtual-time-budget, blocked storage): do not hold the boot on it
    const b = await Promise.race([idb('saves', 'readonly', (s) => s.get(saveKey())),
      new Promise((_, rej) => setTimeout(() => rej(new Error('IndexedDB did not answer in 3 s')), 3000))]);
    if (b && b.length) {
      const n = Mod._port_eeprom_size(), p = Mod._port_eeprom_ptr();
      Mod.HEAPU8.set(b.subarray(0, n), p);
      log(`[eep] loaded ${b.length} bytes from IndexedDB (${saveKey()})`);
      eepStatus(`Loaded the save of slot ${slot}.`);
    } else log(`[eep] no save for ${saveKey()}: blank EEPROM`);
  } catch (e) {
    saveBlocked = true;
    log('[eep] load failed: ' + e.message + '; saving is off for this session', 'fail');
    eepStatus('Could not read the save storage: saving is off for this session (export still works).');
  }
}
$('eep-export').onclick = async () => {
  let b = M ? eepBytes() : await idb('saves', 'readonly', (s) => s.get(saveKey())).catch(() => null);
  if (!b) { eepStatus('No save yet.'); return; }
  const a = document.createElement('a');
  a.href = URL.createObjectURL(new Blob([b], { type: 'application/octet-stream' }));
  a.download = `conker-eu-slot${slot}.eep`;
  document.body.appendChild(a); a.click(); a.remove();
  setTimeout(() => URL.revokeObjectURL(a.href), 5000);
};
async function importEep(f) {
  if (!f) return;
  if (!romSha1) { eepStatus('Load the ROM first.'); return; }
  const raw = new Uint8Array(await f.arrayBuffer());
  if (raw.length !== 2048 && raw.length !== 512) { eepStatus(`Not an EEPROM image (${raw.length} bytes; expected 2048).`); return; }
  const b = new Uint8Array(2048); b.set(raw);
  await idb('saves', 'readwrite', (s) => s.put(b, saveKey()));
  log(`[eep] imported ${f.name} (${raw.length} bytes) into ${saveKey()}`);
  if (running === 'game') { eepStatus('Imported. Reloading so the game reads it at boot…'); setTimeout(() => location.reload(), 600); }
  else eepStatus(`Imported ${f.name}; it loads when the game starts.`);
}
$('eep-import').addEventListener('change', (e) => importEep(e.target.files[0]));

// ---------------------------------------------------------------- fullscreen, pause, volume, audio
function fullscreen() {
  // P360: always the whole page (the picture already fills it; the menu drawer and the touch controls live outside #screen)
  const s = document.documentElement;
  if (document.fullscreenElement) document.exitFullscreen();
  else if (s.requestFullscreen) {
    s.requestFullscreen().then(() => {
      if (s === document.documentElement && screen.orientation && screen.orientation.lock) screen.orientation.lock('landscape').catch(() => {});
    }).catch((e) => log('fullscreen: ' + e.message, 'fail'));
  }
}
document.addEventListener('fullscreenchange', () => {
  document.body.classList.toggle('fs', document.fullscreenElement === document.documentElement);
});
$('fullscreen').onclick = fullscreen;
$('canvas').addEventListener('dblclick', fullscreen);

// P333 option "Rumble": pc_pif.c answers the game's Rumble Pak commands and calls Module.portRumble(channel, on) when
// the motor starts / stops (on the N64 the game pulses it: on for a few frames, off for a few, by strength). Channel 0
// is the keyboard + first gamepad, channel i the gamepad i. Chrome: vibrationActuator.playEffect('dual-rumble');
// Firefox-style: hapticActuators[0].pulse. A long effect is started on "start" and cut by reset() on "stop", so the
// gamepad follows the motor's on / off pattern. window.portRumbleStats counts what happened (headless tests).
const rumbleStats = window.portRumbleStats = { start: 0, stop: 0, played: 0, logged: 0 };
const rumbleMotor = [false, false, false, false];
// Test aid ?p333pad=1: a fake standard gamepad with a vibrationActuator that only counts and logs the calls, so a
// headless run (no real gamepad) shows the playEffect / reset calls the option makes.
if (Q.get('p333pad') === '1') {
  const fake = { id: 'P333 test pad (fake vibrationActuator)', index: 0, connected: true, mapping: 'standard', timestamp: 0,
    buttons: Array.from({ length: 17 }, () => ({ pressed: false, touched: false, value: 0 })), axes: [0, 0, 0, 0],
    vibrationActuator: { type: 'dual-rumble',
      playEffect: (type, p) => { rumbleStats.fakePlay = (rumbleStats.fakePlay || 0) + 1; if (rumbleStats.fakePlay <= 12) log(`[rumble-page] playEffect('${type}', ${JSON.stringify(p)}) #${rumbleStats.fakePlay}`); return Promise.resolve('complete'); },
      reset: () => { rumbleStats.fakeReset = (rumbleStats.fakeReset || 0) + 1; if (rumbleStats.fakeReset <= 12) log(`[rumble-page] reset() #${rumbleStats.fakeReset}`); return Promise.resolve('complete'); } } };
  navigator.getGamepads = () => [fake];
}
function rumbleGamepad(ch) {
  const gps = (navigator.getGamepads ? Array.from(navigator.getGamepads()) : []).filter((g) => g && g.connected);
  return gps[ch] || null;
}
function rumbleSet(ch, on) {
  const gp = rumbleGamepad(ch), act = gp && gp.vibrationActuator, hap = gp && gp.hapticActuators && gp.hapticActuators[0];
  let played = false;
  try {
    if (on && act && act.playEffect) { act.playEffect('dual-rumble', { startDelay: 0, duration: 5000, strongMagnitude: 1.0, weakMagnitude: 0.6 }).catch(() => {}); played = true; }
    else if (on && hap && hap.pulse) { hap.pulse(1.0, 5000); played = true; }
    else if (!on && act) { if (act.reset) act.reset().catch(() => {}); else act.playEffect('dual-rumble', { duration: 0, strongMagnitude: 0, weakMagnitude: 0 }).catch(() => {}); }
    else if (!on && hap && hap.pulse) hap.pulse(0, 1);
  } catch (e) { /* no vibration support */ }
  return played;
}
function portRumble(ch, on) {
  rumbleMotor[ch] = !!on;
  const paused = userPaused || hiddenPaused;
  const played = on && !paused ? rumbleSet(ch, true) : (rumbleSet(ch, false), false);
  if (on) rumbleStats.start++; else rumbleStats.stop++;
  if (played) rumbleStats.played++;
  if (rumbleStats.logged++ < 40) log(`[rumble-page] ch ${ch} ${on ? 'start' : 'stop'}: gamepad ${rumbleGamepad(ch) ? 'yes' : 'none'}, effect ${played ? 'played' : 'not played'} (starts ${rumbleStats.start}, stops ${rumbleStats.stop}, played ${rumbleStats.played})`);
}
function rumbleStopAll() { for (let ch = 0; ch < 4; ch++) if (rumbleMotor[ch]) rumbleSet(ch, false); }
optionChanged.hires2d = (on) => { if (M && M._port_gfx_hires_2d) M._port_gfx_hires_2d(on ? 1 : 0); };   // P349: takes effect at the next frame
optionChanged.smoothfont = (on) => { if (M && M._port_gfx_smooth_font) M._port_gfx_smooth_font(on ? 1 : 0); };   // P356: from the next frame on
optionChanged.hfr = (on) => { if (M && M._port_gfx_hfr) M._port_gfx_hfr(on ? 1 : 0); };   // P351: from the next game frame on
// P350 option "Widescreen": the picture's aspect. Off: 4:3, canvas 640 x 480 (as before). On: the aspect of the space the
// page gives the picture (P360: the whole window), between 4:3 and 21:9 (64:27), with the canvas 480 rows
// high and as wide as that aspect needs; the renderer (port_gfx_widescreen, gfx_f3dex2.c ws_calc) widens the 3D view to
// the canvas and keeps the 2D in the middle. ?canvas=WxH (test aid) fixes the canvas size, and then its aspect.
// layoutScreen runs at start, on window resize / fullscreen changes and when the option changes.
function layoutScreen() {
  const c = $('canvas'), fixed = /^(\d{2,4})x(\d{2,4})$/.exec(Q.get('canvas') || '');
  let ar = 4 / 3, w = 640, h = 480;
  if (fixed) { w = +fixed[1]; h = +fixed[2]; ar = opt('widescreen') ? w / h : 4 / 3; }
  else if (opt('widescreen')) {
    const st = $('stage');   // P360: the stage is the whole window (in fullscreen too)
    const aw = st && st.clientWidth || window.innerWidth, ah = st && st.clientHeight || window.innerHeight;
    ar = Math.max(4 / 3, Math.min(64 / 27, ah > 0 ? aw / ah : 16 / 9));
    w = Math.round(h * ar / 2) * 2;
  }
  document.documentElement.style.setProperty('--ar', ar === 4 / 3 ? '4 / 3' : ar.toFixed(5));
  // P351 option "Full-resolution picture": the drawing buffer = the canvas's size on the page times devicePixelRatio
  // (the CSS box above, so after --ar), at most 2560 x 1440 pixels' worth, kept at the picture's aspect
  if (!fixed && opt('fullres')) {
    const r = c.getBoundingClientRect(), dpr = window.devicePixelRatio || 1;
    if (r.width > 0 && r.height > 0) {
      let fw = r.width * dpr, fh = fw / ar;
      const k = Math.min(1, 2560 / fw, 1440 / fh);
      fw *= k; fh *= k;
      if (fh >= 240) { w = Math.round(fw / 2) * 2; h = Math.round(fh / 2) * 2; }
    }
  }
  if (c.width !== w || c.height !== h) {
    c.width = w; c.height = h;
    if (M && M._port_gfx_resize) M._port_gfx_resize(w, h);
    log(`[widescreen] canvas ${w} x ${h} (aspect ${ar.toFixed(3)})`);
  }
  if (M && M._port_gfx_widescreen) M._port_gfx_widescreen(opt('widescreen') ? 1 : 0);
}
let layoutTimer = 0;
const layoutSoon = () => { clearTimeout(layoutTimer); layoutTimer = setTimeout(layoutScreen, 150); };
window.addEventListener('resize', layoutSoon);
if (window.ResizeObserver && $('stage')) new ResizeObserver(layoutSoon).observe($('stage'));   // P351 (P360: the stage = the window)
document.addEventListener('fullscreenchange', layoutSoon);
optionChanged.widescreen = () => layoutScreen();
optionChanged.fullres = () => layoutScreen();
optionChanged.rumble = (on) => { if (!on) { rumbleStopAll(); rumbleMotor.fill(false); } };

let userPaused = false, hiddenPaused = false;
function applyPause() {
  const p = userPaused || hiddenPaused || e2e.ended;   // P357: a finished replay stays paused
  if (M && M._port_set_paused) M._port_set_paused(p ? 1 : 0);
  if (p) rumbleStopAll();   // P333: no vibration while the page is paused
  const a = window.portAudio, quiet = p || photo.state === 2;   // P348: no sound in photo mode either
  if (a && a.ctx) { if (quiet) a.ctx.suspend().catch(() => {}); else if (gestured) a.ctx.resume().catch(() => {}); }
  $('paused').hidden = !p || running !== 'game';
  $('pause').setAttribute('aria-pressed', String(userPaused));
  $('pause').textContent = userPaused ? 'Resume' : 'Pause';
}
function setPaused(p) { userPaused = p; applyPause(); }
$('pause').onclick = () => setPaused(!userPaused);
document.addEventListener('visibilitychange', () => {
  if (netCfg && window.PortNet && PortNet.M) {   // P338: never pause a session; P339: net.js ticks the game from a worker
    PortNet.background(document.hidden);          // while the page is hidden (hidden pages' timers are throttled to ~1 Hz)
    if (hiddenPaused) { hiddenPaused = false; applyPause(); }
    return;
  }
  if (Q.get('nohidepause')) return;  // dev flag: keep running in a background tab
  hiddenPaused = document.hidden; applyPause();
  log(`[page] tab ${document.hidden ? 'hidden: paused' : 'visible: resumed'}`);
});

window.portVolume = store.get('volume', 80) / 100;
if (Q.get('mute')) window.portVolume = 0;  // P271: test runs pass ?mute=1 (audprobe.sh does by default): gain 0
$('volume').value = Math.round(window.portVolume * 100);
$('volume').addEventListener('input', (e) => {
  window.portVolume = e.target.value / 100;
  store.set('volume', +e.target.value);
  const a = window.portAudio;
  if (a && a.gain) a.gain.gain.value = window.portVolume;
});

// Browsers start an AudioContext only after a user gesture. The game opens its context at the first
// audio buffer (port/audio/aud_out.c); the first click / key press resumes it, and a context opened
// after that gesture starts at once (sticky activation).
// iOS (every iOS browser is WebKit) keeps a context created outside a gesture suspended for good, and
// mutes Web Audio when the ring switch is on silent. So on iOS: mark the page as media playback, create
// the context inside the first tap, unlock it with a silent buffer, and hand that context to the game
// when it asks for one (port/audio/aud_out.c resamples if the rate differs).
let preCtx = null;
if (IOS) {
  try { if (navigator.audioSession) navigator.audioSession.type = 'playback'; } catch (e) { /* older iOS */ }
  for (const k of ['AudioContext', 'webkitAudioContext']) {
    const Orig = window[k];
    if (!Orig) continue;
    window[k] = function (opts) { if (preCtx) { const c = preCtx; preCtx = null; return c; } return new Orig(opts); };
    window[k].prototype = Orig.prototype;
  }
}
function unlockIosAudio() {
  if (!IOS || window.portAudio) return;
  if (preCtx) { if (preCtx.state !== 'running') preCtx.resume().catch(() => {}); return; }
  const C = (window.AudioContext || window.webkitAudioContext).prototype.constructor;
  try {
    const c = new C();
    const b = c.createBuffer(1, 1, 22050), src = c.createBufferSource();
    src.buffer = b; src.connect(c.destination); src.start(0);
    c.resume().catch(() => {});
    preCtx = c;
    log('[audio] iOS: context unlocked by tap: ' + c.state);
  } catch (e) { log('[audio] iOS unlock failed: ' + e, 'fail'); }
}
let gestured = false;
function onGesture() {
  gestured = true;
  unlockIosAudio();
  const a = window.portAudio;
  if (a && a.ctx && a.ctx.state !== 'running' && !(userPaused || hiddenPaused) && photo.state !== 2) {
    a.ctx.resume().then(() => log('[audio] context resumed by user gesture: ' + a.ctx.state)).catch(() => {});
  }
  updateSoundHint();
}
for (const ev of ['pointerdown', 'pointerup', 'keydown', 'touchend', 'click']) window.addEventListener(ev, onGesture, true);
function updateSoundHint() {
  const a = window.portAudio;
  $('soundhint').hidden = !(a && a.ctx && a.ctx.state !== 'running' && !(userPaused || hiddenPaused) && photo.state !== 2);
}
window.portAudioReady = (ctx) => {
  log(`[audio] context created: ${ctx.state}${gestured ? ' (after a gesture)' : ''}`);
  ctx.addEventListener('statechange', updateSoundHint);
  if (gestured && ctx.state !== 'running') ctx.resume().catch(() => {});
  updateSoundHint();
};

// ---------------------------------------------------------------- P337 online multiplayer phase 0
// The state hash (port/ultra/pc_nethash.c) leaves out the port-only static ranges listed in conker_netx.txt
// (port/tools/net_regions.py, written by the build next to conker.wasm). window.__netdump reads the hashed memory after
// ?nethashstop paused the game (port/web/audprobe.js PROBE_DUMP -> tools/port/nethash_diff.py).
async function netLoadExclusions(Mod) {
  try {
    const t = await (await fetch('conker_netx.txt')).text(); let n = 0;
    for (const l of t.split('\n')) { const f = l.split(' '); if (f.length >= 2) { Mod._port_net_exclude(parseInt(f[0], 16), parseInt(f[1], 16)); n++; } }
    log(`[nethash] ${n} excluded static ranges from conker_netx.txt`);
  } catch (e) { log('[nethash] conker_netx.txt not loaded: ' + e, 'fail'); }
}
window.__netdump = {
  info() {
    const regions = [];
    for (let i = 0; M._port_net_region(i, 0) !== -1; i++) {
      const a = M._port_net_region(i, 0) >>> 0, l = M._port_net_region(i, 1);
      if (l) regions.push({ i, addr: a, len: l });
    }
    const fm = /\bnethashstop=(\d+)/.exec(location.search);
    return { frame: fm ? +fm[1] : 0, regions };
  },
  chunk(addr, len) {
    const b = M.HEAPU8.subarray(addr, addr + len); let s = '';
    for (let i = 0; i < b.length; i += 32768) s += String.fromCharCode.apply(null, b.subarray(i, i + 32768));
    return btoa(s);
  },
};

// ---------------------------------------------------------------- P338 online session (port/web/net.js)
// window.__online is what the Online panel's buttons call (and tools/port/scripts/netpair.js, which plays both sides
// of a session in one browser). Host = controller 1; P344: up to 3 guests, each with the controller slot (2..4) the host
// gave it with its code. The host dictates the session: game options, its EEPROM image (user save data, never ROM
// bytes), the input delay. The host checks every guest's build id (SHA-256 of conker.wasm) and ROM SHA-256 before
// anything starts. Test aids: ?netd=D input delay (host), ?neteep=blank.
const netEvents = { status: [], tick: [], desync: [], desyncReport: [], left: [], roster: [] };   // the Online panel subscribes here
const sha256hex = async (buf) => Array.from(new Uint8Array(await crypto.subtle.digest('SHA-256', buf)), (b) => b.toString(16).padStart(2, '0')).join('');
async function netLoad() {
  if (!window.PortNet) await loadScript('net.js');
  if (!PortNet.buildId) {
    PortNet.buildId = (await sha256hex(await (await fetch('conker.wasm')).arrayBuffer())).slice(0, 16);
    PortNet.romSha256 = await sha256hex(romBytes);
    PortNet.log = log;
    if (Q.get('roomapi')) PortNet.roomApi = Q.get('roomapi');   // P345 tests: a local room server (tools/port/scripts/roomserver.mjs)
    for (const ev of Object.keys(netEvents)) PortNet.t.on[ev] = (...a) => { for (const f of netEvents[ev]) f(...a); };
    PortNet.t.on.config = (cfg) => {   // both peers: boot the game into the session
      netCfg = cfg;
      for (const k of Object.keys(optCache)) delete optCache[k];
      log(`[net] session config: channels ${cfg.mask} (players ${(cfg.roster || []).map((c) => c + 1).join(' ')}), mine ${cfg.local}, delay ${cfg.delay}${cfg.autoDelay ? ` (auto, ping ${cfg.ping} ms)` : ''}, EEPROM ${cfg.eeprom ? 'host image' : 'blank'}`);
      start('game');
    };
  }
}
// ---- the Online panel (shown by the option "Online multiplayer")
const showOnlineButton = (on) => { $('t-online').hidden = !on; if (!on && !$('p-online').hidden) toggle('online', false); };
optionChanged.online = showOnlineButton;
showOnlineButton(opt('online') || !!Q.get('netpanel'));
const netStatus = (s, cls) => { $('net-status').textContent = s; $('net-status').className = cls || ''; };
const copyCode = (id) => { const t = $(id); t.select(); (navigator.clipboard ? navigator.clipboard.writeText(t.value) : Promise.reject()).catch(() => document.execCommand('copy')); };
const netGuard = async (fn) => { try { await fn(); } catch (e) { netStatus(String(e.message || e), 'bad'); log('[net] ' + e, 'fail'); } };
$('net-delay').value = store.get('netdelay', 3);
$('net-delay').onchange = () => store.set('netdelay', Math.max(1, Math.min(16, +$('net-delay').value | 0)));
$('net-delay-auto').checked = store.get('netdelayauto', true);   // P339: automatic input delay from the measured ping
$('net-delay').disabled = $('net-delay-auto').checked;
$('net-delay-auto').onchange = () => { store.set('netdelayauto', $('net-delay-auto').checked); $('net-delay').disabled = $('net-delay-auto').checked; };
// P344: the host's panel lists the guest slots (players 2..4): each with its offer code, the answer box and its state
$('net-host').onclick = () => netGuard(async () => {
  netNeedRom();   // before the buttons are disabled, so the player can load the ROM and try again
  $('net-step-host').hidden = false; $('net-step-join').hidden = true; netLockStart();
  netShowSlot(await window.__online.invite());
});
// P345 room codes: Create room (host: the code big + copy + the joined players), Join room (code field); the
// copy-paste flow above stays under "manual codes"
const netLockStart = () => { for (const id of ['net-host', 'net-join', 'net-room-create', 'net-room-join', 'net-manual']) $(id).disabled = true; };
const netUnlockStart = () => { for (const id of ['net-host', 'net-join', 'net-room-create', 'net-room-join', 'net-manual']) $(id).disabled = false; };
$('net-manual').onchange = () => { $('net-manual-box').hidden = !$('net-manual').checked; };
$('net-room-create').onclick = () => netGuard(async () => {
  netNeedRom();
  netLockStart();
  try { $('net-room-show').textContent = await window.__online.roomCreate(); } catch (e) { netUnlockStart(); throw e; }
  $('net-room-box').hidden = false; $('net-room-start').hidden = true;
  $('net-step-host').hidden = false; $('net-invite').hidden = true;
});
$('net-room-copy').onclick = () => { const c = $('net-room-show').textContent; (navigator.clipboard ? navigator.clipboard.writeText(c) : Promise.reject()).catch(() => {}); };
$('net-room-join').onclick = () => netGuard(async () => {
  netNeedRom();
  netLockStart();
  try { await window.__online.roomJoin($('net-room-code').value); } catch (e) { if (!window.PortNet || !PortNet.t.role) netUnlockStart(); throw e; }
  $('net-room-start').hidden = true;
});
$('net-room-code').onkeydown = (e) => { if (e.key === 'Enter') $('net-room-join').click(); };
$('net-invite').onclick = () => netGuard(async () => { $('net-invite').disabled = true; try { netShowSlot(await window.__online.invite()); } finally { $('net-invite').disabled = false; } });
$('net-start').onclick = () => netGuard(async () => { $('net-start').disabled = $('net-invite').disabled = true; await window.__online.start(); });
function netSlotBox(ch) {
  let e = $('net-slot-' + (ch + 1));
  if (e) return e;
  const n = ch + 1;
  e = document.createElement('div'); e.className = 'netslot'; e.id = 'net-slot-' + n;
  e.innerHTML = `<div class="row"><b>Player ${n}</b><span id="net-slot-${n}-state" class="netslotstate">invited</span></div>
    <div id="net-slot-${n}-codes"><label>1. Send this code to player ${n} <button id="net-offer-copy-${n}">Copy</button></label>
    <textarea id="net-offer-${n}" readonly rows="2"></textarea>
    <label>2. Paste player ${n}'s answer code here</label>
    <textarea id="net-answer-in-${n}" rows="2"></textarea>
    <div class="row"><button id="net-accept-${n}" class="primary">Connect player ${n}</button></div></div>`;
  $('net-slots').appendChild(e);
  $('net-offer-copy-' + n).onclick = () => copyCode('net-offer-' + n);
  $('net-accept-' + n).onclick = () => netGuard(async () => { await window.__online.accept($('net-answer-in-' + n).value); $('net-accept-' + n).disabled = true; });
  return e;
}
function netShowSlot({ ch, code }) {
  netSlotBox(ch);
  const n = ch + 1;
  $('net-slot-' + n + '-codes').hidden = false; $('net-accept-' + n).disabled = false;
  $('net-offer-' + n).value = code; $('net-answer-in-' + n).value = '';
}
const NET_SLOT_TEXT = { invited: 'invited: waiting for the answer code', connecting: 'connecting…', connected: 'connected, checking the game build…',
  joined: 'joined', left: 'left', failed: 'could not connect' };
netEvents.roster.push((slots) => {   // host
  let joined = 0;
  for (const s of slots) {
    netSlotBox(s.ch);
    const n = s.ch + 1;
    if (s.state === 'joined') joined++;
    $('net-slot-' + n + '-codes').hidden = !!PortNet.t.room || !['invited', 'connecting', 'failed'].includes(s.state);   // P345: no codes in a room
    $('net-slot-' + n + '-state').textContent = (PortNet.t.room && s.state === 'invited' ? 'joined the room: connecting…' : NET_SLOT_TEXT[s.state] || s.state) + (s.why && s.state !== 'joined' ? ` (${s.why})` : '') +
      (s.rtt && s.state === 'joined' ? ` · ping ${s.rtt} ms` : '') + (s.relay && s.relay.length ? ` · through player 1 with ${s.relay.map((k) => k.split('-').filter((c) => +c !== s.ch).map((c) => 'player ' + (+c + 1))).join(', ')}` : '');
  }
  if (!window.PortNet || !PortNet.t.started) { $('net-start').disabled = !joined; $('net-start').textContent = `Start the game (${joined + 1} players)`; }
  else $('net-host-actions').hidden = $('net-room-box').hidden = true;   // the game started: no more invitations (P345: the room is closed)
  $('net-invite').disabled = slots.length >= 3 && slots.every((s) => !['left', 'failed'].includes(s.state));
});
$('net-join').onclick = () => { $('net-step-join').hidden = false; $('net-step-host').hidden = true; netLockStart(); };
$('net-answer-make').onclick = () => netGuard(async () => { netNeedRom(); $('net-answer-make').disabled = true; $('net-answer').value = await window.__online.join($('net-offer-in').value); });
$('net-answer-copy').onclick = () => copyCode('net-answer');
$('net-leave').onclick = () => { window.__online.leave(); $('net-leave').hidden = true; };
netEvents.status.push((s, cls) => {
  netStatus(s, cls);
  if (/^(connected|joined as)/.test(s) || (window.PortNet && PortNet.t.started)) { $('net-step-join').hidden = true; $('net-room-start').hidden = true; $('net-leave').hidden = false; }
});
let netWaitSince = 0;
netEvents.tick.push((t) => {   // ~100 Hz from net.js
  const now = performance.now();
  if (!t.waiting) netWaitSince = 0; else if (!netWaitSince) netWaitSince = now;
  $('netwait').hidden = !(netWaitSince && now - netWaitSince > 400);
  if (!$('netwait').hidden) {   // P344: name the players the game waits for
    const w = (t.peers || []).filter((p) => p.waiting).map((p) => 'player ' + (p.ch + 1));
    $('netwait').textContent = `waiting for ${w.length ? w.join(', ') : 'the other players'}…`;
  }
  if (now - (netEvents.lastInfo || 0) > 500) {
    netEvents.lastInfo = now;
    $('net-info').textContent = `you are player ${PortNet.t.myCh + 1} · retrace ${t.frame} · waits ${t.stalls} · input delay ${netCfg ? netCfg.delay * 20 + ' ms' + (netCfg.autoDelay ? ' (auto)' : '') : '–'}`;
    // P344: every other player's ping (and who the game waits for)
    $('net-peers').textContent = (t.peers || []).map((p) => `player ${p.ch + 1}: ${p.lost ? 'left (stands still)' : (p.rtt ? 'ping ' + p.rtt + ' ms' : 'ping –') +
      (PortNet.t.routes && Object.entries(PortNet.t.routes).some(([k, v]) => v === 'relay' && k.split('-').map(Number).includes(p.ch) && k.split('-').map(Number).includes(PortNet.t.myCh)) ? ' (through player 1)' : '') +
      (p.waiting ? ' · waiting' : '')}`).join(' · ');
  }
});
netEvents.desync.push((d) => {
  const e = $('net-desync'); if (!e.hidden) return;   // P339: reported once (both peers detect it)
  e.hidden = false;
  e.textContent = `Desync at retrace ${d.frame} with player ${(d.ch || 0) + 1}: this game ${d.mine.map((x) => (x >>> 0).toString(16)).join(' ')}, the other ${d.theirs.map((x) => (x >>> 0).toString(16)).join(' ')}. ` +
    'The two games no longer show the same thing; please report it (open Debug for the log).';
});
netEvents.desyncReport.push((r) => {   // P339: where the two games differ (net.js comparePages)
  const e = $('net-desync'); e.hidden = false;
  e.textContent += ` Where: ${r.where}; ${r.pages} memory page(s) and ${r.stacks.length} thread stack(s) differ.`;
});
netEvents.left.push(() => { if (PortNet.t.left) { $('netwait').hidden = true; $('net-leave').hidden = true; } });   // P344: alone now
// Host / Join compare ROM hashes, so the ROM must be loaded first (without it the hash call failed with a
// SubtleCrypto "not an ArrayBuffer" error).
function netNeedRom() {
  if (!romBytes) throw new Error('load your ROM first ("Choose ROM file…" or drop the file on the page), then Host / Join');
  if (!romOk) throw new Error('this ROM is not the Conker EU ROM; both players need the EU ROM');
  if (!crypto.subtle) throw new Error('this page needs a secure (https) connection for online play');
}
// the host's session config (P345: was inline in __online.invite; also used by rooms): sessionFn of net.js
async function netSessionConfig({ ping, mask }) {   // ping: {n, min, median, p90} ms of the slowest pair (or null)
  const options = {};
  for (const o of OPTIONS) if (o.game !== undefined) options[o.key] = opt(o.key);
  let eeprom = null;
  if (Q.get('neteep') !== 'blank') try { const b = await idb('saves', 'readonly', (s) => s.get(saveKey())); if (b && b.length) eeprom = new Uint8Array(b); } catch (e) { /* no save */ }
  // P339: input delay automatic from the measured ping (panel checkbox, default on) or the panel's field;
  // ?netd=D / ?netd=auto (tests) wins
  const auto = Q.get('netd') ? Q.get('netd') === 'auto' : $('net-delay-auto').checked;
  const d = auto ? PortNet.autoDelay(ping) : +(Q.get('netd') || $('net-delay').value || 3);
  return { mask, delay: Math.max(1, Math.min(16, d | 0)), autoDelay: auto, hashEvery: 10, options, eeprom };
}
window.__online = {
  ready: () => !!romBytes && !running,
  // host: start hosting, returns player 2's offer code (P344: __online.invite() for players 3 and 4, then start())
  async host() { return (await window.__online.invite()).code; },
  async invite() {   // host: {ch, code} for the next free slot
    if (window.PortNet && PortNet.t.role === 'host') return PortNet.invite();
    if (running) throw new Error('the game already runs: reload the page, then host before pressing Start');
    netNeedRom();
    await netLoad();
    return PortNet.host(netSessionConfig);
  },
  // P345 room codes: host -> the room code (players 2..4 join with it); guest -> joins, resolves with its channel
  async roomCreate(max = 4) {
    if (running) throw new Error('the game already runs: reload the page, then create the room before pressing Start');
    netNeedRom();
    await netLoad();
    return PortNet.roomCreate(netSessionConfig, max);
  },
  async roomJoin(code) {
    if (running) throw new Error('the game already runs: reload the page, then join before pressing Start');
    netNeedRom();
    await netLoad();
    return PortNet.roomJoin(code);
  },
  room: () => window.PortNet && PortNet.t.room ? { code: PortNet.t.room.code, ch: PortNet.t.room.ch, closed: !!PortNet.t.room.closed } : null,
  async join(code) {
    if (running) throw new Error('the game already runs: reload the page, then join before pressing Start');
    netNeedRom();
    await netLoad();
    return PortNet.join(code);
  },
  accept: (code) => PortNet.accept(code),   // host: a guest's answer code; returns its channel
  start: () => PortNet.start(),             // host: P344 start the game with every joined player
  slots: () => window.PortNet ? PortNet.slots() : [],
  leave: () => window.PortNet && PortNet.t && PortNet.leave(),
  stats() {
    if (!window.PortNet || !PortNet.t) return null;
    const t = PortNet.t, on = PortNet.M && PortNet.base.input !== undefined;
    const hs = on ? PortNet.hashes() : [], h = hs[hs.length - 1];
    return { state: t.state, me: t.myCh + 1, frame: on ? PortNet.frame() : 0, rtt: Math.round(t.rtt), stalledTicks: on ? PortNet.stat(0) : 0,
      stalledSlots: on ? PortNet.stat(1) : 0, sent: t.sent, recv: t.recv, relayed: t.relayed, simDropped: t.simDropped, hashChecked: t.myHashSeen,
      lastHash: h ? `${h.f}:${h.h.toString(16)}:${h.s.toString(16)}` : '', desync: t.desync, desyncReport: t.desyncReport || null, left: t.left,
      slowedMs: on ? PortNet.stat(7) : 0, waits: on ? PortNet.stat(8) : 0, waitMs: on ? PortNet.stat(9) : 0,
      peers: Object.values(t.peers).map((p) => ({ p: p.ch + 1, rtt: Math.round(p.rtt), m: +p.myMargin.toFixed(2), pm: +p.peerMargin.toFixed(2), lost: p.lost })),
      routes: t.routes };   // P339 time sync, P344 per player
  },
};


// ---------------------------------------------------------------- P357 input recorder (end-to-end tests)
// docs/port/E2E.md. The option "Input recorder" shows the Record button and panel. "Start recording" boots the game from
// power-on (a running game: the page reloads first) as a single-player session of the online machinery with no input
// delay (port/ultra/pc_net.c section 5): forced determinism (det clock, no wall-time frame budget, virtual audio queue,
// static thread stacks), the 50 Hz VI still paced by the wall clock, so the player plays at full speed with sound. At the
// start of every retrace the game samples pad 1 (written here every animation frame, recSetPad) and hands the value to
// recOnInput; at the end of retraces it hands fingerprints: G (build-independent game digest) every 10 retraces, and a
// checkpoint (G + the online hash H / S + level / mode / Conker's position) every 50 retraces and at every level / game
// mode change. Pausing (Esc, the Pause button, a hidden tab) stops the retraces, not the recording; the game options
// are fixed, free camera and photo mode are off; the game's saves are kept as usual. "Stop and save" adds the last
// checkpoint and downloads the recording; the last 10 also stay in this browser (a draft is stored every 10 s, so a
// crash or a reload keeps all but the last seconds).
// File (.ckrec): gzip of one JSON object { format 'conker-e2e-recording', version 1, name, created, build (SHA-256 of
// conker.wasm, 16 hex), rom_sha1, start 'power-on', slot, eeprom (base64 of the 2048-byte EEPROM image at power-on:
// the player's save data, not ROM data), options {game option: value}, view {page-side options, information only},
// check_every 50, g_every 10, retraces N, inputs (base64: runs of u32 LE packed input buttons << 16 | (u8)x << 8 | (u8)y
// + LEB128 count, retrace 1 first), g (base64: u32 LE G of retraces 10, 20, ...), checks [[retrace, H, S, G, level,
// mode, kind 0 periodic / 1 level or mode change / 2 last, x, y, z], ...], complete, wall_s, paused_s, gaps, user_agent }.
// Replay (?replay=URL, tools/port/scripts/e2e_replay.sh): the same session fed from the file, fast (?replayspeed=real
// for 50 Hz), compared checkpoint by checkpoint (H / S only for the same build); window.__e2e.status() for the driver.
const REC_FORMAT = 'conker-e2e-recording', REC_CHECK_EVERY = 50, REC_G_EVERY = 10, REC_KEEP = 10;
const rec = { active: false, runs: [], lastV: -1, frames: 0, g: [], checks: [], gaps: 0, header: null, id: '', t0: 0,
  pausedMs: 0, pauseSince: 0, draftTimer: null, uiTimer: null, drafting: false, level: 0 };
const b64enc = (u8) => { let t = ''; for (let i = 0; i < u8.length; i += 32768) t += String.fromCharCode.apply(null, u8.subarray(i, i + 32768)); return btoa(t); };
const b64dec = (t) => { const b = atob(t || ''), u8 = new Uint8Array(b.length); for (let i = 0; i < b.length; i++) u8[i] = b.charCodeAt(i); return u8; };
function recEncodeRuns(runs) {   // [[value, count], ...] -> u32 LE value + LEB128 count per run
  const out = new Uint8Array(runs.length * 9); let o = 0;
  for (const [v, n] of runs) {
    out[o++] = v & 255; out[o++] = (v >>> 8) & 255; out[o++] = (v >>> 16) & 255; out[o++] = (v >>> 24) & 255;
    let k = n; while (k >= 128) { out[o++] = (k & 127) | 128; k = Math.floor(k / 128); } out[o++] = k;
  }
  return out.subarray(0, o);
}
function recDecodeRuns(u8, total) {   // -> Uint32Array of every retrace's input (retrace 1 first)
  const out = new Uint32Array(total); let o = 0, i = 0;
  while (i + 4 <= u8.length) {
    const v = (u8[i] | u8[i + 1] << 8 | u8[i + 2] << 16 | u8[i + 3] << 24) >>> 0; i += 4;
    let n = 0, m = 1, c; do { c = u8[i++]; n += (c & 127) * m; m *= 128; } while (c & 128);
    for (let k = 0; k < n && o < total; k++) out[o++] = v;
  }
  return out;
}
const u32enc = (arr) => { const b = new Uint8Array(arr.length * 4), d = new DataView(b.buffer); arr.forEach((v, i) => d.setUint32(i * 4, v >>> 0, true)); return b; };
const u32dec = (u8) => { const d = new DataView(u8.buffer, u8.byteOffset, u8.byteLength), out = []; for (let i = 0; i + 4 <= u8.length; i += 4) out.push(d.getUint32(i, true)); return out; };
let wasmBuildId = null;
async function recBuildId() {
  if (!wasmBuildId) try { wasmBuildId = (await sha256hex(await (await fetch('conker.wasm')).arrayBuffer())).slice(0, 16); } catch (e) { wasmBuildId = 'unknown'; }
  return wasmBuildId;
}
async function recPack(doc) {   // the recording object -> a gzip Blob (plain JSON if this browser cannot compress)
  const json = new Blob([JSON.stringify(doc)], { type: 'application/json' });
  if (!window.CompressionStream) return json;
  return new Response(json.stream().pipeThrough(new CompressionStream('gzip'))).blob();
}
async function recUnpack(buf) {   // ArrayBuffer (gzip or plain JSON) -> the recording object
  let u8 = new Uint8Array(buf);
  if (u8[0] === 0x1f && u8[1] === 0x8b) u8 = new Uint8Array(await new Response(new Blob([u8]).stream().pipeThrough(new DecompressionStream('gzip'))).arrayBuffer());
  const doc = JSON.parse(new TextDecoder().decode(u8));
  if (doc.format !== REC_FORMAT) throw new Error('not a Conker input recording');
  return doc;
}
function recDocument(complete) {
  const now = performance.now(), paused = rec.pausedMs + (rec.pauseSince ? now - rec.pauseSince : 0);
  return Object.assign({}, rec.header, { retraces: rec.frames, inputs: b64enc(recEncodeRuns(rec.runs)), g: b64enc(u32enc(rec.g)),
    checks: rec.checks, complete, gaps: rec.gaps, wall_s: Math.round((now - rec.t0) / 100) / 10, paused_s: Math.round(paused / 100) / 10 });
}
const recFileName = (h) => {
  const t = new Date(h.created), p2 = (n) => String(n).padStart(2, '0');
  const slug = (h.name || 'recording').toLowerCase().replace(/[^a-z0-9]+/g, '-').replace(/^-|-$/g, '').slice(0, 40) || 'recording';
  return `conker-rec-${slug}-${t.getFullYear()}${p2(t.getMonth() + 1)}${p2(t.getDate())}-${p2(t.getHours())}${p2(t.getMinutes())}${p2(t.getSeconds())}.ckrec`;
};
async function recStore(doc, blob) {   // keep it in this browser (IndexedDB 'recordings'), the newest REC_KEEP only
  const entry = { id: rec.id, name: doc.name, created: doc.created, retraces: doc.retraces, complete: doc.complete, size: blob.size, file: recFileName(doc), blob };
  await idb('recordings', 'readwrite', (st) => st.put(entry, rec.id));
  const all = await recList();
  for (const old of all.slice(REC_KEEP)) await idb('recordings', 'readwrite', (st) => st.delete(old.id));
}
async function recList() {   // newest first
  const all = await idb('recordings', 'readonly', (st) => st.getAll()).catch(() => []) || [];
  return all.sort((a, b) => (a.created < b.created ? 1 : -1));
}
function recDownload(blob, name) {
  const a = document.createElement('a');
  a.href = URL.createObjectURL(blob); a.download = name;
  document.body.appendChild(a); a.click(); a.remove();
  setTimeout(() => URL.revokeObjectURL(a.href), 20000);
}
async function recSaveDraft() {   // every 10 s while recording (and when the tab is hidden): a crash or reload keeps it
  if (!rec.active || rec.drafting) return;
  rec.drafting = true;
  try { const doc = recDocument(false); await recStore(doc, await recPack(doc)); } catch (e) { log('[rec] draft not stored: ' + e, 'fail'); }
  rec.drafting = false;
}
function recSetPad(p) {   // every animation frame while recording: pad 1 as the game will sample it at the next retrace
  const H = M.HEAP32, a = M._port_net_addr(3) >> 2;
  H[a] = 1; H[a + 1] = p.b; H[a + 2] = p.x; H[a + 3] = p.y;
}
function recOnInput(f, v) {   // pc_net.c: retrace f's input, sampled at its start
  if (!rec.active) return;
  if (f !== rec.frames + 1) { rec.gaps++; if (rec.gaps < 5) log(`[rec] input of retrace ${f} after ${rec.frames}`, 'fail'); }
  rec.frames = f;
  if (v === rec.lastV && rec.runs.length) rec.runs[rec.runs.length - 1][1]++; else { rec.runs.push([v, 1]); rec.lastV = v; }
}
const recPaused = () => userPaused || hiddenPaused;
function recUi() {
  const on = rec.active, txt = $('rec-status');
  $('rec-start').disabled = on || (!!running && (!!netCfg || !!recCfg)); $('rec-stop').disabled = !on;
  $('rec-badge').hidden = !on; $('t-rec').classList.toggle('rec-on', on);
  if (!on) return;
  const now = performance.now();
  if (recPaused() && !rec.pauseSince) rec.pauseSince = now;
  if (!recPaused() && rec.pauseSince) { rec.pausedMs += now - rec.pauseSince; rec.pauseSince = 0; }
  const secs = rec.frames / 50, mm = Math.floor(secs / 60), ss = Math.floor(secs % 60);
  txt.textContent = `Recording "${rec.header.name}": ${mm}:${String(ss).padStart(2, '0')} of game time (retrace ${rec.frames}), level ${rec.level.toString(16).toUpperCase()}` +
    `, ${rec.checks.length} checkpoints${recPaused() ? ' · paused (the recording waits)' : ''}`;
  txt.className = 'ok';
}
async function recShowList() {
  const box = $('rec-list'); if (!box) return;
  const all = await recList();
  box.textContent = all.length ? '' : 'none yet';
  for (const r of all) {
    const row = document.createElement('div'); row.className = 'recrow';
    const secs = (r.retraces || 0) / 50;
    const t = document.createElement('span');
    t.textContent = `${r.name || 'recording'} · ${new Date(r.created).toLocaleString()} · ${Math.floor(secs / 60)}:${String(Math.floor(secs % 60)).padStart(2, '0')} · ${Math.max(1, Math.round(r.size / 1024))} KB${r.complete ? '' : ' · unfinished (the page closed while recording)'}`;
    const dl = document.createElement('button'); dl.textContent = 'Download'; dl.onclick = () => recDownload(r.blob, r.file);
    const del = document.createElement('button'); del.textContent = 'Delete';
    del.onclick = async () => { if (rec.active && r.id === rec.id) return; await idb('recordings', 'readwrite', (st) => st.delete(r.id)); recShowList(); };
    row.append(t, dl, del); box.appendChild(row);
  }
}
// "Start recording": from power-on. A running game is reloaded first (sessionStorage carries the name over).
function recArm(name) {
  if (!romOk) { $('rec-status').textContent = 'Load the ROM first.'; return; }
  if (running) { try { sessionStorage.setItem('conker.recArm', name || ''); } catch (e) { /* no storage */ } location.reload(); return; }
  const options = {};
  for (const o of OPTIONS) if (o.game !== undefined) options[o.key] = opt(o.key);
  options.freecam = false; options.photomode = false;   // not part of the recorded input
  recCfg = { mode: 'record', name: name || 'recording', options };
  for (const k of Object.keys(optCache)) delete optCache[k];
  start('game');
}
async function recStop() {
  if (!rec.active) return;
  M._port_rec_checkpoint_now();   // the last checkpoint: the state after the last recorded retrace
  rec.active = false;
  clearInterval(rec.draftTimer);
  const doc = recDocument(true), blob = await recPack(doc), name = recFileName(doc);
  try { await recStore(doc, blob); } catch (e) { log('[rec] not stored in this browser: ' + e, 'fail'); }
  recDownload(blob, name);
  window.__rec.last = { doc, blob, name };
  log(`[rec] stopped after retrace ${doc.retraces} (${doc.checks.length} checkpoints, ${M._port_rec_checkpoint_ms().toFixed(2)} ms each; ${rec.runs.length} input runs): ${name}, ${blob.size} bytes`);
  recUi();
  $('rec-status').textContent = `Saved ${name} (${Math.max(1, Math.round(blob.size / 1024))} KB): it was downloaded and is listed below. ` +
    'The game goes on without recording (still in the recording mode); reload the page to play normally.';
  recShowList();
}
// before callMain (start): the session
async function recBegin(Mod) {
  Mod.recInput = recOnInput;
  Mod.recG = (f, g) => { if (recCfg.mode === 'record') { if (rec.active) rec.g.push(g); } else e2eG(f, g); };
  Mod.recCheck = (f, h, s, g, level, mode, kind, x, y, z) => {
    const c = [f, h, s, g, level, mode, kind, +x.toFixed(3), +y.toFixed(3), +z.toFixed(3)];
    if (recCfg.mode === 'record') { if (rec.active) { rec.checks.push(c); rec.level = level; } } else e2eCheck(c);
  };
  Mod.recEnd = (f) => e2eEnd(f);
  if (recCfg.mode === 'replay') return e2eBegin(Mod);
  const view = {};
  for (const o of OPTIONS) if (o.game === undefined && !['online', 'recorder'].includes(o.key)) view[o.key] = opt(o.key);
  rec.header = { format: REC_FORMAT, version: 1, name: recCfg.name, created: new Date().toISOString(), build: await recBuildId(),
    rom_sha1: romSha1, start: 'power-on', slot, eeprom: b64enc(eepBytes()), options: recCfg.options, view,
    check_every: REC_CHECK_EVERY, g_every: REC_G_EVERY, user_agent: navigator.userAgent };
  rec.id = 'rec-' + rec.header.created;
  Mod._port_rec_session(1, REC_CHECK_EVERY, REC_G_EVERY, 0, 0, 0, 0);
  rec.active = true; rec.t0 = performance.now();
  rec.draftTimer = setInterval(recSaveDraft, 10000);
  rec.uiTimer = setInterval(recUi, 500);
  log(`[rec] recording "${recCfg.name}" from power-on: build ${rec.header.build}, save of slot ${slot}, options ` +
      Object.entries(recCfg.options).map(([k, v]) => `${k}=${+v}`).join(' '));
  recUi();
}
document.addEventListener('visibilitychange', () => { if (document.hidden && rec.active) recSaveDraft(); });
window.addEventListener('beforeunload', (e) => { if (rec.active) { e.preventDefault(); e.returnValue = ''; } });   // "leave the page?" while recording
const showRecButton = (on) => { $('t-rec').hidden = !on && !rec.active; if (!on && !rec.active && !$('p-rec').hidden) toggle('rec', false); };
optionChanged.recorder = showRecButton;
showRecButton(opt('recorder') || !!Q.get('record'));
$('rec-start').onclick = () => recArm($('rec-name').value.trim());
$('rec-stop').onclick = () => recStop();
$('t-rec').addEventListener('click', () => recShowList());
if (opt('recorder')) recShowList();
window.__rec = {   // tests (tools/port/scripts/e2e_record.js) and the DevTools console
  arm: (name) => recArm(name), stop: () => recStop(), status: () => ({ active: rec.active, frames: rec.frames, checks: rec.checks.length, gaps: rec.gaps, runs: rec.runs.length }),
  last: null, list: () => recList().then((l) => l.map(({ blob, ...r }) => r)),
  draftB64: async () => { const all = await recList(); return all[0] ? b64enc(new Uint8Array(await all[0].blob.arrayBuffer())) : ''; },
  lastB64: async () => (window.__rec.last ? b64enc(new Uint8Array(await window.__rec.last.blob.arrayBuffer())) : ''),
};

// ---- replay (?replay=URL[&replayspeed=real][&replaystop=F][&replaykeep=1]): compare the run with the recording
// e2e.status() = { state: loading / running / done / mismatch / error, frame, total, checks matched, digests matched,
// first: the first difference, sameBuild, level, mode, ms }
Object.assign(e2e, { state: 'idle', doc: null, ci: 0, gi: 0, matchedChecks: 0, matchedG: 0, first: null, mismatches: 0, sameBuild: false,
  t0: 0, endFrame: 0, lastGood: 0, level: 0, mode: 0, keep: !!Q.get('replaykeep') });
const KIND = ['periodic', 'level / mode change', 'end'];
function e2eMismatch(m) {
  e2e.mismatches++;
  if (e2e.first) return;
  e2e.first = Object.assign({ lastGood: e2e.lastGood }, m);
  log(`[e2e] FIRST DIFFERENCE at retrace ${m.f}: ${m.what}`, 'fail');
  if (!e2e.keep) { e2e.state = 'mismatch'; e2e.ended = true; M._port_set_paused(1); }
}
function e2eG(f, g) {
  const want = e2e.g[f / e2e.doc.g_every - 1];
  if (want === undefined) return;   // past the recording's end
  if ((want >>> 0) === (g >>> 0)) { e2e.matchedG++; e2e.lastGood = Math.max(e2e.lastGood, f); return; }
  e2eMismatch({ f, field: 'G', what: `game digest G ${(g >>> 0).toString(16)}, the recording has ${(want >>> 0).toString(16)} (RNG, level / mode, character records)`, level: e2e.level, mode: e2e.mode });
}
function e2eCheck(c) {
  const [f, h, s, g, level, mode, kind, x, y, z] = c, exp = e2e.doc.checks[e2e.ci++];
  e2e.level = level; e2e.mode = mode;
  if (!exp) { if (e2e.doc.complete) e2eMismatch({ f, field: 'extra', what: `a ${KIND[kind]} checkpoint the recording does not have (level ${level.toString(16)}, mode ${mode})`, level, mode }); return; }
  const [ef, eh, es, eg, el, em, ek, ex, ey, ez] = exp;
  const pos = `Conker at ${x}, ${y}, ${z} (recording ${ex}, ${ey}, ${ez})`;
  let what = null, field = null;
  if (ef !== f) { field = 'frame'; what = `${KIND[kind]} checkpoint at retrace ${f} (level ${level.toString(16)} mode ${mode}), the recording's next one is a ${KIND[ek]} at retrace ${ef} (level ${el.toString(16)} mode ${em})`; }
  else if (el !== level || em !== mode) { field = 'level'; what = `level ${level.toString(16)} mode ${mode}, the recording has level ${el.toString(16)} mode ${em}; ${pos}`; }
  else if ((eg >>> 0) !== (g >>> 0)) { field = 'G'; what = `game digest G ${(g >>> 0).toString(16)}, the recording has ${(eg >>> 0).toString(16)}; ${pos}`; }
  else if (e2e.sameBuild && (eh >>> 0) !== (h >>> 0)) { field = 'H'; what = `static memory hash H ${(h >>> 0).toString(16)}, the recording has ${(eh >>> 0).toString(16)} (same build); ${pos}`; }
  else if (e2e.sameBuild && (es >>> 0) !== (s >>> 0)) { field = 'S'; what = `thread stack hash S ${(s >>> 0).toString(16)}, the recording has ${(es >>> 0).toString(16)} (same build)`; }
  if (what) e2eMismatch({ f: Math.min(f, ef), field, what, level, mode, expected: exp, actual: c });
  else { e2e.matchedChecks++; e2e.lastGood = Math.max(e2e.lastGood, f); }
}
function e2eEnd(f) {
  e2e.endFrame = f; e2e.ended = true;
  if (e2e.state === 'mismatch') return;
  const left = e2e.doc.checks.length - e2e.ci;
  if (!e2e.first && left > 0 && !Q.get('replaystop')) e2eMismatch({ f, field: 'missing', what: `${left} checkpoint(s) of the recording never came (the replay ended at retrace ${f})`, level: e2e.level, mode: e2e.mode });
  e2e.state = e2e.first ? 'mismatch' : 'done';
  log(`[e2e] replay ended at retrace ${f} of ${e2e.doc.retraces}: ${e2e.first ? 'DIFFERENT' : 'IDENTICAL'}; ${e2e.matchedChecks} checkpoints and ${e2e.matchedG} digests matched` +
      ` in ${((performance.now() - e2e.t0) / 1000).toFixed(1)} s (checkpoints ${M._port_rec_checkpoint_ms().toFixed(2)} ms each)`);
}
async function e2eBegin(Mod) {
  const doc = e2e.doc, n = doc.retraces, inputs = recDecodeRuns(b64dec(doc.inputs), n);
  e2e.g = u32dec(b64dec(doc.g));
  e2e.sameBuild = doc.build === await recBuildId();
  const p = Mod._malloc(Math.max(4, n * 4));
  Mod.HEAPU8.set(new Uint8Array(inputs.buffer), p);
  const fast = Q.get('replayspeed') !== 'real', stop = +(Q.get('replaystop') || 0);
  Mod._port_rec_session(2, doc.check_every, doc.g_every, p, n, fast ? 1 : 0, stop);
  e2e.state = 'running'; e2e.t0 = performance.now();
  log(`[e2e] replay of "${doc.name}" (${n} retraces, ${doc.checks.length} checkpoints, recorded with build ${doc.build}, this build ${wasmBuildId}: ` +
      `${e2e.sameBuild ? 'same build, H / S compared' : 'other build, only G / level / mode compared'})${fast ? ', fast' : ''}`);
}
async function e2eLoad(url) {   // ?replay=URL: fetch, check, boot
  try {
    e2e.state = 'loading';
    const doc = await recUnpack(await (await fetch(url)).arrayBuffer());
    if (romSha1 && doc.rom_sha1 && doc.rom_sha1 !== romSha1) throw new Error(`the recording was made with ROM SHA-1 ${doc.rom_sha1}, this ROM is ${romSha1}`);
    e2e.doc = doc;
    recCfg = { mode: 'replay', name: doc.name, options: doc.options, eeprom: b64dec(doc.eeprom) };
    for (const k of Object.keys(optCache)) delete optCache[k];
    log(`[e2e] loaded ${url}: "${doc.name}", ${doc.retraces} retraces, created ${doc.created}${doc.complete ? '' : ' (unfinished draft)'}`);
    start('game');
  } catch (e) { e2e.state = 'error'; e2e.error = String(e.message || e); log('[e2e] ' + e2e.error, 'fail'); }
}
window.__e2e = {
  status: () => ({ state: e2e.state, error: e2e.error || null, frame: M && M._port_net_frame ? M._port_net_frame() >>> 0 : 0, total: e2e.doc ? e2e.doc.retraces : 0,
    checks: e2e.doc ? e2e.doc.checks.length : 0, matchedChecks: e2e.matchedChecks, matchedG: e2e.matchedG, mismatches: e2e.mismatches, first: e2e.first,
    sameBuild: e2e.sameBuild, level: e2e.level, mode: e2e.mode, endFrame: e2e.endFrame, ms: e2e.t0 ? Math.round(performance.now() - e2e.t0) : 0,
    name: e2e.doc ? e2e.doc.name : '', build: wasmBuildId, recBuild: e2e.doc ? e2e.doc.build : '' }),
};

// ---------------------------------------------------------------- wasm apps
function loadScript(src) {
  return new Promise((res, rej) => {
    const s = document.createElement('script');
    s.src = src; s.onload = res; s.onerror = () => rej(new Error('cannot load ' + src));
    document.head.appendChild(s);
  });
}
async function start(app) {
  if (running) { location.search = '?app=' + app; return; } // one module per page
  running = app;
  $('demo').disabled = $('start').disabled = true;
  $('drop').hidden = true; $('ready').hidden = true;   // P360
  drawerSet(false);                                     // P360: the game starts with the menu closed
  status(app === 'game' ? 'starting…' : 'scheduler demo', 'ok');
  if (netCfg && app === 'game' && !window.PortNet) await loadScript('net.js');   // P338 (the Online panel loaded it already)
  const [js, factory] = app === 'demo' ? ['sched_demo.js', 'createSchedDemo'] : ['conker.js', 'createConker'];
  log(`-- loading ${js}`);
  await loadScript(js);
  // P349 test aid: ?canvas=WxH sets the canvas's drawing buffer (default 640 x 480) before the renderer reads its size,
  // e.g. ?canvas=1920x1440 to look at the 2D at a large resolution (the page box still scales it to fit)
  // P350: layoutScreen sets it (and the widescreen aspect) before the renderer reads it
  layoutScreen();
  const Mod = await window[factory]({
    canvas: $('canvas'),
    print: (s) => log(s),
    printErr: (s) => log(s, 'fail'),
    onAbort: (w) => { log('Aborted: ' + w, 'fail'); status('crashed (open Debug)', 'bad'); },
    portRumble: (ch, on) => portRumble(ch, on),   // P333 option "Rumble" (pc_pif.c)
    portEepDirty: () => { eepWrites++; if (!eepTimer) eepTimer = setTimeout(persistEeprom, 400); flashSaveIcon(); },
  });
  window.Module = M = Mod;
  for (const o of OPTIONS) sendOption(o);   // before callMain: the game reads them from its first frame
  optionChanged.hires2d(opt('hires2d'));   // P349: the renderer's switch (page-side option)
  optionChanged.smoothfont(opt('smoothfont'));   // P356: the renderer's switch (page-side option)
  optionChanged.hfr(opt('hfr'));           // P351: the renderer's switch (page-side option)
  layoutScreen();                          // P350: the renderer's widescreen switch
  optionsLocked = NETDET || !!netCfg || !!recCfg;
  if (optionsLocked) showSessionOptions();   // P346: the panel shows the session's (the host's) options, disabled
  log('[options] ' + OPTIONS.map((o) => `${o.key}=${o.range ? opt(o.key) : opt(o.key) ? 1 : 0}`).join(' '));
  if (app === 'game' && romBytes) {
    const p = M._malloc(romBytes.length);
    M.HEAPU8.set(romBytes, p);
    M._port_set_rom(p, romBytes.length);
    if (NETDET) { saveBlocked = true; log('[netdet] blank EEPROM, saves stay in this session'); }   // P337 sandbox
    else if (netCfg) {   // P338: the host's EEPROM image (or blank); saves stay in this session
      saveBlocked = true;
      if (netCfg.eeprom) M.HEAPU8.set(netCfg.eeprom.subarray(0, M._port_eeprom_size()), M._port_eeprom_ptr());
      log(`[net] ${netCfg.eeprom ? "host's" : 'blank'} EEPROM, saves stay in this session`);
    } else if (recCfg && recCfg.mode === 'replay') {   // P357: the recording's EEPROM image; nothing is saved
      saveBlocked = true;
      M.HEAPU8.set(recCfg.eeprom.subarray(0, M._port_eeprom_size()), M._port_eeprom_ptr());
      log(`[rec] replay: the recording's EEPROM (${recCfg.eeprom.length} bytes), saves stay in this session`);
    } else await loadEeprom(M);
  }
  $('threads').disabled = false;
  $('threads').onclick = () => M._port_dump_threads();
  $('pause').disabled = app !== 'game';
  // &audonly=1 (P14, audprobe.sh): data segments only, no game threads; for the audio tests
  if (Q.get('audonly')) log('audonly: game memory ' + (M._port_audio_prepare() > 0 ? 'loaded' : 'FAILED') + ', game not started');
  else {
    await netLoadExclusions(M);   // P337 state hash; P348 photo mode's snapshot needs the same list (nothing else uses it)
    if (netCfg) PortNet.begin(M, netCfg, log);   // P338: session before the first retrace
    if (recCfg) await recBegin(M);                // P357: recording / replay session before the first retrace
    try { M.callMain([]); } catch (e) { if (e !== 'unwind') log(String(e), 'fail'); }
  }
  if (app === 'game') status('running', 'ok');
  if (netCfg && netCfg.loop) PortNet.loopback(netCfg.loop);   // P338 test peer
  else if (netCfg) PortNet.startTransport();                    // P338 online: send / receive inputs
  if (netCfg && hiddenPaused) { hiddenPaused = false; applyPause(); }   // P339: the page was hidden before the session
                                                                        // (a covered window): a session never pauses
  applyPause();
  $('canvas').focus();
  // &audtest=HEX[:FRAMES]: n_audio synth + audio HLE test (port/audio/aud_test.c);
  // &voicetest=HEX[:CALLS] (P14): voice clip through the stream handler, MP3 decoder and MP3 ABI.
  // Without &audprobe they run on the next click (a user gesture, so the audio can start).
  const at = Q.get('audtest'), vt = Q.get('voicetest');
  const run = at ? () => { const [r, f] = at.split(':'); M._port_audio_test(parseInt(r, 16), +(f || 150)); }
            : vt ? () => { const [r, f] = vt.split(':'); M._port_voice_test(parseInt(r, 16), +(f || 2000)); } : null;
  if (app === 'game' && run) {
    if (Q.get('audprobe')) { log('audprobe: starting the audio test without a click'); setTimeout(run, 500); }
    else {
      log('audio test: click the page to synthesise and play it');
      document.addEventListener('click', run, { once: true });
    }
  }
  // &eeptest=w:SEED / r:SEED (P27 test aid): EEPROM write / read-back through the PIF commands, 2 s after start
  const et = Q.get('eeptest');
  if (app === 'game' && et) setTimeout(() => M._port_eep_test(et[0] === 'w' ? 1 : 2, parseInt(et.slice(2), 10) || 1), 2000);
}

// &audprobe=1 (P14, test aid): count what the Web Audio graph actually pulls. Every
// ScriptProcessorNode's onaudioprocess is wrapped; after the original handler fills outputBuffer, the
// probe counts callbacks, frames and non-zero samples and the rms, and logs a summary line
// ("[audprobe] ...") every second. port/web/audprobe.sh.
function installAudioProbe() {
  const st = { ctx: 0, nodes: 0, calls: 0, frames: 0, nonzero: 0, sq: 0, peak: 0, rate: 0, state: '' };
  window.audprobe = st;
  for (const name of ['AudioContext', 'webkitAudioContext']) {
    const C = window[name];
    if (!C || C.prototype.__probed) continue;
    C.prototype.__probed = true;
    const orig = C.prototype.createScriptProcessor;
    C.prototype.createScriptProcessor = function (...a) {
      const node = orig.apply(this, a), ctx = this;
      st.nodes++; st.rate = ctx.sampleRate;
      ctx.addEventListener('statechange', () => { st.state = ctx.state; });
      let user = null;
      const wrapped = (e) => {
        if (user) user.call(node, e);
        st.calls++; st.state = ctx.state;
        const b = e.outputBuffer;
        st.frames += b.length;
        for (let c = 0; c < b.numberOfChannels; c++) {
          const d = b.getChannelData(c);
          for (let i = 0; i < d.length; i++) {
            const v = d[i];
            if (v !== 0) { st.nonzero++; st.sq += v * v; if (Math.abs(v) > st.peak) st.peak = Math.abs(v); }
          }
        }
      };
      Object.defineProperty(node, 'onaudioprocess', {
        get: () => user, set: (f) => { user = f; node.addEventListener('audioprocess', wrapped); }, configurable: true,
      });
      return node;
    };
    const Orig = C;
    window[name] = function (...a) { st.ctx++; const c = new Orig(...a); st.state = c.state; return c; };
    window[name].prototype = Orig.prototype;
  }
  setInterval(() => {
    if (!st.calls && !st.ctx) return;
    const rms = st.nonzero ? Math.sqrt(st.sq / st.nonzero) : 0;
    log(`[audprobe] contexts ${st.ctx} nodes ${st.nodes} rate ${st.rate} state ${st.state}: ${st.calls} callbacks, ` +
        `${st.frames} frames pulled, ${st.nonzero} non-zero samples, rms ${rms.toFixed(4)} peak ${st.peak.toFixed(3)}`);
  }, 1000);
}
if (Q.get('audprobe')) installAudioProbe();
$('demo').onclick = () => start('demo');
$('start').onclick = () => start('game');

(async () => {
  if (!Q.get('romurl')) try {
    const cached = await idb('rom', 'readonly', (s) => s.get('eu'));
    if (cached) await setRom(new Uint8Array(cached), 'cached in this browser');
  } catch (e) { /* no IndexedDB: fine */ }
  // dev/test aid: &romurl=PATH fetches the ROM from the (local) server instead of the picker; it is
  // not cached. Used by the headless browser tests with a read-only mount (docs/port/design/P4.md).
  if (Q.get('romurl')) {
    try { await setRom(new Uint8Array(await (await fetch(Q.get('romurl'))).arrayBuffer()), 'dev romurl'); }
    catch (e) { log('romurl: ' + e.message, 'fail'); }
  }
  // &dump=MS: dump threads + the ranked stub-hit list after MS milliseconds
  if (Q.get('dump')) setTimeout(() => window.Module && window.Module._port_dump_threads(), +Q.get('dump'));
  // P357: ?replay=URL (an input recording, e2e_replay.sh) / ?record=1 or a "Start recording" that reloaded the page
  let armed = null; try { armed = sessionStorage.getItem('conker.recArm'); sessionStorage.removeItem('conker.recArm'); } catch (e) { /* no storage */ }
  if (Q.get('replay') && romBytes) return e2eLoad(Q.get('replay'));
  if ((armed !== null || Q.get('record')) && romOk) { showRecButton(true); toggle('rec', true); return recArm(armed || Q.get('recname') || ''); }
  const app = Q.get('app');
  if (app === 'demo' || (app === 'game' && romBytes)) start(app);
})();

// P19: show the wasm stack of an uncaught error on the page (the console text alone has no stack)
window.addEventListener('error', (e) => {
  log(String(e.message || e), 'fail');
  const st = e.error && e.error.stack ? String(e.error.stack).split('\n').slice(0, 12).join('\n') : '';
  if (st) try { log('[error] ' + st, 'fail'); } catch (_) { console.error(st); }
});
