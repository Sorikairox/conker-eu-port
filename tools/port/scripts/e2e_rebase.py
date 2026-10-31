"""P373: rebase an e2e recording (.ckrec, docs/port/E2E.md) on the current build: keep its pad input, save, options and
everything else, replace the reference digests (g), checkpoints (H, S, G, level, mode, kind, Conker position) and the
build id with what this build's replay produced, and log the change in the file's `rebased` list.
Refuses (exit 1, file untouched) when the replay's gameplay differs from the recording: a checkpoint at another
retrace, of another kind, on another level / mode, with Conker elsewhere, or a checkpoint missing / extra. Then the
pad input no longer fits the game and a person has to record the chapter again.
  python3 tools/port/scripts/e2e_rebase.py OUT/<name>/rebase.json tests/e2e/recordings/<name>.ckrec ['why']
(rebase.json comes from tools/port/scripts/e2e_replay.sh REBASE=1, which calls this script.)"""
import gzip, json, sys, datetime

rb_path, rec_path = sys.argv[1], sys.argv[2]
why = sys.argv[3] if len(sys.argv) > 3 else ''
try:
    rb = json.load(open(rb_path))
except (OSError, ValueError) as e:
    sys.exit(f'e2e_rebase: no replay data ({e})')
raw = open(rec_path, 'rb').read()
doc = json.loads(gzip.decompress(raw) if raw[:2] == b'\x1f\x8b' else raw)
name = rec_path.split('/')[-1]
if not rb.get('ended') or rb.get('endFrame') != doc['retraces']:
    sys.exit(f'e2e_rebase: {name}: the replay did not reach the end ({rb.get("endFrame")} of {doc["retraces"]}); not rebased')
if rb['gameplay']:
    print(f'e2e_rebase: {name}: the recorded input no longer plays the same route ({len(rb["gameplay"])} checkpoint(s) differ in '
          f'retrace / kind / level / mode / Conker position); not rebased. First ones:')
    for d in rb['gameplay'][:5]:
        print('   ', json.dumps(d))
    sys.exit(1)
n_g = doc['retraces'] // doc['g_every']
if rb['nG'] < n_g or len(rb['checks']) != len(doc['checks']):
    sys.exit(f'e2e_rebase: {name}: {rb["nG"]} digests / {len(rb["checks"])} checkpoints, the recording has {n_g} / {len(doc["checks"])}')
import base64
g = base64.b64decode(rb['g'])[:4 * n_g]
old = (doc['build'], doc['g'], doc['checks'])
changed_g = sum(1 for i in range(n_g) if g[4 * i:4 * i + 4] != base64.b64decode(doc['g'])[4 * i:4 * i + 4])
doc.setdefault('rebased', []).append({'date': datetime.datetime.now(datetime.timezone.utc).isoformat(timespec='seconds'),
                                      'from_build': doc['build'], 'to_build': rb['build'], 'why': why,
                                      'changed_digests': changed_g})
doc['build'], doc['g'], doc['checks'] = rb['build'], base64.b64encode(g).decode(), rb['checks']
open(rec_path, 'wb').write(gzip.compress(json.dumps(doc, separators=(',', ':')).encode(), mtime=0))
print(f'e2e_rebase: {name}: rebased on build {rb["build"]} (was {old[0]}): {changed_g} of {n_g} digests changed, '
      f'{len(doc["checks"])} checkpoints, same route (every checkpoint\'s retrace, kind, level, mode, Conker position as recorded)')
