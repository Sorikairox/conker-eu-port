# Debugging the game's C source in the browser (P342)

The port has no native build. To debug, you run a DEBUG wasm build (DWARF, `-O0`) in Chrome and use DevTools with
Google's DWARF extension: breakpoints on C lines, stepping, locals, call stack. CLion is used for reading and
navigating the code (`compile_commands.json`), not for running it.

## One-time setup (you)

1. **Chrome extension.** Install **"C/C++ DevTools Support (DWARF)"** (publisher: Chrome DevTools / Google) from the
   Chrome Web Store (id `pdcpmagijalfljmkmjngeonclgbbannb`). Then open `chrome://extensions` → the extension →
   **Details** → turn on **"Allow access to file URLs"**. The DWARF data names host files such as
   `file:///Users/sorikairo/conker-wt/web/conker/src_eu/game_eu_90F50.c`, and the extension can only read them with
   this switch on. No path substitution is needed. If you build in another checkout, its own paths are written in.
   On an old Chrome you may also need DevTools → Settings → Experiments → "WebAssembly Debugging: Enable DWARF support".
2. **CLion.** Run `python3 tools/port/scripts/gen_compile_commands.py` (`debug_build.sh` also runs it). Then use
   File → Open → `~/conker-wt/web/compile_commands.json` → **Open as Project**. It covers all 722 game TUs, port/boot,
   port/ultra, port/gfx and port/audio, with the real flags (`-include port/ultra/port_prefix.h`, `-DPORT`,
   `-nostdinc`, the `conker/include` dirs, wasm32 target: 32-bit `long` and pointers). The PC layer's system headers
   (musl, SDL2) are copied from the emsdk image to `port/build-dbg/cc/`. Both files are generated and gitignored.
   Re-run the script after adding a source file.

## Run it

```
tools/port/scripts/debug_build.sh          # build (first time ~1-2 min, then incremental) + serve
```

It prints the page URL:

```
http://localhost:8077/app/index.html?app=game&mute=1&romurl=../dev/rom.z64&warp=29
```

- The page loads your `baserom.eu.z64` from the local server, so the ROM picker isn't needed. The server listens on
  127.0.0.1 only.
- `&warp=29` starts gameplay on level 0x29 straight from boot (no intro or menus). Any `?warp=<hex level>` works
  (`&warpscene=N` sets the entry). Leave it out to play from the boot screen. `&mute=1` is optional.
- Other commands: `debug_build.sh build` | `serve` | `stop` (stop the server when done) | `cc` (only
  compile_commands.json). Env: `PORT=8077`, `DBG_OPT=-Og` (faster game, fewer visible locals), `DBG_REV=HEAD` (build a
  commit instead of the working files).
- How it works: the sources are rsync'ed to `port/build-dbg/tree`, then built there with the normal Makefile + vbe
  pipeline in debug mode (`PORT_DBG_CFLAGS` in `port/Makefile` and `port/tools/vbe_build.py`).
  `-fdebug-prefix-map` maps the container path of that copy back to your worktree. The release build (`port/build`)
  isn't touched. **Edit the files in the worktree**, never the copy, then re-run the script.

In Chrome: open the URL → DevTools (F12) → **Sources** → Ctrl/Cmd+P → type the C file name (e.g.
`game_eu_90F50.c`) → click a line number to set a breakpoint. The game pauses there. You can step (F10 over, F11
into), see **Scope** (locals and params with C types) and **Call Stack** (C function names), and hover over
variables. Resume with F8.

## Worked example

A breakpoint that hits at once (every frame, no input needed):

1. `tools/port/scripts/debug_build.sh`, open the `&warp=29` URL.
2. Sources → `game_eu_1ACBC0.c` → breakpoint in `screen_fade_alpha` (line 36 ff.), e.g. on
   `b = g_screen_fade_alpha_override[arg0];`. It pauses on the next frame, with Call Stack
   `screen_fade_alpha ← screen_fade_is_opaque ← render_overlay_pass ← game_frame_step ← game_main_loop`. Scope shows
   `arg0` (the view) and `r`/`b`/`d`. F10 steps line by line. Remove the breakpoint and press F8 to go on.

Player actions: `player_try_begin_action` (conker/src_eu/game_eu_90F50.c:295) is called from `player_item_action`
when Conker starts a held-item or context action (it is not called on a plain jump). Put the breakpoint on line 300
(`temp_t6 = arg1 & 0xFFFF;`) and trigger the action in game. Scope then shows `arg0` (the player `struct127 *`; expand
it for its fields, see the limitation below), `arg1` (the anim id) and `arg3` (`s8` kind, shown correctly). F10 through
the `if` chain to see which test returns `0x3E7` (999 = no action). `pickup_update(u8 *obj)` (game_eu_142E40.c:4021)
works the same way in a level that has pickups (multiplayer).

## Limitation: game memory is in N64 layout ("vbe", docs/port/MEMORY.md)

Game memory keeps the N64's big-endian layout. Each aligned 32-bit word holds its value natively, so **32-bit
fields, `f32`, pointers and `s32` locals display correctly**. Sub-word data is lane-swapped: the byte at virtual address
A is stored at `A ^ 3`, the halfword at `A ^ 2`. The debugger doesn't know this, so:

- **`u8`/`s8`/`u16`/`s16` struct fields and array elements display wrong.** In a struct, `p->unk95` (a `u8` at offset
  0x95) is shown from offset 0x95 but its value is at 0x96 (0x95 ^ 3). Read it in the DevTools console (`Module` is
  the game module):
  `Module.HEAPU8[addr ^ 3]` (8-bit), `new DataView(Module.HEAPU8.buffer).getUint16(addr ^ 2, true)` (16-bit),
  `Module.HEAP32[addr >> 2]` (32-bit). Get `addr` from a pointer in Scope (right-click → copy value, or add
  `(int)&p->unk95` as a watch expression).
- **Scalar 8/16-bit locals, parameters and globals display correctly.** The build adds `+3`/`+2` to their DWARF
  location (`dbg_lanes` in port/tools/vbe.py). Local arrays and structs of sub-word type don't get this fix.
- **`s64` / `f64`** are stored with their 32-bit halves swapped: the debugger shows the halves exchanged.
- **Bitfields** use IDO's MSB-first allocation, so the debugger reads them wrong.
- **Pointers.** Every pointer the game holds at run time is a wasm address (data from `0x10000000`,
  `-sGLOBAL_BASE=256MB`), so the debugger follows it. N64 addresses (`0x80xxxxxx`, the `D_800xxxxx` names in
  port/symbols/symbols.tsv, comments) are not wasm addresses. Game data without a C definition lives in the mirror
  array `n64_rdram` at its N64 offset: **wasm = `&n64_rdram` + (n64 & 0x7FFFFF)**. Watch `&n64_rdram` to get the
  base. In C, `port_n64_to_wasm()` / `port_wasm_to_n64()` in port/ultra/pc_mem.h convert either way (data and
  functions), and `vbe_ld8/vbe_ld16` read sub-word fields correctly. The mirror labels (`D_8xxxxxxx`) have no type
  information, so you can't watch them by name.
- Values below `0x10000000` are not wasm data: RSP segment addresses (`0x0Exxxxxx`), offsets, or the null zone that
  absorbs writes through NULL pointers.

## Other limits

- `-O0` game code runs slower than the release build, but it plays (about 12 game frames/s at `det=2` in headless
  Chrome). `DBG_OPT=-Og` is faster, but more locals show as "optimized out". One TU (game_EF410.c, `bomb_explode`) is
  always built at `-O1 -g`, because the wasm backend rejects its function-address constant at `-O0`.
- Debug-only differences from the release build. Integer division by a variable uses the R4300's
  divide-by-zero results instead of a wasm trap (`dbg_div` in port/tools/vbe.py). Matched code keeps dead divisions by
  an unset local (a "fakematch" in `screen_fade_alpha`) that `-O1` deletes and `-O0` would execute. Uninitialized
  locals hold stack garbage at `-O0`, and the result is undefined in both builds.
- Game threads are ASYNCIFY fibers. A step over a call that yields (`osRecvMesg`, retrace waits) can land in another
  thread. Use breakpoints rather than long step sequences. The call stack only shows the current fiber.
- Five TUs are compiled from a patched copy (port/tools/srcfix.py). Their DWARF points at the original file with the
  same line numbers, but a patched line can look different from what runs.
- Functions that only exist as asm stubs (`port/stubs/asm_stubs.c`) have no source.

## Write watchpoint (P353)

DevTools has no data watchpoints for wasm. `DBG_WATCH=1 tools/port/scripts/debug_build.sh build` makes every store of
game code call `__port_wstore` first (port/tools/vbe.py `dbg_watch`, port/ultra/pc_nethash.c). Run the debug build with
`?watch=ADDR` (hex; an N64 address `8xxxxxxx` or a wasm address) and optionally `&watchlen=N` (hex bytes, default 4)
and `&watchmax=N` (hits, default 40): each store that touches the range logs `[watch] retrace R: n-byte store at A, old
word W` and a JS stack with the C function names. Headless example (port 8753 is arbitrary):
`WEB=$PWD/port/build-dbg/tree/port/build/web tools/port/scripts/cshot.sh out.png 450 200 '&watch=80145B8C'` then read
`out.log`. PC-layer writes (audio HLE, renderer) are not instrumented.
