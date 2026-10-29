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
