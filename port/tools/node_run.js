// Headless smoke test: node port/tools/node_run.js port/build/web/sched_demo.js createSchedDemo [seconds] [rom]
const path = require('path'), fs = require('fs');
const [js, factory, secs = '6', rom] = process.argv.slice(2);
global.requestAnimationFrame = (f) => setTimeout(() => f(performance.now()), 16);
const create = require(path.resolve(js));
create({ print: (s) => console.log(s), printErr: (s) => console.error(s), noExitRuntime: true }).then((M) => {
  if (rom) {
    const b = fs.readFileSync(rom); const p = M._malloc(b.length); M.HEAPU8.set(b, p); M._port_set_rom(p, b.length);
  }
  if (process.env.GFXDEMO) { const t = M.stringToNewUTF8 ? M.stringToNewUTF8(process.env.GFXDEMO) : 0; M._port_gfx_demo_test(t); }
  // P337: the online-multiplayer state hash (PORT_NETHASH / PORT_NETHASHSTOP / PORT_NETSNAP) leaves out the ranges the
  // build lists in conker_netx.txt (port/tools/net_regions.py), as the page does
  if ((process.env.PORT_NETHASH || process.env.PORT_NETSNAP) && M._port_net_exclude) {
    const t = fs.readFileSync(path.join(path.dirname(path.resolve(js)), 'conker_netx.txt'), 'utf8'); let n = 0;
    for (const l of t.split('\n')) { const f = l.split(' '); if (f.length >= 2) { M._port_net_exclude(parseInt(f[0], 16), parseInt(f[1], 16)); n++; } }
    console.log(`[nethash] ${n} excluded static ranges from conker_netx.txt`);
  }
  M.callMain([]);
  // AUDTEST=<hex sound record offset>[:frames]: drive the C n_audio synth + audio HLE (port/audio/aud_test.c)
  if (process.env.AUDTEST) setTimeout(() => { const [r, f] = process.env.AUDTEST.split(':'); M._port_audio_test(parseInt(r, 16), +(f || 150)); }, 1500);
  // VOICETEST=<hex voice clip id>[:calls]: voice stream handler + MP3 decoder + MP3 ABI (P14)
  if (process.env.VOICETEST) setTimeout(() => { const [r, f] = process.env.VOICETEST.split(':'); M._port_voice_test(parseInt(r, 16), +(f || 2000)); }, 1500);
  // P27 PADTEST=1: scripted pad 0 input through the heap pad state (same path as the page's keyboard):
  // A + Start + stick (80, -40) from 3 s, released at 4 s; the PIF model and cont_read_frame log [pad] lines
  if (process.env.PADTEST && M._port_pad_state) {
    const p = M._port_pad_state() >> 2;
    setTimeout(() => { M.HEAP32[p + 1] = 0x9000; M.HEAP32[p + 2] = 80; M.HEAP32[p + 3] = -40; console.log('[padtest] press A+Start, stick 80,-40'); }, 3000);
    setTimeout(() => { M.HEAP32[p + 1] = 0; M.HEAP32[p + 2] = 0; M.HEAP32[p + 3] = 0; console.log('[padtest] release'); }, 4000);
  }
  // P49 PADSCRIPT="ms:buttons:x:y; ...": pad 0 state from wall time ms (buttons hex N64 bits, stick x / y, y > 0 = up)
  if (process.env.PADSCRIPT && M._port_pad_state) {
    const p = M._port_pad_state() >> 2;
    for (const step of process.env.PADSCRIPT.split(';').map((x) => x.trim()).filter(Boolean)) {
      const [t, b, x, y] = step.split(':');
      setTimeout(() => { M.HEAP32[p + 1] = parseInt(b || '0', 16); M.HEAP32[p + 2] = +(x || 0); M.HEAP32[p + 3] = +(y || 0);
        console.log(`[padscript] t ${t} ms: buttons ${b || 0} stick ${x || 0},${y || 0}`); }, +t);
    }
  }
  // P27 EEPTEST=seed: EEPROM write then read back through PIF commands 05/04 (no IndexedDB in node)
  if (process.env.EEPTEST && M._port_eep_test) setTimeout(() => { M._port_eep_test(1, +process.env.EEPTEST); M._port_eep_test(2, +process.env.EEPTEST); }, 2000);
  // P337 NETDUMP=PATH: at the end, write the hashed memory regions (after PORT_NETHASHSTOP paused the game) in the
  // page's dump format (port/web/audprobe.js PROBE_DUMP) for tools/port/nethash_diff.py --dump
  const netdump = () => {
    if (!process.env.NETDUMP || !M._port_net_region) return;
    const regions = [];
    for (let i = 0; M._port_net_region(i, 0) !== -1; i++) { const a = M._port_net_region(i, 0) >>> 0, l = M._port_net_region(i, 1); if (l) regions.push({ i, addr: a, len: l }); }
    const fd = fs.openSync(process.env.NETDUMP, 'w');
    fs.writeSync(fd, JSON.stringify({ frame: +(process.env.PORT_NETHASHSTOP || 0), regions }) + '\n');
    for (const r of regions) fs.writeSync(fd, M.HEAPU8.subarray(r.addr, r.addr + r.len));
    fs.closeSync(fd); console.log(`[nethash] dump of ${regions.length} regions -> ${process.env.NETDUMP}`);
  };
  setTimeout(() => { netdump(); M._port_dump_threads(); process.exit(0); }, +secs * 1000);
});
