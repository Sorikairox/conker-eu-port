// Headless smoke test: node port/tools/node_run.js port/build/web/sched_demo.js createSchedDemo [seconds] [rom]
const path = require('path'), fs = require('fs');
const [js, factory, secs = '6', rom] = process.argv.slice(2);
global.requestAnimationFrame = (f) => setTimeout(() => f(performance.now()), 16);
const create = require(path.resolve(js));
create({ print: (s) => console.log(s), printErr: (s) => console.error(s), noExitRuntime: true }).then((M) => {
  if (rom) {
    const b = fs.readFileSync(rom); const p = M._malloc(b.length); M.HEAPU8.set(b, p); M._port_set_rom(p, b.length);
  }
  M.callMain([]);
  setTimeout(() => { M._port_dump_threads(); process.exit(0); }, +secs * 1000);
});
