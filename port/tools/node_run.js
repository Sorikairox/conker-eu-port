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
  setTimeout(() => { M._port_dump_threads(); process.exit(0); }, +secs * 1000);
});
