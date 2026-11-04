#!/usr/bin/env python3
"""P337 online multiplayer phase 0: the static ranges the per-retrace state hash leaves out (port/ultra/pc_nethash.c).

Reads the wasm-ld map (port/build/conker.map, -Wl,-Map in port/Makefile) and prints one line per excluded data symbol,
"ADDR_HEX LEN_HEX OBJECT SYMBOL REASON". The page (main.js) loads the file (port/build/web/conker_netx.txt) under ?nethash
and passes each range to port_net_exclude() before callMain; tools/port/nethash_diff.py reads it to ignore the same bytes.

Rule: everything in the static region (the n64_rdram / n64_seg16 mirrors, every game C global, the port's PIF / timer /
scheduler state, the audio HLE and MP3 decoder state, the game-logic wrappers in port/gfx/p*.c) is game state and is
hashed, except what is port-only and may legitimately differ between peers:
  renderer   gfx_f3dex2.o, gfx_demo.o: GL object mirrors, texture caches, glReadPixels scratch (GPU-dependent bytes)
  audio out  aud_out.o except the virtual AI queue (det_vq, det_vf, det_on, game_rate): the Web Audio ring and its
             indices (moved by the browser's audio callback), WAV capture, pacing statistics
  wall time  pc_os.o t0 / pause_at / pause_total / port_paused, pc_sched.o frame.last_tick_ms / backlog_ms / pacing_mode (wall-clock
             VI pacing), slow_frames / budget_frames (wall-time statistics), sched_astack / sched_fiber (the browser-side
             scheduler context: its stack depth depends on whether rAF or setTimeout called frame()), pc_video.o (GL
             context handle; port_gfx_frame_tasks resets per presented frame, i.e. per rAF tick)
  photo mode pc_photo.o (P348: the photo camera and the clock hold; photo mode restores the hashed state, not itself)
  menu sound pc_sfx.o (P367: the game-style menus' sound decoder output; the page never decodes during a session)
  harness    pc_net.o, pc_nethash.o (this hash itself), pc_pif.o padf* / padrec* (each peer's script text and table)
             p205_obj.o go_n / p240_steer.cfg (test autopilots, set by the ?padf path only; P338)
  libc       dlmalloc state (_gm_, mparams: mparams.magic is seeded from time()), sbrk_val (heap top: moves with page /
             renderer allocations), stdio buffers (log text)
  renderer   pc_os.o port_vi_view.full (?p147vifull cache, first read by the gfx task)
The main C stack (__data_end .. __heap_base) and the heap are outside the static region; the game threads' fiber stacks
(static slots fiber_*stack_pool under ?netdet, heap otherwise) are hashed separately, live slots only (S column)."""
import sys

EXCLUDE_OBJ = {'gfx_f3dex2.o': 'renderer', 'gfx_demo.o': 'renderer', 'pc_net.o': 'harness', 'pc_nethash.o': 'harness',
               'pc_photo.o': 'photo mode',   # P348: photo mode's own state (pose, clock hold) survives the snapshot restores
               'pc_sfx.o': 'menu sounds',    # P367: the page's menu sound decoder (its PCM buffer; never used online)
               'pc_rtw.o': 'retrowser host interface'}   # P376: raw host input, save generation (only in the rtw build)
KEEP_IN_AUD_OUT = {'det_vq', 'det_vf', 'det_on', 'game_rate'}
EXCLUDE_SYM = {
    'pc_os.o': {'port_vi_view.full': 'renderer flag cache', 't0': 'wall time', 'pause_at': 'wall time', 'pause_total': 'wall time', 'port_paused': 'page pause'},
    'pc_sched.o': {'frame.last_tick_ms': 'wall time', 'frame.backlog_ms': 'wall time', 'frame.pacing_mode': 'pacing mode', 'slow_frames': 'wall time',
                   'budget_frames': 'wall time', 'sched_astack': 'browser context', 'sched_fiber': 'browser context',
                   'fiber_cstack_pool': 'hashed as stacks', 'fiber_astack_pool': 'hashed as stacks'},
    'p205_obj.o': {'go_n': 'test aid', 'p240_steer.cfg': 'test aid'},   # P338: ?p205goto / ?p240steer autopilot state (lazy flag reads)
    'pc_video.o': None,   # whole object
    'dlmalloc.o': None, 'sbrk.o': None, 'stdout.o': None, 'stderr.o': None, 'ofl.o': None,
}


def entries(path):
    """(addr, size, object, symbol) of every data input section in the map"""
    for line in open(path):
        p = line.split(None, 3)
        if len(p) != 4 or p[0] == '-' or ':(' not in p[3]:
            continue
        obj, sec = p[3].strip().rsplit(':(', 1)
        sec = sec.rstrip(')')
        if not sec.startswith(('.data.', '.bss.', '.rodata.', '.tdata.')):
            continue
        objname = obj.split('/')[-1]
        if '(' in objname:                       # libc-debug.a(stdout.o)
            objname = objname.split('(')[-1].rstrip(')')
        yield int(p[0], 16), int(p[2], 16), objname, sec.split('.', 2)[2]


def classify(obj, sym):
    if obj in EXCLUDE_OBJ:
        return EXCLUDE_OBJ[obj]
    if obj == 'aud_out.o':
        return None if sym in KEEP_IN_AUD_OUT else 'audio out'
    if obj == 'pc_pif.o' and sym.startswith(('padf', 'padrec')):
        return 'harness (pad script)'
    if obj in EXCLUDE_SYM:
        rules = EXCLUDE_SYM[obj]
        if rules is None:
            return 'port only'
        return rules.get(sym)
    return None


def syms(map_path):
    """P339 --syms: the symbol table of the desync report (net.js comparePages): 'W addr size name' for every hashed
    wasm static symbol (from the map), 'N addr size name' for every N64 data symbol (port/symbols/symbols.tsv, renamed
    through tools/eu_port/names.tsv) for pages inside the n64_rdram mirror."""
    from pathlib import Path
    import re
    root = Path(__file__).resolve().parents[2]
    for addr, size, obj, sym in entries(map_path):
        if size and not classify(obj, sym):
            print(f'W {addr:X} {size:X} {obj}:{sym}')
    new = {}
    names = root / 'tools/eu_port/names.tsv'
    if names.exists():
        for line in open(names):
            f = line.rstrip('\n').split('\t')
            if len(f) >= 2 and not line.startswith('#'):
                new[f[0]] = f[1]
    for line in open(root / 'port/symbols/symbols.tsv'):
        f = line.rstrip('\n').split('\t')
        if line.startswith('#') or len(f) < 4 or f[3] in ('func', 'none') or not re.fullmatch(r'80[0-7][0-9A-Fa-f]{5}', f[1]):
            continue
        size = int(f[2], 16) if re.fullmatch(r'[0-9A-Fa-f]+', f[2] or '') else 0
        print(f'N {f[1].upper()} {size:X} {new.get(f[0], f[0])}')


def main():
    if len(sys.argv) == 3 and sys.argv[1] == '--syms':
        return syms(sys.argv[2])
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    n = total = 0
    for addr, size, obj, sym in entries(sys.argv[1]):
        why = classify(obj, sym)
        if why and size:
            print(f'{addr:08X} {size:X} {obj} {sym} {why.replace(" ", "_")}')
            n += 1; total += size
    print(f'net_regions: {n} excluded ranges, {total >> 10} KB', file=sys.stderr)


if __name__ == '__main__':
    main()
