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
  M.callMain([]);
  // AUDTEST=<hex sound record offset>[:frames]: drive the C n_audio synth + audio HLE (port/audio/aud_test.c)
  if (process.env.AUDTEST) setTimeout(() => { const [r, f] = process.env.AUDTEST.split(':'); M._port_audio_test(parseInt(r, 16), +(f || 150)); }, 1500);
  // VOICETEST=<hex voice clip id>[:calls]: voice stream handler + MP3 decoder + MP3 ABI (P14)
  if (process.env.VOICETEST) setTimeout(() => { const [r, f] = process.env.VOICETEST.split(':'); M._port_voice_test(parseInt(r, 16), +(f || 2000)); }, 1500);
  // P27 PADTEST=1: scripted pad 0 input through the heap pad state (same path as the page's keyboard):
  // A + Start + stick (80, -40) from 3 s, released at 4 s; the PIF model and func_1501BBB8 log [pad] lines
  if (process.env.PADTEST && M._port_pad_state) {
    const p = M._port_pad_state() >> 2;
    setTimeout(() => { M.HEAP32[p + 1] = 0x9000; M.HEAP32[p + 2] = 80; M.HEAP32[p + 3] = -40; console.log('[padtest] press A+Start, stick 80,-40'); }, 3000);
    setTimeout(() => { M.HEAP32[p + 1] = 0; M.HEAP32[p + 2] = 0; M.HEAP32[p + 3] = 0; console.log('[padtest] release'); }, 4000);
  }
  // P27 EEPTEST=seed: EEPROM write then read back through PIF commands 05/04 (no IndexedDB in node)
  if (process.env.EEPTEST && M._port_eep_test) setTimeout(() => { M._port_eep_test(1, +process.env.EEPTEST); M._port_eep_test(2, +process.env.EEPTEST); }, 2000);
  setTimeout(() => { M._port_dump_threads(); process.exit(0); }, +secs * 1000);
});
