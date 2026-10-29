// P355 trailer: rank captured music by how lively it is (no packages; for picking a track by measurement, since the
// tooling cannot listen). Per shot dir (capture.mjs output with audio.pcm + meta.json):
//   rms (dBFS), bright = rms of the first difference / rms (more treble / percussion -> higher), onset density
//   (onsets per second), tempo (BPM from the onset autocorrelation) and its pulse strength (normalised autocorrelation
//   peak: a steady beat -> higher), silence share.
//   node tools/port/trailer/musicstat.mjs DIR [DIR ...]   [FROM=s TO=s env: window inside the pcm]
//   node tools/port/trailer/musicstat.mjs --beats DIR      the beat grid (s) of the window, for cutting on the beat
import fs from 'node:fs';
import path from 'node:path';

const beatsMode = process.argv[2] === '--beats';
const dirs = process.argv.slice(beatsMode ? 3 : 2);
const FROM = +(process.env.FROM || 0), TO = +(process.env.TO || 1e9);
export function analyse(pcm, rate, from = 0, to = 1e9) {
  const n = pcm.length >> 1, i0 = Math.floor(from * rate), i1 = Math.min(n, Math.floor(to * rate));
  const mono = new Float32Array(Math.max(0, i1 - i0));
  for (let i = i0; i < i1; i++) mono[i - i0] = (pcm[2 * i] + pcm[2 * i + 1]) / 65536;
  let e = 0, d = 0, sil = 0;
  for (let i = 1; i < mono.length; i++) { e += mono[i] * mono[i]; const x = mono[i] - mono[i - 1]; d += x * x; }
  const hop = Math.round(rate / 100), env = [];
  for (let i = 0; i + hop <= mono.length; i += hop) {
    let s = 0, hf = 0;
    for (let k = i; k < i + hop; k++) { s += mono[k] * mono[k]; if (k) { const x = mono[k] - mono[k - 1]; hf += x * x; } }
    if (s / hop < 1e-6) sil++;
    env.push(Math.log1p(1e4 * (s + 4 * hf) / hop));   // energy + treble: drums show up
  }
  const on = env.map((v, i) => (i ? Math.max(0, v - env[i - 1]) : 0));
  const m = on.reduce((a, b) => a + b, 0) / on.length, z = on.map((v) => v - m);
  const v0 = z.reduce((a, b) => a + b * b, 0) / z.length || 1;
  let best = [0, 50];
  for (let lag = 30; lag <= 100; lag++) {   // 60..200 BPM
    let c = 0; for (let i = 0; i + lag < z.length; i++) c += z[i] * z[i + lag];
    c /= (z.length - lag) * v0;
    if (c > best[0]) best = [c, lag];
  }
  const thr = m + 1.5 * Math.sqrt(on.reduce((a, b) => a + (b - m) ** 2, 0) / on.length);
  let onsets = 0; for (let i = 1; i < on.length - 1; i++) if (on[i] > thr && on[i] >= on[i - 1] && on[i] > on[i + 1]) onsets++;
  // beat grid: the phase whose comb collects the most onset strength
  const lag = best[1]; let ph = 0, phv = -1;
  for (let p = 0; p < lag; p++) { let s = 0; for (let i = p; i < on.length; i += lag) s += on[i]; if (s > phv) { phv = s; ph = p; } }
  // refine the period to 0.1 ms and the phase to 10 ms (a whole-centisecond lag drifts over a 30 s cut), then the bar
  // phase: the beat of four that collects the most onset strength (the downbeat)
  let rp = [lag / 100, ph / 100], rv = -1;
  for (let per = lag / 100 - 0.008; per <= lag / 100 + 0.008; per += 0.0001)
    for (let p0 = 0; p0 < per; p0 += 0.01) {
      let sum = 0; for (let t = p0; t * 100 < on.length - 1; t += per) { const k = Math.round(t * 100); sum += Math.max(on[k], on[k - 1] || 0, on[k + 1] || 0); }
      if (sum > rv) { rv = sum; rp = [per, p0]; }
    }
  const beats = []; for (let t = rp[1]; t * 100 < on.length; t += rp[0]) beats.push(+(from + t).toFixed(3));
  const barSum = [0, 0, 0, 0]; beats.forEach((b, i) => { const k = Math.round((b - from) * 100); barSum[i % 4] += on[k] || 0; });
  const down = barSum.indexOf(Math.max(...barSum));
  return { secs: +(mono.length / rate).toFixed(1), dbfs: +(10 * Math.log10(e / mono.length + 1e-12)).toFixed(1), bright: +Math.sqrt(d / (e || 1)).toFixed(3),
    onsetsPerSec: +(onsets / (on.length / 100)).toFixed(2), bpm: +(60 / rp[0]).toFixed(2), period: +rp[0].toFixed(4), downbeat: down, pulse: +best[0].toFixed(3), silence: +(sil / env.length).toFixed(2), beats };
}
if (dirs.length) {
  for (const d of dirs) {
    const meta = JSON.parse(fs.readFileSync(path.join(d, 'meta.json'), 'utf8'));
    const b = fs.readFileSync(path.join(d, 'audio.pcm')), pcm = new Int16Array(b.buffer, b.byteOffset, b.length >> 1);
    const r = analyse(pcm, meta.audio.rate, FROM, TO);
    if (beatsMode) { console.log(`${path.basename(d)}: ${r.bpm} BPM, period ${r.period} s (pulse ${r.pulse}), downbeats = beats ${r.downbeat}, ${r.downbeat + 4}, ...`); console.log(r.beats.join(' ')); continue; }
    delete r.beats;
    console.log(path.basename(d).padEnd(14), JSON.stringify(r));
  }
}
