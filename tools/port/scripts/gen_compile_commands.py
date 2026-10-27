#!/usr/bin/env python3
"""P342: write compile_commands.json (worktree root, gitignored) for CLion / clangd code understanding.

Covers every game TU (conker/src_eu/**/*.c, census-failed ones included), the PC-side game TUs (port/boot, the
audio test / mp3 TUs that go through the vbe pass) with the game flags of port/tools/census.py (BASE + PORT_RELAX:
-nostdinc, -include port/ultra/port_prefix.h, -DPORT, the conker/include dirs, ...), and port/ultra, port/gfx,
port/audio, port/sched_demo with port/Makefile's ULTRA_CFLAGS (directory port/, as make runs them). All host paths.

The compiler is the host clang with --target=wasm32-unknown-emscripten (32-bit long and pointers, __EMSCRIPTEN__,
as emcc). The PC layer's system headers (musl, SDL2, clang builtins) come from the emsdk container and are copied
once to port/build-dbg/cc/ (docker); without docker the PC-layer entries still index, minus system headers.
Run: python3 tools/port/scripts/gen_compile_commands.py   (also run by tools/port/scripts/debug_build.sh)"""
import glob, json, os, re, shlex, subprocess, sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../..'))
os.chdir(ROOT)
sys.path.insert(0, os.path.join(ROOT, 'port/tools'))
import census  # noqa: E402  (game flags, the single source of truth)

CC = '/usr/bin/clang'
TARGET = ['--target=wasm32-unknown-emscripten']
SYS = f'{ROOT}/port/build-dbg/cc'


def sys_headers():
    """emscripten sysroot include + clang resource include, copied from the toolchain image (once)"""
    if os.path.isdir(f'{SYS}/sysroot/include/SDL2') and os.path.isdir(f'{SYS}/clang/include'):
        return True
    os.makedirs(SYS, exist_ok=True)
    img = os.environ.get('CONKER_EMSDK_IMAGE', 'conker-emsdk')
    env = dict(os.environ, PATH='/Applications/Docker.app/Contents/Resources/bin:' + os.environ['PATH'])
    cmd = (f'docker run --rm -v "{SYS}":/out {img} sh -c '
           '\'c=$(em-config CACHE); mkdir -p /out/sysroot /out/clang; '
           'cp -r "$c/sysroot/include" /out/sysroot/ && cp -r /emsdk/upstream/lib/clang/*/include /out/clang/\'')
    return subprocess.run(cmd, shell=True, env=env).returncode == 0


def make_var(name):
    """value of `NAME := ...` (with continuation lines) in port/Makefile"""
    m = re.search(rf'^{name}\s*:=\s*((?:.*\\\n)*.*)$', open('port/Makefile').read(), re.M)
    return m[1].replace('\\\n', ' ').split()


def abs_flags(flags, base):
    out, i = [], 0
    while i < len(flags):
        f = flags[i]
        if f in ('-include', '-iquote', '-isystem') and i + 1 < len(flags):
            out += [f, os.path.normpath(os.path.join(base, flags[i + 1]))]
            i += 2
            continue
        if f.startswith('-I'):
            f = '-I' + os.path.normpath(os.path.join(base, f[2:]))
        out.append(f)
        i += 1
    return out


def entry(directory, path, flags):
    f = os.path.normpath(os.path.join(directory, path))
    return {'directory': directory, 'file': f,
            'arguments': [CC] + TARGET + flags + ['-c', f, '-o', '/dev/null']}


def main():
    have_sys = sys_headers()
    game = abs_flags([a for a in census.BASE if a not in ('emcc', '-c', '-O1', '-g0')] + census.PORT_RELAX, ROOT)
    ents = [entry(ROOT, p, game) for p in sorted(glob.glob('conker/src_eu/**/*.c', recursive=True))]
    boot = [p for p in make_var('BOOT_SRC')]
    ents += [entry(ROOT, 'port/' + p, game) for p in boot]
    pc = [a for a in make_var('ULTRA_CFLAGS') if a not in ('-O2', '-g0')]
    sysinc = (['-nostdinc', '-isystem', f'{SYS}/clang/include',
               '-isystem', f'{SYS}/sysroot/include/wasm32-emscripten', '-isystem', f'{SYS}/sysroot/include',
               '-isystem', f'{SYS}/sysroot/include/compat', '-isystem', f'{SYS}/sysroot/include/SDL2'] if have_sys else [])
    pc = abs_flags(pc, f'{ROOT}/port') + sysinc + ['-DEMSCRIPTEN', '-fvisibility=hidden']
    pcsrc = [p for v in ('ULTRA_SRC', 'GFX_SRC', 'AUD_SRC') for p in make_var(v)] + ['sched_demo/demo.c', 'sched_demo/demo_stubs.c']
    ents += [entry(f'{ROOT}/port', p, pc) for p in pcsrc if p not in boot]
    json.dump(ents, open('compile_commands.json', 'w'), indent=1)
    print(f'compile_commands.json: {len(ents)} TUs ({len(ents) - len(boot) - len(pcsrc)} game, {len(boot)} port game-side, '
          f'{len(pcsrc)} PC layer){"" if have_sys else "; PC system headers missing (docker unavailable)"}')


if __name__ == '__main__':
    main()
