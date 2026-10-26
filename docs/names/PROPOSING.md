# Proposing function names (one chunk per session)

The goal is for every `func_XXXXXXXX` to get an explicit name a human can understand and change. Proposal sessions only
**read** code and write one file; the rename itself is applied later, in one step, by `tools/eu_port/rename.py`
(docs/RENAMING.md).

## Your input
- `docs/names/chunks.tsv`: chunk number, file in `conker/src_eu`, number of unnamed functions. Take the files of your chunk.
- Hints: `docs/names/functions.tsv` (heuristic candidates and old descriptions), the existing description comment
  above each function, and the names of functions that already have names (US names in `conker/symbol_addrs.eu.txt`).

## Your output: `docs/names/proposals/chunkNN.tsv`
Tab-separated, with a header line `old	new	confidence	description`:
- `old`: `func_XXXXXXXX`, exactly as in the source (both C bodies and `#pragma GLOBAL_ASM` ones).
- `new`: snake_case. Start with a subsystem prefix shared by the file's functions where one fits (`cutscene_`, `camera_`,
  `audio_`, `menu_`, `particle_`, `player_`, `mp_` ...), then verb_noun: `cutscene_can_skip`, `camera_update_follow`,
  `particle_emitter_draw`. At most about 40 characters. Never reuse a name that already exists in the repo, or one
  used twice in your file. If you understand nothing more than the data a function touches, name it after that
  (`obj_table_clear_slot`) and set the confidence to `low`.
- `confidence`: `high` (clear from the code), `med` or `low`.
- `description`: one line, max 150 characters, saying what the function does. Don't put tabs in it.

Cover every unnamed function in your files. If you run out of budget, finish the file you're on and list the files
you didn't do in a line `# not done: file1.c file2.c` at the end.

## Rules
- Read only. Don't edit any source, don't run builds, don't run git (no commits, no stash). Write only your
  proposals file.
- Look at the callers and callees too: a function called only by `cutscene_*` code is probably cutscene code.
- Several naming sessions run at once and share one scratchpad folder: keep temporary files in a folder named after
  your chunk (`<scratchpad>/chunkNN/`), never under shared names like `out.tsv`.

# Proposing global variable names (one chunk per session)

The same for the globals: every `D_XXXXXXXX` data symbol that C code uses gets an explicit name. The rename itself is
applied later by `tools/eu_port/apply_names.sh gNN` (it must leave `conker.wasm` byte-identical: data names are not in
the binary).

## Your input
- `docs/names/globals.tsv`: chunk, symbol, home file (the C file that uses it most), files using it, uses. Take the
  rows of your chunk (`g01` ...).
- Hints: the comment on the `extern` declaration (many already say what the data is), how the code uses it (array of
  per-player values, a pointer to a struct, a frame counter, a flag tested by a menu ...), the names of the functions
  that read and write it (already renamed, `git grep -n D_XXXXXXXX -- conker/src_eu port`), and its row in
  `port/symbols/symbols.tsv` (address, size, section: `.bss`/`.data` = variable, `.rodata` = constant table/string).

## Your output: `docs/names/proposals/globalsNN.tsv`
Tab-separated, header `old	new	confidence	description`, one row per symbol of your chunk:
- `old`: `D_XXXXXXXX`.
- `new`: `g_` then snake_case, with a subsystem prefix where one fits: `g_camera_saved_states`,
  `g_player_view_flags`, `g_cutscene_skip_timer`, `g_mp_score_table`, `g_str_save_failed` (a string). At most about
  40 characters. Never reuse a name that already exists anywhere in the repo (`git grep -nw <name>` must find nothing,
  also no struct field or local of that name), nor one used twice in your file. If you only know the shape, name it
  after that (`g_obj_table_1a2c`, low confidence).
- `confidence`: `high`, `med` or `low`.
- `description`: one line, max 150 characters, what the data holds. No tabs.

Same rules as for functions: read only, write only your proposals file, no builds, no git commands that change
anything, temporary files under `<scratchpad>/globalsNN/`.
