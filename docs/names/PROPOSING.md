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
