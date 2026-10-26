# Names tables

Function and file names are `func_<ADDR>` / `game_eu_<ADDR>.c` and say nothing about what they do. These tables collect
proposed readable names for a later one-shot rename.

- `functions.tsv`: one row per `func_XXXXXXXX` defined in `src_eu` of the port, portb and web worktrees.
  Columns: address, current_name, file, proposed_name, name_source, description (<=200 chars), source, conflicts.
  `name_source`: `comment` (name written in the source comment), `candidate` (generated heuristically from the
  description, 2-4 words, unique, needs review), `none`. Preference: comment over session doc, then port, portb, web.
  `conflicts` notes differing descriptions between trees, `doc_differs`, `file_differs`, `missing_in:<tree>`, `dup_name`.
- `files.tsv`: per source file a candidate name from the dominant words of its described functions, with evidence
  counts and confidence (`ok`, `low`, `none`). Low-confidence names are only hints.

## Regenerate

    python3 tools/eu_port/names_table.py

Reads `~/conker-wt/{port,portb,web}` (read-only) and rewrites both tables. Python 3 stdlib only.

## Naming convention (for new work)

Put the proposed name first in the comment directly above the function, snake_case, followed by a colon:

    // level_request_music: requests the level's songs on load
    void func_150000B0(void) {

Older comments have no name; their text is kept as the description.

## The rename itself (later, scripted)

Not done here. Symbols: splat symbol addrs (`symbol_addrs.*.txt`) / `undefined_syms*.txt`, plus the C sources. Files:
splat yaml + Makefile. Everything keyed by address (tools, tests, docs, difftest scripts, progress tables) must be
updated in the same pass.
