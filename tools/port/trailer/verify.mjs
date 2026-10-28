// P354 trailer: check the encoded MP4 in Chrome (no ffprobe on the host). The file is demuxed with mp4box.js
// (npm, local tooling under port_work/trailer/npm) and its H.264 samples are decoded with WebCodecs VideoDecoder: the
// tracks' codecs, sizes, sample counts and frame rate, decoded pictures at the given times (contact-sheet frames,
// OUT/check_SS.ss.jpg), and the AAC track decoded by Web Audio (duration, channels, loudness per second).
// (A <video> element drew black frames in headless Chrome, so it is not used for the pictures.)
//   node tools/port/trailer/verify.mjs [port_work/trailer/out/trailer.mp4] [T1,T2,...]
import path from 'node:path';
import { launch, serve, sleep } from './cdp.mjs';

const ROOT = path.resolve(path.dirname(new URL(import.meta.url).pathname), '../../..');
process.chdir(ROOT);
const file = path.resolve(process.argv[2] || 'port_work/trailer/out/trailer.mp4');
const times = (process.argv[3] || '1.5,6.5,12,17.5,23,27,30,33.2,34.3,35.4,36.4,37.5,41').split(',').map(Number);
const dir = path.dirname(file);
const port = 8680 + (process.pid % 10);
const srv = await serve({ '/v.mp4': file, '/t/': 'tools/port/trailer', '/npm/mp4box.js': 'port_work/trailer/npm/node_modules/mp4box/dist/mp4box.all.js' }, port, dir);
const b = await launch(`http://127.0.0.1:${port}/t/blank.html`, { log: path.join(dir, 'verify.log') });
try {
  await sleep(800);
  await b.ev(`new Promise((ok, no) => { const s = document.createElement('script'); s.src = '/npm/mp4box.js'; s.onload = ok; s.onerror = no; document.head.appendChild(s); })`);
  const r = await b.ev(`(async () => {
    const ab = await (await fetch('/v.mp4')).arrayBuffer();
    const mp = MP4Box.createFile(); let info;
    const samples = {};
    mp.onReady = (i) => { info = i; for (const t of i.tracks) { samples[t.id] = []; mp.setExtractionOptions(t.id, null, { nbSamples: 1e6 }); } mp.start(); };
    mp.onSamples = (id, u, s) => { samples[id].push(...s); };
    ab.fileStart = 0; mp.appendBuffer(ab); mp.flush();
    const vt = info.videoTracks[0], at = info.audioTracks[0];
    const out = { duration: info.duration / info.timescale, video: vt && { codec: vt.codec, w: vt.video.width, h: vt.video.height, samples: vt.nb_samples,
      fps: +(vt.nb_samples / (vt.duration / vt.timescale)).toFixed(2), kbps: Math.round(vt.bitrate / 1000) },
      audio: at && { codec: at.codec, rate: at.audio.sample_rate, channels: at.audio.channel_count, samples: at.nb_samples }, shots: [] };
    // avcC -> decoder description
    const trak = mp.getTrackById(vt.id), entry = trak.mdia.minf.stbl.stsd.entries[0];
    const st = new DataStream(undefined, 0, DataStream.BIG_ENDIAN); entry.avcC.write(st);
    const desc = new Uint8Array(st.buffer, 8);
    const vs = samples[vt.id];
    const c = new OffscreenCanvas(vt.video.width, vt.video.height), g = c.getContext('2d');
    for (const t of ${JSON.stringify(times)}) {
      const target = Math.round(t * vt.timescale);
      let k = vs.findIndex((s) => s.cts >= target); if (k < 0) k = vs.length - 1;
      let key = k; while (key > 0 && !vs[key].is_sync) key--;
      const frames = []; let err = null;
      const dec = new VideoDecoder({ output: (f) => frames.push(f), error: (e) => err = e });
      dec.configure({ codec: vt.codec, description: desc });
      for (let i = key; i <= k; i++) dec.decode(new EncodedVideoChunk({ type: vs[i].is_sync ? 'key' : 'delta', timestamp: vs[i].cts * 1e6 / vt.timescale, data: vs[i].data }));
      await dec.flush(); dec.close();
      if (err) throw err;
      frames.sort((a, b2) => a.timestamp - b2.timestamp);
      const f = frames[frames.length - 1]; g.drawImage(f, 0, 0); frames.forEach((x) => x.close());
      const name = 'check_' + t.toFixed(2).padStart(5, '0') + '.jpg';
      await fetch('/upload/' + name, { method: 'POST', body: await c.convertToBlob({ type: 'image/jpeg', quality: 0.9 }) });
      out.shots.push(name);
    }
    const ac = new OfflineAudioContext(2, 48000, 48000), au = await ac.decodeAudioData(ab.slice(0));
    const L = au.getChannelData(0), rms = [];
    for (let s = 0; s < au.duration; s++) { let e = 0, n = 0; for (let i = s * au.sampleRate; i < Math.min(L.length, (s + 1) * au.sampleRate); i++) { e += L[i] * L[i]; n++; } rms.push(+(Math.sqrt(e / n) * 100).toFixed(1)); }
    out.audioDecoded = { duration: au.duration, channels: au.numberOfChannels, rmsPercentPerSecond: rms };
    return JSON.stringify(out);
  })()`);
  console.log(r);
} finally { await b.close(); srv.close(); }
process.exit(0);
